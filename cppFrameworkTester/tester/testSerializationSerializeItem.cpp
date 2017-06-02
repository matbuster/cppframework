
#include "testSerializationSerializeItem.h"
#include "cppFrameworkTesterDefines.h"
#include "TesterReport.h"

// -------------------------------------------------------------------
// include framework Galitt
#include "toolsconstant.h"
#include "Serializer/SerializeLong.h"
#include "Serializer/SerializeBool.h"
#include "Serializer/SerializeShort.h"
#include "Serializer/SerializeInt.h"
#include "Serializer/SerializeFloat.h"
#include "Serializer/SerializeDouble.h"
#include "Serializer/SerializeString.h"
#include "Serializer/Serializer.h"

#include "Math/Math.h"

// -------------------------------------------------------------------
// include cpp
#include <stdio.h>
#include <string.h>

// ---------------------------------------------------
#define TESTER_LONG_INPUT_VALUE					123456
#define TESTER_SHORT_INPUT_VALUE				42
#define TESTER_INT_INPUT_VALUE					-1982
#define TESTER_FLOAT_INPUT_VALUE				-128.3287467
#define TESTER_DOUBLE_INPUT_VALUE				123456.2135484152
#define TESTER_STRING_INPUT_VALUE				"This is a test for string serialization"
// Len
#define TESTER_LONG_SERIT_EXPEXTED_LEN			12
#define TESTER_BOOL_SERIT_EXPEXTED_LEN			9
#define TESTER_SHORT_SERIT_EXPEXTED_LEN			10
#define TESTER_INT_SERIT_EXPEXTED_LEN			12
#define TESTER_FLOAT_SERIT_EXPEXTED_LEN			12
#define TESTER_DOUBLE_SERIT_EXPEXTED_LEN		16
#define TESTER_SERIALIZER_EXPECTED_LEN			80
// ---------------------------------------------------
const unsigned char tester_long_serilization_expected[] = {0x04,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x40,0xe2,0x01,0x00};
const unsigned char tester_bool_serilization_expected[] = {0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01}; 
const unsigned char tester_short_serilization_expected[] = {0x02,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x2a,0x00};
const unsigned char tester_int_serilization_expected[] = {0x03,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x42,0xf8,0xff,0xff};
const unsigned char tester_float_serilization_expected[] = {0x05,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x29,0x54,0x00,0xc3};
const unsigned char tester_double_serilization_expected[] = {0x06,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x36,0xbe,0xb1,0x6a,0x03,0x24,0xfe,0x40};
const unsigned char tester_string_serilization_expected[] = {
	0x07,0x00,0x00,0x00,0x27,0x00,0x00,0x00,0x54,0x68,
	0x69,0x73,0x20,0x69,0x73,0x20,0x61,0x20,0x74,0x65,
	0x73,0x74,0x20,0x66,0x6f,0x72,0x20,0x73,0x74,0x72,
	0x69,0x6e,0x67,0x20,0x73,0x65,0x72,0x69,0x61,0x6c,
	0x69,0x7a,0x61,0x74,0x69,0x6f,0x6e
};
const unsigned char tester_serializer_01_result_expected[] = {
	0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x03,
	0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x42,0xf8,0xff,
	0xff,0x04,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x40,
	0xe2,0x01,0x00,0x07,0x00,0x00,0x00,0x27,0x00,0x00,
	0x00,0x54,0x68,0x69,0x73,0x20,0x69,0x73,0x20,0x61,
	0x20,0x74,0x65,0x73,0x74,0x20,0x66,0x6f,0x72,0x20,
	0x73,0x74,0x72,0x69,0x6e,0x67,0x20,0x73,0x65,0x72,
	0x69,0x61,0x6c,0x69,0x7a,0x61,0x74,0x69,0x6f,0x6e
};
// ---------------------------------------------------
int Test::tester_serialization_serialize_bool()
{
	int iResultTest = TEST_OK;
	unsigned char * pSerializedBlock;

	Serialization::SerializedBool * sBool = new Serialization::SerializedBool(true);
	bool bValue = sBool->getValue();
	if(true != bValue)
	{
		iResultTest = TEST_KO;
		printf("sBool->getValue() : FAILED");
	}
	long lDataLen = sBool->getSerializedDataLen();
	if(TESTER_BOOL_SERIT_EXPEXTED_LEN != lDataLen)
	{
		iResultTest = TEST_KO;
		printf("sBool->getSerializedDataLen() : FAILED");
	}
	pSerializedBlock = (unsigned char * )sBool->getSerializedData();
	if(0 != memcmp(pSerializedBlock, tester_bool_serilization_expected, lDataLen))
	{
		iResultTest = TEST_KO;
		printf("sBool->getSerializedData() : FAILED");
	}
	// test deserialization
	Serialization::SerializedBool * sDeserBool = new Serialization::SerializedBool((unsigned char*)sBool->getSerializedData(), sBool->getSerializedDataLen());
	if(true != sDeserBool->getValue())
	{
		iResultTest = TEST_KO;
		printf("sDeserBool->getValue() : FAILED");
	}
	if(SI_TYPE_BOOL != sDeserBool->getType())
	{
		iResultTest = TEST_KO;
		printf("sDeserBool->getType() : FAILED");
	}

	delete sDeserBool;
	delete sBool;

	return TEST_OK;
}
// ---------------------------------------------------
int Test::tester_serialization_serialize_short()
{
	int iResultTest = TEST_OK;
	unsigned char * pSerializedBlock;

	Serialization::SerializedShort * sShort = new Serialization::SerializedShort(TESTER_SHORT_INPUT_VALUE);
	short sValue = sShort->getValue();
	if(TESTER_SHORT_INPUT_VALUE != sValue)
	{
		iResultTest = TEST_KO;
		printf("sShort->getValue() : FAILED");
	}
	long lDataLen = sShort->getSerializedDataLen();
	if(TESTER_SHORT_SERIT_EXPEXTED_LEN != lDataLen)
	{
		iResultTest = TEST_KO;
		printf("sShort->getSerializedDataLen() : FAILED");
	}
	pSerializedBlock = (unsigned char * )sShort->getSerializedData();
	if(0 != memcmp(pSerializedBlock, tester_short_serilization_expected, lDataLen))
	{
		iResultTest = TEST_KO;
		printf("sShort->getSerializedData() : FAILED");
	}

	// test deserialization
	Serialization::SerializedShort * sDeserShort = new Serialization::SerializedShort((unsigned char*)sShort->getSerializedData(), sShort->getSerializedDataLen());
	if(TESTER_SHORT_INPUT_VALUE != sDeserShort->getValue())
	{
		iResultTest = TEST_KO;
		printf("sDeserShort->getValue() : FAILED");
	}
	if(SI_TYPE_SHORT != sDeserShort->getType())
	{
		iResultTest = TEST_KO;
		printf("sDeserShort->getType() : FAILED");
	}

	delete sDeserShort;
	delete sShort;

	return iResultTest;
}
// ---------------------------------------------------
int Test::tester_serialization_serialize_int()
{
	int iResultTest = TEST_OK;
	unsigned char * pSerializedBlock;

	Serialization::SerializeInt * sInt = new Serialization::SerializeInt(TESTER_INT_INPUT_VALUE);
	int sValue = sInt->getValue();
	if(TESTER_INT_INPUT_VALUE != sValue)
	{
		iResultTest = TEST_KO;
		printf("sInt->getValue() : FAILED");
	}
	long lDataLen = sInt->getSerializedDataLen();
	if(TESTER_INT_SERIT_EXPEXTED_LEN != lDataLen)
	{
		iResultTest = TEST_KO;
		printf("sInt->getSerializedDataLen() : FAILED");
	}
	pSerializedBlock = (unsigned char * )sInt->getSerializedData();
	if(0 != memcmp(pSerializedBlock, tester_int_serilization_expected, lDataLen))
	{
		iResultTest = TEST_KO;
		printf("sInt->getSerializedData() : FAILED");
	}

	// test deserialization
	Serialization::SerializeInt * sDeserInt = new Serialization::SerializeInt((unsigned char*)sInt->getSerializedData(), sInt->getSerializedDataLen());
	if(TESTER_INT_INPUT_VALUE != sDeserInt->getValue())
	{
		iResultTest = TEST_KO;
		printf("sDeserInt->getValue() : FAILED");
	}
	if(SI_TYPE_INT != sDeserInt->getType())
	{
		iResultTest = TEST_KO;
		printf("sDeserInt->getType() : FAILED");
	}

	delete sDeserInt;
	delete sInt;

	return iResultTest;
}
// ---------------------------------------------------
int Test::tester_serialization_serialize_float()
{
	int iResultTest = TEST_OK;
	unsigned char * pSerializedBlock;

	Serialization::SerializeFloat * sFloat = new Serialization::SerializeFloat((float)TESTER_FLOAT_INPUT_VALUE);
	float fValue = sFloat->getValue();

	float fValueSeriaRounded = Math::Round(sFloat->getValue(), 5);
	float fValueInputRounded = Math::Round((float)TESTER_FLOAT_INPUT_VALUE, 5);

	if(fValueSeriaRounded != fValueInputRounded)
	{
		iResultTest = TEST_KO;
		printf("sFloat->getValue() : FAILED");
	}
	long lDataLen = sFloat->getSerializedDataLen();
	if(TESTER_FLOAT_SERIT_EXPEXTED_LEN != lDataLen)
	{
		iResultTest = TEST_KO;
		printf("sFloat->getSerializedDataLen() : FAILED");
	}
	pSerializedBlock = (unsigned char * )sFloat->getSerializedData();
	if(0 != memcmp(pSerializedBlock, tester_float_serilization_expected, lDataLen))
	{
		iResultTest = TEST_KO;
		printf("sFloat->getSerializedData() : FAILED");
	}

	// test deserialization
	Serialization::SerializeFloat * sDeserFloat = new Serialization::SerializeFloat((unsigned char*)sFloat->getSerializedData(), sFloat->getSerializedDataLen());

	float fDeserValue = Math::Round((float)sDeserFloat->getValue(), 5);
	if(fValueInputRounded != fDeserValue)
	{
		iResultTest = TEST_KO;
		printf("sDeserFloat->getValue() : FAILED");
	}
	if(SI_TYPE_FLOAT != sDeserFloat->getType())
	{
		iResultTest = TEST_KO;
		printf("sDeserFloat->getType() : FAILED");
	}

	delete sDeserFloat;
	delete sFloat;

	return iResultTest;
}
// ---------------------------------------------------
int Test::tester_serialization_serialize_double()
{
	int iResultTest = TEST_OK;
	unsigned char * pSerializedBlock;

	Serialization::SerializeDouble * sDouble = new Serialization::SerializeDouble((double)TESTER_DOUBLE_INPUT_VALUE);
	double dValue = sDouble->getValue();

	double dValueSeriaRounded = Math::Round(sDouble->getValue(), 5);
	double dValueInputRounded = Math::Round((double)TESTER_DOUBLE_INPUT_VALUE, 5);

	if(dValueSeriaRounded != dValueInputRounded)
	{
		iResultTest = TEST_KO;
		printf("sDouble->getValue() : FAILED");
	}
	long lDataLen = sDouble->getSerializedDataLen();
	if(TESTER_DOUBLE_SERIT_EXPEXTED_LEN != lDataLen)
	{
		iResultTest = TEST_KO;
		printf("sDouble->getSerializedDataLen() : FAILED");
	}
	pSerializedBlock = (unsigned char * )sDouble->getSerializedData();
	if(0 != memcmp(pSerializedBlock, tester_double_serilization_expected, lDataLen))
	{
		iResultTest = TEST_KO;
		printf("sDouble->getSerializedData() : FAILED");
	}

	// test deserialization
	Serialization::SerializeDouble * sDeserDouble = new Serialization::SerializeDouble((unsigned char*)sDouble->getSerializedData(), sDouble->getSerializedDataLen());

	double dDeserValue = Math::Round((double)sDeserDouble->getValue(), 5);
	if(dValueInputRounded != dDeserValue)
	{
		iResultTest = TEST_KO;
		printf("sDeserFloat->getValue() : FAILED");
	}
	if(SI_TYPE_DOUBLE != sDeserDouble->getType())
	{
		iResultTest = TEST_KO;
		printf("sDeserFloat->getType() : FAILED");
	}

	delete sDeserDouble;
	delete sDouble;

	return iResultTest;
}
// ---------------------------------------------------
int Test::tester_serialization_serialize_long()
{
	int iResultTest = TEST_OK;
	unsigned char * pSerializedBlock;

	// test serialization
	Serialization::SerializedLong * sLong = new Serialization::SerializedLong(TESTER_LONG_INPUT_VALUE);
	long lValue = sLong->getValue();
	if(TESTER_LONG_INPUT_VALUE != lValue)
	{
		iResultTest = TEST_KO;
		printf("sLong->getValue() : FAILED");
	}
	long lDataLen = sLong->getSerializedDataLen();
	if(TESTER_LONG_SERIT_EXPEXTED_LEN != lDataLen)
	{
		iResultTest = TEST_KO;
		printf("sLong->getSerializedDataLen() : FAILED");
	}
	pSerializedBlock = (unsigned char * )sLong->getSerializedData();
	if(0 != memcmp(pSerializedBlock, tester_long_serilization_expected, lDataLen))
	{
		iResultTest = TEST_KO;
		printf("sLong->getSerializedData() : FAILED");
	}

	// test deserialization
	Serialization::SerializedLong * sDeserLong = new Serialization::SerializedLong((unsigned char*)sLong->getSerializedData(), sLong->getSerializedDataLen());
	if(TESTER_LONG_INPUT_VALUE != sDeserLong->getValue())
	{
		iResultTest = TEST_KO;
		printf("sDeserLong->getValue() : FAILED");
	}
	if(SI_TYPE_LONG != sDeserLong->getType())
	{
		iResultTest = TEST_KO;
		printf("sDeserLong->getType() : FAILED");
	}

	delete sDeserLong;
	delete sLong;

	return TEST_OK;
}
// ---------------------------------------------------
int Test::tester_serialization_serialize_string()
{
	int iResultTest = TEST_OK;
	unsigned char * pSerializedBlock;

	// test serialization
	Serialization::SerializeString * sString = new Serialization::SerializeString(TESTER_STRING_INPUT_VALUE);
	unsigned char * pValue = sString->getValue();
	if(0 != memcmp(pValue, TESTER_STRING_INPUT_VALUE, sizeof(TESTER_STRING_INPUT_VALUE) - 1))
	{
		iResultTest = TEST_KO;
		printf("sString->getValue() : FAILED");
	}
	long lDataLen = sString->getSerializedDataLen();
	long lExpectedLen = (4 + 4 + sizeof(TESTER_STRING_INPUT_VALUE)-1);
	if( lExpectedLen != lDataLen)
	{
		iResultTest = TEST_KO;
		printf("sLong->getSerializedDataLen() : FAILED");
	}
	pSerializedBlock = (unsigned char*)sString->getSerializedData();
	if(0 != memcmp(pSerializedBlock, tester_string_serilization_expected, lExpectedLen))
	{
		iResultTest = TEST_KO;
		printf("sLong->getSerializedData() : FAILED");
	}
	
	// test deserialization
	Serialization::SerializeString * sDeserString = new Serialization::SerializeString((unsigned char*)sString->getSerializedData(), sString->getSerializedDataLen());
	long lLength = sDeserString->getLength();
	if(lLength <= 0) 
	{
		iResultTest = TEST_KO;
		printf("sDeserString deserialization failed: FAILED");
		return TEST_KO;
	}
	if(0 != memcmp(sDeserString->getValue(), TESTER_STRING_INPUT_VALUE, sizeof(TESTER_STRING_INPUT_VALUE)-1))
	{
		iResultTest = TEST_KO;
		printf("sDeserString->getValue() : FAILED");
	}
	if(SI_TYPE_STRING != sDeserString->getType())
	{
		iResultTest = TEST_KO;
		printf("sDeserString->getType() : FAILED");
	}

	delete sDeserString;
	delete sString;

	return iResultTest;
}
// ---------------------------------------------------
int Test::tester_serialization_serializer()
{
	int iResultTest = TEST_OK;
	unsigned char * pSerializedData;
	
	// object for serialization
	Serialization::SerializedBool *		sBool = new Serialization::SerializedBool(true);
	Serialization::SerializeInt *		sInt = new Serialization::SerializeInt(TESTER_INT_INPUT_VALUE);
	Serialization::SerializedLong *		sLong = new Serialization::SerializedLong(TESTER_LONG_INPUT_VALUE);
	Serialization::SerializeString *	sString = new Serialization::SerializeString(TESTER_STRING_INPUT_VALUE);

	Serialization::Serializer * serializer = new Serialization::Serializer();
	serializer->AddItem(sBool);
	serializer->AddItem(sInt);
	serializer->AddItem(sLong);
	serializer->AddItem(sString);

	serializer->Serialize();
	if(TESTER_SERIALIZER_EXPECTED_LEN != serializer->getSerializeDataLen())
	{
		iResultTest = TEST_KO;
		printf("Serializer->getSerializeDataLen() : FAILED");
	}
	pSerializedData = serializer->getSerializedData();
	if(NULL == pSerializedData)
	{
		iResultTest = TEST_KO;
		printf("Serializer->getSerializedData() : FAILED");
	}
	if(0 != memcmp(pSerializedData, tester_serializer_01_result_expected, sizeof(tester_serializer_01_result_expected)))
	{
		iResultTest = TEST_KO;
		printf("Serializer->getSerializedData() : FAILED");
	}

	// testing deserilization
	Serialization::Serializer * deserializer = new Serialization::Serializer();
	deserializer->Deserialize(pSerializedData, serializer->getSerializeDataLen());
	if(4 != deserializer->getItemCount())
	{
		iResultTest = TEST_KO;
		printf("Deserialized counter on items : FAILED");
		return iResultTest;
	}

	for(int i = 0; i < deserializer->getItemCount(); i++)
	{
		Serialization::SerializedItem * item = deserializer->getItemAt(i);
		if(i==0)
		{
			if(SI_TYPE_BOOL != item->getType())
			{
				iResultTest = TEST_KO;
				printf("Deserialized getter on Serialized item Boolean : FAILED");
				break;
			}
			bool bDeserBoolean = ((Serialization::SerializedBool*)(item))->getValue();
			if(!bDeserBoolean)
			{
				iResultTest = TEST_KO;
				printf("Deserialized getter on SerializedBool value Boolean : FAILED");
				break;
			}
		}
		else if(i==1)
		{
			if(SI_TYPE_INT != item->getType())
			{
				iResultTest = TEST_KO;
				printf("Deserialized getter on Serialized item Integer : FAILED");
				break;
			}
			int iDeserInt = ((Serialization::SerializeInt*)(item))->getValue();
			if(iDeserInt != TESTER_INT_INPUT_VALUE)
			{
				iResultTest = TEST_KO;
				printf("Deserialized getter on SerializedBool value Integer : FAILED");
				break;
			}
		}
		else if(i==2)
		{
			if(SI_TYPE_LONG != item->getType())
			{
				iResultTest = TEST_KO;
				printf("Deserialized getter on Serialized item Long : FAILED");
				break;
			}
			long lDeserLong = ((Serialization::SerializedLong*)(item))->getValue();
			if(lDeserLong != TESTER_LONG_INPUT_VALUE)
			{
				iResultTest = TEST_KO;
				printf("Deserialized getter on SerializedBool value Long : FAILED");
				break;
			}
		}
		else if(i==3)
		{
			if(SI_TYPE_STRING != item->getType())
			{
				iResultTest = TEST_KO;
				printf("Deserialized getter on Serialized item String : FAILED");
				break;
			}
			size_t deserItemLength = item->getLength(); 
			size_t testerSize = sizeof(TESTER_STRING_INPUT_VALUE) - 1;
			if(deserItemLength != testerSize)
			{
				iResultTest = TEST_KO;
				printf("Deserialized string wrong data length value: FAILED");
				break;
			}
			char * pTemString = (char*)malloc( item->getLength() * sizeof(char) );
			memcpy(pTemString, ((Serialization::SerializeString*)(item))->getValue(), item->getLength());
			if(0 != memcmp(pTemString, TESTER_STRING_INPUT_VALUE, deserItemLength))
			{
				iResultTest = TEST_KO;
				printf("Deserialized string and original string don't match: FAILED");
				free(pTemString);
				break;
			}
			free(pTemString);
		}
	}
	

	delete sString;
	delete sLong;
	delete sInt;
	delete sBool;

	delete serializer;
	delete deserializer;

	return iResultTest;
}
// ---------------------------------------------------
/**! generic test function to test all functionnalities associated
 * to the SerializeItem
 * \return errot code
 */
int Test::tester_serialization_serialize_item()
{
    int iReturnCode = TEST_OK;
    Test::TesterReport::getInstance()->printHeader("testing Item Serializer");
    

	iReturnCode = tester_serialization_serialize_long();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Serialization::Item", "tester_serialization_serialize_long()");
	iReturnCode = tester_serialization_serialize_bool();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Serialization::Item", "tester_serialization_serialize_bool()");
	iReturnCode = tester_serialization_serialize_short();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Serialization::Item", "tester_serialization_serialize_short()");
	iReturnCode = tester_serialization_serialize_int();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Serialization::Item", "tester_serialization_serialize_int()");
	iReturnCode = tester_serialization_serialize_double();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Serialization::Item", "tester_serialization_serialize_double()");
	iReturnCode = tester_serialization_serialize_string();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Serialization::Item", "tester_serialization_serialize_string()");
	iReturnCode = tester_serialization_serializer();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Serialization::Item", "tester_serialization_serializer()");

	return iReturnCode;
}
// ---------------------------------------------------
