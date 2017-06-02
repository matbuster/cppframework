/**
 * \file 		SerializeItem.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */
 
#include "SerializeItem.h"

#include <stdlib.h>
#include <string.h>

// -------------------------------------------------------------------------
/** internal function to initialize data */
void Serialization::SerializedItem::InitInternalData()
{
	m_lSerializedDataLen = 0;
	m_lType = 0;
	m_lLengthItem = 0;
	m_bSerializedDataAllocated = false;
	m_pSerializedData = NULL;
	memset(m_pDataName, 0x00, STR_TINY);
	return;
}
// -------------------------------------------------------------------------
/** constructor and destructor of the class */
Serialization::SerializedItem::SerializedItem(long _lType, long _lLengthItem, void * _pData)
{
	InitInternalData();

	m_lType = _lType;
	m_lLengthItem = _lLengthItem;
	
	if(_pData != NULL)
	{
		m_pValue = malloc(_lLengthItem);
		memcpy(m_pValue, _pData, _lLengthItem);
	}

	// serialize
	Serialize();
}
Serialization::SerializedItem::SerializedItem(unsigned char * _pSerializedBuffer, unsigned long _lLengthData)
{
	InitInternalData();

	m_lSerializedDataLen = _lLengthData;

	// allocate memory for the serialized block
	m_pSerializedData = (unsigned char*) malloc(_lLengthData * sizeof(unsigned char));
	m_bSerializedDataAllocated = true;
	memcpy(m_pSerializedData, _pSerializedBuffer, _lLengthData);

	// deserialize
	Deserialize();
}
Serialization::SerializedItem::~SerializedItem()
{
	if(m_pValue != NULL) 
	{
		free(m_pValue);
	}
	if(true == m_bSerializedDataAllocated)
	{
		if(NULL != m_pSerializedData)
		{
			free(m_pSerializedData);
		}
	}
}
// -------------------------------------------------------------------------
/** internal function to check serializer type available */
long Serialization::SerializedItem::CheckAvailableType()
{
	if(m_lType == SI_TYPE_BOOL) return SI_OK;
	else if(m_lType == SI_TYPE_SHORT) return SI_OK;
	else if(m_lType == SI_TYPE_INT) return SI_OK;
	else if(m_lType == SI_TYPE_LONG) return SI_OK;
	else if(m_lType == SI_TYPE_FLOAT) return SI_OK;
	else if(m_lType == SI_TYPE_DOUBLE) return SI_OK;
	else if(m_lType == SI_TYPE_STRING) return SI_OK;
	else if(m_lType == SI_TYPE_STRUCT) return SI_OK;

	return SI_KO;
}
// -------------------------------------------------------------------------
/** fonction to serialize data */
long Serialization::SerializedItem::Serialize()
{
	int iIndexCpy = 0;

	// calculate size of data block
	m_lSerializedDataLen = sizeof(long) + sizeof(long) + m_lLengthItem;

	// allocate block
	m_pSerializedData = (unsigned char*)malloc(m_lSerializedDataLen * sizeof(unsigned char));

	memcpy(m_pSerializedData + iIndexCpy, &m_lType, sizeof(long));
	iIndexCpy += sizeof(long);
	memcpy(m_pSerializedData + iIndexCpy, &m_lLengthItem, sizeof(long));
	iIndexCpy += sizeof(long);
	memcpy(m_pSerializedData + iIndexCpy, m_pValue, m_lLengthItem);
	iIndexCpy += m_lLengthItem;

	m_lSerializedDataLen = iIndexCpy;
	return SI_OK;
}
// -------------------------------------------------------------------------
/** function to deserialize data */
long Serialization::SerializedItem::Deserialize()
{
	int iIndexCpy = 0;

	memcpy(&m_lType, m_pSerializedData + iIndexCpy, sizeof(long));
	iIndexCpy += sizeof(long);
	
	// update params only if available params
	if(CheckAvailableType() == SI_OK)
	{
		memcpy(&m_lLengthItem, m_pSerializedData + iIndexCpy, sizeof(long));
		iIndexCpy += sizeof(long);

		// allocate size in memory
		m_pValue = malloc(m_lLengthItem);
		memcpy(m_pValue, m_pSerializedData + iIndexCpy, m_lLengthItem);
		iIndexCpy += m_lLengthItem;
	}

	return SI_OK;
}
// -------------------------------------------------------------------------
/** get the the type of data */
long Serialization::SerializedItem::getType()
{
	return m_lType;
}
// -------------------------------------------------------------------------
/** get the length of data */
long Serialization::SerializedItem::getLength()
{
	return m_lLengthItem;
}
// -------------------------------------------------------------------------
/** get pointer on data */
void * Serialization::SerializedItem::getPointerValue()
{
	return m_pValue;
}
// -------------------------------------------------------------------------
/** Serialize item */
void * Serialization::SerializedItem::getSerializedData()
{
	return (void*)m_pSerializedData;
}
// -------------------------------------------------------------------------
/** Serialize item length */
long Serialization::SerializedItem::getSerializedDataLen()
{
	return m_lSerializedDataLen;
}
// -------------------------------------------------------------------------