/**
 * \file 		assertion.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#include "assertion.h"
#include <stdio.h>

// -----------------------------------------------------------------------------
bool Diagnostic::Assert(bool bValue)
{
#ifdef _DEBUG
	assert(bValue);
#endif /* _DEBUG */
	return bValue;
}
// -----------------------------------------------------------------------------
bool Diagnostic::Assert(bool bValue, const char * pMessage)
{
#ifdef _DEBUG
	printf(pMessage);
	printf("\r\n");
	assert(bValue && pMessage);
#else //_DEBUG
	pMessage;
#endif /* _DEBUG */
	return bValue;
}
// -----------------------------------------------------------------------------