#ifndef THREADPOOL_EXECUTION_MODE_H
#define THREADPOOL_EXECUTION_MODE_H

namespace Threading
{
	/**! enumeration associated to the thread pool.
	 * This enumeration describe how execution by the treadpool
	 * has to work.
	 */
	enum ThreadPoolExecutionMode {
		
		/**! execute immediatly the thread when added to pool 
		 */
		ExecuteImmediate,
		/**! execute differs after a timing period
		 */
		ExecuteDiffersTiming,
		/**! execute when af condition has been success
		 */
		ExecuteDiffersCondition,
		/**! wait a start command from thread pool to execute all
		 * the thread at the same time
		 */
		ExecuteWaitStartCommand
	};
};

#endif // THREADPOOL_EXECUTION_MODE_H