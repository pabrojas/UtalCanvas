
/** 
 * File:   utalcanvas_window.h
 * Author: Pablo Ignacio Rojas Valdés (pabrojas@utalca.cl)
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

#include "utalcanvas_structures.h"
#include "utalcanvas_definitions.h"

#ifdef __cplusplus
extern "C" {
#endif

    void UtalCanvasUtilsGetTag(UtalCanvasElementType type, void* data, char tag[TAG_NAME_LENGTH]);
    bool UtalCanvasUtilsIsValidTag(char tag[TAG_NAME_LENGTH]);
    void UtalCanvasUtilsFixRectangle( UtalCanvasPlainRectangle *rectangle, int x1, int y1, int x2, int y2 );    
    
    void delay(double delay_seconds);


#ifdef __cplusplus
}
#endif

#endif /* UTALCANVAS_UTILS_H */

