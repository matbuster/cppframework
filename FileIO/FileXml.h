/**
 * \file 		FileXml.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#ifndef XML_FILE_H
#define XML_FILE_H

#include "..\toolsconstant.h"
#include "FileTxt.h"

namespace FileIO {
	
	class FileXml : FileTxt {
	
	public:
		FileXml(char * cFilename);
		virtual ~FileXml();
	};
};

#endif /* XML_FILE_H */