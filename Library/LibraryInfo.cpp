/**
 * \file 		LibraryInfo.cpp
 * \date 		06/01/2017
 * \author 		NSJ
 */

#include <stdio.h>
#include <string.h>
#include <string>

#include "LibraryInfo.h"

Library::LibraryInfo::LibraryInfo() {
}


Library::LibraryInfo::~LibraryInfo() {
}

bool Library::LibraryInfo::getLibraryName(char * /*_pcName*/) {

	//TODO_NSJ_TIME// 
	//https://msdn.microsoft.com/fr-fr/library/windows/desktop/ms647464(v=vs.85).aspx
	/*char fileEntry[1024];
	sprintf(fileEntry, "\\StringFileInfo\\%04X04B0\\InternalName", GetUserDefaultLangID());
	if (!VerQueryValue(verData, (LPCWSTR)fileEntry, (VOID FAR* FAR*)&lpBuffer, &size))
	{
		return false;
	}*/


	return false;
}

bool Library::LibraryInfo::getLibraryDescription(char * /*_pcDescription*/) {

	//TODO_NSJ_TIME// 
	//https://msdn.microsoft.com/fr-fr/library/windows/desktop/ms647464(v=vs.85).aspx
	/*char fileEntry[1024];
	sprintf(fileEntry, "\\StringFileInfo\\%04X04B0\\FileDescription", GetUserDefaultLangID());
	if (!VerQueryValue(verData, (LPCWSTR)fileEntry, (VOID FAR* FAR*)&lpBuffer, &size))
	{
		return false;
	}*/

	return false;
}

bool Library::LibraryInfo::getLibraryCompanyName(char * /*_pcCompanyName*/) {

	//TODO_NSJ_TIME// 
	//https://msdn.microsoft.com/fr-fr/library/windows/desktop/ms647464(v=vs.85).aspx
	/*char fileEntry[1024];
	sprintf(fileEntry, "\\StringFileInfo\\%04X04B0\\CompanyName", GetUserDefaultLangID());
	if (!VerQueryValue(verData, (LPCWSTR)fileEntry, (VOID FAR* FAR*)&lpBuffer, &size))
	{
		return false;
	}*/

	return false;
}

bool Library::LibraryInfo::getLibraryCopyright(char * /*_pcCopyright*/) {

	//TODO_NSJ_TIME// 
	//https://msdn.microsoft.com/fr-fr/library/windows/desktop/ms647464(v=vs.85).aspx
	/*char fileEntry[1024];
	sprintf(fileEntry, "\\StringFileInfo\\%04X04B0\\LegalCopyright", GetUserDefaultLangID());
	if (!VerQueryValue(verData, (LPCWSTR)fileEntry, (VOID FAR* FAR*)&lpBuffer, &size))
	{
		return false;
	}*/

	return false;
}

bool Library::LibraryInfo::getLibraryVersion(char * _pcVersion) {

#ifdef _WINDOWS
	TCHAR szVersionFile[MAX_PATH]; 
	DWORD  verHandle = 0;
	UINT   size      = 0;
	LPBYTE lpBuffer  = NULL;
	DWORD  verSize   = 0;
	LPSTR verData    = NULL;

	if (!GetModuleFileName(NULL, szVersionFile, MAX_PATH )) {
		return false;
	}

	verSize   = GetFileVersionInfoSize( szVersionFile, &verHandle);
	if (verSize == 0) {
		return false;
	}
	
	verData = (LPSTR) malloc(verSize);
	if (!GetFileVersionInfo( szVersionFile, verHandle, verSize, verData)) {
		free(verData);
		return false;
	}

	if (!VerQueryValue(verData, (LPCWSTR)"\\" ,(VOID FAR* FAR*)&lpBuffer, &size)) {
		free(verData);
		return false;
	}

	if (0 == size) {
		free(verData);
		return false;
	}

	VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO *)lpBuffer;
	if (verInfo->dwSignature != 0xfeef04bd) {
		free(verData);
		return false;
	}

	// Doesn't matter if you are on 32 bit or 64 bit,
	// DWORD is always 32 bits, so first two revision numbers
	// come from dwFileVersionMS, last two come from dwFileVersionLS
	sprintf(_pcVersion, "%d.%d.%d.%d",
		( verInfo->dwFileVersionMS >> 16 ) & 0xffff,
		( verInfo->dwFileVersionMS >>  0 ) & 0xffff,
		( verInfo->dwFileVersionLS >> 16 ) & 0xffff,
		( verInfo->dwFileVersionLS >>  0 ) & 0xffff
		);

	free(verData);	
#endif // _WINDOWS

	return true;
}



