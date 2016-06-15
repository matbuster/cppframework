#ifndef _RING_BUFFER_INDEX_H_
#define _RING_BUFFER_INDEX_H_

#include "RingBufferPos.h"

namespace Buffer {

	class RingBufferIndex {

	private:
		/**! ring buffer trailer
		 */
		Buffer::RingBufferPos * m_rbiTrailer;
		/**! ring buffer reader
		 */
		Buffer::RingBufferPos * m_rbiRead;
		/**! ring buffer writer
		 */
		Buffer::RingBufferPos * m_rbiWrite;

	public:
		RingBufferIndex(unsigned long _ulSizeBuffer);
		~RingBufferIndex();

		/*! calculate the next position in the ring buffer
		 * \param [out] _allowedLenghtTillEnd: allowed aera where it's allowed to copy data between the last pos secure and the end of buffer
		 * \param [out] _allowedFromBeginning : allowed aera where it's allowed to write between the begining of buffer and the next ptotected zone
		 */
		int CalculePosition(int * _allowedLenghtTillEnd, int * _allowedFromBeginning);
	};
};

#endif // _RING_BUFFER_INDEX_H_