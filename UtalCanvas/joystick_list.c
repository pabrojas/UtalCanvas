
#include <stdbool.h>
#include <stdlib.h>

#include "joystick_list.h"
#include "structures.h"

JoystickNode* __joystick_root;

bool __joystick_list_exists( int which )
{
    if(__joystick_root == NULL)
    {
        return false;
    }
    
    JoystickNode* node = __joystick_root;
    do
    {
        if( node->which == which )
        {
            return true;
        }
        node = node->next;
    }
    while( node->next != __joystick_root );
    return false;
}

bool register_joystick(int which, JoystickData* jdata)
{
    if( __joystick_list_exists(which) )
    {
        return false;
    }
    
    //Creo el nuevo nodo
    JoystickNode* new_element = (JoystickNode*)malloc(sizeof(JoystickNode));
    new_element->next = NULL;
    new_element->prev = NULL;
    new_element->data = jdata;
    new_element->which = which;
    
    //si la lista esta vacia asigno el nuevo nodo como el inicio de la lista
    //cumpliendo las propiedades de la lista circular doblemente enlazada
    if( __joystick_root == NULL )
    {
        __joystick_root = new_element;
        __joystick_root->next = __joystick_root;
        __joystick_root->prev = __joystick_root;
        return true;
    }
    
    //en el caso que la lista no se encuentre vacia, dado que es una lista circular
    //accedo al ultimo elemento directamente y agrego el nuevo elemento a continuacion
    JoystickNode* last = __joystick_root->prev;
    new_element->next = __joystick_root;
    __joystick_root->prev = new_element;
    new_element->prev = last;
    last->next = new_element;
    
    return true;
    
    
}

JoystickData* get_joystick_data( int which)
{
    JoystickNode* node = __joystick_root;
    do
    {
        if( node->which == which )
        {
            return node->data;
        }
        node = node->next;
    }
    while( node->next != __joystick_root );
    return NULL;
}

JoystickNode* get_joystick(int which)
{
    JoystickNode* node = __joystick_root;
    do
    {
        if( node->which == which )
        {
            return node;
        }
        node = node->next;
    }
    while( node->next != __joystick_root );
    return NULL;
}

bool remove_joystick(int which)
{
    JoystickNode* node = __joystick_root;
    JoystickNode* root = __joystick_root;
    
    bool removed = false;
    
    if(node == NULL)
    {
        return false;
    }
    
    do
    {
        removed = false;
        
        if( node->which == which )
        {
            node = __remove_joystick_node(node);
            removed = true;
        }
        else
        { 
            node = node->next;
        }
    }
    while( removed == false && node != root );
    
    return removed;
}

JoystickNode* __remove_joystick_node(JoystickNode* node)
{
    JoystickNode* to_return;
            
    if( node == NULL )
    {
        return NULL;
    }
    
    bool isRoot = false;
    if( node == __joystick_root )
    {
        isRoot = true;
    }
    
    bool isAlone = false;
    if( node->next == node)
    {
        isAlone = true;
    }
    
    //lo usare solo en caso que el nodo a eliminar sea la raiz
    JoystickNode* new_root;
    
    if( isAlone )
    {
        to_return = NULL;
    }
    else
    {
        JoystickNode* previous = node->prev;
        JoystickNode* next = node->next;

        previous->next = next;
        next->prev = previous;
        
        to_return = next;
        new_root = next;
    }
    
    __free_joystick_node(node);
    free(node);
    
    if(isRoot)
    {
        if(isAlone)
        {
            __joystick_root = NULL;
        }
        else
        {
            __joystick_root = new_root;
        }
    }
    return to_return;
}

void __free_joystick_node(JoystickNode* node)
{
    JoystickData* data = node->data;
    free(data->axis);
    free(data->buttons);    
    if (SDL_JoystickGetAttached(data->joystick)) 
    {
        SDL_JoystickClose(data->joystick);
    }
    free(node->data);
}