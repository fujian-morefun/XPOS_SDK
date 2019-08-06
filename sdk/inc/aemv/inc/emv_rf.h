#ifndef __EMV_RF__
#define __EMV_RF__

#include <emv_interface.h>

#define EMV_RF_PROP_MSD			0x0080		/**< 1:支持非接触磁条 (MSD) ,0:不支持*/
#define EMV_RF_PROP_PBOCCLSS		0x0040		/**< 1:支持非接触PBOC,0:不支持*/
#define EMV_RF_PROP_QPBOC			0x0020		/**< 1:支持非接触qPBOC,0:不支持*/
#define EMV_RF_PROP_PBOC			0x0010		/**< 1:支持接触PBOC,0:不支持*/
#define EMV_RF_PROP_OFFLINE_ONLY	0x0008		/**< 1:读写器仅支持脱机
											    		0:读写器具有联机能力*/
#define EMV_RF_PROP_ONLINEPIN		0x0004		/**< 1:支持联机PIN,0:不支持*/
#define EMV_RF_PROP_SIGNATURE		0x0002		/**< 1:支持签名,0:不支持*/
#define EMV_RF_PROP_ODA			0x0001	//第1字节第1位支持ODA

#define EMV_RF_PROP_ONLINE			0x0180		/**< 1:要求联机密文,0:不要求*/			
#define EMV_RF_PROP_CVM			0x0140		/**< 1:要求CVM,0:不要求*/
#define EMV_RF_TM_CDCVM			0x0240		/**< 1:支持CDCVM,0:不支持*/
#define EMV_RF_PROP_FDDA        0x80000000  /**< 终端支持01版本的FDDA **/
#define EMV_RF_PROP_ISSUSER_SCRIPT    0x0280  // 发卡行脚本是否支持 字节3位8
#define EMV_RF_PROP_MOBILE    0x0240  //mobile 

#define UN_RF_PROP_ONLINEPIN		0xFFFB		/**< 1:支持联机PIN,0:不支持*/
#define UN_RF_PROP_SIGNATURE		0xFFFD		/**< 1:支持签名,0:不支持*/


/*9F6C 卡返回的卡片交易属性*/
#define VISA_CARD_CASH_DECLIEN			0x0004	/**< VISA - (无返回应用用途控制或现金应用无效，则现金交易切换到其他界面)Switch Interface for Cash Transactions(Application Usage Control - Cash Transactions),见VISA 'Req 5.76'*/
#define VISA_CARD_CASHBACK_DECLIEN		0x0002	/**< VISA - Switch Interface for Cashback Transactions(Application Usage Control - Cashback Transactions'*/
#define EMV_CARD_PROP_ONLINEPIN			0x0080	/**< 需要联机PIN*/
#define EMV_CARD_PROP_SIANATURE			0x0040	/**< 需要签名*/
#define EMV_CARD_PROP_DAFAIL_ONLINE		0x0020	/**< 如果脱机数据认证失败而且可联机则要求联机*/
#define EMV_CARD_PROP_DAFAIL_PBOCTERMIN	0x0010	/**< 如果脱机数据认证失败而且终端支持PBOC则终止*/
#define EMV_CARD_PROP_EXPIR_ONLINE		0x0008	/**< 如果应用过期，则交易联机*/
#define EMV_CARD_PROP_CDCVM				0x0180		/**< CDCVM是否执行， 1-CDCVM已执行，0-CDCVM未执行*/
#define EMV_CARD_PROP_ISSUSER_SCRIPT	0x0140		// 发卡行脚本是否支持，字节2 位7

YESORNO GetICTransPropIsSet(int nMask);
YESORNO GetTmTransPropIsSet(int nMask);

/*	9F10中返回的交易标识*/
#define	IAD_AAC(x )				(( *((x) + 4) & 0x30) == 0x00 )
#define	IAD_TC(x )				(( *((x) + 4) & 0x30) == 0x10 )
#define	IAD_ARQC(x )			(( *((x) + 4) & 0x30) == 0x20 )
#define 	IAD_FCHECK(x)			( *((x) + 5) & 0x20) 		/*卡片频度检查超限位:
														电子现金单笔交易限额
														电子现金余额不足
														授权金额加上 CTTA 大于 CTTAUL
														余额小于电子现金重置阈值*/

#define ISS_IDD_ECBAL			0x01	/**< 电子现金余额*/
#define ISS_IDD_CTTA			0x02	/**< 累积交易总额*/
#define ISS_IDD_ECBAL_CTTA		0x03	/**< 电子现金余额和CTTA*/
#define ISS_IDD_CTTA_CTTAL		0x04	/**< CTTA和CTTAL*/
#define ISS_IDD_OFFBAL			0x05	/**< 可用脱机消费金额*/

/**<Entry Point Pre-Processing Indicators*/
typedef struct {
	char cStatusCheck;				/**< Status Check Requested */
	char bIsRf;						/**< Contactless Application Not Allowed */
	char bAmtZero;					/**< Zero Amount*/
	char bCVMExceeded;				/**< Reader CVM Required Limit Exceeded */
	char bFLExceeded;				/**< Reader Contactless Floor Limit Exceeded*/
	char sTTQ[5+1];					/**< Copy of TTQ*/
}ST_PreIndicator;

/******************************************************************************
 *  	函数名称:	RF_Sel_App: 
 *	函数介绍:	qpboc应用选择
 *	入口参数:	char cTransType,	交易类型
 					int nEmvTransSerial,	交易序列号
 *	出口参数:     char *pcTransMode	交易模式
 * 	返回值  :		SUCC
 					FAIL
 ******************************************************************************/
extern int RF_Sel_App(char cTransType,int nEmvTransSerial,char *pcTransMode);

/******************************************************************************
 *  	函数名称:	RF_Sel_AppEx: 
 *	函数介绍:	非接应用选择
 *	入口参数:	char cTransType,	交易类型
 					int nEmvTransSerial,	交易序列号
 *	出口参数:     char *pcTransMode	交易模式
 * 	返回值  :		SUCC
 					FAIL
 ******************************************************************************/
extern int RF_Sel_AppEx(char cTransType,int nEmvTransSerial,char *pcTransMode);

int RF_EMV_vDealKernelID(char *cpAid,int nAidLen,uchar *ucpKernelId);
int EMV_iSetCurrentKid(int iKernelId);
int EMV_iSendOutInformation(int iFlag, OUTCOME_ERR_TYPE eErrorType,int iKernelId);

int ParseIssData(void);
int Rf_Amount_Check();
/*	Func:	交易成功返回交易类型*/
int RF_Init_App(char *pcTransMode);
int RF_CheckExceptionFile();
int RF_deactive( int nTime );
int Rf_fail_Proc(STEMVPROC *stProc);
/******************************************************************************
 *  	函数名称:	Rf_Msd: 
 *	函数介绍:	
 *	入口参数:	
 *	出口参数:     
 * 	返回值  :		
 ******************************************************************************/
int Rf_Msd(int *nEmvRes,char *cTransMode);
/******************************************************************************
 *  	函数名称:	RF_QPBOC_Trans: 
 *	函数介绍:	
 *	入口参数:	
 *	出口参数:     
 * 	返回值  :		
 ******************************************************************************/
int Rf_Qpboc(STEMVPROC *stProc);

//PAYPASS ADF流程
int PayPass_FinalSelect(ST_RF_ICCAID *stICCAID,STEMVPROC *stProc);
#endif

