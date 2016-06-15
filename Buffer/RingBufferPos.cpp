
#include "RingBufferPos.h"

// -------------------------------------------------------------------------
Buffer::RingBufferPos::RingBufferPos(unsigned long _lLenBuffer) 
{
	m_i64AbsN = 0;
	m_ulPosN = 0;
	m_ulLen = _lLenBuffer;
}
Buffer::RingBufferPos::~RingBufferPos() 
{
}
// -------------------------------------------------------------------------
int Buffer::RingBufferPos::incrementIndex()
{
	m_i64AbsN++;
	m_ulPosN++; 
	if((m_ulPosN)>m_ulLen-1)
	{
		m_ulPosN-=m_ulLen;
	}
	return RBI_OK;
}
// -------------------------------------------------------------------------
int Buffer::RingBufferPos::decrementIndex()
{
	m_i64AbsN--;
	m_ulPosN--;
	if((m_ulPosN)<0)
	{
		m_ulPosN+=m_ulLen;
	}
	return RBI_OK;
}
// -------------------------------------------------------------------------		
int Buffer::RingBufferPos::addIndex(unsigned int _iLenToAdd)
{
	if((_iLenToAdd<0)||((unsigned int)_iLenToAdd>m_ulLen))
	{
		return RBI_SIZE_BUFFER_TO_SMALL;
	}

	m_i64AbsN+= _iLenToAdd;
	m_ulPosN +=_iLenToAdd;
	if(m_ulPosN>=m_ulLen)
	{
		m_ulPosN -= m_ulLen;
	}

	return RBI_OK;
}
// -------------------------------------------------------------------------
int Buffer::RingBufferPos::subIndex(unsigned int _iLenToSub)
{
	if((_iLenToSub<0)||(_iLenToSub >m_ulLen))
	{
		return RBI_SIZE_BUFFER_TO_SMALL;
	}
	if(m_ulPosN < _iLenToSub)
	{
		return RBI_POS_NO_NEGATIVE;
	}

	m_i64AbsN-=_iLenToSub;
	m_ulPosN-=_iLenToSub;
	if(m_ulPosN<0)
	{
		m_ulPosN+=m_ulLen;
	}
	return RBI_OK;
}
// -------------------------------------------------------------------------
unsigned long Buffer::RingBufferPos::getNPosition()
{
	return m_ulPosN;
}
// -------------------------------------------------------------------------
unsigned long Buffer::RingBufferPos::getBufferLen()
{
	return m_ulLen;
}
// -------------------------------------------------------------------------

