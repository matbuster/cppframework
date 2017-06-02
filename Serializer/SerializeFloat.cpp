
#include "SerializeFloat.h"

// --------------------------------------------------------------------------------
Serialization::SerializeFloat::SerializeFloat(float _fValue)
	: SerializedItem(SI_TYPE_FLOAT, sizeof(float), &_fValue)
{
}
Serialization::SerializeFloat::SerializeFloat(unsigned char * _pSerializedData,  unsigned long _lSerializedDataLen)
		: SerializedItem( _pSerializedData, _lSerializedDataLen)
{
}
Serialization::SerializeFloat::~SerializeFloat()
{
}
// --------------------------------------------------------------------------------
float Serialization::SerializeFloat::getValue()
{
	return *(float*)getPointerValue();
}
// --------------------------------------------------------------------------------
