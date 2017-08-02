#ifndef TOOLS_COLLECTION_GETTERS_H
#define TOOLS_COLLECTION_GETTERS_H

#include <list>

namespace Tools {

	namespace Collection {
		
		// ---------------------------------------------------------------
		/** getter on the target item of the list
		 */
		template<typename T> 
		static T get(std::list<T> * l, int index) {
			
			if(index < 0) return NULL;

			int iCounter = 0;
			for( typename std::list<T>::iterator it = l->begin(); it != l->end(); it++)
			{
				if(index == iCounter) {
					return *it;
				}
				iCounter++;
			}

			return NULL;
		}
	};
};

#endif // TOOLS_COLLECTION_GETTERS_H