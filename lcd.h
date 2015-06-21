#ifndef __LCD_H
#define __LCD_H

#include "config.h"       


// Function Declarations
void writeCommandToLCD(unsigned char);
void writeDataToLCD(char);
void initLCD(void);
void clearLCDScreen(void);
void turnOff(void);
void turnOn(void);
void writeStringToLcd(char* str, char length);
void setPosition(unsigned char row, unsigned char column);
#endif