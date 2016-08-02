
/** 
 * File:   utalcanvas_list.h
 * Author: Pablo Ignacio Rojas Valdés (pabrojas@utalca.cl)
 * 
 * Created on 13 de junio de 2016
 */

#ifndef UTALCANVAS_LIST_H
#define UTALCANVAS_LIST_H

#include "utalcanvas_definitions.h"
#include "utalcanvas_structures.h"

#ifdef __cplusplus
extern "C" {
#endif

    UtalCanvasNode* UtalCanvasListGetFirst();
    int UtalCanvasListAddElement( UtalCanvasElementType type, void* data );
    void UtalCanvasListRemoveElementByIndex(int index);
    void UtalCanvasListRemoveElementByTag(char tag[TAG_NAME_LENGTH]);
    void UtalCanvasListRemoveAllElement();
    void UtalCanvasListMoveElementByIndex(int index, int dx, int dy);
    void UtalCanvasListFreeResources(UtalCanvasNode* node);
    
    void UtalCanvasListMoveShow();

#ifdef __cplusplus
}
#endif

#endif /* UTALCANVAS_LIST_H */

