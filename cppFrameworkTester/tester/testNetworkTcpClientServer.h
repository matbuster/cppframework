#ifndef TESTER_NETWORK_TCP_CLIENTSERVER_H
#define TESTER_NETWORK_TCP_CLIENTSERVER_H

// -------------------------------------------------------------------
// defines tester
#define TEST_IP_ADRESS					"127.0.0.1"
#define TEST_PORT						3132
#define TEST_SIMPLE_DATA_CLIENT			"Hello Server, are you here?"
#define TEST_SIMPLE_DATA_SERVER			"Yes, Server I'm here, and I'm you're server"
#define TEST_SERVER_BIG_DATA_MESSAGE	"This is a repeated message for testing server big data num = %04i"
#define TEST_CLIENT_BIG_DATA_MESSAGE	"This is a repeated message for testing client big data num = %04i"
#define TEST_SEP						":"
//
#define TEST_SIZE_BIG_DATA				10000
namespace Test{
	// -------------------------------------------------------------------
	int tester_network_tcp_connect_client_to_server();
	// -------------------------------------------------------------------
	int tester_network_tcp_send_message_client_to_server_no_allocation();
	// -------------------------------------------------------------------
	int tester_network_tcp_send_message_client_to_server_with_allocation();
	// -------------------------------------------------------------------
	int tester_network_tcp_send_message_client_to_server(bool bAllocate);
	// -------------------------------------------------------------------
	int tester_network_tcp_client_server();
	// -------------------------------------------------------------------
}
#endif /** TESTER_NETWORK_TCP_CLIENTSERVER_H */