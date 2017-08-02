#ifndef STD_STRING_TOOLS_H
#define STD_STRING_TOOLS_H

#include <string>
#include <list>

namespace Tools {

	namespace String {

		// -----------------------------------------------------------------------------------------
		/** function to split an existing std::string into a decomposed list of std::string 
		 * \param [out] _pOutResult : list of result
		 * \param [in] _strInputString : string to split
		 * \param [in] _strDelimiter: split string
		 */
		bool StringSplit(std::list<std::string> * _pOutResult, std::string _strInputString, std::string _strDelimiter);

	};
};

#endif // STD_STRING_TOOLS_H