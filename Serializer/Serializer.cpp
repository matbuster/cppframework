/**
 * \file 		Serializer.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */
 
#include "Serializer.h"

// ----------------------------------------------------------------------
/** main constructor and destructor of the class */
Serialization::Serializer::Serializer()
{
	m_list = new Collection::List<SerializedItem>();
	memset(m_pSerializedData, 0x00, SERIALIZER_LEN);
	m_lSerializedDataLen = 0;
}
Serialization::Serializer::~Serializer()
{
	delete m_list;
}
// ----------------------------------------------------------------------
/** function to add an item to the Serializer */
void Serialization::Serializer::AddItem(SerializedItem item)
{
	m_list->Add(item);
}
// ----------------------------------------------------------------------
/** clear all the items inserted in the serializer */
void Serialization::Serializer::ClearItems()
{
	m_list->Clear();
}
// ----------------------------------------------------------------------
/** function to serialize data */
long Serialization::Serializer::Serialize()
{
	int iIndexCpy = 0;
	for(int i = 0; i< m_list->Count();i++) 
	{
		SerializedItem _item = m_list->getItem(i);
		memcpy(m_pSerializedData, _item.getSerializedData(), _item.getSerializedDataLen());
		iIndexCpy += _item.getSerializedDataLen();
	}
	m_lSerializedDataLen = iIndexCpy;

	return SERIALIZER_OK;
}
// ----------------------------------------------------------------------
/** function to get serialized data */
void * Serialization::Serializer::getSerializedData()
{
	return (void*)m_pSerializedData;
}
// ----------------------------------------------------------------------
/** function to get the serialized data len */
long Serialization::Serializer::getSerializeDataLen()
{
	return m_lSerializedDataLen;
}
// ----------------------------------------------------------------------
/** function to deserialize a buffer */
long Serialization::Serializer::Deserialize(unsigned char * _pSerializedBuffer, long _lSerializeDataLen)
{
	// need to fill items list, clear it
	this->ClearItems();
	return SERIALIZER_OK;
}
// ----------------------------------------------------------------------

