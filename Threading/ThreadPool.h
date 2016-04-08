/**
 * \file 		ThreadPool.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "Thread.h"
#include <list>

namespace Threading
{
	/** internal thread pool callback for each thread.
	  * ensure to delete to the pool the current thread */
	typedef struct 
	{
		Threading::Thread * th;
		void * pObject;
	  
	} sPoolGarbagedItem;

	/** class thread pool */
	class ThreadPool
	{
	private:
		/** thread pool */ 
		std::list<Threading::Thread*> * m_pool;

		/** get thread item in the pool */
		Threading::Thread * getItem(int iIndexItem);

		/** mutex for concurent protection */
		Threading::Mutex * m_mutex;

	public:
		/** constructor and destructor */
		ThreadPool();
		~ThreadPool();
		
		/** getter on the total thread number */
		int getNumThread();

		/** add a new thread to the pool, according to the start routine. No object passed */
		long AddThreadToPool(void* lpStartRoutine);

		/** add a new thread to the pool, according to the start routine. Passed an object */
		long AddThreadToPool(void* lpStartRoutine, void * pObject);

		/** stop a target thread */
		long StopThreadFromPool(int iThreadID);

		/** delete the corresponding thread */
		long DeleteThreadFromPool(int iThreadID);

		/** clear the thread pool. Stop all the tread and delete them */
		long ClearThreadPool();

		/** garbage pool coolection */
		long GarbagePool();	

		/** wait all thread of pool closing. This function is blocking while all thread
		 * are no finished.
		 * TODO MAT: reflection on override with the use of timeout for this function 
		 */
		long WaitForSingleObject();
	};
};

#endif /* THREAD_POOL_H */