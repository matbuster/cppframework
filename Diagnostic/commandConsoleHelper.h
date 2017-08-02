/**
 * \file 		commandConsole.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#ifndef COMMAND_CONSOLE_HELPER_H
#define COMMAND_CONSOLE_HELPER_H

#include <string>
// ------------------------------------------------------------------------
namespace Diagnostic {

	class CommandConsoleHelper {
	
	private:
		/**! command value */
		std::string m_strCommand;
		
		/**! helper text value */
		std::string m_strHelperText;
		
	public:
		/**! singleton and destructor */
		CommandConsoleHelper(const char * _strCommand, const char * _strCommandHelper);
		~CommandConsoleHelper();
		
		/**! getter on the command value 
		 * \return command value
 		 */
		std::string getCommand();
		
		/**! getter on the command helper text value 
		 * \return text helper 
 		 */
		std::string getHelperText();
	}; 
};

#endif /* COMMAND_CONSOLE_HELPER_H */