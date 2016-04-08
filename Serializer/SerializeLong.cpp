/**
 * \file 		SerializeLong.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */
 
#include "SerializeLong.h"

// -----------------------------------------------------------
/** main constructor and destructor of the class */
Serialization::SerializedLong::SerializedLong(long _lValue)
	: SerializedItem(SI_TYPE_LONG , sizeof(long), &_lValue)
{
}
Serialization::SerializedLong::SerializedLong(unsigned char * _pSerializedData, long _lSerializedDataLen)
	: SerializedItem(_pSerializedData, _lSerializedDataLen)
{
}
Serialization::SerializedLong::~SerializedLong()
{
}
// -----------------------------------------------------------
