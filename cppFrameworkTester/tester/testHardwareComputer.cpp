
#include "testHardwareComputer.h"
#include "cppFrameworkTesterDefines.h"

// include framework 
#include "Hardware/computer.h"
#include "toolsconstant.h"

// include other functions
#include <stdio.h>
#include <string.h>

// ----------------------------------------------------------
int tester_hardware_computer_getName()
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
int tester_hardware_computer()
{
    int iReturnCode = TEST_OK;

    printf(STR_LINE_DISPLAY_SEP);
    printf("testing Hardware::Computer\r\n");
    printf(STR_LINE_DISPLAY_SEP);

	iReturnCode = tester_hardware_computer_getName();

	return iReturnCode;
}
// ----------------------------------------------------------
