// cppFrameworkTester.cpp�: d�finit le point d'entr�e pour l'application console.
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
//efine TEST_COLLECTIONS
//efine TEST_MATH
//efine TEST_CALLSTACKS
//efine TEST_THREADING
//efine TEST_TIMING
//efine TEST_MEMORY
#define TEST_FILEIO
#define TEST_BUFFER
// --------------------------------------------------------------------
// tester collection include
#include "cppFrameworkTesterDefines.h"
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

#ifdef TEST_TIMING
// threading includes
#include "tester/testThreadingMutex.h"
#endif // TEST_TIMING

// math includes
#ifdef TEST_MATH
#include "tester/testMathMatrix.h"
#endif // TEST_MATH

#ifdef TEST_TIMING
#include "tester/testTimingChrono.h"
#endif // TEST_TIMING

#ifdef TEST_MEMORY
#include "tester/testMemoryRam.h"
#endif // TEST_MEMORY

#ifdef TEST_FILEIO
#include "tester/testFileIOFileIni.h"
#endif //TEST_FILEIO

#ifdef TEST_BUFFER
#include "tester/testBufferRingBufferIndex.h"
#endif // TEST_BUFFER

// --------------------------------------------------------------------
#ifdef WIN32
// general includes for testing in main program
#include <Windows.h>
#include <string>
#include <assert.h>
#endif // WIN32

// --------------------------------------------------------------------
void printHeader(const char * pMessage)
{
	printf(STR_LINE_DISPLAY_SEP);
	printf("%s\r\n", pMessage);
	printf(STR_LINE_DISPLAY_SEP);
	printf(STR_LINE_JUMP);
}
// --------------------------------------------------------------------
void printSummary(bool bCondition, const char * pName, const char * pFunction)
{
	// test summarry
	if(true == bCondition)
	{
		printf("[%s]\t%s\tSUCCESS.\r\n", pName, pFunction);
	}
	else
	{
		printf("[%s]\t%s\tFAILED !!!\r\n", pName, pFunction);
	}
}
// --------------------------------------------------------------------
#ifdef LINUX
int main(int argc, char *argv[])
#endif //LINUX
#ifdef WIN32
int _tmain(int argc, _TCHAR* argv[])
#endif //WIN32
{
	printHeader("Testing cpp framework");

#ifdef TEST_COLLECTIONS        
	// testing namespace Collection 
	tester_collection_list();
	tester_collection_hashmap();
#endif
        
#ifdef TEST_THREADING
        tester_threading_mutex();
#endif // TEST_THREADING
        
	// testing namespace Callstacks
#ifdef TEST_CALLSTACKS
	tester_callstacks_base_message_full();
	tester_callstacks_queue();
	tester_callstacks_absolute_queue();
#endif // TEST_CALLSTACKS
        
#ifdef TEST_MATH	
	// testing namespace math
	tester_math_matrix();
#endif // TEST_MATH
        
#ifdef TEST_TIMING
        tester_timing_chrono();
#endif // TEST_TIMING

#ifdef TEST_MEMORY
		tester_memory_ram();
#endif // TEST_MEMORY
        
#ifdef TEST_FILEIO
		tester_fileio_fileini();
#endif // TEST_FILEIO

#ifdef TEST_BUFFER
		tester_buffer_ring_buffer_index();
#endif // TEST_BUFFER

	system("pause");
	return 0;
}
// --------------------------------------------------------------------

