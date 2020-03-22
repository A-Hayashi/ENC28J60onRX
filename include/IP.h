#ifndef IP_H_
#define IP_H_

/*
 * TCP_IP.h
 *
 * Created: 7/2/2016 12:56:57 PM
 *  Author: ASUS
 */ 

#include "common.h"
#include "ENC_Ethernet.h"
	
//IPヘッダ
//0		バージョン(4bit),ヘッダ長(4bit)
//1		サービス・タイプ(TOS)
//2,3	データグラム長
//4,5	ID
//6,7	フラグ(3bit),フラグメント・オフセット
//8		TTL
//9		プロトコル番号
//10-11	ヘッダ・チェックサム
//12-15	送信元IPアドレス
//16-19 宛先IPアドレス
//20-	データ部

#define IP_HEADER_SISE	(20)
#define IP_PROTOCOL_TCP	(6)
#define IP_PROTOCOL_UDP	(17)

bool IP_Transmit(char raw_data[], uint16_t data_length, char protocol);

#endif
