/**
 * \file 		DllLoader.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef DYNAMIC_LIBRARY_LOADER_H
#define DYNAMIC_LIBRARY_LOADER_H

#ifdef _WINDOWS
#include <Windows.h>
#endif /* _WINDOWS */

// -----------------------------------------------------------------------
#include "toolsconstant.h"
#include "FileIO/FileLog.h"
#include "Collection/Hashmap.hpp"
#include "Collection/List.hpp"

#include <string>

// -----------------------------------------------------------------------
#define DLLLOADER_OK				0
#define DLLLOADER_KO				1
#define DLLLOADER_INVALID_PARAM		2
#define DLLLOADER_CANNOT_LOAD_LIB	3
#define DLLLOADER_CANNOT_LOAD_PROC	4
#define DLLLOADER_NON_INIT			5

// -----------------------------------------------------------------------
namespace Library {

    class DllLoader {
    private:
        /** mapping ot the library */
        Collection::Hashmap<std::string *, void*> * m_mapping;
        
        /** execution path for library, found by code */
        char m_strFullPathLib[STR_LONG];

        /** internal instance declaration */
        void* m_vDllHandle;

		/** state of library, loaded or not */
		bool m_bLibraryLoaded;
        
        /**! initializer for constructor*/
        void initializeObjectForConstructor(FileIO::FileLog * logger);

		/** function to found the library path using the following strategy
		 * 1) current directory 
		 * 2) library directory (Win = C:\Windows; unix = /usr/lib/)
		 */
		bool findLibrary(char * _pFullPathLib, const char * _pInLibTargetName);
        
                /**! internal logger definition */
                FileIO::FileLog * m_logger;
                
                /**! define if this logger has been allocated locally */
                bool m_bInternalLogger;

    public:
        /** main constructor and destructor of the class */
        DllLoader();
        DllLoader(FileIO::FileLog * logger);
        ~DllLoader();

        /** load libray from the dll full path name*/
        unsigned long loadLibrary(const char * pFullPathDllName);

        /** load libray from the dll full path name and list of entrypoints*/
        unsigned long loadLibraryWithEntry(char * pFullPathDllName, Collection::List<std::string> * entryPoints);

        /** release all ressources allocated by Dll loader */
        unsigned long releaseLibrary();

        /** get the value of internal instance declaration of library */
        void * getLibraryHandle();

        /** get the pointer value of the target proc Adress */
        void * getProcAdress(int index);

        /** get the pointer value of the target proc Adress */
        void * getProcAdress(char * cProcName);
    };
};

#endif /* DYNAMIC_LIBRARY_LOADER_H */