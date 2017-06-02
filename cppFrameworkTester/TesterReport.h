#ifndef TESTER_REPORT_H
#define TESTER_REPORT_H

//#define NO_OUTPUT_CONSOLE
//#define NO_OUTPUT_FILE


#define REPORT_SUCCESS "SUCCESS"
#define REPORT_FAILURE "FAILURE"
//#define REPORT_SUCCESS "[%s]\t%s\tSUCCESS.\r\n"
//#define REPORT_FAILURE "[%s]\t%s\tFAILURE.\r\n"

#ifndef NO_OUTPUT_FILE
#include <iostream>
#include <fstream>
#endif /*NO_OUTPUT_FILE*/

namespace Test {

	class TesterReport {

	private:
		char m_pFilename[1024];

#ifndef NO_OUTPUT_FILE
		std::ofstream m_reportFile;
#endif /*NO_OUTPUT_FILE*/

		TesterReport();
		TesterReport(char * _pFilename);

	public:
		static TesterReport * getInstance();
		~TesterReport();

		// --------------------------------------------------------------------
		void printHeader(const char * pMessage);
		
		// --------------------------------------------------------------------
		void printSummary(bool bCondition, const char * pName, const char * pFunction);
	};
}

#endif /** TESTER_REPORT_H */