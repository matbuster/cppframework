/**
 * \file 		TcpClient.h
 * \date 		04/11/2015 
 * \author 		MAT
 */
 
#ifndef TCP_COMM
#define TCP_COMM

#define TCP_OK							0
#define TCP_KO							1
#define TCP_ERR_CLIENT_CLOSE_SOCKET		2
#define TCP_ERR_CLIENT_CLEANUP			3
#define TCP_ERR_CLIENT_CONNECT			4
#define TCP_ERR_CLIENT_WRONG_PARAMS		5
#define TCP_ERR_CLIENT_CLOSED			6
#define TCP_ERR_CLIENT_SEND				7
#define TCP_ERR_CLIENT_RECV				8
#define TCP_BUFF_TOO_SMALL				9

#define STR_LOCALHOST_KEY	"localhost"
#define STR_LOCALHOST_ADDR	"127.0.0.1"

#define TCP_MAX_DATA			8092
#define CLIENT_MAX_RETRY	5

#ifdef _WINDOWS
#include <Winsock2.h>
#endif // _WINDOWS

namespace Network {

	class TCPClient {

	protected:
		/** state of connection */
		bool m_bOpenedConnection;

		/** string containing IP adress*/
		unsigned char m_ucIPAdress[STR_SHORT];

		/** port for tcp connection */
		int m_iPort;
#ifdef _WINDOWS
		/** ! descripteur idenfiant de la socket */
		SOCKET m_iSocket_id;
#endif // _WINDOWS

#ifdef LINUX
		/** ! descripteur idenfiant de la socket */
		int m_iSocket_id;
#endif // LINUX
		/** private function to check and replace localhost */
		char * checkStringLocalhost(char * cInputAdress);

		/** Returns true on success, or false if there was an error */
		bool SetSocketBlockingEnabled(int fd, bool blocking);

	public:
		/** main constructor of class TCP */
		TCPClient();
		~TCPClient();

		/** connection function to a socket */
		long TCPconnect(char * ucIPAdress, int iPort);

		/** send data via tcp connection */
		long TCPSend(char * ucBufferSend, int iLenBufferSend);

		/** receive data from tcp connection */
		long TCPReceive(char * ucBufferReceive, int iLenBufferReceive, int * iOutLenDataReceive);

		/** closing an open connection */
		long TCPclose();
	};
};

#endif /* TCP_COMM */