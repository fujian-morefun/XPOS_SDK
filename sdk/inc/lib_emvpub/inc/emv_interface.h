#ifndef __EMV_INTERFACE__
#define __EMV_INTERFACE__

#include "define.h"
#include "pub/pub.h"
#include "ex_crypto.h"

#ifdef __cplusplus
extern "C"{
#endif

	//#pragma pack(1)

	/**< ---------------------------------------------------------------------------------------------------*/
	/*通用宏定义*/
	#define OFFLINE_PIN_NOMAL		0x03	/**<提示输入脱机PIN*/
	#define OFFLINE_PIN_AGAIN		0x02	/**<提示再次输入脱机PIN*/
	#define OFFLINE_PIN_LAST		0x01	/**<最后一次输入脱机PIN*/
	#define	ONLINE_PIN			0x00

	#define MAXLEN_AID 			16
	#define MAXLEN_DOL 			(252 + 4) 
	#define MAXLEN_MODULUS 		248
#ifdef WIN32
	#define MAXLEN_FILENAME		256
#else
	#define MAXLEN_FILENAME		32
#endif
	/**< ---------------------------------------------------------------------------------------------------*/



	/**< ---------------------------------------------------------------------------------------------------*/
	/**< ICS参数*/
	/**< ICS结构cKernelS内核类型参数*/
	#define KERNEL_QPBOC		0x01		/*QPBOC*/
	#define KERNEL_QUICS		0x02		//QUICS
	#define KERNEL_DISCOVER		0x04		
	#define KERNEL_VISA			0x08		
	#define KERNEL_MASTER		0x10		
	#define KERNEL_JCB 			0x20		
	#define KERNEL_AMEX			0x40		
	#define KERNEL_RUPAY		0x80		
	/**< ICS结构cPackType打包类型参数*/
	#define EMV_PACK_ONLINE (1)
	#define EMV_PACK_BATCH	(2)
	typedef struct{
		/**<应用选择*/
		YESORNO bPSE;				/**<支持PSE应用选择方法*/
		YESORNO bCardHConfirm;		/**<支持持卡人确认*/
		YESORNO bPriorDisp;			/**<有自定义的优先显示顺序*/
		YESORNO bPaticalMatch;		/**<支持AID部分匹配*/
		YESORNO bMultiLangu;		/**<支持多语言*/
		YESORNO bPubChar;			/**<支持公共字符集*/	
		/**<可选内核配置*/
		YESORNO bConfigureKenal;	/**<支持可选内核配置*/
		char cAmtStandard;			/**<金额选择标准(CVM列表)*/		
		/**<数据认证*/
		int nCAPKMAXLen;			/**<CAPK最大长度*/
		char cCAPKExpoMode;		/**<支持的公钥指数*/
		YESORNO bCheckTCRecycle;	/**<检查发卡行公钥证书的回收*/
		/**<回收格式?*/
		YESORNO bDDOL;				/**<包括默认DDOL*/
		YESORNO bOperAct;			/**<CA公钥装载失败时操作员行为是否要求*/
		YESORNO bCheckSum;		/**<CA公钥校验通过校验和*/
		/**<如果不通过CA公钥校验和校验,使用的校验方法*/
		/**<持卡人认证*/
		YESORNO bByPassPin;			/**<支持绕过pin输入*/
		/**<当选择绕过pin输入,所有其他pin输入方法是否也被认为被绕过*/
		YESORNO bGetPinTime;				/**<GET DATA 取PIN重试次数*/
		YESORNO bCVMFail;			/**<支持CVM失败*/
		YESORNO bAMTBeforeCVM;	/**<CVM处理前是否知道金额*/
		/**<终端风险管理*/
		YESORNO bFloorLimit;			/**<最低限额检查*/
		YESORNO bRanSel;			/**<随机交易选择*/
		YESORNO bVelocityCheck;		/**<频度检查*/
		YESORNO bTransLog;			/**<交易日志*/
		YESORNO bExceptionFile;		/**<异常文件*/
		YESORNO bBaseAIP;			/**<风险管理是否基于AIP*/
		/**<终端行为分析*/
		YESORNO bTA;				/**<支持终端行为代码*/
		YESORNO bTAEmpty;			/**<终端行为代码是否为空*/
		/**<仅脱机能力的终端支持*/
		YESORNO bDACBefoer1stGAC;	/**<是否缺省行为代码在第一个Genarate AC之前*/
		YESORNO bDACAfter1stGAC;	/**<是否缺省行为代码在第一个Genarate AC之后*/	
		/**<仅联机能力的终端支持*/
		YESORNO bNoDACtoAAC;		/**<当不能联机时是否跳过缺省行为代码,直接请求AAC*/
		YESORNO bDetectCDAFailBeforeTAA;/**<终端行为分析前是否有能力探测到CDA失败*/
		/**<支持CDA的终端*/
		YESORNO bCDA1stGACforARQC;	/**<在第一个GAC请求ARQC时是否请求CDA*/
		YESORNO bCDA2ndGACforTC;	/**<在第二个GAC请求TC时是否请求CDA*/
		/**<完成处理*/
		YESORNO bForceOnline;		/**<交易强制联机能力*/
		YESORNO bForceAccept;		/**<交易强制接受能力*/
		YESORNO bAdvices;			/**<支持通知*/
		YESORNO bIISVoiceRef;		/**<支持发卡行发起的语言参考*/
		YESORNO bBatchData;			/**<支持批数据获取*/
		YESORNO bOnlineData;		/**<终端是否支持联机数据获取*/
		YESORNO bDefaultTDOL;		/**<是否支持一个缺省的TDOL*/
		/**<异常处理*/
		char szFallBackEntryModo[2];	/**<如果IC不能读取,退转到磁条交易时的POS输入模式*/
		/**<其他*/
		YESORNO bPinPad;			/**<终端是否外接密码键盘*/
		YESORNO bAMTPinSameKeypad;/**<金额和pin是否在同一个键盘输入*/
		YESORNO bCombinedReader;	/**<是否为IC磁条符合读卡器(不是)*/
		YESORNO bSelAccount;		/**<是否支持账户类型选择*/
		YESORNO bISSScriptGreater128;/**<发卡行脚本大于128字节*/
		int nIssScriptMaxLen;			/**<发卡行脚本的最大长度(该字段在脚本长度大于128字节为真时有效)*/
		YESORNO bReadDetail;		/**<是否读交易明细(仅PBOC ICS有该选项)*/
		YESORNO bInteralDataMana;	/**<支持内部日期管理*/
		char cKernelS;				/**<(TERM)测试项目*/
		char cIsApprove;			/**<认证开关>**/
		char cPackType;				/**<(TERM)报文类型*/
		/**< SM算法*/
		YESORNO bSm;
		YESORNO bOda;
		YESORNO bASRPD;				//Application Selection Registered Proprietary Data应用选择注册专有数据
		/**< 其他界面*/
		YESORNO bDualInterface;
	}STICS;
	/**<设置ICS参数*/
	LIB_EXPORT extern int Emv_SetICS(STICS stTermIcs);
	LIB_EXPORT extern int Emv_GetICS(STICS *stTermIcs);
	LIB_EXPORT extern int Emv_SetICSRam(STICS *stTermIcs);

	/**< -----------------------------------------------------------------------------------------------------*/




	/**< -----------------------------------------------------------------------------------------------------*/
	/**<终端参数*/
	/**<终端参数ST_TERMPARA结构EntryMode输入方式参数*/
	#define POSENTMODE_MAG		0x02
	#define POSENTMODE_FALLBACK 0x04
	#define POSENTMODE_IC		0x05
	#define POSENTMODE_QPBOC	0x07
	#define	POSENTMODE_RF_MS	0x91
	#define POSENTMODE_RF		0x98
	/**<终端参数*/
	typedef struct {
		char szAcqID_n_9F01[6];				/**<(TERM)收单行标识*/	
		char szAddTermCap_b_9F40[5];		/**<(TERM)附加终端性能*/	
		char szMerCateCode_n_9F15[2];		/**<(TERM)商户分类码*/
		char szMerID_ans_9F16[15];			/**<(TERM)商户标识*/
		char szMerNameLoc_ans[40];			/**<(TERM)商户名称和位置*/
		//char cMessageType_n;				/**<(TERM)报文类别*/
		char cEntryMode_n_9F39;				/**<(TERM)销售点（POS）输入方式*/
		char szTermCap_b_9F33[3];			/**<(TERM)终端性能*/
		char szTermCountryCode_b_9F1A[2];	/**<(TERM)终端国家代码*/
		char szTermId_an_9F1C[8];			/**<(TERM)终端号*/
		char cTypeTerm_n_9F35;				/**<(TERM)终端类型*/
		char szCurCode_n_5F2A[2];			/**<(TERM)交易货币代码*/
		char cCurExp_n_5F36;				/**<(TERM)交易货币指数*/
		char szRefCurrCode_n_9F3C[2];		/**<(TERM)交易参考货币代码*/
		char cRefCurrExp_n_9F3D;			/**<(TERM)交易参考货币指数*/
		char szIFD_an_9F1E[8];				/**<(TERM)接口设备（IFD）序列号*/
		char szTDOL_b[252];					/**<缺省交易证书数据对象列表*/
		char cTDOLLen;
		/**< 电子现金qPboc参数*/
		char cDF19Check;				/**< (EC)电子现金指示器*/
		char szTransProp_9F66[4+1];			/**< (RF TERM) 终端交易属性*/
		char c9F1BCheck;
		char cRfStatusCheck;				/**< (RF TERM) 非接触终端状态检查*/
		/**< 金额0是否支持*/
		char bZeroAmtAllowed;
	}ST_TERMPARA;
	/**<设置终端参数*/
	LIB_EXPORT extern int Emv_SetTerminalParam(const ST_TERMPARA *stTermPara);
	LIB_EXPORT extern int Emv_GetTerminalParam(ST_TERMPARA *stTermPara);
	LIB_EXPORT extern int Emv_SetTerminalParamRam(ST_TERMPARA *stTermPara);
	LIB_EXPORT extern int Emv_GetTerminalParam_file(ST_TERMPARA *stTermPara);
	/**< -----------------------------------------------------------------------------------------------------*/





	/**< -----------------------------------------------------------------------------------------------*/
	/**<结构体STEMVPROC参数cTransType交易类型*/
#define EMV_GOODS_SERVICES 		0x00
#define EMV_CASH           		0x01
#define EMV_CASHBACK       		0x09
#define EMV_INQUIRY        		0x31
#define EMV_TRANFER        		0x40
#define EMV_ADMIN          		0x66		/**<?自定义*/
#define EMV_CASH_DISBUERSE		0x17		//现金支出
#define EMV_CASHDEPOSIT    		0x21
#define VISA_REFUND    			0x20
#define RUPAY_MONEY_ADD			0x28		//圈存
#define RUPAY_LEGACY_MONEY_ADD    0x33       //Legacy圈存
#define RUPAY_VOID				0x34		//撤销
#define EMV_PAYMENT        		0x50
	/**< 银联或银行交易类型*/
#define EMV_SALE				EMV_GOODS_SERVICES	/**< 消费*/
#define PBOC_READLOG      		0x0A		/**< PBOC读LOG*/
#define UPLOAD_READLOG      	0x0B		/**< 圈存读LOG*/
#define EMV_QPBOC_SIMPLE		0x20		/**< qpboc简易流程*/
#define EMV_SIMPLE_PROC			0x99		/**< 简易流程*/
#define EMV_PREAUTH				0x03		/**< 预授权*/
#define PBOC_EC_BALANCE			EMV_INQUIRY		/**< 电子现金余额查询*/
	/**< 电子现金*/
#define EC_TRANS				EMV_GOODS_SERVICES
#define EC_INQUIRE				0x67		/**< 电子现金余额查询 ?自定义*/
#define EC_BINDLOAD				0x60		/*电子现金指定账户圈存*/
#define EC_NOBINDLOAD			0x62		/*电子现金非指定账户圈存*/
#define EC_CASHLOAD				0x63		/*电子现金现金圈存*/
#define EC_AMOUNT				0x64
#define EC_UPLOAD				0x65
#define EC_CASHLOAD_VOID		0x17		/*电子现金现金圈存撤消*/

	/*结构体STEMVPROC,RF应用选择后,交易方式*/
#define MODE_RF_TYPE_UNKNOW		0x00
#define	MODE_RF_TYPE_PBOC		0x01
#define MODE_RF_TYPE_VCPS		0x02
#define MODE_RF_TYPE_QPBOC		MODE_RF_TYPE_VCPS
#define MODE_RF_TYPE_MSD		0x04
#define MODE_TYPE_EC			0x10		/*电子现金交易*/
#define	MODE_TYPE_RF			0x20		/*非接触*/
#define	MODE_TYPE_DPAS			0x30		/*非接触d-pas*/
#define	MODE_TYPE_AMEX		    0x40		/*非接触AMEX*/

	
//API 返回值
#define UNSUPPORT	(-6)
#define TERMINATE	(-7)
#define GOTOCONTACT (-8)
#define GOTOOTHER	(-9)
#define	GOTOUPCARD	(-10)
#define GOTO_TRYAGAIN		(-11)		//重新挥卡
#define GOTO_CDV_TRYAGAIN	(-12)		//移动设备重新挥卡
#define GOTOOTHERCARD	(-16)		
#define EMV_RES_FALLBACK		(-4)		/**< fallback*/
/**<结构体STEMVPROC数据nEmvRet的值*/
#define EMV_RES_UNKNOW			(-3)		/**< 未知结果*/
#define EMV_RES_AAR				(-2)		/**< */
#define EMV_RES_REFUSE			(-1)		/**< 交易拒绝*/
#define EMV_RES_ACCEPT			(0)			/**< 交易接受*/
#define EMV_RES_REQ_ONLINE		(1)			/**< 请求联机*/
#define EMV_RES_2GACAAC			(2)			/**< 第二次GAC请求AAC*/
#define EMV_RES_ACCEPT_DELAY_AUTH (3)      //AE的延时认证

	/**<结构体STEMVPROC数据nOnlineRes的值*/
#define EMV_ONLINE_SUCC			(0)			/**< 联机成功*/
#define EMV_ONLINE_FAIL			(-1)		/**< 联机失败*/

	/**< STEMVPROC 结构体eInputAMT参数*/
	typedef enum {
		AMT_NO = 0,				/**< 不输入金额*/
		AMT_BEFORESEL,			/**< 应用选择前输入金额*/
		AMT_AFTERSEL			/**< 应用选择后输入金额*/
	}E_INPUTAMT;

	/*	EMV交易选项结构体*/
	typedef struct {
		unsigned char cTransType;  		/**<交易类型,in*/
		char cTransMode;		/**<交易模式out*/
		char *pszEmvData;		/**<EMV数据*/
		int nEmvDataLen;		/**<EMV数据长度*/
		int nEmvTransSerial;	/**<交易序号,in*/
		char bForceOnline;		/**<交易强制联机in*/
		E_INPUTAMT eInputAMT;	/**<是否在应用选择前输入金额*/
		char szPin[8+1];      	/**<联机pin,out*/
		YESORNO bSignatrue;		/**<签名out*/	
		YESORNO bAdvice;		/**<通知out*/
		int nCvmFlag;			/*内核返回CVM方法*/
		int nEmvRet;			/**<返回结果out*/
		int nOnlineRes;			/**<联机结果in*/
		char *pszField55; 		/**<55域数据in*/
		int nField55Len;		/**<数据长度in*/
		char szResponse[2+1];	/**<授权响应码in*/
		char *pszOtherTlvParam;	//其他参数
		int iOtherTlvParamLen;	
	}STEMVPROC;
	/**< -----------------------------------------------------------------------------------------------*/





	/**< -----------------------------------------------------------------------------------------------*/
	/**<AID结构体,结构体长度为400字节,目前预留42字节*/
	typedef struct {
		char szAID_b_9F06[MAXLEN_AID];		/**<(AID)应用标识AID参数(长度5-16)*/
		char cAIDLen;						/**<AID长度*/							
		char szLable_50[MAXLEN_AID];        /**< 应用标签50(ICC), ans, 1-16 bytes*/
		char cLableLen;						
		char szPreName_9F12[MAXLEN_AID];	/**< 应用优先名 */
		char cPreNameLen;					
		unsigned char cPriority_87; 		/**< 应用优先权标识符*/
		char cASI_b_DF01;					/**<(AID)应用选择指示符,指明终端是否支持AID部分匹配方式0x00:部分匹配 0x01完全匹配*/
		char szAppVer_b_9F09[2];			/**<(AID)应用版本号(9F08?9F09?)*/
		char szTACDefault_b_DF11[5];		/**<(AID)终端行为代码－默认*/
		char szTACRefuse_b_DF13[5];			/**<(AID)终端行为代码－拒绝*/
		char szTACOnline_b_DF12[5];			/**<(AID)终端行为代码－联机*/
		char szFloorLimit_b_9F1B[4];		/**<(AID)终端最低限额*/
		char szRanhold_b_DF15[4];			/**<(AID)偏置随机选择的阈值*/
		char cRanMaxPer_b_DF16;				/**<(AID)偏置随机选择的最大目标百分数*/
		char cRanTarPer_b_DF17;				/**<(AID)随机选择的目标百分数*/
		char cOnlinePinCap_b_DF18;			/**<(AID)终端联机pin能力*/
		char szDDOL_b_DF14[252];			/**<(AID)缺省动态数据认证数据对象列表(变长)*/
		char cDDOLLen;						/**< DDOL长度*/
		char sEcLimit_9F7B[6];				/**< (EC)电子现金终端交易限额*/
		char sRf_OfflineLimit_DF19[6];		/**< (RF TERM) 非接脱机最低限额*/
		char sRF_TxnLimit_DF20[6];			/**< (RF TERM) 非接交易限额*/
		char sRf_CVMLimit_DF21[6];			/**< (RF TERM) 非接CVM限额*/
#ifdef AUTO_APPROVE
		char szCurCode_aid_5F2A[2];			/**<(TERM)交易货币代码*/
		char c5F36_len;
		char cCurExp_aid_5F36;				/**<(TERM)交易货币指数*/
		char c9F3C_len;				 
		char szRefCurrCode_aid_9F3C[2];		/**<(TERM)交易参考货币代码*/
		char c9F3D_len;
		char cRefCurrExp_aid_9F3D;			/**<(TERM)交易参考货币指数*/
		char c9F1D_len;
		char cRiskManage_aid_9F1D;			/**<(TERM)终端风险管理数据*/
		char c9F01len;
		char szAcqID_n_9F01[6];				/**<(TERM)收单行标识*/
		char c9F15len;
		char szMerCateCode_n_9F15[2];		/**<(TERM)商户分类码*/
		char c9F16len;
		char szMerID_ans_9F16[15];			/**<(TERM)商户标识*/
		char c9F4Elen;
		char szMerNameLoc_ans_9F4E[40];		/**<(TERM)商户名称和位置*/
		char c9F1Clen;
		char szTermId_an_9F1C[8];			/**<(TERM)终端号*/
		char cTDOLLen;
		char szTDOL_b[50];					/**<缺省交易证书数据对象列表对应 DF8102*/
		//Transaction Reference Currency Conversion 参考货币转换因子 DF8101暂不保存，目前未用到
		char cResv[15];	
#else
		char szCurCode_aid_5F2A[2];			/**<(TERM)交易货币代码*/
		char c5F36_len;
		char cCurExp_aid_5F36;				/**<(TERM)交易货币指数*/
		char c9F3C_len;				 
		char szRefCurrCode_aid_9F3C[2];		/**<(TERM)交易参考货币代码*/
		char c9F3D_len;
		char cRefCurrExp_aid_9F3D;			/**<(TERM)交易参考货币指数*/
		char c9F1D_len;
		char cRiskManage_aid_9F1D;			/**<(TERM)终端风险管理数据*/
		char cResv[31];	
#endif
	}ST_TERMAID;

#define TERMAID_SIZE	(sizeof(ST_TERMAID))

	typedef struct{
		int adicount;//aid数
		char* st_aidlist;//aid缓存数组
		int matchi[10];//匹配索引
		int nmatch;//匹配个数
		int nindex;//最终选择AID
	}ST_TERMAID_LIST;
	LIB_EXPORT int read_aid_list(ST_TERMAID_LIST *stadilist);
	LIB_EXPORT void FreeAidList();
	LIB_EXPORT ST_TERMAID_LIST * get_aid_list(void);
	/**<AID接口*/
	LIB_EXPORT extern int Init_AID(void);
	LIB_EXPORT extern int EMV_GetAid(const char *pszAID, int nLen, ST_TERMAID *stAID,int *nRecNum);
	LIB_EXPORT extern int Emv_AddAID(ST_TERMAID *stAID,YESORNO cCoverFlag);
	LIB_EXPORT extern void Emv_GetAIDNum(int *nNum);
	LIB_EXPORT extern int EMV_GetAidByIndex(ST_TERMAID *stAID,int nRecNum);
	LIB_EXPORT extern int Emv_DelAID(const char *pszAID, int nLen);
	/**< -----------------------------------------------------------------------------------------------*/




	/**< -----------------------------------------------------------------------------------------------*/
	/**<公钥参数CAPK结构体,结构体长度为228字节*/
	typedef struct {
		char szRID_b_9F06[5];				/**<注册的应用提供者标识*/
		char cCAPKIndex_b_9F22;				/**<(CAPK)认证中心公钥索引*/
		char szCAPKExpire_n_DF05[4];		/**<(CAPK)认证中心公钥有效期*/
		char cCAPKHashFlag_b_DF06;			/**<(CAPK)认证中心公钥哈希算法标识*/
		char cCAPKFlag_b_DF07;				/**<(CAPK)认证中心公钥算法标识*/
		char szCAPKMod_b_DF02[MAXLEN_MODULUS];/**<(CAPK)认证中心模(最大为248)*/
		uchar cCAPKModLen;					/**<公钥模长*/
		char szCAPKExponent_b_DF04[3];		/**<(CAPK)认证中心公钥指数(长度1或3)*/
		uchar cCapkExpLen;
		char szCAPKCheckSum_b_DF03[20];		/**<(CAPK)认证中心公钥校验和(变长)*/
		char cCheckSumLen;	
#if AUTO_APPROVE
		char szCAPKCaindex_DF08[3];			/*认证中心公钥序列号*/
		char cDf08_len;
#endif
	}ST_CAPK;
	/**<公钥参数CAPK接口*/
	LIB_EXPORT extern int Init_CAPK(void);
	LIB_EXPORT extern int EMV_GetCAPK(const char *pszRID, char *cIndex,ST_CAPK *stCAPK,int *nRecNum);
	LIB_EXPORT extern int Emv_AddCAPK(ST_CAPK*stCAPK,YESORNO cCoverFlag);
	LIB_EXPORT extern void Emv_GetCAPKNum(int *nNum);
	LIB_EXPORT extern int EMV_GetCAPKByIndex(ST_CAPK *stCapk,int nRecNum);
	LIB_EXPORT extern int Emv_DelCAPK(const char *pszRID, int nLen, char *cCAPKIndex);
	LIB_EXPORT extern int VerifyCAPK(const ST_CAPK *stCAPK);
	/**< -----------------------------------------------------------------------------------------------*/





	/**< -----------------------------------------------------------------------------------------------*/
	/**< 文件存储路径*/
	typedef struct {
		char szFile_Terminal[MAXLEN_FILENAME];			/*终端参数文件名*/
		char szFile_Ics[MAXLEN_FILENAME];				/**<ICS文件名*/
		char szFile_CAPK[MAXLEN_FILENAME];				/*公钥文件名*/
		char szFile_AID[MAXLEN_FILENAME];				/*AID文件名*/
		char szFile_Card_BlackList[MAXLEN_FILENAME];	/*卡黑名单文件名*/
		char szFile_Cert_BlackList[MAXLEN_FILENAME];	/*证书黑名单文件名*/
		char szFile_Log[MAXLEN_FILENAME];				/*LOG文件名*/
		char szFile_RfFail[MAXLEN_FILENAME];			/*闪卡记录文件*/
		char szFile_BinA[MAXLEN_FILENAME];				/*BIN A列表*/
		char szFile_BinB[MAXLEN_FILENAME];				/*BIN B列表*/
		char szFile_BinC[MAXLEN_FILENAME];				/*免密卡BIN C中黑名单*/
	}STEMV_FILE;
	/**< 设置文件存储路径*/
	LIB_EXPORT extern int EMV_SetFileName(STEMV_FILE *stEmvFileName);
	/**< -----------------------------------------------------------------------------------------------*/


	/**< -----------------------------------------------------------------------------------------------*/
	/**<卡黑名单结构*/
	typedef struct
	{
		char cLen;			/**<卡号长度*/
		char szCardNo[10];	/**<卡号*/
		char cIndex;		/**<索引*/
		char cResv;
	}STBlackCard;
	typedef struct{
		int blkcount;//aid数
		char* st_blklist;//aid缓存数组
	}ST_BLC_LIST;
	/**<卡黑名单接口*/
	LIB_EXPORT extern int Init_CardBL(void);
	LIB_EXPORT extern int EMV_FindCardBL(STBlackCard stBlackCard,int ntype);//ntype为0表示存储判断 否则为黑名单判断
	LIB_EXPORT extern int Emv_AddCardBL(STBlackCard stBlackCard,YESORNO cCoverFlag);
	LIB_EXPORT extern int Emv_DelCardBL(STBlackCard stBlackCard);
	/**< --------------------------------------------------------------------------------------------------*/





	/**< --------------------------------------------------------------------------------------------------*/
	/**<发卡行证书黑名单结构体*/
	typedef struct
	{
		char szRID[5];		
		char cIndex;			/**<公钥索引*/
		char szSerialNum[3];	/**<证书序号*/
		char cResv;
	}STBlackCert;
	/**<证书黑名单参数*/
	LIB_EXPORT extern int Init_CertBL(void);
	LIB_EXPORT extern int EMV_FindCertBL(STBlackCert stBlackCert);
	LIB_EXPORT extern int Emv_AddCertBL(STBlackCert stBlackCert,YESORNO cCoverFlag);
	LIB_EXPORT extern int Emv_DelCertBL(STBlackCert stBlackCert);
	/**< ---------------------------------------------------------------------------------------------------*/




	/**< ---------------------------------------------------------------------------------------------------*/
	/**<交易界面函数指针*/
	/*	AID侯选列表结构体,进行侯选列表选择时用到,参加ADF目录入口格式*/
	typedef struct {
		unsigned char szAID_4F[16+1];			/**<AID	应用标识符*/
		int nAIDLen;							
		unsigned char szLable_50[16+1];         /**< 应用标签50(ICC), ans, 1-16 bytes*/
		int nLableLen;						
		unsigned char szPreName_9F12[16+1];		/**< 应用优先名 */
		int nPreNameLen;					
		unsigned char cPriority_87; 		    /**< 应用优先权标识符*/
		int  nIndex;							/**<在终端AID列表中的索引*/
		int nKernelId;							//KernelId
		uchar ucExtendSelect[11+1];				//扩展应用选择
		int nExtendSelectLen;					//最大11字节
		unsigned char szResv[3];				/**<*/
	}ST_ICCAID;

	typedef struct {
		int (*InputAmount)(char *,char);													/**<输入金额界面函数指针*/
		int (*InputOfflinePin)( XM_RSA_PUBLIC_KEY *pk, int nMethod,char cMsgType,char *sw);	/**<输入密码界面函数指针*/	
		int (*InputOnlinePin)(char *,char *);												/*输入密码界面函数指针*/	
		int (*SelectApp)(ST_ICCAID stICCAID[],int nAIDNum,int *nChoice);					/**<应用选择界面函数指针*/
		int (*SelectAccount)(int *nChoice);													/**<账户类型选择界面函数指针*/
		int (*ConfirmCert)(char *pszCertNO,char cCertType);
		int (*DispCard)(char *);															/**<显示卡号函数指针*/
		int (*DispWarn)(char *,...);														/**<显示警告界面函数指针*/
		void (*DispMesg)(char *,...);
		int (*IssVoiceRef)(char *);															/**<发卡行语音参考*/
		int (*SelectEC)(void);																/**< 是否使用电子现金*/
		int (*RfGetCard)(int);																/**< 非接触交易提示用户拿卡*/
		int (*CardStatus)(void);
		int (*InputPin)(char *psCardNo,char *psAmt,char cMsgType,char *psPin);
		int (*GetOnlinePin)(char *psCardNo,char *psAmt,char *psCiphertext);
		int (*GetAmount)(char *);
		int (*Beep)(int nMillisecond);
		int (*ShankaDel)(int);
		int (*SelectLan)(char *);					/**<语言选择界面函数指针*/
		int (*DispOffPin)(int);				        /**<脱机PIN结果提示界面*/
	}ST_UI;
	/**<IC卡函数指针*/
	typedef struct 
	{
		int (*PowerUp)(void) ;											/**<上电函数指针*/
		int (*PowerDown)(void);											/**<下电函数指针*/
		int (*CommRW)(const unsigned char *,int,unsigned char *,int *);	/*读写函数指针*/
	}STCOMM ;

	/**内核交互API回调列表*/
	typedef struct
	{
		void (*EXE_vSendOut)(unsigned char cIns,  int uiDataLen, char *pauData);		//内核输出		
		void (*EXE_vObtain)(unsigned char cIns,  int uiDataLen, char *pauData);		//内核输入 
	}ST_EMV_EXPAND_INTERFACE;

	/**< 设置函数指针接口*/
	LIB_EXPORT extern int EMV_SetFunP(ST_UI *stEMVUI,STCOMM *stEMVICComm,ST_EMV_EXPAND_INTERFACE*stInterface);
	/**< ----------------------------------------------------------------------------------------------------*/



	/**< --------------------------------------------------------------------------------------------------*/
	/*log及bug定位*/
	typedef struct {
		int tick1[10];
		int count;
	}ST_TICK;
	LIB_EXPORT void init_tick(void);
	LIB_EXPORT void get_tick(ST_TICK*tickt);
	LIB_EXPORT void set_tick(int count,int ntype);
	LIB_EXPORT int get_count(void);
	/**<log文件*/
	LIB_EXPORT extern int Init_TransLog(void);
	/**< --------------------------------------------------------------------------------------------------*/



	/**< --------------------------------------------------------------------------------------------------*/
	/**< 获取EMV数据*/
	LIB_EXPORT extern int GetEmvData(char *pszTag,char *pszData,int *nDataLen);
	LIB_EXPORT extern int PackEmvData(char * packData, char * psTag,int nFlag,int * pnLen);
	
	/*************************************************************************************
	Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
	Author:wuxp
	Functions:Match error code
	Input :  iErrcode:Error code
	Output : Nothing
	return: 0: no Match
	1: Match
	*************************************************************************************/
	LIB_EXPORT unsigned int Emv_ISErrCode(unsigned int iErrcode);

	/*************************************************************************************
	Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
	Author:wuxp
	Functions:Get error information
	Input :  pErrMSG:buf
	Output : Nothing
	return: FAIL/SUCC
	*************************************************************************************/
	LIB_EXPORT int EMV_Get_ErrMSG(char* pErrMSG);

	/**< TVR TSI*/
	LIB_EXPORT extern YESORNO GetTVRIsSet(int nMask);
	LIB_EXPORT extern YESORNO GetTSIIsSet(int nMask);
	/**< --------------------------------------------------------------------------------------------------*/


	/**< --------------------------------------------------------------------------------------------------*/
	/*非接内核通用宏定义及API接口*/
	//非接移卡定义宏
	#define RF_GETCARD_POWERDOWN	1
	#define RF_GETCARD_REMOVE		2

	/* 内核类型 / Kernel ID */	
	#define  EMV_KERNELID_DEFAULT          0x00 //默认初始值
	#define  EMV_KERNELID_MASTER           0x02 //非接EMV kernel2 / Master Card 
	#define  EMV_KERNELID_VISA             0x03 //非接EMV kernel3 / VISA
	#define  EMV_KERNELID_AMEX				0x04 //非接EMV kernel4 / AMEX
	#define  EMV_KERNELID_JCB				0x05 //非接EMV kernel5 / JCB 
	#define  EMV_KERNELID_DISCOVER			0x06 //非接EMV kernel6 / DISCOVER	 
	#define  EMV_KERNELID_UNIONPAY			0x07 //非接EMV kernel7 / UNIONPAY	
	//#define  EMV_KERNELID_RUPAY			0x08 //非接EMV RUPAY
	#define  EMV_KERNELID_RUPAY				0x0D //非接EMV RUPAY--规范体现
	/*	AID侯选列表结构体*/
	typedef struct {
		unsigned char szAID_4F[16+1];			/**<AID	应用标识符*/
		int nAIDLen;							
		int nKernelId;							//KernelId
		unsigned char cPriority_87; 		    /**< 应用优先权标识符*/
		uchar ucExtendSelect[11+1];				//扩展应用选择
		int nExtendSelectLen;					//最大11字节
		int nIndex;				/**<在终端AID列表中的索引*/
	}ST_RF_ICCAID;
	
	/*量产外卡API接口*/
	/* AID匹配结构体*/
	typedef struct
	{
		uchar ucAid[MAXLEN_AID];	// AID
		uchar ucAidLen;				// AID长度
		uchar ucPartSelect;			// 部分匹配标识 0x00:部分匹配 0x01完全匹配
		uchar ucKernelId;			// KernelId
		uchar ucCheckKernelIdSign;	// 0--匹配不校验内核ID   1--匹配校验内核ID	
	}EMV_stTermAIDList;
	/**< --------------------------------------------------------------------------------------------------*/

	/**< ---------------------------新增API接口 add by rsjian at 180417--------------------------------------------------------------------------*/
	/*paypass函数及专用参数*/
	//交易模式
	#define  EMV_FLOWTYPE_M_CHIP			0x21	//PayPass Mchip芯片模式
	#define  EMV_FLOWTYPE_M_STRIPE			0x22	//PayPass Stripe磁条模式
	#define  EMV_FLOWTYPE_R_LEGACY			0x23	//RUPAY Legacy模式
	#define  EMV_FLOWTYPE_R_NON_LEGACY		0x24	//RUPAY Non_Legacy模式

	#define  EMV_FLAG_ADD					     0x01 //添加 
	#define  EMV_FLAG_DELETE				     0x02 //删除 
	#define  EMV_FLAG_CLEAR				     0x03 //清除所有	

	#define EMV_INS_SET_TORN					 0xA1 // 发送闪卡交易数据
	#define EMV_INS_GET_TORN                    0xA2 // 获取闪卡交易数据
	#define EMV_INS_DEL_TORN					 0xA3 // 通知删除闪卡记录
	#define EMV_INS_GET_TRAN_PARAM              0xA4 // 获取交易参数		
	#define EMV_INS_OUT_TLVDATA                 0xA5 // PAYPASS OUT信号数据
	#define EMV_INS_MSG_TLVDATA				 0xA6 // PAYPASS MSG信号数据
	#define EMV_INS_GET_CAPK					 0xA7 // 获取认证公钥数据
	#define EMV_INS_DISPLAY                     0xA8 // 发送交互显示信息
	#define EMV_INS_SEND_DISC                   0xA9 // 发送带TornRecord的自定义数据(PAYPASS)	
	#define EMV_INS_DISP_LED_BEEP				 0xB1 // paypass非接性能卡片交互结束,显示绿灯
	#define EMV_INS_ISS_CERT_RECOVER_CHECK			 0xB2 // 发卡行回收证书检查
	#define EMV_INS_ISS_PAN_BLACKLIST_CHECK		 0XB3	//黑名单检测
	#define EMV_INS_GET_TRAN_PARAM_FORM_ICS       0xB4  //用于设置config,针对AMEX增加的   
		/*此卡人验证类型标识 / CVM Flag*/
	#define  EMV_CVMFLAG_NOCVM              0x00 //无需CVM验证
	#define  EMV_CVMFLAG_OFFLINEPIN         0x01 //脱机PIN
	#define  EMV_CVMFLAG_ONLINEPIN          0x02 //联机PIN
	#define  EMV_CVMFLAG_SIGNATURE          0x03 //签名
	#define  EMV_CVMFLAG_OLPIN_SIGN         0x04 //联机PIN加签名
	#define  EMV_CVMFLAG_ODV                0x05 //On device cardholder verification

		/* 信息标识 / Message ID*/
	#define EMV_MSGID_CARD_READ_OK				 0x17 // 读卡完成，可移走卡片（不代表交易成功） / Read card finished
	#define EMV_MSGID_TRY_AGAIN					 0x21 // 请重试 /  Try again
	#define EMV_MSGID_APPROVED					 0x03 // 交易批准 /  Transaction approved
	#define EMV_MSGID_APPROVED_SIGN			 	 0x1A // 交易批准并请求签名 / Transaction approved and requesting signature
	#define EMV_MSGID_DECLINED				     0x07 // 交易拒绝 / Transaction declined
	#define EMV_MSGID_ERR_OTH_CARD			     0x1C // 交易终止，请尝试其它卡片 / Transaction error, please try other card.
	#define EMV_MSGID_INSERT_CARD				 0x1D // 请插入卡片 /  Please insert IC card
	#define EMV_MSGID_SEE_PHONE					 0x20 // 请查看手机 /  Please check cell phone
	#define EMV_MSGID_AUTH_WAIT					 0x1B // 授权等待 /  Waiting authorization
	#define EMV_MSGID_CLEAR_DISPLAY				 0x1E // 清空显示 /  Clear screen display

	typedef enum{	
		OUT_APDU_ERROR,				//APDU 通讯错误
		OUT_APDU_STATUS_ERROR,		//APDU 非9000
		OUT_CARD_DATA_PARSING_ERROR, //卡片数据解析错误	
		OUT_CARD_DATA_MISSING_ERROR, //卡片数据缺失
		OUT_CANDIDATE_LIST_EMPTY,	//候选列表为空
		OUT_USER_STOP,				//用户中止
	}OUTCOME_ERR_TYPE;

	/*交互信息显示结构*/
	typedef struct
	{
		uchar ucMsgID;        // Message ID 参考宏定义
		uchar ucDataLen;      // 信息长度
		uchar auData[30];     // 信息数据
	}EMV_tDisplayMsg;


	//管理终端支持的AID，支持添加、删除操作：0x01-添加AID；0x02-删除AID; 0x03-清空AID
	//LIB_EXPORT extern int EMV_iManageAID(char cAction, EMV_stTermAIDList *pstAIDMatch);	
	LIB_EXPORT EMV_stTermAIDList * EMV_pGetTermAidist(void);
	
	/* 回收公钥证书结构体*/
	typedef struct
	{
		char ucIndex;      // 公钥索引
		char auRID[5];     // RID
		char auSN[3];      // 证书序列号
	}EMV_stRecCert;

	//设置终端TLV标签数据
	LIB_EXPORT extern int SaveEmvListData(char *pszTLVList,int nDataLen);
	LIB_EXPORT extern int SaveEmvData(char *pszTag,char *pszData,int nLen,YESORNO bOverride);
	LIB_EXPORT extern int EMV_iSetCAPubKey(ST_CAPK*stCAPK);
	/**< --------------------------------------------------------------------------------------------------*/


/**< --------------------------------------------------------------------------------------------------*/
/*提取一组通用非接触状态结构体,结构体和ST_VCPS_PROC一直，增加兼容*/
typedef struct {   //一般设置前6个即可
	char checkStatus;
	char checkRCTL;
	char checkCVMLimit;
	char checkFloorLimit;
	char optionAmtZore;
	char checkAmtZore;
	char szFloorLimit_b_9F1B[6+1];//保证4字节对齐
	char sRf_OfflineLimit_DF19[6+1];
	char sRF_TxnLimit_DF20[6+1];//保证4字节对齐
	char sRf_CVMLimit_DF21[6+1];
	char checkCash;
	char checkCashBack;
	char checkOnPIN;
	char checkSig;
	char checkExcpt;
	char cDF19Check;			
	char c9F1BCheck;
	char bSet;//是否被设置过 正式应用上不被设置，则按照默认值配置 从而不影响正常使用
}ST_RF_PROC;

LIB_EXPORT extern int RF_setParam(ST_RF_PROC *st_pr_proc);
LIB_EXPORT extern ST_RF_PROC* RF_getParam(void);

#ifdef __cplusplus
}
#endif

#endif
