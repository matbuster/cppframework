/**
 * \file 		FileIni.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#include "FileIni.h"

#ifdef _WINDOWS
    #include <direct.h>
    #include <Windows.h>
    #define GetCurrentDir _getcwd
#endif
#ifdef LINUX
    #include <unistd.h>
    #include <stdlib.h> 
    #include <string.h>
    #define GetCurrentDir getcwd
#endif

/** main constructor of the class */
FileIO::FileIni::FileIni(char * cPathParamFile) 
	:FileTxt(cPathParamFile)
{
	if(NULL != cPathParamFile)
	{
		memcpy(m_cPathIniFile, cPathParamFile, STR_LONG);
	}
	FileTxtOpen(fileread);
	FileTxtRead();
}

/** destructor of the class */
FileIO::FileIni::~FileIni() 
{
}

/** function to get the corresponding line according to section and key */
long FileIO::FileIni::getline(char * cSection, char * cKey, std::string * strline, int * iIndexLine)
{
	bool bFoundSection		= false;
	bool bFoundKey			= false;
	char cTempSection[STR_LONG];

	memset(cTempSection, 0x00, STR_LONG);
	sprintf(cTempSection,"[%s]\n",cSection);

	std::string strSection  = cTempSection;
	std::string strKey		= cKey;
	int iNumberLines		= getNumLines();

	for(int i = 0; i < iNumberLines; i++)
	{
		std::string line = getItem(i);
		if(line.compare(strSection) == 0)
		{
			// section found
			bFoundSection = true;
		}
		size_t npos = line.find(strKey);
		if(npos == 0)
		{
			 bFoundKey = true;
		}

		// found key and section
		if(bFoundKey && bFoundSection)
		{
			*strline = line;
			*iIndexLine = 0;
			return FILE_SUCCESS;
		}

		// reinit for loop: for a better detection, reinit bFoundSection if another section detected
		bFoundKey = false;
	}
	return FILE_KEY_NOT_FOUND;
}

/** function to replace the value of a line */
long FileIO::FileIni::replaceline(char * cSection, char * cKey, std::string strReplaceValue)
{
	char cTempSection[STR_LONG];

	memset(cTempSection, 0x00, STR_LONG);
	sprintf(cTempSection,"[%s]\n",cSection);

	std::string value = "";
	int iIndexLine = 0;
	if(getline(cSection, cKey, &value, &iIndexLine) == 0)
	{
		std::string strNewLine = cKey;
		strNewLine += "=";
		strNewLine += strReplaceValue;

		replaceItem(iIndexLine, strReplaceValue);
	}
	return FILE_KEY_NOT_FOUND;
}

/** write value in a specific ini file */
long FileIO::FileIni::WriteInt(char * cSection, char * Key, int /*iReadValue*/)
{
#ifdef _WINDOWS
	WriteProfileString(
	  (LPCTSTR)cSection,
	  (LPCTSTR)Key,
	  (LPCTSTR)("33")
	);
	//int iError = GetLastError(); 
#endif
	return FILE_SUCCESS;
}
/** write a string value in a cini file */
long FileIO::FileIni::WriteString(char * /*cSection*/, char * /*cKey*/, char * cStrValue)
{
	std::string strValue = cStrValue;
	//replaceline(cSection, cKey, strValue);
	return FILE_SUCCESS;
}

/** function to replace the file with all modification */
long FileIO::FileIni::SaveIniFile()
{
	return FILE_SUCCESS;
}

/** read an integer parameter in a specific inifile */
long FileIO::FileIni::ReadFloat(char * cSection, char * cKey, float * fReadValue, float fDefaultValue)
{
	char cTempMessage[STR_LONG];
	char cDefaultValue[STR_LONG];

	memset(cTempMessage, 0x00, STR_LONG);
	memset(cDefaultValue, 0x00, STR_LONG);

	sprintf(cDefaultValue, "%f", fDefaultValue);
	FileIO::FileIni::ReadString(cSection, cKey, cTempMessage, STR_LONG, cDefaultValue);

	*fReadValue = (float)atof(cTempMessage);

	return FILE_SUCCESS;
}

/** read an integer parameter in a specific inifile */
long FileIO::FileIni::ReadInt(char * cSection, char * cKey, int * iReadValue, int iDefaultValue)
{
	char cTempMessage[STR_LONG];
	char cDefaultValue[STR_LONG];

	memset(cTempMessage, 0x00, STR_LONG);
	memset(cDefaultValue, 0x00, STR_LONG);

	sprintf(cDefaultValue, "%d", iDefaultValue);
	FileIO::FileIni::ReadString(cSection, cKey, cTempMessage, STR_LONG, cDefaultValue);

	*iReadValue = atoi(cTempMessage);

	return FILE_SUCCESS;
}

/** read a string parameter in a specific inifile */
long FileIO::FileIni::ReadString(char * cSection, char * cKey, char * cReadValue, int iSizeReadBuf, char * cStringDefaultValue)
{
	// creating section
	char cTempSection[STR_LONG];
    char cTempValue[STR_LONG];

	memset(cTempSection, 0x00, STR_LONG);
    memset(cTempValue, 0x00, STR_LONG);
	sprintf(cTempSection,"[%s]\n",cSection);

	std::string strSection  = cTempSection;
	std::string strKey		= cKey;
	std::string delimiter	= "=";
	std::string strCR		= "\n";
	std::string strESP		= " ";
	std::string token		= "";

	std::string value = "";
	int iIndexLine = 0;
	if(getline(cSection, cKey, &value, &iIndexLine) == 0)
	{
		size_t nposdelimiter = value.find(delimiter);
		if(nposdelimiter > 0) {
		
			// just to delete the delimiter in the output str
			nposdelimiter += delimiter.length();
			token = value.substr(nposdelimiter, value.length());
				
			// copy to the output
			// clear and clean string for " " and "\n"
			int iIndexCpy = 0;
			token.copy((char*)cTempValue, (size_t)token.length(), (size_t)0);
			for(int iCpy = 0; iCpy < (int)token.length(); iCpy++)
			{
				if(iCpy >= iSizeReadBuf)
				{
					return FILE_INPUT_BUFF_TOO_SMALL;
				}
				if(cTempValue[iCpy] != CR && cTempValue[iCpy] != ESP){
					cReadValue[iIndexCpy] = cTempValue[iCpy];
					iIndexCpy++;
				}

			}

			return FILE_SUCCESS;
		}
	}

	// copy default value and return item not found
	memcpy(cReadValue, cStringDefaultValue, iSizeReadBuf);
	return FILE_KEY_NOT_FOUND;
}
