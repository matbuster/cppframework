
#include "TcpConnection.h"

// ---------------------------------------------------------------------------
Network::TcpConnection::TcpConnection(char * pIpAdress, unsigned int uiPort)
	: IPAdress(pIpAdress)
{
	m_uiPort = uiPort;
}
// ---------------------------------------------------------------------------
Network::TcpConnection::~TcpConnection()
{
}
// ---------------------------------------------------------------------------
unsigned int Network::TcpConnection::getPort()
{
	return m_uiPort;
}
// ---------------------------------------------------------------------------
void Network::TcpConnection::setPort(unsigned int uiPort)
{
	m_uiPort = uiPort;
}
// ---------------------------------------------------------------------------