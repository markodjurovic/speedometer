#include "lcd.h"

void writeCommandToLCD(unsigned char Command)  
{
	LCD_RS = 0;				  // It is a command
	LCD_PORT = Command;		  // Write value on data bus
	
	LCD_E = 1;                // Give a pulse on E pin
	__delay_us(E_Delay);      // so that LCD can latch the
	LCD_E = 0;                // data from data bus
	__delay_us(E_Delay); 	
}

void writeDataToLCD(unsigned char LCDChar)  
{
	LCD_RS = 1;				  // It is data
	LCD_PORT = LCDChar;		  // Write value on data bus
	
	LCD_E = 1;                // Give a pulse on E pin
	__delay_us(E_Delay);      // so that LCD can latch the
	LCD_E = 0;                // data from data bus
	__delay_us(E_Delay); 
}


void initLCD(void)
{ 
	// Firstly make all pins output
	LCD_E  		 	 = 0;   // E  = 0
	LCD_RS  	 	 = 0;   // RS = 0
	LCD_Data_Bus 	 = 0;  	// Data bus = 0	
	LCD_Data_Bus_Dir = 0;   // Make Output

  ///////////////// Reset process from datasheet //////////////
   __delay_ms(40);
	writeCommandToLCD(0x30);  

   __delay_ms(6);
	writeCommandToLCD(0x30);  

   __delay_us(300);
	writeCommandToLCD(0x30);

   __delay_ms(2);
  /////////////// Reset Process End ////////////////
	writeCommandToLCD(0x38);    //two lines - 8bit interface - standard font size
	writeCommandToLCD(0x0c);    //display on,cursor off,blink off
	writeCommandToLCD(0x01);    //clear display
	writeCommandToLCD(0x06);    //entry mode, set increment
}



void clearLCDScreen(void)       // Clear the Screen and return cursor to zero position
{
	writeCommandToLCD(0x01);    // Clear the screen
	__delay_ms(4);              // Delay for cursor to return at zero position
}

void turnOff(void){
    writeCommandToLCD(0x08);    // Lcd OFF
	__delay_us(40); 
}
void turnOn(void){
    writeCommandToLCD(0x0F);    // Lcd ON with blinking cursor
	__delay_us(40); 
}

void writeStringToLcd(char* str, char length){
    for (char i = 0; i < length; i++){
        writeDataToLCD(str[i]);
        __delay_us(53);
    }
}

void setPosition(unsigned char row, unsigned char column){
    unsigned char command = 0x80;
    if (row){
        column |= 0x40;
    }
    command |= column;
    writeCommandToLCD(command);
    __delay_us(40);
}
