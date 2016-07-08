/**
 * \file 		cryptoDefine.h
 * \date 		20/05/2016
 * \author 		NSJ
 */ 

#ifndef CRYPTO_DEFINE_H
#define CRYPTO_DEFINE_H


typedef struct {
    ULONG total[2];
    ULONG state[5];
    UCHAR buffer[64];
} hash_context;

#endif //CRYPTO_DEFINE_H
