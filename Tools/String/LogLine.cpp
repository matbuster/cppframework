/**
 * \file 		LogLine.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#include "LogLine.h"

#define	LL_STR_LONG	1024

#define LL_OK	0
#define LL_KO	1

/** main constructor and destructor of the class */
Tools::String::LogLine::LogLine(unsigned char * pLine)
{
	m_line = (char*)pLine;

	m_date = "";
	m_hour = "";
	m_ThreadId = "";
	m_prio = "";
	m_orig = "";
	m_comment = "";
	parseline();
}
Tools::String::LogLine::~LogLine()
{
}
/** get next index */
int Tools::String::LogLine::getNextIndex(int iStart, std::string value, std::string delimiter)
{
	return 0;
}
/** internal function to parse line message */
long Tools::String::LogLine::parseline()
{
	char pTempBuffer[LL_STR_LONG];
	char pTempValue[LL_STR_LONG];
	int i = 0;
	int iIndexCopy = 0;
	int iIndexSpace = 0;
	int iItemFound = 0;

	memset(pTempBuffer, 0x00, LL_STR_LONG);
	memset(pTempValue, 0x00, LL_STR_LONG);

	memcpy(pTempBuffer, m_line.c_str(), m_line.size());
	for(i =0;i<(int)m_line.size();i++)
	{
		if(pTempBuffer[i] == '\t')
		{
			if(iIndexSpace <= 0) 
			{
				if(iItemFound == 0) m_date = pTempValue;
				else if(iItemFound == 1) m_hour = pTempValue;
				else if(iItemFound == 2) m_ThreadId = pTempValue;
				else if(iItemFound == 3) m_prio = pTempValue;
				else if(iItemFound == 4) m_orig = pTempValue;

				iItemFound++;
			}

			memset(pTempValue, 0x00, LL_STR_LONG);
			iIndexCopy = 0;
			iIndexSpace++;
		}
		else
		{
			// start of comment detected, stop here and get comment
			if(iItemFound == 5) 
			{
				iIndexCopy = i;
				break;
			}

			pTempValue[iIndexCopy] = pTempBuffer[i];
			iIndexCopy++;
			iIndexSpace = 0;
		}
	}

	// le reste de la ligne est le commentaire
	m_comment = m_line.substr(iIndexCopy, m_line.size());
	return LL_OK;
}
/** function to get the associated comment */
long Tools::String::LogLine::getComment(unsigned char * pCommentValue, long * lCommentValueSize)
{
	if(NULL == pCommentValue) 
	{
		return LL_KO;
	}

	memcpy(pCommentValue, m_comment.c_str(), m_comment.size());
	*lCommentValueSize = m_comment.size();

	return LL_OK;
}