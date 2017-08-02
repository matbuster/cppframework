/**
 * \file 		commandConsole.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#ifndef COMMAND_CONSOLE_H
#define COMMAND_CONSOLE_H

// ------------------------------------------------------------------------
// command key definition
#define COMMAND_KEY_HELP		"HELP"
#define COMMAND_KEY_ESC			"ESC"
#define COMMAND_KEY_DIR			"DIR"
#define COMMAND_KEY_CD			"CD"
#define COMMAND_KEY_GEP_PATH	"GETPATH"

// ------------------------------------------------------------------------
#define COMMAND_CMD_HELP_ADDITIONNAL			"More information about a specific command, use help followed by the target command"
#define COMMAND_CMD_ESP_ADDITIONNAL				"Leave the command console"
#define COMMAND_CMD_DIR_ADDITIONNAL				"List all files and folder in the current directory"
#define COMMAND_CMD_CD_ADDITIONNAL				"Modify the current directory"
#define COMMAND_CMD_GET_PATH_ADDITIONNAL		"Get a path using command "

// ------------------------------------------------------------------------
#define COMMAND_KEY_INPUT_UPPER_DIR		".."

// ------------------------------------------------------------------------
#define COMMAND_NO_STATE		0
#define COMMAND_STATE_HELP		1
#define COMMAND_STATE_ESC		2
#define COMMAND_STATE_DIR		3
#define COMMAND_STATE_CD		4

// ------------------------------------------------------------------------
#define KEY_INPUT			">"
#define KEY_JUMP			"\r\n"

// ------------------------------------------------------------------------
#include "commandConsoleHelper.h"

// ------------------------------------------------------------------------
#include <list>
#include <string>

// ------------------------------------------------------------------------
namespace Diagnostic {

	class CommandConsole {
	
	private:
		/**! value of the current directory */
		std::string m_strCurrentDirectory;

		/**! list of available command */
		std::list<Diagnostic::CommandConsoleHelper*> m_lAvailableCommand;
	
		/**! constructor*/
		CommandConsole();

		/**! function to get current directory value */
		std::string getCurrentDirectory();

		/**! function to set the current directory value */
		void setCurrentDirectory(std::string _strCurrentDirectory);

	public:
		/**! singleton and destructor */
		static CommandConsole * getInstance();
		~CommandConsole();

		// ------------------------------------------------------------------------
		/**! function to know if the current key pressend is a keyword
		 * \param in _pInputKey : input key value
		 * \return next state machine
		 */
		int isKeyWord(char * _pInputKey);

		// ------------------------------------------------------------------------
		/**! display version console in diagnostic console */
		void displayConsoleVersion();

		// ------------------------------------------------------------------------
		/**! function to display help informations */
		void displayHelpInformations();

		// ------------------------------------------------------------------------
		/**! function to print the current path as a command */
		void displayCurrentPath();

		// ------------------------------------------------------------------------
		/**! function to list all the folders and file from the current path */
		void displayDirFromCurrentPath();
		
		// ------------------------------------------------------------------------
		/**! function to modify the current path displayed in the console.
		 * \param [in] _strInputKey : input commant
		 */
		void modifyCurrentPath(std::string _strInputKey);

		// ------------------------------------------------------------------------
		/**! function to display a command console 
		 * \return success or fail
		 */
		bool displayCommandConsole();
	}; 
};

#endif /* COMMAND_CONSOLE_H */