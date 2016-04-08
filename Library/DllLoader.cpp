/**
 * \file 		DllLoader.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */

#include <stdio.h>
#include <string.h>
#include <string>

#ifdef LINUX
#include <dlfcn.h>
#endif //LINUX

#include <string.h>
#include "DllLoader.h"
#include "toolsconstant.h"

#include "Tools/File/Directory.h"
#include "Tools/File/File.h"
#include "FileIO/FileLog.h"

#ifdef _WINDOWS
#include "Windows/System/Environment.h"
#endif

#define LOGGER_DLL_LOADER_FILENAME  "dll_loader_logger.log"

// ---------------------------------------------------------------------

Library::DllLoader::DllLoader() {
    initializeObjectForConstructor(NULL);
}
// ---------------------------------------------------------------------

Library::DllLoader::DllLoader(FileIO::FileLog * logger) {
    initializeObjectForConstructor(logger);
}
// ---------------------------------------------------------------------

Library::DllLoader::~DllLoader() {

    delete m_mapping;
    if (true == m_bInternalLogger) {
        delete m_logger;
    }
}
// ---------------------------------------------------------------------

void Library::DllLoader::initializeObjectForConstructor(FileIO::FileLog * logger) {

    if (NULL == logger) {
        m_bInternalLogger = true;
        m_logger = new FileIO::FileLog(LOGGER_DLL_LOADER_FILENAME);
        // need to define setfilter actions
        m_logger->Log(FileIO::flPrioDebug, FileIO::flOrigSoftware, (char*) "[DllLoader]\tCreate a new logger for DllLoader.");
    } else {
        m_bInternalLogger = false;
        m_logger = logger;
        m_logger->Log(FileIO::flPrioDebug, FileIO::flOrigSoftware, (char*) "[DllLoader]\tUsing define logger for DllLoader.");
    }

    m_mapping = new Collection::Hashmap<std::string *, void*>();
    m_vDllHandle = NULL;

    memset(m_strFullPathLib, 0x00, STR_LONG);
}
// ---------------------------------------------------------------------

bool Library::DllLoader::findLibrary(char * _pFullPathLib, const char * _pInLibTargetName) {
    // Formate le nom du fichier
    char pFullPathDllName[STR_LONG] = {0};
    char cPathFile[STR_LONG] = {0};

    // 1) testing file existing in current directory
    Tools::Directory::GetExeDirectoryPath(pFullPathDllName, STR_LONG);
    sprintf(cPathFile, "%s%s", pFullPathDllName, _pInLibTargetName);

    m_logger->LogArguments(FileIO::flPrioDebug, FileIO::flOrigSoftware, (char*) "[DllLoader]\tFirst try: trying to load library in path %s.", pFullPathDllName);

    bool bExist = Tools::File::FileExists(cPathFile);
    if (true == bExist) {
        memcpy(_pFullPathLib, cPathFile, STR_LONG);
        m_logger->LogArguments(FileIO::flPrioDebug, FileIO::flOrigSoftware, (char*) "[DllLoader]\tSuccess: lib load from %s.", cPathFile);
        return true;
    }

#ifdef _WINDOWS
    // default look in system32, but if system is x64, change the target folder path
    int iSysId = PATH_SYS_32;
#ifdef _WIN64
    iSysId = PATH_SYS_64;
#endif

    // 2) testing existing in C:\Windows\system32 or SysWow64
    if (DIRTOOLS_KO == Tools::Directory::GetSpecificFolder(iSysId, pFullPathDllName, STR_LONG)) {
        memcpy(_pFullPathLib, cPathFile, STR_LONG);
        return false;
    }
    memset(cPathFile, 0x00, STR_LONG);
    sprintf(cPathFile, "%s\\%s", pFullPathDllName, _pInLibTargetName);
    bExist = Tools::File::FileExists(cPathFile);
    if (true == bExist) {
        memcpy(_pFullPathLib, cPathFile, STR_LONG);
        return true;
    }

    // 3) looking in windows path if the library not found
    char path[MAX_PATH_SIZE] = {0};
    long lPathSize = 0;
    //if(ENV_OK != Windows::Environment::GetPath(path, MAX_PATH_SIZE, &lPathSize))
    std::list<std::string> * paths = new std::list<std::string>();
    if (ENV_OK != Windows::Environment::GetPaths(paths)) {
        return false;
    }
    for (std::list<std::string>::iterator it = paths->begin(); it != paths->end(); it++) {
        std::string item = *it;

        memset(cPathFile, 0x00, STR_LONG);
        sprintf(cPathFile, "%s\\%s", item.c_str(), _pInLibTargetName);
        bExist = Tools::File::FileExists(cPathFile);
        if (true == bExist) {
            memcpy(_pFullPathLib, cPathFile, STR_LONG);
            delete paths;
            return true;
        }
    }
    delete paths;

#endif // _WINDOWS

#ifdef LINUX
    // TODO MAT or TODO NSJ
    // implement library search strategy, maybe this is just adding /usr/lib/ ???

    // 2) testing existing in C:\Windows\system32 or SysWow64
    if (DIRTOOLS_KO == Tools::Directory::GetSpecificFolder(PATH_SYS_32, pFullPathDllName, STR_LONG)) {
        memcpy(_pFullPathLib, cPathFile, STR_LONG);
        return false;
    }
    memset(cPathFile, 0x00, STR_LONG);
    sprintf(cPathFile, "%s/%s", pFullPathDllName, _pInLibTargetName);
    bExist = Tools::File::FileExists(cPathFile);
    m_logger->LogArguments(FileIO::flPrioDebug, FileIO::flOrigSoftware, (char*) "[DllLoader]\tSecond Step : Testing if lib exist in path %s.", cPathFile);

    if (true == bExist) {
        m_logger->Log(FileIO::flPrioDebug, FileIO::flOrigSoftware, (char*) "[DllLoader]\tFound library.");
        memcpy(_pFullPathLib, cPathFile, STR_LONG);
        return true;
    }
#endif 

    m_logger->Log(FileIO::flPrioDebug, FileIO::flOrigSoftware, (char*) "[DllLoader]\tCannot find library in any path.");
    return false;
}
// ---------------------------------------------------------------------

unsigned long Library::DllLoader::loadLibrary(const char * pDllName) {

    if (NULL == pDllName) {
        m_logger->Log(FileIO::flPrioDebug, FileIO::flOrigSoftware, (char*) "[DllLoader]\tloadLibrary failed: invalid parameter.");
        return DLLLOADER_INVALID_PARAM;
    }

    // Formate le nom du fichier
    char pFullPathDllName[STR_LONG] = {0};
    findLibrary(pFullPathDllName, pDllName);

    // copy execution path
    memcpy(m_strFullPathLib, pFullPathDllName, STR_LONG);

    // loading library
#ifdef _WINDOWS
    if (NULL == (m_vDllHandle = LoadLibraryA(pFullPathDllName))) {
        return DLLLOADER_CANNOT_LOAD_LIB;
    }
#endif //_WINDOWS

#ifdef LINUX
    m_vDllHandle = dlopen(pFullPathDllName, RTLD_LAZY);
    if (NULL == m_vDllHandle) {
        fprintf(stderr, "%s\n", dlerror());
        m_logger->Log(FileIO::flPrioDebug, FileIO::flOrigSoftware, (char*) "[DllLoader]\tCannot open library with dlopen.");
        m_logger->LogArguments(FileIO::flPrioDebug, FileIO::flOrigSoftware, (char*) "[DllLoader]\tError reason : %s.", stderr);
        return DLLLOADER_CANNOT_LOAD_LIB;
    }
#endif //LINUX

    m_logger->Log(FileIO::flPrioDebug, FileIO::flOrigSoftware, (char*) "[DllLoader]\tFound library and open with success.");
    return DLLLOADER_OK;
}

unsigned long Library::DllLoader::loadLibraryWithEntry(char * pFullPathDllName, Collection::List<std::string> * entryPoints) {

    unsigned long lReturnCode = DLLLOADER_OK;

    if (entryPoints->Count() <= 0) {
        return DLLLOADER_INVALID_PARAM;
    }

    // loading library
    if (DLLLOADER_OK != (lReturnCode = loadLibrary(pFullPathDllName))) {
        return lReturnCode;
    }

#ifdef _WINDOWS
    // loop to load all entry points required 
    for (int i = 0; i < entryPoints->Count(); i++) {
        try {
            std::string * tempEntry = new std::string(entryPoints->getItem(i));

            char tempProcName[STR_LONG];
            memset(tempProcName, 0x00, STR_LONG);
            memcpy(tempProcName, tempEntry->c_str(), tempEntry->length());

            void* procAdress = GetProcAddress((HINSTANCE) m_vDllHandle, (LPCSTR) tempProcName);
            if (NULL != procAdress) {
                m_mapping->Add(tempEntry, procAdress);
            } else {
                lReturnCode = DLLLOADER_CANNOT_LOAD_PROC;
            }

            delete tempEntry;
        } catch (...) {
            lReturnCode = DLLLOADER_CANNOT_LOAD_PROC;
        }
    }
#endif //_WINDOWS

#ifdef LINUX
    //TODO// Voir si on peut charger les lib en direct sous linux
#endif //LINUX

    return lReturnCode;
}
// ---------------------------------------------------------------------

void* Library::DllLoader::getLibraryHandle() {
    return m_vDllHandle;
}

// ---------------------------------------------------------------------

void * Library::DllLoader::getProcAdress(int index) {
    return m_mapping->getSecondItem(index);
}
// ---------------------------------------------------------------------

void * Library::DllLoader::getProcAdress(char * cProcName) {

#ifdef _WINDOWS
    return GetProcAddress((HINSTANCE) m_vDllHandle, (LPCSTR) cProcName);
#endif //_WINDOWS

#ifdef LINUX
    m_logger->LogArguments(FileIO::flPrioDebug, FileIO::flOrigSoftware, (char*) "[DllLoader]\tgetProcAdress for function: %s.", cProcName);    
    return dlsym(m_vDllHandle, cProcName);
#endif //LINUX    

}
// ---------------------------------------------------------------------

unsigned long Library::DllLoader::releaseLibrary() {

#ifdef _WINDOWS
    FreeLibrary((HINSTANCE) m_vDllHandle);
#endif //_WINDOWS

#ifdef LINUX
    dlclose(m_vDllHandle);
#endif //LINUX

    return DLLLOADER_OK;
}
// ---------------------------------------------------------------------