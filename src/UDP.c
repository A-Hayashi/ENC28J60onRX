/*
 * UDP.h
 *
 * Created: 7/30/2016 10:28:58 AM
 *  Author: ASUS
 */ 
#include "UDP.h"

#define UDP_HEADER_SISE	(8)

#define PORTH	0x00
#define PORTL	0x64		// PORT 100

int UDP_check(char data[], int length)
{
	char *etherHeader = (char *)data[0];
	char *ipHeader = (char *)data[ETHER_HEADER_SIZE];
	char *udpHeader = (char *)data[ETHER_HEADER_SIZE + IP_HEADER_SISE];
	char *segment = (char *)data[ETHER_HEADER_SIZE + IP_HEADER_SISE + UDP_HEADER_SISE];

	if (length<(ETHER_HEADER_SIZE + IP_HEADER_SISE + UDP_HEADER_SISE)){
		return 0;
	}else if ((etherHeader[12]==0x08)&&(etherHeader[13]==0x00)&&
			(ipHeader[9]==0x11)&&
			(ipHeader[16]==My_IP[0])&&(ipHeader[17]==My_IP[1])&&(ipHeader[18]==My_IP[2])&&(ipHeader[19]==My_IP[3])&&
			(udpHeader[2]== PORTH)&&(data[3]==PORTL)){
		uint16_t data_length = (udpHeader[4]<<8) | ( 0xFF & udpHeader[5]);
		int x;

		for (x = 0; x<data_length; x++)
		{
			data[x]=segment[x];
		}
		return data_length;
	}else{
		return 0;
	}
}

bool UDP_send(char data[], uint16_t length)
{
	uint16_t total_data;
	uint16_t x;
	
	char *ipHeader = (char *)data[0];
	char *udpHeader = (char *)data[IP_HEADER_SISE];
	char *segment = (char *)data[IP_HEADER_SISE + UDP_HEADER_SISE];

	for (x = 0;x<length;x++)
	{
		segment[x]=data[x];
	}	
	data[x]= 0x00;			//Extra one byte for CRC checking
	total_data = length;	// For data length field
	
	//	UDP header starts
	udpHeader[0]=0xF6;			//送信元ポート
	udpHeader[1]=0x30;			//送信先ポート
	udpHeader[2]=PORTH;			//送信先ポート
	udpHeader[3]=PORTL;			//送信先ポート
	udpHeader[4]=((total_data>>8) & 0xFF);	//セグメント長
	udpHeader[5]=(total_data & 0xFF);		//セグメント長
	udpHeader[6]=0x00;			//チェックサム
	udpHeader[7]=0x00;			//チェックサム

	//	UDP header finish
	total_data += UDP_HEADER_SISE;

	//	Transmit
	return	IP_Transmit(ipHeader, total_data, IP_PROTOCOL_UDP);
}
