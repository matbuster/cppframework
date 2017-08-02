#ifndef FILE_FOLDER_H
#define FILE_FOLDER_H

// ------------------------------------------------------------------------------
// includes framework
#include "FileFolderInfos.h"

// ------------------------------------------------------------------------------
// includes generic
#include <list>
#include <string>

// ------------------------------------------------------------------------------
// defines errors and return
#define FF_TOOLS_OK					0
#define FF_TOOLS_KO					1
#define FF_TOOLS_INVALID_PARAMS		2
#define FF_TOOLS_FILE_NOT_FOUND		3
#define FF_INVALID_PARAM_STAT		4

// ------------------------------------------------------------------------------
#define FF_SHORT_STR				26

namespace Tools {
	
	namespace Files {
	
		// ------------------------------------------------------------------------------
		/**! get the list of files and folders information for the target path
		 * \param [in] _strPath: input path
		 * \param [out] _lFilesAndFolderInfos : file and folder list
		 * \return error code
		 */
		long getFileAndFolderInformations(std::string _strPath, std::list<Tools::Files::FileFolderInfos *> * _lFilesAndFolderInfos);

		// ------------------------------------------------------------------------------
		/** get the list of files and folders information for the target path 
		 * \param [in] _strPath: input path
		 * \param [out] _pListSubfolder : file and folders contained by the path
		 * \return error code
		 */
		long getFilesAndFolderList(std::string _strPath, std::list<std::string> * _pListSubfolder);

		// ------------------------------------------------------------------------------
		/**! function to get informations about creation date 
		 * \param [in] _strFilename : filename
		 * \param [out] _fileInfos : file informations 
		 */
		long getFilesAndFolderDateInformations(std::string _strFilename, Tools::Files::FileFolderInfos * _fileInfos);
	};
};

#endif // FILE_FOLDER_H