
#include "SerializeDouble.h"

// --------------------------------------------------------------------------------
Serialization::SerializeDouble::SerializeDouble(double _dValue)
	: SerializedItem(SI_TYPE_DOUBLE, sizeof(double), &_dValue)
{
}
Serialization::SerializeDouble::SerializeDouble(unsigned char * _pSerializedData,  unsigned long _lSerializedDataLen)
		: SerializedItem( _pSerializedData, _lSerializedDataLen)
{
}
Serialization::SerializeDouble::~SerializeDouble()
{
}
// --------------------------------------------------------------------------------
double Serialization::SerializeDouble::getValue()
{
	return *(double*)getPointerValue();
}
// --------------------------------------------------------------------------------
