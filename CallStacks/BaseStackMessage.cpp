/**
 * \file 		BaseStackMessage.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#include <stdio.h>
#include <string.h>

#include "BaseStackMessage.h"

// ------------------------------------------------
CallStacks::BaseStackMessage::BaseStackMessage()
{
	m_lAbsoluteIdMessage = 0;
	m_lSizeMessage = STR_HUGE;
	memset(m_pBufferMessage, 0x00, STR_HUGE);
}
// ------------------------------------------------
CallStacks::BaseStackMessage::BaseStackMessage(unsigned long ulAbsoluteId, unsigned char * pMessage, unsigned long lSizeMessage)
{
	m_lAbsoluteIdMessage = ulAbsoluteId;
	if(STR_HUGE < lSizeMessage) 
	{
		m_lSizeMessage = STR_HUGE;
	}
	else m_lSizeMessage = lSizeMessage;
	
	// clear allocated buffer
	memset(m_pBufferMessage, 0x00, STR_HUGE);
	memcpy(m_pBufferMessage, pMessage, m_lSizeMessage);
}
// ------------------------------------------------
CallStacks::BaseStackMessage::BaseStackMessage(BaseStackMessage * message)
{
	m_lAbsoluteIdMessage = message->getIdentifiantMessage();
	m_lSizeMessage = message->getSizeMessage();

	memset(m_pBufferMessage, 0x00, STR_HUGE);
	memcpy(m_pBufferMessage, message->getMessage(), m_lSizeMessage);
}
// ------------------------------------------------
CallStacks::BaseStackMessage::~BaseStackMessage()
{
}
// ------------------------------------------------
unsigned long CallStacks::BaseStackMessage::copy(BaseStackMessage * message)
{
	m_lAbsoluteIdMessage = message->getIdentifiantMessage();
	m_lSizeMessage = message->getSizeMessage();

	memset(m_pBufferMessage, 0x00, STR_HUGE);
	memcpy(m_pBufferMessage, message->getMessage(), m_lSizeMessage);

	return 0;
}
// ------------------------------------------------
unsigned long CallStacks::BaseStackMessage::getIdentifiantMessage()
{
	return m_lAbsoluteIdMessage;
}
// ------------------------------------------------
void CallStacks::BaseStackMessage::setIdentifiantMessage(unsigned long id)
{
	m_lAbsoluteIdMessage = id;
}
// ------------------------------------------------
unsigned char * CallStacks::BaseStackMessage::getMessage()
{
	return m_pBufferMessage;
}
// ------------------------------------------------
unsigned long CallStacks::BaseStackMessage::getSizeMessage()
{
	return m_lSizeMessage;
}
// ------------------------------------------------
unsigned long CallStacks::BaseStackMessage::getMaxCapacity()
{
	return STR_HUGE;
}
// ------------------------------------------------

