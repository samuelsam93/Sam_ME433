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
#include "accel.h"


short accels[3]; // accelerations for the 3 axes
short mags[3]; // magnetometer readings for the 3 axes
short temp;
int startrow = 28;
int startcol = 1;
char accels_char[50];
char mags_char[50];
char temp_char[50];
int x_mag, y_mag, x_len, y_len;
char xmag_char, ymag_char;

void main(){
    SAM32_startup();
    display_init();
    acc_setup();
    LATBINV = 0b10000000;
    while(1){
    // read the accelerometer from all three axes

    // the accelerometer and the pic32 are both little endian by default (the lowest address has the LSB)

    // the accelerations are 16-bit twos compliment numbers, the same as a short
    acc_read_register(OUT_X_L_A, (unsigned char *) accels, 6);
    //sprintf(accels_char, "a: %d %d %d", accels[0], accels[1], accels[2]);

    // need to read all 6 bytes in one transaction to get an update.
    acc_read_register(OUT_X_L_M, (unsigned char *) mags, 6);
    //sprintf(mags_char, "mags: %d %d %d", mags[0], mags[1], mags[2]);

    // read the temperature data. Its a right justified 12 bit two's compliment number
    acc_read_register(TEMP_OUT_L, (unsigned char *) &temp, 2);
    //sprintf(temp_char, "temp: %d", temp);

//    display_message(10, 1, accels_char);
//    display_message(30, 1, mags_char);
//    display_message(50, 1, temp_char);
    x_mag = accels[0];
    y_mag = accels[1];
    x_len = x_mag/(-275);
    y_len = y_mag/(-550);
    //display_clear();
    display_bars(x_len, 0);
    display_bars(y_len, 1);
    display_clear();
//    
//        display_clear();
//        display_bars(200, 0);
//        display_bars(200, 1);
//    
    }

}


// HW4 main() function
//int startrow = 28;
//int startcol = 1;
//int num = 1337;
//int size = 50;
//
//void main() {
//    SAM32_startup();
//    display_init();
//    LATBINV = 0b10000000;
//
//    char message[size];
//    //display_pixel_set(20, 30, 1);
//    //display_pixel_set(30, 40, 1);
//    //display_draw();
//    sprintf(message, "It's more than just good. It's good enough!");
//    display_message(startrow, startcol, message);
//    //display_draw();
//    while(1);
//}
//