/** 
 * File:   utalcanvas.h
 * Author: Pablo Ignacio Rojas Valdés (pabrojas@utalca.cl)
 * 
 * Contiene todas las funciones definidas por la librería UtalCanvas.
 * 
 * Esta librería muestra una ventana, la cual inicialmente tiene un tamaño
 * de 640x480 pixeles y adicionalmente posee sus propias coordenadas de mundo,
 * las cuales van en eje X desde 0 a 640 y en el eje Y van desde 0 a 480. El 
 * origen de las coordenadas de mundo se encuentra en la esquina superior izauierda.
 * 
 * Durante la ejecución de esta ventana se pueden ir agregando elementos. 
 * Cada vez que se agrega un nuevo elemento se retorna su identificador único. 
 * Adicionalmente se puede asignar una etiqueta a cada elemento agregado, la 
 * cual no necesita se única, con el propósito de agrupar los elementos por su
 * etiqueta.
 * 
 * Existen funciones para mover y eliminar elementos por su identificador o por
 * su etuqueta. 
 *
 * Created on 15 de junio de 2016
 */

#ifndef UTALCANVAS_H
#define UTALCANVAS_H

#include <stdlib.h>

#include "utalcanvas_definitions.h"

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * Estructura utilizada para almacenar la información del mouse
     */
    struct UtalCanvasMouse
    {
        int x;
        int y;
        int boton;
    };

    /**
     * Muestra la ventana de UtalCanvas. Por defecto esta ventana tine dimensiones
     * de 640x480 pixeles y las coordenadas de mundo en el eje X van desde 
     * 0 hasta 640 y en el eje Y van desde 0 hasta 480. El origen de sistema 
     * coordenado de mundo parte en la esquina inferior izquierda y los valores 
     * aumentan hacia la derecha y arriba.
     */
    void show_window();

    /**
     * Cierra la ventana de UtalCanvas
     */
    void close_window();

    /**
     * Cambia el tamaño de la ventana de UtalCanvas sin modificar los valores
     * de las coordenadas de mundo.
     * 
     * @param width ancho de la ventana en pixeles
     * @param height alto de la ventana en pixeles
     */
    void window_size(int width, int height);

    /**
     * Cambia las coordenadas visibles del mundo.
     * 
     * @param x_bottom valor menor en el eje X, representado en valores de mundo.
     * @param y_bottom valor menor en el eje Y, representado en valores de mundo.
     * @param x_top valor mayor en el eje X, representado en valores de mundo.
     * @param y_top valor mayor en el eje Y, representado en valores de mundo.
     */
    void window_coordinates(int x_bottom, int y_bottom, int x_top, int y_top);

    /**
     * Cambia el color de fondo del mundo. Para ello toma los nombres de los colores
     * provistos en la siguiente página: 
     *      http://cloford.com/resources/colours/500col.htm
     * 
     * @param background nombre del color que tendrá el fondo del mundo.
     */
    void window_background(char background[COLOR_NAME_LENGTH]);

    /**
     * Cambia el título de la ventana.
     * 
     * @param title título de la ventana.
     */
    void window_title(char title[MAX_TEXT_LENGTH]);

    /**
     * Retorna 1 si la ventana está cerrada o un 0 de lo contrario.
     * 
     * @return 1 si la ventana está cerrada o un 0 de lo contrario.
     */
    int window_is_closed();

    /**
     * Dibuja un punto en el mundo y devuelve su índice. 
     * 
     * @param x coordenada X del punto a dibujar, considerando coordenadas de mundo.
     * @param y coordenada Y del punto a dibujar, considerando coordenadas de mundo.
     * @param color del punto a dibujar.
     * @param ... etiqueta del punto, este parámetro es opcional.
     * @return el índice del punto recién creado.
     */
    int create_point(int x, int y, char color[COLOR_NAME_LENGTH], ...);

    /**
     * Dibuja una línea en el mundo y devuelve su índice. 
     * 
     * @param x1 coordenada X del inicio de la línea a dibujar, considerando coordenadas de mundo.
     * @param y1 coordenada Y del inicio de la línea a dibujar, considerando coordenadas de mundo.
     * @param x2 coordenada X del fin de la línea a dibujar, considerando coordenadas de mundo.
     * @param y2 coordenada Y del fin de la línea a dibujar, considerando coordenadas de mundo.
     * @param color de la línea a dibujar.
     * @param ... etiqueta de la línea, este parámetro es opcional.
     * @return el índice de la línea recién creada.
     */
    int create_line(int x1, int y1, int x2, int y2, char color[COLOR_NAME_LENGTH], ...);

    /**
     * Dibuja el borde de una circunferencia en el mundo y devuelve su índice. 
     * 
     * @param x coordenada X del centro de la circunferencia a dibujar, considerando coordenadas de mundo.
     * @param y coordenada Y del centro de la circunferencia a dibujar, considerando coordenadas de mundo.
     * @param radius el radio de la la circunferencia, considerando coordenadas de mundo.
     * @param color del borde de la circunferencia.
     * @param ...etiqueta de la línea, este parámetro es opcional.
     * @return el índice de la circunferencia recién creada.
     */
    int create_circle(int x, int y, int radius, char color[COLOR_NAME_LENGTH], ...);

    /**
     * Dibuja una circunferencia en el mundo y devuelve su índice. 
     * 
     * @param x coordenada X del centro de la circunferencia a dibujar, considerando coordenadas de mundo.
     * @param y coordenada Y del centro de la circunferencia a dibujar, considerando coordenadas de mundo.
     * @param radius el radio de la la circunferencia, considerando coordenadas de mundo.
     * @param borderColor color del borde de la circunferencia.
     * @param fillColor color del relleno de la circunferencia.
     * @param ... etiqueta de la línea, este parámetro es opcional.
     * @return el índice de la circunferencia recién creada.
     */
    int create_filled_circle(int x, int y, int radius, char borderColor[COLOR_NAME_LENGTH], char fillColor[COLOR_NAME_LENGTH], ...);

    /**
     * Dibuja el borde de un rectángulo en el mundo y devuelve su índice, 
     * para ello necesita dos vértices opuestos del rectángulo. 
     * 
     * @param x1 coordenada X del primer vértice del rectángulo a dibujar, considerando coordenadas de mundo.
     * @param y1 coordenada Y del primer vértice del rectángulo a dibujar, considerando coordenadas de mundo.
     * @param x2 coordenada X del segundo vértice del rectángulo a dibujar, considerando coordenadas de mundo.
     * @param y2 coordenada Y del segundo vértice del rectángulo a dibujar, considerando coordenadas de mundo.
     * @param color del borde del rectángulo.
     * @param ... etiqueta de la línea, este parámetro es opcional.
     * @return el índice del rectángulo recién creado.
     */
    int create_rectangle(int x1, int y1, int x2, int y2, char color[COLOR_NAME_LENGTH], ...);

    /**
     * Dibuja un rectángulo en el mundo y devuelve su índice, para ello necesita 
     * dos vértices opuestos del rectángulo. 
     * 
     * @param x1 coordenada X del primer vértice del rectángulo a dibujar, considerando coordenadas de mundo.
     * @param y1 coordenada Y del primer vértice del rectángulo a dibujar, considerando coordenadas de mundo.
     * @param x2 coordenada X del segundo vértice del rectángulo a dibujar, considerando coordenadas de mundo.
     * @param y2 coordenada Y del segundo vértice del rectángulo a dibujar, considerando coordenadas de mundo.
     * @param borderColor color del borde del rectángulo.
     * @param fillColor color del relleno del rectángulo.
     * @param ... etiqueta de la línea, este parámetro es opcional.
     * @return el índice del rectángulo recién creado.
     */
    int create_filled_rectangle(int x1, int y1, int x2, int y2, char borderColor[COLOR_NAME_LENGTH], char fillColor[COLOR_NAME_LENGTH], ...);

    /**
     * Dibuja una imagen en el mundo y devuelve su índice.
     * 
     * @param x coordenada X de la esquina inferior izquierda de la imagen a dibujar, considerando coordenadas de mundo.
     * @param y coordenada Y de la esquina inferior izquierda de la imagen a dibujar, considerando coordenadas de mundo.
     * @param width ancho de la imagen a dibujar, condiderando coordendas de mundo.
     * @param height alto de la imagen a dibujar, considerando coordenadas de mundo.
     * @param filename nombre del archivo que contiene la imagen a dibujar.
     * @param ... etiqueta de la línea, este parámetro es opcional.
     * @return el índice de la imagen recién creada.
     */
    int create_image(int x, int y, int width, int height, char filename[PATHNAME_LENGTH], ...);

    /**
     * Dibuja un texto en el mundo y devuelve su índice.
     * 
     * @param fontFile archivo TTF que contiene la fuente con la cual se dibujará el texto
     * @param x coordenada X de la esquina inferior izquierda del texto a dibujar, considerando coordenadas de mundo.
     * @param y coordenada Y de la esquina inferior izquierda del texto a dibujar, considerando coordenadas de mundo.
     * @param caption texto que se dibujará en el mundo
     * @param size tamaño de la fuente
     * @param color de relleno del texto
     * @param ... etiqueta de la línea, este parámetro es opcional.
     * @return el índice del texto recién creado.
     */
    int create_text(char fontFile[PATHNAME_LENGTH], int x, int y, char caption[MAX_TEXT_LENGTH], int size, char color[COLOR_NAME_LENGTH], ...);

    /**
     * Elimina un elemento del mundo dado su índice.
     * 
     * @param index indice del elemento a eliminar.
     */
    void erase_by_index(int index);

    /**
     * Elimina todos los elementos del mundo que tengan la etiqueta especificada.
     * 
     * @param tag etiqueta de los elementos a eliminar.
     */
    void erase_by_tag(char tag[TAG_NAME_LENGTH]);

    /**
     * Elimina todos los elementos del mundo.
     */
    void erase_all();

    /**
     * Mueve un elemento del mundo, dado su índice, una cantidad específica en 
     * el eje X y en el eje Y, considerando coordenadas de mundo.
     * 
     * @param index índice del elemento a mover.
     * @param dx cantidad a mover en el eje X, considerando coordenadas de mundo.
     * @param dy cantidad a mover en el eje Y, considerando coordenadas de mundo.
     */
    void move_by_index(int index, int dx, int dy);

    /**
     * Mueve todos los elementos del mundo que tengas la etiqueta especificada, 
     * una cantidad específica en el eje X y en el eje Y, considerando 
     * coordenadas de mundo.
     * 
     * @param tag etiqueta de los elementos a mover.
     * @param dx cantidad a mover en el eje X, considerando coordenadas de mundo.
     * @param dy cantidad a mover en el eje Y, considerando coordenadas de mundo.
     */
    void move_by_tag(char tag[TAG_NAME_LENGTH], int dx, int dy);

    /**
     * Retorna la tecla presionada utilizando el enum UtalCanvasKey como 
     * representación de la tecla presionada
     * 
     * @return la tecla presionada
     */
    int key_pressed();

    /**
     * Retorna una variable del tipo struct UtalCanvasWindowMouseInfo, la cual 
     * contiene la información actual del mouse (x, y, botón). La coordenada (x, y)
     * está representada en coordenadas de mundo y el botón tomará uno de los 
     * siguientes valores:
     *  -1: cuando no está presionado ningún botón
     *   1: cuando está presionado el botón de la izquierda
     *   2: cuando está presionado el botón central
     *   3: cuando está presionado el botón de la derecha
     * 
     * @return una variable del tipo struct UtalCanvasWindowMouseInfo que contiene
     *          la información actual del mouse
     */
    struct UtalCanvasMouse mouse_state();

    /**
     * Estructura enumerada que contiene todas las posibles teclas que utalcanvas maneja.
     */
    typedef enum UtalCanvasKey
    {
        UTALKEY_0                , UTALKEY_1             , UTALKEY_2                 , UTALKEY_3              , 
        UTALKEY_4                , UTALKEY_5             , UTALKEY_6                 , UTALKEY_7              , 
        UTALKEY_8                , UTALKEY_9             , UTALKEY_A                 , UTALKEY_AC_BACK        , 
        UTALKEY_AC_BOOKMARKS     , UTALKEY_AC_FORWARD    , UTALKEY_AC_HOME           , UTALKEY_AC_REFRESH     , 
        UTALKEY_AC_SEARCH        , UTALKEY_AC_STOP       , UTALKEY_AGAIN             , UTALKEY_ALTERASE       , 
        UTALKEY_APOSTROPHE       , UTALKEY_APPLICATION   , UTALKEY_AUDIOMUTE         , UTALKEY_AUDIONEXT      , 
        UTALKEY_AUDIOPLAY        , UTALKEY_AUDIOPREV     , UTALKEY_AUDIOSTOP         , UTALKEY_B              , 
        UTALKEY_BACKSLASH        , UTALKEY_BACKSPACE     , UTALKEY_BRIGHTNESSDOWN    , UTALKEY_BRIGHTNESSUP   , 
        UTALKEY_C                , UTALKEY_CALCULATOR    , UTALKEY_CANCEL            , UTALKEY_CAPSLOCK       , 
        UTALKEY_CLEAR            , UTALKEY_CLEARAGAIN    , UTALKEY_COMMA             , UTALKEY_COMPUTER       , 
        UTALKEY_COPY             , UTALKEY_CRSEL         , UTALKEY_CURRENCYSUBUNIT   , UTALKEY_CURRENCYUNIT   , 
        UTALKEY_CUT              , UTALKEY_D             , UTALKEY_DECIMALSEPARATOR  , UTALKEY_DELETE         , 
        UTALKEY_DISPLAYSWITCH    , UTALKEY_DOWN          , UTALKEY_E                 , UTALKEY_EJECT          , 
        UTALKEY_END              , UTALKEY_EQUALS        , UTALKEY_ESCAPE            , UTALKEY_EXECUTE        , 
        UTALKEY_EXSEL            , UTALKEY_F             , UTALKEY_F1                , UTALKEY_F10            , 
        UTALKEY_F11              , UTALKEY_F12           , UTALKEY_F13               , UTALKEY_F14            , 
        UTALKEY_F15              , UTALKEY_F16           , UTALKEY_F17               , UTALKEY_F18            , 
        UTALKEY_F19              , UTALKEY_F2            , UTALKEY_F20               , UTALKEY_F21            , 
        UTALKEY_F22              , UTALKEY_F23           , UTALKEY_F24               , UTALKEY_F3             , 
        UTALKEY_F4               , UTALKEY_F5            , UTALKEY_F6                , UTALKEY_F7             , 
        UTALKEY_F8               , UTALKEY_F9            , UTALKEY_FIND              , UTALKEY_G              , 
        UTALKEY_GRAVE            , UTALKEY_H             , UTALKEY_HELP              , UTALKEY_HOME           , 
        UTALKEY_I                , UTALKEY_INSERT        , UTALKEY_J                 , UTALKEY_K              , 
        UTALKEY_KBDILLUMDOWN     , UTALKEY_KBDILLUMTOGGLE, UTALKEY_KBDILLUMUP        , UTALKEY_KP_0           , 
        UTALKEY_KP_00            , UTALKEY_KP_000        , UTALKEY_KP_1              , UTALKEY_KP_2           , 
        UTALKEY_KP_3             , UTALKEY_KP_4          , UTALKEY_KP_5              , UTALKEY_KP_6           , 
        UTALKEY_KP_7             , UTALKEY_KP_8          , UTALKEY_KP_9              , UTALKEY_KP_A           , 
        UTALKEY_KP_AMPERSAND     , UTALKEY_KP_AT         , UTALKEY_KP_B              , UTALKEY_KP_BACKSPACE   , 
        UTALKEY_KP_BINARY        , UTALKEY_KP_C          , UTALKEY_KP_CLEAR          , UTALKEY_KP_CLEARENTRY  , 
        UTALKEY_KP_COLON         , UTALKEY_KP_COMMA      , UTALKEY_KP_D              , UTALKEY_KP_DBLAMPERSAND, 
        UTALKEY_KP_DBLVERTICALBAR, UTALKEY_KP_DECIMAL    , UTALKEY_KP_DIVIDE         , UTALKEY_KP_E           , 
        UTALKEY_KP_ENTER         , UTALKEY_KP_EQUALS     , UTALKEY_KP_EQUALSAS400    , UTALKEY_KP_EXCLAM      , 
        UTALKEY_KP_F             , UTALKEY_KP_GREATER    , UTALKEY_KP_HASH           , UTALKEY_KP_HEXADECIMAL , 
        UTALKEY_KP_LEFTBRACE     , UTALKEY_KP_LEFTPAREN  , UTALKEY_KP_LESS           , UTALKEY_KP_MEMADD      , 
        UTALKEY_KP_MEMCLEAR      , UTALKEY_KP_MEMDIVIDE  , UTALKEY_KP_MEMMULTIPLY    , UTALKEY_KP_MEMRECALL   , 
        UTALKEY_KP_MEMSTORE      , UTALKEY_KP_MEMSUBTRACT, UTALKEY_KP_MINUS          , UTALKEY_KP_MULTIPLY    , 
        UTALKEY_KP_OCTAL         , UTALKEY_KP_PERCENT    , UTALKEY_KP_PERIOD         , UTALKEY_KP_PLUS        , 
        UTALKEY_KP_PLUSMINUS     , UTALKEY_KP_POWER      , UTALKEY_KP_RIGHTBRACE     , UTALKEY_KP_RIGHTPAREN  , 
        UTALKEY_KP_SPACE         , UTALKEY_KP_TAB        , UTALKEY_KP_VERTICALBAR    , UTALKEY_KP_XOR         , 
        UTALKEY_L                , UTALKEY_LALT          , UTALKEY_LCTRL             , UTALKEY_LEFT           , 
        UTALKEY_LEFTBRACKET      , UTALKEY_LGUI          , UTALKEY_LSHIFT            , UTALKEY_M              , 
        UTALKEY_MAIL             , UTALKEY_MEDIASELECT   , UTALKEY_MENU              , UTALKEY_MINUS          , 
        UTALKEY_MODE             , UTALKEY_MUTE          , UTALKEY_N                 , UTALKEY_NUMLOCKCLEAR   , 
        UTALKEY_O                , UTALKEY_OPER          , UTALKEY_OUT               , UTALKEY_P              , 
        UTALKEY_PAGEDOWN         , UTALKEY_PAGEUP        , UTALKEY_PASTE             , UTALKEY_PAUSE          , 
        UTALKEY_PERIOD           , UTALKEY_POWER         , UTALKEY_PRINTSCREEN       , UTALKEY_PRIOR          , 
        UTALKEY_Q                , UTALKEY_R             , UTALKEY_RALT              , UTALKEY_RCTRL          , 
        UTALKEY_RETURN           , UTALKEY_RETURN2       , UTALKEY_RGUI              , UTALKEY_RIGHT          , 
        UTALKEY_RIGHTBRACKET     , UTALKEY_RSHIFT        , UTALKEY_S                 , UTALKEY_SCROLLLOCK     , 
        UTALKEY_SELECT           , UTALKEY_SEMICOLON     , UTALKEY_SEPARATOR         , UTALKEY_SLASH          , 
        UTALKEY_SLEEP            , UTALKEY_SPACE         , UTALKEY_STOP              , UTALKEY_SYSREQ         , 
        UTALKEY_T                , UTALKEY_TAB           , UTALKEY_THOUSANDSSEPARATOR, UTALKEY_U              , 
        UTALKEY_UNDO             , UTALKEY_UNKNOWN       , UTALKEY_UP                , UTALKEY_V              , 
        UTALKEY_VOLUMEDOWN       , UTALKEY_VOLUMEUP      , UTALKEY_W                 , UTALKEY_WWW            , 
        UTALKEY_X                , UTALKEY_Y             , UTALKEY_Z                 , UTALKEY_NONE              
    } UtalCanvasKey;

#ifdef __cplusplus
}
#endif

#endif /* UTALCANVAS_H */

