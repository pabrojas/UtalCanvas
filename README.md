
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

Descomprimimos los archivos en una carpeta, por ejemplo en **C:\SDL2**, y luego procedemos a configurar NetBeans.
Recordar que Utalcanvas para Windows utilizó las versiones de **32-bits**, por lo cual se referenciarán las carpetas
**i686-w64-mingw32**. Para realizar la configuración, en las propiedades del proyecto UtalCanvas y se deben realizar
las siguientes configuraciones: 

1. En la sección **Build**, sub sección **C Compiler** se debe modificar la propiedad **Include Directories**, como se muestra en 
   la siguiente imagen:

   ![Include Directories](https://lh3.googleusercontent.com/gvA9AyWEr7m6l5IrLNAW_A4G36tjlp7T6uDT_7ETTn6EY31t80fIc6kRIXAQbnaPyyHuZOl_RG2Uzv5KqO3EYWPhIgSU84T2houAivjnLmuQaFQr76A8pMRbRovGsfqloeo1BO0nPb8s8Qwd0epKypkBta2zbZiLenjJ-hiZfFvSXsg7FIXu3w8llgVTQeAxIDJkUFSXr75Km448Pl-5Of0XYXQLHIhUWEx9UX4KgicCLzvxf4OWad77IW4FLMsvgLjxbd3NhbWRZlrXfVCTzhrcv2FewRZk6k7Jp4g7s4jMGtwalYMUs5Owh4N_4VV6YFviGyqKXKo40LjR2ff52WbQ1uHPhjkVlHhQvo6_s3f5nXXeJXMLevrYpxGydk7QkEhLVTAMm0UpatqIexFOADOYUrdj1niAmuyalKrWV6kfNmc6yTQSGyHciuy7gMPoX-dKcbrlvz6IHT4b1HUQQYvoFONUtiDwn2nnnSENIE2eCvervaiarbrZrEPK2v7ETzsHzo1hq6U00Ge-sJ8T6NittjQKVpZR-e5O6pJSNr2VJ55r91YXs3GoQyu5wt6IFtZFOzEBqoh6StgLvjsw2rXsdk9kRQmApY6GACa3WI-k53k=w902-h601-no)

   Luego se debe editar esta propiedad y agregar las referencias a las carpetas **include/SDL2** de cada una de las librerías
   descargadas, como se muestra en la siguiente imagen:

   ![Include Direcrtories](https://lh3.googleusercontent.com/FY_5vyCP60yLuaIFiGWe0DImk91AMhTpGLXbZ0tW4bSrXANpqEdO4a43HbgZ3VqkVaKZ8s2RzTHxd-prgQpEmblFV4iSI7BD0bxT4gYDpiGwwPdsW9cBMzR-AzLpY_dfVgrVtNlVx5Q_tTcziIHwyhL1mQVUEX9oxcZEVuaGOooK2NoOzxKWOahXqDnNwPYTBmCJ46PL1kiDIXuGB-GMvBmiR3uMk3sWzeCVymfhg5i7gH_GW_8kguDztWD-u7LRLUrU8xXC4bVeVLZiRBhk1HncGhqMPJqdhVYauLcUAn5qOiHpS3arpcRQXs9TsV18BFgEPh4rHJQlU3_JcMpqL-djGbaHwtas8o854Gqun1SNj_Q0hlFwTYCYN27PfA0NQCRs5HH4h3cqqEWN5uVgHq29UY_WWKh7Cmnryt4nXE-7O37j8rkS7sRaS0l68ot1tkhYGeTlRnyiAgKDD8nZ7JEVkenT07oD14e1JrJHFVB9_U-X3eFzV0_Q9Kmy7CQ7--LnggY_7eRAo0GvHmAYf7wx2e8Tip84IZU4ClHQl2r0FmCAP1t5ul3sU5fqJyU_PLuZSR9LP-ZzvhwBesN30CZnOW_qV-N-sx1PbyGnxoHtUlw=w482-h352-no)

2. En la sección **Build**, sub sección **Linker** se debe modificar la propiedad **Additional Library Directories**, como se muestra
   en la siguiente imagen:

   ![Additional Library Directories](https://lh3.googleusercontent.com/vDrKYcKlIilOVTdrx0S4DkI5IbLboeuiopGyXB-hgdAYL_PqyXX6DZ4kqkH-av4Gf2xiooMdNaqgMKo7AfR01MhSgJlUTuTjFZmHsp5ZaffAqgtAH2laLt0lHkxi1v4j-LCCX1f07wCUNpY4QNqzG7po6qIym2qh2XnkNGdyNNWgrPuHPXkopy76bWIrVcmhvNjgpks8A-FNy6Adb9Y4E-q5djX6jKVHv1V4XWVbEqDmrKoWf1NX_xZB8xTWqQFnA9YkaasoTmB1dI8-9dmbgxOob9NtY_V0kYmJczemz5QpQBtaQdqex7NzFu6i0sbGhP9LfvUziqXJiolg02pFB4ZBMiw1jPaPFwfcZn0e3dYBSShBQQKlhM18WWoD-lRzlkcQ5Puq4lyJwxg_0xfpMzS1VYxDEzrO66fJq-n6PvHiDUhSHQM9QEWLJkDhhqunAHxmZEjMY0iDOpSx9NIW0-6AtIkxfmhjDoWh8ZzrCPM4SaFYuQqG0qW2bOyaOw64YmrfAkaq9L8C1C1YDb_q4IYqGErco183HpdryVy4eI48voN9Z8bSK3eDr5Pg07mSuHfqtB_WYG_eoYRBiS1D0X9apqAVayjBD090ihx45aaWye2uFHs=w902-h601-no)

   Luego se debe editar esta propiedad y agregar las referencias a las carpetas **lib** de cada una de las librerías descargadas, 
   como se muestra en la siguiente imagen:

   ![Additional Library Directories](https://lh3.googleusercontent.com/DcQvSxAcVhnUIxUbyCtRHm-SmlWOjH1cpg11C6LeQC_XJeprbWsrw89yGBgDC3RLl6wXne4eUhjujNxbrXJTYD66njW06X8aXAfTIFDDf7pgqT_FdWO1UR_in1usocukZI10L3HYMwPXJoB8R7im41a9m5CmwtcpfY79kbCzYxiRMGtc66pVPoSaCzj09Wq1HMjnjbpqO17RQU9s-u7RAtxxUMsxG1o-dkZ1VU4BBiDGOFwtvDsVFbKqiO1JjQ28QmWxSVgJDzNlKhl2tP_7oy9S0u6ka1rGQtsL8qHtVF460lxTC6oCtc4rJeWrzg1j8VvTZjPMnnXl_c7ON2rONd6cNqfX_b_vFi8cGE7S_F9Z4Ke5xFTA5D8KZ6mBa_QrfH0KSySzKxUjG1iJtzpVr0jGvLvyzVAJ0-0QQKUo6iB7tylSeO7WjZ5W5969twdjIfLyLa7VC57Uh6rYGXHHb0QqJzlu4FffjHLfTFcx5jplogxS9Ay1xmNG2Pmv2uU2hfTadVKV0NPH87jQ3vzggHmL7BrJAD0YiJywMwJhrTUJyt1KSfeOxeq_wFLMJkmeNiNASPfKJ3vTM5nrnzbPaByUvkZ3iihAR3EmcCps0omi6ao=w482-h351-no)

3. En la sección **Build**, sub sección **Linker** se debe modificar la propiedad **Additional Options** y agregar las siguientes 
   opciones: **-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm**

> **Nota: ** si ocurre algún problema con la puesta en marcha de SDL se recomienda revisar los tutoriales e instalación de SDL2 en el 
> sitio de [Lazy Foo' Productions](http://lazyfoo.net/tutorials/SDL/)
