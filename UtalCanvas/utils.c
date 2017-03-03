#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "utils.h"
#include "structures.h"

void get_element_tag( UtalCanvasElementType type, void* data, char tag[TAG_NAME_LENGTH] )
{
    if( tag == NULL )
    {
        return;
    }
    
    tag[0] = '\0';
    if( type == ELEMENT_CIRCLE )
    {
        ElementCircle* element = (ElementCircle*)data;
        if(element->tag != NULL)
        {
            strncpy(tag, element->tag, TAG_NAME_LENGTH);
        }
    }
    else if( type == ELEMENT_FILLED_CIRCLE )
    {
        ElementFilledCircle* element = (ElementFilledCircle*)data;
        if(element->tag != NULL)
        {
            strncpy(tag, element->tag, TAG_NAME_LENGTH);
        }
    }
    else if( type == ELEMENT_FILLED_RECTANGLE )
    {
        ElementFilledRectangle* element = (ElementFilledRectangle*)data;
        if(element->tag != NULL)
        {
            strncpy(tag, element->tag, TAG_NAME_LENGTH);
        }
    }
    else if( type == ELEMENT_LINE )
    {
        ElementLine* element = (ElementLine*)data;
        if(element->tag != NULL)
        {
            strncpy(tag, element->tag, TAG_NAME_LENGTH);
        }
    }
    else if( type == ELEMENT_POINT )
    {
        ElementPoint* element = (ElementPoint*)data;
        if(element->tag != NULL)
        {
            strncpy(tag, element->tag, TAG_NAME_LENGTH);
        }
    }
    else if( type == ELEMENT_RECTANGLE )
    {
        ElementRectangle* element = (ElementRectangle*)data;
        if(element->tag != NULL)
        {
            strncpy(tag, element->tag, TAG_NAME_LENGTH);
        }
    }
    else if( type == ELEMENT_TEXT )
    {
        ElementText* element = (ElementText*)data;
        if(element->tag != NULL)
        {
            strncpy(tag, element->tag, TAG_NAME_LENGTH);
        }
    }
    else if( type == ELEMENT_IMAGE )
    {
        ElementImage* element = (ElementImage*)data;
        if(element->tag != NULL)
        {
            strncpy(tag, element->tag, TAG_NAME_LENGTH);
        }
    }
}

bool is_valid_element_tag(char tag[TAG_NAME_LENGTH])
{
    if(tag == NULL)
    {
        return false;
    }
    return tag[0] != '\0';
}


void fix_rectangle(UtalCanvasPlainRectangle *rectangle, int x1, int y1, int x2, int y2 )
{
    int x = (int)fmin(x1, x2);
    int y = (int)fmin(y1, y2);
    int width = (int)fabs(x1 - x2); 
    int height = (int)fabs(y1 - y2);

    rectangle->x = x;
    rectangle->y = y;
    rectangle->width = width;
    rectangle->height = height;
}

bool file_exists( const char* filename)
{
    FILE* file = fopen(filename, "r");
    if( file  )
    {
        fclose(file);
        return true;
    }
    return false;
}

int convert_x_to_window_value(double world_value, UtalCanvasWindowDimension window_dimension, UtalCanvasWindowViewport world_viewport)
{
    int windowWidth = window_dimension.width;
    double worldWidth = world_viewport.xMax - world_viewport.xMin;
    
    int direction = 1;
    if( world_value < world_viewport.xMin )
    {
        direction = -1;
    }
    return (int)(((direction*world_value)/(1.0*worldWidth))*windowWidth);   
}

int convert_y_to_window_value(double world_value, UtalCanvasWindowDimension window_dimension, UtalCanvasWindowViewport world_viewport)
{
    int windowHeight = window_dimension.height;
    double worldHeight = world_viewport.yMax - world_viewport.yMin;
    
    int direction = 1;
    if( world_value < world_viewport.yMin )
    {
        direction = 1;
    }
    return (int)(((direction*world_value)/(1.0*worldHeight))*windowHeight);
}

double convert_x_to_world_value(int window_value, UtalCanvasWindowDimension window_dimension, UtalCanvasWindowViewport world_viewport)
{
    int windowWidth = window_dimension.width;
    double worldWidth = world_viewport.xMax - world_viewport.xMin;
    return window_value*worldWidth/windowWidth;
}
    
double convert_y_to_world_value(int window_value, UtalCanvasWindowDimension window_dimension, UtalCanvasWindowViewport world_viewport)
{
    int windowHeight = window_dimension.height;
    double worldHeight = world_viewport.yMax - world_viewport.yMin;
    return window_value*worldHeight/windowHeight;
}



