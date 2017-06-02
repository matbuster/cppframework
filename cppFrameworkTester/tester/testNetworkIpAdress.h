#ifndef TESTER_NETWORK_IPADRESS_H
#define TESTER_NETWORK_IPADRESS_H

// -------------------------------------------------------------------
// defines tester
#define TEST_IPV4_MATCH_01	"127.0.0.1"
#define TEST_IPV4_MATCH_02	"192.168.1.1"
#define TEST_IPV4_MATCH_03	"192.168.10.144"
#define TEST_IPV4_MATCH_04	"192.168.122.11"

#define TEST_IPV4_WRONG_01	"192.16"
#define TEST_IPV4_WRONG_02	"1a2.1b8.1v2.11"
#define TEST_IPV4_WRONG_03	"azerty"
#define TEST_IPV4_WRONG_04	"357.000.0.11"
#define TEST_IPV4_WRONG_05	"35.357.0.11"
#define TEST_IPV4_WRONG_06	"44.000.357.11"
#define TEST_IPV4_WRONG_07	"37.000.0.357"

#define TEST_IPV6_MATCH_01	"2001:0db8:0000:0000:0000:ff00:0042:8329"
#define TEST_IPV6_MATCH_02	"2001:0db8::ff00:0042:8329"
#define TEST_IPV6_MATCH_03	"::1"

#define TEST_IPV6_WRONG_01	"ThisIsNotAIpV6"
#define TEST_IPV6_WRONG_02	"2001:0db8:zfgt:0000:0000:ff00:0042:8329"

namespace Test{
	// -------------------------------------------------------------------
	int tester_network_ip_v4_adress();
	// -------------------------------------------------------------------
	int tester_network_ip_v6_adress();
	// -------------------------------------------------------------------
	int tester_network_ip_adress();
	// -------------------------------------------------------------------
}
#endif /** TESTER_NETWORK_IPADRESS_H */