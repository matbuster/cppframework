/**
 * \file 		ThreadPool.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#include "ThreadPool.h"
#include "ThreadInterface.h"
#include "ThreadPoolGarbagedItem.h"

// -----------------------------------------------------------------------------
/** main constructor of the class */
Threading::ThreadPool::ThreadPool()
{
	m_ulAbsoluteThreadCounter = 0;
	m_poolGarbaged = new std::list<Threading::ThreadPoolGarbagesItem*>();
	m_mutex = new Threading::Mutex();
	m_ulNumMinThread = 0;
	m_ulNumMaxThread = TP_MAX_THREAD_ALLOWED;
}
// -----------------------------------------------------------------------------
/** main destructor of the class */
Threading::ThreadPool::~ThreadPool()
{
	delete m_poolGarbaged;
	delete m_mutex;
}
// -----------------------------------------------------------------------------
/** getter of the number of thread in the pool */
int Threading::ThreadPool::getNumThread()
{
	int iNumTread = 0;
	if(m_mutex->WaitOne()) 
	{
		iNumTread = (int)m_poolGarbaged->size();
		m_mutex->Release();
	}
	return iNumTread;
}
// -----------------------------------------------------------------------------
unsigned long Threading::ThreadPool::getAbsoluteThreadCounter() 
{
	return m_ulAbsoluteThreadCounter;
}
// -----------------------------------------------------------------------------
unsigned long Threading::ThreadPool::getMinThread()
{
	return m_ulNumMinThread;
}
// -----------------------------------------------------------------------------
unsigned long Threading::ThreadPool::getMaxThread()
{
	return m_ulNumMaxThread;
}
// -----------------------------------------------------------------------------
void Threading::ThreadPool::setMinThread(unsigned long ulMinThread)
{
	m_ulNumMinThread = ulMinThread;
}
// -----------------------------------------------------------------------------
void Threading::ThreadPool::setMaxThread(unsigned long ulMaxThread)
{
	m_ulNumMaxThread = ulMaxThread;
}
// -----------------------------------------------------------------------------
Threading::ThreadPoolGarbagesItem * Threading::ThreadPool::getItem(int iIndexItem)
{
	int iCounter = 0;
	if(m_mutex->WaitOne())
	{
		for( std::list<Threading::ThreadPoolGarbagesItem*>::iterator it = m_poolGarbaged->begin(); it != m_poolGarbaged->end(); it++)
		{
			if(iIndexItem == iCounter) {
				Threading::ThreadPoolGarbagesItem * item = (*it);
				m_mutex->Release();
				return item;
			}
			iCounter++;
 		}
		m_mutex->Release();
	}
	return NULL;
}
// -----------------------------------------------------------------------------
long Threading::ThreadPool::DeleteThreadFromPool(int iThreadID)
{
	if(m_mutex->WaitOne())
	{
		for( std::list<Threading::ThreadPoolGarbagesItem*>::iterator it = m_poolGarbaged->begin(); it != m_poolGarbaged->end(); it++)
		{
			Threading::ThreadPoolGarbagesItem * item = *it;
			if(iThreadID == item->getThreadID())
			{
				delete item;
				m_poolGarbaged->remove(item);
				
				m_mutex->Release();
				return TP_OK;
			}
 		}
		m_mutex->Release();
	}
	return TP_OK;
}
// -----------------------------------------------------------------------------
long Threading::ThreadPool::AddThread(Threading::pfunc_threadpool_doWork lpStarRoutine)
{
	return AddThread(lpStarRoutine, NULL);
}
// -----------------------------------------------------------------------------
THREAD_RETURN_VOID THREAD_CALLCONV internalThreadPoolGarbageItemWorker(THREAD_INPUT_PARAM lpThreadParameter) 
{
	// get the Threadpool item
	Threading::ThreadPoolGarbagesItem * item = (Threading::ThreadPoolGarbagesItem*)lpThreadParameter;

	// calling thread callback
	if(NULL != item->getThreadEntrypoint())
	{
		item->setErrorCode(((Threading::pfunc_threadpool_doWork)(item->getThreadEntrypoint()))(item));
	}

	// manage return value
	item->ThreadStop();

	// garbage thread item, pool ...
	if(NULL != item->getParent())
	{
		Threading::ThreadPool * pool = (Threading::ThreadPool *)(item->getParent());
		pool->GarbagePool();
	}

	return THREAD_RETURN_VAL;
}
// -----------------------------------------------------------------------------
long Threading::ThreadPool::AddThread(Threading::pfunc_threadpool_doWork lPStarRoutine, void * pObject) 
{
	m_ulAbsoluteThreadCounter++;

	// initialize the pool item
	Threading::ThreadPoolGarbagesItem * item = new Threading::ThreadPoolGarbagesItem(this);
	item->setObject(pObject);
	item->setThreadEntrypoint(lPStarRoutine);

	// managed item and start the internal thread
	item->ThreadStart(internalThreadPoolGarbageItemWorker, (void*)item);
	if(m_mutex->WaitOne()) 
	{
		m_poolGarbaged->push_back(item);
		m_mutex->Release();
	}

	return TP_OK;
}
// -----------------------------------------------------------------------------
/** stop a target thread */
long Threading::ThreadPool::StopThreadFromPool(int iThreadID)
{
	if(m_mutex->WaitOne())
	{
		for( std::list<Threading::ThreadPoolGarbagesItem*>::iterator it = m_poolGarbaged->begin(); it != m_poolGarbaged->end(); it++)
		{
			Threading::ThreadPoolGarbagesItem * item = *it;
			if(iThreadID == item->getThreadID())
			{
				item->ThreadStop();
				m_mutex->Release();
			}
		}
		m_mutex->Release();
	}
	return TP_OK;
}
// -----------------------------------------------------------------------------
/** clear the thread pool */
long Threading::ThreadPool::ClearThreadPool()
{
	if(m_mutex->WaitOne()) 
	{	
		for(int i = 0; i< (int)m_poolGarbaged->size();i++) 
		{
			Threading::Thread * th = getItem(i);
			th->ThreadStop();
			delete th;
		}

		m_poolGarbaged->clear();
		m_mutex->Release();
	}
	return TP_OK;
}
// -----------------------------------------------------------------------------
/** garbage pool coolection */
long Threading::ThreadPool::GarbagePool()
{
	if(m_mutex->WaitOne()) 
	{
		for(int i = 0; i< (int)m_poolGarbaged->size();i++) 
		{
			Threading::Thread * th = getItem(i);
			if(NULL != th) 
			{
				if(!th->IsAlive())
				{
					// delete thread in the pool
					DeleteThreadFromPool(th->getThreadID());
				}
			}
		}
		m_mutex->Release();
	}
	return TP_OK;
}
// -----------------------------------------------------------------------------
/** wait all thread of pool closing */
long Threading::ThreadPool::WaitForSingleObject()
{
	bool bThreadRunning = true;
	while(true == bThreadRunning)
	{
		int iNumThreadStopped = 0;
		for(int i = 0; i< (int)m_poolGarbaged->size();i++) 
		{
			Threading::Thread * th = getItem(i);
			if(th->IsAlive())
			{
				bThreadRunning = true;
				break;
			}
			else
			{
				iNumThreadStopped++;
			}
		}

		if(iNumThreadStopped >= (int)m_poolGarbaged->size())
		{
			bThreadRunning = false;
		}
	}
	return TP_OK;
}
// -----------------------------------------------------------------------------
