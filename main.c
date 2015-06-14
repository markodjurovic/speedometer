/* 
 * File:   main.c
 * Author: marko
 *
 * Created on May 23, 2015, 1:08 PM
 */


#include "lcd.h"
#include "speed.h"
#include "eprom.h"
#include "text.h"
#include <float.h>
#include <string.h>
#include <limits.h>

volatile unsigned char overflowCounter = 0;

void interrupt inter(void){
    if (T0IF){
        overflowCounter++;
        T0IF = 0;
        TMR0 = 0x00;
    }
}

int main(int argc, char** argv) {            
    PORTB = 0x00;
    PORTA = 0x00;
    TRISB = 0x00; //all pins output
    TRISA = 0x04; //all output but A2
    OPTION_REG = 0b00000111; //set prescaler to 256
    INTCON = 0b10100000; 
    CMCON = 0x07;
    WREN = 1;
    
    unsigned int lastClock = 0;
    char speedText[7];
    char passedKmsText[5];
    float passedKms = 0.f;
    char overAllKmsText[5];
    
    speedText[3] = 'K';
    speedText[4] = 'm';
    speedText[5] = '/';
    speedText[6] = 'h';    
    passedKmsText[3] = 'K';
    passedKmsText[4] = 'm';
    overAllKmsText[3] = 'K';
    overAllKmsText[4] = 'm';
    
    char continiusZero = 1;
    unsigned char speed = 0;
    unsigned short oa = getShortFromMemory(START_EEPROM_ADDRESS);
    if (oa > 999)
        oa = 0x00;
    float overAllFloat = (float)oa;
    
    unsigned short long zeroCycle = 0x000000;
    char toLongInZero = 0;
    __delay_ms(40);
    
    InitLCD();
    //ClearLCDScreen();
    
    while (1){                
        if (PORTAbits.RA2){            
            if (continiusZero){ //if previous value is 0
                lastClock = TMR0;
                T0IE = 0;
                if (overflowCounter < 255)
                    lastClock = lastClock + (overflowCounter * 0xFF);
                else
                    lastClock = UINT_MAX;
                overflowCounter = 0;
                TMR0 = 0x01;
                T0IE = 1;
                float wheelRoute = WHEEL_2RPI / 1000.f;
                //ClearLCDScreen();
                
                PORTAbits.RA1 = 1;                              
                
                speed = caclculateSpeed((float)lastClock / 9765.625f); //hardcoded is 10M clock per second / 4 with prescaler 256;                
                
                if (speed > 99)
                    speed = 99;
                setTextUChar(speedText, 3, speed);
                SetPosition(0x00, 0x05);
                Write3StringToLcd(speedText, 7);
                
                passedKms += wheelRoute;
                unsigned short passedKmsChar = (unsigned short)passedKms;                
                setTextUShort(passedKmsText, 3, passedKmsChar);
                SetPosition(0x01, 0x01);
                Write3StringToLcd(passedKmsText, 5);
                
                overAllFloat += wheelRoute;
                if (overAllFloat > 999.0){
                    overAllFloat = 0.f;
                }
                unsigned short overAllKms = (unsigned short)overAllFloat;                
                
                putShortToMemory((char)START_EEPROM_ADDRESS, overAllKms);
                setTextUShort(overAllKmsText, 3, overAllKms);
                SetPosition(0x01, 0x0A);
                Write3StringToLcd(overAllKmsText, 5);                                           
            }            
            continiusZero = 0x00;
            toLongInZero = 0x00;
            zeroCycle = 0x00;            
        }
        else{            
            PORTAbits.RA1 = 0;            
            if (!toLongInZero){                
                if (continiusZero && zeroCycle >= USHRTLONG_MAX / 20){
                    //ClearLCDScreen();
                    speed = 0x00;
                    setTextUChar(speedText, 3, speed);
                    SetPosition(0x00, 0x05);
                    Write3StringToLcd(speedText, 7);
                    toLongInZero = 1;
                    zeroCycle = 0;
                }                                
            }
            zeroCycle++;
            continiusZero = 1;
        }        
    }
    return (0);
}

