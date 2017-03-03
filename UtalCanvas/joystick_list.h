/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   joystick_list.h
 * Author: Pablo Rojas
 *
 * Created on 3 de marzo de 2017, 15:12
 */

#ifndef JOYSTICK_LIST_H
#define JOYSTICK_LIST_H

#include <stdbool.h>
#include "structures.h"

#ifdef __cplusplus
extern "C" {
#endif

    
    bool register_joystick(int which, JoystickData* jdata);
    
    JoystickData* get_joystick_data( int which);
    JoystickNode* get_joystick(int which);
    bool remove_joystick(int which);
    
    bool __joystick_list_exists( int wich );
    JoystickNode* __remove_joystick_node(JoystickNode* node);
    void __free_joystick_node(JoystickNode* node);
    



#ifdef __cplusplus
}
#endif

#endif /* JOYSTICK_LIST_H */

