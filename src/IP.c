/*
 * TCP_IP.h
 *
 * Created: 7/2/2016 12:56:57 PM
 *  Author: ASUS
 */ 

#include "IP.h"
	
// Change it according to your need

bool IP_Transmit(char raw_data[], uint16_t data_length, char protocol)
{
	uint16_t checksum_value;

	char *TCP_IP_packet = &raw_data[IP_HEADER_SISE];

	TCP_IP_packet[0]= 0x45;		//IPv4, ヘッダ20byte
	TCP_IP_packet[1]= 0x00;		//サービス・タイプ未使用

	data_length += IP_HEADER_SISE;
	TCP_IP_packet[2]= (data_length >> 8);	//データグラム長
	TCP_IP_packet[3]= (data_length & 0xFF);	//データグラム長

	TCP_IP_packet[4]= 0x1A;			//ID(IPフラグメンテーション非対応のため固定)
	TCP_IP_packet[5]= 0x30;			//ID(IPフラグメンテーション非対応のため固定)

	TCP_IP_packet[6]= (0x00<<5)&0xE0;	//フラグ(分割不可・最後のフラグメント)
	TCP_IP_packet[6]|= 0x00;		//フラグメント・オフセット(IPフラグメンテーション非対応のため0固定)
	TCP_IP_packet[7]= 0x00;			//フラグメント・オフセット(IPフラグメンテーション非対応のため0固定)

	TCP_IP_packet[8]= 0xff;			//TTL

	TCP_IP_packet[9]= protocol;		//プロトコル番号

	TCP_IP_packet[10] = 0x00;	//ヘッダ・チェックサム初期化
	TCP_IP_packet[11] = 0x00;	//ヘッダ・チェックサム初期化

	TCP_IP_packet[12]= My_IP[0];
	TCP_IP_packet[13]= My_IP[1];
	TCP_IP_packet[14]= My_IP[2];
	TCP_IP_packet[15]= My_IP[3];

	TCP_IP_packet[16]= Dest_IP[0];
	TCP_IP_packet[17]= Dest_IP[1];
	TCP_IP_packet[18]= Dest_IP[2];
	TCP_IP_packet[19]= Dest_IP[3];

	checksum_value = checksum(TCP_IP_packet,0,19);
	TCP_IP_packet[10]= ((checksum_value>>8) & 0xFF);	//ヘッダ・チェックサム
	TCP_IP_packet[11]= (checksum_value & 0xFF);			//ヘッダ・チェックサム

	return ENC_Transmit(raw_data, data_length ,'I');
}


