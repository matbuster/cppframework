/**
 * \file 		Serializer.h
 * \date 		04/11/2015 
 * \author 		MAT
 */
 
#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "../Collection/List.hpp"
#include "SerializeItem.h"

#define SERIALIZER_LEN			8092

#define SERIALIZER_OK						0
#define SERIALIZER_KO						1
#define SERIALIZER_WRONG_SIZE_SIRIALIZED	2
#define SERIALIZER_DESER_LOST				3
#define SERIALIZER_DESER_FAILED				4
				
namespace Serialization {

	/** class serializer to serialize data */
	class Serializer {
	
	private:
		/** buffer of serialized data */
		unsigned char * m_pSerializedData;

		/** len of the serialized data buffer */
		unsigned long m_ulSerializedDataLen;

		/** collection of serialized items */
		Collection::List<SerializedItem*> * m_list;

		/** function to estimate buffe len */
		unsigned long getSerilizedDataLenEstimation();
	
	public:
		/** main constructor and destructor of the class */
		Serializer();
		~Serializer();

		/** function to add an item to the Serializer */
		void AddItem(SerializedItem * item);

		/** clear all the items inserted in the serializer */
		void ClearItems();

		/** function to serialize data */
		long Serialize();

		/** function to deserialize a buffer */
		long Deserialize(unsigned char * _pSerializedBuffer, long _lSerializeDataLen);

		/** function to get serialized data */
		unsigned char * getSerializedData();

		/** function to get the serialized data len */
		long getSerializeDataLen();
		
		// ---------------------------------------------------------------
		/**! getter on the size of SerializedItem
		 * \return counter on serialized item
		 */
		int getItemCount();

		// ---------------------------------------------------------------
		/**! getter on the target item, pointer by index
		 * \param [in] index: target index of the item
		 * \return serialized item object, NULL if index is out of bounds
		 */
		SerializedItem * getItemAt(int index);
	};
};

#endif /* SERIALIZER_H */