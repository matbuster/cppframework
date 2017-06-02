/**
 * \file 		Date.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#include "Date.h"
#include "../toolsconstant.h"

#ifdef _WINDOWS
#include <windows.h>
#endif
#include <stdio.h>

// ---------------------------------------------------------------------------------------------------
Timing::Date::DateTime::DateTime()
{
#ifdef _WINDOWS
	time (&m_rawtime);

	SYSTEMTIME time;
	GetLocalTime(&time);

	m_iYear = time.wYear;
	m_iMonth = time.wMonth;
	m_iDayOfTheWeek = time.wDayOfWeek;
	m_iDay = time.wDay;
	m_iHour = time.wHour;
	m_iMinutes = time.wMinute;
	m_iSeconds = time.wSecond;
	m_iMillesconds = time.wMilliseconds;
#else
	// implement for UNIX
	m_iYear = 0;
	m_iMonth = 0;
	m_iDayOfTheWeek = 0;
	m_iDay = 0;
	m_iHour = 0;
	m_iMinutes = 0;
	m_iSeconds = 0;
	m_iMillesconds = 0;
#endif // _WINDOWS
}
Timing::Date::DateTime::~DateTime()
{
}
// ---------------------------------------------------------------------------------------------------
/** getters */
int Timing::Date::DateTime::getYear() const
{
	return m_iYear;
}
int Timing::Date::DateTime::getMonth() const
{
	return m_iMonth;
}
int Timing::Date::DateTime::getDay() const
{
	return m_iDay;
}
int Timing::Date::DateTime::getHour() const
{
	return m_iHour;
}
int Timing::Date::DateTime::getMinutes() const
{
	return m_iMinutes;
}
int Timing::Date::DateTime::getSeconds() const
{
	return m_iSeconds;
}
int Timing::Date::DateTime::getMilliseconds() const
{
	return m_iMillesconds;
}

const char * Timing::Date::DateTime::getFormated(const char * _format)
{
	struct tm * timeinfo;
	timeinfo = localtime (&m_rawtime);
	strftime (m_buffer,80,_format,timeinfo);
	return m_buffer;
}

// ---------------------------------------------------------------------------------------------------
/** setters */
void Timing::Date::DateTime::setDate(int _iYear, int _iMonth, int _iDay)
{
	m_iYear = _iYear;
	m_iMonth = _iMonth;
	m_iDay = _iDay;
}
void Timing::Date::DateTime::setTime(int _iHour, int _iMinutes, int _iSeconds)
{
	m_iHour = _iHour;
	m_iMinutes = _iMinutes;
	m_iSeconds = _iSeconds;
	m_iMillesconds = 0;
}
void Timing::Date::DateTime::setTime(int _iHour, int _iMinutes, int _iSeconds, int _iMilliseconds)
{
	m_iHour = _iHour;
	m_iMinutes = _iMinutes;
	m_iSeconds = _iSeconds;
	m_iMillesconds = _iMilliseconds;
}
// ---------------------------------------------------------------------------------------------------
bool Timing::Date::operator< (Timing::Date::DateTime const &d1, Timing::Date::DateTime const &d2)
{
	return d1.getYear() < d2.getYear() &&
		d1.getMonth() < d2.getMonth() &&
		d1.getDay() < d2.getDay() &&
		d1.getHour() < d2.getHour() &&
		d1.getMinutes() < d2.getMinutes() &&
		d1.getSeconds() < d2.getSeconds() &&
		d1.getMilliseconds() < d2.getMilliseconds();
}
// ---------------------------------------------------------------------------------------------------
Timing::Date::DateTime * Timing::Date::DateTime::Now()
{
	return new Timing::Date::DateTime();
}
// ---------------------------------------------------------------------------------------------------
/** return a date string value to prefix a file name
 * example : YYYY_MM_DD_HH_MM_SS_
 */
long Timing::Date::GetStringDateForFile(char * _pOutDateFormatted, int _iSizeBuffer, int * _iDateSize)
{
#ifdef _WINDOWS
	char pTempDate[STR_TINY];
	memset(pTempDate, 0x00, STR_TINY);

	SYSTEMTIME time;
	GetLocalTime(&time);

	sprintf(pTempDate, "%d_%d_%d_%d_%d_%d_",time.wYear,time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	if(STR_TINY > _iSizeBuffer)
	{
		return DATE_KO;
	}
	memcpy(_pOutDateFormatted, pTempDate, STR_TINY);
	*_iDateSize = STR_TINY;
#endif
	return DATE_OK;
}
// ---------------------------------------------------------------------------------------------------
