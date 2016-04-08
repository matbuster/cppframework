
#include "Collection\Hashmap.hpp"
#include "testCollectionHashmap.h"
#include "cppFrameworkTesterDefines.h"

#include <assert.h>
#include <string>

// -----------------------------------------------------------
int tester_collection_hashmap_getter()
{
	int iReturnCode = TEST_OK;
#ifdef TEST_COLL_HASHMAP_GETTER
	Collection::Hashmap<std::string, int> * mapper = new Collection::Hashmap<std::string, int>();

	for(int i =0;i<MAX_HM_ITEMS; i++)
	{
		char tempChar[10] = {0};
		sprintf(tempChar,"item%d", i);

		std::string item = tempChar;
		mapper->Add(item,i);
	}

	for(int i = 0; i < mapper->Count(); i++)
	{
		int value = mapper->getSecondItem(i);
		assert(value == (i));
		if(value != (i))
		{
			iReturnCode = TEST_KO;
		}
	}

	delete mapper;

	// test summarry
	if(iReturnCode == TEST_OK)
	{
		printf("->tester Collection::List : tester_collection_hashmap_getter() SUCCESS.\r\n");
	}
	else
	{
		printf("->tester Collection::List : tester_collection_hashmap_getter() FAILED !!!\r\n");
	}
#endif /* TEST_COLL_HASHMAP_GETTER */
	return iReturnCode;
}
// -----------------------------------------------------------
int tester_collection_hashmap_remove_items()
{
	int iReturnCode = TEST_OK;
#ifdef TEST_COLL_HASHMAP_REMOVE

#endif /* TEST_COLL_HASHMAP_REMOVE */
	return iReturnCode;
}
// -----------------------------------------------------------
/** generic function to test all hasmap function */
int tester_collection_hashmap()
{
	printf(STR_LINE_DISPLAY_SEP);
	printf("testing Collection::Hashmap\r\n");
	printf(STR_LINE_DISPLAY_SEP);

	int iReturnCode = TEST_OK;
	iReturnCode = tester_collection_hashmap_getter();

	return iReturnCode;
}
// -----------------------------------------------------------