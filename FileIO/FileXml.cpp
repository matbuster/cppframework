/**
 * \file 		FileXml.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#include "FileXml.h"

FileIO::FileXml::FileXml(char * cFilename)
	: FileIO::FileTxt(cFilename)
{	
	FileTxtOpen(fileappend);
}
FileIO::FileXml::~FileXml()
{
	FileTxtClose();
}