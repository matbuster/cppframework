/**
 * \file 		Pointer.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef MEMORY_TOOLS_H
#define MEMORY_TOOLS_H

namespace Memory {

	/** function to check the pointer value 
	 * @return success if pointer is valid, false if not
	 */
	bool CheckPointerValue(int * pointerValue);

	/** function to get the pointer value corresponding message */
	const char * getPointerValueCorrespondingMessage(int * pointerValue);
};

#endif /* MEMORY_TOOLS_H */