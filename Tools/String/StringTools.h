/**
 * \file 		StringTools.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
 
#ifndef STRING_TOOLS_H
#define STRING_TOOLS_H

namespace Tools {

	namespace String {

		/** count the number of occurence of cCharToSearch in pStr 
		 * \return iNumberOccurence : number of occurence of cCharToSearch
		 */
		int StringCountOccurence(char * pStr, long lSizeStr, char cCharToSearch);

		/** function to chexk if str1 contain str2 */
		bool StringCointain(unsigned char * pStr1, long lSizeStr1, unsigned char * pStr2, long lSizeStr2);

		/** function to erase reccurent char from string */
		bool StringEraseChar(unsigned char * pResut, long * lResultLen, unsigned char * pInputString, long lInputStringSize, char cEraseChar);

		/** function to split an existing char array */
		bool StringSplit(char ** pOutResult, int * iOutResultNumber, char * pInputBuffer, int iInputBufferLen, char cSplitChar);

		/** function to transform a String to an hexa buffer */
		bool StringToHexaBuffer(unsigned char * pDataTransformed, char * pStringSource, unsigned long lSourceLgt);
	
		/** function to convert an hexa buffer to string */
		bool HexaBufferToString(unsigned char *target, unsigned char *hexaSource, int hexaSourceLgt); 
	};
};

#endif /* STRING_TOOLS_H */