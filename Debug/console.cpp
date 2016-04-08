/**
 * \file 		console.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#include "console.h"
#include "../toolsconstant.h"

#define CONSOLE_ALLOW_DISPLAY

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

// ------------------------------------------------------------------------
bool Debug::display(char * message)
{
	if(NULL == message) {
		return false;
	}
#ifdef CONSOLE_ALLOW_DISPLAY
	char cMessage[STR_LONG];

	memset(cMessage, 0x00, STR_LONG);
	strcpy(cMessage, message);
	strcat(cMessage, "\n");

	printf(cMessage);
#endif
	return true;
}


// ------------------------------------------------------------------------
bool Debug::display(char * functionName, char * message)
{
	char cMessage[STR_LONG];
	memset(cMessage, 0x00, STR_LONG);

	strcpy(cMessage, functionName);
	strcat(cMessage, "\t");
	strcat(cMessage, message);

	return display(cMessage);
}

// ------------------------------------------------------------------------
bool Debug::displayArgs(char * message, ...)
{
	bool bSuccess = false;

    char cTempMessage[STR_LONG];
    va_list args;

    memset(cTempMessage, 0x00, STR_LONG);

    va_start(args, message);
    vsprintf(cTempMessage, message, args);

    bSuccess = display(cTempMessage);
    va_end(args);

	return bSuccess;
}

// ------------------------------------------------------------------------
bool Debug::displayArgs(char * functionName, char * message, ...)
{
	bool bSuccess = false;
	char cMessage[STR_LONG];
	va_list args;

	memset(cMessage, 0x00, STR_LONG);

    va_start(args, message);
    vsprintf(cMessage, message, args);

    bSuccess = display(functionName, cMessage);
    va_end(args);

	return bSuccess;
}