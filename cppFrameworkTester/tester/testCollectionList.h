#ifndef TESTER_COLLECTION_LIST_H
#define TESTER_COLLECTION_LIST_H

// -----------------------------------------------------------
// constant definition
#define MAX_LIST_ITEMS		100
#define LIST_TEST_STR_HUGE	8092
// -----------------------------------------------------------
// test configuration
#define TEST_COLL_LIST_FULL
#ifdef TEST_COLL_LIST_FULL

#define TEST_COLL_LIST_GETTER
#define TEST_COLL_LIST_REMOVE
#define TEST_COLL_LIST_CLASS

#else /* TEST_COOL_LIST_FULL */

// define here particular case
#define TEST_COLL_LIST_GETTER
//efine TEST_COLL_LIST_REMOVE

#endif /* TEST_COOL_LIST_FULL */

#include <string.h>
// -----------------------------------------------------------
class tempClass {
private:
	char cTemp[LIST_TEST_STR_HUGE];
public:
	tempClass() {memset(cTemp, 0x00, LIST_TEST_STR_HUGE);}
	~tempClass() {}
	void set(int i) {memset(cTemp, (i%0xFF), LIST_TEST_STR_HUGE);}
};
// -----------------------------------------------------------
int tester_collection_list_getter();
// -----------------------------------------------------------
int tester_collection_list_remove_items();
// -----------------------------------------------------------
int tester_collection_list_manage_class();
// -----------------------------------------------------------
/** generic function to test all list function */
int tester_collection_list();
// -----------------------------------------------------------

#endif /* TESTER_COLLECTION_LIST_H */