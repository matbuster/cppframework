
#include "testBufferRingBufferIndex.h"
#include "Buffer/RingBuffer.hpp"

int tester_buffer_initialize_and_release()
{
	Buffer::RingBuffer<double> * _ringBuffer = new Buffer::RingBuffer<double>(1000);
	delete _ringBuffer;

	return 0;
}

int tester_buffer_ring_buffer_index() 
{
	tester_buffer_initialize_and_release();
	return 0;
}