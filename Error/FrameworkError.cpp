/**
 * \file 		FrameworkError.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#include "FrameworkError.h"

// ---------------------------------------------------------------------------------------
char * Error::FrameworkErrorHandling::getNamespaceFromErrorCode(long _lErrorCode)
{
	if(BASESTACK_FRAMEMORK_OFFSET >= _lErrorCode && _lErrorCode < (BASESTACK_FRAMEMORK_OFFSET + 1000))
	{
		return CALLSTACK_NAMESPACE;
	}
	return UNKNOWN_NAMESPACE;
}
// ---------------------------------------------------------------------------------------