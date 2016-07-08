
//Include des en-tetes standard windows
#ifdef WIN32
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h> 

#include "CharArgs.h"

// ------------------------------------------------------
int Tools::String::CharArgs::wstrlen(_TCHAR * wstr)
{
    int l_idx = 0;
    while (((char*)wstr)[l_idx] != 0) l_idx += 2;
    return l_idx;
}

// ------------------------------------------------------
// Allocate char string and copy TCHAR->char->string
char * Tools::String::CharArgs::wstrdup(_TCHAR *wSrc)
{
    int l_idx = 0;
    int l_len = wstrlen(wSrc);
    char *l_nstr = (char *)malloc(l_len);
    if (l_nstr) {
        do {
            l_nstr[l_idx] = (char)wSrc[l_idx];
            l_idx++;
        } while ((char)wSrc[l_idx] != 0);
    }
    l_nstr[l_idx] = 0;
    return l_nstr;
}

// ------------------------------------------------------
Tools::String::CharArgs::CharArgs(int argcc, _TCHAR* argv[]) : arg_num(argcc)
{
    l_argn = (char **)malloc(argcc *sizeof(char*));
    for (int idx = 0; idx < argcc; idx++) l_argn[idx] = wstrdup(argv[idx]);
}

// ------------------------------------------------------
Tools::String::CharArgs::~CharArgs()
{
    for(int idx = 0; idx < arg_num; idx++) if (l_argn[idx]) free(l_argn[idx]);
    free(l_argn);
}

#endif // WIN32

// ------------------------------------------------------