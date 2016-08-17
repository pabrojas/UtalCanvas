#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utalcanvas_list.h"
#include "utalcanvas_structures.h"
#include "utalcanvas_definitions.h"
#include "utalcanvas_utils.h"

int __elementIndex = 0;
UtalCanvasNode* __elementList = NULL;

UtalCanvasNode* UtalCanvasListGetFirst()
{
    return __elementList;
}

int UtalCanvasListAddElement(UtalCanvasElementType type, void* data)
{
    __elementIndex++;
    
    UtalCanvasNode* new_element = (UtalCanvasNode*)malloc(sizeof(UtalCanvasNode));
    new_element->type = type;
    
    char tag[TAG_NAME_LENGTH];
    UtalCanvasUtilsGetTag(type, data, tag);
    
    if(UtalCanvasUtilsIsValidTag(tag))
    {
        strncpy(new_element->tag, tag, TAG_NAME_LENGTH);
    }
    new_element->data = data;

    if( __elementList == NULL )
    {
        new_element->index = __elementIndex;
        __elementList = new_element;
        __elementList->next = __elementList;
        __elementList->prev = __elementList;
        return new_element->index;
    }

    UtalCanvasNode* last = __elementList->prev;
    new_element->index = __elementIndex;

    last->next = new_element;
    new_element->prev = last;
    new_element->next = __elementList;
    __elementList->prev = new_element;

    return new_element->index;
}


void UtalCanvasListRemoveElementByIndex(int index)
{
    UtalCanvasNode* node = UtalCanvasListGetFirst();
    if(node == NULL)
    {
        return;
    }
    
    do
    {
        if( node->index == index )
        {
            //UtalCanvasListFreeResources(node);
            //si este nodo se apunta a si mismo la lista solo tiene un único elemento
            if( node->next == node )
            {
                __elementList = NULL;
                //free(node);
            }
            else
            {   
                if(node->index == __elementList->index)
                {
                    __elementList = node->next;
                }
                
                node->prev->next = node->next;
                node->next->prev = node->prev;
                node->next = NULL;
                node->prev = NULL;
                //free(node);
                
            }
            return;
        }
        node = node->next;
    }
    while( node != __elementList );
}

void UtalCanvasListRemoveElementByTag(char tag[TAG_NAME_LENGTH])
{
    UtalCanvasNode* node = UtalCanvasListGetFirst();
    if(node == NULL)
    {
        return;
    }
    
    do
    {
        if( strcmp(node->tag, tag) == 0 )
        {
            UtalCanvasListFreeResources(node);
            //si este nodo se apunta a si mismo la lista solo tiene un único elemento
            if( node->next == node )
            {
                __elementList = NULL;
                free(node);
                return;
            }
            else
            {
                node->prev->next = node->next;
                node->next->prev = node->prev;
                node->next = NULL;
                node->prev = NULL;
                free(node);
            }
            
        }
        node = node->next;
    }
    while( node != __elementList );
}

void UtalCanvasListRemoveAllElement()
{
    while( __elementList != NULL )
    {
        UtalCanvasListRemoveElementByIndex(__elementList->index);
    }
    
    __elementList = NULL;
}

void __UtalCanvasListMoveElement(UtalCanvasNode* node, int dx, int dy)
{
    if(node == NULL)
    {
        return;
    }
    
    UtalCanvasPoint* point;
    UtalCanvasLine* line;
    UtalCanvasRectangle* rectangle;
    UtalCanvasFilledRectangle* filledRectangle;
    UtalCanvasCircle* circle;
    UtalCanvasFilledCircle* filledCircle;
    UtalCanvasImage* image;
    UtalCanvasText* text;
    switch(node->type)
    {
        case UTALCANVAS_ELEMENT_POINT:
            
            point = (UtalCanvasPoint*)node->data;
            point->x += dx;
            point->y += dy;
            break;
        case UTALCANVAS_ELEMENT_LINE :
            line = (UtalCanvasLine*)node->data;
            line->x1 += dx;
            line->x2 += dx;
            line->y1 += dy;
            line->y2 += dy;
            break;
        case UTALCANVAS_ELEMENT_RECTANGLE :
            rectangle = (UtalCanvasRectangle*)node->data;
            rectangle->x1 += dx;
            rectangle->x2 += dx;
            rectangle->y1 += dy;
            rectangle->y2 += dy;
            break;
        case UTALCANVAS_ELEMENT_FILLED_RECTANGLE :
            filledRectangle = (UtalCanvasFilledRectangle*)node->data;
            filledRectangle->x1 += dx;
            filledRectangle->x2 += dx;
            filledRectangle->y1 += dy;
            filledRectangle->y2 += dy;
            break;
        case UTALCANVAS_ELEMENT_CIRCLE : 
            circle = (UtalCanvasCircle*)node->data;
            circle->x += dx;
            circle->y += dy;
            break;
        case UTALCANVAS_ELEMENT_FILLED_CIRCLE : 
            filledCircle = (UtalCanvasFilledCircle*)node->data;
            filledCircle->x += dx;
            filledCircle->y += dy;
            break;
        case UTALCANVAS_ELEMENT_IMAGE : 
            image = (UtalCanvasImage*)node->data;
            image->x += dx;
            image->y += dy;
            break;
        case UTALCANVAS_ELEMENT_TEXT : 
            text = (UtalCanvasText*)node->data;
            text->x += dx;
            text->y += dy;
            break;
    }
}

void UtalCanvasListMoveElementByIndex(int index, int dx, int dy)
{
    UtalCanvasNode* node = UtalCanvasListGetFirst();
    if(node == NULL)
    {
        return;
    }
    
    do
    {
        if( node->index == index )
        {
            __UtalCanvasListMoveElement(node, dx, dy);
            return;
        }
        node = node->next;
    }
    while( node != __elementList );
}

void UtalCanvasListMoveElementByTag(char tag[TAG_NAME_LENGTH], int dx, int dy)
{
    UtalCanvasNode* node = UtalCanvasListGetFirst();
    if(node == NULL)
    {
        return;
    }
    
    do
    {
        if( strcmp(node->tag, tag) == 0 )
        {
            __UtalCanvasListMoveElement(node, dx, dy);
        }
        node = node->next;
    }
    while( node != __elementList );
}

void UtalCanvasListFreeResources(UtalCanvasNode* node)
{
    UtalCanvasImage* image;
    UtalCanvasText* text;

    
    switch(node->type)
    {
        case UTALCANVAS_ELEMENT_IMAGE: 
            image = (UtalCanvasImage*)node->data;
            
            SDL_DestroyTexture( image->texture );
            free(image->size);
            
            image->texture = NULL;
            image->size = NULL;
            
            break;
        case UTALCANVAS_ELEMENT_TEXT: 
            text = (UtalCanvasText*)node->data;
            
            SDL_DestroyTexture( text->texture );
            SDL_FreeSurface( text->textSurface );
            TTF_CloseFont( text->font );
            
            text->texture = NULL;
            text->textSurface = NULL;
            text->font = NULL;
            
            break;
    }
    free(node->data);
}
