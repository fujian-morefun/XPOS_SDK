#ifndef __EMV_DATA__
#define __EMV_DATA__ 
#include "define.h"

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



#endif

extern int InitEmvData(char *pszData,int nLen);
extern void FreeEmvData(void);
extern YESORNO TagIsTermData(char *pszTag,int nLen);
//extern int GetEmvData(char *pszTag,char *pszData,int *nDataLen);
extern int SaveEmvTlvData(TlvData elem,YESORNO bOverride);
extern int PP_SaveEmvTlvDataForUnknown(TlvData elem,int iType);
extern int SaveEmvData(char *pszTag,char *pszData,int nLen,YESORNO bOverride);
extern int SetEmvData(int nIndex,char cTransType,int nEmvTransSerial);
extern void paypass_random_number(char *sRanNumber);

//paypass改造新增接口
void FreeActResource(void);
void UpdateParamForSelectNextApp(void);		//next app数据
void PP_UpdateParamForSelectNextApp(char *pActParam,int iActParamLen);
int ClearHashTableData(void);
int InitEmvDataEx(void);
int InitEmvDataEx2(char *pszData,int nLen);
//int LC_InitEmvData(char *pszData,int nLen,EMV_stTermAIDList *pstTermAid,int iAidCount);
int PP_iPreProcess(void);
void FreeEmvDataEx(void);
void LC_FreeEmvData(void);
void FreeEmvDataEx2(void);
int  PP_iSaveDetInfo(char *pTlvList,int iListLen);
int PP_iIsPermitDetUpate(char *pTag,int iTagLen);
int  PP_iParseAndStoreCardResponse(char *pTemp,int iTempLen,TlvData elem);
int EMV_iTermSupportAidCount(void);
void EMV_vDisplayTermSupportAid(void);
int PayPass_IsKnownTag(char *pTag,int iTagLen);
int PayPass_iUpdateUnknownTagState(char *Tag,int iTagLen,int iValueLen);
int PayPass_iUpdateTermParamTagState(char *Tag,int iTagLen,int iValueLen);
int PayPass_iCheckTagState(char *Tag);
void PP_vInitTableElement(void);
void PP_vInitTableElement_ADF(void);
int PayPass_iSetUnknownTagUpdateRA(char *pTag,int iTagLen);

int EMV_GetCurrentKid(void);
int EMV_iSetCurrentKid(int iKernelId);

