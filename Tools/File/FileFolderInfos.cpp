
#include "FileFolderInfos.h"
#include "Directory.h"

// -----------------------------------------------------------
Tools::Files::FileFolderInfos::FileFolderInfos()
{
	m_creationDateInfos = new Timing::Date::DateTime();
	m_lFileSize = 0;
	m_bReadPermission = false;
	m_bWritePermission = false;
	m_bExexPermission = false;
}
// -----------------------------------------------------------
Tools::Files::FileFolderInfos::~FileFolderInfos()
{
	delete m_creationDateInfos;
}
// -----------------------------------------------------------
std::string Tools::Files::FileFolderInfos::getFilepath()
{
	return m_strFilepath;
}
// -----------------------------------------------------------
void Tools::Files::FileFolderInfos::setFilepath(std::string _strfilepath)
{
	m_strFilepath = _strfilepath;
}
// -----------------------------------------------------------
std::string Tools::Files::FileFolderInfos::getFilename()
{
	return m_strFilename;
}
// -----------------------------------------------------------
void Tools::Files::FileFolderInfos::setFilename(std::string _strfilename)
{
	m_strFilename = _strfilename;
}
// -----------------------------------------------------------
std::string Tools::Files::FileFolderInfos::getFullName()
{
	std::string value;
	value.append(m_strFilepath.c_str(), strlen(m_strFilepath.c_str())-1 );
	value.append(std::string(PATH_SEPARATOR));
	value.append(m_strFilename);

	return value;
}
// -----------------------------------------------------------
Timing::Date::DateTime * Tools::Files::FileFolderInfos::getCreationDateInformations()
{
	return m_creationDateInfos;
}
// -----------------------------------------------------------
void Tools::Files::FileFolderInfos::setCreationDateInformation(Timing::Date::DateTime * date)
{
	m_creationDateInfos = date;
}
// -----------------------------------------------------------
long Tools::Files::FileFolderInfos::getFileSize()
{
	return m_lFileSize;
}
// -----------------------------------------------------------
void Tools::Files::FileFolderInfos::setFileSize(long _lSize)
{
	m_lFileSize = _lSize;
}
// -----------------------------------------------------------
std::string Tools::Files::FileFolderInfos::getTypeKeyword()
{
	if(m_eType == Tools::Files::folder)
	{
		return KEY_DIRECTORY;
	} 
	else 
	{
		return KEY_FILE;
	}
}
// -----------------------------------------------------------
Tools::Files::FileFolderType Tools::Files::FileFolderInfos::getType()
{
	return m_eType;
}
// -----------------------------------------------------------
void Tools::Files::FileFolderInfos::setType(Tools::Files::FileFolderType eType)
{
	m_eType = eType;
}
// -----------------------------------------------------------			
std::string Tools::Files::FileFolderInfos::getCreationDate()
{
	return m_strFormattedCreationDate;
}
// -----------------------------------------------------------			
std::string Tools::Files::FileFolderInfos::getModificationDate()
{
	return m_strFormattedModificationDate;
}
// -----------------------------------------------------------			
std::string Tools::Files::FileFolderInfos::getLastAccessDate()
{
	return m_strFormatedLastAccesDate;
}
// -----------------------------------------------------------			
void Tools::Files::FileFolderInfos::setFormattedModificationDate(std::string _strModificationDate)
{
	m_strFormattedModificationDate = _strModificationDate;
}
// -----------------------------------------------------------
void Tools::Files::FileFolderInfos::setFormattedCreationDate(std::string _strCreationDate)
{
	m_strFormattedCreationDate = _strCreationDate;
}
// -----------------------------------------------------------
void Tools::Files::FileFolderInfos::setFormattedLastAccessDate(std::string _strLastAccessDate)
{
	m_strFormatedLastAccesDate = _strLastAccessDate;
}
// -----------------------------------------------------------
bool Tools::Files::FileFolderInfos::isReadingAllowed()
{
	return m_bReadPermission;
}
// -----------------------------------------------------------
void Tools::Files::FileFolderInfos::setReadingAllowedProperty(bool _bValue)
{
	m_bReadPermission = _bValue;
}
// -----------------------------------------------------------
bool Tools::Files::FileFolderInfos::isWritingAllowed()
{
	return m_bWritePermission;
}
// -----------------------------------------------------------
void Tools::Files::FileFolderInfos::setWritingAllowedProperty(bool _bValue)
{
	m_bWritePermission = _bValue;
}
// -----------------------------------------------------------
bool Tools::Files::FileFolderInfos::isExecAllowed()
{
	return m_bExexPermission;
}
// -----------------------------------------------------------
void Tools::Files::FileFolderInfos::setExecAllowedProperty(bool _bValue)
{
	m_bExexPermission = _bValue;
}
// -----------------------------------------------------------
