#ifndef TOOLS_PROFILE_NETWORK_PROFILE_H
#define TOOLS_PROFILE_NETWORK_PROFILE_H

#include <string>
#include <list>

#include "toolsconstant.h"

#define NETWORK_PROFILE_OK					0
#define NETWORK_PROFILE_KO					1
#define NETWORK_PROFILE_INVALID_PARAM		2

namespace Tools {

	namespace Profile {
	
		class NetworkProfile {

		private:
			/**! autodetection success */
			bool m_bIsInitialized;

			/**! computer name */
			char m_pComputerName[STR_LONG];

			/**! current user name */
			char m_pCurrentUserName[STR_LONG];
#ifdef _WINDOWS
			/**! name of the associated workgroup
			 * only for Window implementation 
			 */
			char m_pDomainNameFlat[STR_LONG];

			/**! domain name dns */
			char m_pDomainNameDns[STR_LONG];
#endif
			/** list of associated ip v4 adress*/
			std::list<std::string> m_lAvailableIpv4Adress;

			/**! internal function to auto detect all items linked 
			 * to Computer Network Profile 
			 * \return error code
			 */
			long autoDetection();

		public:
			/**! constructor and destructor */
			NetworkProfile();
			~NetworkProfile ();

			// ------------------------------------------
			/**! 
			 * getter on computer name 
			 * \return the associated computer name
			 */
			std::string getComputerName();
			// ------------------------------------------
			/**! 
			 * getter on the Current user name 
			 * \return the associated user name
			 */
			std::string getCurrentUserName();
			// ------------------------------------------
			/**! getter on the Domain Name flat */
			std::string getDomainNameFlat();
			// ------------------------------------------
			/**! getter on the Domain Name dns */
			std::string getDomainNameDns();
			// ------------------------------------------
			/**! getter on the number of available ipv4 */
			int getAvailableIpv4Counter();
			// ------------------------------------------
			/**! getter on the available ip adress*/
			std::string getIpv4Adress(int index);
			
			// ------------------------------------------
			/**! setter onthe computer name */
			void setComputerName(std::string _strComputerName);
			// ------------------------------------------
			/**! setter onthe computer name */
			void setCurrentUserName(std::string _strCurrentUserName);
			// ------------------------------------------
			/**! setter onthe computer name */
			void setDomainNameFlat(std::string _strDomainNameFlat);
			// ------------------------------------------
			/**! setter onthe computer name */
			void setDomainNameDns(std::string _strDomainNameDns);
		};
	};
};

#endif /** TOOLS_PROFILE_NETWORK_PROFILE_H*/