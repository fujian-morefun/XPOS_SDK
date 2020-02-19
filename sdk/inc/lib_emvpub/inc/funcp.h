#ifndef __FUNCP__
#define __FUNCP__

#include "emv_interface.h"

LIB_EXPORT int EMV_SetFileName(STEMV_FILE *stEmvFileName);
LIB_EXPORT int EMV_SetFunP(ST_UI *stEMVUI,STCOMM *stEMVICComm,ST_EMV_EXPAND_INTERFACE*stInterface);
LIB_EXPORT int RF_deactive( int nTime );
LIB_EXPORT ST_UI* emvpub_ui(void);
LIB_EXPORT STEMV_FILE* emvpub_file(void);
LIB_EXPORT ST_EMV_EXPAND_INTERFACE* emvpub_interface(void);
LIB_EXPORT STCOMM * emvpub_icop(void);
LIB_EXPORT STICS* emvpub_ics(void);
LIB_EXPORT int emvpub_read_ics();
//LIB_EXPORT int RF_setParam(ST_RF_PROC *st_pr_proc);
//LIB_EXPORT ST_RF_PROC* RF_getParam(void);
#endif

