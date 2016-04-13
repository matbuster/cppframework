#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "RingBufferIndex.h"
#include "Collection/Buffer.hpp"

namespace Buffer {

	template <typename T>
	class RingBuffer {

	private:
		/**! buffer declaration */
		Collection::Buffer<T> * m_ringBuffer;

		/**! index on ring buffer */
		Buffer::RingBufferIndex * m_index;

	public:
		/**! constructor and destructor of the class */
		RingBuffer(long _lSizeRingBuffer)
		{
			m_ringBuffer = new Collection::Buffer<T>(_lSizeRingBuffer);
			m_index = new Buffer::RingBufferIndex(_lSizeRingBuffer);
		}
		~RingBuffer()
		{
			delete m_ringBuffer;
			delete m_index;
		}

	};
};

#endif // RING_BUFFER_H