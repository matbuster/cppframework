/**
 * \file 		Mutex.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
#include "Mutex.h"
#include "ErnoBaseTranslator.h"
#include <stdio.h>

/** main constructor of the class,
 * initialized an not owned mutex */
Threading::Mutex::Mutex()
{
#ifdef _WINDOWS
    m_hMutex = CreateMutex( 
        NULL,              // default security attributes
        FALSE,             // initially not owned
        NULL);             // unnamed mutex
#endif
#ifdef LINUX
     pthread_mutex_init(&m_hMutex, NULL);
#endif
     m_iCounterLock_Unlock=0;
}
/** destructor of the class */
Threading::Mutex::~Mutex()
{
#ifdef _WINDOWS
	CloseHandle(m_hMutex);
#endif 
#ifdef LINUX
        pthread_mutex_destroy(&m_hMutex);
#endif
}

/** wait infinitely to get mutex */
bool Threading::Mutex::WaitOne()
{
#ifdef _WINDOWS
    int iWaitResult = WaitForSingleObject( 
        m_hMutex,    // handle to mutex
        INFINITE);  // no time-out interval
        
	switch (iWaitResult) 
    {
        // The thread got ownership of the mutex
        case WAIT_OBJECT_0: 
            return true;
        // The thread got ownership of an abandoned mutex
        case WAIT_ABANDONED: 
            return false; 
        // grabbing mutex failed
        case WAIT_FAILED: 
            return false; 
    }

        m_iCounterLock_Unlock++;
	return true;
#endif
#ifdef LINUX
    bool bRetValue = true;
    int iWaitResult = pthread_mutex_lock(&m_hMutex);
    switch(iWaitResult)
    {
        case EINVAL: 
        {
            bRetValue = false;
            break;
        }
        case EDEADLK:
        {
            bRetValue = false;
            break;
        }
        case ENOTRECOVERABLE:
        {
            bRetValue = false;
            break;
        }
        case EOWNERDEAD:
        {
            bRetValue = false;
            break;
        }
        default:
        {
            m_iCounterLock_Unlock++;
            bRetValue = true;
            break;
        }
    }
    return bRetValue;
#endif
}
/** wait with a timeout value expressed in milliseconds */
bool Threading::Mutex::WaitOne(int iTimeout)
{
    
#ifdef _WINDOWS
    int iWaitResult = WaitForSingleObject( 
        m_hMutex,    // handle to mutex
        iTimeout);  // no time-out interval
        
	switch (iWaitResult) 
    {
        // The thread got ownership of the mutex
        case WAIT_OBJECT_0: 
            return true;
        // The wait operation generate a timeout according to the define value
        case WAIT_TIMEOUT: 
            return false; 
        // The thread got ownership of an abandoned mutex
        case WAIT_ABANDONED: 
            return false; 
        // grabbing mutex failed
        case WAIT_FAILED: 
            return false; 
    }

        m_iCounterLock_Unlock++;
	return true;
#endif
#ifdef LINUX
    long timestart = Timing::Chrono::getAbsoluteTime_ms();
    while (pthread_mutex_trylock(&m_hMutex) == 0)
    {
        long timecurrent = Timing::Chrono::getAbsoluteTime_ms();
        long timeellapsed = timestart - timecurrent;
        if(timeellapsed >= iTimeout)
        {
            return false;
        }
    }
    m_iCounterLock_Unlock++;
    return true;
#endif        
}
/** release current mutex */
bool Threading::Mutex::Release()
{
#ifdef _WINDOWS
    if (! ReleaseMutex(m_hMutex)) 
    { 
		// can handle error with GetLastError
        return false;
    } 
    m_iCounterLock_Unlock--;
	return true;
#endif
#ifdef LINUX
    int iWaitResult = pthread_mutex_unlock(&m_hMutex);
    bool bRetValue = true;
    switch(iWaitResult)
    {
        case EINVAL:
        {
            bRetValue = false;
            break;
        }
        case EPERM:
        {
            bRetValue = false;
            break;
        }
        default:
        {
            m_iCounterLock_Unlock--;
            bRetValue = true;
            break;            
        }
    }
    return bRetValue;        
#endif        
}