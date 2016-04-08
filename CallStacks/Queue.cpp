/**
 * \file 		Queue.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#include <stdio.h>
#include <string.h>

#include "Queue.h"

// -------------------------------------------------------------
CallStacks::Queue::Queue() 
	: BaseCallStacks()
{
}
// -------------------------------------------------------------
CallStacks::Queue::~Queue() 
{
}
// -------------------------------------------------------------
unsigned long CallStacks::Queue::getRequest(CallStacks::BaseStackMessage * message)
{
	unsigned long lReturnCode = BASESTACK_OK;
	if(m_mutex->WaitOne()) 
	{
		try
		{
			message->copy(m_stack->getItem(0));
		} 
		catch(...)
		{
			lReturnCode = BASESTACK_NO_ITEMS;
		}
		m_mutex->Release();
	}
	return lReturnCode;
}
// -------------------------------------------------------------
unsigned long CallStacks::Queue::getRequest(unsigned char * pBufferRequest, unsigned long * lSizeBufferRequest)
{
	unsigned long lReturnCode = BASESTACK_OK;
	if(m_mutex->WaitOne()) 
	{
		try
		{
			CallStacks::BaseStackMessage * message = m_stack->getItem(0);
			memcpy(pBufferRequest, message->getMessage(), message->getSizeMessage());
			*lSizeBufferRequest = message->getSizeMessage();
		} 
		catch(...)
		{
			lReturnCode = BASESTACK_NO_ITEMS;
		}
		m_mutex->Release();
	}
	return lReturnCode;
}
// -------------------------------------------------------------
unsigned long CallStacks::Queue::popRequest(unsigned char * pBufferRequest, unsigned long * lSizeBufferRequest)
{
	unsigned long lReturnCode = BASESTACK_OK;
	
	lReturnCode = getRequest(pBufferRequest, lSizeBufferRequest);
	if(BASESTACK_OK == lReturnCode)
	{
		if(m_mutex->WaitOne()) 
		{
			try
			{
				m_stack->Remove(0);
			}
			catch(...)
			{
				lReturnCode = BASESTACK_NO_IT_FOUND;
			}
			m_mutex->Release();
		}
	}

	return lReturnCode;
}
// -------------------------------------------------------------
unsigned long CallStacks::Queue::popRequest(CallStacks::BaseStackMessage * message)
{
	unsigned long lReturnCode = BASESTACK_OK;
	lReturnCode = getRequest(message);
	if(BASESTACK_OK == lReturnCode)
	{
		if(m_mutex->WaitOne()) 
		{
			try
			{
				message->copy(m_stack->getItem(0));
				delete m_stack->getItem(0);
				m_stack->Remove(0);
			}
			catch(...)
			{
				lReturnCode = BASESTACK_NO_IT_FOUND;
			}
			m_mutex->Release();
		}
	}
	return lReturnCode;
}
// -------------------------------------------------------------


