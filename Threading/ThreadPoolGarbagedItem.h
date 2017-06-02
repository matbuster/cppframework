#ifndef THREADPOOL_GARBAGED_ITEM_H
#define THREADPOOL_GARBAGED_ITEM_H

// include from threading namespace
#include "ThreadPoolExcutionMode.h"
#include "Thread.h"
#include "../toolsconstant.h"

namespace Threading {

	/**! class to described an thrading object managed by the threadpool
	 */
	class ThreadPoolGarbagesItem : public Threading::Thread {

	private:
		/**! associated thread callback
		 */
		void * m_work;

		/**! pool parent pointer association
		 */
		void * m_poolParent;

		/**! associated thread name (max STR_TINY charset)
		 */
		char m_pThreadName[STR_TINY]; 

		/**! value of the error code returned by the thread routine
		 */
		long m_lErrorCode;

		/**! boolean to knwon if the pointer has been allocated
		 */
		bool m_bAllocated;

		/**! pointer on the associated object 
		 */
		void * m_pObject;

		/**! associated mode to the manage the thread in the pool
		 */
		Threading::ThreadPoolExecutionMode m_enMode;

	public:
		/**! constructor and desctructor
		 */
		ThreadPoolGarbagesItem(void * parent);
		virtual ~ThreadPoolGarbagesItem();

		/**! getter on the ThreadPool parent
		 * \return pointer value on the threadPool parent
		 */
		void * getParent();

		/**! getter on the object associated to thread item
		 * \return pointer on object associated to thread
		 */
		void * getObject();

		/**! setter on the object to pass to thread
		 */
		void setObject(void * pObject);

		/**! getter on the thread function entry point
		 * \return entry thread function callback
		 */
		void * getThreadEntrypoint();

		/**! setter on the thread function entry point
		 * \param [in] entry thread function callback
		 */
		void setThreadEntrypoint(void * entry);

		/**! getter on the thread routine error code
		 * \return error code
		 */
		long getErrorCode();

		/**! setter on the error code value
		 * \param [in] lvalue : error code value
		 */
		void setErrorCode(long lvalue);
	};
};

#endif // THREADPOOL_GARBAGED_ITEM_H