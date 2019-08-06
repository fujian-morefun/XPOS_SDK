#ifndef __EMV_AID_CAPK__
#define __EMV_AID_CAPK__ 
#include <emv_interface.h>
extern int Emv_GetAIDList(void);
extern void Emv_FreeAIDList(void);
extern int Emv_Is_AIDList();
extern YESORNO IsAIDMatch(char *pszICCAID,int nICCAIDLen,int *nIndex);
extern YESORNO IsAIDMatchEx(char *pszICCAID,int nICCAIDLen,int iKernelId);

//paypassÐÂÔö
extern void Emv_FreeAIDListEx(void);
extern void LC_Emv_FreeAIDList(void);
extern int EMV_vGetCurrentCapk(ST_CAPK *pstCapk);
#endif