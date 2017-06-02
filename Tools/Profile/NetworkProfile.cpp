
#include "NetworkProfile.h"

#include "Hardware/computer.h"

// ----------------------------------------------------------------
Tools::Profile::NetworkProfile::NetworkProfile()
{
	m_bIsInitialized = false;

	memset(m_pComputerName, 0x00, STR_LONG);
	memset(m_pCurrentUserName, 0x00, STR_LONG);
#ifdef _WINDOWS
	memset(m_pDomainNameFlat, 0x00, STR_LONG);
	memset(m_pDomainNameDns, 0x00, STR_LONG);
#endif

	autoDetection();
}
Tools::Profile::NetworkProfile::~NetworkProfile()
{
}
// ----------------------------------------------------------------
long Tools::Profile::NetworkProfile::autoDetection()
{
	std::list<std::string> * _pListIpAdress = new std::list<std::string>();
	std::list<Hardware::Computer::st_network_interface> * _plistInterfaces = new std::list<Hardware::Computer::st_network_interface>();

	Hardware::Computer::getComputerName(m_pComputerName, STR_LONG);
	Hardware::Computer::getComputerUser(m_pCurrentUserName, STR_LONG);
	Hardware::Computer::getComputerIpv4Adress(&m_lAvailableIpv4Adress);
	Hardware::Computer::getNetworkInterfaces(_plistInterfaces);
#ifdef _WINDOWS
	Hardware::Computer::getNetworkDomainName(m_pDomainNameFlat, STR_LONG, m_pDomainNameDns, STR_LONG);
#endif
	delete _pListIpAdress;
	delete _plistInterfaces;

	m_bIsInitialized = true;
	return NETWORK_PROFILE_OK;
}
// ----------------------------------------------------------------
std::string Tools::Profile::NetworkProfile::getComputerName()
{
	return std::string(m_pComputerName);
}
// ----------------------------------------------------------------
std::string Tools::Profile::NetworkProfile::getCurrentUserName()
{
	return std::string(m_pCurrentUserName);
}
// ----------------------------------------------------------------
std::string Tools::Profile::NetworkProfile::getDomainNameFlat()
{
#ifdef _WINDOWS
	return std::string(m_pDomainNameFlat);
#else
	return std::string("");
#endif // _WINDOWS
}
// ----------------------------------------------------------------
std::string Tools::Profile::NetworkProfile::getDomainNameDns()
{
#ifdef _WINDOWS
	return std::string(m_pDomainNameDns);
#else
	return std::string("");
#endif // _WINDOWS
}
// ----------------------------------------------------------------
int Tools::Profile::NetworkProfile::getAvailableIpv4Counter()
{
	return (int)m_lAvailableIpv4Adress.size();
}
// ----------------------------------------------------------------
std::string Tools::Profile::NetworkProfile::getIpv4Adress(int index)
{
	if(index < 0 || index > getAvailableIpv4Counter())
	{
		return "";
	}
	int iCounter = 0;
	for(std::list<std::string>::iterator it = m_lAvailableIpv4Adress.begin(); it != m_lAvailableIpv4Adress.end(); it++)
	{
		if(index == iCounter) {
			return *it;
		}
		iCounter++;
	}
	return "";
}
// ----------------------------------------------------------------
void Tools::Profile::NetworkProfile::setComputerName(std::string _strComputerName)
{
	size_t minCopy = _strComputerName.size();
	if(STR_LONG < minCopy) minCopy = STR_LONG;

	memset(m_pComputerName, 0x00, STR_LONG);
	memcpy(m_pComputerName, _strComputerName.c_str(), minCopy);
}
// ----------------------------------------------------------------
void Tools::Profile::NetworkProfile::setCurrentUserName(std::string _strCurrentUserName)
{
	size_t minCopy = _strCurrentUserName.size();
	if(STR_LONG < minCopy) minCopy = STR_LONG;

	memset(m_pCurrentUserName, 0x00, STR_LONG);
	memcpy(m_pCurrentUserName, _strCurrentUserName.c_str(), minCopy);
}
// ----------------------------------------------------------------
void Tools::Profile::NetworkProfile::setDomainNameFlat(std::string _strDomainNameFlat)
{
	size_t minCopy = _strDomainNameFlat.size();
	if(STR_LONG < minCopy) minCopy = STR_LONG;
#ifdef _WINDOWS
	memset(m_pDomainNameFlat, 0x00, STR_LONG);
	memcpy(m_pDomainNameFlat, _strDomainNameFlat.c_str(), minCopy);
#endif // _WINDOWS
}
// ----------------------------------------------------------------
void Tools::Profile::NetworkProfile::setDomainNameDns(std::string _strDomainNameDns)
{
	size_t minCopy = _strDomainNameDns.size();
	if(STR_LONG < minCopy) minCopy = STR_LONG;

	memset(m_pComputerName, 0x00, STR_LONG);
	memcpy(m_pComputerName, _strDomainNameDns.c_str(), minCopy);
}
// ----------------------------------------------------------------
