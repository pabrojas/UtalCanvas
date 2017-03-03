/** 
 * File:   utalcanvas_colors.h
 * Author: Pablo Ignacio Rojas Valdés (pabrojas@utalca.cl)
 * 
 * Created on 14 de junio de 2016
 */

#ifndef UTALCANVAS_COLORS_H
#define UTALCANVAS_COLORS_H

#include "definitions.h"
#include "structures.h"

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * Retorna una estructura que contiene el color en formato RGB asociado
     * al nombre proporcionado como parametro. Si el color no existe retorna
     * por defecto el color negro.
     * @param name nombre del color a obtener.
     * @return una estructura que contiene el color en formato RGB asociado
     *          al nombre proporcionado como parametro.
     */
    UtalCanvasColor get_color_by_name(char name[COLOR_NAME_LENGTH]);

#ifdef __cplusplus
}
#endif

#endif /* UTALCANVAS_COLORS_H */

