#ifndef TOOLS_STRING_REGEX_H
#define TOOLS_STRING_REGEX_H

#define REGEX_IP_ADRESS		"(\\d{1,3}(\\.\\d{1,3}){3})"

#include <string>
#include <regex>

namespace Tools {
	
	namespace Regex{
	
		// --------------------------------------------------------
		/** function to check if the input string format match 
		 * with the regex.
		 * @param in s input string
		 * @param in regex input string corresponding to the regex
		 * @return true if match, false if not
		 */
		bool show_match(std::string const &s, std::regex const &r);

		// --------------------------------------------------------
		/** function to match an ip adress
		 * @param in s input string
		 * @return true if match, false if not
		 */
		bool match_ipadress(std::string const &s);
	};
	
};

#endif // TOOLS_STRING_REGEX_H