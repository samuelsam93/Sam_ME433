/* 
 * File:   oled.c
 * Author: SHAM
 *
 * Created on April 13, 2015, 11:22 PM
 */
#include <xc.h> // processor SFR definitions
#include <sys/attribs.h> // __ISR macro
#include <stdio.h>
#include <stdlib.h>
#include "i2c_display.h"
#include "i2c_master_int.h"
#include "SAM32_init.h"



int startrow = 28;
int startcol = 1;
int num = 1337;
int size = 50;

void main() {
    SAM32_startup();
    display_init();
    LATBINV = 0b10000000;

    char message[size];
    //display_pixel_set(20, 30, 1);
    //display_pixel_set(30, 40, 1);
    //display_draw();
    sprintf(message, "It's more than just good. It's good enough!");
    display_message(startrow, startcol, message);
    //display_draw();
    while(1);
}





