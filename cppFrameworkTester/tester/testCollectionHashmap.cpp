
#include "Collection\Hashmap.hpp"
#include "testCollectionHashmap.h"
#include "cppFrameworkTesterDefines.h"
#include "TesterReport.h"

#include <assert.h>
#include <string>

// -----------------------------------------------------------
int Test::tester_collection_hashmap_getter()
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

	// test summary
	Test::TesterReport::getInstance()->printSummary((iReturnCode == TEST_OK), "Collection::Hashmap", "tester_collection_hashmap_getter()");

#endif /* TEST_COLL_HASHMAP_GETTER */
	return iReturnCode;
}
// -----------------------------------------------------------
int Test::tester_collection_hashmap_remove_items()
{
	int iReturnCode = TEST_OK;
#ifdef TEST_COLL_HASHMAP_REMOVE

#endif /* TEST_COLL_HASHMAP_REMOVE */
	return iReturnCode;
}
// -----------------------------------------------------------
/** generic function to test all hasmap function */
int Test::tester_collection_hashmap()
{
	Test::TesterReport::getInstance()->printHeader("testing Collection::Hashmap");

	int iReturnCode = TEST_OK;
	iReturnCode = tester_collection_hashmap_getter();

	return iReturnCode;
}
// -----------------------------------------------------------