/**
 * \file 		des.h
 * \date 		04/11/2015 
 * \author 		NSJ
 */ 

#ifndef DES_H
#define DES_H

#include "cryptoDefine.h"

long __sccDES3Key
(
        sccDES3Key_RB_t *TDES8_rb
        );

long scc_single_des_ecb_encrypt
(
        unsigned char *key,
        unsigned char *pcleartxt,
        unsigned long *length,
        unsigned char *pciphrtxt
        );

long scc_single_des_ecb_decrypt
(
        unsigned char *key,
        unsigned char *pciphrtxt,
        unsigned long *length,
        unsigned char *pcleartxt
        );

long scc_single_des_cbc_encrypt
(
        unsigned char *key,
        unsigned char *pcleartxt,
        unsigned long *length,
        unsigned char *pciphrtxt
        );

long scc_single_des_cbc_decrypt
(
        unsigned char *key,
        unsigned char *pciphrtxt,
        unsigned long *length,
        unsigned char *pcleartxt
        );

long scc_triple_des_ecb_encrypt_m2
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pcleartxt,
        unsigned long *length,
        unsigned char *pciphrtxt
        );

long scc_triple_des_ecb_decrypt_m2
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pciphrtxt,
        unsigned long *length,
        unsigned char *pcleartxt
        );

long scc_triple_des_cbc_encrypt
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pcleartxt,
        unsigned long *length,
        unsigned char *pciphrtxt
        );

long scc_triple_des_cbc_decrypt
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pciphrtxt,
        unsigned long *length,
        unsigned char *pcleartxt
        );

long scc_single_des8_encrypt
(
        unsigned char *key,
        unsigned char *pcleartxt,
        unsigned char *pciphrtxt
        );

long scc_single_des8_decrypt
(
        unsigned char *key,
        unsigned char *pcleartxt,
        unsigned char *pciphrtxt
        );

long scc_triple_des8_encrypt
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pcleartxt,
        unsigned char *pciphrtxt
        );

long scc_triple_des8_decrypt
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pcleartxt,
        unsigned char *pciphrtxt
        );

long scc_triple_des8_decrypt_dmode
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pcleartxt,
        unsigned char *pciphrtxt
        );

long scc_triple_des8_encrypt_dmode
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pciphrtxt,
        unsigned char *pcleartxt
        );

long scc_triple_des_cbc_encrypt_dmode
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pcleartxt,
        unsigned long *length,
        unsigned char *pciphrtxt
        );

long scc_triple_des_cbc_decrypt_dmode
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pciphrtxt,
        unsigned long *length,
        unsigned char *pcleartxt
        );

#endif //DES_H
