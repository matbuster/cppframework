/**
 * \file 		des.h
 * \date 		04/11/2015 
 * \author 		NSJ
 */ 

#ifndef DES_H
#define DES_H

#include "cryptoDefine.h"

typedef unsigned char DES_key_t[8];
typedef unsigned char DES_vector_t[8];

typedef union {
    externalBuffer_t exter;
    internalBuffer_t inter;
} DESBuffer_t;

typedef struct {
    DES_key_t key;
    DES_vector_t init_v;
    DES_vector_t term_v;
    DESBuffer_t source;
    DESBuffer_t destination;
    unsigned char prePadding[8];
    unsigned char postPadding[16];
    unsigned long options;
} DES_RB_t;

typedef struct {
    DES_key_t key1;
    DES_key_t key2;
    DES_key_t key3;
    DES_vector_t init_v;
    DES_vector_t term_v;
    DESBuffer_t source;
    DESBuffer_t destination;
    unsigned char prePadding[8];
    unsigned char postPadding[16];
    unsigned long options;
} TDES_RB_t;

typedef struct {
    DES_key_t key;
    unsigned char input_data[8];
    unsigned char output_data[8];
    unsigned long options;
} DES8bytes_RB_t;

typedef struct {
    DES_key_t key_in;
    DES_key_t key1;
    DES_key_t key2;
    DES_key_t key3;
    DES_key_t key_out;
    unsigned long options;
} DES3Key_RB_t;

#define  DES_ENCRYPT            0x00001000
#define  DES_DECRYPT            0x00002000

#define  DES_CBC_MODE           0x00004000
#define  DES_ECB_MODE           0x00008000

#define  DES_TRANSFORM_KEY      0x00010000
#define  DES_USE_KEY            0x00020000
#define  DES_TRIPLE_DES         0x00040000

#define  DES_INTERNAL_INPUT     0x00000001
#define  DES_EXTERNAL_INPUT     0x00000002
#define  DES_CRYPTO_BYPASS      0x00000004

#define  DES_INTERNAL_OUTPUT    0x00000010
#define  DES_EXTERNAL_OUTPUT    0x00000020
#define  DES_MAC                0x00000040

#define  DES3_1_ENCRYPT         0x00000001
#define  DES3_1_DECRYPT         0x00000002
#define  DES3_2_ENCRYPT         0x00000010
#define  DES3_2_DECRYPT         0x00000020
#define  DES3_3_ENCRYPT         0x00000100
#define  DES3_3_DECRYPT         0x00000200

long single_des_ecb_encrypt
(
        unsigned char *key,
        unsigned char *pcleartxt,
        unsigned long *length,
        unsigned char *pciphrtxt
        );

long single_des_ecb_decrypt
(
        unsigned char *key,
        unsigned char *pciphrtxt,
        unsigned long *length,
        unsigned char *pcleartxt
        );

long single_des_cbc_encrypt
(
        unsigned char *key,
        unsigned char *pcleartxt,
        unsigned long *length,
        unsigned char *pciphrtxt
        );

long single_des_cbc_decrypt
(
        unsigned char *key,
        unsigned char *pciphrtxt,
        unsigned long *length,
        unsigned char *pcleartxt
        );

long triple_des_ecb_encrypt
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pcleartxt,
        unsigned long *length,
        unsigned char *pciphrtxt
        );

long triple_des_ecb_decrypt
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pciphrtxt,
        unsigned long *length,
        unsigned char *pcleartxt
        );

long triple_des_cbc_encrypt
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pcleartxt,
        unsigned long *length,
        unsigned char *pciphrtxt
        );

long triple_des_cbc_decrypt
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pciphrtxt,
        unsigned long *length,
        unsigned char *pcleartxt
        );

long single_des8_encrypt
(
        unsigned char *key,
        unsigned char *pcleartxt,
        unsigned char *pciphrtxt
        );

long single_des8_decrypt
(
        unsigned char *key,
        unsigned char *pcleartxt,
        unsigned char *pciphrtxt
        );

long triple_des8_encrypt
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pcleartxt,
        unsigned char *pciphrtxt
        );

long triple_des8_decrypt
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pcleartxt,
        unsigned char *pciphrtxt
        );

long triple_des8_decrypt_dmode
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pcleartxt,
        unsigned char *pciphrtxt
        );

long triple_des8_encrypt_dmode
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pciphrtxt,
        unsigned char *pcleartxt
        );

long triple_des_cbc_encrypt_dmode
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pcleartxt,
        unsigned long *length,
        unsigned char *pciphrtxt
        );

long triple_des_cbc_decrypt_dmode
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pciphrtxt,
        unsigned long *length,
        unsigned char *pcleartxt
        );

#endif //DES_H
