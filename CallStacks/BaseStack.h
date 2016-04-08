/**
 * \file 		BaseStack.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#ifndef BASE_STACK_H
#define BASE_STACK_H

// --------------------------------------------------------
// include cpp framwork tools
#include "Threading/Mutex.h"
#include "Collection/List.hpp"

#include "BaseStackMessage.h"
#include "CallStacksDefines.h"

#define BASESTACK_DEFAULT_ID	0

/** default absolute counter for request */
static unsigned long _sAbsoluteCounter = 0;

namespace CallStacks {

	class BaseCallStacks {
	
	protected:
		/** list used to stack items*/
		Collection::List<CallStacks::BaseStackMessage *> * m_stack;

		/** internal mutex declaration */
		Threading::Mutex * m_mutex;

		/** return the value of absolute counter */
		unsigned long getAbsoluteCounter() { return _sAbsoluteCounter++; }
                
	public:
		BaseCallStacks();
		~BaseCallStacks();

		/** function to get the number of message in stack */
		unsigned long getCount();

		/** getter on the max capacity of the stack */
		unsigned long getMaxCapacity();
		
		/** function to push a new BaseStackMessage to the call stack 
		 * @param [in] pBufferRequest: buffer containing the request
		 * @return error code
		 */
		unsigned long pushRequest(CallStacks::BaseStackMessage * message); 

		/** function to push a new request to the call stack. 
		 * @param [in] pBufferRequest: buffer containing the request
		 * @param [in] lSizeBufferRequest : size of the request
		 * @return error code
		 */
		unsigned long pushRequest(unsigned char * pBufferRequest, unsigned long lSizeBufferRequest); 
	};
};

#endif /* BASE_STACK_H */