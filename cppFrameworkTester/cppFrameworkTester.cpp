// cppFrameworkTester.cpp : definit le point d'entree pour l'application console.
//
// --------------------------------------------------------------------
#ifdef WIN32
#include "stdafx.h"
#endif // WIN32

#ifdef LINUX
#include <stdio.h>
#include <stdlib.h>
#endif // LINUX

// --------------------------------------------------------------------
// define test plan
#define TEST_COLLECTIONS
#define TEST_MATH
#define TEST_CALLSTACKS
#define TEST_THREADING // bug de temps en temps
#define TEST_TIMING
#define TEST_MEMORY // ça aussi?
#define TEST_NETWORK
//#define TEST_NETWORK_HTTP // can't find testNetworkHttpRequest.h
#define TEST_FILEIO
#define TEST_BUFFER
#define TEST_HARDWARE
#define TEST_CRYPTO
#define TEST_SERIALIZATION
// --------------------------------------------------------------------
// tester collection include
#include "cppFrameworkTesterDefines.h"

#ifdef TEST_BUFFER
#include "tester/testBufferRingBufferIndex.h"
#endif // TEST_BUFFER

#ifdef TEST_COLLECTIONS
#include "tester/testCollectionList.h"
#include "tester/testCollectionHashmap.h"
#endif // TEST_COLLECTIONS

// callstack includes
#ifdef TEST_CALLSTACKS
#include "tester/testCallStacksBasemessage.h"
#include "tester/testCallstacksQueue.h"
#include "tester/testCallstacksAbsouteStack.h"
#endif // TEST_CALLSTACKS

#ifdef TEST_CRYPTO
#include "tester/testCryptoGeneric.h"
#endif // TEST_CRYPTO

#ifdef TEST_FILEIO
#include "tester/testFileIOFileIni.h"
#endif //TEST_FILEIO

#ifdef TEST_HARDWARE
#include "tester/testHardwareComputer.h"
#endif // TEST_HARDWARE

#ifdef TEST_THREADING
// threading includes
#include "tester/testThreadingMutex.h"
#include "tester/testThreadingThreadPool.h"
#endif // TEST_THREADING

// math includes
#ifdef TEST_MATH
#include "tester/testMathMatrix.h"
#endif // TEST_MATH

#ifdef TEST_MEMORY
#include "tester/testMemoryRam.h"
#endif // TEST_MEMORY

#ifdef TEST_NETWORK
#include "tester/testNetworkIpAdress.h"
#include "tester/testNetworkTcpClientServer.h"
#endif /** TEST_NETWORK */

#ifdef TEST_NETWORK_HTTP
#include "tester/testNetworkHttpRequest.h"
#endif /** TEST_NETWORK_HTTP */

#ifdef TEST_SERIALIZATION
#include "tester/testSerializationSerializeItem.h"
#include "tester/testSerializationTlvSerializer.h"
#endif /** TEST_SERIALIZATION */

#ifdef TEST_TIMING
#include "tester/testTimingChrono.h"
#endif // TEST_TIMING

// --------------------------------------------------------------------
#ifdef WIN32
// general includes for testing in main program
#include <Windows.h>
#include <string>
#include <assert.h>
#endif // WIN32

#include "TesterReport.h"


// --------------------------------------------------------------------
#ifdef LINUX
int main(int argc, char *argv[])
#endif //LINUX
#ifdef WIN32
int _tmain(int argc, _TCHAR* argv[])
#endif //WIN32
{
	Test::TesterReport::getInstance()->printHeader("Testing cpp framework");
	

#ifdef TEST_COLLECTIONS        
	// testing namespace Collection 
	Test::tester_collection_list();
	Test::tester_collection_hashmap();
#endif
        
#ifdef TEST_THREADING
	Test::tester_threading_mutex();
	Test::test_thread_pool();
#endif // TEST_THREADING
        
	// testing namespace Callstacks
#ifdef TEST_CALLSTACKS
	Test::tester_callstacks_base_message_full();
	Test::tester_callstacks_queue();
	Test::tester_callstacks_absolute_queue();
#endif // TEST_CALLSTACKS
        
#ifdef TEST_MATH	
	// testing namespace math
	Test::tester_math_matrix();
#endif // TEST_MATH
        
#ifdef TEST_TIMING
    Test::tester_timing_chrono();
#endif // TEST_TIMING

#ifdef TEST_MEMORY
	Test::tester_memory_ram();
#endif // TEST_MEMORY

#ifdef TEST_NETWORK
	Test::tester_network_ip_adress();
	Test::tester_network_tcp_client_server();
#endif // TEST_NETWORK

#ifdef TEST_NETWORK_HTTP
	Test::test_network_http_request();
#endif // TEST_NETWORK_HTTP
        
#ifdef TEST_FILEIO
	Test::tester_fileio_fileini();
#endif // TEST_FILEIO

#ifdef TEST_BUFFER
	Test::tester_buffer_ring_buffer_index();
#endif // TEST_BUFFER

#ifdef TEST_HARDWARE
	Test::tester_hardware_computer();
#endif // TEST_HARDWARE

#ifdef TEST_CRYPTO
	Test::tester_crypto();
#endif // TEST_CRYPTO

#ifdef TEST_SERIALIZATION
	Test::tester_serialization_serialize_item();
#endif // TEST_SERIALIZATION

	system("pause");
	return 0;
}
// --------------------------------------------------------------------

