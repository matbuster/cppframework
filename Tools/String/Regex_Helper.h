#ifndef TOOLS_STRING_REGEX_H
#define TOOLS_STRING_REGEX_H

#define REGEX_IP_ADRESS		"(\\d{1,3}(\\.\\d{1,3}){3})"

// TODO_MAT : 2017/08/02 PAT build problem with std::regex
// #define BUILD_WITHOUT_STD_REGEX

#include <string>
#include <regex>

using namespace std;

namespace Tools {
	
	namespace Regex{
	
#ifndef BUILD_WITHOUT_STD_REGEX
		// --------------------------------------------------------
		/** function to check if the input string format match 
		 * with the regex.
		 * \param [in] s input string
		 * \param [in] regex input string corresponding to the regex
		 * \return true if match, false if not
		 */
		bool show_match(std::string const &s, std::regex const &r);
#else // #ifndef BUILD_WITHOUT_STD_REGEX
		bool show_match(std::string const &s, std::string const &r);
#endif // BUILD_WITHOUT_STD_REGEX
		// --------------------------------------------------------
		/** function to match an ip adress
		 * \param [in] s input ipv4 string
		 * \return true if match, false if not
		 */
		bool match_ipV4adress(std::string const &s);

		// --------------------------------------------------------
		/**! function to mach an ipv6 adress
		 * \param [in] s input ipv6 string
		 * \return true if match, false if not
		 */
		bool match_ipv6adress(std::string const &s);
	};
	
};

#endif // TOOLS_STRING_REGEX_H