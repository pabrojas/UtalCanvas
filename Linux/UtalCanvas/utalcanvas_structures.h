
/** 
 * File:   utalcanvas_structures.h
 * Author: Pablo Ignacio Rojas Valdés (pabrojas@utalca.cl)
 * 
 * Created on 13 de junio de 2016
 */

#ifndef UTALCANVAS_STRUCTURES_H
#define UTALCANVAS_STRUCTURES_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include<SDL_mixer.h>

#include "utalcanvas_definitions.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef enum UtalCanvasElementType
    {
        UTALCANVAS_ELEMENT_POINT,
        UTALCANVAS_ELEMENT_LINE,
        UTALCANVAS_ELEMENT_CIRCLE,
        UTALCANVAS_ELEMENT_FILLED_CIRCLE,
        UTALCANVAS_ELEMENT_RECTANGLE,
        UTALCANVAS_ELEMENT_FILLED_RECTANGLE,
        UTALCANVAS_ELEMENT_TEXT,
        UTALCANVAS_ELEMENT_IMAGE,
        UTALCANVAS_ELEMENT_SOUND
    } UtalCanvasElementType;
    
    typedef struct UtalCanvasColor
    {
        int red;
        int green;
        int blue;
    } UtalCanvasColor;

    typedef struct UtalCanvasPoint
    {
        int x;
        int y;
        UtalCanvasColor color;
        char tag[TAG_NAME_LENGTH];
    } UtalCanvasPoint;

    typedef struct UtalCanvasLine
    {
        int x1;
        int y1;
        int x2;
        int y2;
        UtalCanvasColor color;
        char tag[TAG_NAME_LENGTH];
    } UtalCanvasLine;

    typedef struct UtalCanvasCircle
    {
        int x;
        int y;
        int radio;
        UtalCanvasColor color;
        char tag[TAG_NAME_LENGTH];
    } UtalCanvasCircle;

    typedef struct UtalCanvasFilledCircle
    {
        int x;
        int y;
        int radio;
        UtalCanvasColor outerColor;
        UtalCanvasColor fillColor;
        char tag[TAG_NAME_LENGTH];
    } UtalCanvasFilledCircle;

    typedef struct UtalCanvasRectangle
    {
        int x1;
        int y1;
        int x2;
        int y2;
        UtalCanvasColor color;
        char tag[TAG_NAME_LENGTH];
    } UtalCanvasRectangle;
    
    
    typedef struct UtalCanvasSound{
    
        char filename[PATHNAME_LENGTH];
        char tag[TAG_NAME_LENGTH];
        Mix_Chunk* _sample;
    
    }UtalCanvasSound;
    

    typedef struct UtalCanvasFilledRectangle
    {
        int x1;
        int y1;
        int x2;
        int y2;
        UtalCanvasColor outerColor;
        UtalCanvasColor fillColor;
        char tag[TAG_NAME_LENGTH];
    } UtalCanvasFilledRectangle;
    
    typedef struct UtalCanvasImage
    {
        int x;
        int y;
        int width;
        int height;
        char filename[PATHNAME_LENGTH];
        SDL_Texture* texture;
        SDL_Rect* size;
        char tag[TAG_NAME_LENGTH];
    } UtalCanvasImage;
    
    typedef struct UtalCanvasText
    {
        char fontFile[PATHNAME_LENGTH];
        int x;
        int y;
        char text[MAX_TEXT_LENGTH];
        int size;
        UtalCanvasColor color;
        char tag[TAG_NAME_LENGTH];
        TTF_Font *font;
        SDL_Surface* textSurface;
        SDL_Texture* texture;
        int data;
    } UtalCanvasText;
    
    typedef struct UtalCanvasWindowMouseInfo
    {
        int x;
        int y;
        int button;
    } UtalCanvasWindowMouseInfo;
    
    

    typedef struct UtalCanvasNode
    {
        void* data;
        UtalCanvasElementType type;
        int index;
        char tag[TAG_NAME_LENGTH];
        struct UtalCanvasNode *next;
        struct UtalCanvasNode *prev;
    } UtalCanvasNode;

    typedef struct UtalCanvasPlainRectangle
    {
        int x;
        int y;
        int width;
        int height;
    } UtalCanvasPlainRectangle;
    
    typedef struct UtalCanvasWindowViewport
    {
        int xMin;
        int yMin;
        int xMax;
        int yMax;
        
    } UtalCanvasWindowViewport ;
    
    typedef struct UtalCanvasWindowDimension
    {
        int width;
        int height;
        
    } UtalCanvasWindowDimension ;


#ifdef __cplusplus
}
#endif

#endif /* UTALCANVAS_STRUCTURES_H */

