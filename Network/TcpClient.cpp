/**
 * \file 		TcpClient.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */
 
#include "..\toolsconstant.h"
#include "TcpClient.h"

#include <stdio.h>
#include <Winsock2.h>

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
		return TCP_ERR_WRONG_PARAMS;
	}
	if(iPort < 0)
	{
		return TCP_ERR_WRONG_PARAMS;
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
	addr.sin_port   = htons (m_iPort);

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
		return TCP_ERR_CLOSED;
	}
	if(NULL == ucBufferSend)
	{
		return TCP_ERR_WRONG_PARAMS;
	}
	if(iLenBufferSend<0) 
	{
		return TCP_ERR_WRONG_PARAMS;
	}

	// envoi des donnees 
	int nbSend = send(m_iSocket_id, ucBufferSend, iLenBufferSend, 0);
    if (nbSend == SOCKET_ERROR) {
		// check if necessary to use WSAGetLastError() for debug
		return TCP_ERR_SEND;
	}

	return TCP_OK;
}

/** receive data from tcp connection */
long Network::TCPClient::TCPReceive(char * ucBufferReceive, int iLenBufferReceive, int * iOutLenDataReceive)
{
	if(!m_bOpenedConnection)
	{
		return TCP_ERR_CLOSED;
	}
	if(NULL == ucBufferReceive)
	{
		return TCP_ERR_WRONG_PARAMS;
	}
	if(iLenBufferReceive<0) 
	{
		return TCP_ERR_WRONG_PARAMS;
	}
	if(NULL == iOutLenDataReceive)
	{
		return TCP_ERR_WRONG_PARAMS;
	}

	//reception reponse
	int nbRep = recv(m_iSocket_id, ucBufferReceive, iLenBufferReceive, 0);
	if (nbRep==SOCKET_ERROR) {
		return TCP_ERR_RECV;
	}

	*iOutLenDataReceive = nbRep;

	return TCP_OK;
}

/** closing an open connection */
long Network::TCPClient::TCPclose()
{
	if(!m_bOpenedConnection)
	{
		return TCP_ERR_CLOSED;
	}

	int erreur;
	erreur = shutdown(m_iSocket_id, 2);
	if (erreur!=0) {
		// think if necessary to use WSAGetLastError() for debug
		return TCP_ERR_CLOSE_SOCKET;
	}

	erreur = closesocket(m_iSocket_id);
    if (erreur!=0) {
		return TCP_ERR_CLOSE_SOCKET;
	}
 
	erreur = WSACleanup();
	if (erreur!=0) {
		return TCP_ERR_CLEANUP;
	}

	return TCP_OK;
}