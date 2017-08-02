/**
 * \file 		StringTools.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
 
#ifndef STRING_TOOLS_H
#define STRING_TOOLS_H

namespace Tools {

	namespace String {

		// ------------------------------------------------------------------------------------------------
		/** count the number of occurence of cCharToSearch in pStr 
		 * \param [in] pStr: string to search the Specific charset
		 * \param [in] lSizeStr: size of the string
		 * \return iNumberOccurence : number of occurence of cCharToSearch
		 */
		int StringCountOccurence(char * pStr, long lSizeStr, char cCharToSearch);

		// ------------------------------------------------------------------------------------------------
		/** function to check if str1 contain str2 */
		bool StringCointain(unsigned char * pStr1, long lSizeStr1, unsigned char * pStr2, long lSizeStr2);

		// ------------------------------------------------------------------------------------------------
		/** function to erase reccurent char from string */
		bool StringEraseChar(unsigned char * pResut, long * lResultLen, unsigned char * pInputString, long lInputStringSize, char cEraseChar);

		// ------------------------------------------------------------------------------------------------
		/** function to split an existing char array */
		bool StringSplit(char ** pOutResult, int * iOutResultNumber, char * pInputBuffer, int iInputBufferLen, char cSplitChar);

		// ------------------------------------------------------------------------------------------------
		/** function to transform a String to an hexa buffer */
		bool StringToHexaBuffer(unsigned char * pDataTransformed, char * pStringSource, unsigned long lSourceLgt);
	
		// ------------------------------------------------------------------------------------------------
		/** function to convert an hexa buffer to string */
		bool StringToHexaBuffer(unsigned char * pDataTransformed, long * lLenTransformed, char *pStringSource, unsigned long lSourceLgt); 

		// ------------------------------------------------------------------------------------------------
		/** function to convert an hexa buffer to string */
		bool HexaBufferToString(unsigned char *target, unsigned char *hexaSource, int hexaSourceLgt);

		// ------------------------------------------------------------------------------------------------
		/**! get the first occurence of a charset in string. 
		 * Return the first index value
		 * \param [in] pStr: string to search the Specific charset
		 * \param [in] lSizeStr: size of the string
		 * \param [in] cCharToSearch: value of char to search
		 * \param [out] indexValue: index value
		 * \return success or failed
		 */
		bool IndexOf(char * pStr, long lSizeStr, char cCharToSearch, int * indexValue);
		
		// ------------------------------------------------------------------------------------------------
		/**! sub a string from the input string
		 * \param [in] pStr: input string
		 * \param [in] lSizeStr: size of the input string
		 * \param [in] iStartIndex start position where the sub start
		 * \param [in] iLenSub: len of the sub
		 * \param [out] pSubStr: sub string
		 * \return success or failed
		 */
		bool SubString(char * pStr, long lSizeStr, int iStartIndex, int iLenSub, char * pSubStr);

		// ------------------------------------------------------------------------------------------------
		/**! get the upper case of an existing string
		 * \param [in] pInputSting : input string value
		 * \param [in] iInputStringSize : input string size
		 * \param [out] pOutUpperCase : output string as upper case of the input string
		 */
		bool UpperCase(char * pInputSting, int iInputStringSize, char * pOutUpperCase);

  		// ------------------------------------------------------------------------------------------------
		/**! get the lower case of an existing string
		 * \param [in] pInputSting : input string value
		 * \param [in] iInputStringSize : input string size
		 * \param [out] pOutLowerCase : output string as lower case of the input string
		 */
		bool LowerCase(char * pInputSting, int iInputStringSize, char * pOutLowerCase); 
	};
};

#endif /* STRING_TOOLS_H */