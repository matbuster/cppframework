
#include "testToolsHardwareDisk.h"
#include "cppFrameworkTesterDefines.h"

#include <stdio.h>

// framework include disk tools
#include "Tools/Hardware/Disk.h"

// ----------------------------------------------------------
int tester_tools_hardware_disk()
{
    int iReturnCode = TEST_OK;
    printf(STR_LINE_DISPLAY_SEP);
    printf("testing Tools::Hardware::Chrono\r\n");
    printf(STR_LINE_DISPLAY_SEP);

	double _dFreeSpace = Tools::Hardware::Disk::getDiskFreeSpace("C:\\");
	int _iFreeSpace = Tools::Hardware::Disk::getDiskFreeSpaceInMo("C:\\");

    return iReturnCode;	
}
// ----------------------------------------------------------
