/**
 * \file 		Hashmap.hpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>
#include <map>
#include <exception>

namespace Collection {

	/** class map definition using std 
	* template cannot beemented in cpp. fusionning cpp and h is the solution
	* to compile project*/
	template <typename T1, typename T2>
	class Hashmap {
	
	private:
		/** internal map of typename element */
		std::map<T1, T2> * m_map;

	public:
		// ----------------------------------------------------------------------
		/** constructor and destructor */
		Hashmap() {
			m_map = new std::map<T1, T2>();
		}
		~Hashmap() {
			m_map->clear();
			delete m_map;	
		}
		// ----------------------------------------------------------------------
		/** Gets the number of elements contained in the map<T>. */
		int Count() {
			return (int)m_map->size();
		}

		// ----------------------------------------------------------------------
		/** Adds an object to the end of the map<T> 
		 * param [in] item Type: T, The object to be added to the end of the map<T>. The value can be null for reference types.
		 */
		void Add(T1 _item1, T2 _item2) {	
			if(NULL != m_map)
			{
				m_map->insert( m_map->end(), make_pair(_item1,_item2) );	
			}
		}
		// ----------------------------------------------------------------------
		/** Adds the elements of the specified collection to the end of the map<T>. 
		 * \param [in] collection : Type: System.Collections.Generic.IEnumerable<T>
		 *		The collection whose elements should be added to the end of the map<T>. 
		 * The collection itself cannot be null, but it can contain elements that are null, if type T is a reference type.
		 */
		void AddRange(Hashmap<T1, T2> * mapping) {

			for(int i = 0; i<mapping->Count(); i++) {
				this->Add(mapping->getItem(i).first, mapping->getItem(i).second);
			}
		}
		// ----------------------------------------------------------------------
		/** Inserts an element into the map<T> at the specified index. */
		void Insert(int _iIndex, T1 _item1, T2 _item2) {

			int iCounter = 0;
			for( typename std::map<T1,T2>::iterator it = m_map->begin(); it != m_map->end(); it++)
			{
				if(_iIndex == iCounter) {
					m_map->insert(it, std::pair<T1,T2>(_item1,_item2));
					return it;
				}
				iCounter++;
			}
		}
		// ----------------------------------------------------------------------

		// ----------------------------------------------------------------------
		/** Removes all elements from the map<T> */
		void Clear() {
			if(NULL != m_map)
			{
				m_map->clear();
			}		
		}
		// ----------------------------------------------------------------------

		// ----------------------------------------------------------------------
		/** function to get the item corresponding to the index */
		std::pair<T1,T2> getItem(int _index) {

			if(_index < 0 || _index > this->Count())
				throw std::exception();

			int iCounter = 0;
			for( typename std::map<T1,T2>::iterator it = m_map->begin(); it != m_map->end(); it++)
			{
				if(_index == iCounter) {
					std::pair<T1,T2> item = *it;
					return item;
				}
				iCounter++;
			}

			throw std::exception();
		}
		// ----------------------------------------------------------------------
		/** get the first item of hashmap according to the index
		 * @param _index: index of the target item 
		 * @return item value type T1 contained in hashmap
		 * @throws std::exception for index out of bounds
		 */
		T1 getFirstItem(int _index) {

			try 
			{
				std::pair<T1,T2> items = getItem(_index);
				return items.first;
			} 
			catch(...)
			{
				return NULL;
			}
		}
		// ----------------------------------------------------------------------
		/** get the second item of hashmap according to the index
		 * @param _index: index of the target item 
		 * @return item value type T1 contained in hashmap
		 * @throws std::exception for index out of bounds
		 */
		T2 getSecondItem(int _index) {

			try 
			{
				std::pair<T1,T2> items = getItem(_index);
				return items.second;
			} 
			catch(...)
			{
				return NULL;
			}
		}
		// ----------------------------------------------------------------------
	};
}; 

#endif /* HASHMAP_H */