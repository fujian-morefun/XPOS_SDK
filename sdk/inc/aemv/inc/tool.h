#ifndef _TOOL_
#define _TOOL_

extern unsigned long long BcdtoUint64( unsigned char *pszBcdBuf,  int nBufLen);
extern int IntTo4Bcd(char *psBcd, int *pnBcdLen, int nNum);
extern int VisaGetAmount(unsigned char cTransType);
extern int EmvGetAmount();

int GetPanFromTrack(const char *pszTrack,int nMaxTrackLen,int *nPanLen,char *sPan);
/******************************************************************************
 *  	函数名称:	RecoverTrack2: 
 *	函数介绍:	复原二磁道等价数据为二磁道数据
 *	入口参数:	
 *	出口参数:     
 * 	返回值  :		
 ******************************************************************************/
int RecoverTrack2(char *psInTrack2,int nLen,char *psOutTrack2,int *nOutLen);
/******************************************************************************
 *  	函数名称:	GetExpiryFromTrack2: 
 *	函数介绍:	从二磁道数据获取有效期
 *	入口参数:	
 *	出口参数:     
 * 	返回值  :		
 ******************************************************************************/
int GetExpiryFromTrack2(const char *pszTrack,int nMaxTrackLen,char *sExpiry);
/******************************************************************************
 *  	函数名称:	EmvGetAmt: 
 *	函数介绍:	获取金额
 *	入口参数:	
 *	出口参数:     
 * 	返回值  :		
 ******************************************************************************/
int EmvGetAmt(char cTransType);
#endif