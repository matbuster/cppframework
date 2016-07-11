#ifndef COMPUTER_KEYBOARD_H
#define COMPUTER_KEYBOARD_H

// -----------------------------------------------------------
// defines for Hardware::Computer
#define HAR_COMP_OK					0
#define HAR_COMP_KO					1
#define HAR_COMP_INVALID_PARAM		2
#define HAR_BUFFER_TOO_SMALL		3


namespace Hardware {

	namespace Computer {

		/**! getter on the computer name defined in OS 
		 * @param out _pComputerName name of the computter
		 * @param in _iSizeBufferComputerName size of the output buffer
		 * @return error code
		 */
		long getComputerName(char * _pComputerName, unsigned int _iSizeBufferComputerName);
	};
};

#endif // COMPUTER_KEYBOARD_H