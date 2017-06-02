#include "TesterReport.h"
#include "cppFrameworkTesterDefines.h"

#ifdef WIN32
#include "stdafx.h"
#include <Windows.h>
#include <string>
#include <assert.h>
#endif // WIN32

#ifdef LINUX
#include <stdio.h>
#include <stdlib.h>
#endif // LINUX


/**! internal instance definition of Testreport */
static Test::TesterReport * g_instance = NULL;

Test::TesterReport::TesterReport()
{
#ifndef NO_OUTPUT_FILE
	m_reportFile.open("testReport.txt");
#endif /*NO_OUTPUT_FILE*/
}

Test::TesterReport::TesterReport(char * pFilename)
{
#ifndef NO_OUTPUT_FILE
	m_reportFile.open(pFilename);
#endif /*NO_OUTPUT_FILE*/
}

Test::TesterReport::~TesterReport()
{
#ifndef NO_OUTPUT_FILE
	m_reportFile.close();
#endif /*NO_OUTPUT_FILE*/

	if(NULL!=g_instance) {
		delete g_instance;
	}
}

Test::TesterReport * Test::TesterReport::getInstance(){
	if (!g_instance) {
		g_instance = new TesterReport();
	}
	return g_instance;
}

void Test::TesterReport::printHeader(const char * pMessage)
{
#ifndef NO_OUTPUT_CONSOLE
	printf(STR_LINE_JUMP);
	printf(STR_LINE_DISPLAY_SEP);
	printf(STR_LINE_JUMP);
	printf("%s\r\n", pMessage);
	printf(STR_LINE_DISPLAY_SEP);
	printf(STR_LINE_JUMP);
#endif // NO_OUTPUT_CONSOLE

#ifndef NO_OUTPUT_FILE
	// put into file (filename)
	m_reportFile <<  STR_LINE_DISPLAY_SEP << STR_LINE_JUMP<< pMessage << STR_LINE_JUMP << STR_LINE_DISPLAY_SEP << std::endl;
#endif // NO_OUTPUT_FILE

}

// --------------------------------------------------------------------
void Test::TesterReport::printSummary(bool bCondition, const char * pName, const char * pFunction)
{
	// test summary
#ifndef NO_OUTPUT_CONSOLE
	printf("%s\t[%s]\t%s\r\n", (true == bCondition)? REPORT_SUCCESS : REPORT_FAILURE, pName, pFunction);
#endif // NO_OUTPUT_CONSOLE

#ifndef NO_OUTPUT_FILE
	m_reportFile << ((true == bCondition)? REPORT_SUCCESS : REPORT_FAILURE) << "\t[" << pName << "]\t" << pFunction << std::endl;
#endif // NO_OUTPUT_FILE
}

// --------------------------------------------------------------------
