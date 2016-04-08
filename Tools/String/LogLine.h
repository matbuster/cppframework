/**
 * \file 		LogLine.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef LOG_LINE_H
#define LOG_LINE_H

#include <string>

namespace Tools {

	namespace String {

		/** class to split a log line */
		class LogLine {
	
		private:
			/** internal line value */
			std::string m_line;

			std::string m_date;
			std::string m_hour;
			std::string m_ThreadId;
			std::string m_prio;
			std::string m_orig;
			std::string m_comment;

			/** get next index */
			int getNextIndex(int iStart, std::string value, std::string delimiter);

			/** internal function to parse line message */
			long parseline();

		public:
			/** main constructor of the class */
			LogLine(unsigned char * pLine);
			~LogLine();

			/** function to get the associated comment */
			long getComment(unsigned char * pCommentValue, long * lCommentValueSize);
		};
	};
};

#endif /* LOG_LINE_H */

