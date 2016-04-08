/**
 * \file 		File.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include "File.h"
#include "../String/StringTools.h"
#include "../../toolsconstant.h"

#ifdef _WINDOWS
#include <Windows.h>
#endif

#include <string>
#include <fstream>

#define MAX_PATH_DEPTH		128

/** funciton to return the size of a specific file */
long Tools::File::GetFileSize(char * _pInPathFile, long * _lOutFileSize)
{
	long lFileSizeOctets = 0;
	FILE *pFile = NULL;

	// get the file stream
	pFile = fopen(_pInPathFile, "rb" );
	if(NULL != pFile) {

		// set the file pointer to end of file
		// and get the file size
		fseek( pFile, 0, SEEK_END );
		lFileSizeOctets = ftell( pFile );

		// close stream and release buffer
		fclose( pFile );
	}
	*_lOutFileSize = lFileSizeOctets;

	return TOOLS_FILE_OK;
}
/** function to get the path of a file path 
	example: C:\myfile.txt get C:\ */
long Tools::File::GetPathFromFilePath(char * _pFilepath, char * _pOutput)
{
	char pTempMessage[STR_LONG];
	std::string strpath = _pFilepath;

	char ** pSplittedPath = (char**)malloc(MAX_PATH_DEPTH * sizeof(char*));
	for(int i = 0; i < MAX_PATH_DEPTH; i++) pSplittedPath[i] = (char*)malloc(STR_LONG * sizeof(char));;
	
	for(int i =0;i< MAX_PATH_DEPTH;i++) memset(pSplittedPath[i],0x00,STR_LONG);
	memset(pTempMessage, 0x00, STR_LONG);

	int iNumResult = 0;
	Tools::String::StringSplit(pSplittedPath, &iNumResult, (char*)strpath.c_str(), (int)strpath.length(), '\\');

	if(iNumResult > 0) 
	{
		strcpy(pTempMessage, pSplittedPath[0]);
		strcat(pTempMessage, "\\");
		for(int i = 1;i< iNumResult - 1; i++) 
		{
			strcat(pTempMessage, pSplittedPath[i]);
			strcat(pTempMessage, "\\");
		}
	}

	for(int i = 0; i < MAX_PATH_DEPTH; i++) free(pSplittedPath[i]);
	free(pSplittedPath);

	memcpy(_pOutput, pTempMessage, STR_LONG);

	return TOOLS_FILE_OK;
}
/** function to get the file name of a file path 
	example: C:\myfile.txt get myfile */
long Tools::File::GetNameFromFilePath(char * _pFilepath, char * _pOutput)
{
	std::string strpath = _pFilepath;

	char ** pSplittedPath = (char**)malloc(MAX_PATH_DEPTH * sizeof(char*));
	for(int i = 0; i < MAX_PATH_DEPTH; i++) pSplittedPath[i] = (char*)malloc(STR_LONG * sizeof(char));;
	
	for(int i =0;i< MAX_PATH_DEPTH;i++) memset(pSplittedPath[i],0x00,STR_LONG);

	int iNumResult = 0;
	Tools::String::StringSplit(pSplittedPath, &iNumResult, (char*)strpath.c_str(), (int)strpath.length(), '\\');

	if(iNumResult > 1) 
	{
		memcpy(_pOutput, pSplittedPath[iNumResult-1], STR_LONG);
	}

	for(int i = 0; i < MAX_PATH_DEPTH; i++) free(pSplittedPath[i]);
	free(pSplittedPath);

	return TOOLS_FILE_OK;
}
/** function to get the extension of a file path 
	example: C:\myfile.txt get .txt */
long Tools::File::GetExtensionFromFilePath(char * _pFilepath, char * _pOutput)
{
	std::string strpath = _pFilepath;

	char ** pSplittedPath = (char**)malloc(MAX_PATH_DEPTH * sizeof(char*));
	for(int i = 0; i < MAX_PATH_DEPTH; i++) pSplittedPath[i] = (char*)malloc(STR_LONG * sizeof(char));;
	
	for(int i =0;i< MAX_PATH_DEPTH;i++) memset(pSplittedPath[i],0x00,STR_LONG);

	int iNumResult = 0;
	Tools::String::StringSplit(pSplittedPath, &iNumResult, (char*)strpath.c_str(), (int)strpath.length(), '.');

	if(iNumResult > 1) 
	{
		memcpy(_pOutput, pSplittedPath[iNumResult-1], STR_LONG);
	}

	for(int i = 0; i < MAX_PATH_DEPTH; i++) free(pSplittedPath[i]);
	free(pSplittedPath);

	return TOOLS_FILE_OK;
}
/** function to rename a specific file, replace an existing file old name, by a new one */
long Tools::File::FileRename(char * _pOldName, char * _pNewName)
{
	if(NULL == _pOldName)
	{
		return TOOLS_FILE_KO;
	}
	if(NULL == _pNewName)
	{
		return TOOLS_FILE_KO;
	}

	int result;
	result = rename( _pOldName , _pNewName );
	if ( result == 0 )
	{
		return TOOLS_FILE_OK;
	}
	else
	{
		return TOOLS_FILE_KO;
	}
}
/** remove the specific file in directory */
long Tools::File::FileRemove(char * _pFileName)
{
	if(NULL == _pFileName)
	{
		return TOOLS_FILE_KO;
	}

	if( remove( _pFileName ) != 0 ) 
	{
		return TOOLS_FILE_KO;
	}

	return TOOLS_FILE_OK;
}
/** function to check if the file exist or not */
bool Tools::File::FileExists(char * _pFilepath)
{
    if (FILE *file = fopen(_pFilepath, "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}


	
