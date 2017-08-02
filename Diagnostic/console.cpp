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
// constant defines definition
#define DC_CONS_STR_SHORT					128
#define DC_CONS_STR_TINY					32
#define DC_CONS_LOG_MAX_HEXA_PER_LINE		20

// ------------------------------------------------------------------------
bool basicDisplayOptionnal(char * message, bool bAddCrJump)
{
	if(NULL == message) {
		return false;
	}
#ifdef CONSOLE_ALLOW_DISPLAY
	char cMessage[STR_LONG];

	memset(cMessage, 0x00, STR_LONG);
	strcpy(cMessage, message);
	if(true == bAddCrJump)
	{
		strcat(cMessage, "\n");
	}
	printf(cMessage);
#endif
	return true;
}
// ------------------------------------------------------------------------
bool Diagnostic::display(char * message)
{
	return basicDisplayOptionnal(message, true);
}
// ------------------------------------------------------------------------
bool Diagnostic::displayNoJump(char * message)
{
	return basicDisplayOptionnal(message, false);
}
// ------------------------------------------------------------------------
bool Diagnostic::display(char * functionName, char * message)
{
	char cMessage[STR_LONG];
	memset(cMessage, 0x00, STR_LONG);

	strcpy(cMessage, functionName);
	strcat(cMessage, "\t");
	strcat(cMessage, message);

	return display(cMessage);
}

// ------------------------------------------------------------------------
bool Diagnostic::displayArgs(char * message, ...)
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
bool Diagnostic::displayArgsWithFunctionName(char * functionName, char * message, ...)
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
// ------------------------------------------------------------------------
bool Diagnostic::displayBuffer(unsigned char * _pInputBuffer, long _iSizeInputBuffer)
{
	bool bSuccess = false;

	// logging a series of LOG_MAX_HEXA_PER_LINE on n lines
	char cTempLine[DC_CONS_STR_SHORT];
	char cTempChar[DC_CONS_STR_TINY];
	int i = 0;
	int iIndex = 0;

	memset(cTempLine, 0x00, DC_CONS_STR_SHORT);
	memset(cTempChar, 0x00, DC_CONS_STR_TINY);

	for(i = 0; i < _iSizeInputBuffer; i++ )
	{
		if(iIndex >= DC_CONS_LOG_MAX_HEXA_PER_LINE)
		{
			iIndex=0;
			display(cTempLine);
			memset(cTempLine, 0x00, DC_CONS_STR_SHORT);
		}

		// work and copy for line
		sprintf(cTempChar,"%02X ", _pInputBuffer[i]);
		if(iIndex == 0) strcpy(cTempLine,cTempChar);
		else strcat(cTempLine,cTempChar);
		iIndex++;
	}

	// print the last value cat in temp line
	display(cTempLine);

	return bSuccess;
}
// ------------------------------------------------------------------------

