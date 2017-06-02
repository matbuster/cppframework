
#include "computer.h"
#include "../toolsconstant.h"

#ifdef _WINDOWS
//#include <windows.h>
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <DSRole.h>
// includes library
#pragma comment(lib, "netapi32.lib")
#include "../Tools/String/Conversion.h"
#endif // _WINDOWS

#ifdef LINUX
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <limits.h>
#endif // LINUX

#include <string>
#include <list>
#include <stdio.h>     

// -----------------------------------------------------------------
long Hardware::Computer::getComputerName(char * _pComputerName, unsigned int _iSizeBufferComputerName)
{
	if(NULL == _pComputerName)
	{
		return HAR_COMP_INVALID_PARAM;
	}

#ifdef _WINDOWS

	DWORD dwTempSize = _iSizeBufferComputerName;
	wchar_t lpBuffer[STR_SHORT];

	memset(lpBuffer, 0x00, STR_SHORT);
	if(TRUE == GetComputerName((LPWSTR)lpBuffer, &dwTempSize))
	{
		if(dwTempSize > _iSizeBufferComputerName)
		{
			return HAR_BUFFER_TOO_SMALL;
		}
		if(CONVERT_OK != Tools::String::convert_LPWSTR_to_char_array(lpBuffer, STR_SHORT, _pComputerName, _iSizeBufferComputerName))
		{
			return HAR_COMP_KO;
		}
	}
	else return HAR_COMP_KO;

#endif // _WINDOWS
        
#ifdef LINUX
    char hostname[HOST_NAME_MAX];
    memset(hostname, 0x00, HOST_NAME_MAX);
    
    int result = gethostname(hostname, HOST_NAME_MAX);
    if (result)
    {
      return HAR_COMP_KO;
    }       
    memcpy(_pComputerName, hostname, HOST_NAME_MAX);
    
    //printf("hostname %s \r\n", hostname);
#endif // LINUX

	return HAR_COMP_OK;
}
// -----------------------------------------------------------------
long Hardware::Computer::getComputerUser(char * _pComputerUser, unsigned int _iSizeBufferComputerName)
{
	if(NULL == _pComputerUser)
	{
		return HAR_COMP_INVALID_PARAM;
	}

#ifdef _WINDOWS

	DWORD dwTempSize = _iSizeBufferComputerName;
	wchar_t lpBuffer[STR_SHORT];

	memset(lpBuffer, 0x00, STR_SHORT);

	BOOL bResult = GetUserName(lpBuffer, &dwTempSize);
	if(FALSE == bResult)
	{
		return HAR_COMP_KO;
	}

	if(CONVERT_OK != Tools::String::convert_LPWSTR_to_char_array(lpBuffer, dwTempSize, _pComputerUser, _iSizeBufferComputerName))
	{
		return HAR_COMP_KO;
	}

#endif // _WINDOWS
        
#ifdef LINUX
    char username[LOGIN_NAME_MAX];
    memset(username, 0x00, LOGIN_NAME_MAX);
    
    int result = getlogin_r(username, LOGIN_NAME_MAX);
    if (result)
    {
      return HAR_COMP_KO;
    }
    memcpy(_pComputerUser, username, LOGIN_NAME_MAX);
    
    //printf("username %s \r\n", hostname);
#endif // LINUX
    
	return HAR_COMP_OK;    
}
// -----------------------------------------------------------------
long Hardware::Computer::getComputerIpv4Adress(std::list<std::string> * _pListIpAdress)
{
	if(NULL == _pListIpAdress)
	{
		return HAR_COMP_INVALID_PARAM;
	}

#ifdef _WINDOWS
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
		return 255;
	}

	char ac[80];
	if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
		WSAGetLastError();
		return 1;
	}

	struct hostent *phe = gethostbyname(ac);
	if (phe == 0) {
		return 1;
	}

	for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
		struct in_addr addr;
		memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));

		std::string currIp(inet_ntoa(addr));
		_pListIpAdress->push_back(currIp);
	}

	WSACleanup();
#endif // _WINDOWS

#ifdef LINUX
        
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            //printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
            
            std::string currIp(addressBuffer);
            _pListIpAdress->push_back(currIp);
            
        } else if (ifa->ifa_addr->sa_family == AF_INET6) { // check it is IP6
            // is a valid IP6 Address
            tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            //printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
        } 
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
    
#endif // LINUX

	return HAR_COMP_OK;
}
// -----------------------------------------------------------------
long Hardware::Computer::getNetworkInterfaces(std::list<Hardware::Computer::st_network_interface> * _plistInterfaces)
{	
#ifdef _WINDOWS
    WSADATA WinsockData;
    if (WSAStartup(MAKEWORD(2, 2), &WinsockData) != 0) {
        return 2;
    }

    SOCKET sd = WSASocket(AF_INET, SOCK_DGRAM, 0, 0, 0, 0);
    if (sd == SOCKET_ERROR) {
		return 1;
    }

    INTERFACE_INFO InterfaceList[20];
    unsigned long nBytesReturned;
    if (WSAIoctl(sd, SIO_GET_INTERFACE_LIST, 0, 0, &InterfaceList,
			sizeof(InterfaceList), &nBytesReturned, 0, 0) == SOCKET_ERROR) {
		return 1;
    }

    int nNumInterfaces = nBytesReturned / sizeof(INTERFACE_INFO);
    for (int i = 0; i < nNumInterfaces; ++i) {

		st_network_interface currInterface;
		memset(&currInterface, 0x00, sizeof(currInterface));

        sockaddr_in * pAddress;
        pAddress = (sockaddr_in *) & (InterfaceList[i].iiAddress);
		std::string currIp(inet_ntoa(pAddress->sin_addr));
		memcpy(currInterface.pIpAdress, currIp.c_str(), currIp.length());

        pAddress = (sockaddr_in *) & (InterfaceList[i].iiBroadcastAddress);
		std::string currBroadcast(inet_ntoa(pAddress->sin_addr));
		memcpy(currInterface.pBroadcastAdress, currBroadcast.c_str(), currBroadcast.length());

        pAddress = (sockaddr_in *) & (InterfaceList[i].iiNetmask);
		std::string currNetmask(inet_ntoa(pAddress->sin_addr));
		memcpy(currInterface.pBroadcastAdress, currNetmask.c_str(), currNetmask.length());

		currInterface.nFlags = InterfaceList[i].iiFlags;
		
		if (currInterface.nFlags & IFF_UP) currInterface.isUp = true;
        else currInterface.isUp = false;
		if (currInterface.nFlags & IFF_POINTTOPOINT) currInterface.isPointToPoint = true;
		if (currInterface.nFlags & IFF_LOOPBACK) currInterface.isLoopback = true;
		if (currInterface.nFlags & IFF_BROADCAST) currInterface.isBroadcast = true;
		if (currInterface.nFlags & IFF_MULTICAST) currInterface.isMulticast = true;

		_plistInterfaces->push_back(currInterface);
    }

    WSACleanup();
#endif // _WINDOWS

	return HAR_COMP_OK;
}
// -----------------------------------------------------------------
long Hardware::Computer::getNetworkDomainName(char * pDomainNameFlat, unsigned int iSizeDomainNameFlat, char * pDomainNameDns, unsigned int iSizeDomainNameDns)
{
	if(NULL == pDomainNameFlat || NULL == pDomainNameDns)
	{
		return HAR_COMP_INVALID_PARAM;
	}

#ifdef _WINDOWS
    DSROLE_PRIMARY_DOMAIN_INFO_BASIC * info;
    DWORD dw;

    dw = DsRoleGetPrimaryDomainInformation(NULL,
                                           DsRolePrimaryDomainInfoBasic,
                                           (PBYTE *)&info);
    if (dw != ERROR_SUCCESS)
    {
		return HAR_COMP_KO;
    }

    if (info->DomainNameDns == NULL)
    {
		return HAR_COMP_INTERNAL_FAILED;
    }
    else
    {
		if(CONVERT_OK != Tools::String::convert_LPWSTR_to_char_array(info->DomainNameDns, sizeof(info->DomainNameDns), pDomainNameDns, iSizeDomainNameDns))
		{
			return HAR_COMP_KO;
		}
		if(CONVERT_OK != Tools::String::convert_LPWSTR_to_char_array(info->DomainNameFlat, sizeof(info->DomainNameFlat), pDomainNameFlat, iSizeDomainNameFlat))
		{
			return HAR_COMP_KO;
		}
    }

#endif // _WINDOWS

	return HAR_COMP_OK;
}
// -----------------------------------------------------------------
