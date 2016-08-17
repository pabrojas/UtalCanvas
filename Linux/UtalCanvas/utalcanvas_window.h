
/** 
 * File:   utalcanvas_window.h
 * Author: Pablo Ignacio Rojas Valdés (pabrojas@utalca.cl)
 * 
 * Created on 13 de junio de 2016
 */

#ifndef UTALCANVASWINDOW_H
#define UTALCANVASWINDOW_H


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utalcanvas_structures.h"
#include "utalcanvas_definitions.h"
#include "utalcanvas.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    bool UtalCanvasWindowInitialize();
    void UtalCanvasWindowClose();
    void UtalCanvasWindowLoop();
    void UtalCanvasWindowStart();
    void UtalCanvasWindowSetSize(int width, int height);
    void UtalCanvasWindowSetViewport(int xMin, int yMin, int xUp, int yUp);
    void UtalCanvasWindowSetTitle(char title[MAX_TEXT_LENGTH]);
    void UtalCanvasWindowSetBackground(char background[COLOR_NAME_LENGTH]);
    bool UtalCanvasWindowIsClosed();
    
    void UtalCanvasWindowDrawPoint(void* data);
    void UtalCanvasWindowDrawLine(void* data);
    void UtalCanvasWindowDrawRectangle(char* data);
    void UtalCanvasWindowDrawFilledRectangle(char* data);
    void UtalCanvasWindowDrawCircle(char* data);
    void UtalCanvasWindowDrawFilledCircle(void* data);
    void UtalCanvasWindowDrawImage(void* data);
    
    int UtalCanvasWindowAddElement(UtalCanvasElementType type, void* data);
    void UtalCanvasWindowRemoveElementByIndex(int index);
    void UtalCanvasWindowRemoveElementByTag(char tag[TAG_NAME_LENGTH]);
    void UtalCanvasWindowMoveElementByIndex(int index, int dx, int dy);
    void UtalCanvasWindowMoveElementByTag(char tag[TAG_NAME_LENGTH], int dx, int dy);
    
    UtalCanvasKey UtalCanvasWindowGetPressedKey();
    UtalCanvasWindowMouseInfo UtalCanvasWindowGetMouseInfo();
    
    void __UtalCanvasWindowDrawEllipse(UtalCanvasCircle* circle);
    void __UtalCanvasWindowFillEllipse(UtalCanvasFilledCircle* circle);
    

#ifdef __cplusplus
}
#endif

#endif /* UTALCANVASWINDOW_H */

