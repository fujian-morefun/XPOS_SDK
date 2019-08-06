#include "driver/mf_rtc.h"
#include <time.h>
#include "pub\osl\inc\osl_filedef.h"
#include "emv_interface.h"

int Qpass_GetBin(ST_BIN_DATA *pBin,int binType);
int Qpass_Shankadata(ST_QFAIL_DATA *stFail_data,int nIndex);
int Qpass_Shanka(ST_QFAIL_DATA *stFail_data,int nQfailcount);

