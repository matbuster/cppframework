/**
 * \file 		ibm.h
 * \date 		04/11/2015 
 * \author 		NSJ
 */ 

 //TODO_NSJ// Supprimer le ibm.h voir source c
 
#ifndef IBM_H
#define IBM_H

#ifdef _WINDOWS
// Include de pthread necessaire a cmncryt2.h sous windows
#include "pthread.h"
#endif //_WINDOWS

#include "cmncryt2.h"
#include "cmnerrcd.h"

#include "scc_int.h"
#include "cam_xtrn.h"
#include "xc_err.h"


typedef struct {
    ULONG total[2];
    ULONG state[5];
    UCHAR buffer[64];
} hash_context;

#endif //IBM_H
