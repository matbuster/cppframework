/**
 * \file 		ErrorCode.cpp
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

// Include des en-tetes standard c
#include <stddef.h>
#include <stdio.h>

// Include des en-tetes du framework
#include "ErrorCode.h"

long getReturnCode(long lCode) {
    return lCode >> 16;
}

long getReasonCode(long lCode) {
    return lCode & 0x0000FFFF;
}

long getErrorCode(long lReturncode, long lReasoncode) {
    return ((lReturncode & 0x0000FFFF) << 16) | (lReasoncode & 0x0000FFFF);
}
