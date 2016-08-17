#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>

#include "utalcanvas_window.h"
#include "utalcanvas_structures.h"
#include "utalcanvas_list.h"
#include "utalcanvas_colors.h"


SDL_Window* __utalCanvasWindow = NULL;
SDL_Surface* __utalCanvasScreenSurface = NULL;
SDL_Renderer* __utalCanvasRenderer = NULL;

pthread_t __utalCanvasWindowThread = 0;
pthread_mutex_t __utalCanvasWindowMutex;
bool __utalCanvasWindowSignalToClose = false;
bool __utalCanvasWindowClosed = false;

UtalCanvasWindowViewport viewport = {0, 0, 640, 480};
UtalCanvasWindowDimension dimension = {640, 480};
char __title[MAX_TEXT_LENGTH] = "UtalCanvas";

UtalCanvasColor __UtalCanvasWindowBackground = {255, 255 , 255};

const Uint8* __currentKeyStates = NULL;
UtalCanvasWindowMouseInfo __mouseInfo;

bool UtalCanvasWindowInitialize()
{
    
    pthread_mutex_init(&__utalCanvasWindowMutex, NULL);
    
    pthread_mutex_lock(&__utalCanvasWindowMutex);
    bool success = true;
    
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        __utalCanvasWindow = SDL_CreateWindow( "UtalCanvas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dimension.width, dimension.height, SDL_WINDOW_SHOWN );
        if( __utalCanvasWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            __utalCanvasRenderer = SDL_CreateRenderer( __utalCanvasWindow, -1, SDL_RENDERER_ACCELERATED );
            if( __utalCanvasRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( __utalCanvasRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                        success = false;
                }
                
                //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                        success = false;
                }
            }
        }
    }    
    __utalCanvasWindowClosed = false;
    pthread_mutex_unlock(&__utalCanvasWindowMutex);
    return success;
}

void UtalCanvasWindowClose()
{
    pthread_mutex_lock(&__utalCanvasWindowMutex);
    __utalCanvasWindowSignalToClose = true;
    pthread_mutex_unlock(&__utalCanvasWindowMutex);
    
    bool quit = false;
    while(!quit)
    {
        pthread_mutex_lock(&__utalCanvasWindowMutex);
        if( __utalCanvasWindowClosed == true )
        {
            quit = true;
        }
        pthread_mutex_unlock(&__utalCanvasWindowMutex);
    }
    
    UtalCanvasNode* node = UtalCanvasListGetFirst();
    if( node != NULL )
    {
        do
        {
            if(node->type == UTALCANVAS_ELEMENT_IMAGE)
            {
                UtalCanvasImage* image = (UtalCanvasImage*)node->data;
                SDL_DestroyTexture(image->texture);
                image->texture = NULL;
            }
            node = node->next;
        }
        while( node != UtalCanvasListGetFirst() );
    }

    SDL_DestroyWindow( __utalCanvasWindow );
    __utalCanvasWindow = NULL;

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void UtalCanvasWindowSetViewport(int xMin, int yMin, int xUp, int yUp)
{
    pthread_mutex_lock(&__utalCanvasWindowMutex);
    viewport.xMin = xMin < xUp ? xMin : xUp;
    viewport.yMin = yMin < yUp ? yMin : yUp;
    viewport.xMax = xMin > xUp ? xMin : xUp;
    viewport.yMax = yMin > yUp ? yMin : yUp;
    pthread_mutex_unlock(&__utalCanvasWindowMutex);
}

void UtalCanvasWindowSetTitle( char title[MAX_TEXT_LENGTH] )
{
    pthread_mutex_lock(&__utalCanvasWindowMutex);
    SDL_SetWindowTitle(__utalCanvasWindow, title);
    pthread_mutex_unlock(&__utalCanvasWindowMutex);
}

void UtalCanvasWindowSetBackground(char background[COLOR_NAME_LENGTH])
{
    pthread_mutex_lock(&__utalCanvasWindowMutex);
    __UtalCanvasWindowBackground = UtalCanvasColorGetByName(background);
    pthread_mutex_unlock(&__utalCanvasWindowMutex);
}

int UtalCanvasWindowAddElement(UtalCanvasElementType type, void* data)
{
    int index = -1;
    pthread_mutex_lock(&__utalCanvasWindowMutex);
    index = UtalCanvasListAddElement(type, data);
    pthread_mutex_unlock(&__utalCanvasWindowMutex);
    return index;
}

void UtalCanvasWindowRemoveElementByIndex(int index)
{
    pthread_mutex_lock(&__utalCanvasWindowMutex);
    UtalCanvasListRemoveElementByIndex(index);
    pthread_mutex_unlock(&__utalCanvasWindowMutex);
}

void UtalCanvasWindowRemoveElementByTag(char tag[TAG_NAME_LENGTH])
{
    pthread_mutex_lock(&__utalCanvasWindowMutex);
    UtalCanvasListRemoveElementByTag(tag);
    pthread_mutex_unlock(&__utalCanvasWindowMutex);
}

void UtalCanvasWindowRemoveAllElement()
{
    pthread_mutex_lock(&__utalCanvasWindowMutex);
    UtalCanvasListRemoveAllElement();
    pthread_mutex_unlock(&__utalCanvasWindowMutex);
}

void UtalCanvasWindowMoveElementByIndex(int index, int dx, int dy)
{
    pthread_mutex_lock(&__utalCanvasWindowMutex);
    UtalCanvasListMoveElementByIndex(index, dx, dy);
    pthread_mutex_unlock(&__utalCanvasWindowMutex);
}

void UtalCanvasWindowMoveElementByTag(char tag[TAG_NAME_LENGTH], int dx, int dy)
{
    pthread_mutex_lock(&__utalCanvasWindowMutex);
    UtalCanvasListMoveElementByTag(tag, dx, dy);
    pthread_mutex_unlock(&__utalCanvasWindowMutex);
}

void UtalCanvasWindowDrawPoint(void* data)
{
    UtalCanvasPoint* point = (UtalCanvasPoint*)data;
    SDL_SetRenderDrawColor( __utalCanvasRenderer, point->color.red, point->color.green, point->color.blue, 0xFF );
    
    int x = convertXAxis(point->x);
    int y = dimension.height - convertYAxis(point->y);
    SDL_RenderDrawPoint( __utalCanvasRenderer, x, y );
}

void UtalCanvasWindowDrawLine(void* data)
{
    UtalCanvasLine* line = (UtalCanvasLine*)data;
    int x1 = convertXAxis(line->x1);
    int y1 = dimension.height - convertYAxis(line->y1);
    int x2 = convertXAxis(line->x2);
    int y2 = dimension.height - convertYAxis(line->y2);
    
    SDL_SetRenderDrawColor( __utalCanvasRenderer, line->color.red, line->color.green, line->color.blue, 0xFF );
    SDL_RenderDrawLine( __utalCanvasRenderer, x1, y1, x2, y2 );
}

void UtalCanvasWindowDrawRectangle(char* data)
{
    UtalCanvasRectangle* rectangle = (UtalCanvasRectangle*)data;
    SDL_SetRenderDrawColor( __utalCanvasRenderer, rectangle->color.red, rectangle->color.green, rectangle->color.blue, 0xFF );
    UtalCanvasPlainRectangle plainRectangle;
    UtalCanvasUtilsFixRectangle(&plainRectangle, rectangle->x1, rectangle->y1, rectangle->x2, rectangle->y2); 
    int x = convertXAxis(plainRectangle.x);
    int y = dimension.height - convertYAxis(plainRectangle.y);
    int width = convertXAxis(plainRectangle.width);
    int height = -convertYAxis(plainRectangle.height);
    
    SDL_Rect outlineRect = { x, y, width, height };
    SDL_RenderDrawRect( __utalCanvasRenderer, &outlineRect );
}

void UtalCanvasWindowDrawFilledRectangle(char* data)
{
    UtalCanvasFilledRectangle* rectangle = (UtalCanvasFilledRectangle*)data;
    UtalCanvasPlainRectangle plainRectangle;
    UtalCanvasUtilsFixRectangle(plainRectangle, rectangle->x1, rectangle->y1, rectangle->x2, rectangle->y2);
    int x = convertXAxis(plainRectangle.x);
    int y = dimension.height - convertYAxis(plainRectangle.y);
    int width = convertXAxis(plainRectangle.width);
    int height = -convertYAxis(plainRectangle.height);
    SDL_Rect rect = { x, y, width, height };

    SDL_SetRenderDrawColor( __utalCanvasRenderer, rectangle->fillColor.red, rectangle->fillColor.green, rectangle->fillColor.blue, 0xFF );
    SDL_RenderFillRect( __utalCanvasRenderer, &rect );
    SDL_SetRenderDrawColor( __utalCanvasRenderer, rectangle->outerColor.red, rectangle->outerColor.green, rectangle->outerColor.blue, 0xFF );
    SDL_RenderDrawRect( __utalCanvasRenderer, &rect );
}

void UtalCanvasWindowDrawCircle(char* data)
{
    UtalCanvasCircle* circle = (UtalCanvasCircle*)data;
    __UtalCanvasWindowDrawEllipse(circle);
}

void UtalCanvasWindowDrawFilledCircle(void* data)
{
    UtalCanvasFilledCircle* filledCircle = (UtalCanvasFilledCircle*)data;
    __UtalCanvasWindowFillEllipse(filledCircle);
    
    UtalCanvasCircle* circle = (UtalCanvasCircle*)malloc(sizeof(UtalCanvasCircle));
    circle->x = filledCircle->x;
    circle->y = filledCircle->y;
    circle->color = filledCircle->outerColor;
    circle->radio = filledCircle->radio;
    __UtalCanvasWindowDrawEllipse(circle);
    free(circle);
    
    
    
}

void UtalCanvasWindowDrawImage(void* data)
{
    UtalCanvasImage* image = (UtalCanvasImage*)data;
    int width = convertXAxis(image->width);
    int height = convertYAxis(image->height);
    int x = convertXAxis(image->x);
    int y = dimension.height - convertYAxis(image->y) - height;
    
    
    if( image->size == NULL || image->texture == NULL )
    {
        SDL_Surface* surface = IMG_Load( image->filename );
        if(surface == NULL)
        {
            return;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface( __utalCanvasRenderer, surface );
        if(texture == NULL)
        {
            return;
        }

        SDL_Rect* size = (SDL_Rect*)malloc(sizeof(SDL_Rect));
        size->x = 0;
        size->y = 0;
        size->w = surface->w;
        size->h = surface->h;
        
        image->texture = texture;
        image->size = size;
        
        SDL_FreeSurface(surface);
        surface = NULL;
    }
    
    SDL_Rect location = {x, y, width, height};
    SDL_RenderCopy( __utalCanvasRenderer, image->texture, image->size, &location );
}

void UtalCanvasWindowDrawText(void* data)
{
    UtalCanvasText* text = (UtalCanvasText*)data;
    
    if( text->font == NULL )
    {
        text->font = TTF_OpenFont( text->fontFile, text->size );
        if( text->font == NULL)
        {
            return;
        }
    }
    
    SDL_Color textColor = { text->color.red, text->color.green, text->color.blue };
    if( text->textSurface == NULL )
    {
        text->textSurface = TTF_RenderText_Solid( text->font, text->text, textColor );
        if( text->textSurface == NULL )
        {
            return;
        }
    }
    
    if( text->texture == NULL )
    {
        text->texture = SDL_CreateTextureFromSurface( __utalCanvasRenderer, text->textSurface );
        if( text->texture == NULL )
        {
            return;
        }
    }
    
    int mWidth = text->textSurface->w;
    int mHeight = text->textSurface->h;
    int x = convertXAxis(text->x);
    int y = dimension.height - mHeight - convertYAxis(text->y);;
    
    SDL_Rect clip = { 0, 0, mWidth, mWidth };
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopyEx( __utalCanvasRenderer, text->texture, &clip, &renderQuad, 0, NULL, SDL_FLIP_NONE  );
}


void UtalCanvasWindowLoop()
{
    SDL_Event e;
    int x, y;
    bool quit = false;
    
    pthread_mutex_lock(&__utalCanvasWindowMutex);
    __utalCanvasWindowClosed = false;
    pthread_mutex_unlock(&__utalCanvasWindowMutex);
    
    while( !quit )
    {
        pthread_mutex_lock(&__utalCanvasWindowMutex);
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_MOUSEMOTION )
            {
                SDL_GetMouseState( &x, &y );
                __mouseInfo.x = ((1.0*x)/dimension.width)*(viewport.xMax - viewport.xMin) + viewport.xMin;
                __mouseInfo.y = dimension.height - ((1.0*y)/dimension.height)*(viewport.yMax - viewport.yMin) + viewport.yMin;
            }
            else if( e.type == SDL_MOUSEBUTTONDOWN )
            {
                __mouseInfo.button = -1;
                if( e.button.button == SDL_BUTTON_LEFT)
                {
                    __mouseInfo.button = 1;
                }
                else if( e.button.button == SDL_BUTTON_MIDDLE )
                {
                    __mouseInfo.button = 2;
                }
                else if( e.button.button == SDL_BUTTON_RIGHT )
                {
                    __mouseInfo.button = 3;
                }
            }
            else if( e.type == SDL_MOUSEBUTTONUP )
            {
                __mouseInfo.button = -1;
            }
            else if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }
        
        __currentKeyStates = SDL_GetKeyboardState(NULL);

        SDL_SetRenderDrawColor( __utalCanvasRenderer, __UtalCanvasWindowBackground.red, __UtalCanvasWindowBackground.green, __UtalCanvasWindowBackground.blue, 0xFF );
        SDL_RenderClear( __utalCanvasRenderer );
        
        UtalCanvasNode* node = UtalCanvasListGetFirst();
        if( node != NULL )
        {
            do
            {
                switch(node->type)
                {
                    case UTALCANVAS_ELEMENT_POINT            : UtalCanvasWindowDrawPoint(node->data);           break;
                    case UTALCANVAS_ELEMENT_LINE             : UtalCanvasWindowDrawLine(node->data);            break;
                    case UTALCANVAS_ELEMENT_RECTANGLE        : UtalCanvasWindowDrawRectangle(node->data);       break;
                    case UTALCANVAS_ELEMENT_FILLED_RECTANGLE : UtalCanvasWindowDrawFilledRectangle(node->data); break;
                    case UTALCANVAS_ELEMENT_CIRCLE           : UtalCanvasWindowDrawCircle(node->data);          break;
                    case UTALCANVAS_ELEMENT_FILLED_CIRCLE    : UtalCanvasWindowDrawFilledCircle(node->data);    break;
                    case UTALCANVAS_ELEMENT_IMAGE            : UtalCanvasWindowDrawImage(node->data);           break;
                    case UTALCANVAS_ELEMENT_TEXT             : UtalCanvasWindowDrawText(node->data);            break;
                }
                node = node->next;
            }
            while( node != UtalCanvasListGetFirst() );
        }
        
        if( __utalCanvasWindowSignalToClose == true )
        {
            quit = true;
        }
        
        SDL_RenderPresent( __utalCanvasRenderer );
        SDL_UpdateWindowSurface( __utalCanvasWindow );
        
        
        
        pthread_mutex_unlock(&__utalCanvasWindowMutex);
        usleep(50);
    }
    
    pthread_mutex_lock(&__utalCanvasWindowMutex);
    __utalCanvasWindowClosed = true;
    pthread_mutex_unlock(&__utalCanvasWindowMutex);
}

bool UtalCanvasWindowIsClosed()
{
    pthread_mutex_lock(&__utalCanvasWindowMutex);
    bool state = __utalCanvasWindowClosed;
    pthread_mutex_unlock(&__utalCanvasWindowMutex);
    return state;
}

void* loop(void* args)
{
    if( !UtalCanvasWindowInitialize() )
    {
        return;
    }
    UtalCanvasWindowLoop();
}

void UtalCanvasWindowStart()
{
    if(__utalCanvasWindowThread != 0)
        return;
    
    pthread_create(&__utalCanvasWindowThread, NULL, loop, NULL);
}

void UtalCanvasWindowSetSize(int width, int height)
{
    pthread_mutex_lock(&__utalCanvasWindowMutex);
    
    dimension.width = width;
    dimension.height = height;
    
    if( __utalCanvasWindow != NULL )
    {
        SDL_SetWindowSize(__utalCanvasWindow, width, height);
    }
    
    pthread_mutex_unlock(&__utalCanvasWindowMutex);
}

int convertXAxis( int worldValue )
{
    int width = dimension.width;
    int worldWidth = viewport.xMax - viewport.xMin;
    
    int direction = 1;
    if( worldValue < viewport.xMin )
    {
        direction = -1;
    }
    return (int)(((direction*worldValue)/(1.0*worldWidth))*width);   
}

int convertYAxis( int worldValue )
{
    int height = dimension.height;
    int worldHeight = viewport.yMax - viewport.yMin;
    
    int direction = 1;
    if( worldValue < viewport.yMin )
    {
        direction = 1;
    }
    return (int)(((direction*worldValue)/(1.0*worldHeight))*height);
}

void __UtalCanvasWindowDrawEllipse(UtalCanvasCircle* circle)
{
    int x = convertXAxis(circle->x);
    int y = dimension.height - convertYAxis(circle->y);
    int rx = convertXAxis(circle->radio);
    int ry = convertYAxis(circle->radio);
    
    int ix, iy;
    int h, i, j, k;
    int oh, oi, oj, ok;
    int xmh, xph, ypk, ymk;
    int xmi, xpi, ymj, ypj;
    int xmj, xpj, ymi, ypi;
    int xmk, xpk, ymh, yph;

    SDL_SetRenderDrawColor(__utalCanvasRenderer, circle->color.red, circle->color.green, circle->color.blue, 0xFF);
    
    //Caso en el que que el radio en el eje X sea cero
    if (rx == 0) 
    {
        SDL_RenderDrawLine(__utalCanvasRenderer, x, y - ry, x, y + ry);
    }
    
    //Caso en el que el radio en el eje Y sea cero
    if (ry == 0) 
    {
        SDL_RenderDrawLine(__utalCanvasRenderer, x - rx, y, x + rx, y);
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
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xmh, ypk);
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xph, ypk);
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xmh, ymk);
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xph, ymk);
                } 
                else 
                {
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xmh, y);
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xph, y);
                }
                
                ok = k;
                xpi = x + i;
                xmi = x - i;
                if (j > 0) 
                {
                    ypj = y + j;
                    ymj = y - j;
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xmi, ypj);
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xpi, ypj);
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xmi, ymj);
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xpi, ymj);
                } 
                else 
                {
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xmi, y);
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xpi, y);
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
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xmj, ypi); 
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xpj, ypi); 
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xmj, ymi); 
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xpj, ymi);
                } 
                else 
                {
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xmj, y);
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xpj, y);
                }
                oi = i;
                xmk = x - k;
                xpk = x + k;
                if (h > 0) 
                {
                    yph = y + h;
                    ymh = y - h;
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xmk, yph);
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xpk, yph);
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xmk, ymh);
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xpk, ymh);
                } 
                else 
                {
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xmk, y);
                    SDL_RenderDrawPoint(__utalCanvasRenderer, xpk, y);
                }
                oh = h;
            }
            
            ix = ix + iy / ry;
            iy = iy - ix / ry;
        } 
        while (i > h);
    }
}

void __UtalCanvasWindowFillEllipse(UtalCanvasFilledCircle* circle)
{
    int x = convertXAxis(circle->x);
    int y = dimension.height - convertYAxis(circle->y);
    int rx = convertXAxis(circle->radio);
    int ry = convertYAxis(circle->radio);
    
    int ix, iy;
    int h, i, j, k;
    int oh, oi, oj, ok;
    int xmh, xph;
    int xmi, xpi;
    int xmj, xpj;
    int xmk, xpk;

    SDL_SetRenderDrawColor(__utalCanvasRenderer, circle->fillColor.red, circle->fillColor.green, circle->fillColor.blue, 0xFF);
    
    //Caso en el que el radio en el eje X sea cero
    if (rx == 0) 
    {
        SDL_RenderDrawLine(__utalCanvasRenderer, x, y - ry, x, y + ry);
    }
    
    //Caso en el que el radio en el eje Y sea cero
    if (ry == 0) 
    {
        SDL_RenderDrawLine(__utalCanvasRenderer, x - rx, y, x + rx, y);
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
                    SDL_RenderDrawLine(__utalCanvasRenderer, xmh, y + k, xph, y + k);
                    SDL_RenderDrawLine(__utalCanvasRenderer, xmh, y - k, xph, y - k);
                } 
                else 
                {
                    SDL_RenderDrawLine(__utalCanvasRenderer, xmh, y, xph, y);
                }
                ok = k;
            }
            if ((oj != j) && (ok != j) && (k != j)) 
            {
                xmi = x - i;
                xpi = x + i;
                if (j > 0) 
                {
                    SDL_RenderDrawLine(__utalCanvasRenderer, xmi, y + j, xpi, y + j);
                    SDL_RenderDrawLine(__utalCanvasRenderer, xmi, y - j, xpi, y - j);
                } 
                else 
                {
                    SDL_RenderDrawLine(__utalCanvasRenderer, xmi, y, xpi, y);
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
                    SDL_RenderDrawLine(__utalCanvasRenderer, xmj, y + i, xpj, y + i);
                    SDL_RenderDrawLine(__utalCanvasRenderer, xmj, y - i, xpj, y - i);
                } 
                else 
                {
                    SDL_RenderDrawLine(__utalCanvasRenderer, xmj, y, xpj, y);
                }
                oi = i;
            }
            if ((oh != h) && (oi != h) && (i != h)) 
            {
                xmk = x - k;
                xpk = x + k;
                if (h > 0) 
                {
                    SDL_RenderDrawLine(__utalCanvasRenderer, xmk, y + h, xpk, y + h);
                    SDL_RenderDrawLine(__utalCanvasRenderer, xmk, y - h, xpk, y - h);
                } 
                else 
                {
                    SDL_RenderDrawLine(__utalCanvasRenderer, xmk, y, xpk, y);
                }
                oh = h;
            }

            ix = ix + iy / ry;
            iy = iy - ix / ry;
        } 
        while (i > h);
    }
}

UtalCanvasKey UtalCanvasWindowGetPressedKey()
{
    int key = UTALKEY_NONE;
    
    pthread_mutex_lock(&__utalCanvasWindowMutex);
    if( __currentKeyStates != NULL )
    {
        if(__currentKeyStates[SDL_SCANCODE_0]                       == 1){ key = UTALKEY_0;                 }
        else if(__currentKeyStates[SDL_SCANCODE_1]                  == 1){ key = UTALKEY_1;                 }
        else if(__currentKeyStates[SDL_SCANCODE_2]                  == 1){ key = UTALKEY_2;                 }
        else if(__currentKeyStates[SDL_SCANCODE_3]                  == 1){ key = UTALKEY_3;                 }
        else if(__currentKeyStates[SDL_SCANCODE_4]                  == 1){ key = UTALKEY_4;                 }
        else if(__currentKeyStates[SDL_SCANCODE_5]                  == 1){ key = UTALKEY_5;                 }
        else if(__currentKeyStates[SDL_SCANCODE_6]                  == 1){ key = UTALKEY_6;                 }
        else if(__currentKeyStates[SDL_SCANCODE_7]                  == 1){ key = UTALKEY_7;                 }
        else if(__currentKeyStates[SDL_SCANCODE_8]                  == 1){ key = UTALKEY_8;                 }
        else if(__currentKeyStates[SDL_SCANCODE_9]                  == 1){ key = UTALKEY_9;                 }
        else if(__currentKeyStates[SDL_SCANCODE_A]                  == 1){ key = UTALKEY_A;                 }
        else if(__currentKeyStates[SDL_SCANCODE_AC_BACK]            == 1){ key = UTALKEY_AC_BACK;           }
        else if(__currentKeyStates[SDL_SCANCODE_AC_BOOKMARKS]       == 1){ key = UTALKEY_AC_BOOKMARKS;      }
        else if(__currentKeyStates[SDL_SCANCODE_AC_FORWARD]         == 1){ key = UTALKEY_AC_FORWARD;        }
        else if(__currentKeyStates[SDL_SCANCODE_AC_HOME]            == 1){ key = UTALKEY_AC_HOME;           }
        else if(__currentKeyStates[SDL_SCANCODE_AC_REFRESH]         == 1){ key = UTALKEY_AC_REFRESH;        }
        else if(__currentKeyStates[SDL_SCANCODE_AC_SEARCH]          == 1){ key = UTALKEY_AC_SEARCH;         }
        else if(__currentKeyStates[SDL_SCANCODE_AC_STOP]            == 1){ key = UTALKEY_AC_STOP;           }
        else if(__currentKeyStates[SDL_SCANCODE_AGAIN]              == 1){ key = UTALKEY_AGAIN;             }
        else if(__currentKeyStates[SDL_SCANCODE_ALTERASE]           == 1){ key = UTALKEY_ALTERASE;          }
        else if(__currentKeyStates[SDL_SCANCODE_APOSTROPHE]         == 1){ key = UTALKEY_APOSTROPHE;        }
        else if(__currentKeyStates[SDL_SCANCODE_APPLICATION]        == 1){ key = UTALKEY_APPLICATION;       }
        else if(__currentKeyStates[SDL_SCANCODE_AUDIOMUTE]          == 1){ key = UTALKEY_AUDIOMUTE;         }
        else if(__currentKeyStates[SDL_SCANCODE_AUDIONEXT]          == 1){ key = UTALKEY_AUDIONEXT;         }
        else if(__currentKeyStates[SDL_SCANCODE_AUDIOPLAY]          == 1){ key = UTALKEY_AUDIOPLAY;         }
        else if(__currentKeyStates[SDL_SCANCODE_AUDIOPREV]          == 1){ key = UTALKEY_AUDIOPREV;         }
        else if(__currentKeyStates[SDL_SCANCODE_AUDIOSTOP]          == 1){ key = UTALKEY_AUDIOSTOP;         }
        else if(__currentKeyStates[SDL_SCANCODE_B]                  == 1){ key = UTALKEY_B;                 }
        else if(__currentKeyStates[SDL_SCANCODE_BACKSLASH]          == 1){ key = UTALKEY_BACKSLASH;         }
        else if(__currentKeyStates[SDL_SCANCODE_BACKSPACE]          == 1){ key = UTALKEY_BACKSPACE;         }
        else if(__currentKeyStates[SDL_SCANCODE_BRIGHTNESSDOWN]     == 1){ key = UTALKEY_BRIGHTNESSDOWN;    }
        else if(__currentKeyStates[SDL_SCANCODE_BRIGHTNESSUP]       == 1){ key = UTALKEY_BRIGHTNESSUP;      }
        else if(__currentKeyStates[SDL_SCANCODE_C]                  == 1){ key = UTALKEY_C;                 }
        else if(__currentKeyStates[SDL_SCANCODE_CALCULATOR]         == 1){ key = UTALKEY_CALCULATOR;        }
        else if(__currentKeyStates[SDL_SCANCODE_CANCEL]             == 1){ key = UTALKEY_CANCEL;            }
        else if(__currentKeyStates[SDL_SCANCODE_CAPSLOCK]           == 1){ key = UTALKEY_CAPSLOCK;          }
        else if(__currentKeyStates[SDL_SCANCODE_CLEAR]              == 1){ key = UTALKEY_CLEAR;             }
        else if(__currentKeyStates[SDL_SCANCODE_CLEARAGAIN]         == 1){ key = UTALKEY_CLEARAGAIN;        }
        else if(__currentKeyStates[SDL_SCANCODE_COMMA]              == 1){ key = UTALKEY_COMMA;             }
        else if(__currentKeyStates[SDL_SCANCODE_COMPUTER]           == 1){ key = UTALKEY_COMPUTER;          }
        else if(__currentKeyStates[SDL_SCANCODE_COPY]               == 1){ key = UTALKEY_COPY;              }
        else if(__currentKeyStates[SDL_SCANCODE_CRSEL]              == 1){ key = UTALKEY_CRSEL;             }
        else if(__currentKeyStates[SDL_SCANCODE_CURRENCYSUBUNIT]    == 1){ key = UTALKEY_CURRENCYSUBUNIT;   }
        else if(__currentKeyStates[SDL_SCANCODE_CURRENCYUNIT]       == 1){ key = UTALKEY_CURRENCYUNIT;      }
        else if(__currentKeyStates[SDL_SCANCODE_CUT]                == 1){ key = UTALKEY_CUT;               }
        else if(__currentKeyStates[SDL_SCANCODE_D]                  == 1){ key = UTALKEY_D;                 }
        else if(__currentKeyStates[SDL_SCANCODE_DECIMALSEPARATOR]   == 1){ key = UTALKEY_DECIMALSEPARATOR;  }
        else if(__currentKeyStates[SDL_SCANCODE_DELETE]             == 1){ key = UTALKEY_DELETE;            }
        else if(__currentKeyStates[SDL_SCANCODE_DISPLAYSWITCH]      == 1){ key = UTALKEY_DISPLAYSWITCH;     }
        else if(__currentKeyStates[SDL_SCANCODE_DOWN]               == 1){ key = UTALKEY_DOWN;              }
        else if(__currentKeyStates[SDL_SCANCODE_E]                  == 1){ key = UTALKEY_E;                 }
        else if(__currentKeyStates[SDL_SCANCODE_EJECT]              == 1){ key = UTALKEY_EJECT;             }
        else if(__currentKeyStates[SDL_SCANCODE_END]                == 1){ key = UTALKEY_END;               }
        else if(__currentKeyStates[SDL_SCANCODE_EQUALS]             == 1){ key = UTALKEY_EQUALS;            }
        else if(__currentKeyStates[SDL_SCANCODE_ESCAPE]             == 1){ key = UTALKEY_ESCAPE;            }
        else if(__currentKeyStates[SDL_SCANCODE_EXECUTE]            == 1){ key = UTALKEY_EXECUTE;           }
        else if(__currentKeyStates[SDL_SCANCODE_EXSEL]              == 1){ key = UTALKEY_EXSEL;             }
        else if(__currentKeyStates[SDL_SCANCODE_F]                  == 1){ key = UTALKEY_F;                 }
        else if(__currentKeyStates[SDL_SCANCODE_F1]                 == 1){ key = UTALKEY_F1;                }
        else if(__currentKeyStates[SDL_SCANCODE_F10]                == 1){ key = UTALKEY_F10;               }
        else if(__currentKeyStates[SDL_SCANCODE_F11]                == 1){ key = UTALKEY_F11;               }
        else if(__currentKeyStates[SDL_SCANCODE_F12]                == 1){ key = UTALKEY_F12;               }
        else if(__currentKeyStates[SDL_SCANCODE_F13]                == 1){ key = UTALKEY_F13;               }
        else if(__currentKeyStates[SDL_SCANCODE_F14]                == 1){ key = UTALKEY_F14;               }
        else if(__currentKeyStates[SDL_SCANCODE_F15]                == 1){ key = UTALKEY_F15;               }
        else if(__currentKeyStates[SDL_SCANCODE_F16]                == 1){ key = UTALKEY_F16;               }
        else if(__currentKeyStates[SDL_SCANCODE_F17]                == 1){ key = UTALKEY_F17;               }
        else if(__currentKeyStates[SDL_SCANCODE_F18]                == 1){ key = UTALKEY_F18;               }
        else if(__currentKeyStates[SDL_SCANCODE_F19]                == 1){ key = UTALKEY_F19;               }
        else if(__currentKeyStates[SDL_SCANCODE_F2]                 == 1){ key = UTALKEY_F2;                }
        else if(__currentKeyStates[SDL_SCANCODE_F20]                == 1){ key = UTALKEY_F20;               }
        else if(__currentKeyStates[SDL_SCANCODE_F21]                == 1){ key = UTALKEY_F21;               }
        else if(__currentKeyStates[SDL_SCANCODE_F22]                == 1){ key = UTALKEY_F22;               }
        else if(__currentKeyStates[SDL_SCANCODE_F23]                == 1){ key = UTALKEY_F23;               }
        else if(__currentKeyStates[SDL_SCANCODE_F24]                == 1){ key = UTALKEY_F24;               }
        else if(__currentKeyStates[SDL_SCANCODE_F3]                 == 1){ key = UTALKEY_F3;                }
        else if(__currentKeyStates[SDL_SCANCODE_F4]                 == 1){ key = UTALKEY_F4;                }
        else if(__currentKeyStates[SDL_SCANCODE_F5]                 == 1){ key = UTALKEY_F5;                }
        else if(__currentKeyStates[SDL_SCANCODE_F6]                 == 1){ key = UTALKEY_F6;                }
        else if(__currentKeyStates[SDL_SCANCODE_F7]                 == 1){ key = UTALKEY_F7;                }
        else if(__currentKeyStates[SDL_SCANCODE_F8]                 == 1){ key = UTALKEY_F8;                }
        else if(__currentKeyStates[SDL_SCANCODE_F9]                 == 1){ key = UTALKEY_F9;                }
        else if(__currentKeyStates[SDL_SCANCODE_FIND]               == 1){ key = UTALKEY_FIND;              }
        else if(__currentKeyStates[SDL_SCANCODE_G]                  == 1){ key = UTALKEY_G;                 }
        else if(__currentKeyStates[SDL_SCANCODE_GRAVE]              == 1){ key = UTALKEY_GRAVE;             }
        else if(__currentKeyStates[SDL_SCANCODE_H]                  == 1){ key = UTALKEY_H;                 }
        else if(__currentKeyStates[SDL_SCANCODE_HELP]               == 1){ key = UTALKEY_HELP;              }
        else if(__currentKeyStates[SDL_SCANCODE_HOME]               == 1){ key = UTALKEY_HOME;              }
        else if(__currentKeyStates[SDL_SCANCODE_I]                  == 1){ key = UTALKEY_I;                 }
        else if(__currentKeyStates[SDL_SCANCODE_INSERT]             == 1){ key = UTALKEY_INSERT;            }
        else if(__currentKeyStates[SDL_SCANCODE_J]                  == 1){ key = UTALKEY_J;                 }
        else if(__currentKeyStates[SDL_SCANCODE_K]                  == 1){ key = UTALKEY_K;                 }
        else if(__currentKeyStates[SDL_SCANCODE_KBDILLUMDOWN]       == 1){ key = UTALKEY_KBDILLUMDOWN;      }
        else if(__currentKeyStates[SDL_SCANCODE_KBDILLUMTOGGLE]     == 1){ key = UTALKEY_KBDILLUMTOGGLE;    }
        else if(__currentKeyStates[SDL_SCANCODE_KBDILLUMUP]         == 1){ key = UTALKEY_KBDILLUMUP;        }
        else if(__currentKeyStates[SDL_SCANCODE_KP_0]               == 1){ key = UTALKEY_KP_0;              }
        else if(__currentKeyStates[SDL_SCANCODE_KP_00]              == 1){ key = UTALKEY_KP_00;             }
        else if(__currentKeyStates[SDL_SCANCODE_KP_000]             == 1){ key = UTALKEY_KP_000;            }
        else if(__currentKeyStates[SDL_SCANCODE_KP_1]               == 1){ key = UTALKEY_KP_1;              }
        else if(__currentKeyStates[SDL_SCANCODE_KP_2]               == 1){ key = UTALKEY_KP_2;              }
        else if(__currentKeyStates[SDL_SCANCODE_KP_3]               == 1){ key = UTALKEY_KP_3;              }
        else if(__currentKeyStates[SDL_SCANCODE_KP_4]               == 1){ key = UTALKEY_KP_4;              }
        else if(__currentKeyStates[SDL_SCANCODE_KP_5]               == 1){ key = UTALKEY_KP_5;              }
        else if(__currentKeyStates[SDL_SCANCODE_KP_6]               == 1){ key = UTALKEY_KP_6;              }
        else if(__currentKeyStates[SDL_SCANCODE_KP_7]               == 1){ key = UTALKEY_KP_7;              }
        else if(__currentKeyStates[SDL_SCANCODE_KP_8]               == 1){ key = UTALKEY_KP_8;              }
        else if(__currentKeyStates[SDL_SCANCODE_KP_9]               == 1){ key = UTALKEY_KP_9;              }
        else if(__currentKeyStates[SDL_SCANCODE_KP_A]               == 1){ key = UTALKEY_KP_A;              }
        else if(__currentKeyStates[SDL_SCANCODE_KP_AMPERSAND]       == 1){ key = UTALKEY_KP_AMPERSAND;      }
        else if(__currentKeyStates[SDL_SCANCODE_KP_AT]              == 1){ key = UTALKEY_KP_AT;             }
        else if(__currentKeyStates[SDL_SCANCODE_KP_B]               == 1){ key = UTALKEY_KP_B;              }
        else if(__currentKeyStates[SDL_SCANCODE_KP_BACKSPACE]       == 1){ key = UTALKEY_KP_BACKSPACE;      }
        else if(__currentKeyStates[SDL_SCANCODE_KP_BINARY]          == 1){ key = UTALKEY_KP_BINARY;         }
        else if(__currentKeyStates[SDL_SCANCODE_KP_C]               == 1){ key = UTALKEY_KP_C;              }
        else if(__currentKeyStates[SDL_SCANCODE_KP_CLEAR]           == 1){ key = UTALKEY_KP_CLEAR;          }
        else if(__currentKeyStates[SDL_SCANCODE_KP_CLEARENTRY]      == 1){ key = UTALKEY_KP_CLEARENTRY;     }
        else if(__currentKeyStates[SDL_SCANCODE_KP_COLON]           == 1){ key = UTALKEY_KP_COLON;          }
        else if(__currentKeyStates[SDL_SCANCODE_KP_COMMA]           == 1){ key = UTALKEY_KP_COMMA;          }
        else if(__currentKeyStates[SDL_SCANCODE_KP_D]               == 1){ key = UTALKEY_KP_D;              }
        else if(__currentKeyStates[SDL_SCANCODE_KP_DBLAMPERSAND]    == 1){ key = UTALKEY_KP_DBLAMPERSAND;   }
        else if(__currentKeyStates[SDL_SCANCODE_KP_DBLVERTICALBAR]  == 1){ key = UTALKEY_KP_DBLVERTICALBAR; }
        else if(__currentKeyStates[SDL_SCANCODE_KP_DECIMAL]         == 1){ key = UTALKEY_KP_DECIMAL;        }
        else if(__currentKeyStates[SDL_SCANCODE_KP_DIVIDE]          == 1){ key = UTALKEY_KP_DIVIDE;         }
        else if(__currentKeyStates[SDL_SCANCODE_KP_E]               == 1){ key = UTALKEY_KP_E;              }
        else if(__currentKeyStates[SDL_SCANCODE_KP_ENTER]           == 1){ key = UTALKEY_KP_ENTER;          }
        else if(__currentKeyStates[SDL_SCANCODE_KP_EQUALS]          == 1){ key = UTALKEY_KP_EQUALS;         }
        else if(__currentKeyStates[SDL_SCANCODE_KP_EQUALSAS400]     == 1){ key = UTALKEY_KP_EQUALSAS400;    }
        else if(__currentKeyStates[SDL_SCANCODE_KP_EXCLAM]          == 1){ key = UTALKEY_KP_EXCLAM;         }
        else if(__currentKeyStates[SDL_SCANCODE_KP_F]               == 1){ key = UTALKEY_KP_F;              }
        else if(__currentKeyStates[SDL_SCANCODE_KP_GREATER]         == 1){ key = UTALKEY_KP_GREATER;        }
        else if(__currentKeyStates[SDL_SCANCODE_KP_HASH]            == 1){ key = UTALKEY_KP_HASH;           }
        else if(__currentKeyStates[SDL_SCANCODE_KP_HEXADECIMAL]     == 1){ key = UTALKEY_KP_HEXADECIMAL;    }
        else if(__currentKeyStates[SDL_SCANCODE_KP_LEFTBRACE]       == 1){ key = UTALKEY_KP_LEFTBRACE;      }
        else if(__currentKeyStates[SDL_SCANCODE_KP_LEFTPAREN]       == 1){ key = UTALKEY_KP_LEFTPAREN;      }
        else if(__currentKeyStates[SDL_SCANCODE_KP_LESS]            == 1){ key = UTALKEY_KP_LESS;           }
        else if(__currentKeyStates[SDL_SCANCODE_KP_MEMADD]          == 1){ key = UTALKEY_KP_MEMADD;         }
        else if(__currentKeyStates[SDL_SCANCODE_KP_MEMCLEAR]        == 1){ key = UTALKEY_KP_MEMCLEAR;       }
        else if(__currentKeyStates[SDL_SCANCODE_KP_MEMDIVIDE]       == 1){ key = UTALKEY_KP_MEMDIVIDE;      }
        else if(__currentKeyStates[SDL_SCANCODE_KP_MEMMULTIPLY]     == 1){ key = UTALKEY_KP_MEMMULTIPLY;    }
        else if(__currentKeyStates[SDL_SCANCODE_KP_MEMRECALL]       == 1){ key = UTALKEY_KP_MEMRECALL;      }
        else if(__currentKeyStates[SDL_SCANCODE_KP_MEMSTORE]        == 1){ key = UTALKEY_KP_MEMSTORE;       }
        else if(__currentKeyStates[SDL_SCANCODE_KP_MEMSUBTRACT]     == 1){ key = UTALKEY_KP_MEMSUBTRACT;    }
        else if(__currentKeyStates[SDL_SCANCODE_KP_MINUS]           == 1){ key = UTALKEY_KP_MINUS;          }
        else if(__currentKeyStates[SDL_SCANCODE_KP_MULTIPLY]        == 1){ key = UTALKEY_KP_MULTIPLY;       }
        else if(__currentKeyStates[SDL_SCANCODE_KP_OCTAL]           == 1){ key = UTALKEY_KP_OCTAL;          }
        else if(__currentKeyStates[SDL_SCANCODE_KP_PERCENT]         == 1){ key = UTALKEY_KP_PERCENT;        }
        else if(__currentKeyStates[SDL_SCANCODE_KP_PERIOD]          == 1){ key = UTALKEY_KP_PERIOD;         }
        else if(__currentKeyStates[SDL_SCANCODE_KP_PLUS]            == 1){ key = UTALKEY_KP_PLUS;           }
        else if(__currentKeyStates[SDL_SCANCODE_KP_PLUSMINUS]       == 1){ key = UTALKEY_KP_PLUSMINUS;      }
        else if(__currentKeyStates[SDL_SCANCODE_KP_POWER]           == 1){ key = UTALKEY_KP_POWER;          }
        else if(__currentKeyStates[SDL_SCANCODE_KP_RIGHTBRACE]      == 1){ key = UTALKEY_KP_RIGHTBRACE;     }
        else if(__currentKeyStates[SDL_SCANCODE_KP_RIGHTPAREN]      == 1){ key = UTALKEY_KP_RIGHTPAREN;     }
        else if(__currentKeyStates[SDL_SCANCODE_KP_SPACE]           == 1){ key = UTALKEY_KP_SPACE;          }
        else if(__currentKeyStates[SDL_SCANCODE_KP_TAB]             == 1){ key = UTALKEY_KP_TAB;            }
        else if(__currentKeyStates[SDL_SCANCODE_KP_VERTICALBAR]     == 1){ key = UTALKEY_KP_VERTICALBAR;    }
        else if(__currentKeyStates[SDL_SCANCODE_KP_XOR]             == 1){ key = UTALKEY_KP_XOR;            }
        else if(__currentKeyStates[SDL_SCANCODE_L]                  == 1){ key = UTALKEY_L;                 }
        else if(__currentKeyStates[SDL_SCANCODE_LALT]               == 1){ key = UTALKEY_LALT;              }
        else if(__currentKeyStates[SDL_SCANCODE_LCTRL]              == 1){ key = UTALKEY_LCTRL;             }
        else if(__currentKeyStates[SDL_SCANCODE_LEFT]               == 1){ key = UTALKEY_LEFT;              }
        else if(__currentKeyStates[SDL_SCANCODE_LEFTBRACKET]        == 1){ key = UTALKEY_LEFTBRACKET;       }
        else if(__currentKeyStates[SDL_SCANCODE_LGUI]               == 1){ key = UTALKEY_LGUI;              }
        else if(__currentKeyStates[SDL_SCANCODE_LSHIFT]             == 1){ key = UTALKEY_LSHIFT;            }
        else if(__currentKeyStates[SDL_SCANCODE_M]                  == 1){ key = UTALKEY_M;                 }
        else if(__currentKeyStates[SDL_SCANCODE_MAIL]               == 1){ key = UTALKEY_MAIL;              }
        else if(__currentKeyStates[SDL_SCANCODE_MEDIASELECT]        == 1){ key = UTALKEY_MEDIASELECT;       }
        else if(__currentKeyStates[SDL_SCANCODE_MENU]               == 1){ key = UTALKEY_MENU;              }
        else if(__currentKeyStates[SDL_SCANCODE_MINUS]              == 1){ key = UTALKEY_MINUS;             }
        else if(__currentKeyStates[SDL_SCANCODE_MODE]               == 1){ key = UTALKEY_MODE;              }
        else if(__currentKeyStates[SDL_SCANCODE_MUTE]               == 1){ key = UTALKEY_MUTE;              }
        else if(__currentKeyStates[SDL_SCANCODE_N]                  == 1){ key = UTALKEY_N;                 }
        else if(__currentKeyStates[SDL_SCANCODE_NUMLOCKCLEAR]       == 1){ key = UTALKEY_NUMLOCKCLEAR;      }
        else if(__currentKeyStates[SDL_SCANCODE_O]                  == 1){ key = UTALKEY_O;                 }
        else if(__currentKeyStates[SDL_SCANCODE_OPER]               == 1){ key = UTALKEY_OPER;              }
        else if(__currentKeyStates[SDL_SCANCODE_OUT]                == 1){ key = UTALKEY_OUT;               }
        else if(__currentKeyStates[SDL_SCANCODE_P]                  == 1){ key = UTALKEY_P;                 }
        else if(__currentKeyStates[SDL_SCANCODE_PAGEDOWN]           == 1){ key = UTALKEY_PAGEDOWN;          }
        else if(__currentKeyStates[SDL_SCANCODE_PAGEUP]             == 1){ key = UTALKEY_PAGEUP;            }
        else if(__currentKeyStates[SDL_SCANCODE_PASTE]              == 1){ key = UTALKEY_PASTE;             }
        else if(__currentKeyStates[SDL_SCANCODE_PAUSE]              == 1){ key = UTALKEY_PAUSE;             }
        else if(__currentKeyStates[SDL_SCANCODE_PERIOD]             == 1){ key = UTALKEY_PERIOD;            }
        else if(__currentKeyStates[SDL_SCANCODE_POWER]              == 1){ key = UTALKEY_POWER;             }
        else if(__currentKeyStates[SDL_SCANCODE_PRINTSCREEN]        == 1){ key = UTALKEY_PRINTSCREEN;       }
        else if(__currentKeyStates[SDL_SCANCODE_PRIOR]              == 1){ key = UTALKEY_PRIOR;             }
        else if(__currentKeyStates[SDL_SCANCODE_Q]                  == 1){ key = UTALKEY_Q;                 }
        else if(__currentKeyStates[SDL_SCANCODE_R]                  == 1){ key = UTALKEY_R;                 }
        else if(__currentKeyStates[SDL_SCANCODE_RALT]               == 1){ key = UTALKEY_RALT;              }
        else if(__currentKeyStates[SDL_SCANCODE_RCTRL]              == 1){ key = UTALKEY_RCTRL;             }
        else if(__currentKeyStates[SDL_SCANCODE_RETURN]             == 1){ key = UTALKEY_RETURN;            }
        else if(__currentKeyStates[SDL_SCANCODE_RETURN2]            == 1){ key = UTALKEY_RETURN2;           }
        else if(__currentKeyStates[SDL_SCANCODE_RGUI]               == 1){ key = UTALKEY_RGUI;              }
        else if(__currentKeyStates[SDL_SCANCODE_RIGHT]              == 1){ key = UTALKEY_RIGHT;             }
        else if(__currentKeyStates[SDL_SCANCODE_RIGHTBRACKET]       == 1){ key = UTALKEY_RIGHTBRACKET;      }
        else if(__currentKeyStates[SDL_SCANCODE_RSHIFT]             == 1){ key = UTALKEY_RSHIFT;            }
        else if(__currentKeyStates[SDL_SCANCODE_S]                  == 1){ key = UTALKEY_S;                 }
        else if(__currentKeyStates[SDL_SCANCODE_SCROLLLOCK]         == 1){ key = UTALKEY_SCROLLLOCK;        }
        else if(__currentKeyStates[SDL_SCANCODE_SELECT]             == 1){ key = UTALKEY_SELECT;            }
        else if(__currentKeyStates[SDL_SCANCODE_SEMICOLON]          == 1){ key = UTALKEY_SEMICOLON;         }
        else if(__currentKeyStates[SDL_SCANCODE_SEPARATOR]          == 1){ key = UTALKEY_SEPARATOR;         }
        else if(__currentKeyStates[SDL_SCANCODE_SLASH]              == 1){ key = UTALKEY_SLASH;             }
        else if(__currentKeyStates[SDL_SCANCODE_SLEEP]              == 1){ key = UTALKEY_SLEEP;             }
        else if(__currentKeyStates[SDL_SCANCODE_SPACE]              == 1){ key = UTALKEY_SPACE;             }
        else if(__currentKeyStates[SDL_SCANCODE_STOP]               == 1){ key = UTALKEY_STOP;              }
        else if(__currentKeyStates[SDL_SCANCODE_SYSREQ]             == 1){ key = UTALKEY_SYSREQ;            }
        else if(__currentKeyStates[SDL_SCANCODE_T]                  == 1){ key = UTALKEY_T;                 }
        else if(__currentKeyStates[SDL_SCANCODE_TAB]                == 1){ key = UTALKEY_TAB;               }
        else if(__currentKeyStates[SDL_SCANCODE_THOUSANDSSEPARATOR] == 1){ key = UTALKEY_THOUSANDSSEPARATOR;}
        else if(__currentKeyStates[SDL_SCANCODE_U]                  == 1){ key = UTALKEY_U;                 }
        else if(__currentKeyStates[SDL_SCANCODE_UNDO]               == 1){ key = UTALKEY_UNDO;              }
        else if(__currentKeyStates[SDL_SCANCODE_UNKNOWN]            == 1){ key = UTALKEY_UNKNOWN;           }
        else if(__currentKeyStates[SDL_SCANCODE_UP]                 == 1){ key = UTALKEY_UP;                }
        else if(__currentKeyStates[SDL_SCANCODE_V]                  == 1){ key = UTALKEY_V;                 }
        else if(__currentKeyStates[SDL_SCANCODE_VOLUMEDOWN]         == 1){ key = UTALKEY_VOLUMEDOWN;        }
        else if(__currentKeyStates[SDL_SCANCODE_VOLUMEUP]           == 1){ key = UTALKEY_VOLUMEUP;          }
        else if(__currentKeyStates[SDL_SCANCODE_W]                  == 1){ key = UTALKEY_W;                 }
        else if(__currentKeyStates[SDL_SCANCODE_WWW]                == 1){ key = UTALKEY_WWW;               }
        else if(__currentKeyStates[SDL_SCANCODE_X]                  == 1){ key = UTALKEY_X;                 }
        else if(__currentKeyStates[SDL_SCANCODE_Y]                  == 1){ key = UTALKEY_Y;                 }
        else if(__currentKeyStates[SDL_SCANCODE_Z]                  == 1){ key = UTALKEY_Z;                 }
    }
    pthread_mutex_unlock(&__utalCanvasWindowMutex);
    
    return key;
}

UtalCanvasWindowMouseInfo UtalCanvasWindowGetMouseInfo()
{
    UtalCanvasWindowMouseInfo info;
    pthread_mutex_lock(&__utalCanvasWindowMutex);
    info.button = __mouseInfo.button;
    info.x = convertXAxis(__mouseInfo.x);
    info.y = convertYAxis(__mouseInfo.y);
    pthread_mutex_unlock(&__utalCanvasWindowMutex);
    
    if(info.button == 0)
    {
        info.button = -1;
    }
    return info;
}



