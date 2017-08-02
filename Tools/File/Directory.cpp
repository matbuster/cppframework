/**
 * \file 		Directory.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

// Include des en-tetes standard c
#include <stddef.h>
#include <stdio.h>

// Include des en-tetes windows
#ifdef _WINDOWS
#include <Windows.h>
#include <Winbase.h>
#include <Shlobj.h>
#endif //_WINDOWS

// Include des en-tetes windows
#ifdef LINUX
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#endif //LINUX

#ifdef MFC_BUILD
#define CAST_STR_IN
#else
#define CAST_STR_IN LPCSTR
#endif

// Include des en-tetes du framework
#include "Directory.h"
#include "toolsconstant.h"

#include "../String/Conversion.h"
#include "../String/StdStringTools.h"
#include "../Collection/GetterCollection.hpp"

#include <string>
#include <list>

#ifdef _WINDOWS
#include <windows.h>
#include <tchar.h> 
#include <strsafe.h>
#endif // _WINDOWS

#ifdef LINUX
#include <sys/stat.h>
#endif // LINUX

// ------------------------------------------------------------------------------
long Tools::Directory::GetNumberSubfolder(char * _pcPath, int _iMaxSizePath, long * _plNumberSubfolder)
{
	std::list<std::string> pSubFolders;
	long lRet = Tools::Directory::GetSubfolderList(_pcPath, _iMaxSizePath, &pSubFolders);
	if(DIRTOOLS_OK != lRet)
	{
		*_plNumberSubfolder = -1;
		return DIRTOOLS_KO;
	}

	*_plNumberSubfolder = pSubFolders.size();
	return DIRTOOLS_OK;
}
// ------------------------------------------------------------------------------
long Tools::Directory::GetSubfolderList(char * _pcPath, int _iMaxSizePath, std::list<std::string> * pListSubfolder)
{
#ifdef _WINDOWS
	// windows implementation
	WIN32_FIND_DATA ffd;
	unsigned int iSizConvert = 0;
	wchar_t  szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError=0;
  
	memset(szDir, 0, MAX_PATH * sizeof(wchar_t));
	Tools::String::convert_char_array_to_LPWSTR(_pcPath, _iMaxSizePath, szDir, &iSizConvert); 
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

	// Find the first file in the directory.
	hFind = FindFirstFile(szDir, &ffd);
	if (INVALID_HANDLE_VALUE == hFind) 
	{
		return DIRTOOLS_KO;
	} 
   
	// List all the files in the directory with some info about them.
	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			std::string strOut;
			Tools::String::convert_std_wstring_to_std_string(ffd.cFileName, &strOut );

			std::string folder(strOut);
			pListSubfolder->push_back(folder);
		}
		
	}
	while (FindNextFile(hFind, &ffd) != 0);
 
	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES) 
	{	
		return DIRTOOLS_KO;
	}
	FindClose(hFind);

#endif // _WINDOWS

	return DIRTOOLS_OK;
}
// ------------------------------------------------------------------------------
long Tools::Directory::GetExeDirectoryPath(char *_pcPath, int _iMaxSizePath) {

    return GetExeDirectoryPath(NULL, _pcPath, _iMaxSizePath);
}
// ------------------------------------------------------------------------------
long Tools::Directory::GetExeDirectoryPath(char * _pModuleName, char * _pcPath, int _iMaxSizePath) {

#ifdef _WINDOWS
    int iLenghtPath = 0;
    int ii = 0;

	if (2 > (iLenghtPath = GetModuleFileNameA(GetModuleHandleA((CAST_STR_IN)_pModuleName), _pcPath, _iMaxSizePath))) {
        return false;
    }

    //Recherche le dernier '\' dans le nom de l'executable
    for (ii = iLenghtPath; --ii >= 0;) {
        if (_pcPath[ii] == '\\') {
            _pcPath[ii + 1] = '\0';
            break;
        }
    } // [Fin] Recupere le chemin de l'application

    return true;
#endif //_WINDOWS

#ifdef LINUX
    char* path_end;
    /* Read the target of /proc/self/exe.  */
    if (readlink("/proc/self/exe", _pcPath, _iMaxSizePath) <= 0) {
        return false;
    }
        
    /* Find the last occurence of a forward slash, the path separator.  */
    path_end = strrchr(_pcPath, '/');
    if (path_end == NULL) {
        return false;
    }
    /* Advance to the character past the last slash.  */
    ++path_end;
    
    /* Obtain the directory containing the program by truncating the
       path after the last slash.  */
    *path_end = '\0';
    
    return true;
#endif //LINUX
    
}
// ------------------------------------------------------------------------------
long Tools::Directory::GetSpecificFolder(int _idPath, char * _pSpecificPath, int /*_iMaxSizePath*/)
{
	char localPath[STR_LONG] = {0};
#ifdef _WINDOWS	
	int winId= 0;
	if(PATH_WIN == _idPath) winId = CSIDL_WINDOWS;
	else if(PATH_SYS_32 == _idPath) winId = CSIDL_SYSTEM;
	else if(PATH_SYS_64 == _idPath) winId = CSIDL_SYSTEMX86;
	else if(PATH_PROG_FILE_X86== _idPath) winId = CSIDL_PROGRAM_FILESX86;
	else if(PATH_PROG_FILE_X64== _idPath) winId = CSIDL_PROGRAM_FILES;
	else if(PATH_APP_DATA== _idPath) winId = CSIDL_COMMON_APPDATA;
	else if(PATH_DESKTOP == _idPath) winId = CSIDL_DESKTOP;
	else if(PATH_DOCUMENTS == _idPath) winId = CSIDL_MYDOCUMENTS;
	else if(PATH_STARTSUP == _idPath) winId = CSIDL_STARTUP;
	else return DIRTOOLS_KO;
	
	SHGetFolderPathA(NULL, winId, 0, NULL, localPath);
#endif
        
#ifdef LINUX
	if(PATH_SYS_32 == _idPath) { memcpy(localPath, UNIX_PATH_USR_LIB, sizeof(UNIX_PATH_USR_LIB));}
	else if(PATH_SYS_64 == _idPath) { memcpy(localPath, UNIX_PATH_USR_LIB, sizeof(UNIX_PATH_USR_LIB));}
        else return DIRTOOLS_KO;
        
#endif // LINUX
        
	memcpy(_pSpecificPath, localPath, STR_LONG);        
	return DIRTOOLS_OK;
}
// ------------------------------------------------------------------------------
long Tools::Directory::GetUpperFolder(char * _pUpperFolder, int * _iSizeUpperFolder, char * _pCurrentFolder, int _iSizeCurrentFolder)
{
	if(NULL == _pUpperFolder || NULL == _iSizeUpperFolder || NULL == _pCurrentFolder )
	{
		return DIRTOOLS_INVALID_PARAMS;
	}
	if(false == DirectoryExist(_pCurrentFolder))
	{
		return DIRTOOLS_INVALID_FOLDER;
	}

	std::string delimiter(PATH_SEPARATOR);

	// get and split all string items from path
	std::string pInputTemp(_pCurrentFolder, _iSizeCurrentFolder);
	std::list<std::string> pSplitted;
	Tools::String::StringSplit(&pSplitted, pInputTemp, PATH_SEPARATOR);

	if(pSplitted.size() > 0) {

		// rebuild the path
		std::string out;
		for(int i = 0; i<pSplitted.size()-1; i++) {
			std::string item = Tools::Collection::get(&pSplitted, i);
			out.append(item);
			out.append(std::string(PATH_SEPARATOR));
		}

		// copy
		memcpy(_pUpperFolder, out.c_str() , out.size());
		*_iSizeUpperFolder = out.size();
	}

	return DIRTOOLS_OK;
}		
// -----------------------------------------------------------------------------------
bool Tools::Directory::DirectoryExist(char * _pDirectoryPath)
{

#ifdef _WINDOWS
	DWORD ftyp = GetFileAttributesA(_pDirectoryPath);
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
#endif // _WINDOWS

#ifdef LINUX

	struct stat sb;
	if (stat(pathname, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		return true;
	}
	else return false;

#endif // LINUX
}
// ------------------------------------------------------------------------------

