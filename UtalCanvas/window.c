#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__MINGW32__) || defined(__MINGW64__) && !defined(__CYGWIN__)
    #include <windows.h>
#else
    #include <pthread.h>
    #include <unistd.h>
#endif

#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "window.h"
#include "structures.h"
#include "element_list.h"
#include "colors.h"
#include "utils.h"
#include "resources_list.h"
#include "joystick_list.h"

//titulo predefinido de la ventana
char __window_title[MAX_TEXT_LENGTH] = "UtalCanvas";

//Variables de la ventana SDL
SDL_Window* __sdl_window = NULL;
SDL_Surface* __sdl_screen_surface = NULL;
SDL_Renderer* __sdl_renderer = NULL;

//Variables del ciclo principal (game loop)
const int __FPS = 60;
bool __signal_to_end_loop = false;
bool __is_window_closed_flag = false;
const Uint8* __current_keys_state = NULL;
UtalCanvasWindowMouseInfo __current_mouse_state;

//variables usadas en metodo de pintado
bool __repaint_flag;
UtalCanvasWindowViewport viewport = {0, 0, 640, 480};
UtalCanvasWindowDimension dimension = {640, 480};
UtalCanvasColor __background = {255, 255 , 255};

//definicion de las variables para el thread
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__MINGW32__) || defined(__MINGW64__) && !defined(__CYGWIN__)
    HANDLE __windows_thread;
    HANDLE window_mutex;
#else
    pthread_t __linux_thread = 0;
    pthread_mutex_t __linux_mutex;
#endif


    
bool ucw_initialize()
{
    __mutex_init();
    __mutex_lock();
    bool success = true;
    __repaint_flag = true;
    
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0 )
    {
        fprintf(stderr, "SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            fprintf(stderr, "Warning: Linear texture filtering not enabled!");
        }

        __sdl_window = SDL_CreateWindow( __window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dimension.width, dimension.height, SDL_WINDOW_SHOWN );
        if( __sdl_window == NULL )
        {
            fprintf(stderr, "Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            __sdl_renderer = SDL_CreateRenderer( __sdl_window, -1, SDL_RENDERER_ACCELERATED );
            if( __sdl_renderer == NULL )
            {
                fprintf(stderr, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( __sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                        fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                        success = false;
                }
                
                //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    fprintf(stderr, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
                
                // Set up the audio stream
                if(MIX_INIT_MP3 != Mix_Init(MIX_INIT_MP3)) 
                {
                    printf("Mix_Init could not initialize mixer, Mix_Init Error: %s\n", Mix_GetError());
                    success = false;
                }
                
                //if( Mix_OpenAudio(44100, AUDIO_S16SYS, 4, 1024) < 0 ) //Felipe
                //if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) //Lazy Foo' Productions
                if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1 )
                {
                    fprintf(stderr, "SDL_Mixer unable to open audio! SDL_Mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
                if( Mix_AllocateChannels(32) < 0 )
                {
                    fprintf(stderr, "SDL_Mixer unable to allocate mixing channels! SDL_Mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
                
            }
        }
    }    
    __is_window_closed_flag = false;
    __mutex_unlock();
    return success;
}

void ucw_close()
{
    __mutex_lock();
    __signal_to_end_loop = true;
    __mutex_unlock();
    
    bool quit = false;
    while(!quit)
    {
        __mutex_lock();
        if( __is_window_closed_flag == true )
        {
            quit = true;
        }
        __mutex_unlock();
    }
    
    ucw_remove_all_elements();

    SDL_DestroyWindow( __sdl_window );
    __sdl_window = NULL;

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void ucw_set_viewport(double xMin, double yMin, double xUp, double yUp)
{
    __mutex_lock();
    __repaint_flag = true;
    viewport.xMin = xMin < xUp ? xMin : xUp;
    viewport.yMin = yMin < yUp ? yMin : yUp;
    viewport.xMax = xMin > xUp ? xMin : xUp;
    viewport.yMax = yMin > yUp ? yMin : yUp;
    __mutex_unlock();
}

void ucw_set_title( char title[MAX_TEXT_LENGTH] )
{
    __mutex_lock();
    SDL_SetWindowTitle(__sdl_window, title);
    __mutex_unlock();
}

void ucw_set_background(char background[COLOR_NAME_LENGTH])
{
    __mutex_lock();
    __repaint_flag = true;
    __background = get_color_by_name(background);
    __mutex_unlock();
}

int ucw_play_audio(char audio_file[PATHNAME_LENGTH], int loops)
{
    ResourceAudio* resource = resource_list_get_audio(audio_file);
    if( resource == NULL  )
    {
        resource = (ResourceAudio*)malloc(sizeof(ResourceAudio));
        resource->chunk = Mix_LoadWAV(audio_file);
        
        if( resource->chunk == NULL )
        {
            fprintf(stderr, "[UtalCanvas] Play Audio Error: %s\n", SDL_GetError() );
            return -1;
        }
    
        resource_list_add_audio(audio_file, resource);
    }
    
    //el primer parametro escoge el canal donde se reproducira, paso -1 para 
    //que se escoja utomaticamente un canal y retorno ese canal
    return Mix_PlayChannel(-1, resource->chunk, loops);
}

void ucw_pause_audio(int channel)
{
    Mix_Pause(channel);
}

void ucw_resume_audio(int channel)
{
    Mix_Resume(channel);
}

int ucw_stop_audio(int channel)
{
    return Mix_HaltChannel(channel);
}

int ucw_add_element(UtalCanvasElementType type, void* data)
{
    int index = -1;
    __mutex_lock();
    __repaint_flag = true;
    index = element_list_add(type, data);
    __mutex_unlock();
    return index;
}

void ucw_remove_element_by_id(int index)
{
    __mutex_lock();
    __repaint_flag = true;
    element_list_remove_by_index(index);
    __mutex_unlock();
}

void ucw_remove_element_by_tag(char tag[TAG_NAME_LENGTH])
{
    __mutex_lock();
    __repaint_flag = true;
    element_list_remove_by_tag(tag);
    __mutex_unlock();
}

void ucw_remove_all_elements()
{
    __mutex_lock();
    __repaint_flag = true;
    element_list_remove_all();
    __mutex_unlock();
}

void ucw_move_element_by_id(int index, double dx, double dy)
{
    __mutex_lock();
    __repaint_flag = true;
    element_list_move_by_index(index, dx, dy);
    __mutex_unlock();
}

void ucw_move_element_by_tag(char tag[TAG_NAME_LENGTH], double dx, double dy)
{
    __mutex_lock();
    __repaint_flag = true;
    element_list_move_by_tag(tag, dx, dy);
    __mutex_unlock();
}

void ucw_draw_point(void* data)
{
    ElementPoint* point = (ElementPoint*)data;
    SDL_SetRenderDrawColor( __sdl_renderer, point->color.red, point->color.green, point->color.blue, 0xFF );
    
    int x = convert_x_to_window_value(point->x, dimension, viewport);
    int y = dimension.height - convert_y_to_window_value(point->y, dimension, viewport);
    SDL_RenderDrawPoint( __sdl_renderer, x, y );
}

void ucw_draw_line(void* data)
{
    ElementLine* line = (ElementLine*)data;
    int x1 = convert_x_to_window_value(line->x1, dimension, viewport);
    int y1 = dimension.height - convert_y_to_window_value(line->y1, dimension, viewport);
    int x2 = convert_x_to_window_value(line->x2, dimension, viewport);
    int y2 = dimension.height - convert_y_to_window_value(line->y2, dimension, viewport);
    
    SDL_SetRenderDrawColor( __sdl_renderer, line->color.red, line->color.green, line->color.blue, 0xFF );
    SDL_RenderDrawLine( __sdl_renderer, x1, y1, x2, y2 );
}

void ucw_draw_rectangle(char* data)
{
    ElementRectangle* rectangle = (ElementRectangle*)data;
    SDL_SetRenderDrawColor( __sdl_renderer, rectangle->color.red, rectangle->color.green, rectangle->color.blue, 0xFF );
    UtalCanvasPlainRectangle plainRectangle;
    fix_rectangle(&plainRectangle, rectangle->x1, rectangle->y1, rectangle->x2, rectangle->y2); 
    int x = convert_x_to_window_value(plainRectangle.x, dimension, viewport);
    int y = dimension.height - convert_y_to_window_value(plainRectangle.y, dimension, viewport);
    int width = convert_x_to_window_value(plainRectangle.width, dimension, viewport);
    int height = - convert_y_to_window_value(plainRectangle.height, dimension, viewport);
    
    SDL_Rect outlineRect = { x, y, width, height };
    SDL_RenderDrawRect( __sdl_renderer, &outlineRect );
}

void ucw_fill_rectangle(char* data)
{
    ElementFilledRectangle* rectangle = (ElementFilledRectangle*)data;
    UtalCanvasPlainRectangle plainRectangle;
    fix_rectangle(&plainRectangle, rectangle->x1, rectangle->y1, rectangle->x2, rectangle->y2);
    int x = convert_x_to_window_value(plainRectangle.x, dimension, viewport);
    int y = dimension.height - convert_y_to_window_value(plainRectangle.y, dimension, viewport);
    int width = convert_x_to_window_value(plainRectangle.width, dimension, viewport);
    int height = - convert_y_to_window_value(plainRectangle.height, dimension, viewport);
    SDL_Rect rect = { x, y, width, height };

    SDL_SetRenderDrawColor( __sdl_renderer, rectangle->fillColor.red, rectangle->fillColor.green, rectangle->fillColor.blue, 0xFF );
    SDL_RenderFillRect( __sdl_renderer, &rect );
    SDL_SetRenderDrawColor( __sdl_renderer, rectangle->outerColor.red, rectangle->outerColor.green, rectangle->outerColor.blue, 0xFF );
    SDL_RenderDrawRect( __sdl_renderer, &rect );
}

void ucw_draw_circle(char* data)
{
    ElementCircle* circle = (ElementCircle*)data;
    __ucw_draw_ellipse(circle);
}

void ucw_fill_circle(void* data)
{
    ElementFilledCircle* filledCircle = (ElementFilledCircle*)data;
    __ucw_fill_ellipse(filledCircle);
    
    ElementCircle* circle = (ElementCircle*)malloc(sizeof(ElementCircle));
    circle->x = filledCircle->x;
    circle->y = filledCircle->y;
    circle->color = filledCircle->outerColor;
    circle->radio = filledCircle->radio;
    __ucw_draw_ellipse(circle);
    free(circle);
}

void ucw_draw_image(void* data)
{
    ElementImage* image = (ElementImage*)data;
    int width = convert_x_to_window_value(image->width, dimension, viewport);
    int height = convert_y_to_window_value(image->height, dimension, viewport);
    int x = convert_x_to_window_value(image->x, dimension, viewport);
    int y = dimension.height - convert_y_to_window_value(image->y, dimension, viewport) - height;
    
    
    ResourceImage* resource = resource_list_get_image(image->filename);
    if( resource == NULL )
    {
        SDL_Surface* surface = IMG_Load( image->filename );
        if(surface == NULL)
        {
            return;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface( __sdl_renderer, surface );
        if(texture == NULL)
        {
            return;
        }
        
        SDL_Rect* size = (SDL_Rect*)malloc(sizeof(SDL_Rect));
        size->x = 0;
        size->y = 0;
        size->w = surface->w;
        size->h = surface->h;
        
        
        resource = (ResourceImage*)malloc(sizeof(ResourceImage));
        resource->texture = texture;
        resource->size = size;
        
        if( resource_list_add_image(image->filename, resource) == false)
        {
            return;
        }
        SDL_FreeSurface(surface);
        surface = NULL;
    }
    
    image->texture = resource->texture;
    image->size = resource->size;
    
    SDL_Rect location = {x, y, width, height};
    SDL_RenderCopy( __sdl_renderer, image->texture, image->size, &location );
}

void UtalCanvasWindowDrawText(void* data)
{
    ElementText* text = (ElementText*)data;
    
    if( text->font == NULL )
    {
        char name[TAG_NAME_LENGTH];
        snprintf( name, TAG_NAME_LENGTH, "%f:%s", text->size,  text->fontFile );

        ResourceFont* font = resource_list_get_font(name);
        if(font == NULL)
        {
            font = (ResourceFont*)malloc(sizeof(ResourceFont));

            font->font = TTF_OpenFont( text->fontFile, text->size );
            if( font->font == NULL)
            {
                return;
            }
            resource_list_add_font(name, font);
        }
        text->font = font->font;

        SDL_Color textColor = { text->color.red, text->color.green, text->color.blue };
        text->textSurface = TTF_RenderText_Solid( font->font, text->text, textColor );

        if( text->textSurface == NULL )
        {
            text->font = NULL;
            return;
        }

        text->texture = SDL_CreateTextureFromSurface( __sdl_renderer, text->textSurface );
        if( text->texture == NULL )
        {
            text->font = NULL;
            return;
        }
    }
    
    int mWidth = text->textSurface->w;
    int mHeight = text->textSurface->h;
    int x = convert_x_to_window_value(text->x, dimension, viewport);
    int y = dimension.height - mHeight - convert_y_to_window_value(text->y, dimension, viewport);
    
    SDL_Rect clip = { 0, 0, mWidth, mWidth };
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopyEx( __sdl_renderer, text->texture, &clip, &renderQuad, 0, NULL, SDL_FLIP_NONE  );
}


void ucw_loop()
{
    SDL_Joystick *joystick;
    JoystickData* jdata;
    JoystickNode* jnode;
    int which;
    
    long frame_time = 1000.0/__FPS;
    long previous_time;
    long current_time;
    long total_loop_time;
    long delay_time;
    
    SDL_Event e;
    int x, y;
    bool quit = false;
    
    __mutex_lock();
    __is_window_closed_flag = false;
    __mutex_unlock();
    
    previous_time = SDL_GetTicks();
    
    while( !quit )
    {
        __mutex_lock();
        
        while( SDL_PollEvent( &e ) != 0 )
        {
            switch(e.type)
            {
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState( &x, &y );
                    __current_mouse_state.x = convert_x_to_world_value(x, dimension, viewport);
                    __current_mouse_state.y =  convert_y_to_world_value(dimension.height - y, dimension, viewport);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    __current_mouse_state.button = e.button.button;
                    break;
                case SDL_MOUSEBUTTONUP:
                    __current_mouse_state.button = -1;
                    break;
                case SDL_JOYBUTTONDOWN:
                    which = e.jdevice.which;
                    jdata = get_joystick_data(e.jbutton.which);
                    if(jdata != NULL)
                    {
                        jdata->buttons[e.jbutton.button] = true;
                    }
                    break;
                case SDL_JOYBUTTONUP:
                    which = e.jdevice.which;
                    jdata = get_joystick_data(e.jbutton.which);
                    if(jdata != NULL)
                    {
                        jdata->buttons[e.jbutton.button] = false;
                    }
                    break;
                case SDL_JOYAXISMOTION:
                    which = e.jdevice.which;
                    jdata = get_joystick_data(e.jbutton.which);
                    if(jdata != NULL)
                    {
                        jdata->axis[e.jaxis.axis] = e.jaxis.value;
                    }
                    break;
                case SDL_JOYBALLMOTION:
                    break;
                case SDL_JOYHATMOTION:
                    break;
                case SDL_JOYDEVICEADDED:
                    which = e.jdevice.which;
                    joystick = SDL_JoystickOpen(which);
                    jdata = __create_joystick_data(joystick);
                    register_joystick(e.jdevice.which, jdata);
                    break;
                case SDL_JOYDEVICEREMOVED:
                    which = e.jdevice.which;
                    jnode = get_joystick(which);
                    if(jnode != NULL)
                    {
                        jdata = jnode->data;
                        if( jdata != NULL )
                        {
                            SDL_JoystickClose(jdata->joystick);
                            remove_joystick(jnode->which);
                            fflush(stdout);
                        }
                    }
                    break;
                
                case SDL_QUIT:
                    quit = true;
                    break;
            }    
        }
        
        __current_keys_state = SDL_GetKeyboardState(NULL);

        if(  __repaint_flag )
        {
            __repaint_flag = false;
            
            SDL_SetRenderDrawColor( __sdl_renderer, __background.red, __background.green, __background.blue, 0xFF );
            SDL_RenderClear( __sdl_renderer );

            UtalCanvasNode* node = __get_root();
            if( node != NULL )
            {
                do
                {
                    switch(node->type)
                    {
                        case ELEMENT_POINT            : ucw_draw_point(node->data);           break;
                        case ELEMENT_LINE             : ucw_draw_line(node->data);            break;
                        case ELEMENT_RECTANGLE        : ucw_draw_rectangle(node->data);       break;
                        case ELEMENT_FILLED_RECTANGLE : ucw_fill_rectangle(node->data);       break;
                        case ELEMENT_CIRCLE           : ucw_draw_circle(node->data);          break;
                        case ELEMENT_FILLED_CIRCLE    : ucw_fill_circle(node->data);          break;
                        case ELEMENT_IMAGE            : ucw_draw_image(node->data);           break;
                        case ELEMENT_TEXT             : UtalCanvasWindowDrawText(node->data); break;
                    }
                    node = node->next;
                }
                while( node != __get_root() );
            }
        }
        
        if( __signal_to_end_loop == true )
        {
            quit = true;
        }
        
        SDL_RenderPresent( __sdl_renderer );
        SDL_UpdateWindowSurface( __sdl_window );
        __mutex_unlock();
        
        current_time = SDL_GetTicks();
        total_loop_time = current_time - previous_time;
        previous_time = current_time;
        
        delay_time = 1;
        if( total_loop_time < frame_time )
        {
            delay_time = frame_time - total_loop_time;
        }
        
        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__MINGW32__) || defined(__MINGW64__) && !defined(__CYGWIN__)
            Sleep(delay_time);
        #else
            usleep(1000*delay_time);
        #endif
        
        
    }
    
    __mutex_lock();
    __is_window_closed_flag = true;
    __mutex_unlock();
}

bool ucw_is_closed()
{
    __mutex_lock();
    bool state = __is_window_closed_flag;
    __mutex_unlock();
    return state;
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__MINGW32__) || defined(__MINGW64__) && !defined(__CYGWIN__)
DWORD WINAPI loop(void* args)
{
    if( !ucw_initialize() )
    {
        return 0;
    }
    ucw_loop();
    return 0;
}
#else
void* loop(void* args)
{
    if( !ucw_initialize() )
    {
        return NULL;
    }
    ucw_loop();
    return NULL;
}

#endif


void ucw_start()
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__MINGW32__) || defined(__MINGW64__) && !defined(__CYGWIN__)
        if(__windows_thread != NULL)
            return;
        __windows_thread = CreateThread(NULL, 0, loop, NULL, 0, NULL);
    #else
        if(__linux_thread != 0)
            return;
        pthread_create(&__linux_thread, NULL, loop, NULL);
    #endif
}

void ucw_set_size(int width, int height)
{
    __mutex_lock();
    
    __repaint_flag = true;
    
    dimension.width = width;
    dimension.height = height;
    
    if( __sdl_window != NULL )
    {
        SDL_SetWindowSize(__sdl_window, width, height);
    }
    
    __mutex_unlock();
}




void __ucw_draw_ellipse(ElementCircle* circle)
{
    int x = convert_x_to_window_value(circle->x, dimension, viewport);
    int y = dimension.height - convert_y_to_window_value(circle->y, dimension, viewport);
    int rx = convert_x_to_window_value(circle->radio, dimension, viewport);
    int ry = convert_y_to_window_value(circle->radio, dimension, viewport);
    
    int ix, iy;
    int h, i, j, k;
    int oh, oi, oj, ok;
    int xmh, xph, ypk, ymk;
    int xmi, xpi, ymj, ypj;
    int xmj, xpj, ymi, ypi;
    int xmk, xpk, ymh, yph;

    SDL_SetRenderDrawColor(__sdl_renderer, circle->color.red, circle->color.green, circle->color.blue, 0xFF);
    
    //Caso en el que que el radio en el eje X sea cero
    if (rx == 0) 
    {
        SDL_RenderDrawLine(__sdl_renderer, x, y - ry, x, y + ry);
    }
    
    //Caso en el que el radio en el eje Y sea cero
    if (ry == 0) 
    {
        SDL_RenderDrawLine(__sdl_renderer, x - rx, y, x + rx, y);
    }
    
    oh = oi = oj = ok = 0xFFFF;
    
    if (rx > ry) 
    {
        ix = 0;
	iy = rx * 64;
        
	do 
        {
            h = (ix + 32) >> 6;
            i = (iy + 32) >> 6;
            j = (h * ry) / rx;
            k = (i * ry) / rx;
            
            if (((ok != k) && (oj != k)) || ((oj != j) && (ok != j)) || (k != j)) 
            {
                xph = x + h;
                xmh = x - h;
                if (k > 0) 
                {
                    ypk = y + k;
                    ymk = y - k;
                    SDL_RenderDrawPoint(__sdl_renderer, xmh, ypk);
                    SDL_RenderDrawPoint(__sdl_renderer, xph, ypk);
                    SDL_RenderDrawPoint(__sdl_renderer, xmh, ymk);
                    SDL_RenderDrawPoint(__sdl_renderer, xph, ymk);
                } 
                else 
                {
                    SDL_RenderDrawPoint(__sdl_renderer, xmh, y);
                    SDL_RenderDrawPoint(__sdl_renderer, xph, y);
                }
                
                ok = k;
                xpi = x + i;
                xmi = x - i;
                if (j > 0) 
                {
                    ypj = y + j;
                    ymj = y - j;
                    SDL_RenderDrawPoint(__sdl_renderer, xmi, ypj);
                    SDL_RenderDrawPoint(__sdl_renderer, xpi, ypj);
                    SDL_RenderDrawPoint(__sdl_renderer, xmi, ymj);
                    SDL_RenderDrawPoint(__sdl_renderer, xpi, ymj);
                } 
                else 
                {
                    SDL_RenderDrawPoint(__sdl_renderer, xmi, y);
                    SDL_RenderDrawPoint(__sdl_renderer, xpi, y);
                }
                oj = j;
            }

            ix = ix + iy / rx;
            iy = iy - ix / rx;
        } 
        while (i > h);
    } 
    else 
    {
        ix = 0;
        iy = ry * 64;

        do 
        {
            h = (ix + 32) >> 6;
            i = (iy + 32) >> 6;
            j = (h * rx) / ry;
            k = (i * rx) / ry;

            if (((oi != i) && (oh != i)) || ((oh != h) && (oi != h) && (i != h))) 
            {
                xmj = x - j;
                xpj = x + j;
                if (i > 0) 
                {
                    ypi = y + i;
                    ymi = y - i;
                    SDL_RenderDrawPoint(__sdl_renderer, xmj, ypi); 
                    SDL_RenderDrawPoint(__sdl_renderer, xpj, ypi); 
                    SDL_RenderDrawPoint(__sdl_renderer, xmj, ymi); 
                    SDL_RenderDrawPoint(__sdl_renderer, xpj, ymi);
                } 
                else 
                {
                    SDL_RenderDrawPoint(__sdl_renderer, xmj, y);
                    SDL_RenderDrawPoint(__sdl_renderer, xpj, y);
                }
                oi = i;
                xmk = x - k;
                xpk = x + k;
                if (h > 0) 
                {
                    yph = y + h;
                    ymh = y - h;
                    SDL_RenderDrawPoint(__sdl_renderer, xmk, yph);
                    SDL_RenderDrawPoint(__sdl_renderer, xpk, yph);
                    SDL_RenderDrawPoint(__sdl_renderer, xmk, ymh);
                    SDL_RenderDrawPoint(__sdl_renderer, xpk, ymh);
                } 
                else 
                {
                    SDL_RenderDrawPoint(__sdl_renderer, xmk, y);
                    SDL_RenderDrawPoint(__sdl_renderer, xpk, y);
                }
                oh = h;
            }
            
            ix = ix + iy / ry;
            iy = iy - ix / ry;
        } 
        while (i > h);
    }
}

void __ucw_fill_ellipse(ElementFilledCircle* circle)
{
    int x = convert_x_to_window_value(circle->x, dimension, viewport);
    int y = dimension.height - convert_y_to_window_value(circle->y, dimension, viewport);
    int rx = convert_x_to_window_value(circle->radio, dimension, viewport);
    int ry = convert_y_to_window_value(circle->radio, dimension, viewport);
    
    int ix, iy;
    int h, i, j, k;
    int oh, oi, oj, ok;
    int xmh, xph;
    int xmi, xpi;
    int xmj, xpj;
    int xmk, xpk;

    SDL_SetRenderDrawColor(__sdl_renderer, circle->fillColor.red, circle->fillColor.green, circle->fillColor.blue, 0xFF);
    
    //Caso en el que el radio en el eje X sea cero
    if (rx == 0) 
    {
        SDL_RenderDrawLine(__sdl_renderer, x, y - ry, x, y + ry);
    }
    
    //Caso en el que el radio en el eje Y sea cero
    if (ry == 0) 
    {
        SDL_RenderDrawLine(__sdl_renderer, x - rx, y, x + rx, y);
    }

    oh = oi = oj = ok = 0xFFFF;
    if (rx > ry) 
    {
        ix = 0;
        iy = rx * 64;

        do 
        {
            h = (ix + 32) >> 6;
            i = (iy + 32) >> 6;
            j = (h * ry) / rx;
            k = (i * ry) / rx;

            if ((ok != k) && (oj != k)) 
            {
                xph = x + h;
                xmh = x - h;
                if (k > 0) 
                {
                    SDL_RenderDrawLine(__sdl_renderer, xmh, y + k, xph, y + k);
                    SDL_RenderDrawLine(__sdl_renderer, xmh, y - k, xph, y - k);
                } 
                else 
                {
                    SDL_RenderDrawLine(__sdl_renderer, xmh, y, xph, y);
                }
                ok = k;
            }
            if ((oj != j) && (ok != j) && (k != j)) 
            {
                xmi = x - i;
                xpi = x + i;
                if (j > 0) 
                {
                    SDL_RenderDrawLine(__sdl_renderer, xmi, y + j, xpi, y + j);
                    SDL_RenderDrawLine(__sdl_renderer, xmi, y - j, xpi, y - j);
                } 
                else 
                {
                    SDL_RenderDrawLine(__sdl_renderer, xmi, y, xpi, y);
                }
                oj = j;
            }

            ix = ix + iy / rx;
            iy = iy - ix / rx;
        } 
        while (i > h);
    } 
    else 
    {
        ix = 0;
        iy = ry * 64;

        do 
        {
            h = (ix + 32) >> 6;
            i = (iy + 32) >> 6;
            j = (h * rx) / ry;
            k = (i * rx) / ry;

            if ((oi != i) && (oh != i)) 
            {
                xmj = x - j;
                xpj = x + j;
                if (i > 0) 
                {
                    SDL_RenderDrawLine(__sdl_renderer, xmj, y + i, xpj, y + i);
                    SDL_RenderDrawLine(__sdl_renderer, xmj, y - i, xpj, y - i);
                } 
                else 
                {
                    SDL_RenderDrawLine(__sdl_renderer, xmj, y, xpj, y);
                }
                oi = i;
            }
            if ((oh != h) && (oi != h) && (i != h)) 
            {
                xmk = x - k;
                xpk = x + k;
                if (h > 0) 
                {
                    SDL_RenderDrawLine(__sdl_renderer, xmk, y + h, xpk, y + h);
                    SDL_RenderDrawLine(__sdl_renderer, xmk, y - h, xpk, y - h);
                } 
                else 
                {
                    SDL_RenderDrawLine(__sdl_renderer, xmk, y, xpk, y);
                }
                oh = h;
            }

            ix = ix + iy / ry;
            iy = iy - ix / ry;
        } 
        while (i > h);
    }
}

UtalCanvasKey ucw_get_key_pressed()
{
    int key = UTALKEY_NONE;
    
    __mutex_lock();
    if( __current_keys_state != NULL )
    {
        if(__current_keys_state[SDL_SCANCODE_0]                       == 1){ key = UTALKEY_0;                 }
        else if(__current_keys_state[SDL_SCANCODE_1]                  == 1){ key = UTALKEY_1;                 }
        else if(__current_keys_state[SDL_SCANCODE_2]                  == 1){ key = UTALKEY_2;                 }
        else if(__current_keys_state[SDL_SCANCODE_3]                  == 1){ key = UTALKEY_3;                 }
        else if(__current_keys_state[SDL_SCANCODE_4]                  == 1){ key = UTALKEY_4;                 }
        else if(__current_keys_state[SDL_SCANCODE_5]                  == 1){ key = UTALKEY_5;                 }
        else if(__current_keys_state[SDL_SCANCODE_6]                  == 1){ key = UTALKEY_6;                 }
        else if(__current_keys_state[SDL_SCANCODE_7]                  == 1){ key = UTALKEY_7;                 }
        else if(__current_keys_state[SDL_SCANCODE_8]                  == 1){ key = UTALKEY_8;                 }
        else if(__current_keys_state[SDL_SCANCODE_9]                  == 1){ key = UTALKEY_9;                 }
        else if(__current_keys_state[SDL_SCANCODE_A]                  == 1){ key = UTALKEY_A;                 }
        else if(__current_keys_state[SDL_SCANCODE_AC_BACK]            == 1){ key = UTALKEY_AC_BACK;           }
        else if(__current_keys_state[SDL_SCANCODE_AC_BOOKMARKS]       == 1){ key = UTALKEY_AC_BOOKMARKS;      }
        else if(__current_keys_state[SDL_SCANCODE_AC_FORWARD]         == 1){ key = UTALKEY_AC_FORWARD;        }
        else if(__current_keys_state[SDL_SCANCODE_AC_HOME]            == 1){ key = UTALKEY_AC_HOME;           }
        else if(__current_keys_state[SDL_SCANCODE_AC_REFRESH]         == 1){ key = UTALKEY_AC_REFRESH;        }
        else if(__current_keys_state[SDL_SCANCODE_AC_SEARCH]          == 1){ key = UTALKEY_AC_SEARCH;         }
        else if(__current_keys_state[SDL_SCANCODE_AC_STOP]            == 1){ key = UTALKEY_AC_STOP;           }
        else if(__current_keys_state[SDL_SCANCODE_AGAIN]              == 1){ key = UTALKEY_AGAIN;             }
        else if(__current_keys_state[SDL_SCANCODE_ALTERASE]           == 1){ key = UTALKEY_ALTERASE;          }
        else if(__current_keys_state[SDL_SCANCODE_APOSTROPHE]         == 1){ key = UTALKEY_APOSTROPHE;        }
        else if(__current_keys_state[SDL_SCANCODE_APPLICATION]        == 1){ key = UTALKEY_APPLICATION;       }
        else if(__current_keys_state[SDL_SCANCODE_AUDIOMUTE]          == 1){ key = UTALKEY_AUDIOMUTE;         }
        else if(__current_keys_state[SDL_SCANCODE_AUDIONEXT]          == 1){ key = UTALKEY_AUDIONEXT;         }
        else if(__current_keys_state[SDL_SCANCODE_AUDIOPLAY]          == 1){ key = UTALKEY_AUDIOPLAY;         }
        else if(__current_keys_state[SDL_SCANCODE_AUDIOPREV]          == 1){ key = UTALKEY_AUDIOPREV;         }
        else if(__current_keys_state[SDL_SCANCODE_AUDIOSTOP]          == 1){ key = UTALKEY_AUDIOSTOP;         }
        else if(__current_keys_state[SDL_SCANCODE_B]                  == 1){ key = UTALKEY_B;                 }
        else if(__current_keys_state[SDL_SCANCODE_BACKSLASH]          == 1){ key = UTALKEY_BACKSLASH;         }
        else if(__current_keys_state[SDL_SCANCODE_BACKSPACE]          == 1){ key = UTALKEY_BACKSPACE;         }
        else if(__current_keys_state[SDL_SCANCODE_BRIGHTNESSDOWN]     == 1){ key = UTALKEY_BRIGHTNESSDOWN;    }
        else if(__current_keys_state[SDL_SCANCODE_BRIGHTNESSUP]       == 1){ key = UTALKEY_BRIGHTNESSUP;      }
        else if(__current_keys_state[SDL_SCANCODE_C]                  == 1){ key = UTALKEY_C;                 }
        else if(__current_keys_state[SDL_SCANCODE_CALCULATOR]         == 1){ key = UTALKEY_CALCULATOR;        }
        else if(__current_keys_state[SDL_SCANCODE_CANCEL]             == 1){ key = UTALKEY_CANCEL;            }
        else if(__current_keys_state[SDL_SCANCODE_CAPSLOCK]           == 1){ key = UTALKEY_CAPSLOCK;          }
        else if(__current_keys_state[SDL_SCANCODE_CLEAR]              == 1){ key = UTALKEY_CLEAR;             }
        else if(__current_keys_state[SDL_SCANCODE_CLEARAGAIN]         == 1){ key = UTALKEY_CLEARAGAIN;        }
        else if(__current_keys_state[SDL_SCANCODE_COMMA]              == 1){ key = UTALKEY_COMMA;             }
        else if(__current_keys_state[SDL_SCANCODE_COMPUTER]           == 1){ key = UTALKEY_COMPUTER;          }
        else if(__current_keys_state[SDL_SCANCODE_COPY]               == 1){ key = UTALKEY_COPY;              }
        else if(__current_keys_state[SDL_SCANCODE_CRSEL]              == 1){ key = UTALKEY_CRSEL;             }
        else if(__current_keys_state[SDL_SCANCODE_CURRENCYSUBUNIT]    == 1){ key = UTALKEY_CURRENCYSUBUNIT;   }
        else if(__current_keys_state[SDL_SCANCODE_CURRENCYUNIT]       == 1){ key = UTALKEY_CURRENCYUNIT;      }
        else if(__current_keys_state[SDL_SCANCODE_CUT]                == 1){ key = UTALKEY_CUT;               }
        else if(__current_keys_state[SDL_SCANCODE_D]                  == 1){ key = UTALKEY_D;                 }
        else if(__current_keys_state[SDL_SCANCODE_DECIMALSEPARATOR]   == 1){ key = UTALKEY_DECIMALSEPARATOR;  }
        else if(__current_keys_state[SDL_SCANCODE_DELETE]             == 1){ key = UTALKEY_DELETE;            }
        else if(__current_keys_state[SDL_SCANCODE_DISPLAYSWITCH]      == 1){ key = UTALKEY_DISPLAYSWITCH;     }
        else if(__current_keys_state[SDL_SCANCODE_DOWN]               == 1){ key = UTALKEY_DOWN;              }
        else if(__current_keys_state[SDL_SCANCODE_E]                  == 1){ key = UTALKEY_E;                 }
        else if(__current_keys_state[SDL_SCANCODE_EJECT]              == 1){ key = UTALKEY_EJECT;             }
        else if(__current_keys_state[SDL_SCANCODE_END]                == 1){ key = UTALKEY_END;               }
        else if(__current_keys_state[SDL_SCANCODE_EQUALS]             == 1){ key = UTALKEY_EQUALS;            }
        else if(__current_keys_state[SDL_SCANCODE_ESCAPE]             == 1){ key = UTALKEY_ESCAPE;            }
        else if(__current_keys_state[SDL_SCANCODE_EXECUTE]            == 1){ key = UTALKEY_EXECUTE;           }
        else if(__current_keys_state[SDL_SCANCODE_EXSEL]              == 1){ key = UTALKEY_EXSEL;             }
        else if(__current_keys_state[SDL_SCANCODE_F]                  == 1){ key = UTALKEY_F;                 }
        else if(__current_keys_state[SDL_SCANCODE_F1]                 == 1){ key = UTALKEY_F1;                }
        else if(__current_keys_state[SDL_SCANCODE_F10]                == 1){ key = UTALKEY_F10;               }
        else if(__current_keys_state[SDL_SCANCODE_F11]                == 1){ key = UTALKEY_F11;               }
        else if(__current_keys_state[SDL_SCANCODE_F12]                == 1){ key = UTALKEY_F12;               }
        else if(__current_keys_state[SDL_SCANCODE_F13]                == 1){ key = UTALKEY_F13;               }
        else if(__current_keys_state[SDL_SCANCODE_F14]                == 1){ key = UTALKEY_F14;               }
        else if(__current_keys_state[SDL_SCANCODE_F15]                == 1){ key = UTALKEY_F15;               }
        else if(__current_keys_state[SDL_SCANCODE_F16]                == 1){ key = UTALKEY_F16;               }
        else if(__current_keys_state[SDL_SCANCODE_F17]                == 1){ key = UTALKEY_F17;               }
        else if(__current_keys_state[SDL_SCANCODE_F18]                == 1){ key = UTALKEY_F18;               }
        else if(__current_keys_state[SDL_SCANCODE_F19]                == 1){ key = UTALKEY_F19;               }
        else if(__current_keys_state[SDL_SCANCODE_F2]                 == 1){ key = UTALKEY_F2;                }
        else if(__current_keys_state[SDL_SCANCODE_F20]                == 1){ key = UTALKEY_F20;               }
        else if(__current_keys_state[SDL_SCANCODE_F21]                == 1){ key = UTALKEY_F21;               }
        else if(__current_keys_state[SDL_SCANCODE_F22]                == 1){ key = UTALKEY_F22;               }
        else if(__current_keys_state[SDL_SCANCODE_F23]                == 1){ key = UTALKEY_F23;               }
        else if(__current_keys_state[SDL_SCANCODE_F24]                == 1){ key = UTALKEY_F24;               }
        else if(__current_keys_state[SDL_SCANCODE_F3]                 == 1){ key = UTALKEY_F3;                }
        else if(__current_keys_state[SDL_SCANCODE_F4]                 == 1){ key = UTALKEY_F4;                }
        else if(__current_keys_state[SDL_SCANCODE_F5]                 == 1){ key = UTALKEY_F5;                }
        else if(__current_keys_state[SDL_SCANCODE_F6]                 == 1){ key = UTALKEY_F6;                }
        else if(__current_keys_state[SDL_SCANCODE_F7]                 == 1){ key = UTALKEY_F7;                }
        else if(__current_keys_state[SDL_SCANCODE_F8]                 == 1){ key = UTALKEY_F8;                }
        else if(__current_keys_state[SDL_SCANCODE_F9]                 == 1){ key = UTALKEY_F9;                }
        else if(__current_keys_state[SDL_SCANCODE_FIND]               == 1){ key = UTALKEY_FIND;              }
        else if(__current_keys_state[SDL_SCANCODE_G]                  == 1){ key = UTALKEY_G;                 }
        else if(__current_keys_state[SDL_SCANCODE_GRAVE]              == 1){ key = UTALKEY_GRAVE;             }
        else if(__current_keys_state[SDL_SCANCODE_H]                  == 1){ key = UTALKEY_H;                 }
        else if(__current_keys_state[SDL_SCANCODE_HELP]               == 1){ key = UTALKEY_HELP;              }
        else if(__current_keys_state[SDL_SCANCODE_HOME]               == 1){ key = UTALKEY_HOME;              }
        else if(__current_keys_state[SDL_SCANCODE_I]                  == 1){ key = UTALKEY_I;                 }
        else if(__current_keys_state[SDL_SCANCODE_INSERT]             == 1){ key = UTALKEY_INSERT;            }
        else if(__current_keys_state[SDL_SCANCODE_J]                  == 1){ key = UTALKEY_J;                 }
        else if(__current_keys_state[SDL_SCANCODE_K]                  == 1){ key = UTALKEY_K;                 }
        else if(__current_keys_state[SDL_SCANCODE_KBDILLUMDOWN]       == 1){ key = UTALKEY_KBDILLUMDOWN;      }
        else if(__current_keys_state[SDL_SCANCODE_KBDILLUMTOGGLE]     == 1){ key = UTALKEY_KBDILLUMTOGGLE;    }
        else if(__current_keys_state[SDL_SCANCODE_KBDILLUMUP]         == 1){ key = UTALKEY_KBDILLUMUP;        }
        else if(__current_keys_state[SDL_SCANCODE_KP_0]               == 1){ key = UTALKEY_KP_0;              }
        else if(__current_keys_state[SDL_SCANCODE_KP_00]              == 1){ key = UTALKEY_KP_00;             }
        else if(__current_keys_state[SDL_SCANCODE_KP_000]             == 1){ key = UTALKEY_KP_000;            }
        else if(__current_keys_state[SDL_SCANCODE_KP_1]               == 1){ key = UTALKEY_KP_1;              }
        else if(__current_keys_state[SDL_SCANCODE_KP_2]               == 1){ key = UTALKEY_KP_2;              }
        else if(__current_keys_state[SDL_SCANCODE_KP_3]               == 1){ key = UTALKEY_KP_3;              }
        else if(__current_keys_state[SDL_SCANCODE_KP_4]               == 1){ key = UTALKEY_KP_4;              }
        else if(__current_keys_state[SDL_SCANCODE_KP_5]               == 1){ key = UTALKEY_KP_5;              }
        else if(__current_keys_state[SDL_SCANCODE_KP_6]               == 1){ key = UTALKEY_KP_6;              }
        else if(__current_keys_state[SDL_SCANCODE_KP_7]               == 1){ key = UTALKEY_KP_7;              }
        else if(__current_keys_state[SDL_SCANCODE_KP_8]               == 1){ key = UTALKEY_KP_8;              }
        else if(__current_keys_state[SDL_SCANCODE_KP_9]               == 1){ key = UTALKEY_KP_9;              }
        else if(__current_keys_state[SDL_SCANCODE_KP_A]               == 1){ key = UTALKEY_KP_A;              }
        else if(__current_keys_state[SDL_SCANCODE_KP_AMPERSAND]       == 1){ key = UTALKEY_KP_AMPERSAND;      }
        else if(__current_keys_state[SDL_SCANCODE_KP_AT]              == 1){ key = UTALKEY_KP_AT;             }
        else if(__current_keys_state[SDL_SCANCODE_KP_B]               == 1){ key = UTALKEY_KP_B;              }
        else if(__current_keys_state[SDL_SCANCODE_KP_BACKSPACE]       == 1){ key = UTALKEY_KP_BACKSPACE;      }
        else if(__current_keys_state[SDL_SCANCODE_KP_BINARY]          == 1){ key = UTALKEY_KP_BINARY;         }
        else if(__current_keys_state[SDL_SCANCODE_KP_C]               == 1){ key = UTALKEY_KP_C;              }
        else if(__current_keys_state[SDL_SCANCODE_KP_CLEAR]           == 1){ key = UTALKEY_KP_CLEAR;          }
        else if(__current_keys_state[SDL_SCANCODE_KP_CLEARENTRY]      == 1){ key = UTALKEY_KP_CLEARENTRY;     }
        else if(__current_keys_state[SDL_SCANCODE_KP_COLON]           == 1){ key = UTALKEY_KP_COLON;          }
        else if(__current_keys_state[SDL_SCANCODE_KP_COMMA]           == 1){ key = UTALKEY_KP_COMMA;          }
        else if(__current_keys_state[SDL_SCANCODE_KP_D]               == 1){ key = UTALKEY_KP_D;              }
        else if(__current_keys_state[SDL_SCANCODE_KP_DBLAMPERSAND]    == 1){ key = UTALKEY_KP_DBLAMPERSAND;   }
        else if(__current_keys_state[SDL_SCANCODE_KP_DBLVERTICALBAR]  == 1){ key = UTALKEY_KP_DBLVERTICALBAR; }
        else if(__current_keys_state[SDL_SCANCODE_KP_DECIMAL]         == 1){ key = UTALKEY_KP_DECIMAL;        }
        else if(__current_keys_state[SDL_SCANCODE_KP_DIVIDE]          == 1){ key = UTALKEY_KP_DIVIDE;         }
        else if(__current_keys_state[SDL_SCANCODE_KP_E]               == 1){ key = UTALKEY_KP_E;              }
        else if(__current_keys_state[SDL_SCANCODE_KP_ENTER]           == 1){ key = UTALKEY_KP_ENTER;          }
        else if(__current_keys_state[SDL_SCANCODE_KP_EQUALS]          == 1){ key = UTALKEY_KP_EQUALS;         }
        else if(__current_keys_state[SDL_SCANCODE_KP_EQUALSAS400]     == 1){ key = UTALKEY_KP_EQUALSAS400;    }
        else if(__current_keys_state[SDL_SCANCODE_KP_EXCLAM]          == 1){ key = UTALKEY_KP_EXCLAM;         }
        else if(__current_keys_state[SDL_SCANCODE_KP_F]               == 1){ key = UTALKEY_KP_F;              }
        else if(__current_keys_state[SDL_SCANCODE_KP_GREATER]         == 1){ key = UTALKEY_KP_GREATER;        }
        else if(__current_keys_state[SDL_SCANCODE_KP_HASH]            == 1){ key = UTALKEY_KP_HASH;           }
        else if(__current_keys_state[SDL_SCANCODE_KP_HEXADECIMAL]     == 1){ key = UTALKEY_KP_HEXADECIMAL;    }
        else if(__current_keys_state[SDL_SCANCODE_KP_LEFTBRACE]       == 1){ key = UTALKEY_KP_LEFTBRACE;      }
        else if(__current_keys_state[SDL_SCANCODE_KP_LEFTPAREN]       == 1){ key = UTALKEY_KP_LEFTPAREN;      }
        else if(__current_keys_state[SDL_SCANCODE_KP_LESS]            == 1){ key = UTALKEY_KP_LESS;           }
        else if(__current_keys_state[SDL_SCANCODE_KP_MEMADD]          == 1){ key = UTALKEY_KP_MEMADD;         }
        else if(__current_keys_state[SDL_SCANCODE_KP_MEMCLEAR]        == 1){ key = UTALKEY_KP_MEMCLEAR;       }
        else if(__current_keys_state[SDL_SCANCODE_KP_MEMDIVIDE]       == 1){ key = UTALKEY_KP_MEMDIVIDE;      }
        else if(__current_keys_state[SDL_SCANCODE_KP_MEMMULTIPLY]     == 1){ key = UTALKEY_KP_MEMMULTIPLY;    }
        else if(__current_keys_state[SDL_SCANCODE_KP_MEMRECALL]       == 1){ key = UTALKEY_KP_MEMRECALL;      }
        else if(__current_keys_state[SDL_SCANCODE_KP_MEMSTORE]        == 1){ key = UTALKEY_KP_MEMSTORE;       }
        else if(__current_keys_state[SDL_SCANCODE_KP_MEMSUBTRACT]     == 1){ key = UTALKEY_KP_MEMSUBTRACT;    }
        else if(__current_keys_state[SDL_SCANCODE_KP_MINUS]           == 1){ key = UTALKEY_KP_MINUS;          }
        else if(__current_keys_state[SDL_SCANCODE_KP_MULTIPLY]        == 1){ key = UTALKEY_KP_MULTIPLY;       }
        else if(__current_keys_state[SDL_SCANCODE_KP_OCTAL]           == 1){ key = UTALKEY_KP_OCTAL;          }
        else if(__current_keys_state[SDL_SCANCODE_KP_PERCENT]         == 1){ key = UTALKEY_KP_PERCENT;        }
        else if(__current_keys_state[SDL_SCANCODE_KP_PERIOD]          == 1){ key = UTALKEY_KP_PERIOD;         }
        else if(__current_keys_state[SDL_SCANCODE_KP_PLUS]            == 1){ key = UTALKEY_KP_PLUS;           }
        else if(__current_keys_state[SDL_SCANCODE_KP_PLUSMINUS]       == 1){ key = UTALKEY_KP_PLUSMINUS;      }
        else if(__current_keys_state[SDL_SCANCODE_KP_POWER]           == 1){ key = UTALKEY_KP_POWER;          }
        else if(__current_keys_state[SDL_SCANCODE_KP_RIGHTBRACE]      == 1){ key = UTALKEY_KP_RIGHTBRACE;     }
        else if(__current_keys_state[SDL_SCANCODE_KP_RIGHTPAREN]      == 1){ key = UTALKEY_KP_RIGHTPAREN;     }
        else if(__current_keys_state[SDL_SCANCODE_KP_SPACE]           == 1){ key = UTALKEY_KP_SPACE;          }
        else if(__current_keys_state[SDL_SCANCODE_KP_TAB]             == 1){ key = UTALKEY_KP_TAB;            }
        else if(__current_keys_state[SDL_SCANCODE_KP_VERTICALBAR]     == 1){ key = UTALKEY_KP_VERTICALBAR;    }
        else if(__current_keys_state[SDL_SCANCODE_KP_XOR]             == 1){ key = UTALKEY_KP_XOR;            }
        else if(__current_keys_state[SDL_SCANCODE_L]                  == 1){ key = UTALKEY_L;                 }
        else if(__current_keys_state[SDL_SCANCODE_LALT]               == 1){ key = UTALKEY_LALT;              }
        else if(__current_keys_state[SDL_SCANCODE_LCTRL]              == 1){ key = UTALKEY_LCTRL;             }
        else if(__current_keys_state[SDL_SCANCODE_LEFT]               == 1){ key = UTALKEY_LEFT;              }
        else if(__current_keys_state[SDL_SCANCODE_LEFTBRACKET]        == 1){ key = UTALKEY_LEFTBRACKET;       }
        else if(__current_keys_state[SDL_SCANCODE_LGUI]               == 1){ key = UTALKEY_LGUI;              }
        else if(__current_keys_state[SDL_SCANCODE_LSHIFT]             == 1){ key = UTALKEY_LSHIFT;            }
        else if(__current_keys_state[SDL_SCANCODE_M]                  == 1){ key = UTALKEY_M;                 }
        else if(__current_keys_state[SDL_SCANCODE_MAIL]               == 1){ key = UTALKEY_MAIL;              }
        else if(__current_keys_state[SDL_SCANCODE_MEDIASELECT]        == 1){ key = UTALKEY_MEDIASELECT;       }
        else if(__current_keys_state[SDL_SCANCODE_MENU]               == 1){ key = UTALKEY_MENU;              }
        else if(__current_keys_state[SDL_SCANCODE_MINUS]              == 1){ key = UTALKEY_MINUS;             }
        else if(__current_keys_state[SDL_SCANCODE_MODE]               == 1){ key = UTALKEY_MODE;              }
        else if(__current_keys_state[SDL_SCANCODE_MUTE]               == 1){ key = UTALKEY_MUTE;              }
        else if(__current_keys_state[SDL_SCANCODE_N]                  == 1){ key = UTALKEY_N;                 }
        else if(__current_keys_state[SDL_SCANCODE_NUMLOCKCLEAR]       == 1){ key = UTALKEY_NUMLOCKCLEAR;      }
        else if(__current_keys_state[SDL_SCANCODE_O]                  == 1){ key = UTALKEY_O;                 }
        else if(__current_keys_state[SDL_SCANCODE_OPER]               == 1){ key = UTALKEY_OPER;              }
        else if(__current_keys_state[SDL_SCANCODE_OUT]                == 1){ key = UTALKEY_OUT;               }
        else if(__current_keys_state[SDL_SCANCODE_P]                  == 1){ key = UTALKEY_P;                 }
        else if(__current_keys_state[SDL_SCANCODE_PAGEDOWN]           == 1){ key = UTALKEY_PAGEDOWN;          }
        else if(__current_keys_state[SDL_SCANCODE_PAGEUP]             == 1){ key = UTALKEY_PAGEUP;            }
        else if(__current_keys_state[SDL_SCANCODE_PASTE]              == 1){ key = UTALKEY_PASTE;             }
        else if(__current_keys_state[SDL_SCANCODE_PAUSE]              == 1){ key = UTALKEY_PAUSE;             }
        else if(__current_keys_state[SDL_SCANCODE_PERIOD]             == 1){ key = UTALKEY_PERIOD;            }
        else if(__current_keys_state[SDL_SCANCODE_POWER]              == 1){ key = UTALKEY_POWER;             }
        else if(__current_keys_state[SDL_SCANCODE_PRINTSCREEN]        == 1){ key = UTALKEY_PRINTSCREEN;       }
        else if(__current_keys_state[SDL_SCANCODE_PRIOR]              == 1){ key = UTALKEY_PRIOR;             }
        else if(__current_keys_state[SDL_SCANCODE_Q]                  == 1){ key = UTALKEY_Q;                 }
        else if(__current_keys_state[SDL_SCANCODE_R]                  == 1){ key = UTALKEY_R;                 }
        else if(__current_keys_state[SDL_SCANCODE_RALT]               == 1){ key = UTALKEY_RALT;              }
        else if(__current_keys_state[SDL_SCANCODE_RCTRL]              == 1){ key = UTALKEY_RCTRL;             }
        else if(__current_keys_state[SDL_SCANCODE_RETURN]             == 1){ key = UTALKEY_RETURN;            }
        else if(__current_keys_state[SDL_SCANCODE_RETURN2]            == 1){ key = UTALKEY_RETURN2;           }
        else if(__current_keys_state[SDL_SCANCODE_RGUI]               == 1){ key = UTALKEY_RGUI;              }
        else if(__current_keys_state[SDL_SCANCODE_RIGHT]              == 1){ key = UTALKEY_RIGHT;             }
        else if(__current_keys_state[SDL_SCANCODE_RIGHTBRACKET]       == 1){ key = UTALKEY_RIGHTBRACKET;      }
        else if(__current_keys_state[SDL_SCANCODE_RSHIFT]             == 1){ key = UTALKEY_RSHIFT;            }
        else if(__current_keys_state[SDL_SCANCODE_S]                  == 1){ key = UTALKEY_S;                 }
        else if(__current_keys_state[SDL_SCANCODE_SCROLLLOCK]         == 1){ key = UTALKEY_SCROLLLOCK;        }
        else if(__current_keys_state[SDL_SCANCODE_SELECT]             == 1){ key = UTALKEY_SELECT;            }
        else if(__current_keys_state[SDL_SCANCODE_SEMICOLON]          == 1){ key = UTALKEY_SEMICOLON;         }
        else if(__current_keys_state[SDL_SCANCODE_SEPARATOR]          == 1){ key = UTALKEY_SEPARATOR;         }
        else if(__current_keys_state[SDL_SCANCODE_SLASH]              == 1){ key = UTALKEY_SLASH;             }
        else if(__current_keys_state[SDL_SCANCODE_SLEEP]              == 1){ key = UTALKEY_SLEEP;             }
        else if(__current_keys_state[SDL_SCANCODE_SPACE]              == 1){ key = UTALKEY_SPACE;             }
        else if(__current_keys_state[SDL_SCANCODE_STOP]               == 1){ key = UTALKEY_STOP;              }
        else if(__current_keys_state[SDL_SCANCODE_SYSREQ]             == 1){ key = UTALKEY_SYSREQ;            }
        else if(__current_keys_state[SDL_SCANCODE_T]                  == 1){ key = UTALKEY_T;                 }
        else if(__current_keys_state[SDL_SCANCODE_TAB]                == 1){ key = UTALKEY_TAB;               }
        else if(__current_keys_state[SDL_SCANCODE_THOUSANDSSEPARATOR] == 1){ key = UTALKEY_THOUSANDSSEPARATOR;}
        else if(__current_keys_state[SDL_SCANCODE_U]                  == 1){ key = UTALKEY_U;                 }
        else if(__current_keys_state[SDL_SCANCODE_UNDO]               == 1){ key = UTALKEY_UNDO;              }
        else if(__current_keys_state[SDL_SCANCODE_UNKNOWN]            == 1){ key = UTALKEY_UNKNOWN;           }
        else if(__current_keys_state[SDL_SCANCODE_UP]                 == 1){ key = UTALKEY_UP;                }
        else if(__current_keys_state[SDL_SCANCODE_V]                  == 1){ key = UTALKEY_V;                 }
        else if(__current_keys_state[SDL_SCANCODE_VOLUMEDOWN]         == 1){ key = UTALKEY_VOLUMEDOWN;        }
        else if(__current_keys_state[SDL_SCANCODE_VOLUMEUP]           == 1){ key = UTALKEY_VOLUMEUP;          }
        else if(__current_keys_state[SDL_SCANCODE_W]                  == 1){ key = UTALKEY_W;                 }
        else if(__current_keys_state[SDL_SCANCODE_WWW]                == 1){ key = UTALKEY_WWW;               }
        else if(__current_keys_state[SDL_SCANCODE_X]                  == 1){ key = UTALKEY_X;                 }
        else if(__current_keys_state[SDL_SCANCODE_Y]                  == 1){ key = UTALKEY_Y;                 }
        else if(__current_keys_state[SDL_SCANCODE_Z]                  == 1){ key = UTALKEY_Z;                 }
    }
    __mutex_unlock();
    
    return key;
}

UtalCanvasWindowMouseInfo ucw_get_mouse_state()
{
    UtalCanvasWindowMouseInfo info;
    __mutex_lock();
    info.button = __current_mouse_state.button;
    info.x = __current_mouse_state.x;
    info.y = __current_mouse_state.y;
    __mutex_unlock();
    
    if(info.button == 0)
    {
        info.button = -1;
    }
    return info;
}

void __mutex_init()
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__MINGW32__) || defined(__MINGW64__) && !defined(__CYGWIN__)
        WaitForSingleObject(window_mutex, INFINITE);
    #else
        pthread_mutex_init(&__linux_mutex, NULL);
    #endif
}

void __mutex_lock()
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__MINGW32__) || defined(__MINGW64__) && !defined(__CYGWIN__)
    #else
        pthread_mutex_lock(&__linux_mutex);
    #endif
}

void __mutex_unlock()
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__MINGW32__) || defined(__MINGW64__) && !defined(__CYGWIN__)
        ReleaseMutex(window_mutex);
    #else
        pthread_mutex_unlock(&__linux_mutex);
    #endif
}

JoystickData* __create_joystick_data(SDL_Joystick *joystick)
{
    int i;
    JoystickData* jdata = (JoystickData*)malloc(sizeof(JoystickData));
    jdata->joystick = joystick;
    
    //inicializo los botones
    int n_buttons = SDL_JoystickNumButtons(joystick);
    jdata->n_buttons = n_buttons;
    jdata->buttons = (bool*)malloc(n_buttons*sizeof(bool));
    for (i = 0; i < n_buttons; i++) 
    {
        jdata->buttons[i] = false;
    }
   
    //inicializo los axis
    int n_axis = SDL_JoystickNumAxes(joystick);
    jdata->n_axis = n_axis;
    jdata->axis = (int*)malloc(n_axis*sizeof(int));
    for (i = 0; i < n_axis; i++) 
    {
        jdata->axis[i] = 0;
    }
    
    return jdata;
}

int ucw_get_joystick_button_state( int joystick_id, int button )
{
    int value = 0;
    __mutex_lock();
    JoystickData* jdata = get_joystick_data(joystick_id);
    if(jdata != NULL)
    {
        if( button <= jdata->n_buttons )
        {
            value = jdata->buttons[button] ? 1 : 0;
        }
    }
    __mutex_unlock();
    return value;
}
    
int ucw_get_joystick_axis_value( int joystick_id, int axis )
{
    int value = 0;
    __mutex_lock();
    JoystickData* jdata = get_joystick_data(joystick_id);
    if(jdata != NULL)
    {
        if( axis <= jdata->n_axis )
        {
            value = jdata->axis[axis];
        }
    }
    __mutex_unlock();
    return value;
}

int ucw_get_joystick_state( int joystick_id )
{
    __mutex_lock();
    JoystickData* jdata = get_joystick_data(joystick_id);
    __mutex_unlock();
    
    if(jdata != NULL)
    {
        return 1;
    }
    return 0;
}

