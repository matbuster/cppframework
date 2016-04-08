
// -----------------------------------------------------------
// include for Collection::List
#include "Collection\List.hpp"
#include "Memory\Ram.h"
#include "testCollectionList.h"
#include "cppFrameworkTesterDefines.h"

#include <assert.h>

// -----------------------------------------------------------
void internal_fill_class_list(Collection::List<tempClass> * list )
{
	for(int i = 0; i < LIST_TEST_STR_HUGE;i++)
	{
		tempClass c;
		c.set(i);
		list->Add(c);
	}
}
// -----------------------------------------------------------
void internal_static_element( )
{
	Memory::Ram * ramState = new Memory::Ram();
	double dVal0 = ramState->getPhysicalMemoryShiftFromCurrentProcess_mo();
	bool bsuccess = true;

	Collection::List<tempClass> * list = new Collection::List<tempClass>();
	internal_fill_class_list(list);

	double dVal1 = ramState->getPhysicalMemoryShiftFromCurrentProcess_mo();

	list->Clear();
	delete list;

	double dVal2 = ramState->getPhysicalMemoryShiftFromCurrentProcess_mo();

	delete ramState;
	return;
}
// -----------------------------------------------------------
int tester_collection_list_getter()
{
	int iReturnCode = TEST_OK;

#ifdef TEST_COLL_LIST_GETTER
	Collection::List<int> * list = new Collection::List<int>();
	for(int i = 0; i < MAX_LIST_ITEMS;i++)
	{
		list->Add(i);
	}

	for(int i = 0; i < MAX_LIST_ITEMS;i++)
	{
		int value = list->getItem(i);
		assert(i == value);
		if(i != value) 
		{
			iReturnCode = TEST_KO;
			break;
		}
	}
	delete list;

	// test summarry
	if(iReturnCode == TEST_OK)
	{
		printf("->tester Collection::List : tester_collection_list_getter() SUCCESS.\r\n");
	}
	else
	{
		printf("->tester Collection::List : tester_collection_list_getter() FAILED !!!\r\n");
	}
#endif /* TEST_COLL_LIST_GETTER */

	return iReturnCode;
}
// -----------------------------------------------------------
int tester_collection_list_remove_items()
{
	int iReturnCode = TEST_OK;
	
#ifdef TEST_COLL_LIST_REMOVE
	Collection::List<int> * list = new Collection::List<int>();
	for(int i = 0; i < MAX_LIST_ITEMS;i++)
	{
		list->Add(i);
	}

	// remove even items
	for(int i = (MAX_LIST_ITEMS-1); i >= 0; i--)
	{
		try
		{
			if(0 == (i%2) )
			{
				list->Remove(i);
			}
		} 
		catch(...)
		{
			printf("->tester_collection_list_remove_items() : FAILED !!! index out of bound exception.\r\n");
			assert(false);
		}
	}

	// test list size
	double dListSize = (double)list->Count();
	double dItemsRemoved = (double)(MAX_LIST_ITEMS) / 2.0f;
	if(dListSize != dItemsRemoved)
	{
		iReturnCode = TEST_KO;
	}
	assert( dListSize == dItemsRemoved );
	delete list;

	// test summarry
	if(iReturnCode == TEST_OK)
	{
		printf("->tester Collection::List : tester_collection_list_remove_items() SUCCESS.\r\n");
	}
	else
	{
		printf("->tester Collection::List : tester_collection_list_remove_items() FAILED !!!\r\n");
	}
#endif /* TEST_COLL_LIST_REMOVE */

	return iReturnCode;
}
// -----------------------------------------------------------
int tester_collection_list_manage_class_shared_ptr()
{
	int iReturnCode = TEST_OK;
#ifdef TEST_COLL_LIST_CLASS
	Memory::Ram * ramState = new Memory::Ram();
	double dVal0 = ramState->getPhysicalMemoryShiftFromCurrentProcess_mo();
	bool bsuccess = true;

	Collection::List<std::shared_ptr<tempClass>> * list = new Collection::List<std::shared_ptr<tempClass>>();
	for(int i = 0; i < LIST_TEST_STR_HUGE;i++)
	{
		std::shared_ptr<tempClass> p(new tempClass());
		list->Add(p);
	}

	double dVal1 = ramState->getPhysicalMemoryShiftFromCurrentProcess_mo();
	list->Clear();

	if(list->Count() > 0)
	{
		bsuccess = false;
	}

	delete list;

	double dVal2 = ramState->getPhysicalMemoryShiftFromCurrentProcess_mo();
	delete ramState;

	// test summarry
	if(true == bsuccess)
	{
		printf("->tester Collection::List : tester_collection_list_remove_items() SUCCESS.\r\n");
	}
	else
	{
		printf("->tester Collection::List : tester_collection_list_remove_items() FAILED !!!\r\n");
	}

#endif /* TEST_COLL_LIST_CLASS */
	return iReturnCode;
}
// -----------------------------------------------------------
int tester_collection_list_manage_class()
{
	int iReturnCode = TEST_OK;
#ifdef TEST_COLL_LIST_CLASS

	Memory::Ram * ramState = new Memory::Ram();
	double dVal0 = ramState->getPhysicalMemoryShiftFromCurrentProcess_mo();
	bool bsuccess = true;

	Collection::List<tempClass*> * list = new Collection::List<tempClass*>();
	for(int i = 0; i < LIST_TEST_STR_HUGE;i++)
	{
		tempClass * c = new tempClass();
		c->set(i);
		list->Add(c);
	}

	double dVal1 = ramState->getPhysicalMemoryShiftFromCurrentProcess_mo();

	for(int i = (LIST_TEST_STR_HUGE-1); i >= 0 ;i--)
	{
		tempClass* item = list->getItem(0);
		delete item;
		list->Remove(0);
	}

	if(list->Count() > 0)
	{
		bsuccess = false;
	}

	delete list;
	double dVal2 = ramState->getPhysicalMemoryShiftFromCurrentProcess_mo();
	delete ramState;

	// test summarry
	if(true == bsuccess)
	{
		printf("->tester Collection::List : tester_collection_list_remove_items() SUCCESS.\r\n");
	}
	else
	{
		printf("->tester Collection::List : tester_collection_list_remove_items() FAILED !!!\r\n");
	}
#endif /* TEST_COLL_LIST_CLASS */
	return iReturnCode;
}
// -----------------------------------------------------------
int tester_collection_list()
{
	printf(STR_LINE_DISPLAY_SEP);
	printf("testing Collection::List\r\n");
	printf(STR_LINE_DISPLAY_SEP);

	int iReturnCode = TEST_OK;
	iReturnCode = tester_collection_list_getter();
	iReturnCode = tester_collection_list_remove_items();
	iReturnCode = tester_collection_list_manage_class_shared_ptr();
	iReturnCode = tester_collection_list_manage_class();
	internal_static_element();

	printf(STR_LINE_JUMP);
	return iReturnCode;
}
// -----------------------------------------------------------

