/**
 * \file 		SerializeString.h
 * \date 		04/11/2015 
 * \author 		MAT
 */
 
#ifndef SERIALIZED_STRING_H
#define SERIALIZED_STRING_H

#include "SerializeItem.h"
#include <string>

namespace Serialization {

	/** Serializer for long */
	class SerializeString : public Serialization::SerializedItem {

	public:
		/** constructor : serialize a input std::string
		 * \param [in]  _strValue : input std::string value
		 */
		SerializeString(std::string _strValue);
		/** constructor : serialize a input string, using char array and his size
		 * \param [in] _pInputString : input string value as a char * 
		 * \param [in] _ulInputStringLength: size of the input string
		 */
		SerializeString(char * _pInputString, unsigned long _ulInputStringLength);
		/** constructor : Deserialize a serialized buffer
		 * \param [in] _pSerializedData : input for the serialized data
		 * \param [in] _ulSerializedDataLen: size of the serialized data buffer
		 */
		SerializeString(unsigned char * _pSerializedData, unsigned long  _ulSerializedDataLen);
		~SerializeString();

		/**! getter on the value
		 * \return long value
		 */
		unsigned char * getValue();
	};
};

#endif /* SERIALIZED_STRING_H */