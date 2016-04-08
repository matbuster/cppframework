/**
 * \file 		Directory.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef DIRECTORY_H
#define DIRECTORY_H

#define PATH_WIN			0
#define PATH_SYS_32			1
#define PATH_SYS_64			2
#define PATH_PROG_FILE_X86	3
#define PATH_PROG_FILE_X64	4
#define PATH_APP_DATA		5
#define PATH_DESKTOP		6
#define PATH_DOCUMENTS		7
#define PATH_STARTSUP		8

#define DIRTOOLS_OK			0
#define DIRTOOLS_KO			1

#define UNIX_PATH_USR_LIB           "/usr/lib"

namespace Tools {

	namespace Directory {
	
		/** function which return the executable path */
		long GetExeDirectoryPath(char * _pcPath, int _iMaxSizePath);

		/** function to get the executable path of _pModuleName */
		long GetExeDirectoryPath(char * _pModuleName, char * _pcPath, int _iMaxSizePath);

		/** function to get a specific path file */
		long GetSpecificFolder(int _idPath, char * _pSpecificPath, int _iMaxSizePath);
	};
};

#endif //DIRECTORY_H