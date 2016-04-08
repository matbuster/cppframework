/**
 * \file 		File.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef FILE_TOOLS_H
#define FILE_TOOLS_H

#define TOOLS_FILE_OK	0
#define TOOLS_FILE_KO	1

namespace Tools {
	
	namespace File {
	
		/** funciton to return the size of a specific file */
		long GetFileSize(char * _pInPathFile, long * _lOutFileSize);

		/** function to get the path of a file path 
			example: C:\myfile.txt get C:\ */
		long GetPathFromFilePath(char * _pFilepath, char * _pOutput);

		/** function to get the file name of a file path 
			example: C:\myfile.txt get myfile */
		long GetNameFromFilePath(char * _pFilepath, char * _pOutput);

		/** function to get the extension of a file path 
			example: C:\myfile.txt get .txt */
		long GetExtensionFromFilePath(char * _pFilepath, char * _pOutput);

		/** function to rename a specific file, replace an existing file old name, by a new one */
		long FileRename(char * _pOldName, char * _pNewName);

		/** remove the specific file in directory */
		long FileRemove(char * _pFileName);

		/** function to check if the file exist or not */
		bool FileExists(char * _pFilepath);
	};
};

#endif /* FILE_TOOLS_H */