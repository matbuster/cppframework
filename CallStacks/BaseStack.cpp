/**
 * \file 		BaseStack.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */

#include "BaseStack.h"
#include <stdio.h>

// ------------------------------------------------------------

CallStacks::BaseCallStacks::BaseCallStacks() {
    m_mutex = new Threading::Mutex();
    m_stack = new Collection::List<CallStacks::BaseStackMessage*>();
}
// ------------------------------------------------------------

CallStacks::BaseCallStacks::~BaseCallStacks() {
    delete m_mutex;

    // delete each items of the collection
    int iTotalValues = m_stack->Count();
    for (int i = 0; i < iTotalValues; i++) {
        delete m_stack->getItem(0);
        m_stack->Remove(0);
    }
    m_stack->Clear();
    delete m_stack;
}
// ------------------------------------------------------------

unsigned long CallStacks::BaseCallStacks::getCount() {
    int iCount = 0;
    if (m_mutex->WaitOne()) {
        iCount = m_stack->Count();
        m_mutex->Release();
    }
    return iCount;
}
// ----------------------------------------------------------------

unsigned long CallStacks::BaseCallStacks::getMaxCapacity() {
    int iCount = 0;
    if (m_mutex->WaitOne()) {
        iCount = m_stack->getMaxCapacity();
        m_mutex->Release();
    }
    return iCount;
}
// ----------------------------------------------------------------

unsigned long CallStacks::BaseCallStacks::pushRequest(CallStacks::BaseStackMessage * message) {
    
    if (m_mutex->WaitOne()) {
        m_stack->Add(message);
        m_mutex->Release();
    }
    return BASESTACK_OK;
}
// ----------------------------------------------------------------

unsigned long CallStacks::BaseCallStacks::pushRequest(unsigned char * pBufferRequest, unsigned long lSizeBufferRequest) {

    if (m_mutex->WaitOne()) {
        CallStacks::BaseStackMessage * message = new CallStacks::BaseStackMessage(getAbsoluteCounter(), pBufferRequest, lSizeBufferRequest);
        m_stack->Add(message);
        m_mutex->Release();
    }
    return BASESTACK_OK;
}
// ----------------------------------------------------------------

