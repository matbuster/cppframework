/**
 * \file 		BaseStackMessage.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#ifndef BASE_STACK_MESSAGE_H
#define BASE_STACK_MESSAGE_H

#include "toolsconstant.h"

/** \brief class creaation 27/02/2014. First appear in framework 1.0
 * BaseStackMessage is a base message for stack
 */
namespace CallStacks {

	class BaseStackMessage {

	private:
		/** unique id of message in stack */
		unsigned long m_lAbsoluteIdMessage;
		
		/** buffer for stack message */
		unsigned char m_pBufferMessage[STR_HUGE];

		/** size of message */
		unsigned long m_lSizeMessage;

	public:
		/** main constructor and destructor */
		BaseStackMessage();
		BaseStackMessage(unsigned long ulAbsoluteId, unsigned char * pMessage, unsigned long lSizeMessage);
		BaseStackMessage(BaseStackMessage * message);
		~BaseStackMessage();

		/** getter on the absolute id of message
		 * @return absolute identifiant of message
		 */
		unsigned long getIdentifiantMessage();

		/** setter on the absolute id of message
		 * @param id: value of absolute id
		 */
		void setIdentifiantMessage(unsigned long id);

		/** getter on the message
		 * @return pointer on the message
		 */
		unsigned char * getMessage();

		/** function to get the message size
		 * @return lMessageSize : size of buffer 
		 */
		unsigned long getSizeMessage();

		/** function to get the max capacity of stack message
		 * @return lMaxCapacity : capacity max of BaseStackMessage
		 */
		unsigned long getMaxCapacity();

		/** copy a existing message
		 * @param [in] message: input message to copy
		 * @return error return code
		 */
		unsigned long copy(BaseStackMessage * message);
	};
};

#endif /* BASE_STACK_MESSAGE_H */