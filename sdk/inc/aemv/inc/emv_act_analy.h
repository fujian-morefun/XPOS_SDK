#ifndef __EMV_ACT_ANALY__
#define __EMV_ACT_ANALY__

#include <emv_interface.h>
#include <define.h>
#define MAXLEN_ISSAPPDATA 32

extern int GetGACData(char *pszData, int nLen, YESORNO cCDAFlag);
extern int InterpretCid_Low(uchar cid);
extern int PraseGAC(int nGacStep,E_GAC eGacType,char *pszGACData,int nDataLen,STEMVPROC *stProc);
extern void CalcTCHash(void);
extern int Emv_act_analy(STEMVPROC *stProc);
extern int PayPass_term_act_analy(E_GAC *pTermAcType);
extern int PayPass_card_act_analy(E_GAC eGacType,uint iIsPackDsDol,int iIsReqCda,char *pOutRespData,int *piOutDataLen);
extern int SM_CDA_GAC(int nGacStep, char *pszGacRes, int nGacLen);
#endif