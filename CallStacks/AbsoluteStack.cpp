/**
 * \file 		AbsoluteStack.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */

#include <stdio.h>
#include <string.h>

#include "AbsoluteStack.h"

// ----------------------------------------------------------------

CallStacks::AbsoluteStack::AbsoluteStack()
: CallStacks::BaseCallStacks() {
}

CallStacks::AbsoluteStack::~AbsoluteStack() {
}
// ----------------------------------------------------------------

unsigned long CallStacks::AbsoluteStack::getRequest(unsigned char * pBufferRequest, unsigned long * lSizeBufferRequest) {
    // function to get the first request available (FIFO)
    unsigned long lReturnCode = BASESTACK_OK;
    if (m_mutex->WaitOne()) {
        try {
            CallStacks::BaseStackMessage * message = new CallStacks::BaseStackMessage(0, pBufferRequest, *lSizeBufferRequest);
            memcpy(pBufferRequest, message->getMessage(), message->getSizeMessage());
            message = m_stack->getItem(0);
            delete message;
        } catch (...) {
            lReturnCode = BASESTACK_NO_IT_FOUND;
        }
        m_mutex->Release();
    }
    return lReturnCode;
}
// ----------------------------------------------------------------

unsigned long CallStacks::AbsoluteStack::getRequest(CallStacks::BaseStackMessage * message) {
    
    unsigned long lReturnCode = BASESTACK_NO_IT_FOUND;
    if (m_mutex->WaitOne()) {
        // looking for the target absolute id
        try {
            unsigned long ulAbsoluteId = message->getIdentifiantMessage();
            for (int i = 0; i < m_stack->Count(); i++) {
                if (ulAbsoluteId == m_stack->getItem(i)->getIdentifiantMessage()) {
                    message->copy(m_stack->getItem(i));
                    lReturnCode = BASESTACK_OK;
                    break;
                }
            }
        } catch (...) {
            lReturnCode = BASESTACK_NO_IT_FOUND;
        }
        m_mutex->Release();
    }
    return lReturnCode;
}
// ----------------------------------------------------------------

unsigned long CallStacks::AbsoluteStack::popRequest(unsigned char * pBufferRequest, unsigned long * lSizeBufferRequest) {
    unsigned long lReturnCode = BASESTACK_OK;
    if (m_mutex->WaitOne()) {
        lReturnCode = getRequest(pBufferRequest, lSizeBufferRequest);
        if (BASESTACK_OK == lReturnCode) {
            try {
                m_stack->Remove(0);
            } catch (...) {
                lReturnCode = BASESTACK_NO_IT_FOUND;
            }
        }
        m_mutex->Release();
    }
    return lReturnCode;
}
// ----------------------------------------------------------------

unsigned long CallStacks::AbsoluteStack::popRequest(CallStacks::BaseStackMessage * message) {
    unsigned long lReturnCode = BASESTACK_NO_IT_FOUND;
    if (m_mutex->WaitOne()) {
        unsigned long ulAbsId = message->getIdentifiantMessage();
		int iNumberMessage = m_stack->Count();

        for (int i = 0; i < iNumberMessage; i++) {
            try {
				unsigned long ulCurMessageId = m_stack->getItem(i)->getIdentifiantMessage();
                if (ulAbsId == ulCurMessageId) {
                    lReturnCode = BASESTACK_OK;
                    message->copy(m_stack->getItem(i));

                    delete m_stack->getItem(i);
                    m_stack->Remove(i);
                    break;
                }
            } catch (...) {
                lReturnCode = BASESTACK_NO_IT_FOUND;
            }
        }
        m_mutex->Release();
    }
    return lReturnCode;
}
// ----------------------------------------------------------------