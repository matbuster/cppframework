/**
 * \file 		Queue.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef QUEUE_H
#define QUEUE_H

#include "CallStacks/BaseStack.h"

namespace CallStacks {

	/** Queue is a FIFO (first in first out) data structure. 
	 * This class is thread safe.
 	 */
	class Queue : public CallStacks::BaseCallStacks 
	{

	public:
		Queue();
		virtual ~Queue();
		
		/** function to get the first request. this function don't delete it, but get only the first
		 * available. To get it and delete use pop.
		 * @param [out] pBufferRequest: buffer containing the request
		 * @param [out] lSizeBufferRequest : size of the request
		 * @return error code
		 */
		unsigned long getRequest(unsigned char * pBufferRequest, unsigned long * lSizeBufferRequest);

		/** function to get the corresponding message from call stack 
		 * @param [in] pBufferRequest: buffer containing the request
		 * @return error code
		 */
		unsigned long getRequest(CallStacks::BaseStackMessage * message);

		/** function to pop the corresponding request from call stack. For the queue this is First request pushed.
		 * This function det the request and delete it from the queue.
		 * @param [out] pBufferRequest: buffer containing the request
		 * @param [out] lSizeBufferRequest : size of the request
		 * @return error code
		 */
		unsigned long popRequest(unsigned char * pBufferRequest, unsigned long * lSizeBufferRequest);

		/** function to pop the corresponding request from call stack, using baseStackMessage 
		 * @param [in] pBufferRequest: buffer containing the request
		 * @return error code
		 */
		unsigned long popRequest(CallStacks::BaseStackMessage * message);
	};
};

#endif /* QUEUE_H */