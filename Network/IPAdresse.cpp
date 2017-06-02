
// ---------------------------------------------------------------------
// includes
#include "IPAdress.h"
#include "Tools/String/Regex_Helper.h"

// ---------------------------------------------------------------------
Network::IPAdress::IPAdress(char * _pIpAdress)
{
	m_bIsIpv4 = false;
	m_bIsIpv6 = false;
	m_bIpIsValid = false;

	if(NULL != _pIpAdress) {

		m_strIpAdress = std::string(_pIpAdress);
		m_bIpIsValid = CheckValidity();

	} else {

		m_bIpIsValid = false;
	}
}
Network::IPAdress::IPAdress(const IPAdress& _pIpAdress)
{
	m_strIpAdress = _pIpAdress.getIpAdress();
	m_bIsIpv4 = _pIpAdress.IsIpv4();
	m_bIsIpv6 = _pIpAdress.IsIpv6();
	m_bIpIsValid = m_bIsIpv4 || m_bIsIpv6;
}
Network::IPAdress::~IPAdress()
{
}
// ---------------------------------------------------------------------
bool Network::IPAdress::CheckValidity()
{
	m_bIsIpv4 = Tools::Regex::match_ipV4adress(m_strIpAdress);
	m_bIsIpv6 = Tools::Regex::match_ipv6adress(m_strIpAdress);

	return m_bIsIpv4 || m_bIsIpv6;
}
// ---------------------------------------------------------------------
bool Network::IPAdress::IsIpv4() const
{
	return m_bIsIpv4;
}
// ---------------------------------------------------------------------
bool Network::IPAdress::IsIpv6() const
{
	return m_bIsIpv6;
}
// ---------------------------------------------------------------------
std::string Network::IPAdress::getIpAdress() const
{
	return m_strIpAdress;
}
// ---------------------------------------------------------------------
bool Network::IPAdress::setIpAdress(std::string _strIpAdress)
{
	m_strIpAdress = _strIpAdress;
	return CheckValidity();
}
// ---------------------------------------------------------------------
bool Network::IPAdress::setIpAdress(char * _pIPpAdress)
{
	if(NULL == _pIPpAdress) {
		return false;
	}
	else return setIpAdress(std::string(_pIPpAdress));
}
// ---------------------------------------------------------------------
