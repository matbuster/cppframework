/**
 * \file 		FileLog.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#include "../toolsconstant.h"
#include "FileTxt.h"
#include "FileLog.h"

#ifdef _WINDOWS
#include <windows.h>
#include <time.h>
#endif

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/** main constructor of the class, inherit from FilteTxt*/
FileIO::FileLog::FileLog(char * cFilename)
	:FileTxt(cFilename)
{
	FileTxtOpen(fileappend);
	m_iLogPrioFilter = 0;
}

/** destructor */
FileIO::FileLog::~FileLog()
{
	FileTxtClose();
}

/** get the corresponding date and hour [YY/MM/DD]\t[HH:MM:SS] */ 
void FileIO::FileLog::getDate(char * cOutDate) 
{
#ifdef _WINDOWS
	char cTempDate[STR_SHORT];
	struct tm  tstruct;
 
	memset(cTempDate, 0x00, STR_SHORT);

	time_t  timev = time(0);
	//time(&timev);
	tstruct = *localtime(&timev);
	sprintf(cTempDate,"[%d/%d/%d]\t[%d:%d:%d]",(1900 + tstruct.tm_year), tstruct.tm_mon, tstruct.tm_mday, tstruct.tm_hour, tstruct.tm_min, tstruct.tm_sec);

	memcpy(cOutDate, cTempDate, STR_SHORT);
#else
	memcpy(cOutDate,STR_DEFAULT_DATE, sizeof(STR_DEFAULT_DATE));
#endif
}

/** get a corresponding message to the priority enum */
char * FileIO::FileLog::getPrioMessage(FilePriority enPrio)
{
	if(flPrioDebug == enPrio) {
		return (char*)STR_PRIO_DEBUG;
	} else if(flPrioProd == enPrio) {
		return (char*)STR_PRIO_PROD;
	} else if(flPrioInfo == enPrio) {
		return (char*)STR_PRIO_INFO;
	} else if(flPrioWarning == enPrio) {
		return (char*)STR_PRIO_WARNING;
	} else if(flPrioError == enPrio) {
		return (char*)STR_PRIO_ERROR;
	} else {
		return (char*)STR_PRIO_NOPRIO;
	}
}

/** get a corresponding message to the origin enum */
char * FileIO::FileLog::getOrigMessage(FileOrigin enOrig)
{
	if( flOrigHardware == enOrig) {
		return (char*)STR_PRIO_HARD;
	} else if( flOrigSoftware == enOrig) {
		return (char*)STR_PRIO_SOFT;
	} else if( flOrigCPU == enOrig) {
		return (char*)STR_PRIO_CPU;
	} else if( flOrigNetwork == enOrig) {
		return (char*)STR_PRIO_NETWORK;
	} else if( flOrigSystem == enOrig) {
		return (char*)STR_PRIO_SYSTEM;
	} else if( flOrigComm == enOrig) {
		return (char*)STR_PRIO_COMM;
	} else if(flOrigConfig == enOrig) {
		return (char*)STR_PRIO_CONFIG;
	} else {
		return (char*)STR_PRIO_NOORIG;
	}
}
/** function to check the filter validity, true if log is authorized, false if not */
bool FileIO::FileLog::CheckFilter(FilePriority enPrio)
{
	if( m_iLogPrioFilter & enPrio)
	{
		return true;
	} else return false;
}
/** function to set the value of filter, levels of FilePriority */
long FileIO::FileLog::SetFilter(int iFilterValue) 
{
	m_iLogPrioFilter = iFilterValue;
	return FILE_SUCCESS;
}
/** function to check if log rotate is required */
bool FileIO::FileLog::LogRotate()
{
	char pNewFileName[STR_LONG];
	char pFolder[STR_LONG];
	char pFile[STR_LONG];
	char pTempDate[STR_TINY];

	int iLenBuffer = STR_TINY;
	int iOutDate = 0;
	long lFileSize = 0;

	memset(pTempDate, 0x00, STR_TINY);
	memset(pFolder, 0x00, STR_LONG);
	memset(pNewFileName, 0x00, STR_LONG);
	memset(pFile, 0x00, STR_LONG);

	// checking the size of file
	Tools::File::GetFileSize(m_cFilename, &lFileSize);
	if(MAX_LOGFILE_SIZE > lFileSize)
	{
		// close file
		FileTxtClose();

		// get the corresponding date
		Timing::Date::GetStringDateForFile(pTempDate, iLenBuffer, &iOutDate);
	
		// get file info
		Tools::File::GetPathFromFilePath(m_cFilename, pFolder);
		Tools::File::GetNameFromFilePath(m_cFilename, pFile);
	
		strcpy(pNewFileName, pFolder);
		strcat(pNewFileName, pTempDate);
		strcat(pNewFileName, pFile);

		// rename current logfile
		Tools::File::FileRename(m_cFilename, pNewFileName);
		Tools::File::FileRemove(m_cFilename);

		// open file
		FileTxtOpen(m_mode);

		return true;
	}

	return false;
}
/** generic function to log an information without any Prio/Orig (default value) */
long FileIO::FileLog::Log(char * cMessage)
{
	return FileIO::FileLog::Log(FileIO::flPrioNoPrio, FileIO::flOrigNone, cMessage);
}

/** generic function to log an information without any Prio/Orig (default value) with argument */
long FileIO::FileLog::LogArguments(char * format, ... )
{
	char cTempMessage[STR_LONG];
	memset(cTempMessage, 0x00, STR_LONG);

	long lRet = 0;
	va_list args;
	va_start (args, format);
	vsprintf  (cTempMessage, format, args);
	
	lRet = FileIO::FileLog::Log(FileIO::flPrioNoPrio, FileIO::flOrigNone, cTempMessage);
	va_end (args);

	return lRet;
}

/** Log generique pour une commentaire dans le fichier */
long FileIO::FileLog::Log(FilePriority enPrio, FileOrigin enOrig, char * cMessage)
{
	char cTempDate[STR_SHORT];
	char cTempThread[STR_TINY];
	char cTempPrio[STR_TINY];
	char cTempOrig[STR_TINY];
	char cTempLog[2 * STR_LONG];

	if(false == CheckFilter(enPrio))
	{
		return FILE_SUCCESS;
	}

	memset(cTempDate, 0x00, STR_SHORT);
	memset(cTempThread, 0x00, STR_TINY);
	memset(cTempPrio, 0x00, STR_TINY);
	memset(cTempOrig, 0x00, STR_TINY);
	memset(cTempLog ,0x00, 2 * STR_LONG);

	getDate(cTempDate);
	
	strcpy(cTempLog, cTempDate);
	strcat(cTempLog, "\t");
#ifdef _WINDOWS
	int idThread = GetCurrentThreadId();
	sprintf(cTempThread,"%d",idThread);
	strcat(cTempLog, cTempThread);
	strcat(cTempLog, "\t");
#endif
	strcat(cTempLog, getPrioMessage(enPrio));
	strcat(cTempLog, "\t");
	strcat(cTempLog, getOrigMessage(enOrig));
	strcat(cTempLog, "\t");
	strcat(cTempLog, cMessage);
	strcat(cTempLog, "\r\n");

#ifdef LOG_CONSOLE
	printf(cTempLog);
#endif //LOG_CONSOLE

	//LogRotate();

	return FileTxtWrite(cTempLog, 0);
}

/** Log generique pour une commentaire dans le fichier */
long FileIO::FileLog::LogArguments(FilePriority enPrio, FileOrigin enOrig, char * format, ... )
{
	char cTempMessage[STR_LONG];
	memset(cTempMessage, 0x00, STR_LONG);

	long lRet = 0;
	va_list args;
	va_start (args, format);
	vsprintf  (cTempMessage, format, args);
	
	lRet = FileIO::FileLog::Log(enPrio, enOrig, cTempMessage);
	va_end (args);

	return lRet;
}

/** log an hexadecimal buffer */
long FileIO::FileLog::LogHexaBuffer(unsigned char * ucBuffer, int iSzBuffer)
{
	return FileIO::FileLog::LogHexaBuffer(FileIO::flPrioNoPrio, FileIO::flOrigNone, ucBuffer, iSzBuffer);
}

/** log an hexadecimal buffer */
long FileIO::FileLog::LogHexaBuffer(FilePriority enPrio, FileOrigin enOrig, unsigned char * ucBuffer, int iSzBuffer)
{
	// logging a series of LOG_MAX_HEXA_PER_LINE on n lines
	char cTempLine[STR_SHORT];
	char cTempChar[STR_TINY];
	int i = 0;
	int iIndex = 0;

	memset(cTempLine, 0x00, STR_SHORT);
	memset(cTempChar, 0x00, STR_TINY);

	for(i = 0; i < iSzBuffer; i++ )
	{
		if(iIndex >= LOG_MAX_HEXA_PER_LINE)
		{
			iIndex=0;
			FileIO::FileLog::Log(enPrio, enOrig, cTempLine);
			memset(cTempLine, 0x00, STR_SHORT);
		}

		// work and copy for line
		sprintf(cTempChar,"%02X ", ucBuffer[i]);
		if(iIndex == 0) strcpy(cTempLine,cTempChar);
		else strcat(cTempLine,cTempChar);
		iIndex++;
	}

	// print the last value cat in temp line
	FileIO::FileLog::Log(enPrio, enOrig, cTempLine);
	memset(cTempLine, 0x00, LOG_MAX_HEXA_PER_LINE);
	return FILE_SUCCESS;
}
