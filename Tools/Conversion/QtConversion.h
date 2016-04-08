#ifndef QT_CONVERSION_H
#define QT_CONVERSION_H

// ----------------------------------------------------
#include <QString>

// ----------------------------------------------------
// define
#define QT_CONV_OK                  0
#define QT_CONV_KO                  1
#define QT_CONV_INVALID_PTR         2
#define QT_CONV_BAD_LENGTH          3

// ----------------------------------------------------
namespace Tools {
	
	namespace Conversion {
		
#ifdef _QT_FRAMEWORK
    // --------------------------------------------------------------------------------------------------
    /**
     * @brief convert_QChar_To_Char_ptr function to convert a QChar from Qt framework to char * from cpp
     * @param pQtType [in] input QString to convert
     * @param pConvertedString [out] output string converted to char *
     * @param pSizeConvertedString [in] size of the output string
     * @return error code
     */
    long convert_QString_To_Char_ptr(QString pQtType, char * pConvertedString, long pSizeConvertedString);
#endif // _QT_FRAMEWORK

	};
};

#endif // QT_CONVERSION_H
