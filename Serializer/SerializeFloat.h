/**
 * \file 		SerializeFloat.h
 * \date 		14/09/2016 
 * \author 		MAT
 */
 
#ifndef SERIALIZED_FLOAT_H
#define SERIALIZED_FLOAT_H

#include "SerializeItem.h"

namespace Serialization {

	/** Serializer for long */
	class SerializeFloat : public Serialization::SerializedItem {

	public:
		/** main constructor and destructor of the class */
		SerializeFloat(float _fValue);
		SerializeFloat(unsigned char * _pSerializedData,  unsigned long _lSerializedDataLen);
		~SerializeFloat();

		/**! getter on the value
		 * \return long value
		 */
		float getValue();
	};
};

#endif /* SERIALIZED_FLOAT_H */