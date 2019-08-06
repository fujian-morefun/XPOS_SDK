#ifndef __PAYPASS_RRP__
#define __PAYPASS_RRP__

#include "define.h"
#include "pub/pub.h"

//RRP指令卡片应答数据
typedef struct 
{
	uchar ucRRP_Entropy[4];
	uchar ucRRP_MinTimeAPDU[2];
	uchar ucRRP_MaxTimeAPDU[2];
	uchar ucRRP_EstimatedTimeRADDU[2];
}RRP_RESP_DATA;

int paypass_rrp_proc(char *pUnNumber,RRP_RESP_DATA *pRespData,int *piTakenTime);

#endif

