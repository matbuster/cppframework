
#include "testNetworkTcpClientServer.h"
#include "cppFrameworkTesterDefines.h"
#include "TesterReport.h"

// -------------------------------------------------------------------
// include framework Galitt
#include "toolsconstant.h"
#include "Network/TcpClient.h"
#include "Network/TcpServer.h"
#include "Threading/Thread.h"
#include "Threading/ThreadPool.h"

#include <stdio.h>

// -------------------------------------------------------------------
typedef struct {
	
	/**! internal server pointer */
	Network::TCPServer * pServer;
	/**! internal state for allocation */
	bool bDataAllocation;

} Server_Internal_Tester;
// -------------------------------------------------------------------

// -------------------------------------------------------------------
// private function for testing client / server application
// -------------------------------------------------------------------
int feed_buffer_for_test(char * _pInputBuffer, int _iSizeBuffer)
{
	if(NULL == _pInputBuffer) 
	{
		return TEST_KO;
	}
	if(_iSizeBuffer < 0) 
	{
		return TEST_KO;
	}
	for(int i= 0; i < _iSizeBuffer; i++) 
	{
		_pInputBuffer[i] = (i % 255);
	}
	return TEST_OK;
}
// -------------------------------------------------------------------
THREAD_RETURN_VOID THREAD_CALLCONV server_sender_simple_message(THREAD_INPUT_PARAM lpThreadParameter)
{
	Threading::sPoolGarbagedItem * thItem = (Threading::sPoolGarbagedItem*)lpThreadParameter;
	Server_Internal_Tester * pInternalServerStruct = (Server_Internal_Tester *)thItem->pObject;
	Threading::Thread * serverThread = (Threading::Thread * )thItem->th;

	if(NULL != pInternalServerStruct->pServer)
	{
		int iSessionWork= 0;
		int iOutLenDataReceived = 0;
		char * pTempInputMessage;
		if(false == pInternalServerStruct->bDataAllocation)
		{
			pTempInputMessage = (char*)malloc(STR_LONG * sizeof(char));
		}

		// server accept
		int iReturnError = pInternalServerStruct->pServer->TCPaccept(&iSessionWork);
		if(TCP_SERVER_SUCCESS != iReturnError)
		{
			printf(">server_sender_simple_message : TCPaccept from server in thread FAILED!\r\n");
		}

		// server get incoming message and send the answer
		iReturnError = pInternalServerStruct->pServer->TCPReceive(iSessionWork, &pTempInputMessage, STR_LONG, &iOutLenDataReceived, pInternalServerStruct->bDataAllocation);
		if(TCP_SERVER_SUCCESS != iReturnError)
		{
			printf(">server_sender_simple_message : TCPReceive from server in thread FAILED!\r\n");
		}
		if(iOutLenDataReceived <= 0)
		{
			printf(">server_sender_simple_message : No data received on server side!\r\n");
		}
		if(0 != memcmp(pTempInputMessage, TEST_SIMPLE_DATA_CLIENT, sizeof(TEST_SIMPLE_DATA_CLIENT)))
		{
			printf(">server_sender_simple_message : Wrong message received from client in Thread Server!\r\n");
		}

		iReturnError = pInternalServerStruct->pServer->TCPSend(iSessionWork, TEST_SIMPLE_DATA_SERVER, sizeof(TEST_SIMPLE_DATA_SERVER));
		if(TCP_SERVER_SUCCESS != iReturnError)
		{
			printf(">server_sender_simple_message : TCPSend from server in thread FAILED!\r\n");
		}

		// server shutdown
		pInternalServerStruct->pServer->TCPshutdown(iSessionWork);
		free(pTempInputMessage);
	}

	// stopping the thread
	if(NULL != serverThread) serverThread->ThreadStop();
	return THREAD_RETURN_VAL;
}
// -------------------------------------------------------------------
THREAD_RETURN_VOID THREAD_CALLCONV server_sender_big_message(THREAD_INPUT_PARAM lpThreadParameter)
{
	Threading::sPoolGarbagedItem * thItem = (Threading::sPoolGarbagedItem*)lpThreadParameter;
	Server_Internal_Tester * pInternalServerStruct = (Server_Internal_Tester *)thItem->pObject;
	Threading::Thread * serverThread = (Threading::Thread * )thItem->th;

	if(NULL != pInternalServerStruct->pServer)
	{
		int iSessionWork= 0;
		int iOutLenDataReceived = 0;
		char * pTempInputMessage;
		char * pBufferCompare = NULL;

		// server accept
		int iReturnError = pInternalServerStruct->pServer->TCPaccept(&iSessionWork);
		if(TCP_SERVER_SUCCESS != iReturnError)
		{
			printf(">server_sender_simple_message : TCPaccept from server in thread FAILED!\r\n");
		}

		// server get incoming message and send the answer
		iReturnError = pInternalServerStruct->pServer->TCPReceive(iSessionWork, &pTempInputMessage, STR_LONG, &iOutLenDataReceived, pInternalServerStruct->bDataAllocation);
		if(TCP_SERVER_SUCCESS != iReturnError)
		{
			printf(">server_sender_simple_message : TCPReceive from server in thread FAILED!\r\n");
		}
		if(iOutLenDataReceived <= 0)
		{
			printf(">server_sender_simple_message : No data received on server side!\r\n");
		}

		// test data
		pBufferCompare = (char*)malloc(TEST_SIZE_BIG_DATA * sizeof(char));
		feed_buffer_for_test(pBufferCompare, TEST_SIZE_BIG_DATA);

		// check messages and possible errors
		if(TEST_SIZE_BIG_DATA != iOutLenDataReceived)
		{
			printf(">server_sender_simple_message : Expected size and received size is not the same!\r\n");
		}
		if(0 != memcmp(pBufferCompare, pTempInputMessage, TEST_SIZE_BIG_DATA))
		{
			printf(">server_sender_simple_message : Buffer received don't match!\r\n");
		}

		// send an answer and shutdown the connection
		iReturnError = pInternalServerStruct->pServer->TCPSend(iSessionWork, TEST_SIMPLE_DATA_SERVER, sizeof(TEST_SIMPLE_DATA_SERVER));
		if(TCP_SERVER_SUCCESS != iReturnError)
		{
			printf(">server_sender_simple_message : TCPSend from server in thread FAILED!\r\n");
		}

		// server shutdown
		pInternalServerStruct->pServer->TCPshutdown(iSessionWork);
		free(pBufferCompare);
		free(pTempInputMessage);
	}

	// stopping the thread
	if(NULL != serverThread) serverThread->ThreadStop();
	return THREAD_RETURN_VAL;
}
// -------------------------------------------------------------------
int create_client_server_connection(Network::TCPServer * _server, Network::TCPClient * _client)
{
	int iReturnValue = TEST_OK;
	if(NULL == _server || NULL == _client)
	{
		printf(">create_client_server_connection : input pointer for client or server are invalid.\r\n");
		return TEST_KO;
	}

	/////////////////////////////////////////////
	// Client / Server Creation
	//
	// create server connection 
	if(TCP_SERVER_SUCCESS != _server->TCPconnect(TEST_IP_ADRESS, TEST_PORT))
	{
		printf(">create_client_server_connection : FAILED when trying to connect to server.\r\n");
		iReturnValue = TEST_KO;
	}
	// create client connection
	if( TCP_OK != _client->TCPconnect(TEST_IP_ADRESS, TEST_PORT))
	{
		_server->TCPclose();
		printf(">create_client_server_connection : FAILED when trying to connect to client.\r\n");
		iReturnValue = TEST_KO;
	}
	return iReturnValue;
}
// -------------------------------------------------------------------
int close_client_server_connection(Network::TCPServer * _server, Network::TCPClient * _client)
{
	int iReturnValue = TEST_OK;
	if(NULL == _server || NULL == _client)
	{
		printf(">close_client_server_connection : input pointer for client or server are invalid.\r\n");
		return TEST_KO;
	}

	/////////////////////////////////////////////
	// Client / Server Close connection
	//
	// close client connection
	if(TCP_OK != _client->TCPclose())
	{
		printf(">close_client_server_connection : FAILED when trying to close client\r\n");
		iReturnValue = TEST_KO;
	}
	// close server connection
	if(TCP_SERVER_SUCCESS != _server->TCPclose())
	{
		printf(">close_client_server_connection : FAILED when trying to close server connection\r\n");
		iReturnValue = TEST_KO;		
	}
	return TEST_OK;
}
// -------------------------------------------------------------------
// tester public functions to test the server interface
// -------------------------------------------------------------------
int Test::tester_network_tcp_connect_client_to_server()
{
	int iReturnValue = TEST_OK;

	// create client server connection 
	Network::TCPServer * server = new Network::TCPServer();
	Network::TCPClient * client = new Network::TCPClient();
	
	iReturnValue = create_client_server_connection(server, client);
	if(TEST_OK == iReturnValue)
	{
		iReturnValue = close_client_server_connection(server, client);
	}

	// delete object
	delete client;
	delete server;

	return iReturnValue;
}
// -------------------------------------------------------------------
int Test::tester_network_tcp_send_message_client_to_server_no_allocation()
{
	return tester_network_tcp_send_message_client_to_server(false);
}
// -------------------------------------------------------------------
int Test::tester_network_tcp_send_message_client_to_server_with_allocation()
{
	return tester_network_tcp_send_message_client_to_server(true);
}
// -------------------------------------------------------------------
int tester_network_tcp_send_big_message_client_to_server_with_allocation()
{
	bool bAllocate = true;
	char * pBigMessage = NULL;
	char * pAnswer = NULL;
	int iOctetReceived = 0;
	pBigMessage = (char*) malloc(TEST_SIZE_BIG_DATA);
	pAnswer = (char*) malloc(STR_LONG);
	memset(pBigMessage, 0x00, TEST_SIZE_BIG_DATA);
	memset(pAnswer, 0x00, STR_LONG);

	// create client server connection 
	Network::TCPServer * server = new Network::TCPServer();
	Network::TCPClient * client = new Network::TCPClient();
	int iReturnValue = create_client_server_connection(server, client);

	////////////////////////////////////////////////////////////
	// create an internal struct for server configuration in thread
	Server_Internal_Tester * internlServConfig = (Server_Internal_Tester *)malloc(sizeof(Server_Internal_Tester));
	internlServConfig->pServer = server;
	internlServConfig->bDataAllocation = bAllocate;

	////////////////////////////////////////////////////////////
	// Threading for server
	// create server thread
	Threading::Thread * m_ServerThread = new Threading::Thread();
	// create manage thread object
	Threading::sPoolGarbagedItem * garbageItem = new Threading::sPoolGarbagedItem();
	garbageItem->pObject = internlServConfig;
	garbageItem->th = m_ServerThread;
	// start thread
	m_ServerThread->ThreadStart(server_sender_big_message, garbageItem);

	// feed big data buffer
	feed_buffer_for_test(pBigMessage, TEST_SIZE_BIG_DATA);

	// call client and send data
	if(TEST_OK == iReturnValue)
	{
		// send and receive data
		client->TCPSend(pBigMessage, TEST_SIZE_BIG_DATA);
		client->TCPReceive(pAnswer, STR_LONG, &iOctetReceived);

		// test data HERE
		if(0 != memcmp(pAnswer, TEST_SIMPLE_DATA_SERVER, sizeof(TEST_SIMPLE_DATA_SERVER)))
		{
			iReturnValue = TEST_KO;
		}

		// close connection
		iReturnValue = close_client_server_connection(server, client);
	}

	while(m_ServerThread->IsAlive());

	free(pBigMessage);
	// delete object
	delete client;
	delete server;

	return TEST_OK;
}
// -------------------------------------------------------------------
int Test::tester_network_tcp_send_message_client_to_server(bool bAllocate)
{
	int iReturnValue = TEST_OK;
	char pAnswer[STR_LONG];
	int iOctetReceived = 0;

	memset(pAnswer, 0x00, sizeof(pAnswer));

	// create client server connection 
	Network::TCPServer * server = new Network::TCPServer();
	Network::TCPClient * client = new Network::TCPClient();
	iReturnValue = create_client_server_connection(server, client);

	////////////////////////////////////////////////////////////
	// create an internal struct for server configuration in thread
	Server_Internal_Tester * internlServConfig = (Server_Internal_Tester *)malloc(sizeof(Server_Internal_Tester));
	internlServConfig->pServer = server;
	internlServConfig->bDataAllocation = bAllocate;

	////////////////////////////////////////////////////////////
	// Threading for server
	// create server thread
	Threading::Thread * m_ServerThread = new Threading::Thread();
	// create manage thread object
	Threading::sPoolGarbagedItem * garbageItem = new Threading::sPoolGarbagedItem();
	garbageItem->pObject = internlServConfig;
	garbageItem->th = m_ServerThread;
	// start thread
	m_ServerThread->ThreadStart(server_sender_simple_message, garbageItem);

	if(TEST_OK == iReturnValue)
	{
		// send and receive data
		client->TCPSend(TEST_SIMPLE_DATA_CLIENT, sizeof(TEST_SIMPLE_DATA_CLIENT));
		client->TCPReceive(pAnswer, STR_LONG, &iOctetReceived);

		// test data HERE
		if(0 != memcmp(pAnswer, TEST_SIMPLE_DATA_SERVER, sizeof(TEST_SIMPLE_DATA_SERVER)))
		{
			iReturnValue = TEST_KO;
		}

		// close connection
		iReturnValue = close_client_server_connection(server, client);
	}

	while(m_ServerThread->IsAlive());

	// free internal ressources
	free(internlServConfig);
	// delete object
	delete client;
	delete server;

	return iReturnValue;
}
// -------------------------------------------------------------------
int Test::tester_network_tcp_client_server()
{
    int iReturnCode = TEST_OK;
    Test::TesterReport::getInstance()->printHeader("testing Network::Tcp");

	// test 01
	iReturnCode = tester_network_tcp_connect_client_to_server();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Network::TCPClientServer", "tester_network_tcp_connect_client_to_server()");
	
	// test 02
	iReturnCode = tester_network_tcp_send_message_client_to_server_no_allocation();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Network::TCPClientServer", "tester_network_tcp_send_message_client_to_server_no_allocation()");

	// test 03
	iReturnCode = tester_network_tcp_send_message_client_to_server_with_allocation();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Network::TCPClientServer", "tester_network_tcp_send_message_client_to_server_with_allocation()");

	// test 04
	iReturnCode = tester_network_tcp_send_big_message_client_to_server_with_allocation();
	Test::TesterReport::getInstance()->printSummary((TEST_OK == iReturnCode), "Network::TCPClientServer", "tester_network_tcp_send_big_message_client_to_server_with_allocation()");

	return iReturnCode;
}
// -------------------------------------------------------------------
