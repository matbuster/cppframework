
#include "CPU.h"

#ifdef WIN32
#include "TCHAR.h"
#include "pdh.h"
#include "windows.h"
#pragma comment(lib,"Pdh.lib")
#endif // WIN32

#ifdef LINUX
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/times.h"
#include "sys/vtimes.h"
#endif // LINUX

// ------------------------------------------------------
void WindowsCleanupPdhQuery(HLOG _hLog,  HQUERY _hQuery) {
    
	// Close the log file.
    if (_hLog)
        PdhCloseLog (_hLog, 0);

    // Close the query object.
    if (_hQuery)
        PdhCloseQuery (_hQuery);
}

// ------------------------------------------------------

double Tools::Hardware::getCPUCurrentlyUsed() {

    double _dCPUvalue = 0.0;

#ifdef WIN32
	HLOG hLog;
    PDH_HQUERY cpuQuery;
    PDH_HCOUNTER cpuTotal;
	PDH_STATUS pdhStatus;
    PDH_FMT_COUNTERVALUE counterVal;

    pdhStatus = PdhOpenQuery(NULL, NULL, &cpuQuery);
	if (pdhStatus != ERROR_SUCCESS)
	{
		WindowsCleanupPdhQuery(hLog, cpuQuery);
		return _dCPUvalue;
	}
    pdhStatus = PdhAddCounter(cpuQuery, L"\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal);
    if (pdhStatus != ERROR_SUCCESS)
    {
		WindowsCleanupPdhQuery(hLog, cpuQuery);
		return _dCPUvalue;
	}
    PdhCollectQueryData(cpuQuery);

    PdhCollectQueryData(cpuQuery);
    PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
    _dCPUvalue = counterVal.doubleValue;

#endif // WIN32

#ifdef LINUX
//    FILE* file = fopen("/proc/stat", "r");
//    fscanf(file, "cpu %llu %llu %llu %llu", &lastTotalUser, &lastTotalUserLow, &lastTotalSys, &lastTotalIdle);
//    fclose(file);

    double percent;
    FILE* file;
    unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;
    unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;
    
    // scan first data
    file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %llu %llu %llu %llu", &lastTotalUser, &lastTotalUserLow,
        &lastTotalSys, &lastTotalIdle);
    fclose(file);
    
    // scan another data
    file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow,
            &totalSys, &totalIdle);
    fclose(file);


    if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
            totalSys < lastTotalSys || totalIdle < lastTotalIdle) {
        //Overflow detection. Just skip this value.
        percent = -1.0;
    } else {
        total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
                (totalSys - lastTotalSys);
        percent = total;
        total += (totalIdle - lastTotalIdle);
        percent /= total;
        percent *= 100;
    }

    lastTotalUser = totalUser;
    lastTotalUserLow = totalUserLow;
    lastTotalSys = totalSys;
    lastTotalIdle = totalIdle;

    _dCPUvalue = percent;

#endif // LINUX
    return _dCPUvalue;
}
// ------------------------------------------------------

double Tools::Hardware::getCPUCurrentluUsedByProcess() {

    double _dCPUValueUsedByCurrentProcess = 0.0;
#ifdef WIN32
    ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
    int numProcessors;
    HANDLE self;

    SYSTEM_INFO sysInfo;
    FILETIME ftime, fsys, fuser;

    GetSystemInfo(&sysInfo);
    numProcessors = sysInfo.dwNumberOfProcessors;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&lastCPU, &ftime, sizeof (FILETIME));

    self = GetCurrentProcess();
    GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
    memcpy(&lastSysCPU, &fsys, sizeof (FILETIME));
    memcpy(&lastUserCPU, &fuser, sizeof (FILETIME));

    ULARGE_INTEGER now, sys, user;
    double percent;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&now, &ftime, sizeof (FILETIME));

    GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
    memcpy(&sys, &fsys, sizeof (FILETIME));
    memcpy(&user, &fuser, sizeof (FILETIME));
    percent = (sys.QuadPart - lastSysCPU.QuadPart) +
            (user.QuadPart - lastUserCPU.QuadPart);
    percent /= (now.QuadPart - lastCPU.QuadPart);
    percent /= numProcessors;
    lastCPU = now;
    lastUserCPU = user;
    lastSysCPU = sys;

    _dCPUValueUsedByCurrentProcess = percent * 100;

#endif // WIN32

#ifdef LINUX
    
    clock_t lastCPU, lastSysCPU, lastUserCPU;
    int numProcessors;    
    FILE* file;
    struct tms timeSample;
    char line[128];
    clock_t now;
    double percent;

    lastCPU = times(&timeSample);
    lastSysCPU = timeSample.tms_stime;
    lastUserCPU = timeSample.tms_utime;


    file = fopen("/proc/cpuinfo", "r");
    numProcessors = 0;
    while(fgets(line, 128, file) != NULL){
        if (strncmp(line, "processor", 9) == 0) numProcessors++;
    }
    fclose(file);
    
    now = times(&timeSample);
    if (now <= lastCPU || timeSample.tms_stime < lastSysCPU ||
        timeSample.tms_utime < lastUserCPU){
        //Overflow detection. Just skip this value.
        percent = -1.0;
    }
    else{
        percent = (timeSample.tms_stime - lastSysCPU) +
            (timeSample.tms_utime - lastUserCPU);
        percent /= (now - lastCPU);
        percent /= numProcessors;
        percent *= 100;
    }
    lastCPU = now;
    lastSysCPU = timeSample.tms_stime;    
#endif // LINUX
    return _dCPUValueUsedByCurrentProcess;
}
// ------------------------------------------------------
int Tools::Hardware::getNumberProcessor() {
	int iNumProcessor = 0;
#ifdef WIN32
    SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
    iNumProcessor = sysInfo.dwNumberOfProcessors;
#endif // WIN32

#ifdef LINUX
    int numProcessors;    
    FILE* file;

    file = fopen("/proc/cpuinfo", "r");
    numProcessors = 0;
    while(fgets(line, 128, file) != NULL){
        if (strncmp(line, "processor", 9) == 0) numProcessors++;
    }
    fclose(file);
#endif // LINUX

	return iNumProcessor;
}
