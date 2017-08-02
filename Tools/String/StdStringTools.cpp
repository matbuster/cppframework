
#include "StdStringTools.h"

// -----------------------------------------------------------------------------------------
bool Tools::String::StringSplit(std::list<std::string> * _pOutResult, std::string _strInputString, std::string _strDelimiter)
{
	if(NULL == _pOutResult)
	{
		return false;
	}

	std::string sTemp(_strInputString);
	
	size_t pos = 0;
	std::string token;
	while ((pos = sTemp.find(_strDelimiter)) != std::string::npos) {
		token = sTemp.substr(0, pos);
		_pOutResult->push_back(token);
		sTemp.erase(0, pos + _strDelimiter.length());
	}

	_pOutResult->push_back(sTemp);
	return true;
}
// -----------------------------------------------------------------------------------------
