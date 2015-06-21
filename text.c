#include "text.h"

void setTextUChar(char* buffer, char numOfChars, unsigned char value){
    for (char index = 0; index < numOfChars; index++){
        buffer[numOfChars - 1 - index] = (value % 10) + 0x30;                    
        value /= 10;
    }
}

void setTextShort(char* buffer, char numOfChars, unsigned short value){
    for (char index = 0; index < numOfChars; index++){
        buffer[numOfChars - 1 - index] = (value % 10) + 0x30;                    
        value /= 10;
    }
}
