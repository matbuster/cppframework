
#include "commandConsole.h"
#include "console.h"

// framework includes
#include "../Hardware/keyboard.h"
#include "../Tools/String/StringTools.h"
#include "../Tools/String/StdStringTools.h"
#include "../Tools/File/Directory.h"
#include "../Tools/File/FileFolder.h"
#include "../Tools/File/FileFolderInfos.h"
#include "../Tools/Collection/GetterCollection.hpp"

#include <string>

// ------------------------------------------------------------------------
// console version
#define CC_MAJOR_VERSION		1
#define CC_MINOR_VERSION		0
#define CC_RELEASE_VERSION		0

// ------------------------------------------------------------------------
#define MAX_SIZE_INPUT_STRING	1024

// ------------------------------------------------------------------------
/**! internal instance definition of Testreport */
static Diagnostic::CommandConsole * g_instance = NULL;

// ------------------------------------------------------------------------
Diagnostic::CommandConsole::CommandConsole()
{
	char pTempDirectory[MAX_SIZE_INPUT_STRING];
	memset(pTempDirectory, 0, MAX_SIZE_INPUT_STRING);

	// initialize command list
	m_lAvailableCommand.push_back(new Diagnostic::CommandConsoleHelper(COMMAND_KEY_HELP, COMMAND_CMD_HELP_ADDITIONNAL));
	m_lAvailableCommand.push_back(new Diagnostic::CommandConsoleHelper(COMMAND_KEY_ESC, COMMAND_CMD_ESP_ADDITIONNAL));
	m_lAvailableCommand.push_back(new Diagnostic::CommandConsoleHelper(COMMAND_KEY_DIR, COMMAND_CMD_DIR_ADDITIONNAL));
	m_lAvailableCommand.push_back(new Diagnostic::CommandConsoleHelper(COMMAND_KEY_CD, COMMAND_CMD_CD_ADDITIONNAL));

	// initialize current directory value
#ifdef _WINDOWS
	Tools::Directory::GetSpecificFolder(PATH_DOCUMENTS, pTempDirectory, MAX_SIZE_INPUT_STRING);
#endif // WINDOWS

#ifdef LINUX
	// maybe another folder could be initialized for unix system
	Tools::Directory::GetSpecificFolder(PATH_SYS_32, pTempDirectory, MAX_SIZE_INPUT_STRING);
#endif // LINUX

	// update current value
	setCurrentDirectory(pTempDirectory);
}
// ------------------------------------------------------------------------
Diagnostic::CommandConsole::~CommandConsole()
{
	for(std::list<Diagnostic::CommandConsoleHelper*>::iterator it = m_lAvailableCommand.begin(); it != m_lAvailableCommand.end(); it++)
	{
		Diagnostic::CommandConsoleHelper * item = (*it);
		delete item;
	}
}
// ------------------------------------------------------------------------
std::string Diagnostic::CommandConsole::getCurrentDirectory()
{
	return m_strCurrentDirectory;
}
// ------------------------------------------------------------------------
void Diagnostic::CommandConsole::setCurrentDirectory(std::string _strCurrentDirectory)
{
	m_strCurrentDirectory = _strCurrentDirectory;
	// test if the last char is a PATH_DELIMITER
	if(m_strCurrentDirectory.size() > 0) 
	{
		std::string c(1, m_strCurrentDirectory.at(m_strCurrentDirectory.size() - 1));
		if(0 !=  c.compare(PATH_SEPARATOR))
		{
			m_strCurrentDirectory.append(PATH_SEPARATOR);
		}
	}
}
// ------------------------------------------------------------------------
Diagnostic::CommandConsole * Diagnostic::CommandConsole::getInstance()
{
	if(NULL == g_instance)
	{
		g_instance = new Diagnostic::CommandConsole();
	}
	return g_instance;
}
// ------------------------------------------------------------------------
int Diagnostic::CommandConsole::isKeyWord(char * _pInputKey)
{
	int iNextState = COMMAND_NO_STATE;
	char pUpperCase[MAX_SIZE_INPUT_STRING];
	memset(pUpperCase, 0, MAX_SIZE_INPUT_STRING);

	Tools::String::UpperCase(_pInputKey, strlen(_pInputKey), pUpperCase);
	if(0 == memcmp(pUpperCase, COMMAND_KEY_HELP, sizeof(COMMAND_KEY_HELP)-1)) 
	{
		iNextState = COMMAND_STATE_HELP;
	} 
	else if(0 == memcmp(pUpperCase, COMMAND_KEY_ESC, sizeof(COMMAND_KEY_ESC)-1)) 
	{
		iNextState = COMMAND_STATE_ESC;
	}
	else if(0 == memcmp(pUpperCase, COMMAND_KEY_DIR, sizeof(COMMAND_KEY_DIR)-1)) 
	{
		iNextState = COMMAND_STATE_DIR;
	}
	else if(0 == memcmp(pUpperCase, COMMAND_KEY_CD, sizeof(COMMAND_KEY_CD)-1)) 
	{
		iNextState = COMMAND_STATE_CD;
	}
	//

	return iNextState;
}
// ------------------------------------------------------------------------
void Diagnostic::CommandConsole::displayConsoleVersion()
{
	Diagnostic::displayArgsWithFunctionName("Command console", "Version : %d.%d.%d\r\n", CC_MAJOR_VERSION, CC_MINOR_VERSION, CC_RELEASE_VERSION);
}
// ------------------------------------------------------------------------
void Diagnostic::CommandConsole::displayCurrentPath()
{
	char pTempDirectory[MAX_SIZE_INPUT_STRING];
	memset(pTempDirectory, 0, MAX_SIZE_INPUT_STRING);
	//
	memcpy(pTempDirectory, getCurrentDirectory().c_str(), getCurrentDirectory().size() -1 );
	strcat(pTempDirectory, KEY_INPUT);
	//
	Diagnostic::displayNoJump( pTempDirectory );
}
// ------------------------------------------------------------------------
void Diagnostic::CommandConsole::displayHelpInformations()
{
	for(std::list<Diagnostic::CommandConsoleHelper*>::iterator it = m_lAvailableCommand.begin(); it != m_lAvailableCommand.end(); it++)
	{
		Diagnostic::CommandConsoleHelper * item = *it;
		Diagnostic::display((char*)item->getCommand().c_str(), (char*)item->getHelperText().c_str());
		printf(KEY_JUMP);
	}
}
// ------------------------------------------------------------------------
void Diagnostic::CommandConsole::displayDirFromCurrentPath()
{
	Diagnostic::display("TODO exex dir");
	//
	std::list<Tools::Files::FileFolderInfos*> ffinfos;
	Tools::Files::getFileAndFolderInformations(m_strCurrentDirectory,  &ffinfos);
	//
	for(std::list<Tools::Files::FileFolderInfos*>::iterator it = ffinfos.begin(); it != ffinfos.end(); it++)
	{
		Tools::Files::FileFolderInfos * item = *it;
		Diagnostic::displayArgs("%s\t%s\t%lu\t%s",(char*)item->getModificationDate().c_str(), (char*)item->getTypeKeyword().c_str(), item->getFileSize() ,(char*)item->getFilename().c_str());
	}
}
// ------------------------------------------------------------------------
void Diagnostic::CommandConsole::modifyCurrentPath(std::string _strInputKey)
{
	Diagnostic::display("TODO CD Command");

	std::list<std::string> pOut;
	Tools::String::StringSplit(&pOut, _strInputKey, " ");

	if(pOut.size() > 0)
	{
		if(pOut.size() <= 1)
		{
			Diagnostic::display((char*)m_strCurrentDirectory.c_str());
		}
		else
		{
			std::string sAdd = Tools::Collection::get(&pOut, 1);
			if(Tools::String::StringCointain((unsigned char*)sAdd.c_str(), sAdd.length(), (unsigned char*)COMMAND_KEY_INPUT_UPPER_DIR, sizeof(COMMAND_KEY_INPUT_UPPER_DIR)-1))
			{
				char pUpper[256] = {0};
				int iUpperSize = 0;
				if(DIRTOOLS_OK == Tools::Directory::GetUpperFolder(pUpper, &iUpperSize, (char*)m_strCurrentDirectory.c_str(), m_strCurrentDirectory.length()-1))
				{
					setCurrentDirectory(pUpper);
				}
			}
			else //
			{
				Diagnostic::display("Test PATH existing to Change path");
			}
		}
	}
}
// ------------------------------------------------------------------------
bool Diagnostic::CommandConsole::displayCommandConsole()
{
	bool bSuccess = false;
	bool bInputMenuPressed = false;

	// initialize size output
	int iOutStringSize = 0;
	char pKeyString[MAX_SIZE_INPUT_STRING];
	//
	memset(pKeyString ,0, MAX_SIZE_INPUT_STRING);
	
	// display version
	Diagnostic::CommandConsole::displayConsoleVersion();
	while(!bInputMenuPressed) {
	
		// input command as current path
		Diagnostic::CommandConsole::displayCurrentPath();

		// get the input value
		Hardware::Keyboard::getStringValue(pKeyString, &iOutStringSize , MAX_SIZE_INPUT_STRING);
		
		// test key words
		int iNextState = Diagnostic::CommandConsole::getInstance()->isKeyWord(pKeyString);
		switch(iNextState)
		{
		case COMMAND_NO_STATE:
			printf("You entered: %s", pKeyString);
			break;
		case COMMAND_STATE_ESC:
			Diagnostic::display("Leaving Command console, Bye ;)");
			bInputMenuPressed = true;
			break;
		case COMMAND_STATE_HELP:
			displayHelpInformations();
			break;
		case COMMAND_STATE_DIR:
			displayDirFromCurrentPath();
			break;
		case COMMAND_STATE_CD:
			modifyCurrentPath(pKeyString);
			break;
		default:
			bInputMenuPressed = true;
			break;
		};
	}

	return bSuccess;
}
// ------------------------------------------------------------------------
