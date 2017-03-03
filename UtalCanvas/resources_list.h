/* 
 * File:   resources_list.h
 * Author: Pablo Rojas Valdes (pabrojas@utalca.cl)
 * 
 * Lista enlazada de recursos de imagen, audio y archivos de fuentes. Estas
 * listas son circulares y doblemente enlazadas.
 *
 * Created on December 22, 2016
 */

#ifndef RESOURCES_LIST_H
#define RESOURCES_LIST_H

#include "definitions.h"
#include "structures.h"

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * Retorna true si la imagen con el nombre especificado se encuentra
     * registrada en la lista, false de lo contrario.
     * 
     * @param name nombre de la imagen a consutlar.
     * @return true si la imagen con el nombre especificado se encuentra
     *          registrada en la lista, false de lo contrario.
     */
    bool resource_list_image_exists( char name[TAG_NAME_LENGTH] );
    
    /**
     * Retorna el recurso de imagen almacenado con el nombre especificado.
     * 
     * @param name nombre del recurso de imagen a obtener.
     * @return el recurso de imagen almacenado con el nombre especificado.
     */
    ResourceImage* resource_list_get_image( char name[TAG_NAME_LENGTH] );
    
    /**
     * Retorna true si puede registar el recurso de imagen con el nombre proporcionado, 
     * false si ya se encuentra registrado un recurso con ese nombre.
     * 
     * @param name nombre del recurso de imagen a registrar.
     * @param data estructura del recurso de imagen a registrar.
     * @return true si puede registar el recurso de imagen con el nombre proporcionado, 
     *          false si ya se encuentra registrado un recurso con ese nombre.
     */
    bool resource_list_add_image( char name[TAG_NAME_LENGTH], ResourceImage* data );
    
    /**
     * Elimina un recurso de imagen de la lista.
     * 
     * @param name nombre del recurso de imagen a eliminar.
     */
    void resource_list_remove_image( char name[TAG_NAME_LENGTH] );
    
    /**
     * Retorna true si el audio con el nombre especificado se encuentra
     * registrado en la lista, false de lo contrario.
     * 
     * @param name nombre del audio a consutlar.
     * @return true si el audio con el nombre especificado se encuentra
     *          registrada en la lista, false de lo contrario.
     */
    bool resource_list_audio_exists( char name[TAG_NAME_LENGTH] );
    
    /**
     * Retorna el recurso de audio almacenado con el nombre especificado.
     * 
     * @param name nombre del recurso de audio a obtener.
     * @return el recurso de audio almacenado con el nombre especificado.
     */
    ResourceAudio* resource_list_get_audio( char name[TAG_NAME_LENGTH] );
    
    /**
     * Retorna true si puede registar el recurso de audio con el nombre proporcionado, 
     * false si ya se encuentra registrado un recurso con ese nombre.
     * 
     * @param name nombre del recurso de audio a registrar.
     * @param data estructura del recurso de audio a registrar.
     * @return true si puede registar el recurso de audio con el nombre proporcionado, 
     *          false si ya se encuentra registrado un recurso con ese nombre.
     */
    bool resource_list_add_audio( char name[TAG_NAME_LENGTH], ResourceAudio* data );
    
    /**
     * Elimina un recurso de audio de la lista.
     * 
     * @param name nombre del recurso de audio a eliminar.
     */
    void resource_list_remove_audio( char name[TAG_NAME_LENGTH] );
    
    /**
     * Retorna true si el archivo de fuentes con el nombre especificado se encuentra
     * registrado en la lista, false de lo contrario.
     * 
     * @param name nombre del archivo de fuentes a consutlar.
     * @return true si el archivo de fuentes con el nombre especificado se encuentra
     *          registrada en la lista, false de lo contrario.
     */
    bool resource_list_font_exists( char name[TAG_NAME_LENGTH] );
    
    /**
     * Retorna el recurso de audio almacenado con el nombre especificado.
     * 
     * @param name nombre del recurso de audio a obtener.
     * @return el recurso de audio almacenado con el nombre especificado.
     */
    ResourceFont* resource_list_get_font( char name[TAG_NAME_LENGTH] );
    
    /**
     * Retorna true si puede registar el recurso de archivo de fuentes con el nombre proporcionado, 
     * false si ya se encuentra registrado un recurso con ese nombre.
     * 
     * @param name nombre del recurso de archivo de fuentes a registrar.
     * @param data estructura del recurso de archivo de fuentes a registrar.
     * @return true si puede registar el recurso de archivo de fuentes con el nombre proporcionado, 
     *          false si ya se encuentra registrado un recurso con ese nombre.
     */
    bool resource_list_add_font( char name[TAG_NAME_LENGTH], ResourceFont* data );
    
    /**
     * Elimina un recurso de archivo de fuentes de la lista.
     * 
     * @param name nombre del recurso de archivo de fuentes a eliminar.
     */
    void resource_list_remove_font( char name[TAG_NAME_LENGTH] );
    
    /**
     * Retorna true si el recurso con el nombre especificado se encuentra en la 
     * lista con la raiz especificada, false de lo contrario.
     * 
     * FUNCION DE USO INTERNO.
     * 
     * @param root raiz de la lista donde se buscara el recurso.
     * @param name nombre del recurso a buscar.
     * @return true si el recurso con el nombre especificado se encuentra en la 
     *          lista con la raiz especificada, false de lo contrario.
     */
    bool __resource_exists( ResourceNode* root, char name[TAG_NAME_LENGTH] );
    
    /**
     * Retorna true si el recurso con el nombre especificado pertence a la lista
     * asociada al tipo especificado, false de lo contrario.
     * 
     * Para cada uno de los tipos definidos en el tipo enumerado ResourceType existe
     * un nodo raiz para su propia lista.
     * 
     * FUNCION DE USO INTERNO.
     * 
     * @param type tipo de recurso a consultar en su propia lista.
     * @param name nombre del recurso a consultar.
     * @return true si el recurso con el nombre especificado pertence a la lista
     *          asociada al tipo especificado, false de lo contrario.
     */
    bool __resource_list_exists( ResourceType type, char name[TAG_NAME_LENGTH] );
    
    /**
     * Retorna true si el recurso especificado en el parametro data puede ser agregado
     * a la lista asociada al tipo especificado con el nombre especificado, false 
     * de lo contrario.
     * 
     * FUNCION DE USO INTERNO.
     * 
     * @param type tipo de recurso a agregar a su propia lista.
     * @param data recurso a agregar.
     * @param name nombre del recurso.
     * @return true si el recurso especificado en el parametro data puede ser agregado
     *          a la lista asociada al tipo especificado con el nombre especificado, 
     *          false de lo contrario.
     */
    bool __resource_list_add( ResourceType type, void* data, char name[TAG_NAME_LENGTH]);
    
    /**
     * Elimina el recurso con el nombre especificado de la lista asociada al tipo.
     * 
     * FUNCION DE USO INTERNO.
     * 
     * @param type tipo de recurso a eliminar de su lista asociada.
     * @param name nombre del recurso a eliminar.
     */
    void __remove_resource(ResourceType type, char name[TAG_NAME_LENGTH]);
    
    /**
     * Retorna el nodo siguiente al nodo especificado o NULL si la lista
     * asociada al tipo resulta quedar vacia posterior a la eliminacion.
     * 
     * FUNCION DE USO INTERNO.
     * 
     * @param type tipo de nodo a eliminar.
     * @param node nodo a eliminar.
     * @return el nodo siguiente al nodo especificado o NULL si la lista
     *          asociada al tipo resulta quedar vacia posterior a la eliminacion.
     */
    ResourceNode* __remove_resource_node(ResourceType type, ResourceNode* node);
    
    /**
     * Libera los recursos asociados al nodo, para cada uno de los tipos de nodos
     * definidos.
     * 
     * FUNCION DE USO INTERNO.
     * 
     * @param node nodo al cual se liberaran sus recursos.
     */
    void __free_resources_node(ResourceNode* node);
    
    /**
     * Retorna el nodo de recursos aociado al nombre en la lista asociada al 
     * tipo especificado.
     * 
     * FUNCION DE USO INTERNO.
     * 
     * @param type tipo de recurso en el que se buscara en su lista asociada.
     * @param name nombre del recurso a buscar.
     * @return el nodo de recursos aociado al nombre en la lista asociada al 
     *          tipo especificado.
     */
    ResourceNode* __get_resource(ResourceType type, char name[TAG_NAME_LENGTH]);


#ifdef __cplusplus
}
#endif

#endif /* RESOURCES_LIST_H */

