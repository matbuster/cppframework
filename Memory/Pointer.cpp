/**
 * \file 		Pointer.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#include <stddef.h>

#include "Pointer.h"

#ifdef _WINDOWS
#include <Windows.h>
#endif 

#define P_ABABABAB_MSG "0xABABABAB : Used by Microsoft's HeapAlloc() to mark no man's land guard bytes after allocated heap memory"
#define P_ABADCAFE_MSG "0xABADCAFE : A startup to this value to initialize all free memory to catch errant pointers"
#define P_BAADF00D_MSG "0xBAADF00D : Used by Microsoft's LocalAlloc(LMEM_FIXED) to mark uninitialised allocated heap memory"
#define P_BADCAB1E_MSG "0xBADCAB1E : Error Code returned to the Microsoft eVC debugger when connection is severed to the debugger"
#define P_BEEFCACE_MSG "0xBEEFCACE : Used by Microsoft .NET as a magic number in resource files"
#define P_CCCCCCCC_MSG "0xCCCCCCCC : Used by Microsoft's C++ debugging runtime library to mark uninitialised stack memory"
#define P_CDCDCDCD_MSG "0xCDCDCDCD : Used by Microsoft's C++ debugging runtime library to mark uninitialised heap memory"
#define P_DEADDEAD_MSG "0xDEADDEAD : A Microsoft Windows STOP Error code used when the user manually initiates the crash."
#define P_FDFDFDFD_MSG "0xFDFDFDFD : Used by Microsoft's C++ debugging heap to mark no man's land guard bytes before and after allocated heap memory"
#define P_FEEEFEEE_MSG "0xFEEEFEEE : Used by Microsoft's HeapFree() to mark freed heap memory"

// -------------------------------------------------------------------------
bool Memory::CheckPointerValue(int * pointerValue)
{
	if(NULL == pointerValue) return false;
#ifdef _WINDOWS
	else if(0xABADCAFE == (int)pointerValue) return false;
	else if(0xABADCAFE == (int)pointerValue) return false;
	else if(0xBAADF00D == (int)pointerValue) return false;
	else if(0xBADCAB1E == (int)pointerValue) return false;
	else if(0xBEEFCACE == (int)pointerValue) return false;
	else if(0xCCCCCCCC == (int)pointerValue) return false;
	else if(0xCDCDCDCD == (int)pointerValue) return false;
	else if(0xDEADDEAD == (int)pointerValue) return false;
	else if(0xFDFDFDFD == (int)pointerValue) return false;
	else if(0xFEEEFEEE == (int)pointerValue) return false;
#endif
	return true;
}
// -------------------------------------------------------------------------
const char * Memory::getPointerValueCorrespondingMessage(int * /*pointerValue*/)
{
	return "";
}
// -------------------------------------------------------------------------
