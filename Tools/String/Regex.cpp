
#include "Regex_Helper.h"

#include <regex>
#include <iostream>

// ----------------------------------------------------------------------
#ifndef BUILD_WITHOUT_STD_REGEX
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
#else	// BUILD_WITHOUT_STD_REGEX
bool Tools::Regex::show_match(std::string const &/*s*/, std::string const &/*r*/)
{
	return false;
}
#endif	// BUILD_WITHOUT_STD_REGEX
// --------------------------------------------------------
bool Tools::Regex::match_ipV4adress(std::string const & s)
{
	std::regex pattern("\\b(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\."
           "(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\."
           "(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\."
           "(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\b");
#ifndef BUILD_WITHOUT_STD_REGEX
	return show_match(s, pattern);
#else
	return false;
#endif
}
// ----------------------------------------------------------------------
bool Tools::Regex::match_ipv6adress(std::string const & s )
{
  std::string ipv6 = 
    "("
	"([0-9a-fA-F]{1,4}:){7,7}[0-9a-fA-F]{1,4}|"				// 1:2:3:4:5:6:7:8
	"([0-9a-fA-F]{1,4}:){1,7}:|"							// 1::                              1:2:3:4:5:6:7::
	"([0-9a-fA-F]{1,4}:){1,6}:[0-9a-fA-F]{1,4}|"			// 1::8             1:2:3:4:5:6::8  1:2:3:4:5:6::8
	"([0-9a-fA-F]{1,4}:){1,5}(:[0-9a-fA-F]{1,4}){1,2}|"		// 1::7:8           1:2:3:4:5::7:8  1:2:3:4:5::8
	"([0-9a-fA-F]{1,4}:){1,4}(:[0-9a-fA-F]{1,4}){1,3}|"		// 1::6:7:8         1:2:3:4::6:7:8  1:2:3:4::8
	"([0-9a-fA-F]{1,4}:){1,3}(:[0-9a-fA-F]{1,4}){1,4}|"		// 1::5:6:7:8       1:2:3::5:6:7:8  1:2:3::8
	"([0-9a-fA-F]{1,4}:){1,2}(:[0-9a-fA-F]{1,4}){1,5}|"		// 1::4:5:6:7:8     1:2::4:5:6:7:8  1:2::8
	"[0-9a-fA-F]{1,4}:((:[0-9a-fA-F]{1,4}){1,6})|"			// 1::3:4:5:6:7:8   1::3:4:5:6:7:8  1::8  
	":((:[0-9a-fA-F]{1,4}){1,7}|:)|"						// ::2:3:4:5:6:7:8  ::2:3:4:5:6:7:8 ::8       ::     
	"fe80:(:[0-9a-fA-F]{0,4}){0,4}%[0-9a-zA-Z]{1,}|"		// fe80::7:8%eth0   fe80::7:8%1     (link-local IPv6 addresses with zone index)
	"::(ffff(:0{1,4}){0,1}:){0,1}"
	"((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\\.){3,3}"
	"(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])|"				// ::255.255.255.255   ::ffff:255.255.255.255  ::ffff:0:255.255.255.255  (IPv4-mapped IPv6 addresses and IPv4-translated addresses)
	"([0-9a-fA-F]{1,4}:){1,4}:"
	"((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\\.){3,3}"
	"(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])"				// 2001:db8:3:4::192.0.2.33  64:ff9b::192.0.2.33 (IPv4-Embedded IPv6 Address)
	")";
	// End of ipv6 string pattern.
#ifndef BUILD_WITHOUT_STD_REGEX
	std::regex ipv6_pattern(ipv6);
	return show_match(s, ipv6_pattern);
#else
	return false;
#endif
}
// ----------------------------------------------------------------------
