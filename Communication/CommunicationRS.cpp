
#include "stdafx.h"

#include <Windows.h>
#include <stdio.h>

#include "Communication/Communication.h"
#include "Communication/CommunicationRS.h"

#define _EMULATED_COM_

namespace Communications
{
	/*! constructor of class RS com, inherit of a base communication */
	CommunicationRS::CommunicationRS() 
		:Communication()
	{
		m_bThreadedPolling = false;
		m_iPortCOM = 0;
		m_iBaudRade = 38500;
		m_iDtrControl = 0;
		m_iRtsControl = 0;
		m_iParity = 0;
		m_iOneStopBit = 0;

		// type de com
		strcpy_s(m_strCommunicationType,COM_SHORT_STR,COM_TYPE_RS);
	}

	CommunicationRS::~CommunicationRS()
	{
	}

	/*! fonction pour aller définir les paramètres de port com */
	int CommunicationRS::SetConfigParams(int _iPort, int _iBaudRate, int _iDtrControl, int _iRtsControl, int _iParity, int _iOneStopBit)
	{
		m_iPortCOM = _iPort;
		m_iBaudRade = _iBaudRate;
		m_iDtrControl = _iDtrControl;
		m_iRtsControl = _iRtsControl;
		m_iParity = _iParity;
		m_iOneStopBit = _iOneStopBit;
		return COM_OK;
	}

	/*! fonction open sur une com RS */
	int CommunicationRS::Open()
	{
		// seulement si la communicaiton n'est pas déjà ouverte
		if(!m_bOpened)
		{
#ifndef _EMULATED_COM_
			//	http://msdn.microsoft.com/library/default.asp?url=/library/en-us/fileio/fs/createfile.asp
			//	To specify a COM port number greater than 9, use the following syntax: "\\\\.\\COM10". This syntax works for all port numbers and hardware that allows COM port numbers to be specified.
			char _strCommName[COM_SHORT_STR]; memset(_strCommName,0,COM_SHORT_STR);
			sprintf(_strCommName,"\\\\.\\COM%i",m_iPortCOM);

			// open un nouveau port com par rapport à son numéro
			m_hCom=CreateFileA(_strCommName,GENERIC_READ|GENERIC_WRITE,0,0,OPEN_EXISTING,0,NULL);
			if( ( m_hCom==INVALID_HANDLE_VALUE ) || ((int)m_hCom==0) )
			{
				m_bOpened = false;
				return COM_CANNOT_OPEN;
			}

			// setup de la comm RS
			if(SetupComm(m_hCom,COM_INTERNAL_SIZE_BUFFER,COM_INTERNAL_SIZE_BUFFER)!=0)
			{
				DCB dcb;
				GetCommState(m_hCom,&dcb);
				dcb.BaudRate=m_iBaudRade;
				dcb.fBinary=1;
				dcb.fParity=(m_iParity==NOPARITY?0:1);
				dcb.Parity=m_iParity;
				dcb.fOutxCtsFlow=0;
				dcb.fOutxDsrFlow=0;
				dcb.fDtrControl=m_iDtrControl; //DTR_CONTROL_ENABLE;
				dcb.fDsrSensitivity=0;
				dcb.fTXContinueOnXoff=0;
				dcb.fOutX=0;
				dcb.fInX=0;
				dcb.fRtsControl=m_iRtsControl; //RTS_CONTROL_HANDSHAKE précédemment utilisé; DISABLE nécessaire pour le LAAS;
				dcb.fAbortOnError=0;
				dcb.ByteSize=8;
				dcb.Parity=m_iParity;
				dcb.StopBits=m_iOneStopBit;
				if(SetCommState(m_hCom,&dcb)==0)
				{
					m_bOpened = false;
					return COM_CONFIGURATION_FAILED;
				}
			}
			else
			{
				CloseHandle(m_hCom);
				m_bOpened = false;
				return COM_CANNOT_SETUP;	
			}

			// communication timeout configuration
			COMMTIMEOUTS ct;
			ct.ReadIntervalTimeout=MAXDWORD;
			ct.ReadTotalTimeoutMultiplier=0;
			ct.ReadTotalTimeoutConstant=0;
			ct.WriteTotalTimeoutMultiplier=5;
			ct.WriteTotalTimeoutConstant=5;
			SetCommTimeouts(m_hCom,&ct);

			// purge de la com avant validatioj
			PurgeComm(m_hCom,PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
#endif
			// retour ok sans erreur
			m_bOpened = true;
			return COM_OK;			
		}
		else
		{
			return COM_ALREADY_OPEN;
		}
	}

	/*! fonction open sur une com RS */
	int CommunicationRS::Close()
	{
		if(m_bOpened)
		{
#ifndef _EMULATED_COM_
			CloseHandle(m_hCom);
#endif
			m_bOpened = false;
			return COM_OK;
		}
		else
		{
			return COM_ALREADY_CLOSE;
		}
	}

	/*! fonction to send data from an encoded buffer */
	int CommunicationRS::SendData(char* _pBufferToSend,int _iSizeBufferToSend, int* _iOctetsSended)
	{
		// seulement si la com a été ouverte
		if(m_bOpened)
		{
#ifndef _EMULATED_COM_
			// précondifions
			if(_iSizeBufferToSend<=0)
			{
				return COM_NO_DATA_TO_SEND;
			}
			if(NULL == _pBufferToSend)
			{
				return COM_INVALID_DATA_BUFFER;
			}
			if(NULL == _iOctetsSended)
			{
				return COM_INVALID_POINTER;
			}
				
			// définition des constantes
			COMSTAT cst;
			DWORD CodeErreur=0;

			// purge des erreurs de coms
			if(ClearCommError(m_hCom,&CodeErreur,&cst)==0)
			{
				//ClearCommError failed
				return COM_CLEAR_FAILED;
			}

			// TODOMA: voir le cas ou le nombre d'octets reçu est différent de celui que l'on souhaite émettre
			DWORD octetsecrits=0;
			WriteFile(m_hCom,_pBufferToSend,_iSizeBufferToSend,&octetsecrits,0);
			*_iOctetsSended= (int)octetsecrits;

			// copie de la dernière frame envoyée
			strcpy_s(m_strLastFrameSend,octetsecrits,_pBufferToSend);

			// cas aucun octets transmis
			if(0 == octetsecrits)
			{
				return COM_NO_OCTETS_SEND;
			}
#endif
		}
		return COM_OK;
	}

	/*! fonction to receive data from an encoded buffer */
	int CommunicationRS::ReceiveData(char* _pBufferReceived, int _iSizeOutputBuffer, int* _iOctetsReceived)
	{
		if(NULL == _pBufferReceived)
		{
			return COM_INVALID_DATA_BUFFER;
		}
		if(NULL == _iOctetsReceived)
		{
			return COM_INVALID_POINTER;
		}

		if(m_bOpened)
		{
#ifndef _EMULATED_COM_
			COMSTAT cst;
			DWORD CodeErreur = 0;

			// purge des erreurs de coms
			if(0 == ClearCommError(m_hCom,&CodeErreur,&cst))
			{
				//ClearCommError failed
				return COM_CLEAR_FAILED;
			}

			// MAWARNING: attention à la différentiation de _iSizeOutputBuffer, OctetsALire et octetslus
			DWORD octetslus = 0;
			ReadFile(m_hCom,_pBufferReceived,_iSizeOutputBuffer,&octetslus,NULL);
			*_iOctetsReceived=(int)octetslus;

			// copie de la dernière frame
			strcpy_s(m_strLastFramReceived,_iOctetsReceived,_iSizeOutputBuffer);
#endif
		}
		return COM_OK;
	}
}
