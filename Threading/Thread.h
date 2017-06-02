/**
 * \file 		Thread.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef THREAD_H
#define THREAD_H

#define THREAD_SUCCESS			0
#define THREAD_START_FAILED		1

#include "Mutex.h"

#ifdef _WINDOWS
#define PLATFORM_CAST_STR
#define THREAD_CALLCONV         WINAPI
#define THREAD_RETURN_VOID      void
#define THREAD_INPUT_PARAM      LPVOID
#define THREAD_RETURN_VAL
#endif // _WINDOWS

#ifdef LINUX
#define PLATFORM_CAST_STR       (char*)
#define THREAD_CALLCONV
#define THREAD_RETURN_VOID      void*
#define THREAD_INPUT_PARAM      void*
#define THREAD_RETURN_VAL       NULL
#endif

#ifdef LINUX
#include <signal.h>             // needed in definition of pthread_kill()
#include <pthread.h>
typedef void *(*pfunc_start_routine)(void *);
#endif

namespace Threading {
	
	class Thread {
	private:
#ifdef _WINDOWS
		/** handle thread */
		HANDLE m_hThread;
#endif
#ifdef LINUX
                /** handle pthread */
                pthread_t m_hThread;
#endif
		/** thrad callback routine */
		void* m_lpStartAddress;

		/** Unique ID thread */
		int m_IDThread;

		/** state of thread, running or not */
		bool m_bRunning;

		/** request for cancelling thread */
		bool m_bCancel;

		/** mutex for all concurencing operation */
		Threading::Mutex * m_mutex; 

	protected:
		/** getter and setter on running variable, return value if success or not */
		bool setRunning(bool bValue);
		bool getRunning(bool * bValue);
		/** getter and setter on running variable, return value if success or not */
		bool setCancel(bool bValue);
		bool getCancel(bool * bValue);
	public:
		/** main constructor and destructor of the class */
		Thread();
		~Thread();

		/** getter on the thread id member */
		int getThreadID();

		/** starting a new thread with start routine adress */
		long ThreadStart(void* lpStartAddress);

		/** starting a new thread with start routine adress, passing an object */
		long ThreadStart(void* lpStartAddress, void * pObject);

		/** try to stop a thread, passing all the runnig flag to false */
		long ThreadStop();

		/** function to close and kill a thread */
		long KillThread();

		/** status of the thread, is running or not */
		bool IsRunning();

		/** status to know if thread is alive, bRunning = true && bCancel = false  && idThread > 0 */
		bool IsAlive();
	};
};

#endif /* THREAD_H */