/**
 * \file 		Environment.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#define PATH_STR_VALUE		"path"

#define ENV_OK				0
#define ENV_KO				1
#define ENV_VAR_NOT_FOUND	2
#define ENV_SIZE_TOO_SMALL	3

#define MAX_PATH_SIZE		32767
#define MAX_PATH_CONTENT	128

#ifdef _WINDOWS

#include <string.h>
#include <list>

namespace Windows {
	
	namespace Environment {
	
	/** function to read a specific environment variable
	 *\param [in] cKeyEnvironmentName: The name of the environment variable.
	 *\param [in] lKeyEnvironmentNameSize : The size of the buffer pointed to by the lpBuffer parameter, including the null-terminating character, in characters.
	 *\param [out] cOutValue : A pointer to a buffer that receives the contents of the specified environment variable as a null-terminated string. An environment variable has a maximum size limit of 32,767 characters, including the null-terminating character.
	 *\return error code
	 */
	long GetVariable(char * cKeyEnvironmentName, long lKeyEnvironmentNameSize, char * cOutValue);

	/** function to get the value of path
	 *\param [out] cOutValue : A pointer to a buffer that receives the contents of the specified environment variable as a null-terminated string. An environment variable has a maximum size limit of 32,767 characters, including the null-terminating character.
	 *\param [in] lSizeOutValue: max size of cOutValue
	 *\param [out] lSizePath : size of path value
	 */
	long GetPath(char * cOutValue, long lSizeOutValue, long * lSizePath);

	/** function to get the different path contained in path
	 */
	long GetPaths(std::list<std::string> * paths);
	};
};

#endif /* _WINDOWS */

#endif /* ENVIRONMENT_H */
