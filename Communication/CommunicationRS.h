#ifndef _COMMUNICATION_RS_
#define _COMMUNICATION_RS_

#define COM_OK						1
#define COM_CANNOT_OPEN				-1
#define COM_CANNOT_SETUP			-2
#define COM_ALREADY_OPEN			-3
#define COM_ALREADY_CLOSE			-4
#define COM_NO_DATA_TO_SEND			-5
#define COM_INVALID_DATA_BUFFER		-6
#define COM_CLEAR_FAILED			-7
#define COM_NO_OCTETS_SEND			-8
#define COM_CONFIGURATION_FAILED	-9
#define COM_INVALID_POINTER			-10

#define COM_CFG_TYPE				"strCOMType"
#define COM_CFG_NUM_PORT			"iPortCOM"
#define COM_CFG_BAUDRATE			"iBaudRate"
#define COM_CFG_DTR					"iDtrControl"
#define COM_CFG_RTS					"iRtsControl"
#define COM_CFG_PARITY				"iParity"
#define COM_CFG_BITSTOP				"iOneStopBit"

#include <Windows.h>

namespace Communications
{
	/*! classe d'interface vers les moteurs*/
	class CommunicationRS : public Communication
	{
	private:
		/*! fonction pour définir un polling threadé */
		bool m_bThreadedPolling;

		/*! numéro du port COM */
		int m_iPortCOM;

		/*! vitesse sur le port série */
		int m_iBaudRade;

		/*! config dtrcontrol */
		int m_iDtrControl;

		/*! config rts controls */
		int m_iRtsControl;

		/*! config de la parity */
		int m_iParity;

		/*! config du bit de stop */
		int m_iOneStopBit;

		/*! handle sur la com */
		HANDLE m_hCom;

	public:
		/* constructor for a communication RS */
		CommunicationRS();

		/*! destructor for a RS Communication */
		virtual ~CommunicationRS();

		/*! fonction permettant d'aller lire les paramètres de configuration d'un fichier */
		int GetConfigParams(char* _strAbsParamCfgFile, char* _strAxisID);

		/*! fonction pour aller définir les paramètres de port com */
		int SetConfigParams(int _iPort, int _iBaudRate, int _iDtrControl = 0, int _iRtsControl = 0, int _iParity = 0, int _iOneStopBit = 0);
			
		/* open une nouvelle communication RS */
		int Open();

		/*! Close d'une communication RS */
		int Close();
			
		/*! fonction to send data from an encoded buffer */
		int SendData(char* _pBufferToSend,int _iSizeBufferToSend, int* _iOctetsSended);

		/*! fonction to receive data from an encoded buffer */
		int ReceiveData(char* _pBufferReceived, int _iSizeOutputBuffer, int* _iOctetsReceived);
	};
}

#endif