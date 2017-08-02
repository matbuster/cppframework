
#include "keyboard.h"

//Include des en-tetes standard windows
#ifdef _WINDOWS
#include <Windows.h>
#endif // _WINDOWS

// Include des en-tetes standard linux
#ifdef LINUX
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#endif //LINUX

// generic includes
#include <stdio.h>
#include <string>

#include <string.h>
// include from galitt framework
#include "Tools/String/Regex_Helper.h"
#pragma warning(disable:4127)
// ----------------------------------------------------------------------
int Hardware::Keyboard::kbhit() 
{
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);

	// select is include in Winsock, you have to include Ws
    return select(1, &fds, NULL, NULL, &tv);
}
// ----------------------------------------------------------------------
#ifdef LINUX
void Hardware::Keyboard::nonblock(int state) {
    struct termios ttystate;

    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state == NB_ENABLE) {
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    } else if (state == NB_DISABLE) {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    }
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}
#endif //LINUX
// ----------------------------------------------------------------------
bool Hardware::Keyboard::waitKeyToContinue(int * _piKeyAllowed, int _iNumKeyAllowed, int * iKeyValue)
{
	if(NULL == _piKeyAllowed) 
	{
		return false;
	}
	if(NULL == iKeyValue)
	{
		return false;
	}
	if(_iNumKeyAllowed < 0) 
	{
		return false;
	}

	bool bKeyDetected = false;
    while(!bKeyDetected) {

        // get the input value
		if (Hardware::Keyboard::kbhit()) {
            int iCaractere = fgetc(stdin);

			for(int i = 0; i < _iNumKeyAllowed; i++) 
			{
				if(_piKeyAllowed[i] == iCaractere)
				{
					bKeyDetected = true;
					*iKeyValue = iCaractere;
					break;
				}
			}
		}
	}
	return true;
}
// ----------------------------------------------------------------------
bool Hardware::Keyboard::waitYesNoToContinue()
{
	int ikeyAlloed[4];
	ikeyAlloed[0] = 121;	// 'y'
	ikeyAlloed[1] = 89;		// 'Y'
	ikeyAlloed[2] = 110;	// 'n'
	ikeyAlloed[3] = 78;		// 'N'

	int iValue = 0;
	waitKeyToContinue(ikeyAlloed, 4, &iValue);

	if(121 == iValue) return true;
	else if(89 == iValue) return true;
	else return false;
}
// ----------------------------------------------------------------------
int Hardware::Keyboard::getIntegerValue()
{
	int value = 0;
	scanf ("%d",&value);
	printf("Integer value : %d\r\n", value);
	return value;
}
// ----------------------------------------------------------------------
bool Hardware::Keyboard::getIpAdress(char * _pIpAdress, int _iSizeIpAdress)
{
	if(NULL == _pIpAdress)
	{
		return false;
	}
	if(_iSizeIpAdress < 0)
	{
		return false;
	}
	if(_iSizeIpAdress < 15)
	{
		return false;
	}

	char ip[15];
	scanf ("%14s",ip);  
	printf("Ip adress value : %s\r\n", ip);

	std::string sip = ip;
	if(Tools::Regex::match_ipV4adress(sip))
	{
		memset(_pIpAdress, 0x00, _iSizeIpAdress);
		memcpy(_pIpAdress, ip, 15);
	}
	return true;
}
// ----------------------------------------------------------------------
bool Hardware::Keyboard::getStringValue(char * _pOutStringValue, int * _iOutStringSize , int _iMaxInputSize)
{
	if(NULL == _pOutStringValue)
	{
		return false;
	}
	if(NULL == _iOutStringSize)
	{
		return false;
	}

	char buffer[1024];
	char *line = fgets(buffer, sizeof(buffer), stdin);
	if( !line ) {

		if( feof(stdin) ) {
			printf("end of file\n");
		} else if( ferror(stdin) ) {
			printf("An error occurerd\n");
			exit(0);
		}

	} else {
		// copy in output buffer
		int iSizeMessage = strlen(buffer);
		//
		// printf("You entered: %s", line);
		// printf("Length You entered: %d\r\n", iSizeMessage);
		//
		if(_iMaxInputSize >= iSizeMessage) { 
			memcpy(_pOutStringValue, line, iSizeMessage);
			*_iOutStringSize = iSizeMessage;
		} else {
			memcpy(_pOutStringValue, line, _iMaxInputSize);
			*_iOutStringSize = _iMaxInputSize;
		}
	}

	return true;
}
// ----------------------------------------------------------------------
/*
bool Hardware::Keyboard::getStringValue(char * _pOutStringValue, int * _iOutStringSize , int _iMaxInputSize)
{
	std::string out;

	char c;
	//puts ("Enter text. Include a dot ('.') in a sentence to exit:");
	do {
		
		c=getchar();
		putchar (c);

		out += c;

		// tab detect
		if(c != '.')
		{
			break;
		}

	} while (c != '\t');

	// copy in output buffer
	int iSizeMessage = out.size();
	//
	// printf("You entered: %s", line);
	// printf("Length You entered: %d\r\n", iSizeMessage);
	//
	if(_iMaxInputSize >= iSizeMessage) { 
		memcpy(_pOutStringValue, out.c_str(), iSizeMessage);
		*_iOutStringSize = iSizeMessage;
	} else {
		memcpy(_pOutStringValue, out.c_str(), _iMaxInputSize);
		*_iOutStringSize = _iMaxInputSize;
	}

	return true;
}
*/
// ----------------------------------------------------------------------


