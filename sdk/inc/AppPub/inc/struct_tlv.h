#ifndef _BER_TLV_H
#define _BER_TLV_H
#include "pub_define.h"
#include "pub/pub.h"

	typedef struct _Bytes{
		int  nLen;
		BYTE *data;
	}Bytes, *pBytes;

	typedef struct _TlvData{
		Bytes tag;
		Bytes val;
	}TlvData, *pTlvData;

	LIB_EXPORT extern int Ex_TLV_GetDataByTag(BYTE *psTag, BYTE *psSrc, int nSrcLen,BYTE *psBuf, int *nBufLen);
	LIB_EXPORT extern int Ex_TLV_GetDataByTagandTmplt( BYTE *psTag, BYTE *psTmplt, BYTE *psSrc, int nSrcLen,BYTE *psBuf,int *nBufLen);
	LIB_EXPORT extern int Ex_TLV_Count(BYTE *src, int nSrcLen,int *nCount);
	LIB_EXPORT extern int Ex_TLV_Unpack_Data(pTlvData *dst, BYTE *src, int nLen,int *nNum);
	LIB_EXPORT extern int Ex_TLV_Count_EX(BYTE *psSrc, int nSrcLen,int *nCount);
	LIB_EXPORT extern int Ex_TLV_Unpack_Data_EX(pTlvData *dst, BYTE *src, int nLen,int *nNum);
	LIB_EXPORT extern int Ex_TLV_Pack_Data(BYTE *psBuf, BYTE *psTag, BYTE *psSrc, int nSize,int *nBufLen);
	LIB_EXPORT extern int Ex_TLV_GetDataFromTlv(pTlvData tlv,int nCount,BYTE *psTag,BYTE *psBuf,int *nBufLen,int *nIndex);

	LIB_EXPORT extern void Ex_TLV_Parse_Tag(pBytes tag, BYTE *psSrc);
	LIB_EXPORT extern int Ex_TLV_GetTagOff(BYTE *psTag, BYTE *psSrc, int nSrcLen,int *nOff,int *nLen);
	LIB_EXPORT extern int Ex_TLV_IsDuplicates(pTlvData tlv,int nCount,BYTE *psTag);
	LIB_EXPORT extern int ecsn_tlv_data(char*outbuf,char* tag,char*srcdata,int datalen);
	LIB_EXPORT extern int ecsn_tlv2_data(char*outbuf,unsigned char tag,char*srcdata,int datalen);

#endif