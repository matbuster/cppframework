#ifndef COMPUTER_KEYBOARD_H
#define COMPUTER_KEYBOARD_H

// -----------------------------------------------------------
// defines for Hardware::Computer
#define HAR_COMP_OK					0
#define HAR_COMP_KO					1
#define HAR_COMP_INVALID_PARAM		2
#define HAR_BUFFER_TOO_SMALL		3
#define HAR_COMP_INTERNAL_FAILED	4

// -----------------------------------------------------------
// generic includes
#include <string>
#include <list>

// -----------------------------------------------------------
// galitt framework
#include "toolsconstant.h"

namespace Hardware {

	namespace Computer {
		
		// -----------------------------------------------------------------------------------------
		typedef struct {
			
			char pIpAdress[STR_TINY];			//< ip adress
			char pBroadcastAdress[STR_TINY];	//< broadcast adress
			char pNetworkMask[STR_TINY];		//< network mask
			unsigned long nFlags;				//< flag
			bool isUp;							//< information up or down
			bool isPointToPoint;				//< information is point-to-point
			bool isLoopback;					//< information is a loopback iface
			bool isBroadcast;					//< information is bcast
			bool isMulticast;					//< information is multicast
		 
		} st_network_interface;

		// -----------------------------------------------------------------------------------------
		/**! getter on the computer name defined in OS 
		 * 
		 * @param out _pComputerName name of the computter
		 * @param in _iSizeBufferComputerName size of the output buffer
		 * @return error code
		 */
		long getComputerName(char * _pComputerName, unsigned int _iSizeBufferComputerName);
             
		// -----------------------------------------------------------------------------------------
        /**! getter on the user logged on this computer
          * 
          * @param _pComputerUser associated user logged
          * @param _iSizeBufferComputerName size of input buffer
          * @return error code
          */
        long getComputerUser(char * _pComputerUser, unsigned int _iSizeBufferComputerName);
		
		// -----------------------------------------------------------------------------------------
		/**! getter on the computer ip adress available
         * 
		 * @param out _pListIpAdress list of ip adress available on this computer
		 * @return error code
		 */
		long getComputerIpv4Adress(std::list<std::string> * _pListIpAdress);
		
		// -----------------------------------------------------------------------------------------
		/** getter on the network interfaces available on this computer
		 * 
		 * @see Hardware::Computer::st_network_interface for the interface definition
		 * @param _plistInterfaces out list of interfaces 
		 * @return error code
		 */
		long getNetworkInterfaces(std::list<Hardware::Computer::st_network_interface> * _plistInterfaces);

		// -----------------------------------------------------------------------------------------
		/** getter on the Domain name of the computer. Only available on windows.
		 * 
		 * \param out pDomainNameFlat : buffer for the Domain name Flat
		 * \param in iSizeDomainNameFlat : size of buffer pDomainNameFlat
		 * \param out pDomainNameFlat : buffer for the Domain name Flat
		 * \param in iSizeDomainNameFlat : size of buffer pDomainNameFlat
		 * \return error code
		 */
		long getNetworkDomainName(char * pDomainNameFlat, unsigned int iSizeDomainNameFlat, char * pDomainNameDns, unsigned int iSizeDomainNameDns);
	};
};

#endif // COMPUTER_KEYBOARD_H