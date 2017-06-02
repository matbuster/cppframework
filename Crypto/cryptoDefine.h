/**
 * \file 		cryptoDefine.h
 * \date 		20/05/2016
 * \author 		NSJ
 */ 

#ifndef CRYPTO_DEFINE_H
#define CRYPTO_DEFINE_H

#define RESULT_GOOD     0
#define RESULT_ERR      1

typedef unsigned short  bufferID_t;
typedef unsigned short  requestID_t;

typedef struct {
    unsigned long count;
    requestID_t request_id;
    bufferID_t buffer_id;
} externalBuffer_t;

typedef struct {
    unsigned long count;
    void *buffer;
} internalBuffer_t;

typedef struct {
    unsigned long total[2];
    unsigned long state[5];
    unsigned char buffer[64];
} hash_context;

#endif //CRYPTO_DEFINE_H
