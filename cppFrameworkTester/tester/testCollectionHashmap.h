#ifndef TESTER_COLLECITON_HASHMAP_H
#define TESTER_COLLECITON_HASHMAP_H

// -----------------------------------------------------------
// define max constant
#define MAX_HM_ITEMS			1000

// -----------------------------------------------------------
// test configuration
//efine TEST_COOL_HASHMAP_FULL
#ifdef TEST_COOL_HASHMAP_FULL

#define TEST_COLL_HASHMAP_GETTER
#define TEST_COLL_HASHMAP_REMOVE

#else /* TEST_COOL_HASHMAP_FULL */

// define here particular case
//efine TEST_COLL_HASHMAP_GETTER
//efine TEST_COLL_HASHMAP_REMOVE

#endif /* TEST_COOL_HASHMAP_FULL */

// -----------------------------------------------------------
int tester_collection_hashmap_getter();
// -----------------------------------------------------------
int tester_collection_hashmap_remove_items();
// -----------------------------------------------------------
/** generic function to test all hasmap function */
int tester_collection_hashmap();
// -----------------------------------------------------------

#endif /* TESTER_COLLECITON_HASHMAP_H */