/**
 * \file 		CommonStats.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 
 
#include <stddef.h>

#include "CommonStats.h"

Math::Statistics::CommonStats::CommonStats() 
{
	m_dValues = new std::list<double>();
	m_dMin = MAX_DOUBLE;
	m_dMax = MIN_DOUBLE ;
}
Math::Statistics::CommonStats::~CommonStats() 
{
	delete m_dValues;
}
void Math::Statistics::CommonStats::mergeValues(CommonStats * stats)
{
	for( std::list<double>::iterator it = stats->getValues()->begin(); it != stats->getValues()->end(); it++)
	{
		AddValue(*it);
	}
	m_dMin = getMin();
	m_dMax = getMax() ;
}
void Math::Statistics::CommonStats::AddValue(double value)
{
	if(NULL == m_dValues) 
	{
		return;
	}
	m_dValues->push_back(value);
	if(value < m_dMin)
	{
		m_dMin = value;
	}
	if(value > m_dMax)
	{
		m_dMax = value;
	}
}
std::list<double> * Math::Statistics::CommonStats::getValues()
{
	return m_dValues;
}
double Math::Statistics::CommonStats::getAverage()
{
	if(NULL == m_dValues) 
	{
		return -1.0f;
	}

	double dAverageValue = 0.0;
	for(std::list<double>::iterator it = m_dValues->begin(); it != m_dValues->end(); it++)
	{
		dAverageValue += *it;
	}
	dAverageValue /= m_dValues->size();
	return dAverageValue;
}
double Math::Statistics::CommonStats::getStdev()
{
	return 0.0;
}
double Math::Statistics::CommonStats::getMin()
{
	return m_dMin;
}
double Math::Statistics::CommonStats::getMax()
{
	return m_dMax;
}
	