#ifndef TESTER_THREADING_THREADPOOL_H
#define TESTER_THREADING_THREADPOOL_H

#ifdef _WINDOWS
#define THREAD_CALLCONV         WINAPI
#define THREAD_RETURN_VOID      void
#define THREAD_INPUT_PARAM      LPVOID
#define THREAD_RETURN_VAL
#endif // _WINDOWS

#ifdef LINUX
#define THREAD_CALLCONV
#define THREAD_RETURN_VOID      void*
#define THREAD_INPUT_PARAM      void*
#define THREAD_RETURN_VAL       NULL	
#endif

#define TEST_MAX_THREAD_IN_POOL			1000

namespace Test {

	// -------------------------------------------------
	/**! function to test and add one thread to the pool 
	 * \return SUCCESS or FAILED
	 */
	int test_single_thread_in_pool_auto_garbaged();

	// -------------------------------------------------
	/**! function to test and add multiple thread in the pool
	 * \return SUCCESS or FAILED
	 */
	int test_multiple_thread_in_pool_auto_garbaged();

	// -------------------------------------------------
	/**! generic functiono to clas all tester functions
	 * \return SUCCESS if function pass all test FAILED if one test failed
	 */
	int test_thread_pool();
};

#endif /** TESTER_THREADING_THREADPOOL_H */