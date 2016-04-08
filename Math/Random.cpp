/**
 * \file 		Random.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#include "Random.h"

// -----------------------------------------------------------
Math::Random::Random()
{
	m_chrono = new Timing::Chrono();
}
Math::Random::~Random()
{
	delete m_chrono;
}
// -----------------------------------------------------------
int Math::Random::getNextInt(int iMaxValue)
{
	unsigned long value = m_chrono->getAbsoluteTime();
	unsigned int iCalculatedValue = (unsigned int)(value) % iMaxValue;
	return iCalculatedValue;
}
// -----------------------------------------------------------

