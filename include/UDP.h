/*
 * UDP.h
 *
 * Created: 7/30/2016 10:28:58 AM
 *  Author: ASUS
 */ 


#ifndef UDP_H_
#define UDP_H_

#include "common.h"
#include "IP.h"

int UDP_check(char data[], int length);
//	Returns the length of necessary data in the UDP packet. If the packet is not valid, returns 0
//	rewrite the data[] array with only the main data beneath the UDP packet.
// length is the length of the incoming frame

bool UDP_send(char data[], uint16_t length);
// number = serial number of the packet
// returns true or false depending on success.

#endif /* UDP_H_ */
