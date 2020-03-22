#ifndef NETWORK

#include "util.h"
#include "udp.h"
#include "tcp.h"
#include "icmp.h"

#define NET_MIN_DINAMIC_PORT 49152
#define NET_MAX_PORT 65535

#define NET_HANDLE_RESULT_OK       0
#define NET_HANDLE_RESULT_DROP     1
#define NET_HANDLE_RESULT_REJECT   2

#define NETWORK
void NetInit();
void NetHandleNetwork();
void NetHandleIncomingPacket(unsigned short length);
unsigned char *NetGetBuffer();
#endif
