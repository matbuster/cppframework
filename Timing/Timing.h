/**
 * \file 		Timing.h
 * \date 		20/03/2015 
 * \author 		NSJ
 */ 

#ifndef _TIMING_H_
#define _TIMING_H_

#define BILLION         1E9
#define THOUSAND        1E6

namespace Timing {

    class Timing {
    public:
        Timing();
        ~Timing();

        static long sleepInSecond(unsigned long iDuration);
        static long sleepInMilliSecond(unsigned long iDuration);
        static long sleepInMicroSecond(unsigned long iDuration);

        /** function to get the current time value, use CLOCK_REALTIME or ITIMER_REAL
         * depending of the OS. Return a value in Second */
        static double sysGetTime(void);

        /**
         * function to calculate time using the last start time
         * @param message: if message NULL, don't log any information in console
         * @param dStartTime: start time
         * @return return the last time stamp
         */
        static double sysWatchTime(char * message, double dStartTime);
    };
};

#endif //_TIMING_H_
