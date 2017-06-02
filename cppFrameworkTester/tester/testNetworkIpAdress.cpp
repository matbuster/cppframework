
#include "testNetworkIpAdress.h"
#include "cppFrameworkTesterDefines.h"
#include "TesterReport.h"

#include <stdio.h>

#include "Network/IPADress.h"

// -------------------------------------------------------------------
int Test::tester_network_ip_v4_adress()
{
	Network::IPAdress * test_ip_01 = new Network::IPAdress(TEST_IPV4_MATCH_01);
	if(true != test_ip_01->IsIpv4())
	{
		printf(">tester_network_ip_v4_adress : %s FAILED\r\n", TEST_IPV4_MATCH_01);
		return TEST_KO;
	}
	delete test_ip_01;
	Network::IPAdress * test_ip_02 = new Network::IPAdress(TEST_IPV4_MATCH_02);
	if(true != test_ip_02->IsIpv4())
	{
		printf(">tester_network_ip_v4_adress : %s FAILED\r\n", TEST_IPV4_MATCH_02);
		return TEST_KO;
	}
	delete test_ip_02;
	Network::IPAdress * test_ip_03 = new Network::IPAdress(TEST_IPV4_MATCH_03);
	if(true != test_ip_03->IsIpv4())
	{
		printf(">tester_network_ip_v4_adress : %s FAILED\r\n", TEST_IPV4_MATCH_03);
		return TEST_KO;
	}
	delete test_ip_03;
	Network::IPAdress * test_ip_04 = new Network::IPAdress(TEST_IPV4_MATCH_04);
	if(true != test_ip_04->IsIpv4())
	{
		printf(">tester_network_ip_v4_adress : %s FAILED\r\n", TEST_IPV4_MATCH_04);
		return TEST_KO;
	}
	delete test_ip_04;

	// testing wrong ip adress
	Network::IPAdress * test_wrong_ip_01 = new Network::IPAdress(TEST_IPV4_WRONG_01);
	if(false != test_wrong_ip_01->IsIpv4())
	{
		printf(">tester_network_ip_v4_adress : %s FAILED\r\n", TEST_IPV4_WRONG_01);
		return TEST_KO;
	}
	delete test_wrong_ip_01;
	Network::IPAdress * test_wrong_ip_02 = new Network::IPAdress(TEST_IPV4_WRONG_02);
	if(false != test_wrong_ip_02->IsIpv4())
	{
		printf(">tester_network_ip_v4_adress : %s FAILED\r\n", TEST_IPV4_WRONG_02);
		return TEST_KO;
	}
	delete test_wrong_ip_02;
	Network::IPAdress * test_wrong_ip_03 = new Network::IPAdress(TEST_IPV4_WRONG_03);
	if(false != test_wrong_ip_03->IsIpv4())
	{
		printf(">tester_network_ip_v4_adress : %s FAILED\r\n", TEST_IPV4_WRONG_03);
		return TEST_KO;
	}
	delete test_wrong_ip_03;
	Network::IPAdress * test_wrong_ip_04 = new Network::IPAdress(TEST_IPV4_WRONG_04);
	if(false != test_wrong_ip_04->IsIpv4())
	{
		printf(">tester_network_ip_v4_adress : %s FAILED\r\n", TEST_IPV4_WRONG_04);
		return TEST_KO;
	}
	delete test_wrong_ip_04;
	Network::IPAdress * test_wrong_ip_05 = new Network::IPAdress(TEST_IPV4_WRONG_05);
	if(false != test_wrong_ip_05->IsIpv4())
	{
		printf(">tester_network_ip_v4_adress : %s FAILED\r\n", TEST_IPV4_WRONG_05);
		return TEST_KO;
	}
	delete test_wrong_ip_05;
	Network::IPAdress * test_wrong_ip_06 = new Network::IPAdress(TEST_IPV4_WRONG_06);
	if(false != test_wrong_ip_06->IsIpv4())
	{
		printf(">tester_network_ip_v4_adress : %s FAILED\r\n", TEST_IPV4_WRONG_06);
		return TEST_KO;
	}
	delete test_wrong_ip_06;
	Network::IPAdress * test_wrong_ip_07 = new Network::IPAdress(TEST_IPV4_WRONG_07);
	if(false != test_wrong_ip_07->IsIpv4())
	{
		printf(">tester_network_ip_v4_adress : %s FAILED\r\n", TEST_IPV4_WRONG_07);
		return TEST_KO;
	}
	delete test_wrong_ip_07;

	return TEST_OK;
}
// -------------------------------------------------------------------
int Test::tester_network_ip_v6_adress()
{
	Network::IPAdress * test_ip_01 = new Network::IPAdress(TEST_IPV6_MATCH_01);
	if(true != test_ip_01->IsIpv6())
	{
		printf(">tester_network_ip_v6_adress : %s FAILED\r\n", TEST_IPV6_MATCH_01);
		return TEST_KO;
	}
	delete test_ip_01;
	Network::IPAdress * test_ip_02 = new Network::IPAdress(TEST_IPV6_MATCH_02);
	if(true != test_ip_02->IsIpv6())
	{
		printf(">tester_network_ip_v6_adress : %s FAILED\r\n", TEST_IPV6_MATCH_02);
		return TEST_KO;
	}
	delete test_ip_02;
	Network::IPAdress * test_ip_03 = new Network::IPAdress(TEST_IPV6_MATCH_03);
	if(true != test_ip_03->IsIpv6())
	{
		printf(">tester_network_ip_v6_adress : %s FAILED\r\n", TEST_IPV6_MATCH_03);
		return TEST_KO;
	}

	// testing wrong ip adress
	Network::IPAdress * test_wrong_ip_01 = new Network::IPAdress(TEST_IPV6_WRONG_01);
	if(false != test_wrong_ip_01->IsIpv6())
	{
		printf(">tester_network_ip_v4_adress : %s FAILED\r\n", TEST_IPV6_WRONG_01);
		return TEST_KO;
	}
	delete test_wrong_ip_01;
	Network::IPAdress * test_wrong_ip_02 = new Network::IPAdress(TEST_IPV6_WRONG_02);
	if(false != test_wrong_ip_02->IsIpv6())
	{
		printf(">tester_network_ip_v4_adress : %s FAILED\r\n", TEST_IPV6_WRONG_02);
		return TEST_KO;
	}
	delete test_wrong_ip_02;

	return TEST_OK;
}
// ------------------------------------------------------------
int Test::tester_network_ip_adress()
{
    int iReturnCode = TEST_OK;
    Test::TesterReport::getInstance()->printHeader("testing Network: IP Address");

	iReturnCode = tester_network_ip_v4_adress();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Network::IPAddress", "tester_network_ip_v4_adress()");
	iReturnCode = tester_network_ip_v6_adress();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Network::IPAddress", "tester_network_ip_v6_adress()");

	return iReturnCode;
}
// ------------------------------------------------------------