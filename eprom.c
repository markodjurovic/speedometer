#include "eprom.h"
#include "config.h"

unsigned short getShortFromMemory(){    
    unsigned short retVal = EEPROM_READ(START_EEPROM_ADDRESS + 0x01);
    retVal <<= 8;
    retVal |= EEPROM_READ(START_EEPROM_ADDRESS);
    return retVal;
}

void putShortToMemory(unsigned short val){
    unsigned char lowBits = 0x00 | val;
    unsigned char highBits = val >> 8;
    EEPROM_WRITE(START_EEPROM_ADDRESS, lowBits);
    EEPROM_WRITE(START_EEPROM_ADDRESS + 0x01, highBits);
}
