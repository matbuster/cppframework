/**
 * \file 		FileIni.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef FILE_INI_H
#define FILE_INI_H

#include "../toolsconstant.h"
#include "FileTxt.h"

#define CR			'\n'
#define ESP			' '

#define FILE_KEY_NOT_FOUND			10
#define FILE_INPUT_BUFF_TOO_SMALL	11

namespace FileIO {

	/** class file ini, to read and change parameter in a specific ini file 
	  * This implementation is specific _WINDOWS at now.
	  */
	class IMPORT_EXPORT FileIni : FileTxt {
	private:
		/** path of param.ini */
		char m_cPathIniFile[STR_LONG];

		/** function to get the corresponding line according to section and key */
		long getline(char * cSection, char * cKey, std::string * strline, int * iIndexLine);

		/** function to replace the value of a line */
		long replaceline(char * cSection, char * cKey, std::string strReplaceValue);
	public:
		FileIni(char * cPathIniFile);
		~FileIni();

		/** write value in a specific ini file */
		long WriteInt(char * cSection, char * Key, int iReadValue);

		/** write a string value in a cini file */
		long WriteString(char * cSection, char * cKey, char * cStrValue);

		/** read an integer parameter in a specific inifile */
		long ReadFloat(char * cSection, char * cKey, float * fReadValue, float fDefaultValue);

		/** read an integer parameter in a specific inifile */
		long ReadInt(char * cSection, char * Key, int * iReadValue, int iDefaultValue);

		/** read a string parameter in a specific inifile */
		long ReadString(char * cSection, char * Key, char * cReadValue, int iSizeReadBuf, char * cStringDefaultValue);

		/** function to replace the file with all modification */
		long SaveIniFile();
	};
};

#endif /* FILE_INI_H */
