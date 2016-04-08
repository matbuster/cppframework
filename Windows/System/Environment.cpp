/**
 * \file 		Environment.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#include "Environment.h"
#include "toolsconstant.h"
#include "Tools/String/StringTools.h"

#ifdef _WINDOWS
#include <Windows.h>

/** function to read a specific environment variable */
long Windows::Environment::GetVariable(char * cKeyEnvironmentName, long lKeyEnvironmentNameSize, char * cOutValue) 
{
	// précondition
	if(NULL == cKeyEnvironmentName) 
	{
		return ENV_KO;
	}
	if(NULL == lKeyEnvironmentNameSize)
	{
		return ENV_KO;
	}

    const DWORD buffSize = 65535;
    static char buffer[buffSize];

	char tempOutput[STR_LONG];
	memset(tempOutput, 0x00, STR_LONG);

	DWORD dwReturn = ::GetEnvironmentVariableA(cKeyEnvironmentName, buffer, lKeyEnvironmentNameSize);
	if(0 == dwReturn) 
	{
		DWORD dwError = GetLastError();
		if(ERROR_ENVVAR_NOT_FOUND == dwError)
		{
			return ENV_VAR_NOT_FOUND;
		} else return ENV_KO;
	} 
	else 
	{
		// if ret is non szero, return the size of buffer
		memcpy(cOutValue, buffer, dwReturn);
	}
	return ENV_OK;
}

long Windows::Environment::GetPath(char * cOutValue, long lSizeOutValue, long * lSizePath)
{
	if(NULL == cOutValue)
	{
		return ENV_KO;
	}
	if(NULL == lSizePath)
	{
		return ENV_KO;
	}

	// get the size of path
    char * buffer;
	DWORD dwSize = ::GetEnvironmentVariableA(PATH_STR_VALUE, NULL, 0);
	if(0 == dwSize) 
	{
		DWORD dwError = GetLastError();
		if(ERROR_ENVVAR_NOT_FOUND == dwError)
		{
			return ENV_VAR_NOT_FOUND;
		} else return ENV_KO;
	}
	if(lSizeOutValue < (long)dwSize)
	{
		return ENV_SIZE_TOO_SMALL;
	}

	// fill the output buffer, using the right size and a allocated buffer
	buffer = (char*) malloc(dwSize);
	DWORD dwReturn = ::GetEnvironmentVariableA(PATH_STR_VALUE, buffer, dwSize);
	if(0 == dwReturn) 
	{
		DWORD dwError = GetLastError();
		if(ERROR_ENVVAR_NOT_FOUND == dwError)
		{
			return ENV_VAR_NOT_FOUND;
		} else return ENV_KO;
	}	
	memcpy(cOutValue, buffer, dwSize);
	*lSizePath = (long)dwSize;
	free(buffer);

	return ENV_OK;
}

long Windows::Environment::GetPaths(std::list<std::string> * paths)
{
	char path[MAX_PATH_SIZE] = {0};
	long lPathSize = 0;

	long lRet = Windows::Environment::GetPath(path, MAX_PATH_SIZE, &lPathSize);
	if(ENV_OK != lRet)
	{
		return lRet;
	}
			
	char ** pSplittedPath = (char**)malloc(MAX_PATH_CONTENT * sizeof(char*));
	for(int i = 0; i < MAX_PATH_CONTENT; i++) { pSplittedPath[i] = (char*)malloc(STR_LONG * sizeof(char)); memset(pSplittedPath[i] , 0x00, STR_LONG);}

	int iNumberResult = 0;

	int iNumPath = Tools::String::StringCountOccurence(path, lPathSize, ';');
	Tools::String::StringSplit(pSplittedPath, &iNumberResult, path, lPathSize, ';');

	for(int i = 0; i < MAX_PATH_CONTENT; i++) {paths->push_back(pSplittedPath[i]) ;free(pSplittedPath[i]);}
	free(pSplittedPath);

	return ENV_OK;
}
#endif /* _WINDOWS */
