/**
 * \file 		des.cpp
 * \date 		04/11/2015 
 * \author 		NSJ
 */ 

// Include des en-tetes standard c
#include <string.h>

// Include des en-tetes du framework
#include "des.h"
#include "xor.h"

// the eight DES S-boxes

static const unsigned long SB1[64] = {
    0x01010400, 0x00000000, 0x00010000, 0x01010404,
    0x01010004, 0x00010404, 0x00000004, 0x00010000,
    0x00000400, 0x01010400, 0x01010404, 0x00000400,
    0x01000404, 0x01010004, 0x01000000, 0x00000004,
    0x00000404, 0x01000400, 0x01000400, 0x00010400,
    0x00010400, 0x01010000, 0x01010000, 0x01000404,
    0x00010004, 0x01000004, 0x01000004, 0x00010004,
    0x00000000, 0x00000404, 0x00010404, 0x01000000,
    0x00010000, 0x01010404, 0x00000004, 0x01010000,
    0x01010400, 0x01000000, 0x01000000, 0x00000400,
    0x01010004, 0x00010000, 0x00010400, 0x01000004,
    0x00000400, 0x00000004, 0x01000404, 0x00010404,
    0x01010404, 0x00010004, 0x01010000, 0x01000404,
    0x01000004, 0x00000404, 0x00010404, 0x01010400,
    0x00000404, 0x01000400, 0x01000400, 0x00000000,
    0x00010004, 0x00010400, 0x00000000, 0x01010004
};

static const unsigned long SB2[64] = {
    0x80108020, 0x80008000, 0x00008000, 0x00108020,
    0x00100000, 0x00000020, 0x80100020, 0x80008020,
    0x80000020, 0x80108020, 0x80108000, 0x80000000,
    0x80008000, 0x00100000, 0x00000020, 0x80100020,
    0x00108000, 0x00100020, 0x80008020, 0x00000000,
    0x80000000, 0x00008000, 0x00108020, 0x80100000,
    0x00100020, 0x80000020, 0x00000000, 0x00108000,
    0x00008020, 0x80108000, 0x80100000, 0x00008020,
    0x00000000, 0x00108020, 0x80100020, 0x00100000,
    0x80008020, 0x80100000, 0x80108000, 0x00008000,
    0x80100000, 0x80008000, 0x00000020, 0x80108020,
    0x00108020, 0x00000020, 0x00008000, 0x80000000,
    0x00008020, 0x80108000, 0x00100000, 0x80000020,
    0x00100020, 0x80008020, 0x80000020, 0x00100020,
    0x00108000, 0x00000000, 0x80008000, 0x00008020,
    0x80000000, 0x80100020, 0x80108020, 0x00108000
};

static const unsigned long SB3[64] = {
    0x00000208, 0x08020200, 0x00000000, 0x08020008,
    0x08000200, 0x00000000, 0x00020208, 0x08000200,
    0x00020008, 0x08000008, 0x08000008, 0x00020000,
    0x08020208, 0x00020008, 0x08020000, 0x00000208,
    0x08000000, 0x00000008, 0x08020200, 0x00000200,
    0x00020200, 0x08020000, 0x08020008, 0x00020208,
    0x08000208, 0x00020200, 0x00020000, 0x08000208,
    0x00000008, 0x08020208, 0x00000200, 0x08000000,
    0x08020200, 0x08000000, 0x00020008, 0x00000208,
    0x00020000, 0x08020200, 0x08000200, 0x00000000,
    0x00000200, 0x00020008, 0x08020208, 0x08000200,
    0x08000008, 0x00000200, 0x00000000, 0x08020008,
    0x08000208, 0x00020000, 0x08000000, 0x08020208,
    0x00000008, 0x00020208, 0x00020200, 0x08000008,
    0x08020000, 0x08000208, 0x00000208, 0x08020000,
    0x00020208, 0x00000008, 0x08020008, 0x00020200
};

static const unsigned long SB4[64] = {
    0x00802001, 0x00002081, 0x00002081, 0x00000080,
    0x00802080, 0x00800081, 0x00800001, 0x00002001,
    0x00000000, 0x00802000, 0x00802000, 0x00802081,
    0x00000081, 0x00000000, 0x00800080, 0x00800001,
    0x00000001, 0x00002000, 0x00800000, 0x00802001,
    0x00000080, 0x00800000, 0x00002001, 0x00002080,
    0x00800081, 0x00000001, 0x00002080, 0x00800080,
    0x00002000, 0x00802080, 0x00802081, 0x00000081,
    0x00800080, 0x00800001, 0x00802000, 0x00802081,
    0x00000081, 0x00000000, 0x00000000, 0x00802000,
    0x00002080, 0x00800080, 0x00800081, 0x00000001,
    0x00802001, 0x00002081, 0x00002081, 0x00000080,
    0x00802081, 0x00000081, 0x00000001, 0x00002000,
    0x00800001, 0x00002001, 0x00802080, 0x00800081,
    0x00002001, 0x00002080, 0x00800000, 0x00802001,
    0x00000080, 0x00800000, 0x00002000, 0x00802080
};

static const unsigned long SB5[64] = {
    0x00000100, 0x02080100, 0x02080000, 0x42000100,
    0x00080000, 0x00000100, 0x40000000, 0x02080000,
    0x40080100, 0x00080000, 0x02000100, 0x40080100,
    0x42000100, 0x42080000, 0x00080100, 0x40000000,
    0x02000000, 0x40080000, 0x40080000, 0x00000000,
    0x40000100, 0x42080100, 0x42080100, 0x02000100,
    0x42080000, 0x40000100, 0x00000000, 0x42000000,
    0x02080100, 0x02000000, 0x42000000, 0x00080100,
    0x00080000, 0x42000100, 0x00000100, 0x02000000,
    0x40000000, 0x02080000, 0x42000100, 0x40080100,
    0x02000100, 0x40000000, 0x42080000, 0x02080100,
    0x40080100, 0x00000100, 0x02000000, 0x42080000,
    0x42080100, 0x00080100, 0x42000000, 0x42080100,
    0x02080000, 0x00000000, 0x40080000, 0x42000000,
    0x00080100, 0x02000100, 0x40000100, 0x00080000,
    0x00000000, 0x40080000, 0x02080100, 0x40000100
};

static const unsigned long SB6[64] = {
    0x20000010, 0x20400000, 0x00004000, 0x20404010,
    0x20400000, 0x00000010, 0x20404010, 0x00400000,
    0x20004000, 0x00404010, 0x00400000, 0x20000010,
    0x00400010, 0x20004000, 0x20000000, 0x00004010,
    0x00000000, 0x00400010, 0x20004010, 0x00004000,
    0x00404000, 0x20004010, 0x00000010, 0x20400010,
    0x20400010, 0x00000000, 0x00404010, 0x20404000,
    0x00004010, 0x00404000, 0x20404000, 0x20000000,
    0x20004000, 0x00000010, 0x20400010, 0x00404000,
    0x20404010, 0x00400000, 0x00004010, 0x20000010,
    0x00400000, 0x20004000, 0x20000000, 0x00004010,
    0x20000010, 0x20404010, 0x00404000, 0x20400000,
    0x00404010, 0x20404000, 0x00000000, 0x20400010,
    0x00000010, 0x00004000, 0x20400000, 0x00404010,
    0x00004000, 0x00400010, 0x20004010, 0x00000000,
    0x20404000, 0x20000000, 0x00400010, 0x20004010
};

static const unsigned long SB7[64] = {
    0x00200000, 0x04200002, 0x04000802, 0x00000000,
    0x00000800, 0x04000802, 0x00200802, 0x04200800,
    0x04200802, 0x00200000, 0x00000000, 0x04000002,
    0x00000002, 0x04000000, 0x04200002, 0x00000802,
    0x04000800, 0x00200802, 0x00200002, 0x04000800,
    0x04000002, 0x04200000, 0x04200800, 0x00200002,
    0x04200000, 0x00000800, 0x00000802, 0x04200802,
    0x00200800, 0x00000002, 0x04000000, 0x00200800,
    0x04000000, 0x00200800, 0x00200000, 0x04000802,
    0x04000802, 0x04200002, 0x04200002, 0x00000002,
    0x00200002, 0x04000000, 0x04000800, 0x00200000,
    0x04200800, 0x00000802, 0x00200802, 0x04200800,
    0x00000802, 0x04000002, 0x04200802, 0x04200000,
    0x00200800, 0x00000000, 0x00000002, 0x04200802,
    0x00000000, 0x00200802, 0x04200000, 0x00000800,
    0x04000002, 0x04000800, 0x00000800, 0x00200002
};

static const unsigned long SB8[64] = {
    0x10001040, 0x00001000, 0x00040000, 0x10041040,
    0x10000000, 0x10001040, 0x00000040, 0x10000000,
    0x00040040, 0x10040000, 0x10041040, 0x00041000,
    0x10041000, 0x00041040, 0x00001000, 0x00000040,
    0x10040000, 0x10000040, 0x10001000, 0x00001040,
    0x00041000, 0x00040040, 0x10040040, 0x10041000,
    0x00001040, 0x00000000, 0x00000000, 0x10040040,
    0x10000040, 0x10001000, 0x00041040, 0x00040000,
    0x00041040, 0x00040000, 0x10041000, 0x00001000,
    0x00000040, 0x10040040, 0x00001000, 0x00041040,
    0x10001000, 0x00000040, 0x10000040, 0x10040000,
    0x10040040, 0x10000000, 0x00040000, 0x10001040,
    0x00000000, 0x10041040, 0x00040040, 0x10000040,
    0x10040000, 0x10001000, 0x10001040, 0x00000000,
    0x10041040, 0x00041000, 0x00041000, 0x00001040,
    0x00001040, 0x00040040, 0x10000000, 0x10041000
};

// PC1: left and right halves bit-swap
static const unsigned long LHs[16] = {
    0x00000000, 0x00000001, 0x00000100, 0x00000101,
    0x00010000, 0x00010001, 0x00010100, 0x00010101,
    0x01000000, 0x01000001, 0x01000100, 0x01000101,
    0x01010000, 0x01010001, 0x01010100, 0x01010101
};

static const unsigned long RHs[16] = {
    0x00000000, 0x01000000, 0x00010000, 0x01010000,
    0x00000100, 0x01000100, 0x00010100, 0x01010100,
    0x00000001, 0x01000001, 0x00010001, 0x01010001,
    0x00000101, 0x01000101, 0x00010101, 0x01010101,
};

// platform-independant 32-bit integer manipulation macros

#define GET_ULONG(n,b,i)                       \
	{                                            \
		(n) = ( (unsigned long) (b)[(i)    ] << 24 )       \
				| ( (unsigned long) (b)[(i) + 1] << 16 )       \
				| ( (unsigned long) (b)[(i) + 2] <<  8 )       \
				| ( (unsigned long) (b)[(i) + 3]       );      \
	}

#define PUT_ULONG(n,b,i)                        \
	{                                             \
		(b)[(i)    ] = (unsigned char) ( (n) >> 24 );       \
		(b)[(i) + 1] = (unsigned char) ( (n) >> 16 );       \
		(b)[(i) + 2] = (unsigned char) ( (n) >>  8 );       \
		(b)[(i) + 3] = (unsigned char) ( (n)       );       \
	}

// Initial Permutation macro
#define DES_IP(X,Y)                                             \
	{                                                             \
		T = ((X >>  4) ^ Y) & 0x0F0F0F0F; Y ^= T; X ^= (T <<  4);   \
		T = ((X >> 16) ^ Y) & 0x0000FFFF; Y ^= T; X ^= (T << 16);   \
		T = ((Y >>  2) ^ X) & 0x33333333; X ^= T; Y ^= (T <<  2);   \
		T = ((Y >>  8) ^ X) & 0x00FF00FF; X ^= T; Y ^= (T <<  8);   \
		Y = ((Y << 1) | (Y >> 31)) & 0xFFFFFFFF;                    \
		T = (X ^ Y) & 0xAAAAAAAA; Y ^= T; X ^= T;                   \
		X = ((X << 1) | (X >> 31)) & 0xFFFFFFFF;                    \
	}

// Final Permutation macro
#define DES_FP(X,Y)                                             \
	{                                                             \
		X = ((X << 31) | (X >> 1)) & 0xFFFFFFFF;                    \
		T = (X ^ Y) & 0xAAAAAAAA; X ^= T; Y ^= T;                   \
		Y = ((Y << 31) | (Y >> 1)) & 0xFFFFFFFF;                    \
		T = ((Y >>  8) ^ X) & 0x00FF00FF; X ^= T; Y ^= (T <<  8);   \
		T = ((Y >>  2) ^ X) & 0x33333333; X ^= T; Y ^= (T <<  2);   \
		T = ((X >> 16) ^ Y) & 0x0000FFFF; Y ^= T; X ^= (T << 16);   \
		T = ((X >>  4) ^ Y) & 0x0F0F0F0F; Y ^= T; X ^= (T <<  4);   \
	}

// DES round macro
#define DES_ROUND(X,Y)                          \
	{                                             \
		T = *SK++ ^ X;                              \
		Y ^= SB8[ (T      ) & 0x3F ] ^              \
				 SB6[ (T >>  8) & 0x3F ] ^              \
				 SB4[ (T >> 16) & 0x3F ] ^              \
				 SB2[ (T >> 24) & 0x3F ];               \
																								\
		T = *SK++ ^ ((X << 28) | (X >> 4));         \
		Y ^= SB7[ (T      ) & 0x3F ] ^              \
				 SB5[ (T >>  8) & 0x3F ] ^              \
				 SB3[ (T >> 16) & 0x3F ] ^              \
				 SB1[ (T >> 24) & 0x3F ];               \
	}

// DES key

void des_main_ks(unsigned long SK[32], unsigned char key[8]) {
    unsigned long i;
    unsigned long X, Y, T;

    GET_ULONG(X, key, 0);
    GET_ULONG(Y, key, 4);

    // Permuted Choice 1

    T = ((Y >> 4) ^ X) & 0x0F0F0F0F;
    X ^= T;
    Y ^= (T << 4);
    T = ((Y) ^ X) & 0x10101010;
    X ^= T;
    Y ^= (T);

    X = (LHs[ (X) & 0xF] << 3) | (LHs[ (X >> 8) & 0xF ] << 2)
            | (LHs[ (X >> 16) & 0xF] << 1) | (LHs[ (X >> 24) & 0xF ])
            | (LHs[ (X >> 5) & 0xF] << 7) | (LHs[ (X >> 13) & 0xF ] << 6)
            | (LHs[ (X >> 21) & 0xF] << 5) | (LHs[ (X >> 29) & 0xF ] << 4);

    Y = (RHs[ (Y >> 1) & 0xF] << 3) | (RHs[ (Y >> 9) & 0xF ] << 2)
            | (RHs[ (Y >> 17) & 0xF] << 1) | (RHs[ (Y >> 25) & 0xF ])
            | (RHs[ (Y >> 4) & 0xF] << 7) | (RHs[ (Y >> 12) & 0xF ] << 6)
            | (RHs[ (Y >> 20) & 0xF] << 5) | (RHs[ (Y >> 28) & 0xF ] << 4);

    X &= 0x0FFFFFFF;
    Y &= 0x0FFFFFFF;

    // calculate subkeys

    for (i = 0; i < 16; i++) {
        if (i < 2 || i == 8 || i == 15) {
            X = ((X << 1) | (X >> 27)) & 0x0FFFFFFF;
            Y = ((Y << 1) | (Y >> 27)) & 0x0FFFFFFF;
        } else {
            X = ((X << 2) | (X >> 26)) & 0x0FFFFFFF;
            Y = ((Y << 2) | (Y >> 26)) & 0x0FFFFFFF;
        }

        *SK++ = ((X << 4) & 0x24000000) | ((X << 28) & 0x10000000)
                | ((X << 14) & 0x08000000) | ((X << 18) & 0x02080000)
                | ((X << 6) & 0x01000000) | ((X << 9) & 0x00200000)
                | ((X >> 1) & 0x00100000) | ((X << 10) & 0x00040000)
                | ((X << 2) & 0x00020000) | ((X >> 10) & 0x00010000)
                | ((Y >> 13) & 0x00002000) | ((Y >> 4) & 0x00001000)
                | ((Y << 6) & 0x00000800) | ((Y >> 1) & 0x00000400)
                | ((Y >> 14) & 0x00000200) | ((Y) & 0x00000100)
                | ((Y >> 5) & 0x00000020) | ((Y >> 10) & 0x00000010)
                | ((Y >> 3) & 0x00000008) | ((Y >> 18) & 0x00000004)
                | ((Y >> 26) & 0x00000002) | ((Y >> 24) & 0x00000001);

        *SK++ = ((X << 15) & 0x20000000) | ((X << 17) & 0x10000000)
                | ((X << 10) & 0x08000000) | ((X << 22) & 0x04000000)
                | ((X >> 2) & 0x02000000) | ((X << 1) & 0x01000000)
                | ((X << 16) & 0x00200000) | ((X << 11) & 0x00100000)
                | ((X << 3) & 0x00080000) | ((X >> 6) & 0x00040000)
                | ((X << 15) & 0x00020000) | ((X >> 4) & 0x00010000)
                | ((Y >> 2) & 0x00002000) | ((Y << 8) & 0x00001000)
                | ((Y >> 14) & 0x00000808) | ((Y >> 9) & 0x00000400)
                | ((Y) & 0x00000200) | ((Y << 7) & 0x00000100)
                | ((Y >> 7) & 0x00000020) | ((Y >> 3) & 0x00000011)
                | ((Y << 2) & 0x00000004) | ((Y >> 21) & 0x00000002);
    }
}

// fonctions internes

void sccDES8(unsigned long *SK, unsigned char *input, unsigned char *output) {
    unsigned long X, Y, T;

    GET_ULONG(X, input, 0);
    GET_ULONG(Y, input, 4);

    DES_IP(X, Y);

    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);

    DES_FP(Y, X);

    PUT_ULONG(Y, output, 0);
    PUT_ULONG(X, output, 4);
}

void sccTDES8(unsigned long *SK, unsigned char *input, unsigned char *output) {
    unsigned long X, Y, T;

    GET_ULONG(X, input, 0);
    GET_ULONG(Y, input, 4);

    DES_IP(X, Y);

    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);

    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);

    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);
    DES_ROUND(Y, X);
    DES_ROUND(X, Y);

    DES_FP(Y, X);

    PUT_ULONG(Y, output, 0);
    PUT_ULONG(X, output, 4);
}

// fonctions standards

long __sccDES
(
        DES_RB_t *DES_rb
        ) {
    unsigned long i, nb = 0;
    unsigned long ctx[2][96];
    unsigned char temp[8], temp2[8];

    des_main_ks(ctx[0], DES_rb->key);

    if (DES_DECRYPT & DES_rb->options) {
        for (i = 0; i < 32; i += 2) {
            ctx[1][i] = ctx[0][30 - i];
            ctx[1][i + 1] = ctx[0][31 - i];
        }
        nb = 1;
    }

    if (DES_ECB_MODE & DES_rb->options) {
        for (i = 0; i < DES_rb->source.inter.count; i += 8)
            sccDES8(ctx[nb], (unsigned char*) DES_rb->source.inter.buffer + i, (unsigned char*)DES_rb->destination.inter.buffer + i);
    }
    if (DES_CBC_MODE & DES_rb->options) {
        for (i = 0; i < DES_rb->source.inter.count; i += 8) {
            if (DES_ENCRYPT & DES_rb->options) {
                if (0 == i)
                    XorLen(DES_rb->init_v, (unsigned char*)DES_rb->source.inter.buffer, temp, 8);
                else
                    XorLen((unsigned char*)DES_rb->destination.inter.buffer + i - 8, (unsigned char*)DES_rb->source.inter.buffer + i, temp, 8);
            }
            if (DES_DECRYPT & DES_rb->options) {
                memcpy(temp, (unsigned char*)DES_rb->source.inter.buffer + i, 8);
            }

            sccDES8(ctx[nb], temp, (unsigned char*)DES_rb->destination.inter.buffer + i);

            if (DES_DECRYPT & DES_rb->options) {
                if (0 == i)
                    XorLen(DES_rb->init_v, (unsigned char*)DES_rb->destination.inter.buffer, (unsigned char*)DES_rb->destination.inter.buffer, 8);
                else
                    XorLen(temp2, (unsigned char*)DES_rb->destination.inter.buffer + i, (unsigned char*)DES_rb->destination.inter.buffer + i, 8);
                memcpy(temp2, temp, 8);
            }
        }
    }

    return RESULT_GOOD;
}

long TDES
(
        TDES_RB_t *TDES_rb
        ) {
    unsigned long i, nb;
    unsigned long ctx[2][96];
    unsigned char temp[8], temp2[8];

    des_main_ks(ctx[0], TDES_rb->key1);
    des_main_ks(ctx[1] + 32, TDES_rb->key2);
    des_main_ks(ctx[0] + 64, TDES_rb->key3);

    if (DES_ENCRYPT & TDES_rb->options) {
        for (i = 0; i < 32; i += 2) {
            ctx[0][i + 32] = ctx[1][62 - i];
            ctx[0][i + 33] = ctx[1][63 - i];
        }
        nb = 0;
    }
    if (DES_DECRYPT & TDES_rb->options) {
        for (i = 0; i < 32; i += 2) {
            ctx[1][i] = ctx[0][94 - i];
            ctx[1][i + 1] = ctx[0][95 - i];
            ctx[1][i + 64] = ctx[0][30 - i];
            ctx[1][i + 65] = ctx[0][31 - i];
        }
        nb = 1;
    }

    if (DES_ECB_MODE & TDES_rb->options) {
        for (i = 0; i < TDES_rb->source.inter.count; i += 8)
            sccTDES8(ctx[nb], (unsigned char*)TDES_rb->source.inter.buffer + i, (unsigned char*)TDES_rb->destination.inter.buffer + i);
    }
    if (DES_CBC_MODE & TDES_rb->options) {
        for (i = 0; i < TDES_rb->source.inter.count; i += 8) {
            if (DES_ENCRYPT & TDES_rb->options) {
                if (0 == i)
                    XorLen(TDES_rb->init_v, (unsigned char*)TDES_rb->source.inter.buffer, temp, 8);
                else
                    XorLen((unsigned char*)TDES_rb->destination.inter.buffer + i - 8, (unsigned char*)TDES_rb->source.inter.buffer + i, temp, 8);
            }
            if (DES_DECRYPT & TDES_rb->options) {
                memcpy(temp, (unsigned char*)TDES_rb->source.inter.buffer + i, 8);
            }

            sccTDES8(ctx[nb], temp, (unsigned char*)TDES_rb->destination.inter.buffer + i);

            if (DES_DECRYPT & TDES_rb->options) {
                if (0 == i)
                    XorLen(TDES_rb->init_v, (unsigned char*)TDES_rb->destination.inter.buffer, (unsigned char*)TDES_rb->destination.inter.buffer, 8);
                else
                    XorLen(temp2, (unsigned char*)TDES_rb->destination.inter.buffer + i, (unsigned char*)TDES_rb->destination.inter.buffer + i, 8);
                memcpy(temp2, temp, 8);
            }

        }
    }

    return RESULT_GOOD;
}

long DES8bytes
(
        DES8bytes_RB_t *des8_rb
        ) {
    unsigned long i, nb;
    unsigned long ctx[2][32];

    des_main_ks(ctx[0], des8_rb->key);
    if (des8_rb->options & DES_DECRYPT) {
        for (i = 0; i < 32; i += 2) {
            ctx[1][i] = ctx[0][30 - i];
            ctx[1][i + 1] = ctx[0][31 - i];
        }
        nb = 1;
    } else {
        nb = 0;
    }
    sccDES8(ctx[nb], des8_rb->input_data, des8_rb->output_data);

    return RESULT_GOOD;
}

long DES3Key
(
        DES3Key_RB_t *TDES8_rb
        ) {
    unsigned long i, nb;
    unsigned long ctx[2][32];
    unsigned char Temp[8];

    des_main_ks(ctx[0], TDES8_rb->key1);
    if (TDES8_rb->options & DES3_1_DECRYPT) {
        for (i = 0; i < 32; i += 2) {
            ctx[1][i] = ctx[0][30 - i];
            ctx[1][i + 1] = ctx[0][31 - i];
        }
        nb = 1;
    } else {
        nb = 0;
    }
    sccDES8(ctx[nb], TDES8_rb->key_in, TDES8_rb->key_out);

    des_main_ks(ctx[0], TDES8_rb->key2);
    if (TDES8_rb->options & DES3_2_DECRYPT) {
        for (i = 0; i < 32; i += 2) {
            ctx[1][i] = ctx[0][30 - i];
            ctx[1][i + 1] = ctx[0][31 - i];
        }
        nb = 1;
    } else {
        nb = 0;
    }
    sccDES8(ctx[nb], TDES8_rb->key_out, Temp);

    des_main_ks(ctx[0], TDES8_rb->key3);
    if (TDES8_rb->options & DES3_3_DECRYPT) {
        for (i = 0; i < 32; i += 2) {
            ctx[1][i] = ctx[0][30 - i];
            ctx[1][i + 1] = ctx[0][31 - i];
        }
        nb = 1;
    } else {
        nb = 0;
    }
    sccDES8(ctx[nb], Temp, TDES8_rb->key_out);

    return RESULT_GOOD;
}

// fonctions externes

long single_des_ecb_encrypt
(
        unsigned char *key,
        unsigned char *pcleartxt,
        unsigned long *length,
        unsigned char *pciphrtxt
        ) {
    DES_RB_t DES_rb;

    memcpy(&DES_rb.key, key, 8);
    memset(&DES_rb.init_v, 0, 8);
    memset(&DES_rb.term_v, 0, 8);
    DES_rb.source.inter.count = *length;
    DES_rb.source.inter.buffer = pcleartxt;
    DES_rb.destination.inter.count = *length;
    DES_rb.destination.inter.buffer = pciphrtxt;
    memset(&DES_rb.prePadding, 0, sizeof (DES_rb.prePadding));
    memset(&DES_rb.postPadding, 0, sizeof (DES_rb.postPadding));

    DES_rb.options = DES_USE_KEY |
            DES_ENCRYPT |
            DES_ECB_MODE |
            DES_INTERNAL_INPUT |
            DES_INTERNAL_OUTPUT;

    return __sccDES(&DES_rb);
}

// --------------------------------------------------------
// single_des_ecb_decrypt
//     to decrypt a multiple of 8 bytes in ECB mode
// --------------------------------------------------------

long single_des_ecb_decrypt
(
        unsigned char *key,
        unsigned char *pciphrtxt,
        unsigned long *length,
        unsigned char *pcleartxt
        ) {
    DES_RB_t DES_rb;

    memcpy(&DES_rb.key, key, 8);
    memset(&DES_rb.init_v, 0, 8);
    memset(&DES_rb.term_v, 0, 8);
    DES_rb.source.inter.count = *length;
    DES_rb.source.inter.buffer = pciphrtxt;
    DES_rb.destination.inter.count = *length;
    DES_rb.destination.inter.buffer = pcleartxt;
    memset(&DES_rb.prePadding, 0, sizeof (DES_rb.prePadding));
    memset(&DES_rb.postPadding, 0, sizeof (DES_rb.postPadding));

    DES_rb.options = DES_USE_KEY |
            DES_DECRYPT |
            DES_ECB_MODE |
            DES_INTERNAL_INPUT |
            DES_INTERNAL_OUTPUT;

    return __sccDES(&DES_rb);
}

// --------------------------------------------------------
// single_des_cbc_encrypt
//     to encrypt a multiple of 8 bytes in CBC mode
// --------------------------------------------------------

long single_des_cbc_encrypt
(
        unsigned char *key,
        unsigned char *pcleartxt,
        unsigned long *length,
        unsigned char *pciphrtxt
        ) {
    DES_RB_t DES_rb;

    memcpy(&DES_rb.key, key, 8);
    memset(&DES_rb.init_v, 0, 8);
    memset(&DES_rb.term_v, 0, 8);
    DES_rb.source.inter.count = *length;
    DES_rb.source.inter.buffer = pcleartxt;
    DES_rb.destination.inter.count = *length;
    DES_rb.destination.inter.buffer = pciphrtxt;
    memset(&DES_rb.prePadding, 0, sizeof (DES_rb.prePadding));
    memset(&DES_rb.postPadding, 0, sizeof (DES_rb.postPadding));

    DES_rb.options = DES_USE_KEY |
            DES_ENCRYPT |
            DES_CBC_MODE |
            DES_INTERNAL_INPUT |
            DES_INTERNAL_OUTPUT;

    return __sccDES(&DES_rb);
}

// --------------------------------------------------------
// single_des_cbc_decrypt
//     to decrypt a multiple of 8 bytes in CBC mode
// --------------------------------------------------------

long single_des_cbc_decrypt
(
        unsigned char *key,
        unsigned char *pciphrtxt,
        unsigned long *length,
        unsigned char *pcleartxt
        ) {
    DES_RB_t DES_rb;

    memcpy(&DES_rb.key, key, 8);
    memset(&DES_rb.init_v, 0, 8);
    memset(&DES_rb.term_v, 0, 8);
    DES_rb.source.inter.count = *length;
    DES_rb.source.inter.buffer = pciphrtxt;
    DES_rb.destination.inter.count = *length;
    DES_rb.destination.inter.buffer = pcleartxt;
    memset(&DES_rb.prePadding, 0, sizeof (DES_rb.prePadding));
    memset(&DES_rb.postPadding, 0, sizeof (DES_rb.postPadding));

    DES_rb.options = DES_USE_KEY |
            DES_DECRYPT |
            DES_CBC_MODE |
            DES_INTERNAL_INPUT |
            DES_INTERNAL_OUTPUT;

    return __sccDES(&DES_rb);
}

// --------------------------------------------------------
// scc_triple_des_ecb_encrypt.m2
//     to TDES-encrypt a multiple of 8 bytes in ECB mode
// --------------------------------------------------------

long triple_des_ecb_encrypt
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pcleartxt,
        unsigned long *length,
        unsigned char *pciphrtxt
        ) {
    TDES_RB_t TDES_rb;

    memcpy(&TDES_rb.key1, key1, 8);
    memcpy(&TDES_rb.key2, key2, 8);
    memcpy(&TDES_rb.key3, key3, 8);
    memset(&TDES_rb.init_v, 0, 8);
    memset(&TDES_rb.term_v, 0, 8);
    TDES_rb.source.inter.count = *length;
    TDES_rb.source.inter.buffer = pcleartxt;
    TDES_rb.destination.inter.count = *length;
    TDES_rb.destination.inter.buffer = pciphrtxt;
    memset(&TDES_rb.prePadding, 0, sizeof (TDES_rb.prePadding));
    memset(&TDES_rb.postPadding, 0, sizeof (TDES_rb.postPadding));

    TDES_rb.options = DES_TRIPLE_DES |
            DES_USE_KEY |
            DES_ENCRYPT |
            DES_ECB_MODE |
            DES_INTERNAL_INPUT |
            DES_INTERNAL_OUTPUT;

    return TDES(&TDES_rb);
}

long triple_des_ecb_decrypt
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pciphrtxt,
        unsigned long *length,
        unsigned char *pcleartxt
        ) {
    TDES_RB_t TDES_rb;

    memcpy(&TDES_rb.key1, key1, 8);
    memcpy(&TDES_rb.key2, key2, 8);
    memcpy(&TDES_rb.key3, key3, 8);
    memset(&TDES_rb.init_v, 0, 8);
    memset(&TDES_rb.term_v, 0, 8);
    TDES_rb.source.inter.count = *length;
    TDES_rb.source.inter.buffer = pciphrtxt;
    TDES_rb.destination.inter.count = *length;
    TDES_rb.destination.inter.buffer = pcleartxt;
    memset(&TDES_rb.prePadding, 0, sizeof (TDES_rb.prePadding));
    memset(&TDES_rb.postPadding, 0, sizeof (TDES_rb.postPadding));

    TDES_rb.options = DES_TRIPLE_DES |
            DES_USE_KEY |
            DES_DECRYPT |
            DES_ECB_MODE |
            DES_INTERNAL_INPUT |
            DES_INTERNAL_OUTPUT;

    return TDES(&TDES_rb);
}

// --------------------------------------------------------
// triple_des_cbc_encrypt
//     to TDES-encrypt a multiple of 8 bytes in CBC mode
// --------------------------------------------------------

long triple_des_cbc_encrypt
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pcleartxt,
        unsigned long *length,
        unsigned char *pciphrtxt
        ) {
    TDES_RB_t TDES_rb;

    memcpy(&TDES_rb.key1, key1, 8);
    memcpy(&TDES_rb.key2, key2, 8);
    memcpy(&TDES_rb.key3, key3, 8);
    memset(&TDES_rb.init_v, 0, 8);
    memset(&TDES_rb.term_v, 0, 8);
    TDES_rb.source.inter.count = *length;
    TDES_rb.source.inter.buffer = pcleartxt;
    TDES_rb.destination.inter.count = *length;
    TDES_rb.destination.inter.buffer = pciphrtxt;
    memset(&TDES_rb.prePadding, 0, sizeof (TDES_rb.prePadding));
    memset(&TDES_rb.postPadding, 0, sizeof (TDES_rb.postPadding));

    TDES_rb.options = DES_TRIPLE_DES |
            DES_USE_KEY |
            DES_ENCRYPT |
            DES_CBC_MODE |
            DES_INTERNAL_INPUT |
            DES_INTERNAL_OUTPUT;

    return TDES(&TDES_rb);
}

long triple_des_cbc_decrypt
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pciphrtxt,
        unsigned long *length,
        unsigned char *pcleartxt
        ) {
    TDES_RB_t TDES_rb;

    memcpy(&TDES_rb.key1, key1, 8);
    memcpy(&TDES_rb.key2, key2, 8);
    memcpy(&TDES_rb.key3, key3, 8);
    memset(&TDES_rb.init_v, 0, 8);
    memset(&TDES_rb.term_v, 0, 8);
    TDES_rb.source.inter.count = *length;
    TDES_rb.source.inter.buffer = pciphrtxt;
    TDES_rb.destination.inter.count = *length;
    TDES_rb.destination.inter.buffer = pcleartxt;
    memset(&TDES_rb.prePadding, 0, sizeof (TDES_rb.prePadding));
    memset(&TDES_rb.postPadding, 0, sizeof (TDES_rb.postPadding));

    TDES_rb.options = DES_TRIPLE_DES |
            DES_USE_KEY |
            DES_DECRYPT |
            DES_CBC_MODE |
            DES_INTERNAL_INPUT |
            DES_INTERNAL_OUTPUT;

    return TDES(&TDES_rb);
}

// --------------------------------------------------------
// single_des8_encrypt
//     to DES-encrypt 8 bytes
// --------------------------------------------------------

long single_des8_encrypt
(
        unsigned char *key,
        unsigned char *pcleartxt,
        unsigned char *pciphrtxt
        ) {
    DES8bytes_RB_t DES8_rb;
    long Retmsg;

    memcpy(&DES8_rb.key, key, 8);
    memcpy(&DES8_rb.input_data, pcleartxt, 8);

    DES8_rb.options = DES_ENCRYPT;

    Retmsg = DES8bytes(&DES8_rb);
    if (RESULT_GOOD == Retmsg)
        memcpy(pciphrtxt, &DES8_rb.output_data, 8);
    return Retmsg;
}

// --------------------------------------------------------
// single_des8_decrypt
//     to DES-decrypt 8 bytes
// --------------------------------------------------------

long single_des8_decrypt
(
        unsigned char *key,
        unsigned char *pcleartxt,
        unsigned char *pciphrtxt
        ) {
    DES8bytes_RB_t DES8_rb;
    long Retmsg;

    memcpy(&DES8_rb.key, key, 8);
    memcpy(&DES8_rb.input_data, pcleartxt, 8);

    DES8_rb.options = DES_DECRYPT;

    Retmsg = DES8bytes(&DES8_rb);
    if (RESULT_GOOD == Retmsg)
        memcpy(pciphrtxt, &DES8_rb.output_data, 8);
    return Retmsg;
}

// --------------------------------------------------------
// triple_des8_encrypt
//     to TDES-encrypt 8 bytes
// --------------------------------------------------------

long triple_des8_encrypt
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pcleartxt,
        unsigned char *pciphrtxt
        ) {
    DES3Key_RB_t TDES8_rb;
    long Retmsg;

    memcpy(&TDES8_rb.key1, key1, 8);
    memcpy(&TDES8_rb.key2, key2, 8);
    memcpy(&TDES8_rb.key3, key3, 8);
    memcpy(&TDES8_rb.key_in, pcleartxt, 8);

    TDES8_rb.options = DES3_1_ENCRYPT |
            DES3_2_DECRYPT |
            DES3_3_ENCRYPT;

    Retmsg = DES3Key(&TDES8_rb);
    if (RESULT_GOOD == Retmsg)
        memcpy(pciphrtxt, &TDES8_rb.key_out, 8);
    return Retmsg;
}


// --------------------------------------------------------
// triple_des8_decrypt
//     to TDES-decrypt 8 bytes
// --------------------------------------------------------

long triple_des8_decrypt
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pciphrtxt,
        unsigned char *pcleartxt
        ) {
    DES3Key_RB_t TDES8_rb;
    long Retmsg;

    memcpy(&TDES8_rb.key1, key3, 8);
    memcpy(&TDES8_rb.key2, key2, 8);
    memcpy(&TDES8_rb.key3, key1, 8);
    memcpy(&TDES8_rb.key_in, pciphrtxt, 8);
    TDES8_rb.options = DES3_1_DECRYPT |
            DES3_2_ENCRYPT |
            DES3_3_DECRYPT;

    Retmsg = DES3Key(&TDES8_rb);
    if (RESULT_GOOD == Retmsg)
        memcpy(pcleartxt, &TDES8_rb.key_out, 8);
    return Retmsg;
}

// --------------------------------------------------------
// triple_des8_decrypt_dmode
//     to TDES-encrypt-encrypt-encrypt 8 bytes
// --------------------------------------------------------

long triple_des8_decrypt_dmode
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pcleartxt,
        unsigned char *pciphrtxt
        ) {
    DES3Key_RB_t TDES8_rb; // In/Out struc f.DES (SCC_INT.H)
    long Retmsg; // subroutine error message

    memcpy(&TDES8_rb.key1, key1, 8);
    memcpy(&TDES8_rb.key2, key2, 8);
    memcpy(&TDES8_rb.key3, key3, 8);
    memcpy(&TDES8_rb.key_in, pcleartxt, 8);

    TDES8_rb.options = DES3_1_ENCRYPT |
            DES3_2_ENCRYPT |
            DES3_3_ENCRYPT;

    // -----------------------------------
    // Run the DES3Key call
    // -----------------------------------
    Retmsg = DES3Key(&TDES8_rb);
    if (RESULT_GOOD == Retmsg)
        memcpy(pciphrtxt, &TDES8_rb.key_out, 8);
    return Retmsg;
} // end of triple_des8_encrypt

// --------------------------------------------------------
// triple_des8_encrypt_dmode
//     to TDES-decrypt-decrypt-decrypt 8 bytes
// --------------------------------------------------------

long triple_des8_encrypt_dmode
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pciphrtxt,
        unsigned char *pcleartxt
        ) {
    DES3Key_RB_t TDES8_rb; // In/Out struc f.DES (SCC_INT.H)
    long Retmsg; // subroutine error message

    memcpy(&TDES8_rb.key1, key1, 8);
    memcpy(&TDES8_rb.key2, key2, 8);
    memcpy(&TDES8_rb.key3, key3, 8);
    memcpy(&TDES8_rb.key_in, pciphrtxt, 8);

    TDES8_rb.options = DES3_1_DECRYPT |
            DES3_2_DECRYPT |
            DES3_3_DECRYPT;

    // -----------------------------------
    // Run the DES3Key call
    // -----------------------------------
    Retmsg = DES3Key(&TDES8_rb);
    if (RESULT_GOOD == Retmsg)
        memcpy(pcleartxt, &TDES8_rb.key_out, 8);
    return Retmsg;
} // end of triple_des8_decrypt

// --------------------------------------------------------
// triple_des_cbc_encrypt_dmode
//     to TDES-decrypt-decrypt-decrypt a multiple of 8 bytes in CBC mode
// --------------------------------------------------------

long triple_des_cbc_encrypt_dmode
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pcleartxt,
        unsigned long *length,
        unsigned char *pciphrtxt
        ) {
    unsigned long indice;
    long RetMsg;
    unsigned char *pointer = pciphrtxt;

    for (indice = 0; indice<*length; indice += 8) {
        if (0 < indice)
            XorLen(pcleartxt + indice, pointer - 8, pointer, 8);
        else
            memcpy(pointer, pcleartxt, 8);

        RetMsg = triple_des8_encrypt_dmode
                (
                key1,
                key2,
                key3,
                pointer,
                pointer
                );
        if (RESULT_GOOD != RetMsg)
            return RetMsg;
        pointer += 8;
    }
    return RESULT_GOOD;
}

// --------------------------------------------------------
// triple_des_cbc_decrypt_dmode
//     to TDES-encrypt-encrypt-encrypt a multiple of 8 bytes in CBC mode
// --------------------------------------------------------

long triple_des_cbc_decrypt_dmode
(
        unsigned char *key1,
        unsigned char *key2,
        unsigned char *key3,
        unsigned char *pciphrtxt,
        unsigned long *length,
        unsigned char *pcleartxt
        ) {
    unsigned long indice;
    long RetMsg;
    unsigned char *pointer = pciphrtxt + *length;

    for (indice = *length; indice >= 8; indice -= 8) {
        pointer -= 8;

        RetMsg = triple_des8_decrypt_dmode
                (
                key1,
                key2,
                key3,
                pointer,
                pointer
                );
        if (RESULT_GOOD != RetMsg)
            return RetMsg;

        if (8 < indice)
            XorLen(pointer, pointer - 8, pcleartxt + indice - 8, 8);
        else
            memcpy(pcleartxt, pointer, 8);
    }
    return RESULT_GOOD;
}
