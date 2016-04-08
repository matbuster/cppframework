/**
 * \file 		Thread.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#include "Thread.h"

#ifdef LINUX
static long g_lAbsoluteThreadID = 0;

long getThreadID() {
    return g_lAbsoluteThreadID++;
}
#endif //LINUX

/** main constructor of the class*/
Threading::Thread::Thread() {
    m_hThread = 0;
    m_lpStartAddress = 0;
    m_IDThread = 0;
    m_bRunning = false;
    m_bCancel = false;
    m_mutex = new Threading::Mutex();
}

/** destructor of the class */
Threading::Thread::~Thread() {
    m_bCancel = true;
}

/** setter on running variable, return value if success or not. THREAD SAFE */
bool Threading::Thread::setRunning(bool bValue) {
    if (m_mutex->WaitOne()) {
        m_bRunning = bValue;
        m_mutex->Release();
        return true;
    } else return false;
}

/** getter of internal value bRunning, THREAD SAFE */
bool Threading::Thread::getRunning(bool * bValue) {
    if (m_mutex->WaitOne()) {
        *bValue = m_bRunning;
        m_mutex->Release();
        return true;
    } else return false;
}

/** getter and setter on cancel variable, return value if success or not. THREAD SAFE */
bool Threading::Thread::setCancel(bool bValue) {
    if (m_mutex->WaitOne()) {
        m_bCancel = bValue;
        m_mutex->Release();
        return true;
    } else return false;
}

/** getter of internal value cancel, THREAD SAFE */
bool Threading::Thread::getCancel(bool * bValue) {
    if (m_mutex->WaitOne()) {
        *bValue = m_bCancel;
        m_mutex->Release();
        return true;
    } else return false;
}

/** getter on the thread id member */
int Threading::Thread::getThreadID() {
    return m_IDThread;
}

/** status of the thread, is running or not */
bool Threading::Thread::IsRunning() {
    bool bIsRunning = false;
    getRunning(&bIsRunning);
    return bIsRunning;
}

/** status to know if thread is alive, bRunning = true && bCancel = false  && idThread > 0 */
bool Threading::Thread::IsAlive() {
    bool bIsCancelled = false;
    bool bIsRunning = false;

    getCancel(&bIsCancelled);
    getRunning(&bIsRunning);

    if (bIsRunning == true && m_IDThread >= 0) {
        return true;
    } else return false;
}

/** starting a new thread with start routine adress */
long Threading::Thread::ThreadStart(void* lpStartAddress) {
    return Threading::Thread::ThreadStart(lpStartAddress, NULL);
}

/** starting a new thread with start routine adress, want to pass an object */
long Threading::Thread::ThreadStart(void* lpStartAddress, void * pObject) {
#ifdef _WINDOWS
    DWORD dwIDThread = 0;
    m_hThread = CreateThread(NULL, //no security attributes
            0, //use default stack size
            (LPTHREAD_START_ROUTINE) lpStartAddress, //start procedure
            (LPVOID) pObject, //parameter to thread function
            CREATE_SUSPENDED, //creation flag
            &dwIDThread); // returns thread ID

    if (m_hThread) {
        ResumeThread(m_hThread);
    } else {
        return THREAD_START_FAILED;
    }
    m_IDThread = dwIDThread;
    m_lpStartAddress = lpStartAddress;
#endif
#ifdef LINUX
    int iReturn = pthread_create(&m_hThread, NULL, (pfunc_start_routine) lpStartAddress, pObject);
    if (0 != iReturn) {
        return THREAD_START_FAILED;
    }
    m_lpStartAddress = lpStartAddress;
    m_IDThread = getThreadID();
#endif
    setRunning(true);
    m_bCancel = false;
    return THREAD_SUCCESS;
}

/** try to stop a thread, passing all the runnig flag to false */
long Threading::Thread::ThreadStop() {
    m_bCancel = false;
#ifdef _WINDOWS
    CloseHandle(m_hThread);
#endif
#ifdef LINUX
    pthread_cancel(m_hThread);
#endif
    m_hThread = 0;
    setRunning(false);

    return THREAD_SUCCESS;
}

/** function to close and kill a thread */
long Threading::Thread::KillThread() {
    m_bCancel = false;
#ifdef _WINDOWS
    TerminateThread(m_hThread, 0);
    CloseHandle(m_hThread);

    WaitForSingleObject(m_hThread, INFINITE);
#endif
#ifdef LINUX
    pthread_kill(m_hThread, 0);
    pthread_cancel(m_hThread);
#endif
    setRunning(false);
    return THREAD_SUCCESS;
}
