
#include "FileFolder.h"

// framework includes
#include "../File/Directory.h"
#include "../File/File.h"
#include "../String/Conversion.h"

#include <iterator>
#include <algorithm>

#ifdef _WINDOWS
#include <Windows.h>
#include <tchar.h> 
#include <strsafe.h>

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#endif // _WINDOWS

#include <stdio.h>

// ------------------------------------------------------------------

std::string globalReplace(
    std::string::const_iterator begin,
    std::string::const_iterator end,
    std::string const& before,
    std::string const& after )
{
    std::string retval;
    std::back_insert_iterator<std::string> dest( retval );
    std::string::const_iterator current = begin;
    std::string::const_iterator next
            = std::search( current, end, before.begin(), before.end() );
    while ( next != end ) {
        std::copy( current, next, dest );
        std::copy( after.begin(), after.end(), dest );
        current = next + before.size();
        next = std::search( current, end, before.begin(), before.end() );
    }
    std::copy( current, next, dest );
    return retval;
}
// ------------------------------------------------------------------
std::string extract_string_no_carriage_return(const char * _pIn)
{
	std::string ret(_pIn);
	
	return globalReplace(ret.begin(), ret.end(), "\n", "");
}
// ------------------------------------------------------------------
long Tools::Files::getFileAndFolderInformations(std::string _strPath, std::list<Tools::Files::FileFolderInfos *> * _lFilesAndFolderInfos)
{
	if(NULL == _lFilesAndFolderInfos)
	{
		return FF_TOOLS_INVALID_PARAMS;
	}
	if(true == _strPath.empty())
	{
		return FF_TOOLS_INVALID_PARAMS;
	}

#ifdef _WINDOWS
	// windows implementation
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	unsigned int iSizConvert = 0;
	wchar_t  szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError=0;
  
	memset(szDir, 0, MAX_PATH * sizeof(wchar_t));
	Tools::String::convert_char_array_to_LPWSTR(_strPath.c_str(), _strPath.length(), szDir, &iSizConvert); 
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
		Tools::Files::FileFolderInfos * infos = new Tools::Files::FileFolderInfos();
		std::string strOut;
		Tools::String::convert_std_wstring_to_std_string(ffd.cFileName, &strOut );

		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			infos->setType(Tools::Files::FileFolderType::folder);
		} 
		else 
		{
			filesize.LowPart = ffd.nFileSizeLow;
			filesize.HighPart = ffd.nFileSizeHigh;
			infos->setType(Tools::Files::FileFolderType::file);
			infos->setFileSize(filesize.QuadPart);
		}
		
		// add infos to the list
		infos->setFilepath(_strPath);
		infos->setFilename(strOut);

		getFilesAndFolderDateInformations(infos->getFullName(), infos);

		_lFilesAndFolderInfos->push_back(infos);
	}
	while (FindNextFile(hFind, &ffd) != 0);
 
	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES) 
	{	
		return DIRTOOLS_KO;
	}
	FindClose(hFind);

#endif // _WINDOWS

	return FF_TOOLS_OK;
}
// ------------------------------------------------------------------------------
long Tools::Files::getFilesAndFolderList(std::string _strPath, std::list<std::string> * _pListSubfolder)
{
	if(NULL == _pListSubfolder)
	{
		return FF_TOOLS_INVALID_PARAMS;
	}
	if(true == _strPath.empty())
	{
		return FF_TOOLS_INVALID_PARAMS;
	}



	return FF_TOOLS_OK;
}
// ------------------------------------------------------------------------------
long Tools::Files::getFilesAndFolderDateInformations(std::string _strFilename, Tools::Files::FileFolderInfos * _fileInfos)
{
	struct _stat buf;
	int result;
	char timebuf[FF_SHORT_STR];
	errno_t err;

	// Get data associated with "crt_stat.c": 
	result = _stat( _strFilename.c_str(), &buf );

	// Check if statistics are valid: 
	if( result != 0 )
	{
		switch (errno)
		{
			case ENOENT:
				return FF_TOOLS_FILE_NOT_FOUND;
			case EINVAL:
				return FF_INVALID_PARAM_STAT;
			default:
				return FF_TOOLS_KO;
		}
	}
	else
	{
		// Output some of the statistics: timing
		_fileInfos->setFileSize(buf.st_size);
		err = ctime_s(timebuf, FF_SHORT_STR, &buf.st_mtime);
		_fileInfos->setFormattedModificationDate(extract_string_no_carriage_return(timebuf));
		err = ctime_s(timebuf, FF_SHORT_STR, &buf.st_atime);
		_fileInfos->setFormattedLastAccessDate(extract_string_no_carriage_return(timebuf));
		err = ctime_s(timebuf, FF_SHORT_STR, &buf.st_ctime);
		_fileInfos->setFormattedCreationDate(extract_string_no_carriage_return(timebuf));

		// output some permissions
		if (buf.st_mode & _S_IREAD)
		{
			_fileInfos->setReadingAllowedProperty(true);
		} else _fileInfos->setReadingAllowedProperty(false);
		if (buf.st_mode & _S_IWRITE)
		{
			_fileInfos->setWritingAllowedProperty(true);
		} else _fileInfos->setWritingAllowedProperty(false);
		if (buf.st_mode & _S_IEXEC)
		{
			_fileInfos->setExecAllowedProperty(true);
		} else _fileInfos->setExecAllowedProperty(false);

		// handle error
		if (err)
		{
			return FF_TOOLS_KO;
		}
	}
	return FF_TOOLS_OK;
}
// ------------------------------------------------------------------
