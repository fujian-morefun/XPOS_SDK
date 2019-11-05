#ifndef __EMV_AID_CAPK__
#define __EMV_AID_CAPK__ 
#include <emv_interface.h>

LIB_EXPORT int Emv_GetAIDList(void);
LIB_EXPORT void Emv_FreeAIDList(void);

LIB_EXPORT YESORNO IsAIDMatch(char *pszICCAID,int nICCAIDLen,int *nIndex);
LIB_EXPORT YESORNO Rf_IsAIDMatch(char *pszICCAID,int nICCAIDLen,int iKernelId,int *nIndex);

//paypassÐÂÔö
LIB_EXPORT void PP_FreeAIDListEx(void);
LIB_EXPORT void LC_Emv_FreeAIDList(void);
#endif