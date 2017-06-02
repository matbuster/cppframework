#ifndef CPP_FRAMEWORK_TESTER_DEFINES_H
#define CPP_FRAMEWORK_TESTER_DEFINES_H

// ---------------------------------------------------------------------------------------------
// generic error code definition
#define TEST_OK							0
#define TEST_KO							1

// ---------------------------------------------------------------------------------------------
// string constant definition
#define STR_LINE_JUMP					"\r\n"
#define STR_LINE_DISPLAY_SEP			"##################################################"
#define STR_LINE_TAB					"\t"

// ---------------------------------------------------------------------------------------------
void printHeader(const char * pMessage);
// ---------------------------------------------------------------------------------------------
void printSummary(bool bCondition, const char * pName, const char * pFunction);
// ---------------------------------------------------------------------------------------------

#endif /* CPP_FRAMEWORK_TESTER_DEFINES_H */