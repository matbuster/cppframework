/**
 * \file 		Timing.cpp
 * \date 		20/03/2015 
 * \author 		NSJ
 */ 
 
// Include des en-tetes du framework
#include "Timing.h"

// Include des en-tetes standard c
#include <stdio.h>
#include <string.h>

#ifdef LINUX
#include <unistd.h>
#include <sys/time.h>
#endif //LINUX

#ifdef _CYGWIN
#include <unistd.h>
#include <sys/time.h>
#endif //_CYGWIN

#ifdef _WINDOWS
#include <windows.h>
#endif //_WINDOWS

long Timing::Timing::sleepInMicroSecond(unsigned long iDuration) {
#ifdef _CYGWIN
    return usleep(iDuration);
#endif //_CYGWIN

#ifdef LINUX
    return usleep(iDuration);
#endif //LINUX

#ifdef _WINDOWS
    Sleep(iDuration / 1000);
    return 0;
#endif //_WINDOWS
}

long Timing::Timing::sleepInMilliSecond(unsigned long iDuration) {
#ifdef _CYGWIN
    return usleep(iDuration * 1000);
#endif //_CYGWIN

#ifdef LINUX
    return usleep(iDuration * 1000);
#endif //LINUX

#ifdef _WINDOWS
    Sleep(iDuration);
    return 0;
#endif //_WINDOWS
}

long Timing::Timing::sleepInSecond(unsigned long iDuration) {
#ifdef _CYGWIN
    return usleep(iDuration * 1000000);
#endif //_CYGWIN    

#ifdef LINUX
    return usleep(iDuration * 1000000);
#endif //LINUX

#ifdef _WINDOWS
    Sleep(iDuration * 1000);
    return 0;
#endif //_WINDOWS
}

double Timing::Timing::sysGetTime() {
    double dtimevalue = 0;
#ifdef LINUX 

    //TODO_NSJ// Voir laquelle est utilise ds la carte HSM

    //Methode 1
    struct timeval tv;
    gettimeofday(&tv, NULL);

    dtimevalue = (double) (tv.tv_sec) + ((double) (tv.tv_usec) / (double) (THOUSAND));

    //Methode 2
    /*double totalStart = 0;
struct timespec requestStart;
clock_gettime(CLOCK_REALTIME, &requestStart);

dtimevalue = requestStart.tv_sec + requestStart.tv_nsec / BILLION;*/
#endif //LINUX

    return dtimevalue;
}

double Timing::Timing::sysWatchTime(char * message, double dStartTime) {

	//TODO_MAT// use message mother fucker !!!
    double dStopTime = sysGetTime();
    double dEllapsedTime = dStopTime - dStartTime;
    return dEllapsedTime;
}
