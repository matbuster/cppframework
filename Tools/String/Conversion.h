#ifndef TOOLS_STRING_CONVERTION_H
#define TOOLS_STRING_CONVERTION_H

// ------------------------------------------------------
// convertion defines
#define CONVERT_OK							0
#define CONVERT_KO							1
#define CONVERT_INVALID_INPUT_PARAM			2

// ------------------------------------------------------
#ifdef _WINDOWS
#include <Windows.h>
#endif // _WINDOWS

namespace Tools {

	namespace String {

#ifdef _WINDOWS
		/**! function to convert an input string LPWSTR to a char array
		 * @param in _pInBuffer input string buffer
		 * @param in _uiInputSize input size for string buffer to convert
		 * @param out _pConvertedData converted string
		 * @param out _iSizeConverted converted output buffer size
		 */
		long convert_LPWSTR_to_char_array(LPWSTR _pInBuffer, unsigned int _uiInputSize, char * _pConvertedData, unsigned int _iSizeConverted);
#endif // _WINDOWS

	};
};

#endif // TOOLS_STRING_CONVERTION_H
