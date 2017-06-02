/**
 * \file 		SerializeItem.h
 * \date 		04/11/2015 
 * \author 		MAT
 */
 
#ifndef SERIALIZED_ITEM_H
#define SERIALIZED_ITEM_H

// -----------------------------------------------------------
// type definition
#define SI_TYPE_BOOL			0x00000001
#define SI_TYPE_SHORT			0x00000002
#define SI_TYPE_INT				0x00000003
#define SI_TYPE_LONG			0x00000004
#define SI_TYPE_FLOAT			0x00000005
#define SI_TYPE_DOUBLE			0x00000006
#define SI_TYPE_STRING			0x00000007
#define SI_TYPE_STRUCT			0x00000008
#define SI_TYPE_OBJECT			0x00000009

// -----------------------------------------------------------
// definition of serialized internal length
#define SI_SERIALIZED_BLOCK_LEN	1024
#define SI_OK					0
#define SI_KO					1

#include "toolsconstant.h"

namespace Serialization {

	class SerializedItem{
	
	private:
		/** buffer for the associated name */
		unsigned char m_pDataName[STR_TINY];
		/** type of the serialized item */
		long m_lType;
		/** length of the serialized item */
		long m_lLengthItem;
		/** value of the serialized item */
		void * m_pValue;
		/** serialized data value */
		unsigned char * m_pSerializedData;
		/** length of serialized data */
		unsigned long m_lSerializedDataLen;
		/** status of allocation of serialized data*/
		bool m_bSerializedDataAllocated;

		/** internal function to initialize data */
		void InitInternalData();
		/** internal function to check serializer type available */
		long CheckAvailableType();

	protected:
		/** fonction to serialize data */
		long Serialize();
		/** function to deserialize data */
		long Deserialize();
		/** get pointer on data */
		void * getPointerValue();

	public:
		/** constructor and destructor of the class */
		SerializedItem(long _lType, long _lLengthItem, void * pData);
		SerializedItem(unsigned char * _pSerializedBuffer, unsigned long  _lLengthData);
		virtual ~SerializedItem();
		/** get the the type of data */
		long getType();
		/** get the length of data */
		long getLength();
		/** Serialize item */
		void * getSerializedData();
		/** Serialize item length */
		long getSerializedDataLen();
	};
};

#endif /* SERIALIZED_ITEM_H */

