#ifdef _QT_FRAMEWORK
// -----------------------------------------------------------
/** only define for Qt Build, convert Qt type into cpp type */
// -----------------------------------------------------------

#include "QtConversion.h"
#include "toolsconstant.h"

#include <QString>

// -----------------------------------------------------------
long Tools::Conversion::convert_QString_To_Char_ptr(QString  pQtType, char * pConvertedString, long pSizeConvertedString)
{
    if(NULL == pQtType) {
        return QT_CONV_INVALID_PTR;
    }
    if(NULL == pConvertedString) {
        return QT_CONV_INVALID_PTR;
    }
    if(pQtType.length() == 0) {
        return QT_CONV_BAD_LENGTH;
    }
    if(pQtType.length() > pSizeConvertedString) {
        return QT_CONV_BAD_LENGTH;
    }

    int iCountValidChar = 0;
    int iCharLength = pQtType.length() * 2;
    char pTempString[STR_LONG];
    memset(pTempString, 0x00, pSizeConvertedString);
    memset(pConvertedString, 0x00, pSizeConvertedString);
    memcpy(pTempString, pQtType.data(), iCharLength);

    for(int i = 0; i < iCharLength; i++) {

        if(0x00 != pTempString[i]) {
            pConvertedString[iCountValidChar] = pTempString[i];
            iCountValidChar++;
        }
    }


    return QT_CONV_OK;
}
#endif // _QT_FRAMEWORK
