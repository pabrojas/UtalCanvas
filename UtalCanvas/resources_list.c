#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "element_list.h"
#include "structures.h"
#include "definitions.h"
#include "utils.h"
#include "resources_list.h"

ResourceNode* __images_root;
ResourceNode* __audios_root;
ResourceNode* __fonts_root;

/*
 * Metodos para los recursos de tipo RESOURCE_IMAGE
 */
bool resource_list_image_exists( char name[TAG_NAME_LENGTH] )
{
    return __resource_list_exists(RESOURCE_IMAGE, name);
}

ResourceImage* resource_list_get_image( char name[TAG_NAME_LENGTH] )
{
    ResourceNode* node = __get_resource(RESOURCE_IMAGE, name);
    if( node == NULL )
    {
        return NULL;
    }
    return (ResourceImage*)node->data;
}

bool resource_list_add_image( char name[TAG_NAME_LENGTH], ResourceImage* data )
{
    return __resource_list_add(RESOURCE_IMAGE, data, name);
}

void resource_list_remove_image( char name[TAG_NAME_LENGTH] )
{
    __remove_resource(RESOURCE_IMAGE, name);
}

/*
 * Metodos para los recursos de tipo RESOURCE_AUDIO
 */
bool resource_list_audio_exists( char name[TAG_NAME_LENGTH] )
{
    return __resource_list_exists(RESOURCE_AUDIO, name);
}

ResourceAudio* resource_list_get_audio( char name[TAG_NAME_LENGTH] )
{
    ResourceNode* node = __get_resource(RESOURCE_AUDIO, name);
    if( node == NULL )
    {
        return NULL;
    }
    return (ResourceAudio*)node->data;
}

bool resource_list_add_audio( char name[TAG_NAME_LENGTH], ResourceAudio* data )
{
    return  __resource_list_add(RESOURCE_AUDIO, data, name);
}

void resource_list_remove_audio( char name[TAG_NAME_LENGTH] )
{
    __remove_resource(RESOURCE_AUDIO, name);
}

/*
 * Metodos para los recursos de tipo RESOURCE_FONT
 */
bool resource_list_font_exists( char name[TAG_NAME_LENGTH] )
{
    return __resource_list_exists(RESOURCE_FONT, name);
}

ResourceFont* resource_list_get_font( char name[TAG_NAME_LENGTH] )
{
    ResourceNode* node = __get_resource(RESOURCE_FONT, name);
    if( node == NULL )
    {
        return NULL;
    }
    return (ResourceFont*)node->data;
}

bool resource_list_add_font( char name[TAG_NAME_LENGTH], ResourceFont* data )
{
    return __resource_list_add(RESOURCE_FONT, data, name);
}

void resource_list_remove_font( char name[TAG_NAME_LENGTH] )
{
    __remove_resource(RESOURCE_FONT, name);
}



/*
 * Metodos genericos de las listas
 */

bool __resource_exists( ResourceNode* root, char name[TAG_NAME_LENGTH] )
{
    if(root == NULL)
    {
        return false;
    }
    
    ResourceNode* node = root;
    do
    {
        if( strcmp(node->name, name) == 0 )
        {
            return true;
        }
        node = node->next;
    }
    while( node->next != root );
    return false;
}

bool __resource_list_exists( ResourceType type, char name[TAG_NAME_LENGTH] )
{
    if( type == RESOURCE_IMAGE )
    {
        return __resource_exists(__images_root, name);
    }
    else if( type == RESOURCE_IMAGE )
    {
        return __resource_exists(__audios_root, name);
    }
    else if( type == RESOURCE_FONT )
    {
        return __resource_exists(__fonts_root, name);
    }
    
    return false;
}

bool __resource_list_add( ResourceType type, void* data, char name[TAG_NAME_LENGTH])
{
    
    ResourceNode* root;
    if( type == RESOURCE_IMAGE )
    {
        root = __images_root;
    }
    else if( type == RESOURCE_AUDIO )
    {
        root = __audios_root;
    }
    else if( type == RESOURCE_FONT )
    {
        root = __fonts_root;
    }
    else
    {
        return false;
    }
    
    if( __resource_exists(root, name) )
    {
        return false;
    }
    
    //Creo el nuevo nodo y asigno todos los datos basicos
    ResourceNode* new_element = (ResourceNode*)malloc(sizeof(ResourceNode));
    new_element->next = NULL;
    new_element->prev = NULL;
    new_element->type = type;
    new_element->data = data;
    strncpy(new_element->name, name, TAG_NAME_LENGTH);
    
    
    //si la lista esta vacia asigno elnuevo nodo como el inicio de la lista
    //cumpliendo las propiedades de la lista circular doblemente enlazada
    if( type == RESOURCE_IMAGE && __images_root == NULL )
    {
        __images_root = new_element;
        __images_root->next = __images_root;
        __images_root->prev = __images_root;
        return true;
    }
    if( type == RESOURCE_AUDIO && __audios_root == NULL )
    {
        __audios_root = new_element;
        __audios_root->next = __audios_root;
        __audios_root->prev = __audios_root;
        return true;
    }
    if( type == RESOURCE_FONT && __fonts_root == NULL )
    {
        __fonts_root = new_element;
        __fonts_root->next = __fonts_root;
        __fonts_root->prev = __fonts_root;
        return true;
    }
    
    
    //en el caso que la lista no se encuentre vacia, dado que es una lista circular
    //accedo al ultimo elemento directamente y agrego el nuevo elemento a continuacion
    ResourceNode* last = root->prev;
    new_element->next = root;
    root->prev = new_element;
    new_element->prev = last;
    last->next = new_element;
    

    return true;
}

void __remove_resource(ResourceType type, char name[TAG_NAME_LENGTH])
{
    ResourceNode* node;
    ResourceNode* root;
    if( type == RESOURCE_IMAGE )
    {
        node = __images_root;
        root = __images_root;
    }
    else if( type == RESOURCE_AUDIO )
    {
        node = __audios_root;
        root = __audios_root;
    }
    else if( type == RESOURCE_FONT )
    {
        node = __fonts_root;
        root = __fonts_root;
    }
    else
    {
        return;
    }
    
    bool removed = false;
    
    if(node == NULL)
    {
        return;
    }
    
    do
    {
        removed = false;
        
        if( strcmp(node->name, name) == 0 )
        {
            node = __remove_resource_node(type, node);
            removed = true;
        }
        else
        { 
            node = node->next;
        }
    }
    while( removed == false && node != root );
}

ResourceNode* __remove_resource_node(ResourceType type, ResourceNode* node)
{
    ResourceNode* to_return;
            
    if( node == NULL )
    {
        return NULL;
    }
    
    bool isRoot = false;
    if( (type == RESOURCE_IMAGE && node == __images_root) || (type == RESOURCE_AUDIO && node == __audios_root) || (type == RESOURCE_FONT && node == __fonts_root) )
    {
        isRoot = true;
    }
    
    bool isAlone = false;
    if( node->next == node)
    {
        isAlone = true;
    }
    
    //lo usare solo en caso que el nodo a eliminar sea la raiz
    ResourceNode* new_root;
    
    if( isAlone )
    {
        to_return = NULL;
    }
    else
    {
        ResourceNode* previous = node->prev;
        ResourceNode* next = node->next;

        previous->next = next;
        next->prev = previous;
        
        to_return = next;
        new_root = next;
    }
    
    __free_resources_node(node);
    free(node);
    
    if(isRoot)
    {
        if(isAlone)
        {
            if( type == RESOURCE_IMAGE )
            {
                __images_root = NULL;
            }
            else if( type == RESOURCE_AUDIO )
            {
                __audios_root = NULL;
            }
            else if( type == RESOURCE_FONT )
            {
                __fonts_root = NULL;
            }
        }
        else
        {
            if( type == RESOURCE_IMAGE )
            {
                __images_root = new_root;
            }
            else if( type == RESOURCE_AUDIO )
            {
                __audios_root = new_root;
            }
            else if( type == RESOURCE_FONT )
            {
                __fonts_root = new_root;
            }
        }
    }
    return to_return;
}


void __free_resources_node(ResourceNode* node)
{
    ResourceImage* image;
    ResourceAudio* sound;
    ResourceFont* font;

    switch(node->type)
    {
        case RESOURCE_IMAGE: 
            image = (ResourceImage*)node->data;
            SDL_DestroyTexture( image->texture );
            image->texture = NULL;
            
            break;
        case RESOURCE_AUDIO:
            sound = (ResourceAudio*)node->data;
            Mix_FreeChunk(sound->chunk);
            break;
        case RESOURCE_FONT:
            font = (ResourceFont*)node->data;
            TTF_CloseFont( font->font );
            break;
    }
    
    free(node->data);
}


ResourceNode* __get_resource(ResourceType type, char name[TAG_NAME_LENGTH])
{
    ResourceNode* root;
    if( type == RESOURCE_AUDIO )
    {
        root = __audios_root;
    }
    else if( type == RESOURCE_IMAGE )
    {
        root = __images_root;
    }
    else if( type == RESOURCE_FONT )
    {
        root = __fonts_root;
    }
    else
    {
        return NULL;
    }
    
    if( root == NULL )
    {
        return NULL;
    }
    
    ResourceNode* node = root;
    do
    {
        if( strcmp(node->name, name) == 0 )
        {
            return node;
        }
        node = node->next;
    }
    while(node != root);
    
    return NULL;
    
}
