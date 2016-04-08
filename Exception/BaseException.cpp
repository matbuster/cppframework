/**
 * \file 		BaseException.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#include "BaseException.h"

// ------------------------------------------------------------------
/** main constructor and destructor */
Exception::BaseException::BaseException()
	: std::exception()
{
	m_strMessage=STR_BASE_EXCEPTION;
}
Exception::BaseException::BaseException(const char * _pConstChar)
	: std::exception()
{
	m_strMessage = std::string(_pConstChar);
}
Exception::BaseException::~BaseException()
{
}
// ------------------------------------------------------------------