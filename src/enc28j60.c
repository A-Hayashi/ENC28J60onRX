//********************************************************************************************
//
// File : enc28j60.c Microchip ENC28J60 Ethernet Interface Driver
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
#include "enc28j60.h"
//

//struct enc28j60_flag
//{
//	unsigned rx_buffer_is_free:1;
//	unsigned unuse:7;
//}enc28j60_flag;

// ENC28J60 Control Registers
// Control register definitions are a combination of address,
// bank number, and Ethernet/MAC/PHY indicator bits.
// - Register address        (bits 0-4)
// - Bank number        (bits 5-6)
// - MAC/PHY indicator        (bit 7)

#define ADDR_MASK        0x1F
#define BANK_MASK        0x60
#define SPRD_MASK        0x80
// All-bank registers
#define EIE              0x1B
#define EIR              0x1C
#define ESTAT            0x1D
#define ECON2            0x1E
#define ECON1            0x1F
// Bank 0 registers
#define ERDPTL           (0x00|0x00)
#define ERDPTH           (0x01|0x00)
#define EWRPTL           (0x02|0x00)
#define EWRPTH           (0x03|0x00)
#define ETXSTL           (0x04|0x00)
#define ETXSTH           (0x05|0x00)
#define ETXNDL           (0x06|0x00)
#define ETXNDH           (0x07|0x00)
#define ERXSTL           (0x08|0x00)
#define ERXSTH           (0x09|0x00)
#define ERXNDL           (0x0A|0x00)
#define ERXNDH           (0x0B|0x00)
#define ERXRDPTL         (0x0C|0x00)
#define ERXRDPTH         (0x0D|0x00)
#define ERXWRPTL         (0x0E|0x00)
#define ERXWRPTH         (0x0F|0x00)
#define EDMASTL          (0x10|0x00)
#define EDMASTH          (0x11|0x00)
#define EDMANDL          (0x12|0x00)
#define EDMANDH          (0x13|0x00)
#define EDMADSTL         (0x14|0x00)
#define EDMADSTH         (0x15|0x00)
#define EDMACSL          (0x16|0x00)
#define EDMACSH          (0x17|0x00)
// Bank 1 registers
#define EHT0             (0x00|0x20)
#define EHT1             (0x01|0x20)
#define EHT2             (0x02|0x20)
#define EHT3             (0x03|0x20)
#define EHT4             (0x04|0x20)
#define EHT5             (0x05|0x20)
#define EHT6             (0x06|0x20)
#define EHT7             (0x07|0x20)
#define EPMM0            (0x08|0x20)
#define EPMM1            (0x09|0x20)
#define EPMM2            (0x0A|0x20)
#define EPMM3            (0x0B|0x20)
#define EPMM4            (0x0C|0x20)
#define EPMM5            (0x0D|0x20)
#define EPMM6            (0x0E|0x20)
#define EPMM7            (0x0F|0x20)
#define EPMCSL           (0x10|0x20)
#define EPMCSH           (0x11|0x20)
#define EPMOL            (0x14|0x20)
#define EPMOH            (0x15|0x20)
#define EWOLIE           (0x16|0x20)
#define EWOLIR           (0x17|0x20)
#define ERXFCON          (0x18|0x20)
#define EPKTCNT          (0x19|0x20)
// Bank 2 registers
#define MACON1           (0x00|0x40|0x80)
#define MACON2           (0x01|0x40|0x80)
#define MACON3           (0x02|0x40|0x80)
#define MACON4           (0x03|0x40|0x80)
#define MABBIPG          (0x04|0x40|0x80)
#define MAIPGL           (0x06|0x40|0x80)
#define MAIPGH           (0x07|0x40|0x80)
#define MACLCON1         (0x08|0x40|0x80)
#define MACLCON2         (0x09|0x40|0x80)
#define MAMXFLL          (0x0A|0x40|0x80)
#define MAMXFLH          (0x0B|0x40|0x80)
#define MAPHSUP          (0x0D|0x40|0x80)
#define MICON            (0x11|0x40|0x80)
#define MICMD            (0x12|0x40|0x80)
#define MIREGADR         (0x14|0x40|0x80)
#define MIWRL            (0x16|0x40|0x80)
#define MIWRH            (0x17|0x40|0x80)
#define MIRDL            (0x18|0x40|0x80)
#define MIRDH            (0x19|0x40|0x80)
// Bank 3 registers
#define MAADR1           (0x00|0x60|0x80)
#define MAADR0           (0x01|0x60|0x80)
#define MAADR3           (0x02|0x60|0x80)
#define MAADR2           (0x03|0x60|0x80)
#define MAADR5           (0x04|0x60|0x80)
#define MAADR4           (0x05|0x60|0x80)
#define EBSTSD           (0x06|0x60)
#define EBSTCON          (0x07|0x60)
#define EBSTCSL          (0x08|0x60)
#define EBSTCSH          (0x09|0x60)
#define MISTAT           (0x0A|0x60|0x80)
#define EREVID           (0x12|0x60)
#define ECOCON           (0x15|0x60)
#define EFLOCON          (0x17|0x60)
#define EPAUSL           (0x18|0x60)
#define EPAUSH           (0x19|0x60)
// PHY registers
#define PHCON1           0x00
#define PHSTAT1          0x01
#define PHHID1           0x02
#define PHHID2           0x03
#define PHCON2           0x10
#define PHSTAT2          0x11
#define PHIE             0x12
#define PHIR             0x13
#define PHLCON           0x14

// ENC28J60 ERXFCON Register Bit Definitions
#define ERXFCON_UCEN     0x80
#define ERXFCON_ANDOR    0x40
#define ERXFCON_CRCEN    0x20
#define ERXFCON_PMEN     0x10
#define ERXFCON_MPEN     0x08
#define ERXFCON_HTEN     0x04
#define ERXFCON_MCEN     0x02
#define ERXFCON_BCEN     0x01
// ENC28J60 EIE Register Bit Definitions
#define EIE_INTIE        0x80
#define EIE_PKTIE        0x40
#define EIE_DMAIE        0x20
#define EIE_LINKIE       0x10
#define EIE_TXIE         0x08
#define EIE_WOLIE        0x04
#define EIE_TXERIE       0x02
#define EIE_RXERIE       0x01
// ENC28J60 EIR Register Bit Definitions
#define EIR_PKTIF        0x40
#define EIR_DMAIF        0x20
#define EIR_LINKIF       0x10
#define EIR_TXIF         0x08
#define EIR_WOLIF        0x04
#define EIR_TXERIF       0x02
#define EIR_RXERIF       0x01
// ENC28J60 ESTAT Register Bit Definitions
#define ESTAT_INT        0x80
#define ESTAT_LATECOL    0x10
#define ESTAT_RXBUSY     0x04
#define ESTAT_TXABRT     0x02
#define ESTAT_CLKRDY     0x01
// ENC28J60 ECON2 Register Bit Definitions
#define ECON2_AUTOINC    0x80
#define ECON2_PKTDEC     0x40
#define ECON2_PWRSV      0x20
#define ECON2_VRPS       0x08
// ENC28J60 ECON1 Register Bit Definitions
#define ECON1_TXRST      0x80
#define ECON1_RXRST      0x40
#define ECON1_DMAST      0x20
#define ECON1_CSUMEN     0x10
#define ECON1_TXRTS      0x08
#define ECON1_RXEN       0x04
#define ECON1_BSEL1      0x02
#define ECON1_BSEL0      0x01
// ENC28J60 MACON1 Register Bit Definitions
#define MACON1_LOOPBK    0x10
#define MACON1_TXPAUS    0x08
#define MACON1_RXPAUS    0x04
#define MACON1_PASSALL   0x02
#define MACON1_MARXEN    0x01
// ENC28J60 MACON2 Register Bit Definitions
#define MACON2_MARST     0x80
#define MACON2_RNDRST    0x40
#define MACON2_MARXRST   0x08
#define MACON2_RFUNRST   0x04
#define MACON2_MATXRST   0x02
#define MACON2_TFUNRST   0x01
// ENC28J60 MACON3 Register Bit Definitions
#define MACON3_PADCFG2   0x80
#define MACON3_PADCFG1   0x40
#define MACON3_PADCFG0   0x20
#define MACON3_TXCRCEN   0x10
#define MACON3_PHDRLEN   0x08
#define MACON3_HFRMLEN   0x04
#define MACON3_FRMLNEN   0x02
#define MACON3_FULDPX    0x01
// ENC28J60 MACON4 Register Bit Definitions
#define	MACON4_DEFER	(1<<6)
#define	MACON4_BPEN		(1<<5)
#define	MACON4_NOBKOFF	(1<<4)
// ENC28J60 MICMD Register Bit Definitions
#define MICMD_MIISCAN    0x02
#define MICMD_MIIRD      0x01
// ENC28J60 MISTAT Register Bit Definitions
#define MISTAT_NVALID    0x04
#define MISTAT_SCAN      0x02
#define MISTAT_BUSY      0x01
// ENC28J60 PHY PHCON1 Register Bit Definitions
#define PHCON1_PRST      0x8000
#define PHCON1_PLOOPBK   0x4000
#define PHCON1_PPWRSV    0x0800
#define PHCON1_PDPXMD    0x0100
// ENC28J60 PHY PHSTAT1 Register Bit Definitions
#define PHSTAT1_PFDPX    0x1000
#define PHSTAT1_PHDPX    0x0800
#define PHSTAT1_LLSTAT   0x0004
#define PHSTAT1_JBSTAT   0x0002
// ENC28J60 PHY PHCON2 Register Bit Definitions
#define PHCON2_FRCLINK   0x4000
#define PHCON2_TXDIS     0x2000
#define PHCON2_JABBER    0x0400
#define PHCON2_HDLDIS    0x0100

// ENC28J60 Packet Control Byte Bit Definitions
#define PKTCTRL_PHUGEEN  0x08
#define PKTCTRL_PPADEN   0x04
#define PKTCTRL_PCRCEN   0x02
#define PKTCTRL_POVERRIDE 0x01

// SPI operation codes
#define ENC28J60_READ_CTRL_REG       0x00
#define ENC28J60_READ_BUF_MEM        0x3A
#define ENC28J60_WRITE_CTRL_REG      0x40
#define ENC28J60_WRITE_BUF_MEM       0x7A
#define ENC28J60_BIT_FIELD_SET       0x80
#define ENC28J60_BIT_FIELD_CLR       0xA0
#define ENC28J60_SOFT_RESET          0xFF

/* 暫定 ここから */
#define NET_MAC 0x15, 0x8, 0x45, 0x89, 0x69, 0x99

char dummy = 0x00;
#define ENC28J60_PORT			(dummy)
#define ENC28J60_DDR			(dummy)
#define SPDR					(dummy)
#define SPCR					(dummy)
#define SPSR					(dummy)

#define ENC28J60_RESET_PIN_DDR	(0)
#define ENC28J60_RESET_PIN		(0)
#define ENC28J60_INT_PIN_DDR	(0)
#define ENC28J60_INT_PIN		(0)
#define ENC28J60_SCK_PIN_DDR	(0)
#define ENC28J60_SCK_PIN		(0)
#define ENC28J60_SI_PIN_DDR		(0)
#define ENC28J60_SI_PIN			(0)
#define ENC28J60_CS_PIN_DDR		(0)
#define ENC28J60_CS_PIN			(0)
#define ENC28J60_SO_PIN_DDR		(0)
#define SPE						(0)
#define MSTR					(0)
#define SPI2X					(0)
#define SPIF					(0)
/* 暫定 ここまで */

// set CS to 0 = active
#define CSACTIVE ENC28J60_PORT &= ~_BV(ENC28J60_CS_PIN)
// set CS to 1 = passive
#define CSPASSIVE ENC28J60_PORT |= _BV(ENC28J60_CS_PIN)
//

#define waitspi() while(!(SPSR&(1<<SPIF)))

// The RXSTART_INIT should be zero. See Rev. B4 Silicon Errata
// buffer boundaries applied to internal 8K ram
// the entire available packet buffer space is allocated
//

// max frame length which the conroller will accept:
#define MAX_FRAMELEN	(NET_BUFFER_SIZE+4)        // maximum ethernet frame length

// start with recbuf at 0/
#define RXSTART_INIT	0x0000
#define RXSTOP_INIT		(8192-NET_BUFFER_SIZE-1)
#define TXSTART_INIT	(8192-NET_BUFFER_SIZE)
#define TXSTOP_INIT		8192

static unsigned char Enc28j60Bank;
static unsigned short next_packet_ptr;
const unsigned char avr_mac[MAC_ADDRESS_SIZE] = {NET_MAC};

static unsigned char enc28j60ReadOp(unsigned char op, unsigned char address);
static void enc28j60WriteOp(unsigned char op, unsigned char address, unsigned char data);
static void enc28j60SetBank(unsigned char address);
static unsigned char enc28j60Read(unsigned char address);
static void enc28j60Write(unsigned char address, unsigned char data);
static unsigned short enc28j60_read_phyreg(unsigned char address);
static void enc28j60PhyWrite(unsigned char address, unsigned short data);
static unsigned char enc28j60getrev(void);
//*******************************************************************************************
//
// Function : enc28j60ReadOp
//
//*******************************************************************************************
static unsigned char enc28j60ReadOp(unsigned char op, unsigned char address)
{
	// activate CS
	CSACTIVE;
	// issue read command
	SPDR = op | (address & ADDR_MASK);
	waitspi();
	// read data
	SPDR = 0x00;
	waitspi();
	// do dummy read if needed (for mac and mii, see datasheet page 29)
	if(address & 0x80)
	{
		SPDR = 0x00;
		waitspi();
	}
	// release CS
	CSPASSIVE;
	return(SPDR);
}
//*******************************************************************************************
//
// Function : icmp_send_request
// Description : Send ARP request packet to destination.
//
//*******************************************************************************************
static void enc28j60WriteOp(unsigned char op, unsigned char address, unsigned char data)
{
	CSACTIVE;
	// issue write command
	SPDR = op | (address & ADDR_MASK);
	waitspi();
	// write data
	SPDR = data;
	waitspi();
	CSPASSIVE;
}
//*******************************************************************************************
//
// Function : icmp_send_request
// Description : Send ARP request packet to destination.
//
//*******************************************************************************************
static void enc28j60SetBank(unsigned char address)
{
	// set the bank (if needed)
	if((address & BANK_MASK) != Enc28j60Bank)
	{
		// set the bank
		enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, (ECON1_BSEL1|ECON1_BSEL0));
		enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, (address & BANK_MASK)>>5);
		Enc28j60Bank = (address & BANK_MASK);
	}
}
//*******************************************************************************************
//
// Function : enc28j60Read
//
//*******************************************************************************************
static unsigned char enc28j60Read(unsigned char address)
{
	// select bank to read
	enc28j60SetBank(address);

	// do the read
	return enc28j60ReadOp(ENC28J60_READ_CTRL_REG, address);
}
//*******************************************************************************************
//
// Function : icmp_send_request
// Description : Send ARP request packet to destination.
//
//*******************************************************************************************
static void enc28j60Write(unsigned char address, unsigned char data)
{
	// select bank to write
	enc28j60SetBank(address);

	// do the write
	enc28j60WriteOp(ENC28J60_WRITE_CTRL_REG, address, data);
}
//*******************************************************************************************
//
// Function : enc28j60_read_phyreg
//
//*******************************************************************************************
static unsigned short enc28j60_read_phyreg(unsigned char address)
{
	unsigned short data;

	// set the PHY register address
	enc28j60Write(MIREGADR, address);
	enc28j60Write(MICMD, MICMD_MIIRD);

	// Loop to wait until the PHY register has been read through the MII
	// This requires 10.24us
	while( (enc28j60Read(MISTAT) & MISTAT_BUSY) );

	// Stop reading
	enc28j60Write(MICMD, MICMD_MIIRD);

	// Obtain results and return
	data = enc28j60Read ( MIRDL );
	data |= enc28j60Read ( MIRDH );

	return data;
}
//*******************************************************************************************
//
// Function : enc28j60PhyWrite
//
//*******************************************************************************************
static void enc28j60PhyWrite(unsigned char address, unsigned short data)
{
	// set the PHY register address
	enc28j60Write(MIREGADR, address);
	// write the PHY data
	enc28j60Write(MIWRL, Low(data));
	enc28j60Write(MIWRH, High(data));
	// wait until the PHY write completes
	while(enc28j60Read(MISTAT) & MISTAT_BUSY)
	{
		_delay_us(15);
	}
}
//*******************************************************************************************
//
// Function : icmp_send_request
// Description : Send ARP request packet to destination.
//
//*******************************************************************************************

void enc28j60_init()
{
	// initialize I/O
	//DDRB |= _BV( DDB4 );
	//CSPASSIVE;

	// enable PB0, reset as output
	ENC28J60_DDR |= _BV(ENC28J60_RESET_PIN_DDR);

	// enable PD2/INT0, as input
	ENC28J60_DDR &= ~_BV(ENC28J60_INT_PIN_DDR);
	ENC28J60_PORT |= _BV(ENC28J60_INT_PIN);

	// set output to gnd, reset the ethernet chip
	ENC28J60_PORT &= ~_BV(ENC28J60_RESET_PIN);
	_delay_ms(10);

	// set output to Vcc, reset inactive
	ENC28J60_PORT |= _BV(ENC28J60_RESET_PIN);
	_delay_ms(200);

    // set SPI anc CS I/O pins
	ENC28J60_DDR |= _BV(ENC28J60_CS_PIN_DDR) | _BV(ENC28J60_SI_PIN_DDR) | _BV(ENC28J60_SCK_PIN_DDR); // output pin
	ENC28J60_DDR &= ~_BV(ENC28J60_SO_PIN_DDR); // input pin

	CSPASSIVE;
	ENC28J60_PORT &= ~(_BV(ENC28J60_SI_PIN) | _BV(ENC28J60_SCK_PIN));
	//
	// initialize SPI interface
	// master mode and Fosc/2 clock:
    SPCR = _BV( SPE ) | _BV( MSTR );
    SPSR |= _BV( SPI2X );

	// perform system reset
	enc28j60WriteOp(ENC28J60_SOFT_RESET, 0, ENC28J60_SOFT_RESET);

	_delay_ms(50);

	// check CLKRDY bit to see if reset is complete
	// The CLKRDY does not work. See Rev. B4 Silicon Errata point. Just wait.
	//while(!(enc28j60Read(ESTAT) & ESTAT_CLKRDY));
	// do bank 0 stuff
	// initialize receive buffer
	// 16-bit transfers, must write low byte first
	// set receive buffer start address
	next_packet_ptr = RXSTART_INIT;
    // Rx start
	enc28j60Write(ERXSTL, RXSTART_INIT&0xFF);
	enc28j60Write(ERXSTH, RXSTART_INIT>>8);
	// set receive pointer address
	enc28j60Write(ERXRDPTL, RXSTART_INIT&0xFF);
	enc28j60Write(ERXRDPTH, RXSTART_INIT>>8);
	// RX end
	enc28j60Write(ERXNDL, RXSTOP_INIT&0xFF);
	enc28j60Write(ERXNDH, RXSTOP_INIT>>8);
	// TX start
	enc28j60Write(ETXSTL, TXSTART_INIT&0xFF);
	enc28j60Write(ETXSTH, TXSTART_INIT>>8);
	// TX end
	enc28j60Write(ETXNDL, TXSTOP_INIT&0xFF);
	enc28j60Write(ETXNDH, TXSTOP_INIT>>8);

	// do bank 2 stuff
	// enable MAC receive
	enc28j60Write(MACON1, MACON1_MARXEN|MACON1_TXPAUS|MACON1_RXPAUS);

	// bring MAC out of reset
	//enc28j60Write(MACON2, 0x00);

	// enable automatic padding to 60bytes and CRC operations
	enc28j60Write(MACON3, MACON3_PADCFG0|MACON3_TXCRCEN|MACON3_FRMLNEN);

	// Allow infinite deferals if the medium is continuously busy
    // (do not time out a transmission if the half duplex medium is
    // completely saturated with other people's data)
    enc28j60Write(MACON4, MACON4_DEFER);

	// Late collisions occur beyond 63+8 bytes (8 bytes for preamble/start of frame delimiter)
	// 55 is all that is needed for IEEE 802.3, but ENC28J60 B5 errata for improper link pulse
	// collisions will occur less often with a larger number.
    enc28j60Write(MACLCON2, 63);

	// Set non-back-to-back inter-packet gap to 9.6us.  The back-to-back
	// inter-packet gap (MABBIPG) is set by MACSetDuplex() which is called
	// later.
	enc28j60Write(MAIPGL, 0x12);
	enc28j60Write(MAIPGH, 0x0C);

	// Set the maximum packet size which the controller will accept
    // Do not send packets longer than MAX_FRAMELEN:
	enc28j60Write(MAMXFLL, MAX_FRAMELEN&0xFF);
	enc28j60Write(MAMXFLH, MAX_FRAMELEN>>8);

	// do bank 3 stuff
    // write MAC address
	// NOTE: MAC address in ENC28J60 is byte-backward
	// ENC28J60 is big-endian avr gcc is little-endian

	enc28j60Write(MAADR5, avr_mac[0]);
	enc28j60Write(MAADR4, avr_mac[1]);
	enc28j60Write(MAADR3, avr_mac[2]);
	enc28j60Write(MAADR2, avr_mac[3]);
	enc28j60Write(MAADR1, avr_mac[4]);
	enc28j60Write(MAADR0, avr_mac[5]);

	// no loopback of transmitted frames
	enc28j60PhyWrite(PHCON2, PHCON2_HDLDIS);

	// Magjack leds configuration, see enc28j60 datasheet, page 11
	// 0x476 is PHLCON LEDA=links status, LEDB=receive/transmit
	// enc28j60PhyWrite(PHLCON,0b0000 0100 0111 00 10);
	enc28j60PhyWrite(PHLCON, 0x0472);

	// do bank 1 stuff, packet filter:
	// For broadcast packets we allow only ARP packtets
	// All other packets should be unicast only for our mac (MAADR)
	//
	// The pattern to match on is therefore
	// Type     ETH.DST
	// ARP      BROADCAST
 	// 06 08 -- ff ff ff ff ff ff -> ip checksum for theses bytes=f7f9
	// in binary these poitions are:11 0000 0011 1111
	// This is hex 303F->EPMM0=0x3f,EPMM1=0x30
	enc28j60Write(ERXFCON, ERXFCON_UCEN|ERXFCON_CRCEN|ERXFCON_PMEN);
	enc28j60Write(EPMM0, 0x3f);
	enc28j60Write(EPMM1, 0x30);
	enc28j60Write(EPMCSL, 0xf9);
	enc28j60Write(EPMCSH, 0xf7);

	// set inter-frame gap (back-to-back)
	enc28j60Write(MABBIPG, 0x12);

	// switch to bank 0
	enc28j60SetBank(ECON1);

	// enable interrutps
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, EIE, EIE_INTIE|EIE_PKTIE);

	// enable packet reception
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_RXEN);

	_delay_ms(20);
}
//*******************************************************************************************
//
// Function : enc28j60getrev
// Description : read the revision of the chip.
//
//*******************************************************************************************
static unsigned char enc28j60getrev(void)
{
	return(enc28j60Read(EREVID));
}
//*******************************************************************************************
//
// Function : enc28j60_packet_send
// Description : Send packet to network.
//
//*******************************************************************************************
void enc28j60_packet_send ( unsigned char *buffer, unsigned short length )
{
	//Set the write pointer to start of transmit buffer area
	enc28j60Write(EWRPTL, Low(TXSTART_INIT));
	enc28j60Write(EWRPTH, High(TXSTART_INIT));

	// Set the TXND pointer to correspond to the packet size given
	enc28j60Write(ETXNDL, Low(TXSTART_INIT+length));
	enc28j60Write(ETXNDH, High(TXSTART_INIT+length));

	// write per-packet control byte (0x00 means use macon3 settings)
	enc28j60WriteOp(ENC28J60_WRITE_BUF_MEM, 0, 0x00);

	CSACTIVE;
	// issue write command
	SPDR = ENC28J60_WRITE_BUF_MEM;
	waitspi();
	while(length)
	{
		length--;
		// write data
		SPDR = *buffer++;
		waitspi();
	}
	CSPASSIVE;

	// send the contents of the transmit buffer onto the network
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_TXRTS);

	// Reset the transmit logic problem. See Rev. B4 Silicon Errata point 12.
	if( (enc28j60Read(EIR) & EIR_TXERIF) )
	{
		enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_TXRTS);
	}
}

//*******************************************************************************************
//
// Function : enc28j60_packet_receive
// Description : check received packet and return length of data
//
//*******************************************************************************************
unsigned short enc28j60_packet_receive ( unsigned char *rxtx_buffer, unsigned short max_length )
{
	unsigned short rx_status, data_length;

	// check if a packet has been received and buffered
	// if( !(enc28j60Read(EIR) & EIR_PKTIF) ){
	// The above does not work. See Rev. B4 Silicon Errata point 6.
	if( enc28j60Read(EPKTCNT) == 0 )
	{
		return 0;
	}

	// Set the read pointer to the start of the received packet
	enc28j60Write(ERDPTL, Low(next_packet_ptr));
	enc28j60Write(ERDPTH, High(next_packet_ptr));

	// read the next packet pointer
    LowPut(&next_packet_ptr, enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0));
    HighPut(&next_packet_ptr, enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0));

	// read the packet length (see datasheet page 43)
	LowPut(&data_length, enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0));
	HighPut(&data_length, enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0));
	data_length -=4; //remove the CRC count

	// read the receive status (see datasheet page 43)
	LowPut(&rx_status, enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0));
	HighPut(&rx_status, enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0));

	if ( data_length > (max_length-1) )
	{
		data_length = max_length-1;
	}

	// check CRC and symbol errors (see datasheet page 44, table 7-3):
	// The ERXFCON.CRCEN is set by default. Normally we should not
	// need to check this.
	if ( (rx_status & 0x80)==0 )
	{
		// invalid
		data_length = 0;
	}
	else
	{
		// read data from rx buffer and save to rxtx_buffer
		rx_status = data_length;
		CSACTIVE;
		// issue read command
		SPDR = ENC28J60_READ_BUF_MEM;
		waitspi();
		while(rx_status)
		{
			rx_status--;
			SPDR = 0x00;
			waitspi();
			*rxtx_buffer++ = SPDR;
		}
		CSPASSIVE;
	}

	// Move the RX read pointer to the start of the next received packet
	// This frees the memory we just read out
	enc28j60Write(ERXRDPTL, Low(next_packet_ptr));
	enc28j60Write(ERXRDPTH, High(next_packet_ptr));

	// decrement the packet counter indicate we are done with this packet
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON2, ECON2_PKTDEC);

	return data_length;
}

