/**
 * \file 		SerializeDouble.h
 * \date 		14/09/2016 
 * \author 		MAT
 */
 
#ifndef SERIALIZED_DOUBLE_H
#define SERIALIZED_DOUBLE_H

#include "SerializeItem.h"

namespace Serialization {

	/** Serializer for long */
	class SerializeDouble : public Serialization::SerializedItem {

	public:
		/** main constructor and destructor of the class */
		SerializeDouble(double _fValue);
		SerializeDouble(unsigned char * _pSerializedData,  unsigned long _lSerializedDataLen);
		~SerializeDouble();

		/**! getter on the value
		 * \return double value
		 */
		double getValue();
	};
};

#endif /* SERIALIZED_DOUBLE_H */