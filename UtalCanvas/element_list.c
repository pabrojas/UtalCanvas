#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "element_list.h"
#include "structures.h"
#include "definitions.h"
#include "utils.h"

int __elementIndex = 0;
UtalCanvasNode* __root = NULL;

char __no_tag[TAG_NAME_LENGTH] = "[[UtalCanvasNoTag-3906551015]]";

UtalCanvasNode* __get_root()
{
    return __root;
}

int element_list_add(UtalCanvasElementType type, void* data)
{
    UtalCanvasNode* last;
            
    //Aumento el nuevo indice de los elementos
    __elementIndex++;
    
    //Creo el nuevo nodo y asigno todos los datos basicos
    UtalCanvasNode* new_element = (UtalCanvasNode*)malloc(sizeof(UtalCanvasNode));
    new_element->next = NULL;
    new_element->prev = NULL;
    new_element->type = type;
    new_element->index = __elementIndex;
    new_element->data = data;
    
    //asigno el tag al nodo
    char tag[TAG_NAME_LENGTH];
    get_element_tag(type, data, tag);
    if(is_valid_element_tag(tag))
    {
        strncpy(new_element->tag, tag, TAG_NAME_LENGTH);
    }
    else
    {
        strncpy(new_element->tag, __no_tag, TAG_NAME_LENGTH);
    }
    
    
    
    //si la lista esta vacia asigno elnuevo nodo como el inicio de la lista
    //cumpliendo las propiedades de la lista circular doblemente enlazada
    if( __root == NULL )
    {
        __root = new_element;
        __root->next = __root;
        __root->prev = __root;
    }
    //en el caso que la lista no se encuentre vacia, dado que es una lista circular
    //accedo al ultimo elemento directamente y agrego el nuevo elemento a continuacion
    else
    {
        last = __root->prev;
        new_element->next = __root;
        __root->prev = new_element;
        new_element->prev = last;
        last->next = new_element;
    }

    return new_element->index;
}

UtalCanvasNode* __remove_node(UtalCanvasNode* node)
{
    UtalCanvasNode* to_return;
            
    if( node == NULL )
    {
        return NULL;
    }
    
    bool isRoot = false;
    if( node == __root )
    {
        isRoot = true;
    }
    
    bool isAlone = false;
    if( node->next == node)
    {
        isAlone = true;
    }
    
    //lo usare solo en caso que el nodo a eliminar sea la raiz
    UtalCanvasNode* new_root = node->next;
    
    if( isAlone )
    {
        to_return = NULL;
    }
    else
    {
        UtalCanvasNode* previous = node->prev;
        UtalCanvasNode* next = node->next;

        previous->next = next;
        next->prev = previous;
        
        to_return = next;
    }
    
    __free_resources(node);
    free(node);
    
    if(isRoot)
    {
        if(isAlone)
        {
            __root = NULL;
        }
        else
        {
            __root = new_root;
        }
    }
    
    return to_return;
    
    
    
}


void element_list_remove_by_index(int index)
{
    UtalCanvasNode* node = __get_root();
    if(node == NULL)
    {
        return;
    }
    
    do
    {
        if( node->index == index )
        {
            __remove_node(node);
            return;
        }
        node = node->next;
    }
    while( node != __root );
}

void element_list_remove_by_tag(char tag[TAG_NAME_LENGTH])
{
    UtalCanvasNode* node = __get_root();
    bool removed = false;
    
    if(node == NULL)
    {
        return;
    }
    
    do
    {
        removed = false;
        
        if( strcmp(node->tag, tag) == 0 )
        {
            node = __remove_node(node);
            removed = true;
        }
        else
        { 
            node = node->next;
        }
    }
    while( (removed == true && node != NULL) || (removed == false && node != __root) );
}

void element_list_remove_all()
{
    while( __root != NULL )
    {
        element_list_remove_by_index(__root->index);
    }
    
    __root = NULL;
}

void __UtalCanvasListMoveElement(UtalCanvasNode* node, double dx, double dy)
{
    if(node == NULL)
    {
        return;
    }
    
    ElementPoint* point;
    ElementLine* line;
    ElementRectangle* rectangle;
    ElementFilledRectangle* filledRectangle;
    ElementCircle* circle;
    ElementFilledCircle* filledCircle;
    ElementImage* image;
    ElementText* text;
    switch(node->type)
    {
        case ELEMENT_POINT:
            
            point = (ElementPoint*)node->data;
            point->x += dx;
            point->y += dy;
            break;
        case ELEMENT_LINE :
            line = (ElementLine*)node->data;
            line->x1 += dx;
            line->x2 += dx;
            line->y1 += dy;
            line->y2 += dy;
            break;
        case ELEMENT_RECTANGLE :
            rectangle = (ElementRectangle*)node->data;
            rectangle->x1 += dx;
            rectangle->x2 += dx;
            rectangle->y1 += dy;
            rectangle->y2 += dy;
            break;
        case ELEMENT_FILLED_RECTANGLE :
            filledRectangle = (ElementFilledRectangle*)node->data;
            filledRectangle->x1 += dx;
            filledRectangle->x2 += dx;
            filledRectangle->y1 += dy;
            filledRectangle->y2 += dy;
            break;
        case ELEMENT_CIRCLE : 
            circle = (ElementCircle*)node->data;
            circle->x += dx;
            circle->y += dy;
            break;
        case ELEMENT_FILLED_CIRCLE : 
            filledCircle = (ElementFilledCircle*)node->data;
            filledCircle->x += dx;
            filledCircle->y += dy;
            break;
        case ELEMENT_IMAGE : 
            image = (ElementImage*)node->data;
            image->x += dx;
            image->y += dy;
            break;
        case ELEMENT_TEXT : 
            text = (ElementText*)node->data;
            text->x += dx;
            text->y += dy;
            break;
    }
}

void element_list_move_by_index(int index, double dx, double dy)
{
    UtalCanvasNode* node = __get_root();
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
    while( node != __root );
}

void element_list_move_by_tag(char tag[TAG_NAME_LENGTH], double dx, double dy)
{
    UtalCanvasNode* node = __get_root();
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
    while( node != __root );
}

void __free_resources(UtalCanvasNode* node)
{
    ElementImage* image;
    ElementText* text;

    switch(node->type)
    {
        case ELEMENT_IMAGE: 
            image = (ElementImage*)node->data;
            
            SDL_DestroyTexture( image->texture );
            free(image->size);
            
            image->texture = NULL;
            image->size = NULL;
            
            break;
        case ELEMENT_TEXT: 
            text = (ElementText*)node->data;
            
            SDL_DestroyTexture( text->texture );
            SDL_FreeSurface( text->textSurface );
            TTF_CloseFont( text->font );
            
            text->texture = NULL;
            text->textSurface = NULL;
            text->font = NULL;
    
            break;
            
        case ELEMENT_POINT : break;
        case ELEMENT_LINE : break;
        case ELEMENT_CIRCLE : break;
        case ELEMENT_FILLED_CIRCLE : break;
        case ELEMENT_RECTANGLE : break;
        case ELEMENT_FILLED_RECTANGLE : break;
        
    }
    free(node->data);
}
