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
#include <limits.h>

volatile unsigned char overflowCounter = 0U;

void interrupt inter(void){
    if (T0IF){
        overflowCounter++;
        T0IF = 0;
        TMR0 = 0x00;
    }
}

char getAvg(unsigned char* array){
    short avg = 0;
    for (char i = 0; i < TEXT_OUT_CYCLUS_PLUS_ONE; i++){
        avg += array[i];
    }
    avg /= TEXT_OUT_CYCLUS_PLUS_ONE;
    return (char)avg;
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
    
    unsigned int lastClock = 0U;
    unsigned int lastTextClock = 0U;
    char speedText[7];
    char passedKmsText[5];
    float passedKms = 0.f;
    char overAllKmsText[5];
    bool writeText = 1;
    char magnetPassingCounter = 0;
    unsigned char lastNSpeeds[TEXT_OUT_CYCLUS_PLUS_ONE];
    
    speedText[3] = 'K';
    speedText[4] = 'm';
    speedText[5] = '/';
    speedText[6] = 'h';    
    passedKmsText[3] = 'K';
    passedKmsText[4] = 'm';
    overAllKmsText[3] = 'K';
    overAllKmsText[4] = 'm';
    
    char continiusZero = 1;
    unsigned char speed = 0U;
    unsigned short overAllKms = getShortFromMemory();
//    if (overAllKms > 999)
//        overAllKms = 0x00;    
    float overAllFloat = (float)overAllKms;
    unsigned short passedKmsChar = 0U;
    
    short long zeroCycle = 0x000000;
    char toLongInZero = 0;
    __delay_ms(40);
    
    initLCD();   
    
    while (1){                
        if (PORTAbits.RA2){            
            if (continiusZero){ //if previous value is 0
                lastClock = TMR0;
                T0IE = 0;
                if (overflowCounter < 255)
                    lastClock = lastClock + (overflowCounter * 0xFF);
                else
                    lastClock = UINT_MAX;
                overflowCounter = 0U;
                TMR0 = 0x01;
                T0IE = 1;
                
                lastTextClock += lastClock;
                
                PORTAbits.RA1 = 1;                              
                
                speed = caclculateSpeed((float)lastClock / 9765.625f); //hardcoded is 10M clock per second / 4 with prescaler 256
                
                passedKms += WHEEL_2RPI;
                if (passedKms > 999.f){
                    passedKms = 0.f;
                }
                passedKmsChar = (unsigned short)passedKms;
                
                overAllFloat += WHEEL_2RPI;
                if (overAllFloat > 999.0){
                    overAllFloat = 0.f;
                }
                overAllKms = (short)overAllFloat;
                putShortToMemory(overAllKms);
                magnetPassingCounter++;
                if (magnetPassingCounter == TEXT_OUT_CYCLUS_PLUS_ONE){
                    magnetPassingCounter = 0;
                }
                lastNSpeeds[magnetPassingCounter] = speed;
                if (lastTextClock > 9765){                    
                    speed = getAvg(lastNSpeeds);
                    writeText = 1;                    
                    lastTextClock = 0;
                }
            }            
            continiusZero   = 0x00;
            toLongInZero    = 0x00;
            zeroCycle       = 0x00;            
        }
        else{            
            PORTAbits.RA1 = 0;            
            if (!toLongInZero){                
                if (continiusZero && zeroCycle >= 838860){//short long max / 10
                    speed = 0x00;
                    toLongInZero = 1;
                    zeroCycle = 0;
                    writeText = 1;
                }                                
            }
            zeroCycle++;
            continiusZero = 1;
        }
        if (writeText){
            setTextShort(overAllKmsText, 3, overAllKms);
            setPosition(1, 10);
            writeStringToLcd(overAllKmsText, 5);
            
            setTextShort(passedKmsText, 3, passedKmsChar);
            setPosition(1, 1);
            writeStringToLcd(passedKmsText, 5);
            
            setTextUChar(speedText, 3, speed);
            setPosition(0, 5);
            writeStringToLcd(speedText, 7);
        }
        writeText = 0;
    }
    return (0);
}

