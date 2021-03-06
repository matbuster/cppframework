/**
 * \file 		CallStacksDefines.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#ifndef CALLSTACKS_ERROR_H
#define CALLSTACKS_ERROR_H

#define CALLSTACK_NAMESPACE					"CallStacks"

#define BASESTACK_FRAMEMORK_OFFSET			1000

#define BASESTACK_OK						0
#define BASESTACK_KO						BASESTACK_FRAMEMORK_OFFSET + 1
#define BASESTACK_NO_ITEMS					BASESTACK_FRAMEMORK_OFFSET + 2
#define BASESTACK_NO_IT_FOUND				BASESTACK_FRAMEMORK_OFFSET + 3

#endif /* CALLSTACKS_ERROR_H */