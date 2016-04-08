/**
 * \file 		Date.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#include "Date.h"
#include "../toolsconstant.h"

#ifdef _WINDOWS
#include <windows.h>
#endif
#include <stdio.h>

/** return a date string value to prefix a file name
 * example : YYYY_MM_DD_HH_MM_SS_
 */
long Timing::Date::GetStringDateForFile(char * _pOutDateFormatted, int _iSizeBuffer, int * _iDateSize)
{
#ifdef _WINDOWS
	char pTempDate[STR_TINY];
	memset(pTempDate, 0x00, STR_TINY);

	SYSTEMTIME time;
	GetLocalTime(&time);

	sprintf(pTempDate, "%d_%d_%d_%d_%d_%d_",time.wYear,time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	if(STR_TINY > _iSizeBuffer)
	{
		return DATE_KO;
	}
	memcpy(_pOutDateFormatted, pTempDate, STR_TINY);
	*_iDateSize = STR_TINY;
#endif
	return DATE_OK;
}