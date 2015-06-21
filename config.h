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


#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


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
#define WHEEL_2RPI 0.00135653970782 //in kms 17 inch
#define ZERO_SPEED_INTERVAL 6
#define START_EEPROM_ADDRESS 0x0A
#define TEXT_OUT_CYCLUS 5
#define TEXT_OUT_CYCLUS_PLUS_ONE 6

#define bool char

#endif
