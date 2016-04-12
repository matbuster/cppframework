#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "RingBufferIndex.h"
#include "Collection/Buffer.hpp"

namespace Buffer {

	class RingBuffer {

	private:
		/**! ring buffer trailer
		 */
		Buffer::RingBufferIndex * m_rbiTrailer;
		/**! ring buffer reader
		 */
		Buffer::RingBufferIndex * m_rbiRead;
		/**! ring buffer writer
		 */
		Buffer::RingBufferIndex * m_rbiWrite;

		/**! buffer declaration */
		Collection::Buffer<double> * m_ringBuffer;

	public:
		RingBuffer(long _lSizeRingBuffer);
		~RingBuffer();
	};
};

#endif // RING_BUFFER_H