#include "lcd.h"

void WriteCommandToLCD(unsigned char Command)  
{
	LCD_RS = 0;				  // It is a command
	LCD_PORT = Command;		  // Write value on data bus
	
	LCD_E = 1;                // Give a pulse on E pin
	__delay_us(E_Delay);      // so that LCD can latch the
	LCD_E = 0;                // data from data bus
	__delay_us(E_Delay); 	
}

void WriteDataToLCD(unsigned char LCDChar)  
{
	LCD_RS = 1;				  // It is data
	LCD_PORT = LCDChar;		  // Write value on data bus
	
	LCD_E = 1;                // Give a pulse on E pin
	__delay_us(E_Delay);      // so that LCD can latch the
	LCD_E = 0;                // data from data bus
	__delay_us(E_Delay); 
}


void InitLCD(void)
{ 
	// Firstly make all pins output
	LCD_E  		 	 = 0;   // E  = 0
	LCD_RS  	 	 = 0;   // RS = 0
	LCD_Data_Bus 	 = 0;  	// Data bus = 0	
	LCD_Data_Bus_Dir = 0;   // Make Output

  ///////////////// Reset process from datasheet //////////////
   __delay_ms(40);
	WriteCommandToLCD(0x30);  

   __delay_ms(6);
	WriteCommandToLCD(0x30);  

   __delay_us(300);
	WriteCommandToLCD(0x30);

   __delay_ms(2);
  /////////////// Reset Process End ////////////////
	WriteCommandToLCD(0x38);    //two lines - 8bit interface - standard font size
	WriteCommandToLCD(0x0c);    //display on,cursor off,blink off
	WriteCommandToLCD(0x01);    //clear display
	WriteCommandToLCD(0x06);    //entry mode, set increment
}



void ClearLCDScreen(void)       // Clear the Screen and return cursor to zero position
{
	WriteCommandToLCD(0x01);    // Clear the screen
	__delay_ms(4);              // Delay for cursor to return at zero position
}

void TurnOff(void){
    WriteCommandToLCD(0x08);    // Lcd OFF
	__delay_us(40); 
}
void TurnOn(void){
    WriteCommandToLCD(0x0F);    // Lcd ON with blinking cursor
	__delay_us(40); 
}

void Write3StringToLcd(char* str, char length){
    for (char i = 0; i < length; i++){
        WriteDataToLCD(str[i]);
        __delay_us(53);
    }
}

void SetPosition(unsigned char row, unsigned char column){
    unsigned char command = 0x80;
    if (row){
        column |= 0x40;
    }
    command |= column;
    WriteCommandToLCD(command);
    __delay_us(40);
}
