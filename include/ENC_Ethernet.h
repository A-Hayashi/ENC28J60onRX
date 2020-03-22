#ifndef ENC_ETHERNET_H_
#define ENC_ETHERNET_H_

/*

Library file for SPI ENC memory.
Written by Shadman Sakib
2ra Technology Ltd.
 */ 

/*

Needs the following libraries to work properly:

#define F_CPU 

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#include "hd44780_settings.h"
#include "hd44780.h"
#include "hd44780.c"

*/
#include "common.h"

void ENC_MasterInit(void);
void ENC_init();
bool ENC_Transmit(char data[], uint16_t data_length, char protocol);  // returns True if successful, False if not.
int ENC_Receive(char data[]);  // Returns the length of received data, Fill the argument array with that data
char NewPacket();

extern char MAC[6];
extern char Remote_mac[6];
extern char Dest_IP[4];
extern char My_IP[4];

#endif

