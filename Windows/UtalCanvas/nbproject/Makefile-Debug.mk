#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/utalcanvas.o \
	${OBJECTDIR}/utalcanvas_colors.o \
	${OBJECTDIR}/utalcanvas_list.o \
	${OBJECTDIR}/utalcanvas_utils.o \
	${OBJECTDIR}/utalcanvas_window.o


# C Compiler Flags
CFLAGS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/C/SDL/SDL2-2.0.4/i686-w64-mingw32/lib -L/C/SDL/SDL2_image-2.0.1/i686-w64-mingw32/lib -L/C/SDL/SDL2_mixer-2.0.1/i686-w64-mingw32/lib -L/C/SDL/SDL2_ttf-2.0.14/i686-w64-mingw32/lib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libUtalCanvas.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libUtalCanvas.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libUtalCanvas.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -shared

${OBJECTDIR}/utalcanvas.o: utalcanvas.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/C/SDL/SDL2-2.0.4/i686-w64-mingw32/include/SDL2 -I/C/SDL/SDL2_image-2.0.1/i686-w64-mingw32/include/SDL2 -I/C/SDL/SDL2_mixer-2.0.1/i686-w64-mingw32/include/SDL2 -I/C/SDL/SDL2_ttf-2.0.14/i686-w64-mingw32/include/SDL2  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utalcanvas.o utalcanvas.c

${OBJECTDIR}/utalcanvas_colors.o: utalcanvas_colors.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/C/SDL/SDL2-2.0.4/i686-w64-mingw32/include/SDL2 -I/C/SDL/SDL2_image-2.0.1/i686-w64-mingw32/include/SDL2 -I/C/SDL/SDL2_mixer-2.0.1/i686-w64-mingw32/include/SDL2 -I/C/SDL/SDL2_ttf-2.0.14/i686-w64-mingw32/include/SDL2  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utalcanvas_colors.o utalcanvas_colors.c

${OBJECTDIR}/utalcanvas_list.o: utalcanvas_list.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/C/SDL/SDL2-2.0.4/i686-w64-mingw32/include/SDL2 -I/C/SDL/SDL2_image-2.0.1/i686-w64-mingw32/include/SDL2 -I/C/SDL/SDL2_mixer-2.0.1/i686-w64-mingw32/include/SDL2 -I/C/SDL/SDL2_ttf-2.0.14/i686-w64-mingw32/include/SDL2  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utalcanvas_list.o utalcanvas_list.c

${OBJECTDIR}/utalcanvas_utils.o: utalcanvas_utils.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/C/SDL/SDL2-2.0.4/i686-w64-mingw32/include/SDL2 -I/C/SDL/SDL2_image-2.0.1/i686-w64-mingw32/include/SDL2 -I/C/SDL/SDL2_mixer-2.0.1/i686-w64-mingw32/include/SDL2 -I/C/SDL/SDL2_ttf-2.0.14/i686-w64-mingw32/include/SDL2  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utalcanvas_utils.o utalcanvas_utils.c

${OBJECTDIR}/utalcanvas_window.o: utalcanvas_window.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/C/SDL/SDL2-2.0.4/i686-w64-mingw32/include/SDL2 -I/C/SDL/SDL2_image-2.0.1/i686-w64-mingw32/include/SDL2 -I/C/SDL/SDL2_mixer-2.0.1/i686-w64-mingw32/include/SDL2 -I/C/SDL/SDL2_ttf-2.0.14/i686-w64-mingw32/include/SDL2  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utalcanvas_window.o utalcanvas_window.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libUtalCanvas.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
