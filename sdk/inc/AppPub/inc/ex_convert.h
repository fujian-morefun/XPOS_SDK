#ifndef _CONVERT_H
#define _CONVERT_H
#include "pub/pub.h"

#include "pub_def.h"
#ifdef __cplusplus
extern "C"{
#endif



LIB_EXPORT extern const  char *Ex_Str_hexdump(const void *data, unsigned int len);
LIB_EXPORT extern int Ex_Str_AscToHex (const unsigned char* pszAsciiBuf, int nLen, char cAlignment, unsigned char* pszBcdBuf);
LIB_EXPORT extern int Ex_Str_HexToAsc (const unsigned char* pszBcdBuf, int nLen, char cAlignment, unsigned char* pszAsciiBuf);
LIB_EXPORT extern void Ex_Str_IntToChar4 (unsigned char* pszBuf, const unsigned int nNum );
LIB_EXPORT extern void Ex_Str_IntToC4(char* buffer, int num);
LIB_EXPORT extern void Ex_Str_IntToChar2 (unsigned char* pszBuf, const unsigned int nNum );
LIB_EXPORT extern void Ex_Str_Char4ToInt (unsigned int* nNum, unsigned char* pszBuf );
LIB_EXPORT extern int C4ToInt(unsigned char* buffer);
LIB_EXPORT extern void Ex_Str_Char2ToInt(unsigned int *nNum, unsigned char *pszBuf);
LIB_EXPORT extern int Ex_Str_ByteToBcd(int nNum, char *ch);
LIB_EXPORT extern int Ex_Str_BcdToByte(char ch, int *pnNum);
LIB_EXPORT extern int Ex_Str_IntToBcd(char *psBcd, int *pnBcdLen, int nNum);
LIB_EXPORT extern int Ex_Str_BcdToInt(const char * psBcd, int *nNum);
LIB_EXPORT extern int Ex_Str_IncOne (char* pcStrNum );
LIB_EXPORT extern void Ex_Str_Reverse(char *indata,char *outdata,int length);
LIB_EXPORT extern char *Ex_Str_myitoa(int num,char *str,int radix) ;
//extern void Ex_Str_TimeSt2Sz(mf_DATETIME stDataTime, char *pszTime);
LIB_EXPORT extern int Valid_YYMMDD(char *pszTime);
LIB_EXPORT extern YESORNO IsExpire(char *pszExpDate);
LIB_EXPORT extern void Ex_GetDataTime(char *pszDateTime);
LIB_EXPORT extern char * EX_GetResPath(char *pFilePath);
LIB_EXPORT extern char * EX_GetFilePath(char *pFilePath);
LIB_EXPORT extern int  Ex_ConvPanDis(const char * szPan,char * szPanDes,int  * nPanLen);
LIB_EXPORT extern int Ex_ConvInputAmount(char *AmountSource,char * AmountDest);
LIB_EXPORT extern unsigned long long Ex_BcdtoUint64( unsigned char *pszBcdBuf,  int nBufLen);
LIB_EXPORT extern int Ex_IntTo4Bcd(char *psBcd, int *pnBcdLen, int nNum);
LIB_EXPORT extern int Ex_ConvertTime(const char *srcDate ,char * desDate);
LIB_EXPORT extern int Ex_ConvertDate(const char *srcDate ,char * desDate);
LIB_EXPORT extern void Ex_Str_LongToChar12 (unsigned char* pszBuf, const long long nNum );
LIB_EXPORT extern void Ex_Str_Char12ToLong (long long* nNum, unsigned char* pszBuf );
#ifdef __cplusplus
}
#endif

#endif