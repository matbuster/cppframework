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
		SerializedLong(unsigned char * _pSerializedData, unsigned long  _lSerializedDataLen);
		~SerializedLong();

		/**! getter on the value
		 * \return long value
		 */
		long getValue();
	};
};

#endif /* SERIALIZED_LONG_H */