#ifndef __EMV_BLACKLIST__
#define __EMV_BLACKLIST__ 

/* transaction log with amount */
typedef struct {
	char szPan[10];
	char cPanLen;
	char szAmt[4];
	char cResv;
}STTRANSLOG;

extern int LC_CheckCertBL(char *pszSerialNum);
extern int CheckCertBL_EX(char *pszSerialNum);
extern int CheckCertBL(char *pszSerialNum);
extern int Emv_AddTransLog(void);
extern int GetTransTotleAmt(char *pszPan,int nLen,long long *nOutTotal);

#endif