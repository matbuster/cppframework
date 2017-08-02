
#include "testThreadingMutex.h"
#include "cppFrameworkTesterDefines.h"
#include "TesterReport.h"

// include framework tools
#include "Threading/Mutex.h"
#include "Threading/Thread.h"

// debug tools
#include "Diagnostic/assertion.h"

#include <stdio.h>

#define MAX_LOOP_CONTER         10000

typedef struct {
    
    Threading::Mutex * mutex;
    int iSharedCounter;
    
} THREADING_STRUCT;

// ----------------------------------------------------------
int tester_loop_something(THREADING_STRUCT * structShared) {
    
    while(structShared->iSharedCounter < MAX_LOOP_CONTER) {
        
        if(structShared->mutex->WaitOne()) {
            structShared->iSharedCounter++;
            structShared->mutex->Release();
        }
    }
    return TEST_OK;
}
// ----------------------------------------------------------
#ifdef LINUX
int background_work_for_tester_one_mutex_threading_lock(int lpThreadParameter)
#endif //LINUX
#ifdef WIN32
DWORD WINAPI background_work_for_tester_one_mutex_threading_lock(LPVOID lpThreadParameter)
#endif //WIN32
{
    THREADING_STRUCT * structShared = (THREADING_STRUCT*)(lpThreadParameter);
    tester_loop_something(structShared);

    return TEST_OK;
}
// ----------------------------------------------------------

int Test::tester_one_mutex_no_timeout() {
    
    int iReturnCode = TEST_OK;
    
    Threading::Mutex * mutex = new Threading::Mutex();
    if(mutex->WaitOne()) {
       
        if(false == mutex->Release()) {
            Diagnostic::Assert(false,"Release mutex failed in function : tester_one_mutex_no_timeout()");
        }
    } else {
        Diagnostic::Assert(false,"WaitOne mutex failed in function : tester_one_mutex_no_timeout()");
    }
    delete mutex;
    
    return iReturnCode;
}
// ----------------------------------------------------------
int Test::tester_one_mutex_with_timeout() {

    int iReturnCode = TEST_OK;
    
    Threading::Mutex * mutex = new Threading::Mutex();
    if(mutex->WaitOne(100)) {
       
        if(false == mutex->Release()) {
            Diagnostic::Assert(false,"Release mutex failed in function : tester_one_mutex_with_timeout()");
        }
    } else {
        Diagnostic::Assert(false,"WaitOne mutex failed in function, or timeout reached : tester_one_mutex_with_timeout()");
    }
    delete mutex;
    
    return iReturnCode;    
}
// ----------------------------------------------------------
int Test::tester_one_mutex_threading_lock() {

    int iReturnCode = TEST_OK;    
    THREADING_STRUCT structShared;

    printf("[tester_one_mutex_threading_lock]\tEnterring tester_one_mutex_threading_lock\n");
    
    structShared.iSharedCounter = 0;
    structShared.mutex = new Threading::Mutex();
    Threading::Thread * thread = new Threading::Thread();
    
    thread->ThreadStart((void*)background_work_for_tester_one_mutex_threading_lock, (void*)(&structShared));
    
    bool loop = true;
    while(loop) {
        
        int iCounterValue = 0;
        if(structShared.mutex->WaitOne()) {
            iCounterValue = structShared.iSharedCounter;
            structShared.mutex->Release();
        }
        
        printf("[tester_one_mutex_threading_lock]\tThreading Counter value : %d\n", iCounterValue);
        if(iCounterValue >= MAX_LOOP_CONTER) {
            loop = false;
        }
    }
    
    delete thread;
    delete structShared.mutex;
    
    printf("[tester_one_mutex_threading_lock]\tExit tester_one_mutex_threading_lock\n");
    return iReturnCode;
}
// ----------------------------------------------------------

int Test::tester_threading_mutex() {
    
    Test::TesterReport::getInstance()->printHeader("testing Threading::Mutex");
    
    int iReturnCode = TEST_OK;

    iReturnCode = tester_one_mutex_no_timeout();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Threading::Mutex", "tester_one_mutex_no_timeout()");
    if (TEST_OK != iReturnCode) {
        return TEST_KO;
    }
	iReturnCode = tester_one_mutex_with_timeout();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Threading::Mutex", "tester_one_mutex_with_timeout()");
    if (TEST_OK != iReturnCode) {
        return TEST_KO;
    }   
	iReturnCode = tester_one_mutex_threading_lock();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Threading::Mutex", "tester_one_mutex_threading_lock()");
    if (TEST_OK != iReturnCode) {
        return TEST_KO;
    }       
    return iReturnCode;
}
// ----------------------------------------------------------