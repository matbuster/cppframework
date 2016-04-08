
#include "testFileIOFileIni.h"
#include "cppFrameworkTesterDefines.h"

// include cpp framework
#include "FileIO/FileIni.h"

#define TEST_SAMPLE_FILE	"D:/SVN/framework_svn_trunk/hsm/loadBalancer/loadBalancerLib/_ext_tools/cppFrameworkTester/tester/sample_test/hsmEmulated_Coprocessor_1.ini"

#define TS_SECTION_PROFILES        "profiles"
#define TS_SECTION_PROFILE         "profile%d"

#define TS_KEY_NUMBER_PROFILE      "num"
#define TS_KEY_PROFILE_NAME        "name"
#define TS_KEY_PROFILE_PASSWORD    "password"
#define TS_KEY_ASSOCIATED_ROLE     "role_name"


// --------------------------------------------------------------------
int tester_read_file() 
{
	int iNumberProfiles = 0;
	FileIO::FileIni * inifile = new FileIO::FileIni(TEST_SAMPLE_FILE);

    // read number of profiles
    inifile->ReadInt(TS_SECTION_PROFILES, TS_KEY_NUMBER_PROFILE, &iNumberProfiles, 0);

	delete inifile;
	return TEST_OK;
}
// --------------------------------------------------------------------
int tester_fileio_fileini() 
{
	int iReturnCode = TEST_OK;

	iReturnCode = tester_read_file();
	return iReturnCode;
}
// --------------------------------------------------------------------