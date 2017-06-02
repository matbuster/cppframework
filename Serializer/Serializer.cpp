/**
 * \file 		Serializer.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */
 
#include "Serializer.h"
#include "SerializeBool.h"
#include "SerializeShort.h"
#include "SerializeInt.h"
#include "SerializeLong.h"
#include "SerializeFloat.h"
#include "SerializeDouble.h"
#include "SerializeString.h"

#include "EnumSerializerDetection.h"

#include <string>

// ----------------------------------------------------------------------
/** main constructor and destructor of the class */
Serialization::Serializer::Serializer()
{
	m_list = new Collection::List<SerializedItem * >();
	m_pSerializedData = NULL;
	m_ulSerializedDataLen = 0;
}
Serialization::Serializer::~Serializer()
{
	if(NULL != m_pSerializedData)
	{
		free(m_pSerializedData);
	}
	delete m_list;
}
// ----------------------------------------------------------------------
unsigned long Serialization::Serializer::getSerilizedDataLenEstimation()
{
	unsigned long ulEstimationLen = 0;
	for(int i = 0; i< m_list->Count(); i++) 
	{
		SerializedItem * _item = m_list->getItem(i);
		ulEstimationLen += _item->getSerializedDataLen();
	}
	return ulEstimationLen;
}
// ----------------------------------------------------------------------
/** function to add an item to the Serializer */
void Serialization::Serializer::AddItem(SerializedItem * item)
{
	m_list->Add(item);
}
// ----------------------------------------------------------------------
/** clear all the items inserted in the serializer */
void Serialization::Serializer::ClearItems()
{
	// clear all serialized object
	for(int i = 0; i< m_list->Count(); i++) 
	{
		SerializedItem * _item = m_list->getItem(i);
		if(NULL !=_item)
		{
			delete _item;
		}
	}
	m_list->Clear();
}
// ----------------------------------------------------------------------
/** function to serialize data */
long Serialization::Serializer::Serialize()
{
	int iIndexCpy = 0;

	// test if mem is already allocated, in this case clear it
	if(m_ulSerializedDataLen > 0)
	{
		memset(m_pSerializedData, 0x00, m_ulSerializedDataLen);
	}

	// realloc serilized data
	unsigned long ulExpedSize = getSerilizedDataLenEstimation();
	if(ulExpedSize != m_ulSerializedDataLen)
	{
		m_pSerializedData = (unsigned char*)realloc(m_pSerializedData, ulExpedSize);
		m_ulSerializedDataLen = ulExpedSize;
	}
	
	// serilize object
	for(int i = 0; i< m_list->Count(); i++) 
	{
		SerializedItem * _item = m_list->getItem(i);
		memcpy(m_pSerializedData + iIndexCpy, _item->getSerializedData(), _item->getSerializedDataLen());
		iIndexCpy += _item->getSerializedDataLen();
	}
	m_ulSerializedDataLen = iIndexCpy;
	if(m_ulSerializedDataLen != ulExpedSize)
	{
		return SERIALIZER_WRONG_SIZE_SIRIALIZED;
	}

	return SERIALIZER_OK;
}
// ----------------------------------------------------------------------
/** function to get serialized data */
unsigned char * Serialization::Serializer::getSerializedData()
{
	return m_pSerializedData;
}
// ----------------------------------------------------------------------
/** function to get the serialized data len */
long Serialization::Serializer::getSerializeDataLen()
{
	return m_ulSerializedDataLen;
}
// ----------------------------------------------------------------------
int Serialization::Serializer::getItemCount()
{
	return m_list->Count();
}
// ----------------------------------------------------------------------
Serialization::SerializedItem * Serialization::Serializer::getItemAt(int index)
{
	if(index < 0 || index > getItemCount())
	{
		return NULL;
	}
	SerializedItem * _item = m_list->getItem(index);
	return _item;
}
// ----------------------------------------------------------------------
/** function to deserialize a buffer */
long Serialization::Serializer::Deserialize(unsigned char * _pSerializedBuffer, long _lSerializeDataLen)
{
	// need to fill items list, clear it
	this->ClearItems();

	// loop on the serialized input buffer
	EnumSerializerDetection detection = initialized;
	unsigned long ulIndexCopy = 0;
	long lCurrentTagId = 0;
	long lCurrentLength = 0;
	while(detection != end)
	{
		if(detection == initialized
			|| detection == detectTag)
		{
			// detection part for TAG
			lCurrentTagId = 0;
			memcpy(&lCurrentTagId, _pSerializedBuffer + ulIndexCopy, sizeof(long));
			// tag compare
			if(SI_TYPE_BOOL != lCurrentTagId
				&& SI_TYPE_SHORT != lCurrentTagId
				&& SI_TYPE_INT != lCurrentTagId
				&& SI_TYPE_LONG != lCurrentTagId
				&& SI_TYPE_FLOAT != lCurrentTagId
				&& SI_TYPE_DOUBLE != lCurrentTagId
				&& SI_TYPE_STRING != lCurrentTagId
				&& SI_TYPE_STRUCT != lCurrentTagId
				&& SI_TYPE_OBJECT != lCurrentTagId
				)
			{
				detection = lost;
				return SERIALIZER_DESER_LOST;
			}

			// shift the current index
			ulIndexCopy += sizeof(long);
			detection = detectSize;
		}
		else if(detection == detectSize)
		{
			lCurrentLength = 0;
			memcpy(&lCurrentLength, _pSerializedBuffer + ulIndexCopy, sizeof(long));
			if(lCurrentLength <= 0)
			{
				detection = lost;
				return SERIALIZER_DESER_LOST;
			}

			// shift the current index
			ulIndexCopy += sizeof(long);
			detection = detectBuffer;
		}
		else if(detection == detectBuffer)
		{
			char * pBuffer;
			pBuffer = (char*)malloc(lCurrentLength * sizeof(char));
			memset(pBuffer, 0x00, lCurrentLength);
			memcpy(pBuffer, _pSerializedBuffer + ulIndexCopy, lCurrentLength);

			// tag compare
			Serialization::SerializedItem * currItem = NULL;
			if(SI_TYPE_BOOL == lCurrentTagId)
			{
				bool bTemp = false;
				memcpy(&bTemp, pBuffer, sizeof(bool));
				currItem = new Serialization::SerializedBool(bTemp);
			}
			else if(SI_TYPE_SHORT == lCurrentTagId)
			{
				short sTemp = 0;
				memcpy(&sTemp, pBuffer, sizeof(short));
				currItem = new Serialization::SerializedShort(sTemp);
			}
			else if(SI_TYPE_INT == lCurrentTagId)
			{
				int iTemp = 0;
				memcpy(&iTemp, pBuffer, sizeof(int));
				currItem = new Serialization::SerializeInt(iTemp);
			}
			else if(SI_TYPE_LONG == lCurrentTagId)
			{
				long lTemp = 0;
				memcpy(&lTemp, pBuffer, sizeof(long));
				currItem = new Serialization::SerializedLong(lTemp);
			}
			else if(SI_TYPE_FLOAT == lCurrentTagId)
			{
				float fTemp = 0.0;
				memcpy(&fTemp, pBuffer, sizeof(float));
				currItem = new Serialization::SerializeFloat(fTemp);
			}
			else if(SI_TYPE_DOUBLE == lCurrentTagId)
			{
				double dTemp = 0.0;
				memcpy(&dTemp, pBuffer, sizeof(double));
				currItem = new Serialization::SerializeDouble(dTemp);
			}
			else if(SI_TYPE_STRING == lCurrentTagId)
			{
				currItem = new Serialization::SerializeString(pBuffer, lCurrentLength);
			}
			else if(SI_TYPE_STRUCT == lCurrentTagId)
			{
				// TO BE IMPLEMENTED
			}
			else if(SI_TYPE_OBJECT == lCurrentTagId)
			{
				// TO BE IMPLEMENTED
			} 
			else
			{
				detection = lost;
			}
			free(pBuffer);
			ulIndexCopy += lCurrentLength;

			if(detection == lost)
			{
				return SERIALIZER_DESER_LOST;
			}

			this->AddItem(currItem);
			if((long)ulIndexCopy >= _lSerializeDataLen)
			{
				detection = end;
			}
			else 
			{
				detection = detectTag;
			}
		}
	}

	return SERIALIZER_OK;
}
// ----------------------------------------------------------------------

