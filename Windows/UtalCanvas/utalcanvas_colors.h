/** 
 * File:   utalcanvas_colors.h
 * Author: Pablo Ignacio Rojas Valdés (pabrojas@utalca.cl)
 * 
 * Created on 14 de junio de 2016
 */

#ifndef UTALCANVAS_COLORS_H
#define UTALCANVAS_COLORS_H

#include "utalcanvas_definitions.h"
#include "utalcanvas_structures.h"

#ifdef __cplusplus
extern "C" {
#endif

    UtalCanvasColor UtalCanvasColorGetByName(char name[COLOR_NAME_LENGTH]);

#ifdef __cplusplus
}
#endif

#endif /* UTALCANVAS_COLORS_H */

