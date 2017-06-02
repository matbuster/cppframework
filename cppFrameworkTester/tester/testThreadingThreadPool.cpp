
#include "testThreadingThreadPool.h"
#include "cppFrameworkTesterDefines.h"

#include "TesterReport.h"

// includes debug framework
#include "Diagnostic/console.h"
#include "Threading/Thread.h"
#include "Threading/Threadpool.h"
#include "Timing/Chrono.h"
#include "Timing/Timing.h"
#include "Math/Math.h"

#include <stdio.h>

#define TEST_PRIME_NUMBER			17456897

// --------------------------------------------------------
// Function calculation
bool IsPrimeInRange(long number, long start, long end)
{
    for (long i = Math::Max(start, 2); i < end; i = ++i)
    {              
        if (number % i == 0L)
        {
            return false;
        }
    }

    return true;
}
// --------------------------------------------------------
bool IsPrime(long number)
{
	return IsPrimeInRange(number, 2, number);
}
// --------------------------------------------------------
long garbagedThreadRoutine(Threading::ThreadPoolGarbagesItem * item)
{
	int iIdThread = (int)(*((int*)(item->getObject()))); 

	// calling a function to do something
	printf(">[Thread][Id=%d] : calculate Prime Number %d\r\n", iIdThread, TEST_PRIME_NUMBER);

	Timing::Chrono * measureTime = new Timing::Chrono();
	measureTime->startChrono();

	IsPrime(TEST_PRIME_NUMBER);
	printf(">[Thread][Id=%d] : calculation time %.03f ms\r\n",iIdThread,  measureTime->getTime_ms());

	delete measureTime;
	return 0;
}
// -------------------------------------------------
int Test::test_single_thread_in_pool_auto_garbaged()
{
	int iCounterThread = 1;
	Threading::ThreadPool * pool = new Threading::ThreadPool();
	pool->AddThread(garbagedThreadRoutine, (void*)(&iCounterThread) );

	int iNumThread = pool->getNumThread();
	if(iNumThread <= 0)
	{
		printf(">test_single_thread_in_pool_auto_garbaged : Number thread in threadpool in WRONG\r\n");
		delete pool;
		return TEST_KO;
	}

	// wait end of execution
	do {
		Timing::Timing::sleepInMilliSecond(10);
	} while(pool->getNumThread() > 0);

	delete pool;
	return TEST_OK;
}
// --------------------------------------------------------
int Test::test_multiple_thread_in_pool_auto_garbaged() 
{
	// create multiple thread in pool
	Threading::ThreadPool * pool = new Threading::ThreadPool();
	for(int i = 0; i < TEST_MAX_THREAD_IN_POOL; i++)
	{
		pool->AddThread(garbagedThreadRoutine, (void*)(&i));
	}

	int iNumThread = pool->getAbsoluteThreadCounter();
	if(iNumThread != TEST_MAX_THREAD_IN_POOL)
	{
		printf(">test_multiple_thread_in_pool_auto_garbaged : Number thread in threadpool in WRONG\r\n");
		delete pool;
		return TEST_KO;
	}

	// garbage pool
	do {
		Timing::Timing::sleepInMilliSecond(10);
	} while(pool->getNumThread() > 0);

	delete pool;
	return TEST_OK;
}
// --------------------------------------------------------
int Test::test_thread_pool()
{
    int iReturnCode = TEST_OK;
    Test::TesterReport::getInstance()->printHeader("testing Threading::Threadpool");
    

	iReturnCode = test_single_thread_in_pool_auto_garbaged();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Threading::Pool", "test_single_thread_in_pool_auto_garbaged()");
	iReturnCode = test_multiple_thread_in_pool_auto_garbaged();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Threading::Pool", "test_multiple_thread_in_pool_auto_garbaged()");

	return iReturnCode;
}
// --------------------------------------------------------