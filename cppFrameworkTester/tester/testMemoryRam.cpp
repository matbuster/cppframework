
#include "testMemoryRam.h"
#include "cppFrameworkTesterDefines.h"

// Memory Tools
#include "Memory/RAM.h"

// include conversion
#include "Tools/Conversion/SizeFileConversion.h"
#include "Tools/Hardware/CPU.h"

// debug tools
#include "Debug/assertion.h"

#include <stdio.h>
#include <stdlib.h>
// ----------------------------------------------------------
#define SIZE_ONE_MEGA					1024 * 1024
#define DBL_MEMORY_SHIFT_ACCURACY		0.1
// ----------------------------------------------------------

int tester_one_mega_allocation() {

    int iRetValue = TEST_OK;

    Memory::Ram * mem = new Memory::Ram();
    double _dPhysicalMemoryStartup = mem->getPhysicalMemoryShiftFromCurrentProcess_mo();

    char * _pAllocatedBuffer = (char*) malloc(SIZE_ONE_MEGA);
    double _dPhysicalMemoryShift = mem->getPhysicalMemoryShiftFromCurrentProcess_mo();

    printf("[DEBUG]\t[Memory]\t[tester_one_mega_allocation]\tPhysical memory for current process %0.6f Mo\n", (_dPhysicalMemoryShift - _dPhysicalMemoryStartup));
    if (1.2 == (_dPhysicalMemoryShift - _dPhysicalMemoryStartup)) {
        Debug::Assert(false, "Accuracy for testing allocation is not efficient.");
        iRetValue = TEST_KO;
    }

    free(_pAllocatedBuffer);

    _dPhysicalMemoryStartup = mem->getPhysicalMemoryShiftFromCurrentProcess_mo();
    _pAllocatedBuffer = (char*) malloc(10 * SIZE_ONE_MEGA);
    _dPhysicalMemoryShift = mem->getPhysicalMemoryShiftFromCurrentProcess_mo();

    printf("[DEBUG]\t[Memory]\t[tester_one_mega_allocation]\tPhysical memory for current process %0.6f Mo\n", (_dPhysicalMemoryShift - _dPhysicalMemoryStartup));
    if (10.2 == (_dPhysicalMemoryShift - _dPhysicalMemoryStartup)) {
        Debug::Assert(false, "Accuracy for testing allocation is not efficient.");
        iRetValue = TEST_KO;
    }

    free(_pAllocatedBuffer);
    delete mem;
    return iRetValue;
}
// ----------------------------------------------------------

int tester_total_virtual_memory() {

    int iReturnCode = TEST_KO;

    Memory::Ram * mem = new Memory::Ram();
    uint64_t _ui64TotalVirtualMem = mem->getTotalVirtualMemory();
    printf("[DEBUG]\t[Memory]\t[tester_total_virtual_memory]\tTotal Virtual Mem %llu bytes\n", _ui64TotalVirtualMem);
    if (0 == _ui64TotalVirtualMem) {
        Debug::Assert(false, "Total Virtual Mem cannot be equals to Zero.");
        iReturnCode = TEST_KO;
    }

    delete mem;
    return iReturnCode;
}
// ----------------------------------------------------------

int tester_virtual_memory_currently_used() {

    int iReturnCode = TEST_KO;
    Memory::Ram * mem = new Memory::Ram();
    uint64_t _ui64VirtualMemoryCurrentlyUsed = mem->getVirtualMemoryCurrentlyUsed();
    printf("[DEBUG]\t[Memory]\t[tester_virtual_memory_currently_used]\tVirtual memory currently used %llu bytes\n", _ui64VirtualMemoryCurrentlyUsed);
    if (0 == _ui64VirtualMemoryCurrentlyUsed) {
        Debug::Assert(false, "Virtual memory currently used cannot be equals to Zero.");
        iReturnCode = TEST_KO;
    }

    delete mem;
    return iReturnCode;
}
// ----------------------------------------------------------

int tester_virtual_memory_currently_used_by_current_process() {

    int iReturnCode = TEST_KO;
    Memory::Ram * mem = new Memory::Ram();
    uint64_t _ui64VirtualMemoryCurrentlyUsedForCurrentProcess = mem->getVirtualMemoryCurrentyUsedByProcess();
    printf("[DEBUG]\t[Memory]\t[tester_virtual_memory_currently_used_by_current_process]\tVirtual memory currently used for current process %llu bytes\n", _ui64VirtualMemoryCurrentlyUsedForCurrentProcess);
    if (0 == _ui64VirtualMemoryCurrentlyUsedForCurrentProcess) {
        Debug::Assert(false, "Virtual memory currently used for current process cannot be equals to Zero.");
        iReturnCode = TEST_KO;
    }

    delete mem;
    return iReturnCode;
}
// ----------------------------------------------------------

int tester_total_physics_memory() {

    int iReturnCode = TEST_KO;
    Memory::Ram * mem = new Memory::Ram();
    uint64_t _ui64TotalPhysicMem = mem->getTotalPhysicsMemory();
    printf("[DEBUG]\t[Memory]\t[tester_total_virtual_memory]\tTotal Physics Mem %llu bytes\n", _ui64TotalPhysicMem);
    if (0 == _ui64TotalPhysicMem) {
        Debug::Assert(false, "Total Physic Mem cannot be equals to Zero.");
        iReturnCode = TEST_KO;
    }

    delete mem;
    return iReturnCode;
}
// ----------------------------------------------------------

int tester_physic_memory_currently_used() {
    int iReturnCode = TEST_KO;
    Memory::Ram * mem = new Memory::Ram();

    uint64_t _ui64PhysicMemCurrentlyUsed = mem->getPhysicalMemoryCurrentlyUsed();
    printf("[DEBUG]\t[Memory]\t[tester_physic_memory_currently_used]\tPhysics Mem currently used %llu bytes\n", _ui64PhysicMemCurrentlyUsed);
    if (0 == _ui64PhysicMemCurrentlyUsed) {
        Debug::Assert(false, "Physics Mem currently used cannot be equals to Zero.");
        iReturnCode = TEST_KO;
    }

    delete mem;
    return iReturnCode;
}
// ----------------------------------------------------------

int tester_physic_memory_currently_used_by_current_process() {

    int iReturnCode = TEST_KO;
    Memory::Ram * mem = new Memory::Ram();

    uint64_t _ui64PhysicMemCurrentlyUsedByCurrentProcess = mem->getPhysicalMemoryCurrentlyUsedByProcess();
    printf("[DEBUG]\t[Memory]\t[tester_physic_memory_currently_used_by_current_process]\tPhysics Mem currently used by current process %llu bytes\n", _ui64PhysicMemCurrentlyUsedByCurrentProcess);
    if (0 == _ui64PhysicMemCurrentlyUsedByCurrentProcess) {
        Debug::Assert(false, "Physics Mem currently used by current process cannot be equals to Zero.");
        iReturnCode = TEST_KO;
    }

    printf("[DEBUG]\t[Memory]\tSize if Ko %0.3f Ko\n", Tools::Conversion::convertOctetsToKiloOctets(_ui64PhysicMemCurrentlyUsedByCurrentProcess));
    printf("[DEBUG]\t[Memory]\tSize if Ko %0.3f Mo\n", Tools::Conversion::convertOctetsToMegaOctets(_ui64PhysicMemCurrentlyUsedByCurrentProcess));

    delete mem;
    return iReturnCode;
}
// ----------------------------------------------------------

int tester_memory_ram() {

    int iReturnCode = TEST_KO;
    printf(STR_LINE_DISPLAY_SEP);
    printf("testing Memory::RAM\r\n");
    printf(STR_LINE_DISPLAY_SEP);

    //iReturnCode = tester_one_mega_allocation();
    // virtual memory
    iReturnCode = tester_total_virtual_memory();
    iReturnCode = tester_virtual_memory_currently_used();
    iReturnCode = tester_virtual_memory_currently_used_by_current_process();

    // physic memory
    iReturnCode = tester_total_physics_memory();
    iReturnCode = tester_physic_memory_currently_used();
    iReturnCode = tester_physic_memory_currently_used_by_current_process();

    // testing cpu occupation
    double _dCPUCurrentValue = Tools::Hardware::getCPUCurrentlyUsed();
	double _dCPUCurrentProcessValue = Tools::Hardware::getCPUCurrentluUsedByProcess();
	int _iNumPross = Tools::Hardware::getNumberProcessor();

    printf("[DEBUG]\t[CPU]\tCPU current occupation %0.3f purcent\n", _dCPUCurrentValue);
    printf("[DEBUG]\t[CPU]\tCPU current process occupation %0.3f purcent\n", _dCPUCurrentProcessValue);
	printf("[DEBUG]\t[CPU]\tNumber processor %d\n", _iNumPross);

    return iReturnCode;
}
// ----------------------------------------------------------
