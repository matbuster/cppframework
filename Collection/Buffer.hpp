#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>

namespace Collection {

	template <typename T>
	class Buffer {

	private:
		/**! buffer declaration*/
		T * m_pBuffer;

		/**! buffer len */
		long m_lBufferSize;

	public:
		/**! \brief constructor of Buffer class
		 * \param [in] _lSizeBuffer : target size of buffer
		 */
		Buffer(long _lSizeBuffer) 
		{
			m_pBuffer = (T*)malloc(_lSizeBuffer * sizeof(T));
			m_lBufferSize = _lSizeBuffer;
		}
		/**! \brief destructor of the class */
		~Buffer() 
		{
			free(m_pBuffer);
		}
		/**! getter on the buffer size
		* \return m_lBufferSize buffer size
		*/
		long getSize()
		{
			return m_lBufferSize;
		}
	};

};

#endif // BUFFER_H