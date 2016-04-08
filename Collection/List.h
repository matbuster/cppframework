/**
 * \file 		List.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <list>

namespace Collection {

	/** class list definition using std */
	template <typename T>
	class List {
	
	private:
		/** internal list of typename element */
		std::list<T> * m_list;

		/** function to get the item corresponding to the index */
		T& getItem(int index);
	public:
		/** constructor and destructor */
		List();
		~List();

		/** Adds an object to the end of the List<T> 
		 * param [in] item Type: T, The object to be added to the end of the List<T>. The value can be null for reference types.
		 */
		void Add(T _item);

		/** Removes all elements from the List<T> */
		void Clear();

		/** define operator array to get the corresponding element */
		T& operator[] (int index);
	};
}; 

#endif /* LIST_H */