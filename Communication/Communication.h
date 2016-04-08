#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#define COM_SHORT_STR				128
#define COM_LONG_STR				1024
#define COM_INTERNAL_SIZE_BUFFER	2048

#define COM_TYPE_RS					"RS"
#define COM_TYPE_USB				"USB"

#include "toolsConstant.h"

namespace Communications
{
	/*! classe d'interface vers les moteurs*/
	class Communication
	{
	protected:
		/*! status of communication, initialized or not */
		bool m_bOpened;

		/*! type de la communication */
		char m_strCommunicationType[COM_SHORT_STR];

		/*! dernière trame envoyée */
		char m_strLastFrameSend[STR_LONG];

		/*! dernière trame reçue */
		char m_strLastFramReceived[STR_LONG];

	public:
		/*! constructor of the class */
		Communication();
		~Communication();

		/* open a new communication interface */
		virtual int Open() = 0;

		/*! close a communication interface*/
		virtual int Close() = 0;

		/*! fonction to send data from an encoded buffer */
		virtual int SendData(char* _pBufferToSend,int _iSizeBufferToSend, int* _iOctetsSended) = 0;

		/*! fonction to receive data from an encoded buffer */
		virtual int ReceiveData(char* _pBufferReceived, int _iSizeOutputBuffer, int* _iOctetsReceived) = 0;
	};
}

#endif