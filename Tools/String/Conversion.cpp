
#include "Conversion.h"

#include <stdlib.h>

#ifdef WIN32
long Tools::String::convert_LPWSTR_to_char_array(LPWSTR _pInBuffer, unsigned int _uiInputSize, char * _pConvertedData, unsigned int _iSizeConverted)
{
	if(NULL == _pInBuffer)
	{
		return CONVERT_INVALID_INPUT_PARAM;
	}

	wcstombs(_pConvertedData, _pInBuffer, _iSizeConverted);
	return CONVERT_OK;
}
#endif // WIN32

