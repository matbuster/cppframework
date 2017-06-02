
#include "SerializeInt.h"

// --------------------------------------------------------------------------------
Serialization::SerializeInt::SerializeInt(int _iValue)
	: SerializedItem(SI_TYPE_INT, sizeof(int), &_iValue)
{
}
Serialization::SerializeInt::SerializeInt(unsigned char * _pSerializedData,  unsigned long _lSerializedDataLen)
		: SerializedItem( _pSerializedData, _lSerializedDataLen)
{
}
Serialization::SerializeInt::~SerializeInt()
{
}
// --------------------------------------------------------------------------------
int Serialization::SerializeInt::getValue()
{
	return *(int*)getPointerValue();
}
// --------------------------------------------------------------------------------
