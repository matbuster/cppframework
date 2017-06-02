/**
 * \file 		SerializeInt.h
 * \date 		14/09/2016 
 * \author 		MAT
 */
 
#ifndef SERIALIZED_INT_H
#define SERIALIZED_INT_H

#include "SerializeItem.h"

namespace Serialization {

	/** Serializer for long */
	class SerializeInt : public Serialization::SerializedItem {

	public:
		/** main constructor and destructor of the class */
		SerializeInt(int _iValue);
		SerializeInt(unsigned char * _pSerializedData,  unsigned long _lSerializedDataLen);
		~SerializeInt();

		/**! getter on the value
		 * \return long value
		 */
		int getValue();
	};
};

#endif /* SERIALIZED_INT_H */