
#include "testCallstacksAbsouteStack.h"
#include "CallStacks/AbsoluteStack.h"
#include "Debug/assertion.h"
#include "cppFrameworkTesterDefines.h"
#include "toolsconstant.h"

#ifdef LINUX
#include <stdio.h>
#include <string.h>
#endif // LINUX

// ------------------------------------------------------------
int tester_callstacks_absolute_stacks_push_pop_1()
{
	int iReturnCode = TEST_OK;
#ifdef TEST_CSTK_ABSSTACK_PUSH_POP
	CallStacks::AbsoluteStack * absStack = new CallStacks::AbsoluteStack();

	unsigned long ulAbsoluteCounter = 0;
	int iNumMessageToTest = MAX_TEST_MESSAFE;
        printf("->testing CallStacks::AbsoluteStack  : tester_callstacks_absolute_stacks_push_pop_1()\r\n");

	CallStacks::BaseStackMessage * message1 = new CallStacks::BaseStackMessage(0, (unsigned char*) MESSAGE_1, sizeof(MESSAGE_1)); 
	CallStacks::BaseStackMessage * message2 = new CallStacks::BaseStackMessage(1, (unsigned char*) MESSAGE_2, sizeof(MESSAGE_2)); 
	CallStacks::BaseStackMessage * message3 = new CallStacks::BaseStackMessage(2, (unsigned char*) MESSAGE_3, sizeof(MESSAGE_3)); 

	absStack->pushRequest( message1 );
	absStack->pushRequest( message2 );
	absStack->pushRequest( message3 );

	if(absStack->getCount() != iNumMessageToTest)
	{
		Debug::Assert(false, "tester_callstacks_absolute_stacks_push_pop_1() : Wrong number of items after push.");
	}

	// testing loop
	for(int i = 0; i < MAX_TEST_MESSAFE; i++)
	{
		CallStacks::BaseStackMessage tempMessage;
		tempMessage.setIdentifiantMessage(i);
		iReturnCode = absStack->popRequest( &tempMessage );

		iNumMessageToTest--;
		if(absStack->getCount() != iNumMessageToTest)
		{
			Debug::Assert(false, "tester_callstacks_absolute_stacks_push_pop_1() : Wrong number of items left after pop.");
			iReturnCode = TEST_KO;
		}

		if(i==0) {if(0 != memcmp(tempMessage.getMessage(), MESSAGE_1, tempMessage.getSizeMessage())){ Debug::Assert(false, "tester_callstacks_absolute_stacks_push_pop_1() : Wrong MESSAGE_1.");iReturnCode = TEST_KO;}}
		else if(i==1) {if(0 != memcmp(tempMessage.getMessage(), MESSAGE_2, tempMessage.getSizeMessage())){ Debug::Assert(false, "tester_callstacks_absolute_stacks_push_pop_1() : Wrong MESSAGE_2.");iReturnCode = TEST_KO;}}
		else if(i==2) {if(0 != memcmp(tempMessage.getMessage(), MESSAGE_3, tempMessage.getSizeMessage())){ Debug::Assert(false, "tester_callstacks_absolute_stacks_push_pop_1() : Wrong MESSAGE_3.");iReturnCode = TEST_KO;}}
	}

	delete absStack;

	// test summarry
	if(iReturnCode == TEST_OK)
	{
		printf("->tester CallStacks::AbsoluteStack  : tester_callstacks_absolute_stacks_push_pop_1() SUCCESS.\r\n");
	}
	else
	{
		printf("->tester CallStacks::AbsoluteStack  : tester_callstacks_absolute_stacks_push_pop_1() FAILED !!!\r\n");
	}
#endif /* TEST_CSTK_ABSSTACK_PUSH_POP */
	return iReturnCode;
}
int tester_callstacks_absolute_stacks_push_pop_2()
{
	int iReturnCode = TEST_OK;
#ifdef TEST_CSTK_ABSSTACK_PUSH_POP
	CallStacks::AbsoluteStack * absStack = new CallStacks::AbsoluteStack();

	unsigned long ulAbsoluteCounter = 0;
	int iNumMessageToTest = MAX_TEST_MESSAFE;
        printf("->testing CallStacks::AbsoluteStack  : tester_callstacks_absolute_stacks_push_pop_2()\r\n");

	CallStacks::BaseStackMessage * message1 = new CallStacks::BaseStackMessage(0, (unsigned char*) MESSAGE_1, sizeof(MESSAGE_1)); 
	CallStacks::BaseStackMessage * message2 = new CallStacks::BaseStackMessage(1, (unsigned char*) MESSAGE_2, sizeof(MESSAGE_2)); 
	CallStacks::BaseStackMessage * message3 = new CallStacks::BaseStackMessage(2, (unsigned char*) MESSAGE_3, sizeof(MESSAGE_3)); 

	absStack->pushRequest( message1 );
	absStack->pushRequest( message2 );
	absStack->pushRequest( message3 );

	if(absStack->getCount() != iNumMessageToTest)
	{
		Debug::Assert(false, "tester_callstacks_absolute_stacks_push_pop_2() : Wrong number of items after push.");
	}

	// get the second message
	CallStacks::BaseStackMessage tempMessage;
	tempMessage.setIdentifiantMessage(1);
	iReturnCode = absStack->popRequest( &tempMessage );
	if(0 != memcmp(tempMessage.getMessage(), MESSAGE_2, tempMessage.getSizeMessage())) 
	{
		Debug::Assert(false, "tester_callstacks_absolute_stacks_push_pop_2() : Wrong MESSAGE_2.");
		iReturnCode = TEST_KO;
	}

	// get the last message
	tempMessage.setIdentifiantMessage(2);
	iReturnCode = absStack->popRequest( &tempMessage );
	if(0 != memcmp(tempMessage.getMessage(), MESSAGE_3, tempMessage.getSizeMessage())) 
	{
		Debug::Assert(false, "tester_callstacks_absolute_stacks_push_pop_2() : Wrong MESSAGE_3.");
		iReturnCode = TEST_KO;
	}

	// get the first message
	tempMessage.setIdentifiantMessage(0);
	iReturnCode = absStack->popRequest( &tempMessage );
	if(0 != memcmp(tempMessage.getMessage(), MESSAGE_1, tempMessage.getSizeMessage())) 
	{
		Debug::Assert(false, "tester_callstacks_absolute_stacks_push_pop_2() : Wrong MESSAGE_1.");
		iReturnCode = TEST_KO;
	}

	delete absStack;

	// test summarry
	if(iReturnCode == TEST_OK)
	{
		printf("->tester CallStacks::AbsoluteStack  : tester_callstacks_absolute_stacks_push_pop_2() SUCCESS.\r\n");
	}
	else
	{
		printf("->tester CallStacks::AbsoluteStack  : tester_callstacks_absolute_stacks_push_pop_2() FAILED !!!\r\n");
	}
#endif /* TEST_CSTK_ABSSTACK_PUSH_POP */
	return iReturnCode;
}
// ------------------------------------------------------------
int tester_callstacks_absolute_stacks_push_pop_not_found()
{
	int iReturnCode = TEST_OK;
#ifdef TEST_CSTK_ABSSTACK_PUSH_POP
	CallStacks::AbsoluteStack * absStack = new CallStacks::AbsoluteStack();
        printf("->testing CallStacks::AbsoluteStack  : tester_callstacks_absolute_stacks_push_pop_not_found()\r\n");

	unsigned long ulAbsoluteCounter = 0;
	int iNumMessageToTest = MAX_TEST_MESSAFE;

	CallStacks::BaseStackMessage * message1 = new CallStacks::BaseStackMessage(0, (unsigned char*) MESSAGE_1, sizeof(MESSAGE_1)); 
	CallStacks::BaseStackMessage * message2 = new CallStacks::BaseStackMessage(1, (unsigned char*) MESSAGE_2, sizeof(MESSAGE_2)); 
	CallStacks::BaseStackMessage * message3 = new CallStacks::BaseStackMessage(2, (unsigned char*) MESSAGE_3, sizeof(MESSAGE_3)); 

	absStack->pushRequest( message1 );
	absStack->pushRequest( message2 );
	absStack->pushRequest( message3 );

	if(absStack->getCount() != iNumMessageToTest)
	{
		Debug::Assert(false, "tester_callstacks_absolute_stacks_push_pop_not_found() : Wrong number of items after push.");
	}

	// get the second message
	CallStacks::BaseStackMessage tempMessage;
	tempMessage.setIdentifiantMessage(10);
	iReturnCode = absStack->popRequest( &tempMessage );
	if(iReturnCode != BASESTACK_NO_IT_FOUND)
	{
		Debug::Assert(false, "tester_callstacks_absolute_stacks_push_pop_not_found() : Wrong number of items after push.");
	}

	if(absStack->getCount() != iNumMessageToTest)
	{
		Debug::Assert(false, "tester_callstacks_absolute_stacks_push_pop_not_found() : Wrong number of items after pop.");
	}

	delete absStack;

	// test summarry
	if(iReturnCode == BASESTACK_NO_IT_FOUND)
	{
		printf("->tester CallStacks::AbsoluteStack  : tester_callstacks_absolute_stacks_push_pop_not_found() SUCCESS.\r\n");
	}
	else
	{
		printf("->tester CallStacks::AbsoluteStack  : tester_callstacks_absolute_stacks_push_pop_not_found() FAILED !!!\r\n");
	}

#endif /* TEST_CSTK_ABSSTACK_PUSH_POP */
	return iReturnCode;
}
// ------------------------------------------------------------
int tester_callstacks_absolute_stacks_push_get()
{
	int iReturnCode = TEST_OK;
#ifdef TEST_CSTK_ABSSTACK_PUSH_GET
	CallStacks::AbsoluteStack * absStack = new CallStacks::AbsoluteStack();
        printf("->testing CallStacks::AbsoluteStack  : tester_callstacks_absolute_stacks_push_get()\r\n");

	unsigned long ulAbsoluteCounter = 0;

	CallStacks::BaseStackMessage * message1 = new CallStacks::BaseStackMessage(0, (unsigned char*) MESSAGE_1, sizeof(MESSAGE_1)); 
	CallStacks::BaseStackMessage * message2 = new CallStacks::BaseStackMessage(1, (unsigned char*) MESSAGE_2, sizeof(MESSAGE_2)); 
	CallStacks::BaseStackMessage * message3 = new CallStacks::BaseStackMessage(2, (unsigned char*) MESSAGE_3, sizeof(MESSAGE_3)); 

	absStack->pushRequest( message1 );
	absStack->pushRequest( message2 );
	absStack->pushRequest( message3 );

	if(absStack->getCount() != MAX_TEST_MESSAFE)
	{
		Debug::Assert(false, "tester_callstacks_absolute_stacks_push_get() : Wrong number of items after push.");
	}

	// testing loop
	for(int i = 0; i < MAX_TEST_MESSAFE; i++)
	{
		CallStacks::BaseStackMessage tempMessage;
		tempMessage.setIdentifiantMessage(i);
		iReturnCode = absStack->getRequest( &tempMessage );
                
		if(absStack->getCount() != MAX_TEST_MESSAFE)
		{
			Debug::Assert(false, "tester_callstacks_absolute_stacks_push_get() : Wrong number of items left after pop.");
			iReturnCode = TEST_KO;
		}
                        
		if(i==0) {if(0 != memcmp(tempMessage.getMessage(), MESSAGE_1, tempMessage.getSizeMessage())){ Debug::Assert(false, "tester_callstacks_absolute_stacks_push_get() : Wrong MESSAGE_1.");iReturnCode = TEST_KO;}}
		else if(i==1) {if(0 != memcmp(tempMessage.getMessage(), MESSAGE_2, tempMessage.getSizeMessage())){ Debug::Assert(false, "tester_callstacks_absolute_stacks_push_get() : Wrong MESSAGE_2.");iReturnCode = TEST_KO;}}
		else if(i==2) {if(0 != memcmp(tempMessage.getMessage(), MESSAGE_3, tempMessage.getSizeMessage())){ Debug::Assert(false, "tester_callstacks_absolute_stacks_push_get() : Wrong MESSAGE_3.");iReturnCode = TEST_KO;}}
	}

	delete absStack;

	// test summarry
	if(iReturnCode == TEST_OK)
	{
		printf("->tester CallStacks::AbsoluteStack  : tester_callstacks_absolute_stacks_push_get() SUCCESS.\r\n");
	}
	else
	{
		printf("->tester CallStacks::AbsoluteStack  : tester_callstacks_absolute_stacks_push_get() FAILED !!!\r\n");
	}
#endif /* TEST_CSTK_ABSSTACK_PUSH_GET */
	return iReturnCode;
}
// ------------------------------------------------------------
int tester_callstacks_absolute_queue()
{
	printf(STR_LINE_DISPLAY_SEP);
	printf("testing CallStacks::AbsoluteStack\r\n");
	printf(STR_LINE_DISPLAY_SEP);

	int iReturnCode = TEST_OK;
	
	iReturnCode = tester_callstacks_absolute_stacks_push_pop_1();
	iReturnCode = tester_callstacks_absolute_stacks_push_pop_2();
	tester_callstacks_absolute_stacks_push_pop_not_found();
	iReturnCode = tester_callstacks_absolute_stacks_push_get();

	return iReturnCode;
}
// ------------------------------------------------------------
