
# UtalCanvas

UtalCanvas es una librería que proporciona un conjunto de funciones para mostrar en una ventana algunas primitivas 
básicas de dibujo. El principal propósito de esta librería es ser utilizada como una herramienta que apoye pedagógicamente 
el proceso de enseñanza de algorimia y programación en los primeros cursos de introducción a la programación.

UtalCanvas fue desarrollado por Pablo Rojas Valdés (pabrojas@utalca.cl) en colaboración con Felipe Besoaín Pino 
(fbesoain@utalca.cl), ambos profesores de la escuela de Ingeniería en Desarrollo de Videojuegos y Realidad Virtual de la
Universidad de Talca.


# Configuración de ambiente para desarrollo

La librería UtalCanvas fue desarrollada en C utilizando SDL 2 como librería gráfica en el IDE NetBeans 8.2. Para no tener 
problemas de compatibilidad en Windows se utilizaron las versiones de 32 bits de SDL2, SDL_mixer, SDL_ttf y SDL_image.

## Configuración para Windows

Para windows primero se debe instalar MinGW (Minimalist GNU for Windows para 32 bits) y una vez en el instalador de paquetes se debe marcar y luego instalar lo siguiente:

* mingw-developer-toolkit
* mingw32-base
* mingw32-gcc-g++
* msys-base

Posterior a ello se debe descargar la última versión de la librería SDL 2.0 y las últimas versiones de SDL_mixer, SDL_ttf 
y SDL_image. Debido a que se utilizó windows y MinGW entonces debemos descargar las librerías para desarrollo adecuadas. 
Las versiones que se utilizaron para esta versión fueron:

* [SDL2-devel-2.0.5-mingw.tar.gz](http://libsdl.org/release/SDL2-devel-2.0.5-mingw.tar.gz)
* [SDL2_image-devel-2.0.1-mingw.tar.gz](http://libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.1-mingw.tar.gz)
* [SDL2_mixer-devel-2.0.1-mingw.tar.gz](http://libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.1-mingw.tar.gz)
* [SDL2_ttf-devel-2.0.14-mingw.tar.gz](http://libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.14-mingw.tar.gz)
