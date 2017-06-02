#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include "IPAdress.h"

namespace Network {

	class TcpConnection : public IPAdress {

	private:
		// -------------------------------------------------------
		/**! port definition */
		unsigned int m_uiPort;

	public:
		
		// -------------------------------------------------------
		/**! construcor
		 * \param [in] pIpAdress : value of the ip adresse
		 * \param [in] uiPort : target port value
		 */
		TcpConnection(char * pIpAdress, unsigned int uiPort);
		virtual ~TcpConnection();
		
		// -------------------------------------------------------
		/**! getter on the port value
		 * \return port value
		 */
		unsigned int getPort();
		
		// -------------------------------------------------------
		/**! setter on the port value
		 * \param [in] uiPort : port value definition
		 */
		void setPort(unsigned int uiPort);
	};
};

#endif TCP_CONNECTION_H