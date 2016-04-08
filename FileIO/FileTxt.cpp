/**
 * \file 		FileTxt.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#include <stdio.h>
#include <string.h>

#include "../toolsconstant.h"
#include "FileTxt.h"

//#define FORCE_NO_OUTPUT_TEXT

/** main constructor of the class*/
FileIO::FileTxt::FileTxt(char * cFilename) 
{
	memcpy(m_cFilename, cFilename, STR_LONG);
	m_bFileOpened = false;
	m_mode = filenomode;
	m_fContent = new std::list<std::string>();
	m_mutex = new Threading::Mutex();
}

/** desconstructor of the class*/
FileIO::FileTxt::~FileTxt() 
{
	m_bFileOpened = false;
	m_mode = filenomode;
	delete m_mutex;
}

/** internal function to get the corresponding mode from enum */
const char * FileIO::FileTxt::getMode(FileIO::FileTxtMode mode)
{
	if(filewrite == mode) {
		return (const char*)CONST_WRITE;
	} else if(fileread == mode) {
		return (const char*)CONST_READ;
	} else if(fileappend == mode) {
		return (const char*)CONST_APPEND;
	} else {
		return (const char*)CONST_APPEND;
	}
}

/** get appropriate line in a texte file */
std::string FileIO::FileTxt::getItem(int iIndexItem)
{
	int iCounter = 0;
	for( std::list<std::string>::iterator it = m_fContent->begin(); it != m_fContent->end(); it++)
	{
		if(iIndexItem == iCounter) {
			std::string item = *it;
			return *it;
		}
		iCounter++;
 	}
	return "";
}
/** insert an item in the list at index passed as argument */
long FileIO::FileTxt::insertItem(int iIndexItem, std::string strValue)
{
	std::list<std::string>::iterator itIndex = m_fContent->begin();
	std::advance(itIndex, iIndexItem);

	m_fContent->insert(itIndex, strValue);
	return FILE_SUCCESS;
}
/** replace the item at the index passed as argument */
long FileIO::FileTxt::replaceItem(int iIndexItem, std::string strValue)
{
	std::list<std::string>::iterator itIndex = m_fContent->begin();
	std::advance(itIndex, iIndexItem);
	
	m_fContent->erase(itIndex);
	m_fContent->insert(itIndex, strValue);
	return FILE_SUCCESS;
}
/** get the number of line in text file */
int FileIO::FileTxt::getNumLines()
{
	if(NULL != m_fContent)
	{
		return (int)m_fContent->size();
	}
	return 0;
}

/** openening the file text */
long FileIO::FileTxt::FileTxtOpen(FileTxtMode mode) 
{
	if(!m_bFileOpened) 
	{
#ifndef FORCE_NO_OUTPUT_TEXT
        m_file = fopen((const char*)m_cFilename, getMode(mode));
		if(NULL != m_file)
		{
			m_bFileOpened = true;
			m_mode = mode;
		}
#else	/* FORCE_NO_OUTPUT_TEXT */
		m_bFileOpened = true;
		m_mode = mode;
#endif /* FORCE_NO_OUTPUT_TEXT*/
	}

	return FILE_SUCCESS;
}

/** closing an instance of the file text */
long FileIO::FileTxt::FileTxtClose()
{
	if(m_bFileOpened) 
	{
#ifndef FORCE_NO_OUTPUT_TEXT
		fclose(m_file);
#endif
		m_bFileOpened = false;
		m_mode = filenomode;
	}
	return FILE_SUCCESS;
}

/** write in the openning text file the input message */
long FileIO::FileTxt::FileTxtWrite(char * cInMessage, int iMessageLen)
{
	if(!m_bFileOpened) 
	{
		return FILE_NOT_OPENNED;
	}
	if(filenomode == m_mode || fileread == m_mode) 
	{
		return FILE_WRONG_MODE;
	}

	// mutex to ensure that concurrent access cannot happen
	if(true == m_mutex->WaitOne()) {
#ifndef FORCE_NO_OUTPUT_TEXT
		fprintf(m_file, cInMessage);
		fflush(m_file);
#endif
		m_mutex->Release();
	}

	return FILE_SUCCESS;
}

/** read a message in the openned text file */
long FileIO::FileTxt::FileTxtRead()
{
	if(!m_bFileOpened) 
	{
		return FILE_NOT_OPENNED;
	}
	if(filenomode == m_mode || filewrite == m_mode) 
	{
		return FILE_WRONG_MODE;
	}

	char pTempVal[STR_LONG];
	memset(pTempVal, 0x00, STR_LONG);
	
	while ( fgets(pTempVal, STR_LONG, m_file) != NULL)
	{
		m_fContent->push_back(pTempVal);
	}

	return FILE_SUCCESS;
}

/** function to get the content of data readed. Sequence is Open, Read
 * getReadeContent, Close; Then	pDataRead contain the readed buffer */
long FileIO::FileTxt::getReadContent(unsigned char * pDataRead, long lDataInputMaxSize, long * lDataReadSize)
{
	if(filenomode == m_mode || filewrite == m_mode) 
	{
		return FILE_WRONG_MODE;
	}
	if(m_fContent->size() <= 0)
	{
		return FILE_NO_DATA_READ;
	}

	*lDataReadSize = 0;
	// loop on the content file
	for(std::list<std::string>::iterator it = m_fContent->begin(); it != m_fContent->end(); it++) 
	{
		std::string _currentStr = *it;

		//checking max value
		if( (*lDataReadSize + (long)_currentStr.size()) < lDataInputMaxSize)
		{
			memcpy(pDataRead, _currentStr.c_str(), _currentStr.size());
			*lDataReadSize += (long)_currentStr.size();
		}
		else 
		{
			return FILE_INPUT_BUFF_TO_SMALL;
		}
	}

	return FILE_SUCCESS;
}

/** get the number of line read */
long FileIO::FileTxt::getReadNumLines(long * lNumberLineRead)
{
	if(filenomode == m_mode || filewrite == m_mode) 
	{
		return FILE_WRONG_MODE;
	}
	if(m_fContent->size() <= 0)
	{
		return FILE_NO_DATA_READ;
	}

	*lNumberLineRead = getNumLines();

	return FILE_SUCCESS;
}

/** function to get the specific line read */
long FileIO::FileTxt::getLine(int iIndexLine, unsigned char * pBufferLine, long lInputBufferLineSize, long * lOutLineSize)
{
	if(filenomode == m_mode || filewrite == m_mode) 
	{
		return FILE_WRONG_MODE;
	}
	if(m_fContent->size() <= 0)
	{
		return FILE_NO_DATA_READ;
	}
	if(NULL == pBufferLine) 
	{
		return FILE_INVALID_POINTER;
	}
	if(NULL == lOutLineSize)
	{
		return FILE_INVALID_POINTER;
	}
	if(iIndexLine < 0 || iIndexLine > getNumLines())
	{
		return FILE_INDEX_OUT_OF_BOUNDS;
	}

	std::string _line = getItem(iIndexLine);
	if(lInputBufferLineSize <= (long)_line.size())
	{
		return FILE_BUFFER_TOO_SMALL;
	}

	memcpy(pBufferLine, _line.c_str(), _line.size());
	*lOutLineSize = (long)_line.size();

	return FILE_SUCCESS;
}
