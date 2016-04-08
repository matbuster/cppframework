/**
 * \file 		ErrorCode.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#ifndef ERROR_CODE_H
#define ERROR_CODE_H

long getReturnCode(long lCode);

long getReasonCode(long lCode);

long getErrorCode(long lReturncode, long lReasoncode);

#endif //ERROR_CODE_H