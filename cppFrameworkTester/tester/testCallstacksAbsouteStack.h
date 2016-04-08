#ifndef TEST_CALLSTACKS_ABS_STACK_H
#define TEST_CALLSTACKS_ABS_STACK_H

#define MESSAGE_1	"Hello World!!!"
#define MESSAGE_2	"Salut le monde !!!"
#define MESSAGE_3	"zaezty zaiye wk, frpsqfksqore pùsqrkpzerqpezojfze jfseqihigzrie zporkzepqk,xzruaoernczqo rjzeioansxroziqruzqenieun"

#define MAX_TEST_MESSAFE	3
// -----------------------------------------------------------
// test configuration
#define TEST_CSTK_ABSSTACK_FULL
#ifdef TEST_CSTK_ABSSTACK_FULL

#define TEST_CSTK_ABSSTACK_PUSH_POP
#define TEST_CSTK_ABSSTACK_PUSH_GET

#else /* TEST_COOL_LIST_FULL */

// define here particular case
#define TEST_CSTK_ABSSTACK_PUSH_POP

#endif /* TEST_COOL_LIST_FULL */

// ------------------------------------------------------------
int tester_callstacks_absolute_stacks_push_pop_1();
int tester_callstacks_absolute_stacks_push_pop_2();
int tester_callstacks_absolute_stacks_push_get();
// ------------------------------------------------------------
int tester_callstacks_absolute_queue();
// ------------------------------------------------------------

#endif /* TEST_CALLSTACKS_ABS_STACK_H */