/**
 * \file 		commandConsole.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
#include "commandConsoleHelper.h"

// ------------------------------------------------------------------------
Diagnostic::CommandConsoleHelper::CommandConsoleHelper(const char * _strCommand, const char * _strCommandHelper)
{
	m_strCommand.assign(_strCommand, strlen(_strCommand));
	m_strHelperText.assign(_strCommandHelper, strlen(_strCommandHelper));
}
// ------------------------------------------------------------------------
Diagnostic::CommandConsoleHelper::~CommandConsoleHelper()
{
}
// ------------------------------------------------------------------------
std::string Diagnostic::CommandConsoleHelper::getCommand()
{
	return m_strCommand;
}
// ------------------------------------------------------------------------
std::string Diagnostic::CommandConsoleHelper::getHelperText()
{
	return m_strHelperText;
}
// ------------------------------------------------------------------------
