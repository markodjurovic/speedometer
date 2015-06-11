/* 
 * File:   config.h
 * Author: marko
 *
 * Created on May 23, 2015, 1:14 PM
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG
#define _XTAL_FREQ 10000000


#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF      // Watchdog Timer (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)


// Define Pins
#define LCD_E    		RA0   	// Enable pin for LCD
#define LCD_RS  		RA3   	// RS pin for LCD
#define LCD_Data_Bus    PORTB 	// Data bus for LCD

// Define Pins direction registrers
#define LCD_E_Dir      		  TRISA0
#define LCD_RS_Dir     		  TRISA3
#define LCD_Data_Bus_Dir      TRISB


// Constants
#define E_Delay       500
#define LCD_PORT PORTB
#define WHEEL_2RPI 1.67572552142f

#endif
