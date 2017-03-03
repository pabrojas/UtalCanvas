
/** 
 * File:   structures.h
 * Author: Pablo Ignacio Rojas Valdes (pabrojas@utalca.cl)
 * Contributor: Felipe Andres Besoain Pino (fbesoain@utalca.cl)
 * 
 * Contiene todas las estructuras y tipos enumerados para toda la libreria 
 * UtalCanvas.
 * 
 * Created on 13 de junio de 2016
 */

#ifndef UTALCANVAS_STRUCTURES_H
#define UTALCANVAS_STRUCTURES_H

#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "definitions.h"

#ifdef __cplusplus
extern "C" {
#endif

    //Tipos de elementos graficos a ser agregados a la ventana de UtalCanvas.
    typedef enum UtalCanvasElementType
    {
        ELEMENT_POINT,
        ELEMENT_LINE,
        ELEMENT_CIRCLE,
        ELEMENT_FILLED_CIRCLE,
        ELEMENT_RECTANGLE,
        ELEMENT_FILLED_RECTANGLE,
        ELEMENT_TEXT,
        ELEMENT_IMAGE
    } UtalCanvasElementType;
    
    //Tipos de recursos a ser almacenados en memoria principal. 
    //Usados principalmente en resources_list.h.
    typedef enum ResourceType
    {
        RESOURCE_IMAGE,
        RESOURCE_AUDIO,
        RESOURCE_FONT
    } ResourceType;
    
    //Estructura que almacena un color en formato RGB.
    typedef struct UtalCanvasColor
    {
        int red;
        int green;
        int blue;
    } UtalCanvasColor;

    //Estructura que almacena la informacion de un punto para ser pintado en la 
    //ventana de UtalCanvas.
    typedef struct ElementPoint
    {
        double x;
        double y;
        UtalCanvasColor color;
        char tag[TAG_NAME_LENGTH];
    } ElementPoint;

    //Estructura que almacena la informacion de una linea para ser pintada en la 
    //ventana de UtalCanvas.
    typedef struct ElementLine
    {
        double x1;
        double y1;
        double x2;
        double y2;
        UtalCanvasColor color;
        char tag[TAG_NAME_LENGTH];
    } ElementLine;

    //Estructura que almacena la informacion de un circulo para ser pintado en la 
    //ventana de UtalCanvas.
    typedef struct ElementCircle
    {
        double x;
        double y;
        double radio;
        UtalCanvasColor color;
        char tag[TAG_NAME_LENGTH];
    } ElementCircle;

    //Estructura que almacena la informacion de un circul relleno para ser pintado en la 
    //ventana de UtalCanvas.
    typedef struct ElementFilledCircle
    {
        double x;
        double y;
        double radio;
        UtalCanvasColor outerColor;
        UtalCanvasColor fillColor;
        char tag[TAG_NAME_LENGTH];
    } ElementFilledCircle;

    //Estructura que almacena la informacion de un rectangulo para ser pintado en la 
    //ventana de UtalCanvas.
    typedef struct ElementRectangle
    {
        double x1;
        double y1;
        double x2;
        double y2;
        UtalCanvasColor color;
        char tag[TAG_NAME_LENGTH];
    } ElementRectangle;
    
    //Estructura que almacena la informacion de un rectangulo relleno para ser pintado en la 
    //ventana de UtalCanvas.
    typedef struct ElementFilledRectangle
    {
        double x1;
        double y1;
        double x2;
        double y2;
        UtalCanvasColor outerColor;
        UtalCanvasColor fillColor;
        char tag[TAG_NAME_LENGTH];
    } ElementFilledRectangle;
    
    //Estructura que almacena la informacion de una imagen para ser pintada en la 
    //ventana de UtalCanvas.
    typedef struct ElementImage
    {
        double x;
        double y;
        double width;
        double height;
        char filename[PATHNAME_LENGTH];
        SDL_Texture* texture;
        SDL_Rect* size;
        char tag[TAG_NAME_LENGTH];
    } ElementImage;
    
    //Estructura que almacena la informacion de un texto para ser pintado en la 
    //ventana de UtalCanvas.
    typedef struct ElementText
    {
        char fontFile[PATHNAME_LENGTH];
        double x;
        double y;
        char text[MAX_TEXT_LENGTH];
        double size;
        UtalCanvasColor color;
        char tag[TAG_NAME_LENGTH];
        TTF_Font *font;
        SDL_Surface* textSurface;
        SDL_Texture* texture;
        int data;
    } ElementText;
    
    //Estructura que almacena la informacion del mouse. 
    //Usada principalmente en window.h.
    typedef struct UtalCanvasWindowMouseInfo
    {
        double x;
        double y;
        int button;
    } UtalCanvasWindowMouseInfo;
    
    //Estructura de nodo para ser usada en utalcanvas_list.h
    typedef struct UtalCanvasNode
    {
        void* data;
        UtalCanvasElementType type;
        int index;
        char tag[TAG_NAME_LENGTH];
        struct UtalCanvasNode *next;
        struct UtalCanvasNode *prev;
    } UtalCanvasNode;
    
    typedef struct ResourceNode
    {
        void* data;
        ResourceType type;
        char name[TAG_NAME_LENGTH];
        struct ResourceNode *next;
        struct ResourceNode *prev;
    } ResourceNode;
    
    typedef struct JoystickData
    {
        SDL_Joystick* joystick;
        int n_buttons;
        bool* buttons;
        int n_axis;
        int* axis;
    } JoystickData;
    
    typedef struct JoystickNode
    {
        JoystickData* data;
        int which;
        struct JoystickNode* next;
        struct JoystickNode* prev;
    } JoystickNode;
    
    typedef struct ResourceImage
    {
        SDL_Texture* texture;
        SDL_Rect* size;
    } ResourceImage;
    
    typedef struct ResourceAudio
    {
        Mix_Chunk* chunk;
    } ResourceAudio;
    
    typedef struct ResourceFont
    {
        TTF_Font *font;
    } ResourceFont;
    
    typedef struct UtalCanvasPlainRectangle
    {
        double x;
        double y;
        double width;
        double height;
    } UtalCanvasPlainRectangle;
    
    typedef struct UtalCanvasWindowViewport
    {
        double xMin;
        double yMin;
        double xMax;
        double yMax;
        
    } UtalCanvasWindowViewport;
    
    typedef struct UtalCanvasWindowDimension
    {
        int width;
        int height;
        
    } UtalCanvasWindowDimension;


#ifdef __cplusplus
}
#endif

#endif /* UTALCANVAS_STRUCTURES_H */

