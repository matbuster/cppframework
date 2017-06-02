/**
 * \file 		SerializeString.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */
 
#include "SerializeString.h"

// -----------------------------------------------------------
/** main constructor and destructor of the class */
Serialization::SerializeString::SerializeString(std::string _strValue)
	: SerializedItem(SI_TYPE_STRING, _strValue.length(), (void*)_strValue.c_str())
{
}
Serialization::SerializeString::SerializeString(char * _pInputString, unsigned long _ulInputStringLength)
	: SerializedItem(SI_TYPE_STRING, _ulInputStringLength, (void*)_pInputString)
{
}
Serialization::SerializeString::SerializeString(unsigned char * _pSerializedData, unsigned long  _lSerializedDataLen)
	: SerializedItem(_pSerializedData, _lSerializedDataLen)
{
}
Serialization::SerializeString::~SerializeString()
{
}
// -----------------------------------------------------------
unsigned char* Serialization::SerializeString::getValue()
{
	return (unsigned char*)getPointerValue();
}
// -----------------------------------------------------------

