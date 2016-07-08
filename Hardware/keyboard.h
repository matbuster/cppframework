#ifndef HARDWARE_KEYBOARD_H
#define HARDWARE_KEYBOARD_H

// ----------------------------------------------
// blocking state defines
#define NB_ENABLE 0
#define NB_DISABLE 1

namespace Hardware {
	
	namespace Keyboard {

		// ----------------------------------------------
		/**! La fonction int kbhit(void); indique si une touche du clavier a �t� frapp�e et que, 
		 * par cons�quent, un caract�re est en attente d'�tre lu.
		 * Son appel renvoie 0 si aucun caract�re n'est en attente et une valeur non nulle autrement.
		 * @return 0 si aucun caract�re n'est en attente
		 */
		int kbhit(void);

		// ----------------------------------------------
#ifdef LINUX
		/**! define or not blocking state for keyboard for one keyboard input*/
		void nonblock(int state);
#endif // LINUX

		// ----------------------------------------------
		/**! wait specific key to continue. This function is blocking
		 * @param _piKeyAllowed array containing the key allowed
		 * @param _iNumKeyAllowed size of the array, number of key waited
		 * @return success or failed 
		 */
		bool waitKeyToContinue(int * _piKeyAllowed, int _iNumKeyAllowed, int * iKeyValue);

		// ----------------------------------------------
		/**! Wait input from user. Key waited are y,Y,n,N
		 * @return succes if Y or y, failed if another key is pressed
		 */
		bool waitYesNoToContinue();

		// ----------------------------------------------
		/** getter on an integer value
		 * @return a integer value
		 */
		int getIntegerValue();

		// ----------------------------------------------
		/** getter for an ip adress
		 * @param [out] _pIpAdress ipadress
		 * @param [in] _iSizeIpAdress
		 * @param success or failed
		 */
		bool getIpAdress(char * _pIpAdress, int _iSizeIpAdress);
	};
};

#endif // HARDWARE_KEYBOARD_H