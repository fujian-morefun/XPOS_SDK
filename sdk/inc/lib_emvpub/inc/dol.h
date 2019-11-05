#ifndef __DOL__
#define __DOL__

#include "emv_interface.h"

LIB_EXPORT int Pack_Dol_Pdol(char * pszDol, int nDolLen,char * pszDolData,int *nDolDataLen);
LIB_EXPORT int Pack_Dol(char * pszDol, int nDolLen,char * pszDolData,int *nDolDataLen);
LIB_EXPORT int Pack_Dol_DsDol(char * pszDol, int nDolLen,char * pszDolData,int *nDolDataLen);
LIB_EXPORT int Pack_Dol_Cdol(char * pszDol, int nDolLen,char * pszDolData,int *nDolDataLen);
LIB_EXPORT int TagIsDolInclude(char *pTag,char *pDolData,int iDolDataLen);
#endif