
#include "CallStacks/BaseStackMessage.h"
#include "Memory/RAM.h"
#include "testCallStacksBasemessage.h"
#include "cppFrameworkTesterDefines.h"
#include "toolsconstant.h"

#include <string>
#include <assert.h>

#ifdef LINUX
#include <stdio.h>
#include <string.h>
#endif // LINUX

#define MAX_MESSAGE_CREATION	10000000

// ------------------------------------------------------------
int tester_callstacks_create_max_base_message()
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

	// test summarry
	if(abs(dVal2-dVal1)<0.0001)
	{
		printf("->tester CallStacks::BaseStackMessage : tester_callstacks_create_max_base_message() SUCCESS.\r\n");
	}
	else
	{
		printf("->tester CallStacks::BaseStackMessage : tester_callstacks_create_max_base_message() FAILED !!!\r\n");
	}

#endif // TEST_CREATE_BASE_MESSAGE

	return 0;
}
// ------------------------------------------------------------
int tester_callstacks_base_message()
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

	// test summarry
	if(iReturnCode == TEST_OK)
	{
		printf("->tester CallStacks::BaseStackMessage : tester_callstacks_base_message() SUCCESS.\r\n");
	}
	else
	{
		printf("->tester CallStacks::BaseStackMessage : tester_callstacks_base_message() FAILED !!!\r\n");
	}
#endif /* TEST_BASE_MESSAGE */

	return iReturnCode;
}
// ------------------------------------------------------------
int tester_callstacks_base_message_full()
{
	printf(STR_LINE_DISPLAY_SEP);
	printf("testing CallStack::BaseStackMessage\r\n");
	printf(STR_LINE_DISPLAY_SEP);

	tester_callstacks_create_max_base_message();
	tester_callstacks_base_message();

	return 0;
}
// ------------------------------------------------------------
