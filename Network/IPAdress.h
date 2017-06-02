#ifndef IP_ADRESS_H
#define IP_ADRESS_H

#include "toolsconstant.h"
#include <string>

namespace Network {

	class IPAdress {
	
	private:
		/**! string value of the ip adress */
		std::string m_strIpAdress;
		
		/**! validity of ip adress*/
		bool m_bIpIsValid;

		/**! the ip adress is an ipv4 adress */
		bool m_bIsIpv4;

		/**! the ip adress is an ipv6 adress */
		bool m_bIsIpv6;

		/**! ckeck the validity of object Adress IP
		 * \return valid (true) or not (false)
		 */
		bool CheckValidity();

	public:
		/**! constructor and destructor */
		IPAdress(char * _pIpAdress);
		IPAdress(const IPAdress& _pIpAdress);
		~IPAdress();

		/**! funciton to check if the adress is an ip v4 adress
		 * \return valid ipv4 (true), non-valid (false)
		 */
		bool IsIpv4() const;

		/**! funciton to check if the adress is an ip v6 adress
		 * \return valid ipv6 (true), non-valid (false)
		 */
		bool IsIpv6() const;

		/**! getter on the value of IPAdress
		 * \return the string value of IpAdress
		 */
		std::string getIpAdress() const;

		/**! setter on the Ip adress, using string
		 * \param [in] _ipAdress : new ip adress as a string
		 * \return success (true) or failed (false)
		 */
		bool setIpAdress(std::string _strIpAdress);


		/**! setter on the Ip adress, using string
		 * \param [in] _ipAdress : new ip adress as a char pointer
		 * \return success (true) or failed (false)
		 */
		bool setIpAdress(char * _pIPpAdress);
	};
};

#endif /** IP_ADRESS_H */