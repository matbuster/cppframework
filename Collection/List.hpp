/**
 * \file 		List.hpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <list>
#include <exception>

namespace Collection {

	/** class list definition using std 
	* template cannot beemented in cpp. fusionning cpp and h is the solution
	* to compile project*/
	template <typename T>
	class List {
	
	private:
		/** internal list of typename element */
		std::list<T> * m_list;
                
 	public:
		// ----------------------------------------------------------------------
		/** constructor and destructor */
		List() {
			m_list = new std::list<T>();
		}
		~List() {
			m_list->clear();
			delete m_list;	
		}
		// ----------------------------------------------------------------------
		/** Gets the number of elements contained in the List<T>. */
		int Count() {
			return (int)m_list->size();
		}
		// ----------------------------------------------------------------------
		/** get the max capacity of the element */
		int getMaxCapacity() {
			return (int)m_list->max_size();
		}
		// ----------------------------------------------------------------------
		/** Adds an object to the end of the List<T> 
		 * param [in] item Type: T, The object to be added to the end of the List<T>. The value can be null for reference types.
		 */
		void Add(T _item) {	
			if(NULL != m_list)
			{
				m_list->push_back(_item);
			}
		}
		// ----------------------------------------------------------------------
		/** Adds the elements of the specified collection to the end of the List<T>. 
		 * \param [in] collection : Type: System.Collections.Generic.IEnumerable<T>
		 *		The collection whose elements should be added to the end of the List<T>. The collection itself cannot be null, but it can contain elements that are null, if type T is a reference type.
		 */
		void AddRange(List<T> collection) {
			for(int i = 0; i<collection->Count(); i++) {
				this->Add(collection->getItem(i));
			}
		}
		// ----------------------------------------------------------------------
		/** Inserts an element into the List<T> at the specified index. */
		void Insert(int _iIndex, T _item) {
			int iCounter = 0;
			for( typename std::list<T>::iterator it = m_list->begin(); it != m_list->end(); it++)
			{
				if(_iIndex == iCounter) {
					m_list->insert(it, _item);
					return it;
				}
				iCounter++;
			}
		}
		// ----------------------------------------------------------------------

		// ----------------------------------------------------------------------
		/** Removes all elements from the List<T> */
		void Clear() {
			if(NULL != m_list)
			{
				m_list->clear();
			}		
		}
		// ----------------------------------------------------------------------

		// ----------------------------------------------------------------------
		/** function to remove a specific element from the List<T> */
		void Remove(int _index)
		{
			if(_index < 0 || _index > this->Count())
				throw std::exception();

			int iCounter = 0;
			for( typename std::list<T>::iterator it = m_list->begin(); it != m_list->end(); it++)
			{
				if(_index == iCounter) {
					m_list->erase(it);
					return;
				}
				iCounter++;
			}
			throw std::exception();
		}
		// ----------------------------------------------------------------------
		/** function to delete all element of collection */
		void DeleteAll()
		{
			for(int i = (m_list->size()-1); i >= 0;i--)
			{
				m_list->pop_back();
			}
		}

		// ----------------------------------------------------------------------
		/** function to get the item corresponding to the index */
		T getItem(int _index) {

			if(_index < 0 || _index > this->Count())
				throw std::exception();
			
			int iCounter = 0;
			for( typename std::list<T>::iterator it = m_list->begin(); it != m_list->end(); it++)
			{
				if(_index == iCounter) {
					return *it;
				}
				iCounter++;
			}

			throw std::exception();
		}
		// ----------------------------------------------------------------------
	};
}; 

#endif /* LIST_H */