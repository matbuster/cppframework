
#include "SerializeShort.h"

// --------------------------------------------------------------------------------
Serialization::SerializedShort::SerializedShort(short _sValue)
	: SerializedItem(SI_TYPE_SHORT, sizeof(short), &_sValue)
{
}
Serialization::SerializedShort::SerializedShort(unsigned char * _pSerializedData,  unsigned long _lSerializedDataLen)
		: SerializedItem( _pSerializedData, _lSerializedDataLen)
{
}
Serialization::SerializedShort::~SerializedShort()
{
}
// --------------------------------------------------------------------------------
short Serialization::SerializedShort::getValue()
{
	return *(short*)getPointerValue();
}
// --------------------------------------------------------------------------------
