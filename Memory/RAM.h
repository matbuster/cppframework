/**
 * \file 		RAM.h
 * \date 		04/11/2015 
 * \author 		MAT
 */

#ifndef RAM_H
#define RAM_H

#include <stdint.h>

namespace Memory {


    // helpfull link for different memory usage : http://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process

    class Ram {
    private:
        /** internal snapshot total memory physics store at creation */
        uint64_t m_ui64TotalPhysicsMemory;

        /** internal snapshot total memory virtual store at creation */
        uint64_t m_ui64TotalVirtualMemory;

        /** internal snapshot available memory physics store at creation */
        uint64_t m_ui64AvailablePhysicsMemory;

        /** internal snapshot available memory virtual store at creation  */
        uint64_t m_ui64AvailableVirtualMemory;

        /** internal snapshop of physical memory usage by process at creation */
        uint64_t m_ui64PhysicalUsedByProcess;
#ifdef LINUX
        /**! unix only to parse brievly content of memory file*/
        int parseLine(char* line);
#endif // LINUX
    public:
        Ram();
        ~Ram();

        /** 
         * The amount of physical memory currently available, in bytes. 
         * This is the amount of physical memory that can be immediately reused without 
         * having to write its contents to disk first. 
         * It is the sum of the size of the standby, free, and zero lists.
         * @return total physics memory in bytes
         */
        uint64_t getTotalPhysic_bytes();

        /** The size of the user-mode portion of the virtual address space of the calling process, 
         * in bytes. This value depends on the type of process, the type of processor, and the configuration
         * of the operating system. For example, this value is approximately 2 GB for most 32-bit processes
         * on an x86 processor and approximately 3 GB for 32-bit processes that are large address aware 
         * running on a system with 4-gigabyte tuning enabled.
         * @return total virtual memory in bytes
         */
        uint64_t getTotalVirtual_bytes();

        /** The amount of physical memory currently available, in bytes. 
         * This is the amount of physical memory that can be immediately reused without 
         * having to write its contents to disk first. 
         * It is the sum of the size of the standby, free, and zero lists.
         * @return available physics memory in bytes
         */
        uint64_t getAvailablePhysic_bytes();

        /** The amount of unreserved and uncommitted memory currently in the 
         * user-mode portion of the virtual address space of the calling process, in bytes.
         * @return available virtual memory in bytes
         */
        uint64_t getAvailableVirtual_bytes();

        /** get the current memomry usage for the current process
         * @return current physical memory used by currenr process
         */
        uint64_t getPhysicalUsedByCurrentProcess_bytes();

        /** get total physical memory in mo
         */
        double getTotalPhysic_mo();

        /** get total virtual memory in mo
         */
        double getTotalVirtual_mo();

        /** get physics available memory in mo
         */
        double getAvailablePhysic_mo();

        /** get virtual memory available in mo 
         */
        double getAvailableVirtual_mo();

        /** function to get the physical memory shift generate by current process in bytes
         */
        uint64_t getPhysicalMemoryShiftFromCurrentProcess_bytes();

        /** function to get the physical memory shift generate by current process in mo
         */
        double getPhysicalMemoryShiftFromCurrentProcess_mo();

        // -------------------------------------------------------------
        // -------------------------------------------------------------
        // New implementation
        /** getter on Total Virtual Memory
         * @return Total Virtual Memory in bytes
         */
        uint64_t getTotalVirtualMemory();

        /** getter on Virtual memory currently used
         * @return Virtual Memory currently used in bytes
         */
        uint64_t getVirtualMemoryCurrentlyUsed();

		/** getter on virtual memory currently used by process
		 *@return cirtual memory currently used by process in bytes
		 */
		uint64_t getVirtualMemoryCurrentyUsedByProcess();

        /**
         * getter on the total physics memory
         * @return  total physics memory in bytes
         */
        uint64_t getTotalPhysicsMemory();

		/** getter on the physical memory currently used
		 * @return physical memory currently used
		 */
		uint64_t getPhysicalMemoryCurrentlyUsed();

		/** getter on the Physical memory used by current process
		 * @return physical me
		 */
		uint64_t getPhysicalMemoryCurrentlyUsedByProcess();
    };
};

#endif /* RAM_H */