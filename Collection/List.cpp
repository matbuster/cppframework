/**
 * \file 		List.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#include "List.h"

// ----------------------------------------------------------------------
/** main constructor and destructor of the class */
template<typename T>
Collection::List<T>::List() 
{ 
	m_list = new std::list<T>();
}
template<typename T>
Collection::List<T>::~List() 
{
	m_list->clear();
	delete m_list;
}
// ----------------------------------------------------------------------
/** function to get the item corresponding to the index */
template<typename T>
T& Collection::List<T>::getItem(int _index)
{
	int iCounter = 0;
	for( typename std::list<T>::iterator it = m_list->begin(); it != m_list->end(); it++)
	{
		if(_index == iCounter) {
			T item = *it;
			return it;
		}
		iCounter++;
 	}
	return NULL;
}
// ----------------------------------------------------------------------
/** Adds an object to the end of the List<T> */
template<typename T>
void Collection::List<T>::Add(T _item)
{
	if(NULL != m_list)
	{
		m_list->push_back(_item);
	}
}
// ----------------------------------------------------------------------
/** Removes all elements from the List<T> */
template<typename T>
void Collection::List<T>::Clear()
{
	if(NULL != m_list)
	{
		m_list->clear();
	}
}
// ----------------------------------------------------------------------
/** define operator array to get the corresponding element */
template<typename T>
T& Collection::List<T>::operator[] (int index)
{
	T _item;
	return _item;
}
// ----------------------------------------------------------------------
