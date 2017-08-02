
#include "testToolsFileDirectory.h"
#include "cppFrameworkTesterDefines.h"
#include "TesterReport.h"

// framework include tools file
#include "Tools/File/Directory.h"

#define MAX_PATH_TEST 32

#define PATH_DEFAULT_WINDOWS "C:"
#define PATH_DEFAULT_UNIX	"/opt/home"

// ----------------------------------------------------------
int Test::test_tools_file_directory_countFiles()
{
	int iSizePath = 0;
	char path[MAX_PATH_TEST];
	memset( path, 0, MAX_PATH_TEST);

#ifdef _WINDOWS
	memcpy(path, PATH_DEFAULT_WINDOWS, sizeof(PATH_DEFAULT_WINDOWS));
	iSizePath = sizeof(PATH_DEFAULT_WINDOWS);
#endif // _WINDOWS

#ifdef UNIX
	memcpy(path, PATH_DEFAUULT_UNIX, sizeof(PATH_DEFAULT_UNIX));
	iSizePath = sizeof(PATH_DEFAULT_UNIX);
#endif // UNIX

	long lNumberSubfolder = 0;
	long lRetCode = Tools::Directory::GetNumberSubfolder( path, iSizePath, &lNumberSubfolder );

	if(lNumberSubfolder <= 0)
	{
		printf(">test_tools_file_directory_countFiles no folders present in DEFAULT FOLDER\r\n");
		return TEST_KO;
	}

	return TEST_OK;
}
// ----------------------------------------------------------
int Test::test_tools_file_directory() 
{
    int iReturnCode = TEST_OK;

	Test::TesterReport::getInstance()->printHeader("testing Directory");

	iReturnCode = test_tools_file_directory_countFiles();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Directory", "test_tools_file_directory_countFiles()");

	return TEST_OK;
}
// ----------------------------------------------------------

