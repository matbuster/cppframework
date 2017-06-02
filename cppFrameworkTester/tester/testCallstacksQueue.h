#ifndef TEST_CALLSTACKs_QUEUE_H
#define TEST_CALLSTACKs_QUEUE_H

// -----------------------------------------------------------
// constant definition
#define TEST_MESSAGE_1		"Hello world!!"
#define TEST_MESSAGE_2		"Ceci est un message de test."
#define TEST_MESSAGE_3		"eaujfsdlqjfl qj,jspqdfoj,qcofpo,isqp,xfioreuqnfpseo,xopsoriqx,ùpiouseresqnirxeuiqynreqpizorynzqeorynx"
#define TEST_MESSAGE_4		"Et nata municipia latius dispersos et missilibus serpentes montium obvios inter municipia dispersos serpentes quisque multitudine municipia ululatu et plurima ardor milites mollia editos et educata lacessens pro confertos dispositos nunc moliens loca dispersos recurvosque sed latius ingenti multitudine hic globis isdem plurima eminus globis repellere globis multitudine pro et educata viribus editos et perterrens mollia per lacessens conterminant multitudine municipia quae missilibus missilibus ardor superabatur plurima viribus milites educata viribus et ut aliquotiens moliens conterminant plana plana recurvosque plurima nunc serpentes aliquotiens ardor eos confertos obvios persultat viribus milites latius confertos et conterminant serpentes educata ambitus moliens ululatu ut."

#define NUM_TEST_MESSAGE	4
#define QUEUE_TEST_STR_HUGE 8082

// -----------------------------------------------------------
// test configuration
#define TEST_CSTK_QUEU_FULL
#ifdef TEST_CSTK_QUEU_FULL

#define TEST_CSTK_QUEU_PUSH_POP
#define TEST_CSTK_QUEU_PUSH_GET
#define TEST_CSTK_QUEU_MEM_GET_CLASS
#define TEST_CSTK_QUEU_MEM_POP_CLASS

#else /* TEST_COOL_LIST_FULL */

// define here particular case
#define TEST_CSTK_QUEU_PUSH_POP

#endif /* TEST_COOL_LIST_FULL */
namespace Test{
	// ------------------------------------------------------------
	int tester_callstacks_queue_push_pop();
	// ------------------------------------------------------------
	int tester_callstacks_queue_push_get();
	// ------------------------------------------------------------
	int tester_callstacks_queue_get_mem_class();
	// ------------------------------------------------------------
	int tester_callstacks_queue_pop_mem_class();
	// ------------------------------------------------------------
	int tester_callstacks_queue();
	// ------------------------------------------------------------
}
#endif /* TEST_CALLSTACKs_QUEUE_H */