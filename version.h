/**
 * \file 		version.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef VERSION_H
#define VERSION_H

// ---------------------------------------------------------------------------
/** versionning history */
/** v1.0.0 : MAT - initial version. 
		This version of framework contains the basic namespace used in different 
		project. Used to group as a framework all class, method, interface ... to 
		manage basic operation in cpp. 
		The implementation targetting WINDOWS and UNIX (some class implemented for 
		only one target).
*/ 
/** v1.0.1 : MAT - adding namespace Hardware::keyboard to read keyboard inpur*/
/** v1.0.2 : MAT - adding namespace Hardware::Computer to get computer infos */
/** v1.0.3 : MAT - adding more functionalities in Debug::Console */
/** v1.1.0 : MAT - TCP module dynamic received / send and big buffer management
				 - Improving dllLoader initialization
				 - complete serialization module */
/** v1.2.0 : MAT - adding tinyXml2 library
				 - adding VS2010 projet */
// ---------------------------------------------------------------------------

/**
 * \def FRAMEWORK_MAJOR_VERSION
 * \brief Edit to each code restructuring 
 */ 
#define FRAMEWORK_MAJOR_VERSION			1

/**
 * \def FRAMEWORK_MINOR_VERSION
 * \brief Edit to each add function
 */ 
#define FRAMEWORK_MINOR_VERSION			2

/**
 * \def FRAMEWORK_RELEASE_VERSION
 * \brief Edit to each bug correction 
 */ 
#define FRAMEWORK_RELEASE_VERSION		0

#endif // VERSION_H