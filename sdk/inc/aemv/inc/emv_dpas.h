#ifndef __EMV_DPAS__
#define __EMV_DPAS__ 

#include "emv_interface.h"

extern int Dpas_Rf_PreProcess(STEMVPROC *stProc,char *pszAid,char nAidLen);

extern int EMV_Rf_Trans_Dpas(STEMVPROC *stProc);

extern int EMV_Rf_Compelte_Dpas(STEMVPROC *stProc);




#endif