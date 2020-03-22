#ifndef ENC28J60_H
#define ENC28J60_H
//********************************************************************************************
//
// File : enc28j60.h Microchip ENC28J60 Ethernet Interface Driver
//
//********************************************************************************************
//
// Copyright (C) 2007
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
// This program is distributed in the hope that it will be useful, but
//
// WITHOUT ANY WARRANTY;
//
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 51
// Franklin St, Fifth Floor, Boston, MA 02110, USA
//
// http://www.gnu.de/gpl-ger.html
//
//********************************************************************************************

#define MAC_ADDRESS_SIZE 6
#define NET_BUFFER_SIZE 400

#define MAX_TX_BUFFER	NET_BUFFER_SIZE
#define MAX_RX_BUFFER	NET_BUFFER_SIZE

extern const unsigned char avr_mac[MAC_ADDRESS_SIZE];

// functions
void enc28j60_init();
void enc28j60_packet_send ( unsigned char *buffer, unsigned short length);
unsigned short enc28j60_packet_receive ( unsigned char *rxtx_buffer, unsigned short max_length );

#endif
