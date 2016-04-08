/**
 * \file 		TcpClient.h
 * \date 		04/11/2015 
 * \author 		MAT
 */
 
#ifndef TCP_COMM
#define TCP_COMM

#define TCP_OK						0
#define TCP_KO						1
#define TCP_ERR_CLOSE_SOCKET		2
#define TCP_ERR_CLEANUP				3
#define TCP_ERR_CONNECT				4
#define TCP_ERR_WRONG_PARAMS		5
#define TCP_ERR_CLOSED				6
#define TCP_ERR_SEND				7
#define TCP_ERR_RECV				8

#define STR_LOCALHOST_KEY	"localhost"
#define STR_LOCALHOST_ADDR	"127.0.0.1"

namespace Network {

	class TCPClient {
	protected:
		/** state of connection */
		bool m_bOpenedConnection;

		/** string containing IP adress*/
		unsigned char m_ucIPAdress[STR_SHORT];

		/** port for tcp connection */
		int m_iPort;

		/** ! descripteur idenfiant de la socket */
		int m_iSocket_id;

		/** private function to check and replace localhost */
		char * checkStringLocalhost(char * cInputAdress);

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