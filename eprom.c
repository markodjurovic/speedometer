#include "eprom.h"
#include "config.h"

unsigned short getShortFromMemory(char address){    
    unsigned short retVal = EEPROM_READ(address + 0x01);
    retVal <<= 8;
    retVal |= EEPROM_READ(address);
    return retVal;
}

void putShortToMemory(char address, unsigned short val){
    unsigned char lowBits = 0x00 | val;
    unsigned char highBits = val >> 8;
    EEPROM_WRITE(START_EEPROM_ADDRESS, lowBits);
    EEPROM_WRITE(START_EEPROM_ADDRESS + 0x01, highBits);
}
