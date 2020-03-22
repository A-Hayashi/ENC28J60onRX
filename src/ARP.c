/*
 * ARP.h
 *
 * Created: 7/21/2016 3:51:12 PM
 *  Author: ASUS
 */ 

#include "ARP.h"

static void ARP_reply(char dest_IP[] , char dest_MAC[]);

char ARP_check(char data[])
{
	char *ether = &data[0];
	char *arp	= &data[14];

	//イーサネットヘッダ
	//0-5	宛先MACアドレス
	//6-11	送信元MACアドレス
	//12,13	フレームタイプ:0x0806

	//ARPパケット
	//0,1	ハードウェアタイプ:0x0001
	//2,3	プロトコルタイプ:0x0800
	//4		ハードウェアアドレスサイズ:0x06
	//5		プロトコルアドレスサイズ:0x04
	//6,7	オペレーション:ARPリクエスト:0x0001, ARPリプライ0x0002
	//8-13	送信元ハードウェアアドレス
	//14-17	送信元プロトコルアドレス
	//18-23	送信先ハードウェアアドレス
	//24-27	送信先プロトコルアドレス

	if ((ether[12]==0x08)&&(ether[13]==0x06)&&(arp[0]==0x00)&&
		(arp[14]==My_IP[0])&&(arp[15]==My_IP[1])&&(arp[16]==My_IP[2])&&(arp[17]==My_IP[3])){
		static char ARP_IP[4];
		static char Source_MAC[6];

		Source_MAC[0]= ether[6];
		Source_MAC[1]= ether[7];
		Source_MAC[2]= ether[8];
		Source_MAC[3]= ether[9];
		Source_MAC[4]= ether[10];
		Source_MAC[5]= ether[11];
		ARP_IP[0]= arp[14];
		ARP_IP[1]= arp[15];
		ARP_IP[2]= arp[16];
		ARP_IP[3]= arp[17];

		//	Yes, Its ARP for you
		ARP_reply(ARP_IP ,Source_MAC);
		return 'N';
	}else{
		if (ether[0]==0xFF){
			return 'N';				//	No, ignore it
		}else{
			return 'O';				//	Other packet for you
		}
	}
}

static void ARP_reply(char dest_IP[] , char dest_MAC[] )
{
	char ARP_Request[28] = {0x00,0x01,
							0x08,0x00,
							0x06,
							0x04,
							0x00,0x02,
							MAC[0],MAC[1],MAC[2],MAC[3],MAC[4],MAC[5],
							My_IP[0],My_IP[1],My_IP[2],My_IP[3],
							dest_MAC[0],dest_MAC[1],dest_MAC[2],dest_MAC[3],dest_MAC[4],dest_MAC[5],
							dest_IP[0],dest_IP[1],dest_IP[2],dest_IP[3]};
							
	ENC_Transmit(ARP_Request,sizeof(ARP_Request),'A');
}
