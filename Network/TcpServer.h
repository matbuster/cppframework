/**
 * \file 		TcpServer.h
 * \date 		04/11/2015 
 * \author 		MAT
 */
 
#ifndef TCP_INTERFACE
#define TCP_INTERFACE

#ifdef _WINDOWS
#include <stdio.h>
#include <Winsock2.h>
#endif

#ifdef LINUX
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

//! this define is implemented according to the ogdcvi server implementation
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
#define INVALID_SOCKET (SOCKET)(-1)
#define SOCKET_ERROR -1
#endif

#define TCP_SV_ERR_SHIFT			100

#define TCP_SERVER_SUCCESS			0
#define TCP_ERR_SERV_PARAMS			TCP_SV_ERR_SHIFT + 1
#define TCP_ERR_SERV_CREATE_SOCKET	TCP_SV_ERR_SHIFT + 2
#define TCP_ERR_SERV_BIND_PORT		TCP_SV_ERR_SHIFT + 3
#define TCP_ERR_SERV_ACCEPT			TCP_SV_ERR_SHIFT + 4
#define TCP_ERR_SERV_NOT_CONNECT	TCP_SV_ERR_SHIFT + 5
#define TCP_ERR_SERV_NOT_ACCEPTED	TCP_SV_ERR_SHIFT + 6
#define TCP_ERR_SERV_SEND			TCP_SV_ERR_SHIFT + 7
#define TCP_ERR_SERV_CLOSE			TCP_SV_ERR_SHIFT + 8
#define TCP_ERR_SERV_RECV			TCP_SV_ERR_SHIFT + 9
#define TCP_ERR_SERV_SHUTDOWN		TCP_SV_ERR_SHIFT + 10
#define TCP_ERR_SERV_WSAS			TCP_SV_ERR_SHIFT + 11
#define TCP_ERR_SERV_INVALID_PT		TCP_SV_ERR_SHIFT + 12

#define TCP_MAX_DATA			8092
#define TCP_MAX_ACCEPTANCE		5
#define MAX_TRY_RECEIVED		5

#define KEY_STR_INADDR_ANY		"INADDR_ANY"

namespace Network {

	class TCPServer {
	protected:
#ifdef _WINDOWS
		/** WSADATA for windows implementation */
		WSADATA m_wsaData;
#endif // _WINDOWS
		/** state of connection */
		bool m_bConnected;

		/** state of connection accepted */
		bool m_bAccepted;

		/** string containing IP adress*/
		unsigned char m_ucIPAdress[STR_SHORT];

		/** port for tcp connection */
		int m_iPort;

		/** information sur la source */
		SOCKADDR_IN m_sockInInfo;

		/** descripteur idenfiant de la socket */
		int m_iSocket_id;

		/** session identifiant */
		int m_iSession_id;

		/** private function to check and replace localhost */
		char * checkStringLocalhost(char * cInputAdress);

		/** Returns true on success, or false if there was an error */
		bool SetSocketBlockingEnabled(int fd, bool blocking);

	public:
		/** main constructor of class TCP */
		TCPServer();
		~TCPServer();

		/** connection function to a socket */
		long TCPconnect(char * cIPAdress, int iPort);

		/** acceptation de la demande d'ouverture de session */ 
		long TCPaccept();

		/** acceptation de la demande d'ouverture de session */ 
		long TCPaccept(int * iSession_ID);

		/** send data via tcp connection */
		long TCPSend(char * ucBufferSend, int iLenBufferSend);

		/** send data via tcp connection, using session ID */
		long TCPSend(int iSession_ID, char * ucBufferSend, int iLenBufferSend);

		/** receive data from tcp connection */
		long TCPReceive(char * ucBufferReceive, int iLenBufferReceive, int * iOutLenDataReceive);

		/** receive data from tcp connection, using session ID */
		long TCPReceive(int iSession_ID, char * ucBufferReceive, int iLenBufferReceive, int * iOutLenDataReceive);

		/** receive data from tcp connection, using session ID */
		long TCPReceive(int iSession_ID, char ** ucBufferReceive, int iLenBufferReceive, int * iOutLenDataReceive, bool bAllowAllocate);

		/** shutdown socket session connection */
		long TCPshutdown();

		/** shutdown socket session connection, using session ID */
		long TCPshutdown(int iSession_ID);

		/** closing an open connection */
		long TCPclose();
	};
};

#endif