/**
 * \file 		SerializeShort.h
 * \date 		14/09/2016 
 * \author 		MAT
 */
 
#ifndef SERIALIZED_SHORT_H
#define SERIALIZED_SHORT_H

#include "SerializeItem.h"

namespace Serialization {

	/** Serializer for long */
	class SerializedShort : public Serialization::SerializedItem {

	public:
		/** main constructor and destructor of the class */
		SerializedShort(short _sValue);
		SerializedShort(unsigned char * _pSerializedData,  unsigned long _lSerializedDataLen);
		~SerializedShort();

		/**! getter on the value
		 * \return long value
		 */
		short getValue();
	};
};

#endif /* SERIALIZED_SHORT_H */