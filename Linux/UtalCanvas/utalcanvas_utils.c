#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "utalcanvas_utils.h"
#include "utalcanvas_structures.h"

void UtalCanvasUtilsGetTag( UtalCanvasElementType type, void* data, char tag[TAG_NAME_LENGTH] )
{
    if( tag == NULL )
    {
        return;
    }
    
    tag[0] = '\0';
    if( type == UTALCANVAS_ELEMENT_CIRCLE )
    {
        UtalCanvasCircle* element = (UtalCanvasCircle*)data;
        if(element->tag != NULL)
        {
            strncpy(tag, element->tag, TAG_NAME_LENGTH);
        }
    }
    else if( type == UTALCANVAS_ELEMENT_FILLED_CIRCLE )
    {
        UtalCanvasFilledCircle* element = (UtalCanvasFilledCircle*)data;
        if(element->tag != NULL)
        {
            strncpy(tag, element->tag, TAG_NAME_LENGTH);
        }
    }
    else if( type == UTALCANVAS_ELEMENT_FILLED_RECTANGLE )
    {
        UtalCanvasFilledRectangle* element = (UtalCanvasFilledRectangle*)data;
        if(element->tag != NULL)
        {
            strncpy(tag, element->tag, TAG_NAME_LENGTH);
        }
    }
    else if( type == UTALCANVAS_ELEMENT_LINE )
    {
        UtalCanvasLine* element = (UtalCanvasLine*)data;
        if(element->tag != NULL)
        {
            strncpy(tag, element->tag, TAG_NAME_LENGTH);
        }
    }
    else if( type == UTALCANVAS_ELEMENT_POINT )
    {
        UtalCanvasPoint* element = (UtalCanvasPoint*)data;
        if(element->tag != NULL)
        {
            strncpy(tag, element->tag, TAG_NAME_LENGTH);
        }
    }
    else if( type == UTALCANVAS_ELEMENT_RECTANGLE )
    {
        UtalCanvasRectangle* element = (UtalCanvasRectangle*)data;
        if(element->tag != NULL)
        {
            strncpy(tag, element->tag, TAG_NAME_LENGTH);
        }
    }
    else if( type == UTALCANVAS_ELEMENT_TEXT )
    {
        UtalCanvasText* element = (UtalCanvasText*)data;
        if(element->tag != NULL)
        {
            strncpy(tag, element->tag, TAG_NAME_LENGTH);
        }
    }
    else if( type == UTALCANVAS_ELEMENT_IMAGE )
    {
        UtalCanvasImage* element = (UtalCanvasImage*)data;
        if(element->tag != NULL)
        {
            strncpy(tag, element->tag, TAG_NAME_LENGTH);
        }
    }
    
    
}

bool UtalCanvasUtilsIsValidTag(char tag[TAG_NAME_LENGTH])
{
    if(tag == NULL)
    {
        return false;
    }
    return tag[0] != '\0';
}


void UtalCanvasUtilsFixRectangle(  UtalCanvasPlainRectangle *rectangle, int x1, int y1, int x2, int y2 )
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

void delay(double delay_seconds)
{
    const time_t start = time(NULL);
    time_t current;

    do
    {
        time(&current);
    }
    while(difftime(current, start) < delay_seconds);
}


