/**
 * \file 		xor.cpp
 * \date 		04/11/2015 
 * \author 		NSJ
 */ 

// Include des en-tetes framework
#include "xor.h"

void XorLen
  (
    unsigned char *In1,
    unsigned char *In2,
    unsigned char *Out,
    unsigned long In_Lg
  )
  {
    unsigned long indice;
    for (indice=0;indice<In_Lg;indice++)
      Out[indice]=In1[indice]^In2[indice];
  }
