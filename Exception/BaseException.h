/**
 * \file 		BaseException.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H

#include <exception>
#include <iostream>

#define STR_BASE_EXCEPTION	"A unknown BaseException happened"

namespace Exception {

	/** implement function base exception */
	class BaseException : std::exception
	{

	private:
		/** message exception */
		std::string m_strMessage;

	public:
		/** main constructor and destructor */
		BaseException() throw();
		BaseException(const char * _pConstChar) throw();
		virtual ~BaseException() throw();

		/** override internal what function. Need to be reimplemented for inheritance */
		virtual const char* what() const throw()
		{
			return m_strMessage.c_str();
		}		
	};
};

#endif /* EXCEPTION_H */