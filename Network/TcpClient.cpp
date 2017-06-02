/**
 * \file 		TcpClient.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */
 
#include "../toolsconstant.h"
#include "Timing/Timing.h"
#include "TcpClient.h"

#include <stdio.h>

/** main constructor of the class TCP */
Network::TCPClient::TCPClient() 
{
	m_bOpenedConnection = false;
	memset(m_ucIPAdress, 0x00, STR_SHORT);
	m_iPort = 0;
}

/** destructor of class TCP */
Network::TCPClient::~TCPClient() 
{
}
/** Returns true on success, or false if there was an error */
bool Network::TCPClient::SetSocketBlockingEnabled(int fd, bool blocking)
{
   if (fd < 0) return false;

#ifdef _WINDOWS
   unsigned long mode = blocking ? 0 : 1;
   return (ioctlsocket(fd, FIONBIO, &mode) == 0) ? true : false;
#else // _WINDOWS
   int flags = fcntl(fd, F_GETFL, 0);
   if (flags < 0) return false;
   flags = blocking ? (flags&~O_NONBLOCK) : (flags|O_NONBLOCK);
   return (fcntl(fd, F_SETFL, flags) == 0) ? true : false;
#endif // _WINDOWS
}
/** private function to check and replace localhost */
char * Network::TCPClient::checkStringLocalhost(char * cInputAdress)
{
	if(strcmp(STR_LOCALHOST_KEY,cInputAdress) == 0) 
	{
		return STR_LOCALHOST_ADDR;
	} 
	else
	{
		return cInputAdress;
	}
}

long Network::TCPClient::TCPconnect(char * ucIPAdress, int iPort) 
{
	if(NULL == ucIPAdress)
	{
		return TCP_ERR_CLIENT_WRONG_PARAMS;
	}
	if(iPort < 0)
	{
		return TCP_ERR_CLIENT_WRONG_PARAMS;
	}

	struct sockaddr_in addr;
	int	ret;
	int wsalasterror = 0;
	
	// copie des éléments de configuration dans les membres de la classe
	m_iPort = iPort;
	memcpy(m_ucIPAdress, ucIPAdress, STR_SHORT);

    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,0), &WSAData);

	memset((char *) &addr, 0, sizeof(addr));
	addr.sin_addr.s_addr	= inet_addr(ucIPAdress);
	addr.sin_family = AF_INET;		
	addr.sin_port   = htons ((u_short)m_iPort);

	m_iSocket_id = socket(AF_INET, SOCK_STREAM, 0);

    ret = connect(m_iSocket_id, (struct sockaddr *) &addr, sizeof(addr));
	// If connected, it will return 0, or error
	if (ret == SOCKET_ERROR)
	{
		WSACleanup();
		wsalasterror = WSAGetLastError();
		return wsalasterror;
	}
	
	m_bOpenedConnection = true;
	return TCP_OK;
}
/** send data via tcp connection */
long Network::TCPClient::TCPSend(char * ucBufferSend, int iLenBufferSend)
{
	if(!m_bOpenedConnection)
	{
		return TCP_ERR_CLIENT_CLOSED;
	}
	if(NULL == ucBufferSend)
	{
		return TCP_ERR_CLIENT_WRONG_PARAMS;
	}
	if(iLenBufferSend<0) 
	{
		return TCP_ERR_CLIENT_WRONG_PARAMS;
	}

	// envoi des donnees 
	int nbSend = send(m_iSocket_id, ucBufferSend, iLenBufferSend, 0);
    if (nbSend == SOCKET_ERROR) {
		// check if necessary to use WSAGetLastError() for debug
		return TCP_ERR_CLIENT_SEND;
	}

	return TCP_OK;
}

/** receive data from tcp connection */
long Network::TCPClient::TCPReceive(char * ucBufferReceive, int iLenBufferReceive, int * iOutLenDataReceive)
{
	if(!m_bOpenedConnection)
	{
		return TCP_ERR_CLIENT_CLOSED;
	}
	if(NULL == ucBufferReceive)
	{
		return TCP_ERR_CLIENT_WRONG_PARAMS;
	}
	if(iLenBufferReceive<0) 
	{
		return TCP_ERR_CLIENT_WRONG_PARAMS;
	}
	if(NULL == iOutLenDataReceive)
	{
		return TCP_ERR_CLIENT_WRONG_PARAMS;
	}

	// Put the socket in non-blocking mode:
	//SetSocketBlockingEnabled(m_iSocket_id, false);
	//printf("Configure non blocking\r\n");

	int iTotal_received = 0;
	int inumRetry = 0;
	int nbRep = 0;
	char pTempBuffer[TCP_MAX_DATA];
	memset(pTempBuffer, 0x00, TCP_MAX_DATA);

	do
	{
		//reception reponse
		nbRep = recv(m_iSocket_id, pTempBuffer, TCP_MAX_DATA, 0);
		if (nbRep==SOCKET_ERROR) {
			
			*iOutLenDataReceive=0;
			return TCP_ERR_CLIENT_RECV;
		}

		// manage receiption
		if(nbRep > 0)
		{
			// calculate max copy
			if((iTotal_received + nbRep) <= iLenBufferReceive)
			{
				memcpy(ucBufferReceive + iTotal_received, pTempBuffer, nbRep);
				iTotal_received+=nbRep;
				memset(pTempBuffer, 0x00, TCP_MAX_DATA);
			}
			else
			{
				*iOutLenDataReceive=iLenBufferReceive;
				return TCP_BUFF_TOO_SMALL;
			}
		}
		else
		{
			inumRetry++;
			Timing::Timing::sleepInMilliSecond(100);
		}

	} while( (nbRep > 0) || ( inumRetry < CLIENT_MAX_RETRY));

	*iOutLenDataReceive = iTotal_received;
	return TCP_OK;
}

/** closing an open connection */
long Network::TCPClient::TCPclose()
{
	if(!m_bOpenedConnection)
	{
		return TCP_ERR_CLIENT_CLOSED;
	}

	int erreur;
	erreur = shutdown(m_iSocket_id, 2);
	if (erreur!=0) {
		// think if necessary to use WSAGetLastError() for debug
		return TCP_ERR_CLIENT_CLOSE_SOCKET;
	}

	erreur = closesocket(m_iSocket_id);
    if (erreur!=0) {
		return TCP_ERR_CLIENT_CLOSE_SOCKET;
	}
 
	erreur = WSACleanup();
	if (erreur!=0) {
		return TCP_ERR_CLIENT_CLEANUP;
	}

	return TCP_OK;
}