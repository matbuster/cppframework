
#include "testHardwareComputer.h"
#include "cppFrameworkTesterDefines.h"
#include "TesterReport.h"

// include framework 
#include "Hardware/computer.h"
#include "toolsconstant.h"

// include other functions
#include <stdio.h>
#include <string.h>

// ----------------------------------------------------------
int Test::tester_hardware_computer_getName()
{
	char pTestBuffer[STR_LONG];
	memset(pTestBuffer, 0x00, STR_LONG);

	Hardware::Computer::getComputerName(pTestBuffer, STR_LONG);
	if(NULL == pTestBuffer)
	{
		return TEST_KO;
	}

	return TEST_OK;
}
// ----------------------------------------------------------
int Test::tester_hardware_computer_getIpAdressAvailable()
{
	std::list<std::string> pListIpAdress; 

	Hardware::Computer::getComputerIpv4Adress(&pListIpAdress);
	return TEST_OK;
}
// ----------------------------------------------------------
int Test::tester_hardware_computer_getInterfaceAvailable()
{
	std::list<Hardware::Computer::st_network_interface> pListInterfaces;
	Hardware::Computer::getNetworkInterfaces(&pListInterfaces);
	return TEST_OK;
}
// ----------------------------------------------------------
int Test::tester_hardware_computer()
{
    int iReturnCode = TEST_OK;

    Test::TesterReport::getInstance()->printHeader("testing Hardware::Computer");

	iReturnCode = tester_hardware_computer_getName();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Hardware::Computer", "tester_hardware_computer_getName()");
	iReturnCode = tester_hardware_computer_getIpAdressAvailable();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Hardware::Computer", "tester_hardware_computer_getIpAdressAvailable()");
	iReturnCode = tester_hardware_computer_getInterfaceAvailable();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Hardware::Computer", "tester_hardware_computer_getInterfaceAvailable()");

	return iReturnCode;
}
// ----------------------------------------------------------
