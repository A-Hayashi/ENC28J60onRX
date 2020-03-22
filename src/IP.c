/*
 * TCP_IP.h
 *
 * Created: 7/2/2016 12:56:57 PM
 *  Author: ASUS
 */ 

#include "IP.h"

	
static char TCP_IP_packet[1600];
// Change it according to your need

static void version_and_header();
static void Type_of_service();
static void Total_length(uint16_t length_of_data);
static void Fragment_number();
static void Flag_and_fragment_offset();
static void Time_to_live();
static void Protocol();
static void IP_Checksum();
static void Source_IP(char My_IP[]);
static void Target_IP(char Destination_IP[]);

void Make_IP_packet(char raw_data[], uint16_t data_length, char Destination_IP[],char My_IP[], char protocol, char result[])
{
	uint16_t x;

	version_and_header();
	Type_of_service();
	Total_length(data_length);
	Fragment_number();
	Flag_and_fragment_offset();
	Time_to_live();
	Protocol();
	IP_Checksum();
	Source_IP(My_IP);
	Target_IP(Destination_IP);
	
	for (x = 0;x<data_length;x++)
	{
		TCP_IP_packet[20+x] = raw_data[x];
	}
	
	for (x = 0;x<(data_length+20);x++)
	{
		result[x] = TCP_IP_packet[x];
	}
	
	
}


static void version_and_header()
{
	TCP_IP_packet[0]= 0x45;
}

static void Type_of_service()
{
	TCP_IP_packet[1]= 0x00;
}

static void Total_length(uint16_t length_of_data)
{
	length_of_data+=20;
	
	TCP_IP_packet[2]= (length_of_data>>8);
	TCP_IP_packet[3] = (length_of_data & 0xFF);
}

static void Fragment_number()						//	Give a Random number for small data.
{
	TCP_IP_packet[4]= 0x00;
	TCP_IP_packet[5] = 0x00;
}

static void Flag_and_fragment_offset()
{
	TCP_IP_packet[6]= 0x40;
	TCP_IP_packet[7] = 0x00;
}

static void Time_to_live()
{
	TCP_IP_packet[8]= 0x80;
}

static void Protocol()
{
	TCP_IP_packet[9]= 0x06;					//	For TCP. Change will occure for UDP and others.
}

static void IP_Checksum()
{
	TCP_IP_packet[10]= 0x00;
	TCP_IP_packet[11]= 0x25;
}

static void Source_IP(char My_IP[])
{
	TCP_IP_packet[12]= My_IP[0];
	TCP_IP_packet[13]= My_IP[1];
	TCP_IP_packet[14]= My_IP[2];
	TCP_IP_packet[15]= My_IP[3];
}

static void Target_IP(char Destination_IP[])
{
	TCP_IP_packet[16]= Destination_IP[0];
	TCP_IP_packet[17]= Destination_IP[1];
	TCP_IP_packet[18]= Destination_IP[2];
	TCP_IP_packet[19]= Destination_IP[3];
}
