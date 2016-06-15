#ifndef RING_BUFFER_POS_H
#define RING_BUFFER_POS_H

#define RBI_OK						0
#define RBI_KO						1
#define RBI_SIZE_BUFFER_TO_SMALL	2
#define RBI_WRONG_INDEX_CFG			3
#define RBI_POS_NO_NEGATIVE			4


namespace Buffer {

	class RingBufferPos {
	
	private:
		/** absolute position in octets (num of octet acquired since the start of acquisition)
		 */
		__int64 m_i64AbsN;
		/** Position in the current circular buffer in octets (offset in circular buffer)
		 */
		unsigned long m_ulPosN;
		/** Length of the circular buffer
		 */
		unsigned long m_ulLen;

	public:
		/** constructor and destroctor of class RingBufferIndex */
		RingBufferPos(unsigned long _lLenBuffer);
		~RingBufferPos();
		/**!
		 * \brief increment the position of ring buffer index
		 * \return error code
		 */
		int incrementIndex();
		/**!
		 * \brief decrement the position of ring buffer index
		 * \return error code
		 */
		int decrementIndex();
		/**!
		 * \brief add to the ring buffer index a specific length to the buffer
		 * \param [in] _iLenToAdd: targte length to add to the buffer
		 * \return error code
		 */
		int addIndex(unsigned int _iLenToAdd);
		/**!
		 * \brief sub to the ring buffer index a specific length to the buffer
		 * \param [in] _iLenToAdd: targte length to add to the buffer
		 * \return error code
		 */
		int subIndex(unsigned int _iLenToSub);

		/**! getter on the Current Position of the ring buffer index
		 * \return current position of the circular index
		 */
		unsigned long getNPosition();

		/**! getter on the buffer length
		 * \return the length of target buffer
		 */
		unsigned long getBufferLen();
	};
};

#endif // RING_BUFFER_INDEX_H

