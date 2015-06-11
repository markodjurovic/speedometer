#ifndef __LCD_H
#define __LCD_H

#include "config.h"       


// Function Declarations
void WriteCommandToLCD(unsigned char);
void WriteDataToLCD(char);
void InitLCD(void);
void ClearLCDScreen(void);
void TurnOff(void);
void TurnOn(void);
void Write3StringToLcd(char* str, char length);
void SetPosition(unsigned char row, unsigned char column);
#endif