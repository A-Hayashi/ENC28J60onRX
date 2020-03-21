#ifndef IP_H_
#define IP_H_

/*
 * TCP_IP.h
 *
 * Created: 7/2/2016 12:56:57 PM
 *  Author: ASUS
 */ 

#include "common.h"
	
void Make_IP_packet(char raw_data[], uint16_t data_length, char Destination_IP[], char My_IP[], char protocol, char result[]);		// Rearranges the input array and put the headers

#endif
