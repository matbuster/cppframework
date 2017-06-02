
#include "SerializeBool.h"

// --------------------------------------------------------------------------------
Serialization::SerializedBool::SerializedBool(bool _bValue)
	: SerializedItem(SI_TYPE_BOOL, sizeof(bool), &_bValue)
{
}
Serialization::SerializedBool::SerializedBool(unsigned char * _pSerializedData,  unsigned long _lSerializedDataLen)
		: SerializedItem(_pSerializedData, _lSerializedDataLen)
{
}
Serialization::SerializedBool::~SerializedBool()
{
}
// --------------------------------------------------------------------------------
bool Serialization::SerializedBool::getValue()
{
	return *(bool*)getPointerValue();
}
// --------------------------------------------------------------------------------
