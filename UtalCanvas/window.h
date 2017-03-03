
/** 
 * File:   utalcanvas_window.h
 * Author: Pablo Ignacio Rojas Valdes (pabrojas@utalca.cl)
 * Contributor: Felipe Andres Besoaen Pino (fbesoain@utalca.cl)
 * 
 * Contiene todas las funciones de acceso y modificacion de elementos a la 
 * ventana y audio. Para agilizar el proceso de pintado, los recursos se carga 
 * una única vez y se mantienen en memoria principal para su acceso posterior. 
 * Lo mismo ocurre con los archivos de aurio. Para lograr este proposito se 
 * implemento una adaptacion del patron de diseno Objecto Pool, mediante el uso
 * de tres listas enlazadas (imagenes, archivos de fuentes y audios), definidas 
 * en resources_list.h.
 * 
 * Para no agotar los recursos de procesamiento del computador, el ciclo principal
 * de pintado intenta trabajar a 60 FPS. Si el computador se encuentra demasiado
 * sobrecargado, el ciclo al menos realizara una pausa de 1 milisegundo entre 
 * iteraciones para pintar cada frame.
 * 
 * El acceso a todos los recursos compartidos se realiza a traves de las funciones
 * __mutex_lock() y __mutex_unlock(). Ambas funciones, incluyendo la funcion
 * __mutex_init() fueron programadas para funcionar en windows utilizando los 
 * Windows Threads y en *nix usando pthreads.
 * 
 * Para el manejo de los joysticks se utiliza una lista enlazada adicional, la 
 * cual fue implementada en la libreria joystick_list.h.
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

#include "structures.h"
#include "definitions.h"
#include "utalcanvas.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     * Inicializa la ventana de SDL, habilitando audio, imagenes y fuentes.
     */
    bool ucw_initialize();
    
    /**
     * Cierra el ciclo principal (game loop) para que termine el thread, luego
     * elimina todos los elementos de la lista y cierra SDL.
     */
    void ucw_close();
    
    /**
     * Ciclo principal (game loop) de la libreria UtalCanvas. Repinta la ventana 
     * cuando se agrega algun elemento e intenta respetar 60 FPS. Mantiene actualizada
     * la informacion de las teclas y del mouse.
     */
    void ucw_loop();
    
    /**
     * Inicia el thread de la ventana de UtalCanvas usando Windows Threads o pthreads,
     * dependiendo del sistema operativo.
     */
    void ucw_start();
    
    /**
     * Cambia el tamano de la ventana de UtalCanvas creada con SDL.
     * 
     * @param width nuevo ancho de la ventana.
     * @param height nuevo alto de la ventana.
     */
    void ucw_set_size(int width, int height);
    
    /**
     * Cambia el area visible del mundo que muestra la ventana de UtalCanvas.
     * 
     * @param xMin menor valor en el eje x.
     * @param yMin menor valor en el eje y.
     * @param xUp mayor valor en el eje x.
     * @param yUp mayor valor en el eje y.
     */
    void ucw_set_viewport(double xMin, double yMin, double xUp, double yUp);
    
    /**
     * Cambia el titulo de la ventana.
     * 
     * @param title nuevo titulo de la ventana.
     */
    void ucw_set_title(char title[MAX_TEXT_LENGTH]);
    
    /**
     * Cambia el color de fondo de la ventana UtalCanvas segun el nombre
     * del color.
     * 
     * @param background nombre del nuevo color de fondo.
     */
    void ucw_set_background(char background[COLOR_NAME_LENGTH]);
    
    /**
     * Retorna true si la ventana se encuentra cerrada o false de lo contratio.
     * 
     * @return true si la ventana se encuentra cerrada o false de lo contratio.
     */
    bool ucw_is_closed();
    
    /**
     * Dibuja un punto en la ventana. Recibe como parametro una estructura del tipo
     * UtalCanvasPoint (definido en definitions.h), si se especifica un parametro de 
     * otro tipo el metodo fallara.
     * 
     * @param data parametro del tipo UtalCanvasPoint que se dibujara en la ventana.
     */
    void ucw_draw_point(void* data);
    
    /**
     * Dibuja una linea en la ventana. Recibe como parametro una estructura del tipo
     * UtalCanvasLine (definido en definitions.h), si se especifica un parametro de 
     * otro tipo el metodo fallara.
     * 
     * @param data parametro del tipo UtalCanvasLine que se dibujara en la ventana.
     */
    void ucw_draw_line(void* data);
    
    /**
     * Dibuja el borde de un rectangulo en la ventana. Recibe como parametro una 
     * estructura del tipo UtalCanvasRectangle (definido en definitions.h), si se 
     * especifica un parametro de otro tipo el metodo fallara.
     * 
     * @param data parametro del tipo UtalCanvasRectangle que se dibujara en la ventana.
     */
    void ucw_draw_rectangle(char* data);
    
    /**
     * Dibuja un rectangulo relleno en la ventana. Recibe como parametro una estructura 
     * del tipo UtalCanvasFilledRectangle (definido en definitions.h), si se especifica 
     * un parametro de otro tipo el metodo fallara.
     * 
     * @param data parametro del tipo UtalCanvasFilledRectangle que se dibujara en la ventana.
     */
    void ucw_fill_rectangle(char* data);
    
    /**
     * Dibuja un el borde de un circulo en la ventana. Recibe como parametro una estructura 
     * del tipo UtalCanvasCircle (definido en definitions.h), si se especifica 
     * un parametro de otro tipo el metodo fallara.
     * 
     * @param data parametro del tipo UtalCanvasCircle que se dibujara en la ventana.
     */
    void ucw_draw_circle(char* data);
    
    /**
     * Dibuja un circulo relleno en la ventana. Recibe como parametro una estructura 
     * del tipo UtalCanvasFilledCircle (definido en definitions.h), si se especifica 
     * un parametro de otro tipo el metodo fallara.
     * 
     * @param data parametro del tipo UtalCanvasFilledCircle que se dibujara en la ventana.
     */
    void ucw_fill_circle(void* data);
    
    /**
     * Dibuja una imagen en la ventana. Recibe como parametro una estructura del tipo
     * UtalCanvasImage (definido en definitions.h), si se especifica un parametro de 
     * otro tipo el metodo fallara.
     * 
     * @param data parametro del tipo UtalCanvasImage que se dibujara en la ventana.
     */
    void ucw_draw_image(void* data);
    
    /**
     * Reproduce un audio en formato wav o mp3. Recibe como parametro la ruta del 
     * archivo a reproducir y la cantidad de veces que se repetira. Siempre se 
     * reproduce al menos una vez y despues, dependiendo del valor del parametro 
     * loops, será la cantidad de repeticiones. 
     * 
     * Si se especifica 0 para el parametro
     * loops se reproducira una vez, si se especifica 1 para el mismo parametro
     * se reproducira 2 veces y asi sucesivamente. Si se especifica el valor de -1
     * se reproducira infinitamente hasta que se pause o se detenga la reproduccion
     * del canal.
     * 
     * El valor deretorno especifica el canal en el que se esta reproduciendo este audio.
     *  
     * @param audio_file archivo wav o mp3 que se desea reproducir.
     * @param loops cantidad de repeticiones posterior a su reproduccion.
     * @return el indice del canal donde se encuentra la reproduccion del audio.
     */
    int ucw_play_audio(char audio_file[PATHNAME_LENGTH], int loops);
    
    /**
     * Pausa una reproduccion de un audio dado su canal.
     *  
     * @param channel canal que se desea pausar su reproduccion.
     */
    void ucw_pause_audio(int channel);

    /**
     * Resume una reproduccion de un audio dado su canal.
     *  
     * @param channel canal que se desea resumir su reproduccion.
     */
    void ucw_resume_audio(int channel);
    
    /**
     * Detiene una reproduccion de un audio dado su canal y lo libera para su uso posterior.
     *  
     * @param channel canal que se desea detener su reproduccion.
     */
    int ucw_stop_audio(int channel);
    
    /**
     * Agrega un elemento a la lista de elementos graficos y luego repinta la ventana.
     * El primer parametro especifica el tipo de elemento a agregar y el segundo
     * parametro contiene el elemento a agregar, luego retorna el indice del 
     * elemento agregado.
     * 
     * Este metodo bloquea el acceso a la lista de elementos, ya que esta lista puede
     * ser usada concurrentemente desde el thread iniciado por el programa principal
     * y desde el thread de la ventana de SDL.
     * 
     * @param type tipo del elemento a agregar, es usado para realizar la conversion explicita.
     * @param data estructura de datos a agregar, debe corresponder con el tipo 
     *          especificado en el primer parametro
     * @return el indice del elemento recien agregado
     */
    int  ucw_add_element(UtalCanvasElementType type, void* data);
    
    /**
     * Elimina un elemento de la lista de elementos segun su identificador. Este
     * metodo bloque el acceso  a la lista de elementos, ya que esta lista puede
     * ser usada concurrentemente desde el thread iniciado por el programa principal
     * y desde el thread de la ventana de SDL.
     */
    void ucw_remove_element_by_id(int index);
    
    /**
     * Elimina todos los elementos de la lista de elementos que contengan el tag especificado. 
     * Este metodo bloque el acceso a la lista de elementos, ya que esta lista puede
     * ser usada concurrentemente desde el thread iniciado por el programa principal
     * y desde el thread de la ventana de SDL.
     */
    void ucw_remove_element_by_tag(char tag[TAG_NAME_LENGTH]);
    
    /**
     * Elimina todos los elementos de la lista de elementos. Este metodo bloque el acceso 
     * a la lista de elementos, ya que esta lista puede ser usada concurrentemente 
     * desde el thread iniciado por el programa principal y desde el thread de 
     * la ventana de SDL.
     */
    void ucw_remove_all_elements();
    
    /**
     * Cambia los valores de los atributos x e y del elemento de la lista elementos 
     * segun su identificador. Este metodo bloque el acceso  a la lista de elementos, 
     * ya que esta lista puede ser usada concurrentemente desde el thread iniciado 
     * por el programa principal y desde el thread de la ventana de SDL.
     */
    void ucw_move_element_by_id(int index, double dx, double dy);
    
    /**
     * Cambia los valores de los atributos x e y de todos los elementos de la lista elementos 
     * que contengan el tag especificado. Este metodo bloque el acceso  a la lista de elementos, 
     * ya que esta lista puede ser usada concurrentemente desde el thread iniciado 
     * por el programa principal y desde el thread de la ventana de SDL.
     */
    void ucw_move_element_by_tag(char tag[TAG_NAME_LENGTH], double dx, double dy);
    
    /**
     * Retorna la tecla presionada por el usuario mientras se encuentra en ejecucion
     * la ventana de UtalCanvas.
     * 
     * @return la tecla presionada por el usuario mientras se encuentra en ejecucion
     *          la ventana de UtalCanvas.
     */
    UtalCanvasKey ucw_get_key_pressed();
    
    /**
     * Retorna el estado del mouse mientra se encuentra en ejecucion la ventana de UtalCanvas.
     * Los valores de x e y se encuentran en coordenadas de mundo. El valor del boton es obtenido
     * de la libreria SDL. Si no hay ningun boton presionado el valor de boton sera -1.
     * 
     * @return el estado del mouse mientra se encuentra en ejecucion la ventana de UtalCanvas.
     */
    UtalCanvasWindowMouseInfo ucw_get_mouse_state();
    
    /**
     * Retorna 1 si el boton del joystick_id especificado como parametro se 
     * encuentra presionado, o un 0 de lo contrario.
     * 
     * @param joystick_id identificador del joystick.
     * @param button numero del boton.
     * @return 1 si el boton del joystick_id se encuentra presionado, 0 de lo contrario.
     */
    int ucw_get_joystick_button_state( int joystick_id, int button );
    
    /**
     * Retorna el estado del axis del joystick_id especificado como parametro.
     * 
     * @param joystick_id identificador del joystick.
     * @param axis numero del axis.
     * @return el estado del axis del joystick_id especificado como parametro.
     */
    int ucw_get_joystick_axis_value( int joystick_id, int axis );
    
    /**
     * Retorna 1 si el joystick_id pasado como parametro se encuentra conectado, 
     * o un 0 de lo contrario.
     * 
     * @param joystick_id identificador del joystick.
     * @return 1 si el joystick_id pasado como parametro se encuentra conectado, 
     *          o un 0 de lo contrario.
     */
    int ucw_get_joystick_state( int joystick_id );
    
    
    /**
     * Dibuja el borde de una elipse en la ventana usando coordenadas de ventana.
     * Este metodo usa el Bresenham's line algorithm para dibujar el borde sin usar
     * las funciones de la libreria matematica.
     * 
     * @param circle estructura UtalCanvasCircle que contiene la informacion del 
     *          circulo (en coordenas de mundo) a pintar en la ventana (en 
     *          coordenadas de ventana).
     */
    void __ucw_draw_ellipse(ElementCircle* circle);
    
    /**
     * Dibuja una elipse rellena y luego dibuja el borde en la ventana usando 
     * coordenadas de ventana.
     * 
     * Este metodo usa el Bresenham's line algorithm para dibujar el relleno y 
     * borde sin usar las funciones de la libreria matematica. Para dibujar el
     * relleno, dibuna lineas entre cada uno de los puntos de los bordes calculados,
     * para cada uno de los octantes horizontales simetricos.
     * 
     * @param circle estructura UtalCanvasFilledCircle que contiene la informacion del 
     *          circulo (en coordenas de mundo) a pintar en la ventana (en 
     *          coordenadas de ventana).
     */
    void __ucw_fill_ellipse(ElementFilledCircle* circle);
    
    /**
     * Crea y retorna una estructura del tipo JoystickData (definida en definitions.h)
     * la cual almacenara el estado del joystick especificado con el parametro
     * joystick.
     * 
     * FUNCION DE USO INTERNO.
     * 
     * @param joystick estructura de SDL que contiene la informacion del joystick.
     * @return retorna una estructura del tipo JoystickData la cual almacenara el 
     *          estado del joystick.
     */
    JoystickData* __create_joystick_data(SDL_Joystick *joystick);
    
    /**
     * Inicializa el mutex que exluira el acceso a los datos compartidos entre
     * el thread principal y el thread de la ventana de UtalCanvas.
     * 
     * FUNCION DE USO INTERNO.
     */
    void __mutex_init();
    
    /**
     * Bloquea el mutex para acceder a los datos compartidos entre
     * el thread principal y el thread de la ventana de UtalCanvas.
     * 
     * FUNCION DE USO INTERNO.
     */
    void __mutex_lock();
    
    /**
     * Desbloquea el mutex para acceder a los datos compartidos entre
     * el thread principal y el thread de la ventana de UtalCanvas.
     * 
     * FUNCION DE USO INTERNO.
     */
    void __mutex_unlock();
    

#ifdef __cplusplus
}
#endif

#endif /* UTALCANVASWINDOW_H */

