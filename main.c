/* 
 * File:   main.c
 * Author: marko
 *
 * Created on May 23, 2015, 1:08 PM
 */


#include "lcd.h"
#include "speed.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile unsigned char overflowCounter = 0;
static unsigned int lastClock = 0;
static unsigned char speed = 0;//first bit is previous value
static char speedText[4];
static float passedKms = 0.f;

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
    OPTION_REG = 0b00000111;
//    OPTION_REG &= 0xD7;//set internal cycle clock (port 5)
//    OPTION_REG |= 0x07;//set prescaler to 256
    INTCON = 0b10100000;     
    speedText[2] = 'K';
    speedText[3] = 'm';
    //speedText[4] = 'h';
        
    __delay_ms(40);
    
    InitLCD();
//    TurnOff();
//    TurnOn();
    ClearLCDScreen();
    
    while (1){        
        if (PORTAbits.RA2){
            lastClock = TMR0;                            
            if (!(speed & 0x80)){ //if previous value is 0
                T0IE = 0;
                lastClock = lastClock + (overflowCounter * 0xFF);
                overflowCounter = 0;
                TMR0 = 0x01;
                T0IE = 1;
                ClearLCDScreen();
                PORTAbits.RA1 = 1;
                speed = caclculateSpeed((float)lastClock / 9765.625f); //hardcoded is 10M clock per second / 4 with prescaler 256;
                //passedKms += (WHEEL_2RPI / 1000.f);
                if (speed > 99)
                    speed = 99;                
                char index = 2;
                while (speed > 0){
                    index--;
                    speedText[index] = (speed % 10) + 0x30;
                    speed /= 10;
                }                       
                SetPosition(0x00, 0x06);
                Write3StringToLcd(speedText, 4);                
                speedText[0] = 0x30;
                speedText[1] = 0x30;
            }
            speed |= 0x80; // set previous value to 1;
        }
        else{                        
            PORTAbits.RA1 = 0;
            speed &= 0x7F; //set previous value to 0;
        }        
    }
    return (0);
}

