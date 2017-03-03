
#include <stdarg.h>
#include <string.h>

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "utalcanvas.h"
#include "window.h"
#include "colors.h"
#include "utils.h"
#include "structures.h"
#include "resources_list.h"
#include "joystick_list.h"

extern char __no_tag[TAG_NAME_LENGTH];


void show_window()
{
    ucw_start();
}

void close_window()
{
    ucw_close();
}

void window_size(int width, int height)
{
    ucw_set_size(width, height);
}

void window_coordinates(double x_bottom, double y_bottom, double x_top, double y_top)
{
    ucw_set_viewport(x_bottom, y_bottom, x_top, y_top);
}

void window_background(char background[COLOR_NAME_LENGTH])
{
    ucw_set_background(background);
}

void window_title(char title[MAX_TEXT_LENGTH])
{
    ucw_set_title(title);
}

int window_is_closed()
{
    return ucw_is_closed();
}


int create_point(double x, double y, char color[COLOR_NAME_LENGTH], ...)
{
    char tag[TAG_NAME_LENGTH];
    va_list parameters;
    va_start(parameters, color);
    char *p_tag = va_arg(parameters, char *);
    
    if(p_tag == NULL || strlen(p_tag) == 0)
    {
        strncpy(tag, __no_tag, TAG_NAME_LENGTH);
    }
    else
    {
        strncpy(tag, p_tag, TAG_NAME_LENGTH);
    }
    
    ElementPoint* point = (ElementPoint*)malloc( sizeof(ElementPoint));
    point->x = x;
    point->y = y;
    point->color = get_color_by_name(color);
    strncpy(point->tag, tag, TAG_NAME_LENGTH);
    return ucw_add_element( ELEMENT_POINT, point );
}

int create_line(double x1, double y1, double x2, double y2, char color[COLOR_NAME_LENGTH], ...)
{
    char tag[TAG_NAME_LENGTH];
    va_list parameters;
    va_start(parameters, color);
    char *p_tag = va_arg(parameters, char *);
    
    if(p_tag == NULL || strlen(p_tag) == 0)
    {
        strncpy(tag, __no_tag, TAG_NAME_LENGTH);
    }
    else
    {
        strncpy(tag, p_tag, TAG_NAME_LENGTH);
    }
    
    ElementLine* line;
    line = (ElementLine*)malloc( sizeof(ElementLine));
    line->x1 = x1;
    line->y1 = y1;
    line->x2 = x2;
    line->y2 = y2;
    line->color = get_color_by_name(color);
    strncpy(line->tag, tag, TAG_NAME_LENGTH);
    return ucw_add_element( ELEMENT_LINE, line );
}

int create_circle(double x, double y, double radius, char color[COLOR_NAME_LENGTH], ...)
{
    char tag[TAG_NAME_LENGTH];
    va_list parameters;
    va_start(parameters, color);
    char *p_tag = va_arg(parameters, char *);
    
    if(p_tag == NULL || strlen(p_tag) == 0)
    {
        strncpy(tag, __no_tag, TAG_NAME_LENGTH);
    }
    else
    {
        strncpy(tag, p_tag, TAG_NAME_LENGTH);
    }
    
    ElementCircle* circle;
    circle = (ElementCircle*)malloc( sizeof(ElementCircle));
    circle->x = x;
    circle->y = y;
    circle->radio = radius;
    circle->color = get_color_by_name(color);
    strncpy(circle->tag, tag, TAG_NAME_LENGTH);
    return ucw_add_element( ELEMENT_CIRCLE, circle );
}

int create_filled_circle(double x, double y, double radius, char borderColor[COLOR_NAME_LENGTH], char fillColor[COLOR_NAME_LENGTH], ...)
{
    char tag[TAG_NAME_LENGTH];
    va_list parameters;
    va_start(parameters, fillColor);
    char *p_tag = va_arg(parameters, char *);
    
    if(p_tag == NULL || strlen(p_tag) == 0)
    {
        strncpy(tag, __no_tag, TAG_NAME_LENGTH);
    }
    else
    {
        strncpy(tag, p_tag, TAG_NAME_LENGTH);
    }
    
    ElementFilledCircle* filledCircle;
    filledCircle = (ElementFilledCircle*)malloc( sizeof(ElementFilledCircle));
    filledCircle->x = x;
    filledCircle->y = y;
    filledCircle->radio = radius;
    filledCircle->outerColor = get_color_by_name(borderColor);
    filledCircle->fillColor = get_color_by_name(fillColor);
    strncpy(filledCircle->tag, tag, TAG_NAME_LENGTH);
    return ucw_add_element( ELEMENT_FILLED_CIRCLE, filledCircle );
}

int create_rectangle(double x1, double y1, double x2, double y2, char color[COLOR_NAME_LENGTH], ...)
{
    char tag[TAG_NAME_LENGTH];
    va_list parameters;
    va_start(parameters, color);
    char *p_tag = va_arg(parameters, char *);
    
    if(p_tag == NULL || strlen(p_tag) == 0)
    {
        strncpy(tag, __no_tag, TAG_NAME_LENGTH);
    }
    else
    {
        strncpy(tag, p_tag, TAG_NAME_LENGTH);
    }
    
    ElementRectangle* rectangle;
    rectangle = (ElementRectangle*)malloc( sizeof(ElementRectangle));
    rectangle->x1 = x1 < x2 ? x1 : x2;
    rectangle->y1 = x1 < y2 ? y1 : y2;
    rectangle->x2 = x1 < x2 ? x2 : x1;
    rectangle->y2 = x1 < y2 ? y2 : y1;
    rectangle->color = get_color_by_name(color);
    strncpy(rectangle->tag, tag, TAG_NAME_LENGTH);
    return ucw_add_element( ELEMENT_RECTANGLE, rectangle );
}

int create_filled_rectangle(double x1, double y1, double x2, double y2, char borderColor[COLOR_NAME_LENGTH], char fillColor[COLOR_NAME_LENGTH], ...)
{
    char tag[TAG_NAME_LENGTH];
    va_list parameters;
    va_start(parameters, fillColor);
    char *p_tag = va_arg(parameters, char *);
    
    if(p_tag == NULL || strlen(p_tag) == 0)
    {
        strncpy(tag, __no_tag, TAG_NAME_LENGTH);
    }
    else
    {
        strncpy(tag, p_tag, TAG_NAME_LENGTH);
    }
    
    ElementFilledRectangle* filledRectangle;
    filledRectangle = (ElementFilledRectangle*)malloc( sizeof(ElementFilledRectangle));
    filledRectangle->x1 = x1 < x2 ? x1 : x2;
    filledRectangle->y1 = x1 < y2 ? y1 : y2;
    filledRectangle->x2 = x1 < x2 ? x2 : x1;
    filledRectangle->y2 = x1 < y2 ? y2 : y1;
    filledRectangle->outerColor = get_color_by_name(borderColor);
    filledRectangle->fillColor = get_color_by_name(fillColor);
    strncpy(filledRectangle->tag, tag, TAG_NAME_LENGTH);
    return ucw_add_element( ELEMENT_FILLED_RECTANGLE, filledRectangle );
}

int create_image(double x, double y, double width, double height, char filename[PATHNAME_LENGTH], ...)
{
    if( !file_exists(filename) )
    {
        return -1;
    }
    
    char tag[TAG_NAME_LENGTH];
    va_list parameters;
    va_start(parameters, filename);
    char *p_tag = va_arg(parameters, char *);
    
    if(p_tag == NULL || strlen(p_tag) == 0)
    {
        strncpy(tag, __no_tag, TAG_NAME_LENGTH);
    }
    else
    {
        strncpy(tag, p_tag, TAG_NAME_LENGTH);
    }
          
    ElementImage* image;
    image = (ElementImage*)malloc( sizeof(ElementImage));
    image->x = x;
    image->y = y;
    image->width = width;
    image->height = height;
    strncpy(image->filename, filename, TAG_NAME_LENGTH);
    strncpy(image->tag, tag, TAG_NAME_LENGTH);
    image->size = NULL;
    image->texture = NULL;
    
    return ucw_add_element( ELEMENT_IMAGE, image );
}

int create_text(char fontFile[PATHNAME_LENGTH], double x, double y, char caption[MAX_TEXT_LENGTH], double size, char color[COLOR_NAME_LENGTH], ...)
{
    char tag[TAG_NAME_LENGTH];
    va_list parameters;
    va_start(parameters, color);
    char *p_tag = va_arg(parameters, char *);
    
    if(p_tag == NULL || strlen(p_tag) == 0)
    {
        strncpy(tag, __no_tag, TAG_NAME_LENGTH);
    }
    else
    {
        strncpy(tag, p_tag, TAG_NAME_LENGTH);
    }

    ElementText* text;
    text = (ElementText*)malloc( sizeof(ElementText));
    text->x = x;
    text->y = y;
    text->size = size;
    strncpy(text->fontFile, fontFile, PATHNAME_LENGTH);
    text->color = get_color_by_name(color);
    strncpy(text->text, caption, MAX_TEXT_LENGTH);
    strncpy(text->tag, tag, TAG_NAME_LENGTH);
    text->font = NULL;
    text->textSurface = NULL;
    text->texture = NULL;
    
    return ucw_add_element(ELEMENT_TEXT, text);
}

void erase_by_index(int index)
{
    ucw_remove_element_by_id(index);
}

void erase_by_tag(char tag[TAG_NAME_LENGTH])
{
    ucw_remove_element_by_tag(tag);
}

void erase_all()
{
    ucw_remove_all_elements();
}

void move_by_index(int index, double dx, double dy)
{
    ucw_move_element_by_id(index, dx, dy);
}

void move_by_tag(char tag[TAG_NAME_LENGTH], double dx, double dy)
{
    ucw_move_element_by_tag(tag, dx, dy);
}

int key_pressed()
{
    return ucw_get_key_pressed();
}

struct UtalCanvasMouse mouse_state()
{
    UtalCanvasWindowMouseInfo mouseInfo;
    mouseInfo = ucw_get_mouse_state();
    
    struct UtalCanvasMouse mouse;
    mouse.x = mouseInfo.x;
    mouse.y = mouseInfo.y;
    mouse.boton = mouseInfo.button;
    
    return mouse;
}

int play_audio(char filename[PATHNAME_LENGTH], int loops)
{
    return ucw_play_audio(filename, loops);
}

void stop_audio(int id)
{
    ucw_stop_audio(id);
}

void pause_audio(int id)
{
    ucw_pause_audio(id);
}

void resume_audio(int id)
{
    ucw_resume_audio(id);
}

int joystick_button_is_pressed( int joystick_id, int button )
{
    return ucw_get_joystick_button_state(joystick_id, button);
}

int joystick_axis_value( int joystick_id, int axis )
{
    return ucw_get_joystick_axis_value(joystick_id, axis);
}

int joystick_is_connected( int joystick_id )
{
    return ucw_get_joystick_state(joystick_id);
}