/**
 * \file 		Registry.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef REGISTRY_H
#define REGISTRY_H

namespace Windows {
	
	/** typedef enum key available */
	typedef enum {
		enLocalMachine,	// HKEY_LOCAL_MACHINE
		enCurrentUser,	// HKEY_CURRENT_USER
		enClassRoot,	// HKEY_CLASSES_ROOT
		enUsers			// HKEY_USERS
	} RootKey;
	
	/** class registry to read / write in widows registry */ 
	class Registry{
	
	private:
		/** internal function to get Hkey value according to the enum */
		HKEY getRootKey(RootKey hkey);
	
	public:
		/** main constructor and destructor*/
		Registry();
		~Registry();
		
		/*! get a specific value in the registry */
		long GetStringValue(RootKey hrk, char * cKeyName, char * cValueName, char * cValue, char * cDefaultValue);
	};
};

#endif /* REGISTRY_H */