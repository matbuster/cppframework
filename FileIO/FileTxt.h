/**
 * \file 		FileTxt.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef FILE_TXT_H
#define FILE_TXT_H

#define CONST_WRITE		"w"
#define CONST_READ		"r"
#define CONST_APPEND	"ab"

#define FILE_SUCCESS				0
#define FILE_NOT_OPENNED			1
#define FILE_WRONG_MODE				2
#define FILE_BUFFER_TOO_SMALL		3
#define FILE_WRONG_INDEX			4
#define FILE_NO_DATA_READ			5
#define FILE_INPUT_BUFF_TO_SMALL	6
#define FILE_INVALID_POINTER		7
#define FILE_INDEX_OUT_OF_BOUNDS	8	

#include <stdio.h>
#include <string>
#include <list>

#include "../Threading/Mutex.h"
#include "../toolsconstant.h"

using namespace std;

#ifndef BUILD_DLL
#define IMPORT_EXPORT
#endif

namespace FileIO {
	
	/** enum corresponding to the file access mode */
	enum FileTxtMode {
		filenomode = 0,
		filewrite,
		fileread,
		fileappend
	};

	/** class textfile to open, close read and write in a text file
	 */
	class IMPORT_EXPORT FileTxt {

	protected:
		/** name of the opnned text file */
		char m_cFilename[STR_LONG];

		/** status of text file, opened or not */
		bool m_bFileOpened;

		/** define internal windows base FILE */
		FILE * m_file;

		/** mode for appeninf in text file */
		FileTxtMode m_mode;

		/** contrent of the file */
		std::list<std::string> * m_fContent;

		/** mutex for access to the file */
		Threading::Mutex * m_mutex;

	private:
		/** internal function to get the corresponding mode from enum */
		const char * getMode(FileIO::FileTxtMode mode);

	protected:
		/** get appropriate line in a texte file */
		std::string getItem(int iIndexItem);
		/** replace the item at the index passed as argument */
		long replaceItem(int iIndexItem, std::string strValue);
		/** insert an item in the list at index passed as argument */
		long insertItem(int iIndexItem, std::string strValue);
		/** get the number of line in text file */
		int getNumLines();

	public:
		/** main constructor and destructor */
		FileTxt(char * cFilename);
		virtual ~FileTxt();

		/** openening the file text */
		long FileTxtOpen(FileTxtMode mode);
		/** closing an instance of the file text */
		long FileTxtClose();
		/** write in the openning text file the input message */
		long FileTxtWrite(char * cInMessage, int iMessageLen);
		/** read the content of a text file */
		long FileTxtRead();

		// ------------------------------------------------------
		// Read function and get appropriated data
	public:
		/** function to get the content of data readed. Sequence is Open, Read
		 * getReadeContent, Close; Then	pDataRead contain the readed buffer */
		long getReadContent(unsigned char * pDataRead, long lDataInputMaxSize, long * lDataReadSize);

		/** get the number of line read */
		long getReadNumLines(long * lNumberLineRead);

		/** function to get the specific line read */
		long getLine(int iIndexLine, unsigned char * pBufferLine, long lInputBufferLineSize, long * lOutLineSize);
	};
};

#endif /* FILE_TXT_H */