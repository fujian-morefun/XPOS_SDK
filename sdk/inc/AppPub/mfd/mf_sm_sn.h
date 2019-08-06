#pragma once



#ifdef __cplusplus
extern "C"{
#endif

#include "pub/pub.h"

enum
{
	SM_ECB		=	0,	///<ECBģʽ
	SM_CBC				///<CBCģʽ
};
#define SN_SM4_ENCRYPT     1
#define SN_SM4_DECRYPT     0

LIB_EXPORT int mf_sm4Calc(unsigned char *output, unsigned char *input, unsigned char *key, int direction,int cbc_ecb);
LIB_EXPORT int get_encry_sn_info(char*sSnInfo,int nlen,char* sEncrySn);

#ifdef __cplusplus
}
#endif
