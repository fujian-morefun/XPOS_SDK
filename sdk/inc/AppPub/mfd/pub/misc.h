#pragma once

#include "pub/pub.h"

#ifdef __cplusplus
extern "C"{
#endif

LIB_EXPORT unsigned char* makeXOR(unsigned char *b1, unsigned char *b2, int start, int n);

//没有异或
LIB_EXPORT int makeXORnDES(unsigned char *key, int nKeyLen,unsigned char *mac, unsigned char *data, int start, int n);

LIB_EXPORT int AscToHex1 (const unsigned char* pszAsciiBuf, int nLen, char cType, unsigned char* pszBcdBuf);

//有异或
LIB_EXPORT int makeXORnDES_ex(unsigned char *key, int nKeyLen,unsigned char *mac, unsigned char *data, int start, int n);

#ifdef __cplusplus
}
#endif
