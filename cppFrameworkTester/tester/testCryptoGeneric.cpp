
#include "testCryptoGeneric.h"
#include "cppFrameworkTesterDefines.h"

#include <stdio.h>
#include <cstring>

// include framework cpp
#include "Crypto/md5.h"
#include "Crypto/crc.h"
#include "Tools/String/StringTools.h"
#include "TesterReport.h"

#include <stdint.h>

#define CONST_TEST_STRING	"1234567890"
#include <stdio.h>

// ------------------------------------------------------------
int Test::tester_crypto_crc16()
{
    int iReturnCode = TEST_OK;

	unsigned char output[128];
	long lSize = 0;

	memset(output, 0x00, 128);
	Tools::String::StringToHexaBuffer(output, &lSize, CONST_TEST_STRING, sizeof(CONST_TEST_STRING)-1);

	unsigned short iValCrc16 = Crypto::getCRC16("123456789");
	if(0xBB3D != iValCrc16)
	{
		printf(">tester_crypto_crc16 CRC16 FAILED\r\n");
		return TEST_KO;
	}
	unsigned short iValCrc16Modbus = Crypto::getCRC16Modbus("123456789");
	if(0x4B37 != iValCrc16Modbus)
	{
		printf(">tester_crypto_crc16 CRC16Modbus FAILED\r\n");
		return TEST_KO;
	}
	unsigned short iValCrc16Dnp = Crypto::getCRC16Dnp("123456789");
	if(0x56A6 != iValCrc16Dnp)
	{
		printf(">tester_crypto_crc16 CRC16Dnp FAILED\r\n");
		return TEST_KO;
	}

	return iReturnCode;
}
// ------------------------------------------------------------
int Test::tester_crypto_md5()
{
    int iReturnCode = TEST_OK;
	std::string strMd5(Crypto::md5("calculate_my_crc"));
	std::string expected("97ef1b6c289c1b87907cda08d4658ec5");

	if(0 != expected.compare(strMd5))
	{
		printf(">tester_crypto_md5 FAILED\r\n");
		return TEST_KO;
	}

	return iReturnCode;
}
// ------------------------------------------------------------
int Test::tester_crypto()
{
    int iReturnCode = TEST_OK;
    Test::TesterReport::getInstance()->printHeader("testing Crypto");

	iReturnCode = tester_crypto_md5();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Crypto", "tester_crypto_md5()");
	iReturnCode = tester_crypto_crc16();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Crypto", "tester_crypto_crc16()");

	return iReturnCode;
}
// ------------------------------------------------------------