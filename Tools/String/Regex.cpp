
#include "Regex_Helper.h"

#include <regex>
#include <iostream>

// ----------------------------------------------------------------------
bool Tools::Regex::show_match(std::string const &s, std::regex const &r) { 
    std::smatch match;
    if (std::regex_search(s, match, r)) {
     	return true;
	}
    else
	{
		return false;
	}
}
// --------------------------------------------------------
bool Tools::Regex::match_ipadress(std::string const &s)
{
	std::regex pattern("(\\d{1,3}(\\.\\d{1,3}){3})");
	return show_match(s, pattern);
}
// ----------------------------------------------------------------------