#ifndef TCP_H_
#define TCP_H_


/*
 * TCP.h
 *
 * Created: 7/10/2016 12:22:47 PM
 *  Author: ASUS
 */ 

/*

[Ethernet Frame[IP packet[TCP Data]]]

Data to be sent --->> TCP format data --->> Payload of IP Packet --->> Payload of Ethernet frame --->> Transmit through wire

*/

#include "common.h"
#include "checksum.h"
#include "ENC_Ethernet.h"

int TCP_check(char data[], int length);
void Make_TCP_Packet(char raw_data[], int data_length, bool SYN, bool ACK, bool psh);

extern bool connected;

#endif
