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

// ---------------------------------------------------
#define DIRTOOLS_OK					0
#define DIRTOOLS_KO					1
#define DIRTOOLS_INVALID_PARAMS		2
#define DIRTOOLS_INVALID_FOLDER		3

// ---------------------------------------------------
#if defined(WIN32) || defined(_WIN32) 
#define PATH_SEPARATOR "\\" 
#else 
#define PATH_SEPARATOR "/" 
#endif 

// ---------------------------------------------------
#define UNIX_PATH_USR_LIB           "/usr/lib"

// ---------------------------------------------------
#include <string>
#include <list>

namespace Tools {

	namespace Directory {
	
		// -----------------------------------------------------------------------------------
		/**! getter on the number of sub directory in the target directory */
		long GetNumberSubfolder(char * _pcPath, int _iMaxSizePath, long * _plNumberSubfolder);

		// -----------------------------------------------------------------------------------
		/**! getter on the list of subfolders */
		long GetSubfolderList(char * _pcPath, int _iMaxSizePath, std::list<std::string> * pListSubfolder);

		// -----------------------------------------------------------------------------------
		/** function which return the executable path */
		long GetExeDirectoryPath(char * _pcPath, int _iMaxSizePath);

		// -----------------------------------------------------------------------------------
		/** function to get the executable path of _pModuleName */
		long GetExeDirectoryPath(char * _pModuleName, char * _pcPath, int _iMaxSizePath);

		// -----------------------------------------------------------------------------------
		/** function to get a specific path file */
		long GetSpecificFolder(int _idPath, char * _pSpecificPath, int _iMaxSizePath);

		// -----------------------------------------------------------------------------------
		/**! function to get the upper folder
		 * \param [out] _pUpperFolder : value of the upper folder
		 * \param [out] _iSizeUpperFolder : size of the upper folder string
		 * \param [in] _pCurrentFolder : value of the current folder
		 * \param [in] _iSizeCurrentFolder : size of the current folder
		 */
		long GetUpperFolder(char * _pUpperFolder, int * _iSizeUpperFolder, char * _pCurrentFolder, int _iSizeCurrentFolder);

		// -----------------------------------------------------------------------------------
		/**! function to test if a directory exist 
		 * \param [in] _pDirectoryPath : path of the target directory
		 * \return true if the directory exist, false if not
		 */
		bool DirectoryExist(char * _pDirectoryPath);
	};
};

#endif //DIRECTORY_H