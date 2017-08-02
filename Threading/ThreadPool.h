/**
 * \file 		ThreadPool.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "Thread.h"
#include "ThreadInterface.h"
#include "ThreadPoolGarbagedItem.h"
#include <list>

#define TP_OK					0
#define TP_KO					1
#define TP_INVALID_PARAM		2
#define TP_MIN_THREAD_REACHED	3
#define TP_MAX_THREAD_REACHED	4

// default value for max thread
#define TP_MAX_THREAD_ALLOWED	1000

namespace Threading
{
	/** class thread pool */
	class ThreadPool
	{
	private:
		/**! absolute counter of thread managed (created, used and destroyed) by the threadpool */
		unsigned long m_ulAbsoluteThreadCounter;

		/**! testing garbaged thread pool */ 
		std::list<Threading::ThreadPoolGarbagesItem*> * m_poolGarbaged;

		/**! get thread item in the pool */
		Threading::ThreadPoolGarbagesItem * getItem(int iIndexItem);

		/**! mutex for concurent protection */
		Threading::Mutex * m_mutex;

		/**! minimum of thread allowed in the pool */
		unsigned long m_ulNumMinThread;

		/**! maximum of thread allowed in the pool */
		unsigned long m_ulNumMaxThread;

	public:
		/** constructor and destructor */
		ThreadPool();
		~ThreadPool();
		
		// -----------------------------------------------------------------------------
		/**! getter on the total thread number 
		 * \return number of the current thread added in the pool
		 */
		int getNumThread();
		
		// -----------------------------------------------------------------------------
		/**! getter on the absolute counter of thread.
		 * Number thread created, used and destroyed in this pool since creation
		 * \return absolute counter of thread
		 */
		unsigned long getAbsoluteThreadCounter();

		// -----------------------------------------------------------------------------
		/**! getter on the minimum thread number
		 * \return minimum thread number
		 */
		unsigned long getMinThread();
		
		// -----------------------------------------------------------------------------
		/**! getter on the maximum thread number
		 * \return maximum thread number
		 */
		unsigned long getMaxThread();

		// -----------------------------------------------------------------------------
		/**! setter on the minimum thread number 
		 * \param [in] ulMinThread : minimum thread number
		 */
		void setMinThread(unsigned long ulMinThread);
		
		// -----------------------------------------------------------------------------
		/**! setter on the maximum thread number 
		 * \param [in] ulMaxThread : maximum thread number
		 */
		void setMaxThread(unsigned long ulMaxThread);

		// -----------------------------------------------------------------------------
		/** add a new start routine to the pool. This function create an internal Thread
		 * Object to add it to the pool. No object passed. 
		 * The thread is automatically started when added to pool. Garbage of item is 
		 * automatically done when the thread routine ends.
		 *
		 * \param [in] lpStartRoutine : adress of the start routine
		 * \return error code
		 */
		long AddThread(Threading::pfunc_threadpool_doWork lpStarRoutine);

		// -----------------------------------------------------------------------------
		/** add a new start routine to the pool. This function create an internal garbaged 
		 * Thread Object to add it to the pool. User can specify an object to pass to the 
		 * thread.  
		 * The thread is automatically started when added to pool. Garbage of item is 
		 * automatically done when the thread routine ends.
		 *
		 * \param [in] lpStarRoutine : adress of the start routine
		 * \param [in] pObject : object to pass to the thread
		 * \return error code
		 */
		long AddThread(Threading::pfunc_threadpool_doWork lpStarRoutine, void * pObject);
				
		// -----------------------------------------------------------------------------
		/** stop a target thread */
		long StopThreadFromPool(int iThreadID);
		
		// -----------------------------------------------------------------------------
		/** delete the corresponding thread */
		long DeleteThreadFromPool(int iThreadID);
		
		// -----------------------------------------------------------------------------
		/** clear the thread pool. Stop all the tread and delete them */
		long ClearThreadPool();
		
		// -----------------------------------------------------------------------------
		/** function to garbage pool collection 
		 * \return error code
		 */
		long GarbagePool();	

		// -----------------------------------------------------------------------------
		/** wait all thread of pool closing. This function is blocking while all thread
		 * are no finished.
		 * TODO MAT: reflection on override with the use of timeout for this function 
		 */
		long WaitForSingleObject();
	};
};

#endif /* THREAD_POOL_H */