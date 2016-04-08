/**
 * \file 		sha1.h
 * \date 		04/11/2015 
 * \author 		NSJ
 */ 
 
#ifndef SHA1_H
#define SHA1_H

#include "ibm.h"

typedef struct {
    sccInternalBuffer_t source;
    unsigned long options;
    sccSHA1_hash_t hash_value;
    hash_context ctx;
} __sccSHA_RB_t;

#ifdef NT2000
__declspec(dllexport)
#endif
long scc_SHA1
(
        unsigned long Data_Lg,
        unsigned char *Data,
        unsigned char *Rule_Array,
        unsigned char *SHA1,
        unsigned char *Context
        );


#endif //SHA1_H
