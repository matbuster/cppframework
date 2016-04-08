/**
 * \file 		FrameworkError.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef FRAMEWORK_ERROR_H
#define FRAMEWORK_ERROR_H

// --------------------------------------------------------------------------------------
// includes
// TODOMAT
// define all SHIFHT_ERROR_HANDLING_NAMESPACE in a single file for each namespace called ErrorNamespace.h 
#include "../CallStacks/CallStacksDefines.h"

// --------------------------------------------------------------------------------------
#define UNKNOWN_NAMESPACE		"NoNamespace"

// --------------------------------------------------------------------------------------
namespace Error {

	namespace FrameworkErrorHandling {

		/** function to return the specific namespace according to the normalize error code from framework */
		static char * getNamespaceFromErrorCode(long _lErrorCode);
	};
};

#endif /* FRAMEWORK_ERROR_H */