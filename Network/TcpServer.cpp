/**
 * \file 		TcpServer.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */
 
#include "../toolsconstant.h"
#include "TcpServer.h"

#include <string.h>

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
/** connection function to a socket */
long Network::TCPServer::TCPconnect(char * cIPAdress, int iPort)
{
	if(iPort < 0)
	{
		return TCP_ERR_PARAMS;
	}

	long lReturn = 0;

#ifdef WIN32
	lReturn = WSAStartup(MAKEWORD(2,2), &m_wsaData);
    if (lReturn!=0) {
        // see if WSAGetLastError() is needed for debug
		return TCP_ERR_WSAS;
	}
#endif

	// ouverture d'une socket
	m_iSocket_id = socket(AF_INET, SOCK_STREAM, 0);
	if (m_iSocket_id == INVALID_SOCKET)
	{
#ifdef WIN32
		WSACleanup();
#endif
		return TCP_ERR_CREATE_SOCKET;
	}

	// manage keyword to configure server to listen a specific adress or any
	if(memcmp(cIPAdress,KEY_STR_INADDR_ANY, sizeof(KEY_STR_INADDR_ANY)) == 0) {
		m_sockInInfo.sin_addr.s_addr = INADDR_ANY;	// Ecoute sur toutes les IP locales
	} else {
		m_sockInInfo.sin_addr.s_addr = inet_addr(cIPAdress);	// Ecoute sur toutes les IP locales
	}

	// lie la socket � une IP et un port d'�coute
	m_sockInInfo.sin_family = AF_INET;
	
	m_sockInInfo.sin_port=htons(iPort);			// Ecoute sur le port configure
	lReturn = bind(m_iSocket_id, (struct sockaddr*)&m_sockInInfo, sizeof(m_sockInInfo));
	if (lReturn!=0)
	{
#ifdef WIN32
		WSACleanup();
#endif
		return TCP_ERR_BIND_PORT;
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
		return TCP_ERR_PARAMS;
	}
	if(!m_bConnected)
	{
		return TCP_ERR_NOT_CONNECT;
	}
#ifdef WIN32
	int iSizeSrc = 0;
#endif
#ifdef LINUX
        socklen_t iSizeSrc = 0;
#endif
	// Attente reception de demande d'ouverture de session tcp (SYN)
	iSizeSrc = sizeof(m_sockInInfo); // Passe par une variable afin d'utiliser un pointeur
	*iSession_ID = accept(m_iSocket_id, (struct sockaddr*)&m_sockInInfo, &iSizeSrc);
	if(*iSession_ID == INVALID_SOCKET)
	{
#ifdef WIN32
		WSACleanup();
#endif
		return TCP_ERR_ACCEPT;
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
		return TCP_ERR_NOT_CONNECT;
	}
	if(!m_bAccepted)
	{
		return TCP_ERR_NOT_ACCEPTED;
	}

	// d'un buffer via la socket
	unsigned long nb_recept = 0;
	nb_recept = send(iSession_ID, ucBufferSend, iLenBufferSend, 0);
	if (nb_recept == SOCKET_ERROR) {
#ifdef WIN32
		WSACleanup();
#endif
		return TCP_ERR_SEND;
	}

	return TCP_SERVER_SUCCESS;
}
/** receive data from tcp connection */
long Network::TCPServer::TCPReceive(char * ucBufferReceive, int iLenBufferReceive, int * iOutLenDataReceive)
{
	return TCPReceive(m_iSession_id, ucBufferReceive, iLenBufferReceive, iOutLenDataReceive);
}
/** receive data from tcp connection, using session ID */
long Network::TCPServer::TCPReceive(int iSession_ID, char * ucBufferReceive, int iLenBufferReceive, int * iOutLenDataReceive)
{
	if(!m_bConnected)
	{
		return TCP_ERR_NOT_CONNECT;
	}
	if(!m_bAccepted)
	{
		return TCP_ERR_NOT_ACCEPTED;
	}

	char cTempBuffer[TCP_MAX_DATA];
	memset(cTempBuffer, 0x00, TCP_MAX_DATA);

	int nb_recept = 0;
	nb_recept = recv(iSession_ID, cTempBuffer, TCP_MAX_DATA, 0);

	// copy output data if data buffer size is efficient
	if(nb_recept > iLenBufferReceive) 
	{
#ifdef WIN32
		WSACleanup();
#endif
		return TCP_ERR_RECV;
	}
	if(nb_recept > 0)
	{
		*iOutLenDataReceive = nb_recept;
		memcpy(ucBufferReceive, cTempBuffer, nb_recept);
	}
	else return TCP_ERR_RECV;

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
		return TCP_ERR_NOT_CONNECT;
	}
	if(!m_bAccepted)
	{
		return TCP_ERR_NOT_ACCEPTED;
	}

	int iRet = 0;
	// 2 signifie socket d'�mission et d'�coute
	iRet = shutdown(iSession_ID, 2);
	if (iRet!=0){
		return TCP_ERR_SHUTDOWN;
	}
#ifdef WIN32
	iRet = closesocket(iSession_ID);
#endif
#ifdef LINUX
        iRet = close(iSession_ID);
#endif
	if (iRet!=0){
		return TCP_ERR_SHUTDOWN;
	}
	
	m_bAccepted = false;

	return TCP_SERVER_SUCCESS;
}
/** closing an open connection */
long Network::TCPServer::TCPclose()
{
	long lRet = 0; 

#ifdef WIN32
	lRet = closesocket(m_iSocket_id);
	WSACleanup();
#endif
#ifdef LINUX
        lRet = close(m_iSocket_id);
#endif
	if(lRet != 0) return TCP_ERR_CLOSE;

	m_bConnected = false;
	return TCP_SERVER_SUCCESS;
}
