
/** 
 * File:   utalcanvas_window.h
 * Author: Pablo Ignacio Rojas Valdes (pabrojas@utalca.cl)
 * 
 * Libreria de funciones utilitarias, usadas principalmente el window.h y 
 * element_list.h
 * 
 * Created on 13 de junio de 2016
 */

#ifndef UTALCANVAS_UTILS_H
#define UTALCANVAS_UTILS_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "structures.h"
#include "definitions.h"

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * Obtiene el tag del elemento data segun el tipo especificado y lo almacena en 
     * el parametro tag.
     * 
     * @param type tipo del elemento a obtener el tag.
     * @param data estructura asociada al tipo pasado como parametro.
     * @param tag etiqueta obtenida del elemento.
     */
    void get_element_tag(UtalCanvasElementType type, void* data, char tag[TAG_NAME_LENGTH]);
    
    /**
     * Retorna true si la etiqueta de elemento es valida, false de lo contrario.
     * Si el parametro tag es NULL o en la posicion 0 se encuentra el caracter de
     * fin de texto la etiqueta no sera valida.
     * 
     * @param tag etiqueta a consultar.
     * @return true si la etiqueta de elemento es valida, false de lo contrario.
     */
    bool is_valid_element_tag(char tag[TAG_NAME_LENGTH]);
    
    /**
     * Con los valores de los puntos (x1, y1) y (x2, y2) genera los puntos inferior-izquierdo
     * y superior-derecho de un rectnagulo y lo alamacena en el parametro UtalCanvasPlainRectangle.
     * 
     * @param rectangle estructura donde se almacenara el rectangulo generado.
     * @param x1 coordenada X del primer punto.
     * @param y1 coordenada Y del primer punto.
     * @param x2 coordenada X del segundo punto.
     * @param y2 coordenada Y del segundo punto.
     */
    void fix_rectangle( UtalCanvasPlainRectangle *rectangle, int x1, int y1, int x2, int y2 );    
    
    /**
     * Retorna true si la ruta del archivo existe, false de lo contrario.
     * 
     * @param filename ruta del archivo a verificar.
     * @return true si la ruta del archivo existe, false de lo contrario.
     */
    bool file_exists( const char* filename);
    
    /**
     * Retorna el valor expresado en coordendas de ventana resultante de convertir en el eje X el parametro world_value, 
     * expresado en coordenadas de mundo, a coordenadas de ventana.
     * 
     * @param worldValue valor de mundo a convertir.
     * @param window_dimension dimension de la ventana.
     * @param world_viewport coordenadas del area visible del mundo.
     * @return el valor expresado en coordendas de ventana resultante de convertir en el eje X el parametro world_value, 
     *          expresado en coordenadas de mundo, a coordenadas de ventana.
     */
    int convert_x_to_window_value(double world_value, UtalCanvasWindowDimension window_dimension, UtalCanvasWindowViewport world_viewport);
    
    /**
     * Retorna el valor expresado en coordendas de ventana resultante de convertir en el eje Y el parametro world_value, 
     * expresado en coordenadas de mundo, a coordenadas de ventana.
     * 
     * @param worldValue valor de mundo a convertir.
     * @param window_dimension dimension de la ventana.
     * @param world_viewport coordenadas del area visible del mundo.
     * @return el valor expresado en coordendas de ventana resultante de convertir en el eje Y el parametro world_value, 
     *          expresado en coordenadas de mundo, a coordenadas de ventana.
     */
    int convert_y_to_window_value(double world_value, UtalCanvasWindowDimension window_dimension, UtalCanvasWindowViewport world_viewport);
    
    /**
     * Retorna el valor expresado en coordendas de mundo resultante de convertir en el eje X el parametro window_value, 
     * expresado en coordenadas de ventana, a coordenadas de mundo.
     * 
     * @param window_value valor de ventana a convertir.
     * @param window_dimension dimension de la ventana.
     * @param world_viewportcoordenadas del area visible del mundo.
     * @return el valor expresado en coordendas de mundo resultante de convertir en el eje X el parametro window_value, 
     *          expresado en coordenadas de ventana, a coordenadas de mundo.
     */
    double convert_x_to_world_value(int window_value, UtalCanvasWindowDimension window_dimension, UtalCanvasWindowViewport world_viewport);
    
    /**
     * Retorna el valor expresado en coordendas de mundo resultante de convertir en el eje Y el parametro window_value, 
     * expresado en coordenadas de ventana, a coordenadas de mundo.
     * 
     * @param window_value valor de ventana a convertir.
     * @param window_dimension dimension de la ventana.
     * @param world_viewportcoordenadas del area visible del mundo.
     * @return el valor expresado en coordendas de mundo resultante de convertir en el eje Y el parametro window_value, 
     *          expresado en coordenadas de ventana, a coordenadas de mundo.
     */
    double convert_y_to_world_value(int window_value, UtalCanvasWindowDimension window_dimension, UtalCanvasWindowViewport world_viewport);



#ifdef __cplusplus
}
#endif

#endif /* UTALCANVAS_UTILS_H */

