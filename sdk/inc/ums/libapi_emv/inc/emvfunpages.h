#ifndef __EMVFUNPAGES_H__
#define __EMVFUNPAGES_H__

#include "emv\inc\emv_interface.h"
#include "AppPub/inc/pub_define.h"
#include "AppPub/inc/pub_def.h"
#include "AppPub/inc/ex_misc.h"

void InitEMVFunP();
void SetAmount(long long nAmt);
void SetIsEC(mf_bool bEc);
mf_bool GetIsPowerUp();

int SetEmvFunc();
int SetEmvRfFunc();

#endif

