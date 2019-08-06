#ifndef _TOOL_
#define _TOOL_

#include "apppub/inc/mf_basic.h"
#include "apppub/inc/pub_def.h"
#include "emv_interface.h"

/*	9F10中返回的交易标识*/
#define	IAD_AAC(x )				(( *((x) + 4) & 0x30) == 0x00 )
#define	IAD_TC(x )				(( *((x) + 4) & 0x30) == 0x10 )
#define	IAD_ARQC(x )			(( *((x) + 4) & 0x30) == 0x20 )
#define IAD_FCHECK(x)			( *((x) + 5) & 0x20) 		/*卡片频度检查超限位:
														电子现金单笔交易限额
														电子现金余额不足
														授权金额加上 CTTA 大于 CTTAUL
														余额小于电子现金重置阈值*/

LIB_EXPORT unsigned long long BcdtoUint64( unsigned char *pszBcdBuf,  int nBufLen);
LIB_EXPORT int IntTo4Bcd(char *psBcd, int *pnBcdLen, int nNum);
LIB_EXPORT int VisaGetAmount(unsigned char cTransType);
LIB_EXPORT int EmvGetAmount();

LIB_EXPORT int GetPanFromTrack(const char *pszTrack,int nMaxTrackLen,int *nPanLen,char *sPan);
/******************************************************************************
 *  	函数名称:	RecoverTrack2: 
 *	函数介绍:	复原二磁道等价数据为二磁道数据
 *	入口参数:	
 *	出口参数:     
 * 	返回值  :		
 ******************************************************************************/
LIB_EXPORT int RecoverTrack2(char *psInTrack2,int nLen,char *psOutTrack2,int *nOutLen);
/******************************************************************************
 *  	函数名称:	GetExpiryFromTrack2: 
 *	函数介绍:	从二磁道数据获取有效期
 *	入口参数:	
 *	出口参数:     
 * 	返回值  :		
 ******************************************************************************/
LIB_EXPORT int GetExpiryFromTrack2(const char *pszTrack,int nMaxTrackLen,char *sExpiry);
/******************************************************************************
 *  	函数名称:	EmvGetAmt: 
 *	函数介绍:	获取金额
 *	入口参数:	
 *	出口参数:     
 * 	返回值  :		
 ******************************************************************************/
LIB_EXPORT int EmvGetAmt(unsigned char cTransType);

LIB_EXPORT YESORNO BeforeDate(uchar *pszDate,int nlen);
LIB_EXPORT YESORNO AfterDate(uchar *pszDate);

LIB_EXPORT int CheckAppVer();
LIB_EXPORT int CheckAUC();

LIB_EXPORT int CheckAppData();

LIB_EXPORT int CheckExpireDate();
LIB_EXPORT int CheckEffecDate();

//非接通用接口
LIB_EXPORT YESORNO rf_GetICTransPropIsSet(int nMask);
LIB_EXPORT YESORNO rf_GetTmTransPropIsSet(int nMask);
LIB_EXPORT void rf_SetTmTransProp( int iSetMask);

LIB_EXPORT int rf_get_pan_len(char*sData, int nLen);
LIB_EXPORT int rf_aflcheck(char *szData,int nDataLen);
LIB_EXPORT int rf_check_pan(char*pszTrack,int nMaxTrackLen);
LIB_EXPORT int rf_quic_ccid(char*szIssAppData,YESORNO*bccid);

LIB_EXPORT YESORNO dpas_GetCardPropRequireIsSet(int nMask);
LIB_EXPORT void dpas_SetCardPropRequire( int iSetMask);

#endif
