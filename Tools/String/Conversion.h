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

#include <string>
#include <iostream>
#include <clocale>
#include <locale>
#include <vector>

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

		/**! function to convert an input string from char array to a LPWSTR 
		 * @param in _pInBuffer input string buffer
		 * @param in _uiInputSize input size for string buffer to convert
		 * @param out _pConvertedData converted string
		 * @param out _iSizeConverted converted output buffer size
		 */
		long convert_char_array_to_LPWSTR(const char * _pInBuffer, unsigned int _uiInputSize, wchar_t * _pConvertedData, unsigned int * _iSizeConverted);
#endif // _WINDOWS

		/**! function to convert an input wstring to a string 
		 * @param in _wstInput input std::wstring
		 * @param out _stOutput output std::string
		 */
		long convert_std_wstring_to_std_string(std::wstring _wstInput, std::string * _stOutput);

	};
};

#endif // TOOLS_STRING_CONVERTION_H
