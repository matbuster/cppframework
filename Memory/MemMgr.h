/**
 * \file 		MemMgr.h
 * \date 		04/11/2015 
 * \author 		MAT
 */ 

#ifndef _MEMMGR_H_
#define _MEMMGR_H_
#pragma once

//#define DEBUG_MEM_MGR_INFO

#include "../toolsConstant.h"

#ifdef __linux__
#ifndef DWORD
#define DWORD unsigned long
#endif
#define SHORT_STR 32
#define LONG_STR 2048
#else //__linux__
#include <Windows.h>
#endif //__linux__

typedef struct
{
	DWORD size;
	void* ptr;
	char* ptr_orig;
	char name[STR_LONG];
} TypMemDescr;

void* memAlloc(long size,const char* name);
void* memAllocZ(long size,const char* name);
void* memRealloc(void* ptr, long size, const char* name );
void memFree(void* ptr);
void memCheck();
void memCheckIntegrity();

double memUsedMemory();
void memTotalUsedMemory(int *szMem1, int *comp1 );

#else
#error "MemMgr.h deja inclus"
#endif
