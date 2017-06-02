/**
 * \file 		TcpServer.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */
 
#include "../toolsconstant.h"
#include "TcpServer.h"

#include "Timing/Timing.h"

#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

/** main constructor of class TCP */
Network::TCPServer::TCPServer()
{
	m_bConnected = false;
	m_bAccepted = false;
	memset(m_ucIPAdress, 0x00, STR_SHORT);
	m_iPort = 0;
	m_iSocket_id = 0;
	m_iSession_id = 0;
}
Network::TCPServer::~TCPServer()
{
}
/** Returns true on success, or false if there was an error */
bool Network::TCPServer::SetSocketBlockingEnabled(int fd, bool blocking)
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
/** connection function to a socket */
long Network::TCPServer::TCPconnect(char * cIPAdress, int iPort)
{
	if(iPort < 0)
	{
		return TCP_ERR_SERV_PARAMS;
	}

	long lReturn = 0;

#ifdef _WINDOWS
	lReturn = WSAStartup(MAKEWORD(2,2), &m_wsaData);
    if (lReturn!=0) {
        // see if WSAGetLastError() is needed for debug
		return TCP_ERR_SERV_WSAS;
	}
#endif // _WINDOWS

	// ouverture d'une socket
	m_iSocket_id = socket(AF_INET, SOCK_STREAM, 0);
	if (m_iSocket_id == INVALID_SOCKET)
	{
#ifdef _WINDOWS
		WSACleanup();
#endif	// _WINDOWS
		return TCP_ERR_SERV_CREATE_SOCKET;
	}

	// manage keyword to configure server to listen a specific adress or any
	if(memcmp(cIPAdress,KEY_STR_INADDR_ANY, sizeof(KEY_STR_INADDR_ANY)) == 0) {
		m_sockInInfo.sin_addr.s_addr = INADDR_ANY;	// Ecoute sur toutes les IP locales
	} else {
		m_sockInInfo.sin_addr.s_addr = inet_addr(cIPAdress);	// Ecoute sur toutes les IP locales
	}

	// lie la socket � une IP et un port d'�coute
	m_sockInInfo.sin_family = AF_INET;
	
	m_sockInInfo.sin_port=htons((u_short)iPort);			// Ecoute sur le port configure
	lReturn = bind(m_iSocket_id, (struct sockaddr*)&m_sockInInfo, sizeof(m_sockInInfo));
	if (lReturn!=0)
	{
#ifdef _WINDOWS
		WSACleanup();
#endif // _WINDOWS
		return TCP_ERR_SERV_BIND_PORT;
	}

	m_iPort = iPort;
	memcpy(m_ucIPAdress, cIPAdress, STR_SHORT);

	// attente d'ouverture de session
	// Initialisation dde l'erreur pour �tre sur que l'on entre dans la boucle
	// on tourne tant qu'une demande de session tcp n'a pas �t� re�ue.
	lReturn = 99;
	while(lReturn!=0) {
		lReturn = listen(m_iSocket_id, TCP_MAX_ACCEPTANCE);
	}

	m_bConnected = true;
	return TCP_SERVER_SUCCESS;
}
/** acceptation de la demande d'ouverture de session */ 
long Network::TCPServer::TCPaccept()
{
	return TCPaccept(&m_iSession_id);
}
/** acceptation de la demande d'ouverture de session */ 
long Network::TCPServer::TCPaccept(int * iSession_ID)
{
	if(NULL == iSession_ID)
	{
		return TCP_ERR_SERV_PARAMS;
	}
	if(!m_bConnected)
	{
		return TCP_ERR_SERV_NOT_CONNECT;
	}
#ifdef _WINDOWS
	int iSizeSrc = 0;
#endif // _WINDOWS
#ifdef LINUX
        socklen_t iSizeSrc = 0;
#endif
	// Attente reception de demande d'ouverture de session tcp (SYN)
	iSizeSrc = sizeof(m_sockInInfo); // Passe par une variable afin d'utiliser un pointeur
	*iSession_ID = accept(m_iSocket_id, (struct sockaddr*)&m_sockInInfo, &iSizeSrc);
	if(*iSession_ID == INVALID_SOCKET)
	{
#ifdef _WINDOWS
		WSACleanup();
#endif // _WINDOWS
		return TCP_ERR_SERV_ACCEPT;
	}

	m_bAccepted = true;
	return TCP_SERVER_SUCCESS;
}
/** send data via tcp connection */
long Network::TCPServer::TCPSend(char * ucBufferSend, int iLenBufferSend)
{
	return TCPSend(m_iSession_id, ucBufferSend, iLenBufferSend);
}
/** send data via tcp connection, using session ID */
long Network::TCPServer::TCPSend(int iSession_ID, char * ucBufferSend, int iLenBufferSend)
{
	if(!m_bConnected)
	{
		return TCP_ERR_SERV_NOT_CONNECT;
	}
	if(!m_bAccepted)
	{
		return TCP_ERR_SERV_NOT_ACCEPTED;
	}

	// d'un buffer via la socket
	int nb_recept = 0;
	int i_total_send = 0;
	do
	{
		// test, do not send a negative octets buffer
		if( (iLenBufferSend - i_total_send) < 0)
		{
#ifdef _WINDOWS
			WSACleanup();
#endif // _WINDOWS
			return TCP_ERR_SERV_SEND;
		}

		nb_recept = send(iSession_ID, ucBufferSend + i_total_send, (iLenBufferSend - i_total_send), 0);
		i_total_send += nb_recept;

		if (nb_recept == SOCKET_ERROR) {
#ifdef _WINDOWS
			WSACleanup();
#endif // _WINDOWS
			return TCP_ERR_SERV_SEND;
		}

		// tempo to wait
		if(i_total_send < iLenBufferSend)
		{
			Timing::Timing::sleepInMilliSecond(10);
		}

	} while(i_total_send < iLenBufferSend);

	return TCP_SERVER_SUCCESS;
}
/** receive data from tcp connection */
long Network::TCPServer::TCPReceive(char * ucBufferReceive, int iLenBufferReceive, int * iOutLenDataReceive)
{
	return TCPReceive(m_iSession_id, ucBufferReceive, iLenBufferReceive, iOutLenDataReceive);
}
long Network::TCPServer::TCPReceive(int iSession_ID, char * ucBufferReceive, int iLenBufferReceive, int * iOutLenDataReceive)
{
	return TCPReceive(iSession_ID, &ucBufferReceive, iLenBufferReceive, iOutLenDataReceive, false);
}
/** receive data from tcp connection, using session ID */
long Network::TCPServer::TCPReceive(int iSession_ID, char ** ucBufferReceive, int iLenBufferReceive, int * iOutLenDataReceive, bool bAllowAllocate)
{
	if(!m_bConnected)
	{
		return TCP_ERR_SERV_NOT_CONNECT;
	}
	if(!m_bAccepted)
	{
		return TCP_ERR_SERV_NOT_ACCEPTED;
	}

	int iSizeBuffer = 0;
	char * pBuffer = NULL;
	char * pReallocBuffer = NULL;
	char cTempBuffer[TCP_MAX_DATA];
	memset(cTempBuffer, 0x00, TCP_MAX_DATA);

	// Put the socket in non-blocking mode:
	SetSocketBlockingEnabled(iSession_ID, false);
	
	int i_total_received = 0;
	int nb_recept = 1;
	int i_try_to_receive_counter = 0;

	do
	{
		nb_recept = recv(iSession_ID, cTempBuffer, TCP_MAX_DATA, 0);
		if(nb_recept > 0)
		{
			// need to increase buffer size
			if(iSizeBuffer <= (i_total_received + nb_recept))
			{
				iSizeBuffer += TCP_MAX_DATA;
				pReallocBuffer = (char*) realloc(pBuffer, iSizeBuffer * sizeof(char));
				if(NULL == pReallocBuffer)
				{
#ifdef _WINDOWS
					WSACleanup();
#endif // _WINDOWS
					free(pBuffer);
					return TCP_ERR_SERV_INVALID_PT;
				}
				pBuffer = pReallocBuffer;
			}
			
			memcpy(pBuffer+i_total_received, cTempBuffer, nb_recept);
			i_total_received += nb_recept;

		} else {
			i_try_to_receive_counter++;
			Timing::Timing::sleepInMilliSecond(100);
		}

	} while( (nb_recept > 0) || (i_try_to_receive_counter < MAX_TRY_RECEIVED) );

	// copy output data if data buffer size is efficient
	if( false == bAllowAllocate && (i_total_received > iLenBufferReceive) ) 
	{
#ifdef _WINDOWS
		WSACleanup();
#endif // _WINDOWS
		free(pBuffer);
		return TCP_ERR_SERV_RECV;
	}
	if(i_total_received > 0)
	{
		*iOutLenDataReceive = i_total_received;
		if(!bAllowAllocate)
		{
			int maxCopy = TCP_MAX_DATA;
			if(i_total_received < maxCopy) {
				maxCopy = i_total_received;
			}
			memcpy(*ucBufferReceive, pBuffer, maxCopy);
		}
		else 
		{
			*ucBufferReceive = (char*)malloc(i_total_received * sizeof(char));
			memcpy(*ucBufferReceive, pBuffer, i_total_received);
		}
		free(pBuffer);
	}
	else
	{
		free(pBuffer);
		return TCP_ERR_SERV_RECV;
	}

	return TCP_SERVER_SUCCESS;
}
/** shutdown socket session connection */
long Network::TCPServer::TCPshutdown()
{
	return TCPshutdown(m_iSession_id);
}
/** shutdown socket session connection, using session ID */
long Network::TCPServer::TCPshutdown(int iSession_ID)
{
	if(!m_bConnected)
	{
		return TCP_ERR_SERV_NOT_CONNECT;
	}
	if(!m_bAccepted)
	{
		return TCP_ERR_SERV_NOT_ACCEPTED;
	}

	int iRet = 0;
	// 2 signifie socket d'�mission et d'�coute
	iRet = shutdown(iSession_ID, 2);
	if (iRet!=0){
		return TCP_ERR_SERV_SHUTDOWN;
	}
#ifdef _WINDOWS
	iRet = closesocket(iSession_ID);
#endif // _WINDOWS
#ifdef LINUX
        iRet = close(iSession_ID);
#endif
	if (iRet!=0){
		return TCP_ERR_SERV_SHUTDOWN;
	}
	
	m_bAccepted = false;

	return TCP_SERVER_SUCCESS;
}
/** closing an open connection */
long Network::TCPServer::TCPclose()
{
	long lRet = 0; 

#ifdef _WINDOWS
	lRet = closesocket(m_iSocket_id);
	WSACleanup();
#endif // _WINDOWS
#ifdef LINUX
        lRet = close(m_iSocket_id);
#endif
	if(lRet != 0) return TCP_ERR_SERV_CLOSE;

	m_bConnected = false;
	return TCP_SERVER_SUCCESS;
}
