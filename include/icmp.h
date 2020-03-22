#ifndef ICMP
#define ICMP
//********************************************************************************************
//
// File : icmp.h implement for Internet Control Message Protocol
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

//********************************************************************************************
//
// Prototype function
//
//********************************************************************************************
unsigned char icmp_send_reply ( unsigned char *rxtx_buffer, unsigned short length, unsigned char *dest_mac, unsigned char *dest_ip );
void IcmpSendUnreachable(unsigned char *buffer, const unsigned char *remoteMac, const unsigned char *remoteIp, unsigned short ipTotalLength);
#endif
