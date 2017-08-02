
#include "Conversion.h"

#include <stdlib.h>

#ifdef _WINDOWS
// --------------------------------------------------------
long Tools::String::convert_LPWSTR_to_char_array(LPWSTR _pInBuffer, unsigned int /*_uiInputSize*/, char * _pConvertedData, unsigned int _iSizeConverted)
{
	if(NULL == _pInBuffer)
	{
		return CONVERT_INVALID_INPUT_PARAM;
	}

	wcstombs(_pConvertedData, _pInBuffer, _iSizeConverted);
	return CONVERT_OK;
}
// --------------------------------------------------------
long Tools::String::convert_char_array_to_LPWSTR(const char * _pInBuffer, unsigned int _uiInputSize, wchar_t * _pConvertedData, unsigned int * _iSizeConverted)
{
	if(NULL == _iSizeConverted)
	{
		return CONVERT_INVALID_INPUT_PARAM;
	}
	if(NULL == _pInBuffer)
	{
		*_iSizeConverted = 0;
		return CONVERT_INVALID_INPUT_PARAM;
	}
	if(NULL == _pConvertedData)
	{
		*_iSizeConverted = 0;
		return CONVERT_INVALID_INPUT_PARAM;
	}

	std::wstring wc( _uiInputSize, L'#' );
	mbstowcs( &wc[0], _pInBuffer, _uiInputSize );

	wcscpy(_pConvertedData, &wc[0]);

	*_iSizeConverted = wc.length();
	return CONVERT_OK;
}
// --------------------------------------------------------
long Tools::String::convert_std_wstring_to_std_string(std::wstring _wstInput, std::string * _stOutput)
{
	if(NULL == _stOutput)
	{
		return CONVERT_INVALID_INPUT_PARAM;
	}

	const std::locale locale("");
	typedef std::codecvt<wchar_t, char, std::mbstate_t> converter_type;
	const converter_type& converter = std::use_facet<converter_type>(locale);
	std::vector<char> to(_wstInput.length() * converter.max_length());
	std::mbstate_t state;
	const wchar_t* from_next;
	char* to_next;

	const converter_type::result result = converter.out(state, _wstInput.data(), _wstInput.data() + _wstInput.length(), from_next, &to[0], &to[0] + to.size(), to_next);
	if (result == converter_type::ok || result == converter_type::noconv) {

		const std::string s(&to[0], to_next);
		//std::cout <<"std::string =     "<<s<<std::endl;
		_stOutput->assign(s.c_str(), s.length());
	}

	return CONVERT_OK;
}
// --------------------------------------------------------
#endif // _WINDOWS

