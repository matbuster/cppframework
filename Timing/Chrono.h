/**
 * \file 		Chrono.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

 #ifndef CHRONO_H
#define CHRONO_H

#define BILLION         1E9
#define THOUSAND        1E6

#define CHRONO_OK	0
#define CHRONO_KO	1

#ifdef LINUX
#include <sys/time.h>
#endif

#ifdef _WINDOWS
#include <windows.h>
#endif

namespace Timing
{
    /** class chrono implementation, not yet implemeted*/
	class Chrono
	{
	private:
#ifdef _WINDOWS
#ifndef CYGWIN
		/** windows implementation non cygwin*/
		double m_PCFreq;

		/** absolute start of program */
		__int64 m_i64CounterStart;
#endif
#endif
                
#ifdef LINUX
                /** absolute start of program */
                struct timeval m_startTime;
#endif // LINUX
	public:
        Chrono();
        ~Chrono();

		/** function to start a chronometer, init start time  */
		long startChrono();

		/** function to get the absolute time according to startChrono()*/
		double getTime_ms();

		/** function to return the absolute time value */
		unsigned long getAbsoluteTime();

        /** function to get the absolute time */
        static long getAbsoluteTime_ms();                
	};
};

#endif /* CHRONO_H */