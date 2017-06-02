
// include from threading namespace
#include "ThreadPoolGarbagedItem.h"
#include <string.h>

// ----------------------------------------------------------------
Threading::ThreadPoolGarbagesItem::ThreadPoolGarbagesItem(void * parent)
	: Threading::Thread()
{
	m_bAllocated = false;
	m_enMode = Threading::ExecuteImmediate;
	memset(m_pThreadName, 0x00, STR_TINY);
	m_work = NULL;
	m_poolParent = parent;
	m_lErrorCode = 0;
}
// ----------------------------------------------------------------
Threading::ThreadPoolGarbagesItem::~ThreadPoolGarbagesItem()
{
}
// ----------------------------------------------------------------
void * Threading::ThreadPoolGarbagesItem::getParent()
{
	return m_poolParent;
}
// ----------------------------------------------------------------
void * Threading::ThreadPoolGarbagesItem::getObject()
{
	return m_pObject;
}
// ----------------------------------------------------------------
void Threading::ThreadPoolGarbagesItem::setObject(void * pObject)
{
	m_pObject = pObject;
}
// ----------------------------------------------------------------
void * Threading::ThreadPoolGarbagesItem::getThreadEntrypoint()
{
	return m_work;
}
// ----------------------------------------------------------------
void Threading::ThreadPoolGarbagesItem::setThreadEntrypoint(void * entry)
{
	m_work = entry;
}
// ----------------------------------------------------------------
long Threading::ThreadPoolGarbagesItem::getErrorCode()
{
	return m_lErrorCode;
}
// ----------------------------------------------------------------
void Threading::ThreadPoolGarbagesItem::setErrorCode(long lvalue)
{
	m_lErrorCode = lvalue;
}
// ----------------------------------------------------------------

