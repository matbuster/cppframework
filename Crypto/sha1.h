/**
 * \file 		sha1.h
 * \date 		04/11/2015 
 * \author 		NSJ
 */ 
 
#ifndef SHA1_H
#define SHA1_H

#include "cryptoDefine.h"

typedef unsigned char SHA1_hash_t[20];

#define  SHA_MSGPART_ONLY       0x01000000
#define  SHA_MSGPART_FIRST      0x02000000
#define  SHA_MSGPART_MIDDLE     0x04000000
#define  SHA_MSGPART_FINAL      0x08000000

typedef struct {
    internalBuffer_t source;
    unsigned long options;
    SHA1_hash_t hash_value;
    hash_context ctx;
} SHA_RB_t;

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
