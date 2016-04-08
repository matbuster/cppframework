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

#define SERIALIZER_OK			0

namespace Serialization {

	/** class serializer to serialize data */
	class Serializer {
	
	private:
		/** buffer of serialized data */
		unsigned char m_pSerializedData[SERIALIZER_LEN];

		/** len of the serialized data buffer */
		long m_lSerializedDataLen;

		/** collection of serialized items */
		Collection::List<SerializedItem> * m_list;

		/** function to get the tag of element and size */
		//long get
	
	public:
		/** main constructor and destructor of the class */
		Serializer();
		~Serializer();

		/** function to add an item to the Serializer */
		void AddItem(SerializedItem item);

		/** clear all the items inserted in the serializer */
		void ClearItems();

		/** function to serialize data */
		long Serialize();

		/** function to deserialize a buffer */
		long Deserialize(unsigned char * _pSerializedBuffer, long _lSerializeDataLen);

		/** function to get serialized data */
		void * getSerializedData();

		/** function to get the serialized data len */
		long getSerializeDataLen();

		/** function to export serialized data into an xml file */
		// long ExportToXml();

		/** function to export serialized data into an csv file */
		// long ExportToCsv();
	};
};

#endif /* SERIALIZER_H */