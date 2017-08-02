
#include "testTimingChrono.h"
#include "cppFrameworkTesterDefines.h"
#include "TesterReport.h"

// framework include timing
#include "Timing/Chrono.h"
#include "Timing/Timing.h"
#include "Timing/Date.h"

// framework include assertion
#include "Diagnostic/assertion.h"

#include <stdio.h>

#define CONST_ACCURACY_TIMING_MS		2
#define TEST_ELLAPSED_VALUE_1_MS		10		
#define TEST_ELLAPSED_VALUE_2_MS		100		
#define TEST_ELLAPSED_VALUE_3_MS		200		
#define TEST_ELLAPSED_VALUE_4_MS		500		
#define TEST_ELLAPSED_VALUE_5_MS		1000

// ----------------------------------------------------------
int Test::tester_timing_datetime()
{
	Timing::Date::DateTime * date = Timing::Date::DateTime::Now();
	delete date;

    return TEST_OK;
}
// ----------------------------------------------------------

int Test::tester_timing_duration() {

    long _lAbsoluteStartTime_ms = Timing::Chrono::getAbsoluteTime_ms();
    long _lAbsoluteEndTime_ms = 0;
    Timing::Timing::sleepInMilliSecond(TEST_ELLAPSED_VALUE_1_MS);
    _lAbsoluteEndTime_ms = Timing::Chrono::getAbsoluteTime_ms();

    long _lEllapsedTime_ms = (_lAbsoluteEndTime_ms - _lAbsoluteStartTime_ms);
    printf("[DEBUG]\t[tester_timing_duration]\tEllapsed time %lu ms\n", _lEllapsedTime_ms);
    if (_lEllapsedTime_ms < (TEST_ELLAPSED_VALUE_1_MS - CONST_ACCURACY_TIMING_MS) || _lEllapsedTime_ms > (TEST_ELLAPSED_VALUE_1_MS + CONST_ACCURACY_TIMING_MS)) {
        Diagnostic::Assert(false, "Precision on measure timing is not enough efficient for TEST_ELLAPSED_VALUE_1_MS.");
        return TEST_KO;
    }

    _lAbsoluteStartTime_ms = Timing::Chrono::getAbsoluteTime_ms();
    Timing::Timing::sleepInMilliSecond(TEST_ELLAPSED_VALUE_2_MS);
    _lAbsoluteEndTime_ms = Timing::Chrono::getAbsoluteTime_ms();
    _lEllapsedTime_ms = (_lAbsoluteEndTime_ms - _lAbsoluteStartTime_ms);
    printf("[DEBUG]\t[tester_timing_duration]\tEllapsed time %lu ms\n", _lEllapsedTime_ms);
    if (_lEllapsedTime_ms < (TEST_ELLAPSED_VALUE_2_MS - CONST_ACCURACY_TIMING_MS) || _lEllapsedTime_ms > (TEST_ELLAPSED_VALUE_2_MS + CONST_ACCURACY_TIMING_MS)) {
        Diagnostic::Assert(false, "Precision on measure timing is not enough efficient for TEST_ELLAPSED_VALUE_2_MS.");
        return TEST_KO;
    }

    _lAbsoluteStartTime_ms = Timing::Chrono::getAbsoluteTime_ms();
    Timing::Timing::sleepInMilliSecond(TEST_ELLAPSED_VALUE_3_MS);
    _lAbsoluteEndTime_ms = Timing::Chrono::getAbsoluteTime_ms();
    _lEllapsedTime_ms = (_lAbsoluteEndTime_ms - _lAbsoluteStartTime_ms);
    printf("[DEBUG]\t[tester_timing_duration]\tEllapsed time %lu ms\n", _lEllapsedTime_ms);
    if (_lEllapsedTime_ms < (TEST_ELLAPSED_VALUE_3_MS - CONST_ACCURACY_TIMING_MS) || _lEllapsedTime_ms > (TEST_ELLAPSED_VALUE_3_MS + CONST_ACCURACY_TIMING_MS)) {
        Diagnostic::Assert(false, "Precision on measure timing is not enough efficient for TEST_ELLAPSED_VALUE_3_MS.");
        return TEST_KO;
    }

    _lAbsoluteStartTime_ms = Timing::Chrono::getAbsoluteTime_ms();
    Timing::Timing::sleepInMilliSecond(TEST_ELLAPSED_VALUE_4_MS);
    _lAbsoluteEndTime_ms = Timing::Chrono::getAbsoluteTime_ms();
    _lEllapsedTime_ms = (_lAbsoluteEndTime_ms - _lAbsoluteStartTime_ms);
    printf("[DEBUG]\t[tester_timing_duration]\tEllapsed time %lu ms\n", _lEllapsedTime_ms);
    if (_lEllapsedTime_ms < (TEST_ELLAPSED_VALUE_4_MS - CONST_ACCURACY_TIMING_MS) || _lEllapsedTime_ms > (TEST_ELLAPSED_VALUE_4_MS + CONST_ACCURACY_TIMING_MS)) {
        Diagnostic::Assert(false, "Precision on measure timing is not enough efficient for TEST_ELLAPSED_VALUE_4_MS.");
        return TEST_KO;
    }

    _lAbsoluteStartTime_ms = Timing::Chrono::getAbsoluteTime_ms();
    Timing::Timing::sleepInMilliSecond(TEST_ELLAPSED_VALUE_5_MS);
    _lAbsoluteEndTime_ms = Timing::Chrono::getAbsoluteTime_ms();
    _lEllapsedTime_ms = (_lAbsoluteEndTime_ms - _lAbsoluteStartTime_ms);
    printf("[DEBUG]\t[tester_timing_duration]\tEllapsed time %lu ms\n", _lEllapsedTime_ms);
    if (_lEllapsedTime_ms < (TEST_ELLAPSED_VALUE_5_MS - CONST_ACCURACY_TIMING_MS) || _lEllapsedTime_ms > (TEST_ELLAPSED_VALUE_5_MS + CONST_ACCURACY_TIMING_MS)) {
        Diagnostic::Assert(false, "Precision on measure timing is not enough efficient for TEST_ELLAPSED_VALUE_5_MS.");
        return TEST_KO;
    }

    return TEST_OK;
}
// ----------------------------------------------------------

int Test::tester_timing_Chrono() {

    Timing::Chrono * chrono = new Timing::Chrono();
    chrono->startChrono();
    Timing::Timing::sleepInMilliSecond(TEST_ELLAPSED_VALUE_1_MS);
    double _dTimeEllapsed = chrono->getTime_ms();
    double _dAdditionnalTime = TEST_ELLAPSED_VALUE_1_MS;
    double _dPrecision = CONST_ACCURACY_TIMING_MS;

    printf("[DEBUG]\t[tester_timing_Chrono]\tEllapsed time %0.2f ms\n", _dTimeEllapsed);
    if(_dTimeEllapsed < (double)(_dAdditionnalTime - _dPrecision) || _dTimeEllapsed > (double)(_dAdditionnalTime + _dPrecision)) {
        Diagnostic::Assert(false, "Precision on measure timing for Chrono is not enough efficient for TEST_ELLAPSED_VALUE_1_MS.");
        return TEST_KO;        
    }
    
    Timing::Timing::sleepInMilliSecond(TEST_ELLAPSED_VALUE_2_MS);
    _dAdditionnalTime += TEST_ELLAPSED_VALUE_2_MS;
    _dPrecision += CONST_ACCURACY_TIMING_MS;
    _dTimeEllapsed = chrono->getTime_ms();
    printf("[DEBUG]\t[tester_timing_Chrono]\tEllapsed time %0.2f ms\n", _dTimeEllapsed);
    if(_dTimeEllapsed < (double)(_dAdditionnalTime - _dPrecision) || _dTimeEllapsed > (double)(_dAdditionnalTime + _dPrecision)) {
        Diagnostic::Assert(false, "Precision on measure timing for Chrono is not enough efficient for TEST_ELLAPSED_VALUE_2_MS.");
        return TEST_KO;        
    }    
    
    Timing::Timing::sleepInMilliSecond(TEST_ELLAPSED_VALUE_3_MS);
    _dAdditionnalTime += TEST_ELLAPSED_VALUE_3_MS;
    _dPrecision += CONST_ACCURACY_TIMING_MS;
    _dTimeEllapsed = chrono->getTime_ms();
    printf("[DEBUG]\t[tester_timing_Chrono]\tEllapsed time %0.2f ms\n", _dTimeEllapsed);
    if(_dTimeEllapsed < (double)(_dAdditionnalTime - _dPrecision) || _dTimeEllapsed > (double)(_dAdditionnalTime + _dPrecision)) {
        Diagnostic::Assert(false, "Precision on measure timing for Chrono is not enough efficient for TEST_ELLAPSED_VALUE_3_MS.");
        return TEST_KO;        
    }    
    
    Timing::Timing::sleepInMilliSecond(TEST_ELLAPSED_VALUE_4_MS);
    _dAdditionnalTime += TEST_ELLAPSED_VALUE_4_MS;
    _dPrecision += CONST_ACCURACY_TIMING_MS;
    _dTimeEllapsed = chrono->getTime_ms();
    printf("[DEBUG]\t[tester_timing_Chrono]\tEllapsed time %0.2f ms\n", _dTimeEllapsed);
    if(_dTimeEllapsed < (double)(_dAdditionnalTime - _dPrecision) || _dTimeEllapsed > (double)(_dAdditionnalTime + _dPrecision)) {
        Diagnostic::Assert(false, "Precision on measure timing for Chrono is not enough efficient for TEST_ELLAPSED_VALUE_4_MS.");
        return TEST_KO;        
    }
    
    Timing::Timing::sleepInMilliSecond(TEST_ELLAPSED_VALUE_5_MS);
    _dAdditionnalTime += TEST_ELLAPSED_VALUE_5_MS;
    _dPrecision += CONST_ACCURACY_TIMING_MS;
    _dTimeEllapsed = chrono->getTime_ms();
    printf("[DEBUG]\t[tester_timing_Chrono]\tEllapsed time %0.2f ms\n", _dTimeEllapsed);
    if(_dTimeEllapsed < (double)(_dAdditionnalTime - _dPrecision) || _dTimeEllapsed > (double)(_dAdditionnalTime + _dPrecision)) {
        Diagnostic::Assert(false, "Precision on measure timing for Chrono is not enough efficient for TEST_ELLAPSED_VALUE_2_MS.");
        return TEST_KO;        
    }     

    delete chrono;
    return TEST_OK;
}
// ----------------------------------------------------------

int Test::tester_timing_chrono() {

    int iReturnCode = TEST_OK;
    Test::TesterReport::getInstance()->printHeader("testing Timing::Chrono");

	iReturnCode = tester_timing_datetime();
	Test::TesterReport::getInstance()->printSummary((iReturnCode == TEST_OK), "Timing", "tester_timing_datetime()");
	if (TEST_OK != iReturnCode) {
        return TEST_KO;
    }

	iReturnCode = tester_timing_duration();
	Test::TesterReport::getInstance()->printSummary((iReturnCode == TEST_OK), "Timing", "tester_timing_duration()");
    if (TEST_OK != iReturnCode) {
        return TEST_KO;
    }

	iReturnCode = tester_timing_Chrono();
	Test::TesterReport::getInstance()->printSummary((iReturnCode == TEST_OK), "Timing", "tester_timing_Chrono()");
    if (TEST_OK != iReturnCode) {
        return TEST_KO;
    }

    return iReturnCode;
}
// ----------------------------------------------------------
