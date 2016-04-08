/**
 * \file 		SerializeLong.h
 * \date 		04/11/2015 
 * \author 		MAT
 */
 
#ifndef SERIALIZED_LONG_H
#define SERIALIZED_LONG_H

#include "SerializeItem.h"

namespace Serialization {

	/** Serializer for long */
	class SerializedLong : public Serialization::SerializedItem {

	public:
		/** main constructor and destructor of the class */
		SerializedLong(long _lValue);
		SerializedLong(unsigned char * _pSerializedData, long _lSerializedDataLen);
		~SerializedLong();
	};
};

#endif /* SERIALIZED_LONG_H */