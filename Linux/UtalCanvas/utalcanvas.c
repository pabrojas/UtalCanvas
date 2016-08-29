
#include <stdarg.h>
#include <string.h>

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "utalcanvas.h"
#include "utalcanvas_window.h"
#include "utalcanvas_colors.h"
#include "utalcanvas_utils.h"
#include "utalcanvas_structures.h"

char __no_tag[TAG_NAME_LENGTH] = "[[UtalCanvasNoTag-3906551015]]";


void show_window()
{
    UtalCanvasWindowStart();
}

void close_window()
{
    UtalCanvasWindowClose();
}

void window_size(int width, int height)
{
    UtalCanvasWindowSetSize(width, height);
}

void window_coordinates(int x_bottom, int y_bottom, int x_top, int y_top)
{
    UtalCanvasWindowSetViewport(x_bottom, y_bottom, x_top, y_top);
}

void window_background(char background[COLOR_NAME_LENGTH])
{
    UtalCanvasWindowSetBackground(background);
}

void window_title(char title[MAX_TEXT_LENGTH])
{
    UtalCanvasWindowSetTitle(title);
}

int window_is_closed()
{
    return UtalCanvasWindowIsClosed();
}


int create_point(int x, int y, char color[COLOR_NAME_LENGTH], ...)
{
    char tag[TAG_NAME_LENGTH];
    va_list parameters;
    va_start(parameters, color);
    char *p_tag = va_arg(parameters, char *);
    
    if(strlen(p_tag) == 0 || p_tag == NULL)
    {
        strncpy(tag, __no_tag, TAG_NAME_LENGTH);
    }
    else
    {
        strncpy(tag, p_tag, TAG_NAME_LENGTH);
    }
    
    UtalCanvasPoint* point = (UtalCanvasPoint*)malloc( sizeof(UtalCanvasPoint));
    point->x = x;
    point->y = y;
    point->color = UtalCanvasColorGetByName(color);
    strncpy(point->tag, tag, TAG_NAME_LENGTH);
    return UtalCanvasWindowAddElement( UTALCANVAS_ELEMENT_POINT, point );
}

int create_line(int x1, int y1, int x2, int y2, char color[COLOR_NAME_LENGTH], ...)
{
    char tag[TAG_NAME_LENGTH];
    va_list parameters;
    va_start(parameters, color);
    char *p_tag = va_arg(parameters, char *);
    
    if(strlen(p_tag) == 0 || p_tag == NULL)
    {
        strncpy(tag, __no_tag, TAG_NAME_LENGTH);
    }
    else
    {
        strncpy(tag, p_tag, TAG_NAME_LENGTH);
    }
    
    UtalCanvasLine* line;
    line = (UtalCanvasLine*)malloc( sizeof(UtalCanvasLine));
    line->x1 = x1;
    line->y1 = y1;
    line->x2 = x2;
    line->y2 = y2;
    line->color = UtalCanvasColorGetByName(color);
    strncpy(line->tag, tag, TAG_NAME_LENGTH);
    return UtalCanvasWindowAddElement( UTALCANVAS_ELEMENT_LINE, line );
}

int create_circle(int x, int y, int radius, char color[COLOR_NAME_LENGTH], ...)
{
    char tag[TAG_NAME_LENGTH];
    va_list parameters;
    va_start(parameters, color);
    char *p_tag = va_arg(parameters, char *);
    
    if(strlen(p_tag) == 0 || p_tag == NULL)
    {
        strncpy(tag, __no_tag, TAG_NAME_LENGTH);
    }
    else
    {
        strncpy(tag, p_tag, TAG_NAME_LENGTH);
    }
    
    UtalCanvasCircle* circle;
    circle = (UtalCanvasCircle*)malloc( sizeof(UtalCanvasCircle));
    circle->x = x;
    circle->y = y;
    circle->radio = radius;
    circle->color = UtalCanvasColorGetByName(color);
    strncpy(circle->tag, tag, TAG_NAME_LENGTH);
    return UtalCanvasWindowAddElement( UTALCANVAS_ELEMENT_CIRCLE, circle );
}

int create_filled_circle(int x, int y, int radius, char borderColor[COLOR_NAME_LENGTH], char fillColor[COLOR_NAME_LENGTH], ...)
{
    char tag[TAG_NAME_LENGTH];
    va_list parameters;
    va_start(parameters, fillColor);
    char *p_tag = va_arg(parameters, char *);
    
    if(strlen(p_tag) == 0 || p_tag == NULL)
    {
        strncpy(tag, __no_tag, TAG_NAME_LENGTH);
    }
    else
    {
        strncpy(tag, p_tag, TAG_NAME_LENGTH);
    }
    
    UtalCanvasFilledCircle* filledCircle;
    filledCircle = (UtalCanvasFilledCircle*)malloc( sizeof(UtalCanvasFilledCircle));
    filledCircle->x = x;
    filledCircle->y = y;
    filledCircle->radio = radius;
    filledCircle->outerColor = UtalCanvasColorGetByName(borderColor);
    filledCircle->fillColor = UtalCanvasColorGetByName(fillColor);
    strncpy(filledCircle->tag, tag, TAG_NAME_LENGTH);
    return UtalCanvasWindowAddElement( UTALCANVAS_ELEMENT_FILLED_CIRCLE, filledCircle );
}

int create_rectangle(int x1, int y1, int x2, int y2, char color[COLOR_NAME_LENGTH], ...)
{
    char tag[TAG_NAME_LENGTH];
    va_list parameters;
    va_start(parameters, color);
    char *p_tag = va_arg(parameters, char *);
    
    if(strlen(p_tag) == 0 || p_tag == NULL)
    {
        strncpy(tag, __no_tag, TAG_NAME_LENGTH);
    }
    else
    {
        strncpy(tag, p_tag, TAG_NAME_LENGTH);
    }
    
    UtalCanvasRectangle* rectangle;
    rectangle = (UtalCanvasRectangle*)malloc( sizeof(UtalCanvasRectangle));
    rectangle->x1 = x1 < x2 ? x1 : x2;
    rectangle->y1 = x1 < y2 ? y1 : y2;
    rectangle->x2 = x1 < x2 ? x2 : x1;
    rectangle->y2 = x1 < y2 ? y2 : y1;
    rectangle->color = UtalCanvasColorGetByName(color);
    strncpy(rectangle->tag, tag, TAG_NAME_LENGTH);
    return UtalCanvasWindowAddElement( UTALCANVAS_ELEMENT_RECTANGLE, rectangle );
}

int create_filled_rectangle(int x1, int y1, int x2, int y2, char borderColor[COLOR_NAME_LENGTH], char fillColor[COLOR_NAME_LENGTH], ...)
{
    char tag[TAG_NAME_LENGTH];
    va_list parameters;
    va_start(parameters, fillColor);
    char *p_tag = va_arg(parameters, char *);
    
    if(strlen(p_tag) == 0 || p_tag == NULL)
    {
        strncpy(tag, __no_tag, TAG_NAME_LENGTH);
    }
    else
    {
        strncpy(tag, p_tag, TAG_NAME_LENGTH);
    }
    
    UtalCanvasFilledRectangle* filledRectangle;
    filledRectangle = (UtalCanvasFilledRectangle*)malloc( sizeof(UtalCanvasFilledRectangle));
    filledRectangle->x1 = x1 < x2 ? x1 : x2;
    filledRectangle->y1 = x1 < y2 ? y1 : y2;
    filledRectangle->x2 = x1 < x2 ? x2 : x1;
    filledRectangle->y2 = x1 < y2 ? y2 : y1;
    filledRectangle->outerColor = UtalCanvasColorGetByName(borderColor);
    filledRectangle->fillColor = UtalCanvasColorGetByName(fillColor);
    strncpy(filledRectangle->tag, tag, TAG_NAME_LENGTH);
    return UtalCanvasWindowAddElement( UTALCANVAS_ELEMENT_FILLED_RECTANGLE, filledRectangle );
}

int create_image(int x, int y, int width, int height, char filename[PATHNAME_LENGTH], ...)
{
    char tag[TAG_NAME_LENGTH];
    va_list parameters;
    va_start(parameters, filename);
    char *p_tag = va_arg(parameters, char *);
    
    if(strlen(p_tag) == 0 || p_tag == NULL)
    {
        strncpy(tag, __no_tag, TAG_NAME_LENGTH);
    }
    else
    {
        strncpy(tag, p_tag, TAG_NAME_LENGTH);
    }
    
    SDL_Surface* surface = IMG_Load( filename );
    if(surface == NULL)
    {
        printf("[UtalCanvas] No se puede cargar la imagen: '%s'.\n", filename);
        return -1;
    }
    SDL_FreeSurface(surface);
          
    UtalCanvasImage* image;
    image = (UtalCanvasImage*)malloc( sizeof(UtalCanvasImage));
    image->x = x;
    image->y = y;
    image->width = width;
    image->height = height;
    strncpy(image->filename, filename, TAG_NAME_LENGTH);
    strncpy(image->tag, tag, TAG_NAME_LENGTH);
    image->size = NULL;
    image->texture = NULL;
    return UtalCanvasWindowAddElement( UTALCANVAS_ELEMENT_IMAGE, image );
}

int create_text(char fontFile[PATHNAME_LENGTH], int x, int y, char caption[MAX_TEXT_LENGTH], int size, char color[COLOR_NAME_LENGTH], ...)
{
    char tag[TAG_NAME_LENGTH];
    va_list parameters;
    va_start(parameters, color);
    char *p_tag = va_arg(parameters, char *);
    
    if(strlen(p_tag) == 0 || p_tag == NULL)
    {
        strncpy(tag, __no_tag, TAG_NAME_LENGTH);
    }
    else
    {
        strncpy(tag, p_tag, TAG_NAME_LENGTH);
    }
/*
 * 
 * Verificar que el archivo existe.
    TTF_Font* font = TTF_OpenFont(fontFile, size);
    if (font == NULL)
    {
        
        printf("[UtalCanvas] No se puede cargar el archivo de fuentes: '%s'.\n", fontFile);
        return -1;
    }
    TTF_CloseFont(font);
 * 
 * 
    
*/
    UtalCanvasText* text;
    text = (UtalCanvasText*)malloc( sizeof(UtalCanvasText));
    text->x = x;
    text->y = y;
    text->size = size;
    strncpy(text->fontFile, fontFile, PATHNAME_LENGTH);
    text->color = UtalCanvasColorGetByName(color);
    strncpy(text->text, caption, MAX_TEXT_LENGTH);
    strncpy(text->tag, tag, TAG_NAME_LENGTH);
    text->font = NULL;
    text->textSurface = NULL;
    text->texture = NULL;
    
    return UtalCanvasWindowAddElement( UTALCANVAS_ELEMENT_TEXT, text );
}

void erase_by_index(int index)
{
    UtalCanvasWindowRemoveElementByIndex(index);
}

void erase_by_tag(char tag[TAG_NAME_LENGTH])
{
    UtalCanvasWindowRemoveElementByTag(tag);
}

void erase_all()
{
    UtalCanvasWindowRemoveAllElement();
}

void move_by_index(int index, int dx, int dy)
{
    UtalCanvasWindowMoveElementByIndex(index, dx, dy);
}

void move_by_tag(char tag[TAG_NAME_LENGTH], int dx, int dy)
{
    UtalCanvasWindowMoveElementByTag(tag, dx, dy);
}

int key_pressed()
{
    return UtalCanvasWindowGetPressedKey();
}

struct UtalCanvasMouse mouse_state()
{
    UtalCanvasWindowMouseInfo mouseInfo;
    mouseInfo = UtalCanvasWindowGetMouseInfo();
    
    struct UtalCanvasMouse mouse;
    mouse.x = mouseInfo.x;
    mouse.y = mouseInfo.y;
    mouse.boton = mouseInfo.button;
    
    return mouse;
}

