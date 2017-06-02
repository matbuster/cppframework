#ifndef THREADING_THREAD_INTERFACE_H
#define THREADING_THREAD_INTERFACE_H

#include "ThreadPoolGarbagedItem.h"

namespace Threading {

	// -------------------------------------------------------------------------------
	/**! define doDork prototype for all thread manage by the threadpool 
	 * \param [in] item : garbaged item associated to a thread pool
	 * \return error code
	 */
	typedef long (*pfunc_threadpool_doWork)(Threading::ThreadPoolGarbagesItem * item);
	
};

#endif /** THREADING_THREAD_INTERFACE_H */