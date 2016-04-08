/**
 * \file 		FileLog.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef FILE_LOG_H
#define FILE_LOG_H

/*##########################################################*
 *                      USER DEFINE
 *##########################################################*/

#ifndef BUILD_CARD
// Uncomment #define if you want to log on the console
//define LOG_CONSOLE
#endif //BUILD_CARD  

/*##########################################################*
 *                     END USER DEFINE
 *##########################################################*/

#define STR_PRIO_NOPRIO		"[NoPrio]"
#define STR_PRIO_DEBUG		"[Debug]"
#define STR_PRIO_PROD		"[Prod]"
#define STR_PRIO_INFO		"[Info]"
#define STR_PRIO_WARNING	"[Warning]"
#define STR_PRIO_ERROR		"[Error]"

#define STR_PRIO_NOORIG		"[NoOrig]"
#define STR_PRIO_HARD		"[Hadw]"
#define STR_PRIO_SOFT		"[Softw]"
#define STR_PRIO_CPU		"[CPU]"
#define STR_PRIO_NETWORK	"[Network]"
#define STR_PRIO_SYSTEM		"[System]"
#define STR_PRIO_COMM		"[Comm]"
#define STR_PRIO_CONFIG		"[Config]"

#define STR_DEFAULT_DATE	"[YY/MM/DD]\t[HH:MM:SS]"

#define LOG_MAX_HEXA_PER_LINE	20

#include "../toolsconstant.h"
#include "FileTxt.h"
#include "../Timing/Date.h"
#include "../Tools/File/File.h"

#define PRIO_FILTER_NO_ORIG			0x01
#define PRIO_FILTER_DEBUG			0x02
#define PRIO_FILTER_PROD			0x04
#define PRIO_FILTER_INFO			0x08
#define PRIO_FILTER_WARNING			0x10
#define PRIO_FILTER_ERROR			0x20
#define PRIO_FILTER_DEBUG_TIMING	0x40

#define MAX_LOGFILE_SIZE			4 * 1024 * 1024 // default size 4 Mo

namespace FileIO {
	
	/** enum corresponding to the prioroty of log file */
	enum FilePriority {
		flPrioNoPrio = 0x01,
		flPrioDebug = 0x02,
		flPrioProd = 0x04,
		flPrioInfo = 0x08,
		flPrioWarning = 0x10,
		flPrioError = 0x20,
		flPrioDebugTiming = 0x40
	};

	/** file corresponding to the origin of log file */
	enum FileOrigin {
		flOrigNone = 0,
		flOrigHardware,
		flOrigSoftware,
		flOrigCPU,
		flOrigNetwork,
		flOrigSystem,
		flOrigComm,
		flOrigConfig
	};

	/** class textfile to open, close read and write in a text file
	 */
	class FileLog : FileTxt {
	
	private:
		/** definition of filter to set the display of priority comment */
		int m_iLogPrioFilter;

		/** get the corresponding date and hour [YY/MM/DD]\t[HH:MM:SS] */ 
		void getDate(char * cOutDate);

		/** get a corresponding message to the priority enum */
		char * getPrioMessage(FilePriority enPrio);

		/** get a corresponding message to the origin enum */
		char * getOrigMessage(FileOrigin enOrig);

		/** function to check the filter validity, true if log is authorized, false if not */
		bool CheckFilter(FilePriority enPrio);

		/** function to check if log rotate is required */
		bool LogRotate();

	public:
		/** main constructor and destructor of the class */
		FileLog(char * cFilename);
		~FileLog();

		/** function to set the value of filter, levels of FilePriority */
		long SetFilter(int iFilterValue);

		/** generic function to log an information without any Prio/Orig (default value) */
		long Log(char * cMessage);

		/** generic function to log an information without any Prio/Orig (default value) with argument */
		long LogArguments(char * cMessage, ... );

		/** log an hexadecimal buffer */
		long LogHexaBuffer(unsigned char * ucBuffer, int iSzBuffer);

		/** Log g�n�rique pour une commentaire dans le fichier */
		long Log(FilePriority enPrio, FileOrigin enOrig, char * cMessage);

		/** Log g�n�rique pour une commentaire dans le fichier */
		long LogArguments(FilePriority enPrio, FileOrigin enOrig, char * cMessage, ... );

		/** log an hexadecimal buffer */
		long LogHexaBuffer(FilePriority enPrio, FileOrigin enOrig, unsigned char * ucBuffer, int iSzBuffer);
	};
};

#endif /* FILE_LOG_H */