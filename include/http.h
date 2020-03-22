#ifndef HTTP
#define HTTP

#define TCP_ON_NEW_CONNETION_CALLBACK HttpTcpOnNewConnection
#define TCP_ON_CONNECT_CALLBACK HttpTcpOnConnect
#define TCP_ON_INCOMING_DATA_CALLBACK HttpTcpOnIncomingData
#define TCP_ON_DISCONNECT_CALLBACK HttpTcpOnDisconnect

#include "tcp.h"

#ifndef HTTP_TCP_INCLUDED
#define HTTP_TCP_INCLUDED 0
#endif

#define HTTP_MAX_METHOD_LENGTH 10

#ifndef HTTP_MAX_STATUS_MESSAGE_LENGTH
#define HTTP_MAX_STATUS_MESSAGE_LENGTH 30
#endif

#define HTTP_REQUEST_STATE_NO_REQUEST 0
#define HTTP_REQUEST_STATE_START_REQUEST 1
#define HTTP_REQUEST_STATE_METHOD 2
#define HTTP_REQUEST_STATE_URL 3

#define HTTP_RESPONSE_STATE_WAITING 0
#define HTTP_RESPONSE_STATE_CODE 1
#define HTTP_RESPONSE_STATE_MESSAGE 2

#define HTTP_STATE_VERSION 4
#define HTTP_STATE_LINUX_END_HEADER 5
#define HTTP_STATE_MAC_END_HEADER 6
#define HTTP_STATE_WIN_END_HEADER 7
#define HTTP_STATE_WIN_END_HEADER2 8
#define HTTP_STATE_HEADER 9
#define HTTP_STATE_END_HEADER 10
#define HTTP_STATE_END_MESSAGE 11

#define HTTP_REQUEST_STATE_REQUEST_HANDLING 12

#ifndef HTTP_HEADER_ROW_BREAK
#define HTTP_HEADER_ROW_BREAK "\r\n"
#endif

typedef struct{
 unsigned short headersLenght;
 unsigned char headers[HTTP_MAX_HEADER_ROWS_LENGTH+1];
 unsigned char data[HTTP_MAX_DATA_LENGTH];
 unsigned char dataLength;
} HttpMessage;

typedef struct{
 const TcpConnection *connection;
 HttpMessage *message;
 unsigned char method[HTTP_MAX_METHOD_LENGTH+1];
 unsigned char url[HTTP_MAX_URL_LENGTH];
 unsigned char urlLength;
} HttpRequest;

typedef struct{
 unsigned short code;
 const char *message;
} HttpStatus;

typedef struct{
 HttpStatus status;
 HttpMessage *message;
} HttpResponse;

typedef struct{
 unsigned short length;
 unsigned char *value;
} HttpHeaderValue;

#if HTTP_TCP_INCLUDED == 1
unsigned char TcpOnNewConnection(const unsigned char connectionId);
void TcpOnConnect(const unsigned char connectionId);
void TcpOnIncomingData(const unsigned char connectionId, const unsigned char *data, unsigned short dataLength);
void TcpOnDisconnect(const unsigned char connectionId);
#endif
const HttpHeaderValue HttpParseHeaderValue(const HttpMessage *message, const unsigned char *header);
void HttpOnIncomingRequest(const HttpRequest *request);


void HttpInit(){
const HttpHeaderValue HttpParseHeaderValue(const HttpMessage *message, const unsigned char *header);
const HttpResponse* HttpSendRequest(const unsigned char *ip, const unsigned short port, const unsigned short connectionTimeout, unsigned short requestTimeout, const unsigned char *method, const unsigned char *url, const unsigned char urlLength, const unsigned char *headers, const unsigned short headersLength, const unsigned char *data, unsigned short dataLength);
unsigned char HttpSendResponse(const HttpStatus *status, unsigned char *headers, unsigned short headersLength, unsigned char *data, unsigned short dataLength);
unsigned char HttpTcpOnNewConnection(const unsigned char connectionId);
void HttpTcpOnConnect(const unsigned char connectionId);
void HttpTcpOnIncomingData(const unsigned char connectionId, const unsigned char *data, unsigned short dataLength);
void HttpTcpOnDisconnect(const unsigned char connectionId);

#endif
