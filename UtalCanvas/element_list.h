
/** 
 * File:   resources_list.h
 * Author: Pablo Ignacio Rojas Valdes (pabrojas@utalca.cl)
 * 
 * Contiene todas las funciones para almacenar los elementos
 * graficos de la libreria UtalCanvas. Todos los elementos
 * son almacenados en una lista doblemente enlazada y circular.
 * 
 * Utiliza como nodo a la estructura UtalCanvasNode. Para diferenciar y almacenar
 * los distintos tipos de elementos se utilizan los siguientes valores enumerados
 * provenienetes de UtalCanvasElementType. La correspondencia entre los valores 
 * enumerados y las estructuras para cada tipo es:
 * 
 *          +---------------------------+-----------------------------+
 *          | Tipo                      |   Estructura                |
 *          |---------------------------+-----------------------------+
 *          | ELEMENT_POINT             |   ElementPoint              |
 *          | ELEMENT_LINE              |   ElementLine               |
 *          | ELEMENT_CIRCLE            |   ElementCircle             |
 *          | ELEMENT_FILLED_CIRCLE     |   ElementFilledCircle       |
 *          | ELEMENT_RECTANGLE         |   ElementRectangle          |
 *          | ELEMENT_FILLED_RECTANGLE  |   ElementFilledRectangle    |
 *          | ELEMENT_TEXT              |   ElementText               |
 *          | ELEMENT_IMAGE             |   ElementImage              |
 *          +---------------------------+-----------------------------+
 * 
 * Todas las definiciones de los tipos enumerados y estrucutras se encuentran en 
 * definitions.h.
 * 
 * Created on 13 de junio de 2016
 */

#ifndef UTALCANVAS_LIST_H
#define UTALCANVAS_LIST_H

#include "definitions.h"
#include "structures.h"

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * Retorna el indice del nuevo elemento agregado a la lista.
     * Dependiendo del tipo (especificado en structures.h) realiza una conversion
     * explicita del parametro data para obtner su tag. Luego agrega este elemento
     * al final de la lista, le asigna su indice y se lo retorna. Esta es una 
     * lista doblemente enlazada y circular.
     * 
     * @param type tipo de elemento a agregar.
     * @param data estructura correspondiente al tipo especificado.
     * @return indice del nuevo elemento agregado.
     */
    int element_list_add( UtalCanvasElementType type, void* data );
    
    /**
     * Elimina al elemento asociado al indice pasado como paramtro y libera todos
     * sus recursos asociados.
     * 
     * @param index indice del elemento a eliminar.
     */
    void element_list_remove_by_index(int index);
    
    /**
     * Elimina todos los elementos de la lista que contengan la etiqueta pasada 
     * como parametro y librera todos sus recursos.
     * 
     * @param tag etiqueta de los elementos a eliminar.
     */
    void element_list_remove_by_tag(char tag[TAG_NAME_LENGTH]);
    
    /**
     * Elimina todos los elementos de la lista y libera todos sus recursos.
     */
    void element_list_remove_all();
    
    /**
     * Mueve el elemento que conenga el indice especificado como parametro dx en
     * el eje  x y dy en el eje y.
     * 
     * @param index indice del elemento a mover.
     * @param dx cantidad a mover en el eje x.
     * @param dy cantidad a mover en el eje y.
     */
    void element_list_move_by_index(int index, double dx, double dy);
    
    /**
     * Mueve los elementos que conengan la etiqueta especificada como parametro 
     * dx en el eje  x y dy en el eje y.
     * 
     * @param tag etiqueta de los elememtos a mover.
     * @param dx cantidad a mover en el eje x.
     * @param dy cantidad a mover en el eje y.
     */
    void element_list_move_by_tag(char tag[TAG_NAME_LENGTH], double dx, double dy);
    
    /**
     * Libera los recursos del elemento que almacena dicho nodo, no libera el nodo, 
     * sino solo los elementos.
     * 
     * Para hacer esta eliminacion, se consulta por el tipo de elemento almacenado, 
     * se realiza la conversion explicita y luego se liberan sus recursos.
     * 
     * FUNCION DE USO INTERNO.
     * 
     * @param node nodo a liberar sus recursos.
     */
    void __free_resources(UtalCanvasNode* node);
    
    /**
     * Retorna el primer elemento de la lista enlazda.
     * 
     * FUNCION DE USO INTERNO.
     * 
     * @return el primer elemento de la lista enlazada.
     */
    UtalCanvasNode* __get_root();

#ifdef __cplusplus
}
#endif

#endif /* UTALCANVAS_LIST_H */

