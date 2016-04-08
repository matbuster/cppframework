/**
 * \file 		RAM.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */
 
#include "RAM.h"

#ifdef WIN32
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <psapi.h>
// comment include in project dependencies psapi.lib
#endif /* WIN32 */

#ifdef LINUX
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#endif /* LINUX */

using namespace std;

// -----------------------------------------------------------------

Memory::Ram::Ram() {
    m_ui64TotalPhysicsMemory = getTotalPhysic_bytes();
    m_ui64TotalVirtualMemory = getAvailableVirtual_bytes();
    m_ui64AvailablePhysicsMemory = getAvailablePhysic_bytes();
    m_ui64AvailableVirtualMemory = getAvailableVirtual_bytes();
    m_ui64PhysicalUsedByProcess = getPhysicalUsedByCurrentProcess_bytes();
}
// -----------------------------------------------------------------

Memory::Ram::~Ram() {
}

// -----------------------------------------------------------------
#ifdef LINUX
int Memory::Ram::parseLine(char* line){
    
    int i = strlen(line);
    while (*line < '0' || *line > '9') line++;
    line[i-3] = '\0';
    i = atoi(line);
    return i;
}
#endif
// -----------------------------------------------------------------

uint64_t Memory::Ram::getTotalPhysic_bytes() {
    uint64_t ui64Value = 0;
#ifdef WIN32
    MEMORYSTATUSEX statex = {0};

    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx(&statex);
    ui64Value = statex.ullTotalPhys;
#else
    struct sysinfo memInfo;
    
    sysinfo (&memInfo);
    long long totalPhysMem = memInfo.totalram;
    //Multiply in next statement to avoid int overflow on right hand side...
    totalPhysMem *= memInfo.mem_unit;
    ui64Value = totalPhysMem;
#endif
    return ui64Value;
}
// -----------------------------------------------------------------

uint64_t Memory::Ram::getTotalVirtual_bytes() {
    uint64_t ui64Value = 0;
#ifdef WIN32
    MEMORYSTATUSEX statex = {0};

    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx(&statex);
    ui64Value = statex.ullTotalVirtual;
#else
    struct sysinfo memInfo;
    
    sysinfo (&memInfo);
    long long totalVirtualMem = memInfo.totalram;
    //Add other values in next statement to avoid int overflow on right hand side...
    totalVirtualMem += memInfo.totalswap;
    totalVirtualMem *= memInfo.mem_unit;
    
    ui64Value = totalVirtualMem;
#endif
    return ui64Value;
}
// -----------------------------------------------------------------

uint64_t Memory::Ram::getAvailablePhysic_bytes() {
    uint64_t ui64Value = 0;
#ifdef WIN32
    MEMORYSTATUSEX statex = {0};

    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx(&statex);
    ui64Value = statex.ullAvailPhys;
#else
    struct sysinfo memInfo;
    
    sysinfo (&memInfo);
    long long physMemUsed = memInfo.totalram - memInfo.freeram;
    //Multiply in next statement to avoid int overflow on right hand side...
    physMemUsed *= memInfo.mem_unit;    
#endif
    return ui64Value;
}
// -----------------------------------------------------------------

uint64_t Memory::Ram::getAvailableVirtual_bytes() {
    uint64_t ui64Value = 0;
#ifdef WIN32
    MEMORYSTATUSEX statex = {0};

    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx(&statex);
    ui64Value = statex.ullAvailVirtual;
#else

#endif
    return ui64Value;
}
// -----------------------------------------------------------------		

uint64_t Memory::Ram::getPhysicalUsedByCurrentProcess_bytes() {
    uint64_t ui64Value = 0;
#ifdef WIN32
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof (pmc));
    ui64Value = pmc.WorkingSetSize;
#else
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
#endif
    return ui64Value;
}
// -----------------------------------------------------------------		

double Memory::Ram::getTotalPhysic_mo() {
    double dValue = 0.0;
    dValue = (double) getTotalPhysic_bytes() / (1024.0 * 1024.0);

    return dValue;
}
// -----------------------------------------------------------------

double Memory::Ram::getTotalVirtual_mo() {
    double dValue = 0.0;
    dValue = (double) getTotalVirtual_bytes() / (1024.0 * 1024.0);

    return dValue;
}
// -----------------------------------------------------------------

double Memory::Ram::getAvailablePhysic_mo() {
    double dValue = 0.0;
    dValue = (double) getAvailablePhysic_bytes() / (1024.0 * 1024.0);

    return dValue;
}
// -----------------------------------------------------------------

double Memory::Ram::getAvailableVirtual_mo() {
    double dValue = 0.0;
    dValue = (double) getAvailableVirtual_bytes() / (1024.0 * 1024.0);

    return dValue;
}
// -----------------------------------------------------------------

uint64_t Memory::Ram::getPhysicalMemoryShiftFromCurrentProcess_bytes() {

#ifdef WIN32
    uint64_t ui64MemShift = _abs64(getPhysicalUsedByCurrentProcess_bytes() - m_ui64PhysicalUsedByProcess);
#endif //WIN32

#ifdef LINUX
    uint64_t uiMemCurrentProcess = getPhysicalUsedByCurrentProcess_bytes();
    uint64_t ui64MemShift = abs(uiMemCurrentProcess - m_ui64PhysicalUsedByProcess);
    printf("[DEBUG]\t[UNIX]\t function return %llu\n", uiMemCurrentProcess);
    printf("[DEBUG]\t[UNIX]\t Shift mem return %llu\n", ui64MemShift);
#endif //LINUX 
    
    return ui64MemShift;
}
// -----------------------------------------------------------------

double Memory::Ram::getPhysicalMemoryShiftFromCurrentProcess_mo() {
    return ((double) getPhysicalMemoryShiftFromCurrentProcess_bytes() / (1024.0 * 1024.0));
}
// -----------------------------------------------------------------
// -------------------------------------------------------------
// -------------------------------------------------------------
// New implementation
uint64_t Memory::Ram::getTotalVirtualMemory() {
    
    uint64_t _ui64TotlaVirtualMemory = 0;
#ifdef WIN32
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;   
    _ui64TotlaVirtualMemory = totalVirtualMem;
#endif //WIN32

#ifdef LINUX
    struct sysinfo memInfo;

    sysinfo (&memInfo);
    long long totalVirtualMem = memInfo.totalram;
    //Add other values in next statement to avoid int overflow on right hand side...
    totalVirtualMem += memInfo.totalswap;
    totalVirtualMem *= memInfo.mem_unit;
    _ui64TotlaVirtualMemory = totalVirtualMem;
#endif // LINUX   
    return _ui64TotlaVirtualMemory;
}
// -------------------------------------------------------------
uint64_t Memory::Ram::getVirtualMemoryCurrentlyUsed() {    
	
	uint64_t _ui64VirtualMemoryCurrentlyUsed = 0;
#ifdef WIN32
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);    
	DWORDLONG virtualMemUsed = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;
	_ui64VirtualMemoryCurrentlyUsed = virtualMemUsed;
#endif // WIN32
#ifdef LINUX
    struct sysinfo memInfo;

    sysinfo (&memInfo);    
    long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
    //Add other values in next statement to avoid int overflow on right hand side...
    virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
    virtualMemUsed *= memInfo.mem_unit;
    _ui64VirtualMemoryCurrentlyUsed = virtualMemUsed;
#endif // LINUX
	return _ui64VirtualMemoryCurrentlyUsed;
}
// -------------------------------------------------------------
uint64_t Memory::Ram::getVirtualMemoryCurrentyUsedByProcess() {
	
	uint64_t _ui64VirtualMemoryCurrentlyUsedByProcess = 0;
#ifdef WIN32
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
	_ui64VirtualMemoryCurrentlyUsedByProcess = virtualMemUsedByMe;
#endif // WIN32
#ifdef LINUX
	FILE* file = fopen("/proc/self/status", "r");
	int result = -1;
	char line[128];
    
	while (fgets(line, 128, file) != NULL){
		if (strncmp(line, "VmSize:", 7) == 0){
			result = parseLine(line);
			break;
		}
	}
	fclose(file);
        _ui64VirtualMemoryCurrentlyUsedByProcess = result;
#endif // LINUX
	return _ui64VirtualMemoryCurrentlyUsedByProcess;
}
// -------------------------------------------------------------
uint64_t Memory::Ram::getTotalPhysicsMemory() {    
    
    uint64_t _ui64TotlaPhysicsMemory = 0;
#ifdef WIN32
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);    
    DWORDLONG totalPhysMem = memInfo.ullTotalPhys;    
    _ui64TotlaPhysicsMemory = totalPhysMem;
#endif // WIN32

#ifdef LINUX
    struct sysinfo memInfo;

    sysinfo (&memInfo);    
    long long totalPhysMem = memInfo.totalram;
    //Multiply in next statement to avoid int overflow on right hand side...
    totalPhysMem *= memInfo.mem_unit;
    _ui64TotlaPhysicsMemory = totalPhysMem;
#endif // LINUX    
    return _ui64TotlaPhysicsMemory;
}
// -------------------------------------------------------------
uint64_t Memory::Ram::getPhysicalMemoryCurrentlyUsed() {

	uint64_t _ui64PhysicalMemoryCurrently = 0;
#ifdef WIN32
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);    
	DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
	_ui64PhysicalMemoryCurrently = physMemUsed;
#endif // WIN32
#ifdef LINUX
    struct sysinfo memInfo;

    sysinfo (&memInfo);    
    long long totalPhysMem = memInfo.totalram;
    //Multiply in next statement to avoid int overflow on right hand side...
    totalPhysMem *= memInfo.mem_unit;
	_ui64PhysicalMemoryCurrently = totalPhysMem;
#endif // LINUX
	return _ui64PhysicalMemoryCurrently;
}
// -------------------------------------------------------------		
uint64_t Memory::Ram::getPhysicalMemoryCurrentlyUsedByProcess() {

	uint64_t _ui64PhysicalMemoryCurrentlyUsedByProcess = 0;
#ifdef WIN32
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
	_ui64PhysicalMemoryCurrentlyUsedByProcess = physMemUsedByMe;
#endif // WIN32

#ifdef LINUX
        FILE* file = fopen("/proc/self/status", "r");
        int result = -1;
        char line[128];

        while (fgets(line, 128, file) != NULL){
            if (strncmp(line, "VmRSS:", 6) == 0){
                result = parseLine(line);
                break;
            }
        }
        fclose(file);
        _ui64PhysicalMemoryCurrentlyUsedByProcess = result;
#endif // LINUX
	return _ui64PhysicalMemoryCurrentlyUsedByProcess;
}
// -------------------------------------------------------------		
