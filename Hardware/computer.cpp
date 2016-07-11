
#include "computer.h"
#include "../toolsconstant.h"

#ifdef WIN32
#include <windows.h>
#include "../Tools/String/Conversion.h"
#endif // WIN32

// -----------------------------------------------------------------
long Hardware::Computer::getComputerName(char * _pComputerName, unsigned int _iSizeBufferComputerName)
{
	if(NULL == _pComputerName)
	{
		return HAR_COMP_INVALID_PARAM;
	}

#ifdef WIN32

	DWORD dwTempSize = _iSizeBufferComputerName;
	wchar_t lpBuffer[STR_SHORT];

	memset(lpBuffer, 0x00, STR_SHORT);
	if(true == GetComputerName((LPWSTR)lpBuffer, &dwTempSize))
	{
		if(dwTempSize > _iSizeBufferComputerName)
		{
			return HAR_BUFFER_TOO_SMALL;
		}
		if(CONVERT_OK != Tools::String::convert_LPWSTR_to_char_array(lpBuffer, STR_SHORT, _pComputerName, _iSizeBufferComputerName))
		{
			return HAR_COMP_KO;
		}
	}
	else return HAR_COMP_KO;

#endif // WIN32

	return HAR_COMP_OK;
}
// -----------------------------------------------------------------
