
#include "RingBufferPos.h"

// -------------------------------------------------------------------------
Buffer::RingBufferPos::RingBufferPos(long _lLenBuffer) 
{
	m_i64AbsN = 0;
	m_lPosN = 0;
	m_lLen = _lLenBuffer;
}
Buffer::RingBufferPos::~RingBufferPos() 
{
}
// -------------------------------------------------------------------------
int Buffer::RingBufferPos::incrementIndex()
{
	m_i64AbsN++;
	m_lPosN++; 
	if((m_lPosN)>m_lLen-1)
	{
		m_lPosN-=m_lLen;
	}
	return RBI_OK;
}
// -------------------------------------------------------------------------
int Buffer::RingBufferPos::decrementIndex()
{
	m_i64AbsN--;
	m_lPosN--;
	if((m_lPosN)<0)
	{
		m_lPosN+=m_lLen;
	}
	return RBI_OK;
}
// -------------------------------------------------------------------------		
int Buffer::RingBufferPos::addIndex(int _iLenToAdd)
{
	if((_iLenToAdd<0)||(_iLenToAdd>m_lLen))
	{
		return RBI_SIZE_BUFFER_TO_SMALL;
	}

	m_i64AbsN+= _iLenToAdd;
	m_lPosN +=_iLenToAdd;
	if(m_lPosN>=m_lLen)
	{
		m_lPosN -= m_lLen;
	}

	return RBI_OK;
}
// -------------------------------------------------------------------------
int Buffer::RingBufferPos::subIndex(int _iLenToSub)
{
	if((_iLenToSub<0)||(_iLenToSub >m_lLen))
	{
		return RBI_SIZE_BUFFER_TO_SMALL;
	}

	m_i64AbsN-=_iLenToSub;
	m_lPosN-=_iLenToSub;
	if(m_lPosN<0)
	{
		m_lPosN+=m_lLen;
	}
	return RBI_OK;
}
// -------------------------------------------------------------------------
long Buffer::RingBufferPos::getNPosition()
{
	return m_lPosN;
}
// -------------------------------------------------------------------------
long Buffer::RingBufferPos::getBufferLen()
{
	return m_lLen;
}
// -------------------------------------------------------------------------

