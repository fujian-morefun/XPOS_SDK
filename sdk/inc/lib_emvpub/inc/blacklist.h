#ifndef __EMV_BLACKLIST__
#define __EMV_BLACKLIST__ 

#include "emv_interface.h"
/* transaction log with amount */
typedef struct {
	char szPan[10];
	char cPanLen;
	char szAmt[4];
	char cResv;
}STTRANSLOG;

LIB_EXPORT int Rf_CheckCertBL(char *pszSerialNum);
LIB_EXPORT int CheckCertBL(char *pszSerialNum);
LIB_EXPORT int Emv_AddTransLog(void);
LIB_EXPORT int GetTransTotleAmt(char *pszPan,int nLen,long long *nOutTotal);

#endif