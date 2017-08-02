
#include "CallStacks/Queue.h"
#include "Diagnostic/assertion.h"
#include "Memory/RAM.h"
#include "testCallstacksQueue.h"
#include "cppFrameworkTesterDefines.h"
#include "toolsconstant.h"
#include "TesterReport.h"

#ifdef LINUX
#include <stdio.h>
#include <string.h>
#endif // LINUX

// ------------------------------------------------------------
int Test::tester_callstacks_queue_push_pop()
{
	int iReturnCode = TEST_OK;
#ifdef TEST_CSTK_QUEU_PUSH_POP

	unsigned char cTempMessage[STR_LONG];
	unsigned long lSizeMessage = 0;

	memset(cTempMessage, 0x00, STR_LONG);
	CallStacks::Queue * queue = new CallStacks::Queue();
	
	queue->pushRequest((unsigned char *)TEST_MESSAGE_1, sizeof(TEST_MESSAGE_1) );
	queue->pushRequest((unsigned char *)TEST_MESSAGE_2, sizeof(TEST_MESSAGE_2) );
	queue->pushRequest((unsigned char *)TEST_MESSAGE_3, sizeof(TEST_MESSAGE_3) );
	queue->pushRequest((unsigned char *)TEST_MESSAGE_4, sizeof(TEST_MESSAGE_4) );

	if(NUM_TEST_MESSAGE != queue->getCount())
	{
		iReturnCode = TEST_KO;
	}
	assert(NUM_TEST_MESSAGE == queue->getCount());

	for(int i = 0; i<NUM_TEST_MESSAGE; i++) 
	{
		unsigned char cTargetPop[STR_LONG] = {0};
		unsigned long ulTargetPopSize = 0;
		int iLeftInQueue = NUM_TEST_MESSAGE;

		if(i == 0) {memcpy(cTargetPop, TEST_MESSAGE_1, sizeof(TEST_MESSAGE_1)); ulTargetPopSize=sizeof(TEST_MESSAGE_1);}
		else if(i == 1) {memcpy(cTargetPop, TEST_MESSAGE_2, sizeof(TEST_MESSAGE_2)); ulTargetPopSize=sizeof(TEST_MESSAGE_2);}
		else if(i == 2) {memcpy(cTargetPop, TEST_MESSAGE_3, sizeof(TEST_MESSAGE_3)); ulTargetPopSize=sizeof(TEST_MESSAGE_3);}
		else if(i == 3) {memcpy(cTargetPop, TEST_MESSAGE_4, sizeof(TEST_MESSAGE_4)); ulTargetPopSize=sizeof(TEST_MESSAGE_4);}

		queue->popRequest(cTempMessage, &lSizeMessage);
		iLeftInQueue--;
	
		// test pop message
		if( (unsigned long)(iLeftInQueue-i) != queue->getCount())	
		{
			iReturnCode = TEST_KO;
			Diagnostic::Assert(false, "tester_callstacks_queue_push_pop() : Wrong number of left items in Queue.");
			break;
		}
		if(lSizeMessage != ulTargetPopSize)
		{
			iReturnCode = TEST_KO;
			Diagnostic::Assert(false, "tester_callstacks_queue_push_pop() : Wrong size of pop message.");
			break;
		}
		if( memcmp(cTempMessage, cTargetPop, lSizeMessage) != 0)
		{
			iReturnCode = TEST_KO;
			Diagnostic::Assert(false, "tester_callstacks_queue_push_pop() : Wrong message get in queue.");
			break;
		}
	}
	delete queue;

	// test summary
	Test::TesterReport::getInstance()->printSummary((iReturnCode == TEST_OK), "CallStacks::Queue", "tester_callstacks_queue_push_pop()");

#endif /* TEST_CSTK_QUEU_PUSH_POP */
	return iReturnCode; 
}
// ------------------------------------------------------------
int Test::tester_callstacks_queue_push_get()
{
	int iReturnCode = TEST_OK;
#ifdef TEST_CSTK_QUEU_PUSH_GET

	unsigned char cTempMessage[STR_LONG];
	unsigned long lSizeMessage = 0;

	memset(cTempMessage, 0x00, STR_LONG);
	CallStacks::Queue * queue = new CallStacks::Queue();
	
	queue->pushRequest((unsigned char *)TEST_MESSAGE_1, sizeof(TEST_MESSAGE_1) );
	queue->pushRequest((unsigned char *)TEST_MESSAGE_2, sizeof(TEST_MESSAGE_2) );
	queue->pushRequest((unsigned char *)TEST_MESSAGE_3, sizeof(TEST_MESSAGE_3) );
	queue->pushRequest((unsigned char *)TEST_MESSAGE_4, sizeof(TEST_MESSAGE_4) );

	if(NUM_TEST_MESSAGE != queue->getCount())
	{
		iReturnCode = TEST_KO;
	}
	assert(NUM_TEST_MESSAGE == queue->getCount());

	int iLeftMessage = NUM_TEST_MESSAGE;
	for(int i = 0; i<NUM_TEST_MESSAGE; i++) 
	{
		unsigned char cTargetPop[STR_LONG] = {0};
		unsigned long ulTargetPopSize = 0;

		if(i == 0) {memcpy(cTargetPop, TEST_MESSAGE_1, sizeof(TEST_MESSAGE_1)); ulTargetPopSize=sizeof(TEST_MESSAGE_1);}
		else if(i == 1) {memcpy(cTargetPop, TEST_MESSAGE_2, sizeof(TEST_MESSAGE_2)); ulTargetPopSize=sizeof(TEST_MESSAGE_2);}
		else if(i == 2) {memcpy(cTargetPop, TEST_MESSAGE_3, sizeof(TEST_MESSAGE_3)); ulTargetPopSize=sizeof(TEST_MESSAGE_3);}
		else if(i == 3) {memcpy(cTargetPop, TEST_MESSAGE_4, sizeof(TEST_MESSAGE_4)); ulTargetPopSize=sizeof(TEST_MESSAGE_4);}

		queue->getRequest(cTempMessage, &lSizeMessage);
	
		// test pop message
		if( (unsigned long)(iLeftMessage) != queue->getCount())	
		{
			iReturnCode = TEST_KO;
			Diagnostic::Assert(false, "tester_callstacks_queue_push_get() : Wrong number of left items in Queue.");
			break;
		}
		if(lSizeMessage != ulTargetPopSize)
		{
			iReturnCode = TEST_KO;
			Diagnostic::Assert(false, "tester_callstacks_queue_push_get() : Wrong size of pop message.");
			break;
		}
		if( memcmp(cTempMessage, cTargetPop, lSizeMessage) != 0)
		{
			iReturnCode = TEST_KO;
			Diagnostic::Assert(false, "tester_callstacks_queue_push_get() : Wrong message get in queue.");
			break;
		}

		queue->popRequest(cTempMessage, &lSizeMessage);
		iLeftMessage--;
	}
	delete queue;

	// test summary
	Test::TesterReport::getInstance()->printSummary((iReturnCode == TEST_OK), "CallStacks::Queue", "tester_callstacks_queue_push_get()");
	

#endif /* TEST_CSTK_QUEU_PUSH_GET */
	return iReturnCode; 
}
// ------------------------------------------------------------
int Test::tester_callstacks_queue_get_mem_class()
{
	int iReturnCode = TEST_OK;
#ifdef TEST_CSTK_QUEU_MEM_GET_CLASS
	Memory::Ram * ramState = new Memory::Ram();

	//double dVal0 = ramState->getPhysicalMemoryShiftFromCurrentProcess_mo();
	CallStacks::Queue * queue = new CallStacks::Queue();
	for(int i = 0; i< QUEUE_TEST_STR_HUGE; i++)
	{
		queue->pushRequest(new CallStacks::BaseStackMessage());
	}

	//double dVal1 = ramState->getPhysicalMemoryShiftFromCurrentProcess_mo();
	// get request for each element
	for(int i = (QUEUE_TEST_STR_HUGE-1); i >= 0; i--)
	{
		CallStacks::BaseStackMessage * temp = new CallStacks::BaseStackMessage();
		queue->getRequest(temp);
		delete temp;
	}

	// SIZE DO NOT CHANGE
	Diagnostic::Assert(QUEUE_TEST_STR_HUGE == queue->getCount());

	//double dVal2 = ramState->getPhysicalMemoryShiftFromCurrentProcess_mo();
	// test summary
	bool bSuccess = (QUEUE_TEST_STR_HUGE == queue->getCount());
	Test::TesterReport::getInstance()->printSummary((bSuccess == true), "CallStacks::Queue", "tester_callstacks_queue_get_mem_class()");


	delete queue;
	delete ramState;

#endif /* TEST_CSTK_QUEU_MEM_GET_CLASS*/
	return iReturnCode;
}
// ------------------------------------------------------------
int Test::tester_callstacks_queue_pop_mem_class()
{
	int iReturnCode = TEST_OK;
#ifdef TEST_CSTK_QUEU_MEM_POP_CLASS
	Memory::Ram * ramState = new Memory::Ram();

	//double dVal0 = ramState->getPhysicalMemoryShiftFromCurrentProcess_mo();
	CallStacks::Queue * queue = new CallStacks::Queue();
	for(int i = 0; i< QUEUE_TEST_STR_HUGE; i++)
	{
		queue->pushRequest(new CallStacks::BaseStackMessage());
	}

	//double dVal1 = ramState->getPhysicalMemoryShiftFromCurrentProcess_mo();
	// get request for each element
	for(int i = (QUEUE_TEST_STR_HUGE-1); i >= 0; i--)
	{
		CallStacks::BaseStackMessage * temp = new CallStacks::BaseStackMessage();
		queue->popRequest(temp);
		delete temp;
	}

	// SIZE DO NOT CHANGE
	Diagnostic::Assert(0 == queue->getCount());
	//double dVal2 = ramState->getPhysicalMemoryShiftFromCurrentProcess_mo();

	// test summary
	bool bSuccess = (0 == queue->getCount());
	Test::TesterReport::getInstance()->printSummary((bSuccess == true), "CallStacks::Queue", "tester_callstacks_queue_pop_mem_class()");


	delete queue;
	delete ramState;

#endif /* TEST_CSTK_QUEU_MEM_POP_CLASS */
	return iReturnCode;
}
// ------------------------------------------------------------
int Test::tester_callstacks_queue()
{
	Test::TesterReport::getInstance()->printHeader("testing CallStacks::Queue");

	int iReturnCode = TEST_OK;

	iReturnCode = tester_callstacks_queue_push_pop();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Callstack::Queue", "tester_callstacks_queue_push_pop()");
	iReturnCode = tester_callstacks_queue_push_get();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Callstack::Queue", "tester_callstacks_queue_push_get()");
	iReturnCode = tester_callstacks_queue_get_mem_class();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Callstack::Queue", "tester_callstacks_queue_get_mem_class()");
	iReturnCode = tester_callstacks_queue_pop_mem_class();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Callstack::Queue", "tester_callstacks_queue_pop_mem_class()");

	return iReturnCode;
}
// ------------------------------------------------------------
