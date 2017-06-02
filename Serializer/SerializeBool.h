/**
 * \file 		SerializeBool.h
 * \date 		14/09/2016 
 * \author 		MAT
 */
 
#ifndef SERIALIZED_BOOL_H
#define SERIALIZED_BOOL_H

#include "SerializeItem.h"

namespace Serialization {

	/** Serializer for long */
	class SerializedBool : public Serialization::SerializedItem {

	public:
		/** main constructor and destructor of the class */
		SerializedBool(bool _bValue);
		SerializedBool(unsigned char * _pSerializedData,  unsigned long _lSerializedDataLen);
		~SerializedBool();

		/**! getter on the value
		 * \return long value
		 */
		bool getValue();
	};
};

#endif /* SERIALIZED_BOOL_H */