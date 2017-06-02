/**
 * \file 		LibraryInfo.h
 * \date 		06/01/2017
 * \author 		NSJ
 */ 
 
#ifndef LIBRARY_INFO_H
#define LIBRARY_INFO_H

#ifdef _WINDOWS
#include <Windows.h>
#endif /* _WINDOWS */

#include <string>

#include "FileIO/FileLog.h"

// -----------------------------------------------------------------------
namespace Library {

    class LibraryInfo {
    public:
        /** main constructor and destructor of the class */
        LibraryInfo();
        ~LibraryInfo();

        /** get the library name */
        bool getLibraryName(char * _pcName);
		
		/** get the library description */
        bool getLibraryDescription(char * _pcDescription);
		
		/** get the library company name */
        bool getLibraryCompanyName(char * _pcCompanyName);
		
		/** get the library copyright */
        bool getLibraryCopyright(char * _pcCopyright);
		
		/** get the library version */
        bool getLibraryVersion(char * _pcVersion);
		
    };
};

#endif /* LIBRARY_INFO_H */