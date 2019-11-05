#ifndef __EMV_DATA__
#define __EMV_DATA__ 
#include "define.h"
#include "emv_interface.h"

#define LEN_RANDOM 4

typedef struct {
	unsigned char szDF_84[16+1];			/*	DF名*/
	int nDFLen;							/**<文件名长度*/
	unsigned char szFCI_A5[MAXLEN_ICCRESP+1];	/*	FCI数据*/
	int nFCILen;							/**<FCI数据长度*/
}ST_ICFILE;

/*****paypass改造新增接口********/
/* 数据元结构 */
typedef struct ST_DATA_ELEMENT
{
	uchar   ucTag[3+1];		// 数据标签(最大长度3字节)
	uchar   ucLenTag;		// 数据标签的实际长度
	uchar   ucLenCheck;		// 长度校验标志		0---不校验长度  1--校验长度
	ushort  usLenMin;		// 数据的最小长度 
	ushort  usLenMax;		// 数据的最大长度 
	uchar   ucState;		// 数据元状态(0---不存在  1---Emtpy 2--Not Empty)
	uchar	cTempType;		// 数据元可能所在的模板
	uchar   ucIsSupportRA;	// 是否支持RA更新条件
}ST_Element;

//#define AID_MAX_NUM  50
#define AID_MAX_NUM  25
//#define REC_CERT_MAX_NUM	100
#define REC_CERT_MAX_NUM	70   //检测程序要求默认设置60条

LIB_EXPORT int InitEmvData(char *pszData,int nLen);
LIB_EXPORT void FreeEmvData(void);
LIB_EXPORT YESORNO TagIsTermData(char *pszTag,int nLen);
LIB_EXPORT int SaveEmvTlvData(TlvData elem,YESORNO bOverride);
LIB_EXPORT int SetEmvData(int nIndex,char cTransType,int nEmvTransSerial);
LIB_EXPORT int DelEmvData(char *pszTag,int nTaglen);
LIB_EXPORT int ClearHashTableData(void);

LIB_EXPORT void Rf_FreeEmvData(void);

LIB_EXPORT int EMV_iTermSupportAidCount(void);
LIB_EXPORT void EMV_vDisplayTermSupportAid(void);

LIB_EXPORT int EMV_GetCurrentKid(void);
LIB_EXPORT int EMV_iSetCurrentKid(int iKernelId);

LIB_EXPORT void SaveTransType(char cTransType);

LIB_EXPORT char IsEcOnly();

LIB_EXPORT void Emv_SetErrCode(char cCode);
LIB_EXPORT void Emv_vSetSW1SW2(int iSW1SW2);
LIB_EXPORT int Emv_iGetSW1SW2(void);
LIB_EXPORT int EMV_iGetL1ErrorCode(void);
LIB_EXPORT void EMV_iSetL1ErrorCode(int iErrorCode);

LIB_EXPORT int Emv_Is_AIDList();
LIB_EXPORT int EMV_vGetCurrentCapk(ST_CAPK *pstCapk);

LIB_EXPORT int Init_PP_Data(void);
LIB_EXPORT void set_pp_actLen(int nvalue);
LIB_EXPORT int get_pp_actLen(void);
LIB_EXPORT int PP_SaveEmvTlvDataForUnknown(TlvData elem,int iType);

LIB_EXPORT int Rf_InitEmvData(char *pszData,int nLen,EMV_stTermAIDList *pstTermAid,int iAidCount);

#endif