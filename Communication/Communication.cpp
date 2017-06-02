
#include <windows.h>
#include "Communication.h"

namespace Communications
{
	/*! constructeur de la classe communication */
	Communication::Communication()
	{
		m_bOpened = false;
		memset(m_strLastFrameSend,0,STR_LONG);
		memset(m_strLastFramReceived,0,STR_LONG);
	}

	Communication::~Communication()
	{
	}
}