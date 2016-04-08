/**
 * \file 		Date.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef DATE_H
#define DATE_H

#define DATE_OK	0
#define DATE_KO	1

namespace Timing {
	
	namespace Date {
	
		/** return a date string value to prefix a file name
		 * example : YYYY_MM_DD_HH_MM_SS_
		 */
		long GetStringDateForFile(char * _pOutDateFormatted, int _iSizeBuffer, int * _iDateSize);
	};
};
#endif /* DATE_H */