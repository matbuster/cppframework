/**
 * \file 		StringTools.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#include <stdio.h>
#include <string.h>

#include "StringTools.h"
#include "../../toolsconstant.h"

#include <algorithm>
#include <string>

/** count the number of occurence of cCharToSearch in pStr 
 * \return iNumberOccurence : number of occurence of cCharToSearch
 */
int Tools::String::StringCountOccurence(char * pStr, long lSizeStr, char cCharToSearch)
{
	if(NULL == pStr)
	{
		return 0;
	}

	int iNumberOccurence = 0;
	for(int i =0; i<lSizeStr; i++)
	{
		if(pStr[i] == cCharToSearch)
		{
			iNumberOccurence++;
		}
	}

	return iNumberOccurence;
}

/** function to check if str1 contain str2 */
bool Tools::String::StringCointain(unsigned char * pStr1, long lSizeStr1, unsigned char * pStr2, long lSizeStr2)
{
	long indexCheck = 0;
	int iIndexMatch = 0;

	// test if nothing to compare
	if(lSizeStr1 <= 0 || lSizeStr2 <= 0)
	{
		return false;
	}

	for(indexCheck = 0; indexCheck < lSizeStr1; indexCheck++)
	{
		if(pStr1[indexCheck] == pStr2[iIndexMatch])
		{
			iIndexMatch++;
			if(iIndexMatch >= lSizeStr2)
			{
				// str1 contain str 2
				return true;
			}
		}
		else 
		{
			iIndexMatch = 0;
		}
	}

	return false;
}

/** function to erase reccurent char from string */
bool Tools::String::StringEraseChar(unsigned char * pResut, long * lResultLen, unsigned char * pInputString, long lInputStringSize, char cEraseChar)
{
	int iIndexCopy = 0;
	for(int i = 0; i< lInputStringSize; i++)
	{
		if(pInputString[i] != cEraseChar) 
		{
			pResut[iIndexCopy] = pInputString[i];
			iIndexCopy++;
		}
	}

	*lResultLen = iIndexCopy;
	return true;
}

/** function to split an existing char array */
bool Tools::String::StringSplit(char ** pOutResult, int * iOutResultNumber, char * pInputBuffer, int iInputBufferLen, char cSplitChar)
{
	// preco
	if(NULL == pOutResult)
	{
		return false;
	}
	if(NULL == iOutResultNumber)
	{
		return false;
	}
	if(NULL == pInputBuffer)
	{
		return false;
	}

	int iNumberResult = 0;
	int iIndexCopy = 0;
	for(int i =0; i< iInputBufferLen; i++)
	{
		if(cSplitChar == pInputBuffer[i]) 
		{
			iIndexCopy = 0;
			iNumberResult++;
		}
		else 
		{
			pOutResult[iNumberResult][iIndexCopy] = pInputBuffer[i];
			iIndexCopy++;
		}
	}

	// if at least one char inside, there is another element inside
	if(iIndexCopy > 0) 
	{
		iNumberResult++;
	}

	*iOutResultNumber = iNumberResult;
	return true;
}

bool Tools::String::StringToHexaBuffer(unsigned char * pDataTransformed, char * pStringSource, unsigned long lSourceLgt)
{
	long lVal = 0;
	return StringToHexaBuffer(pDataTransformed, &lVal, pStringSource, lSourceLgt);
}

/** function to transform a String to an hexa buffer */
bool Tools::String::StringToHexaBuffer(unsigned char * pDataTransformed, long * lLenTransformed, char * pStringSource, unsigned long lSourceLgt)
{
	unsigned char	ucVal;
	int				nStrchar;
	unsigned long	i;
	unsigned long	lNumberValues = 0;
	
	if ((NULL == pDataTransformed) || (NULL == pStringSource) || (NULL == lLenTransformed))
		return false;

	ucVal = 0;
	for (i = 0; i < lSourceLgt; i++)
	{
		nStrchar = pStringSource [i];
		switch (nStrchar)
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				ucVal = (unsigned char)((ucVal << 4) + (nStrchar - '0'));
				break;	

			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
				ucVal = (unsigned char)((ucVal << 4) + nStrchar - 'A' + 10);
				break;	

			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
				ucVal = (unsigned char)((ucVal << 4) + nStrchar - 'a' + 10);
				break;		

			default:
				return false;
		}

		//or each odd index in source string
		if (i & 0x01)
		{
			pDataTransformed [i >> 1] = ucVal;
			ucVal = 0;
			lNumberValues++;
		}
	}

	//	si la longueur est impaire
	if (lSourceLgt & 0x01)
	{
		pDataTransformed [i >> 1] = (ucVal << 4);
	}

	*lLenTransformed=lNumberValues;
	return true;
}

bool Tools::String::HexaBufferToString(unsigned char *target, unsigned char *hexaSource, int hexaSourceLgt) 
{
    int i;
    const char *cars;
    unsigned char cvar;

    unsigned char pTempSource[STR_HUGE] = {0};

    if ((target == NULL) || (hexaSource == NULL)) {
        return false;
    }

    if (hexaSourceLgt <= 0) {
        return false;
    }

    memcpy(pTempSource, hexaSource, hexaSourceLgt);

    cars = "0123456789ABCDEF";

    for (i = 0; i < hexaSourceLgt; i++) {
        // first digit
        cvar = pTempSource[i] & 0xF0;
        cvar >>= 4;
        cvar &= 0x0F;
        target[i << 1] = cars[cvar];

        // second digit
        cvar = pTempSource[i] & 0x0F;
        target[(i << 1) + 1] = cars[cvar];
    }

    target[hexaSourceLgt << 1] = '\0';

    return true;
}

bool Tools::String::IndexOf(char * pStr, long lSizeStr, char cCharToSearch, int * indexValue)
{
	if(NULL == pStr ||  NULL == indexValue)
	{
		return false;
	}

	for(int i = 0; i <lSizeStr; i++)
	{
		if(pStr[i] == cCharToSearch)
		{
			*indexValue = i;
			return true;
		}
	}

	return false;
}

bool Tools::String::SubString(char * pStr, long lSizeStr, int iStartIndex, int iLenSub, char * pSubStr)
{
	if(NULL == pStr || NULL == pSubStr)
	{
		return false;
	}
	if(iStartIndex < 0 || iStartIndex > lSizeStr)
	{
		return false;
	}
	if(iLenSub < 0 || iLenSub > lSizeStr || (iLenSub + iStartIndex) > lSizeStr)
	{
		return false;
	}

	memcpy(pSubStr, pStr+iStartIndex, iLenSub);
	return true;
}

// ------------------------------------------------------------------------------------------------
bool Tools::String::UpperCase(char * pInputSting, int iInputStringSize, char * pOutUpperCase)
{
	if(NULL == pInputSting || NULL == pOutUpperCase)
	{
		return false;
	}
	//
	std::string str(pInputSting);
	std::transform(str.begin(), str.end(),str.begin(), ::toupper);
	//
	memcpy(pOutUpperCase, str.c_str(), str.length());
	//
	return true;
}
// ------------------------------------------------------------------------------------------------
bool Tools::String::LowerCase(char * pInputSting, int iInputStringSize, char * pOutLowerCase)
{
	if(NULL == pInputSting || NULL == pOutLowerCase)
	{
		return false;
	}
	//
	std::string str(pInputSting);
	std::transform(str.begin(), str.end(),str.begin(), ::tolower);
	//
	memcpy(pOutLowerCase, str.c_str(), str.length());
	//
	return true;
}
// ------------------------------------------------------------------------------------------------
