#ifndef HARDWARE_CPU_H
#define HARDWARE_CPU_H

namespace Tools {

    // using sample from : http://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
    // TODO : test because windows function return Max Double and unix nan
    namespace Hardware {

        /** getter on the value of CPU currently used
         * @return value of CPU occupation
         */
        double getCPUCurrentlyUsed();

        /** getter on the value of CPU currently used by current process
         * @return value of CPU occupation by the current process
         */
        double getCPUCurrentluUsedByProcess();

        /** getter on the number of processor
         * @return value of the number of processor available on this computer
         */
        int getNumberProcessor();
    };
};

#endif // HARDWARE_CPU_H