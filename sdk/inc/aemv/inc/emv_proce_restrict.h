#ifndef __EMV_PROC_RESTRICT__
#define __EMV_PROC_RESTRICT__

#define VISA_AAC	1
#define	VISA_ARQC	2
#define	VISA_TC		3
#define	VISA_OTHER	4//转其他界面

extern void Emv_Process_Restrict();
extern int vcps_Process_Restrict(int iadtype,unsigned char cTransType);
extern void PP_ProcessRestrict_Step(void);

extern void Dpas_EMV_Process_Restrict();

YESORNO BeforeDate(uchar *pszDate,int nLen);
int CheckExpireDate();
int CheckEffecDate();
#endif