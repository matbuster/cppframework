/**
 * \file 		assertion.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef ASSERTION_H
#define ASSERTION_H

#include <assert.h>

//#define ASSERT(value, message)	assert(value && message)
//#define CHECK(value, message)

namespace Debug {

	// -----------------------------------------------------------------------------
	/** assert, only available for debug mode. This function using base assert
	 * function to work. A message will display if condition is false
	 * @param [in] bValue: false for display assert message, true to pass test
	 * @return success or failed
	 */
	bool Assert(bool bValue);
	
	// -----------------------------------------------------------------------------
	/** assert, only available for debug mode. This function using base assert
	 * function to work. A message will display if condition is false. The pMessage
	 * will be displayed in a console if the programm is attached to console
	 * @param [in] bValue: false for display assert message, true to pass test
	 * @return success or failed
	 */
	bool Assert(bool bValue, const char * pMessage);
};

#endif /* ASSERTION_H */