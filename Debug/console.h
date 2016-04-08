/**
 * \file 		console.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#ifndef CONSOLE_H
#define CONSOLE_H

namespace Debug {

	// ------------------------------------------------------------------------
	/** function to display a message in a console
	 * \param [in] message: message to display in console ( message to display, no additionnal CR )
	 * \return success or failed
	 */
	bool display(char * message);

	
	// ------------------------------------------------------------------------
	/** function to display a message in a console
	 * \param [in] functionName: name of funciton to display in the console
	 * \param [in] message: message to display in console ( message to display, no additionnal CR )
	 * \return success or failed
	 */
	bool display(char * functionName, char * message);

	// ------------------------------------------------------------------------
	/** function to display a message and add argument in the corresponding message
	 * \param [in] message: message to display in console
	 * \param [in] ... argument to pass to function to display in message
	 * \return success or fail
	 */
	bool displayArgs(char * message, ...);

	// ------------------------------------------------------------------------
	/** function to display a message and add argument in the corresponding message
	 * \param [in] functionName: name of funciton to display in the console
	 * \param [in] message: message to display in console
	 * \param [in] ... argument to pass to function to display in message
	 * \return success or fail
	 */
	bool displayArgs(char * functionName, char * message, ...);
};

#endif /* CONSOLE_H */