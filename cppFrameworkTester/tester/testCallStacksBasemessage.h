#ifndef TEST_CALLSTACKS_BASE_MESSAGE_H
#define TEST_CALLSTACKS_BASE_MESSAGE_H

//define TEST_BASESTACK_FULL
#ifdef TEST_BASESTACK_FULL

#define TEST_CREATE_BASE_MESSAGE
#define TEST_BASE_MESSAGE

#else
#define TEST_BASE_MESSAGE
#endif

namespace Test{
	// ------------------------------------------------------------
	int tester_callstacks_create_max_base_message();
	// ------------------------------------------------------------
	int tester_callstacks_base_message();
	// ------------------------------------------------------------
	int tester_callstacks_base_message_full();
	// ------------------------------------------------------------
}

#endif /* TEST_CALLSTACKS_BASE_MESSAGE_H */
