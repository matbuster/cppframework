/**
 * \file 		ThreadPool.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#include "ThreadPool.h"

/** main constructor of the class */
Threading::ThreadPool::ThreadPool()
{
	m_pool = new std::list<Threading::Thread*>();
	m_mutex = new Threading::Mutex();
}
/** main destructor of the class */
Threading::ThreadPool::~ThreadPool()
{
	delete m_pool;
	delete m_mutex;
}
/** getter of the number of thread in the pool */
int Threading::ThreadPool::getNumThread()
{
	int iNumTread = 0;
	if(m_mutex->WaitOne()) 
	{
		iNumTread = (int)m_pool->size();
		m_mutex->Release();
	}
	return iNumTread;
}
/** get thread item in the pool */
Threading::Thread * Threading::ThreadPool::getItem(int iIndexItem)
{
	int iCounter = 0;
	if(m_mutex->WaitOne())
	{
		for( std::list<Threading::Thread*>::iterator it = m_pool->begin(); it != m_pool->end(); it++)
		{
			if(iIndexItem == iCounter) {
				Threading::Thread * item = (*it);
				m_mutex->Release();
				return item;
			}
			iCounter++;
 		}
		m_mutex->Release();
	}
	return NULL;
}
/** delete the corresponding thread */
long Threading::ThreadPool::DeleteThreadFromPool(int iThreadID)
{
	if(m_mutex->WaitOne())
	{
		for( std::list<Threading::Thread*>::iterator it = m_pool->begin(); it != m_pool->end(); it++)
		{
			Threading::Thread * item = *it;
			if(iThreadID == item->getThreadID())
			{
				delete item;
				m_pool->remove(item);
				
				m_mutex->Release();
				return 0;
			}
 		}
		m_mutex->Release();
	}
	return 0;
}
/** add a new thread to the pool, according to the start routine */
long Threading::ThreadPool::AddThreadToPool(void* lpStartRoutine)
{
	return AddThreadToPool(lpStartRoutine, NULL);
}
/** add a new thread to the pool, according to the start routine */
long Threading::ThreadPool::AddThreadToPool(void* lpStartRoutine, void * pObject)
{
	Threading::Thread * thNew = new Threading::Thread();

	// initialize the pool item
	sPoolGarbagedItem * item = new sPoolGarbagedItem();
	item->th = thNew;
	item->pObject = pObject;

	thNew->ThreadStart(lpStartRoutine, (void*)item);
	
	if(m_mutex->WaitOne()) 
	{
		m_pool->push_back(thNew);
		m_mutex->Release();
	}
	return 0;
}
/** stop a target thread */
long Threading::ThreadPool::StopThreadFromPool(int iThreadID)
{
	if(m_mutex->WaitOne())
	{
		for( std::list<Threading::Thread*>::iterator it = m_pool->begin(); it != m_pool->end(); it++)
		{
			Threading::Thread * item = *it;
			if(iThreadID == item->getThreadID())
			{
				item->ThreadStop();
				m_mutex->Release();
			}
		}
		m_mutex->Release();
	}
	return 0;
}
/** clear the thread pool */
long Threading::ThreadPool::ClearThreadPool()
{
	if(m_mutex->WaitOne()) 
	{	
		for(int i = 0; i< (int)m_pool->size();i++) 
		{
			Threading::Thread * th = getItem(i);
			th->ThreadStop();
			delete th;
		}

		m_pool->clear();
		m_mutex->Release();
	}
	return 0;
}
/** garbage pool coolection */
long Threading::ThreadPool::GarbagePool()
{
	for(int i = 0; i< (int)m_pool->size();i++) 
	{
		Threading::Thread * th = getItem(i);
		if(!th->IsAlive())
		{
			// delete thread in the pool
			DeleteThreadFromPool(th->getThreadID());
		}
	}
	return 0;
}
/** wait all thread of pool closing */
long Threading::ThreadPool::WaitForSingleObject()
{
	bool bThreadRunning = true;
	while(true == bThreadRunning)
	{
		int iNumThreadStopped = 0;
		for(int i = 0; i< (int)m_pool->size();i++) 
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

		if(iNumThreadStopped >= (int)m_pool->size())
		{
			bThreadRunning = false;
		}
	}
	return 0;
}