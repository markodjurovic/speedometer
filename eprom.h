/* 
 * File:   eprom.h
 * Author: marko
 *
 * Created on June 13, 2015, 1:21 AM
 */

#ifndef EPROM_H
#define	EPROM_H

unsigned short getShortFromMemory(char address);
void putShortToMemory(char address, unsigned short val);

#endif	/* EPROM_H */

