/**
 * \file 		Chrono.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#include <stddef.h>

#include "Chrono.h"

#ifdef _WINDOWS
using namespace std;
#include <stdlib.h>
#endif // _WINDOWS

#ifdef LINUX
#include <string.h>
#endif // LINUX

/** get an absolute value of time */
long Timing::Chrono::getAbsoluteTime_ms() {
    long lChronoValueMs = 0;
    
#ifdef LINUX
    struct timeval tv;
    gettimeofday(&tv, NULL);
    lChronoValueMs = ((long) (tv.tv_sec) * (long) (THOUSAND) + (long) (tv.tv_usec)) / 1000;
#endif //LINUX
    
#ifdef _WINDOWS
#ifdef CYGWIN
    struct timespec requestStart;
    clock_gettime(CLOCK_REALTIME, &requestStart);

    lChronoValueMs = (long) requestStart.tv_sec * (long) (THOUSAND) + (long) requestStart.tv_nsec / (long) BILLION;
#else //CYGWIN
    LARGE_INTEGER li;
    QueryPerformanceFrequency(&li);
	double _dFrequency = double(li.QuadPart) / 1000.0;

    // get the absolute start
    QueryPerformanceCounter(&li);
	__int64 _lNumberTicks = li.QuadPart;

	double _dTimeRetValue = (double)_lNumberTicks / _dFrequency;
    lChronoValueMs = (long)(_dTimeRetValue);
#endif //CYGWIN
#endif //_WINDOWS
    return lChronoValueMs;
}

/** main constructor of chronoS*/
Timing::Chrono::Chrono() {
#ifdef _WINDOWS
#ifndef CYGWIN
    m_i64CounterStart = 0;
    m_PCFreq = 0.0;
#endif //CYGWIN
#endif //_WINDOWS
#ifdef LINUX
    memset(&m_startTime, 0x00, sizeof(timeval));
#endif
}

/** desconstructor of chronoS*/
Timing::Chrono::~Chrono() {
}

/** function to start a chronometer, init start time  */
long Timing::Chrono::startChrono() {
#ifdef _WINDOWS
#ifndef CYGWIN
    LARGE_INTEGER li;
    QueryPerformanceFrequency(&li);

    // get the frequency of cpu
    m_PCFreq = double(li.QuadPart) / 1000.0;

    // get the absolute start
    QueryPerformanceCounter(&li);
    m_i64CounterStart = li.QuadPart;

    return CHRONO_OK;
#endif //CYGWIN
#endif //_WINDOWS
    
#ifdef LINUX
    gettimeofday(&m_startTime, NULL);
	return CHRONO_OK;
#endif // LINUX
}

/** function to get the absolute time according to startChrono()*/
double Timing::Chrono::getTime_ms() {
#ifdef _WINDOWS
#ifndef CYGWIN
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - m_i64CounterStart) / m_PCFreq;
#endif //CYGWIN
#endif //_WINDOWS
    
#ifdef LINUX
    struct timeval end;
    long seconds, useconds, shiftTime;    
    gettimeofday(&end, NULL);

    seconds  = end.tv_sec - m_startTime.tv_sec;
    useconds = end.tv_usec - m_startTime.tv_usec;

    shiftTime = ((seconds) * 1000 + useconds/1000.0) + 0.5;       
    return (double)shiftTime;
#endif // LINUX    
}

/** function to return the absolute time value */
unsigned long Timing::Chrono::getAbsoluteTime() {
#ifdef _WINDOWS
#ifndef CYGWIN
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return unsigned long(li.QuadPart - m_i64CounterStart);
#endif //CYGWIN
#endif //_WINDOWS
    
#ifdef LINUX
    struct timeval end;
    long seconds, useconds, shiftTime;    
    gettimeofday(&end, NULL);

    seconds  = end.tv_sec - m_startTime.tv_sec;
    useconds = end.tv_usec - m_startTime.tv_usec;

    shiftTime = ((seconds) * 1000 + useconds/1000.0) + 0.5;       
    return shiftTime;
#endif // LINUX
}