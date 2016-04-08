/**
 * \file 		Mutex.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#ifndef MUTEX_H
#define MUTEX_H

#ifdef _WINDOWS
#include <windows.h>
#endif
#ifdef LINUX
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include "../Timing/Chrono.h"
#endif

namespace Threading
{
	class Mutex
	{
	private:
#ifdef _WINDOWS
		/** win handle on the mutex */
		HANDLE m_hMutex;
#endif
#ifdef LINUX
                pthread_mutex_t m_hMutex;
#endif
                
                /** internal lock release counter*/
                int m_iCounterLock_Unlock;    
            
	public:
		Mutex();
		~Mutex();
		/** get mutex  */
		bool WaitOne();
		/** wait with a timeout value expressed in milliseconds */
		bool WaitOne(int iTimeout);
		/** release mutex */
		bool Release();
	};
};

#endif /* MUTEX_H*/