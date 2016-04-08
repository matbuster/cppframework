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

long Tools::Directory::GetExeDirectoryPath(char *_pcPath, int _iMaxSizePath) {

    return GetExeDirectoryPath(NULL, _pcPath, _iMaxSizePath);
}

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


long Tools::Directory::GetSpecificFolder(int _idPath, char * _pSpecificPath, int _iMaxSizePath)
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
