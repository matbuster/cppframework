
#include "CallStacks/BaseStackMessage.h"
#include "Memory/RAM.h"
#include "testCallStacksBasemessage.h"
#include "cppFrameworkTesterDefines.h"
#include "toolsconstant.h"
#include "TesterReport.h"

#include <string>
#include <assert.h>

#ifdef LINUX
#include <stdio.h>
#include <string.h>
#endif // LINUX

#define MAX_MESSAGE_CREATION	10000000

// ------------------------------------------------------------
int Test::tester_callstacks_create_max_base_message()
{
#ifdef TEST_CREATE_BASE_MESSAGE

	Memory::Ram * ramState = new Memory::Ram();

	for(int i = 0; i <MAX_MESSAGE_CREATION;i++)
	{
		CallStacks::BaseStackMessage * message = new CallStacks::BaseStackMessage();
		delete message;
	}

	double dVal1 = ramState->getPhysicalMemoryShiftFromCurrentProcess_mo();
	for(int i = 0; i <MAX_MESSAGE_CREATION;i++)
	{
		CallStacks::BaseStackMessage message;
	}

	double dVal2 = ramState->getPhysicalMemoryShiftFromCurrentProcess_mo();
	delete ramState;

	// test summary
	Test::TesterReport::getInstance()->printSummary((abs(dVal2-dVal1)<0.0001), "CallStacks::BaseStackMessage", "tester_callstacks_create_max_base_message()");


#endif // TEST_CREATE_BASE_MESSAGE

	return 0;
}
// ------------------------------------------------------------
int Test::tester_callstacks_base_message()
{
	int iReturnCode = TEST_OK;

#ifdef TEST_BASE_MESSAGE
	std::string testMessage = "Hello! Ceci est un message de test pour tester les CallStacks::BaseStackMessage().";
	CallStacks::BaseStackMessage * message = new CallStacks::BaseStackMessage( 0,(unsigned char*)testMessage.c_str(), (unsigned long)testMessage.length());
	
	// testing size message
	if( (unsigned long)(testMessage.length()) != message->getSizeMessage())
	{
		iReturnCode = TEST_KO;
	}
	assert((unsigned long)(testMessage.length()) == message->getSizeMessage());

	// testing message
	if(memcmp(message->getMessage(), testMessage.c_str(), message->getSizeMessage()) != 0)
	{
		iReturnCode = TEST_KO;
	}
	assert(memcmp(message->getMessage(), testMessage.c_str(), message->getSizeMessage()) == 0);

	delete message;

	// test summary
	Test::TesterReport::getInstance()->printSummary((iReturnCode == TEST_OK), "CallStacks::BaseStackMessage", "tester_callstacks_base_message()");

#endif /* TEST_BASE_MESSAGE */

	return iReturnCode;
}
// ------------------------------------------------------------
int Test::tester_callstacks_base_message_full()
{
	Test::TesterReport::getInstance()->printHeader("testing CallStack::BaseStackMessage");

	int iReturnCode = TEST_OK;

	iReturnCode = tester_callstacks_create_max_base_message();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Callstack::BaseMessage", "tester_callstacks_create_max_base_message()");
	iReturnCode = tester_callstacks_base_message();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Callstack::BaseMessage", "tester_callstacks_base_message()");

	return 0;
}
// ------------------------------------------------------------
