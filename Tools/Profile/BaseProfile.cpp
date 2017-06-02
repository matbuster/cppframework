
#include <string.h>
#include "BaseProfile.h"

// --------------------------------------------------------------
Tools::Profile::BaseProfile::BaseProfile()
{
	m_strFirstName = KEY_UNKNWON;
	m_strLastName = KEY_UNKNWON;
	m_strSurname = KEY_UNKNWON;
	m_strActuelLocation = KEY_UNKNWON;
	m_iAge = 0;
	m_gender = Tools::Profile::unknwon;
	m_birthdate = Timing::Date::DateTime::Now();
}
Tools::Profile::BaseProfile::~BaseProfile()
{
	if(NULL != m_birthdate) 
	{
		delete m_birthdate;
	}
}
// --------------------------------------------------------------
std::string Tools::Profile::BaseProfile::getFirstName()
{
	return m_strFirstName;
}
std::string Tools::Profile::BaseProfile::getLastName()
{
	return m_strLastName;
}
std::string Tools::Profile::BaseProfile::getSurname()
{
	return m_strSurname;
}
std::string Tools::Profile::BaseProfile::getActuelLocation()
{
	return m_strActuelLocation;
}
int Tools::Profile::BaseProfile::getAge()
{
	return m_iAge;
}
Tools::Profile::ProfileGender Tools::Profile::BaseProfile::getGender()
{
	return m_gender;
}
Timing::Date::DateTime * Tools::Profile::BaseProfile::getBirthdate()
{
	return m_birthdate;
}
// --------------------------------------------------------------
void Tools::Profile::BaseProfile::setFirstName(std::string _strFirstname)
{
	m_strFirstName = _strFirstname;
}
void Tools::Profile::BaseProfile::setLastName(std::string _strLastname)
{
	m_strLastName = _strLastname;
}
void Tools::Profile::BaseProfile::setSurname(std::string _strSurname)
{
	m_strSurname = _strSurname;
}
void Tools::Profile::BaseProfile::setActuelLocation(std::string _strLocation)
{
	m_strActuelLocation = _strLocation;
}
void Tools::Profile::BaseProfile::setAge(int _iAge)
{
	m_iAge = _iAge;
}
void Tools::Profile::BaseProfile::setGender(Tools::Profile::ProfileGender _gender)
{
	m_gender = _gender;
}
void Tools::Profile::BaseProfile::setBirthdate(Timing::Date::DateTime * /*_birthdate*/)
{
}
// --------------------------------------------------------------
