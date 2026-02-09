/////////////////////////////////////// 
// Created own header file, 
// not sure if this is supposed 
// to be provided by the assignment 
// or if it's part of the assignment
///////////////////////////////////////

#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

void assignment_1( void );
void gpio_d_set_pin_input( int pin, int mode );
void gpio_d_set_pin_output( int pin, int mode );
void gpio_d_set_pin_high( int pin );
void gpio_d_set_pin_low( int pin );
int get_keyboard_button( void );

#endif