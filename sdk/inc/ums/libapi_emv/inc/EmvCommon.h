#ifndef _EMV_COMMON_H_
#define _EMV_COMMON_H_

#define BOOL int
#define TRUE 1
#define FALSE 0

#define MAX_APP_ITEMS       16



#define MAX_APPNAME_LEN					33		//AppName的最大长度

#define CAPK_FILE	"Emv_Capk.dat"
#define APP_FILE	"Emv_AppLst.dat"


#define PEDICCARD	0x01			//0x01:内置IC卡
#define EXICCARD	0x02			//外置IC卡
#define PEDPICCCARD	0x03			//内置PICC
#define EXPICCCARD	0x04			//外置PICC 



#define STATPIN_NONE 			0		//不需要PIN
#define STATPIN_INOLINEPIN 		1		//输入了联机PIN
#define STATPIN_CDCVM	   		2		//进行了CDCVM
#define STATPIN_PINBYPASS  		3		//联机PIN,用户直接PYPASS
#define STATPIN_OFFLINEPIN 		4		//成功的执行了脱机PIN
#define STATPIN_CERT			5		//成功的进行了证件认证

//#define TERM_AIDLIST		"termaid.lst"   
#define ICC_SCRIPT_FILE		"iccscript"
#define FILE_TRADE_ATT		"trade.att"


//非接交易通道
#define TRADE_CHANNEL_AUTO 0
#define TRADE_CHANNEL_ONLINE 1
#define TRADE_CHANNEL_OFFLINE 2
#define TRADE_CHANNEL_CLPBOC  3


//STRUCTOR DEF
typedef struct _EMV_APPLIST_{
    unsigned char AppName[MAX_APPNAME_LEN];	//本地应用名,以'\x00'结尾的字符串
    unsigned char AID[17];				//应用标志
    unsigned char AidLen;				//AID的长度
    unsigned char SelFlag;				//选择标志(0部分匹配/1全匹配)      
    unsigned char Priority;				//优先级标志
    unsigned char TargetPer;			//目标百分比数
    unsigned char MaxTargetPer;			//最大目标百分比数
    unsigned char FloorLimitCheck;		//是否检查最低限额
    unsigned char RandTransSel;			//是否进行随机交易选择
    unsigned char VelocityCheck;		//是否进行频度检测
    unsigned long FloorLimit;			//最低限额
    unsigned long Threshold;			//阀值
    unsigned char TACDenial[6];			//终端行为代码(拒绝)
    unsigned char TACOnline[6];			//终端行为代码(联机)
    unsigned char TACDefault[6];		//终端行为代码(缺省)
    unsigned char AcquierId[7];			//收单行标志
    unsigned char dDOL[100];				//终端缺省DDOL
    unsigned char PreferAppName[17];   
    unsigned char AppLabel[17];
    unsigned char PreferLang[8 + 1]; //5F2D 首选语言
    unsigned char codeIdx;  //9f11 代码索引
    unsigned char TerminalType;  //终端类型
    //国际
    unsigned char bUseIntParam;  //是否使用国际参数
    unsigned char TargetPerInt;
    unsigned char MaxTargetPerInt;
    unsigned char FloorLimitInt[4];
    unsigned char ThresholdInt[4];
	
    unsigned char Capability[3];			//终端性能
    unsigned char ExCapability[5];			//终端扩展性能
   
    unsigned char reserved_0[92];
    unsigned char tDOL[256];			//终端缺省TDOL
    unsigned char Version[3];			//应用版本
    unsigned char RiskManData[10];		//风险管理数据
	unsigned char EC_bTermLimitCheck;	//是否支持终端交易限额
	unsigned long EC_TermLimit;			//终端交易限额，
	unsigned char CL_bStatusCheck;		//是否支持qPBOC状态检查
	unsigned long CL_FloorLimit;        //非接触终端最低限额
	unsigned long CL_TransLimit;        //非接触终端交易限额
	unsigned long CL_CVMLimit;          //非接触终端CVM限
	unsigned char TermQuali_byte2;      //交易金额与每个AID限额的判断结果，在刷卡前处理，通过此变量缓存判断结果
	unsigned char bOnlinePin;           //此AID是否支持联机PIN
}EMV_APPLIST;

typedef struct _EMV_CLAPPLIST_{
    unsigned char AppName[MAX_APPNAME_LEN];	//本地应用名,以'\x00'结尾的字符串
    unsigned char AID[17];					//应用标志
    unsigned char AidLen;					//AID的长度
    unsigned char SelFlag;					//选择标志( 部分匹配/全匹配) 
    
    unsigned char Priority;					//优先级标志
    unsigned char TargetPer;				//目标百分比数
    unsigned char MaxTargetPer;				//最大目标百分比数
    unsigned char FloorLimitCheck;			//是否检查最低限额
    
    unsigned char RandTransSel;				//是否进行随机交易选择
    unsigned char VelocityCheck;			//是否进行频度检测
    
    unsigned long FloorLimit;				//最低限额
    unsigned long Threshold;				//阀值
    unsigned char TACDenial[6];				//终端行为代码(拒绝)
    unsigned char TACOnline[6];				//终端行为代码(联机)
    
    unsigned char TACDefault[6];			//终端行为代码(缺省)
    unsigned char AcquierId[7];				//收单行标志
    unsigned char dDOL[100];				//终端缺省DDOL
    unsigned char PreferAppName[17];   
    unsigned char AppLabel[17];
    unsigned char PreferLang[8 + 1]; //5F2D 首选语言
    unsigned char codeIdx;  //9f11 代码索引
    unsigned char TerminalType;  //终端类型
	//国际
    	unsigned char bUseIntParam;  //是否使用国际参数
	unsigned char TargetPerInt;
	unsigned char MaxTargetPerInt;
	unsigned char FloorLimitInt[4];
	unsigned char ThresholdInt[4];

	unsigned char Capability[3];			//终端性能
	unsigned char ExCapability[5];			//终端扩展性能
    	unsigned char reserved_0[92];
	unsigned char tDOL[82];				//终端缺省TDOL
    //
    // 24byte for paywave
  	unsigned char CL_bZeroAmtNoCheck;   //是否不进行0金额检查反逻辑
  	unsigned char CL_zeroAmtCheckOpt; //0--0金额联机 非0--拒绝交易
	unsigned char CL_bTransLimitCheck;
	unsigned char CL_bCVMLimitCheck;
	unsigned char CL_bFloorLimitCheck;
	unsigned char CL_bCLFloorLimit;  //是否有非接最低限额
	unsigned char CL_bAppNotAllowed;//动态设置
	unsigned char bSupCVN17; ///* MSD CVN17 是否支持标志, 0-不支持，1- 支持*/
	unsigned char TermQuali_byte3;
	unsigned char TermQuali_byte4;
 	unsigned char reserved_for_paywave[14];
   //
   // for paypasss 104byte
   	unsigned char MagStripeAVN[2];  //Mag-stripe Application Version Number (Reader)
	unsigned char KernelID;
	unsigned char KernelConfig;
	unsigned char CVMCapabilityCVM;
	unsigned char CVMCapabilityNoCVM;
	unsigned char MagCVMCapabilityCVM;
	unsigned char MagCVMCapabilityNoCVM;

	unsigned char TransLimitODCVM[4];
	unsigned char TransLimitNoODCVM[4];
	unsigned char uDOL[81];
	unsigned char reserved_for_paypass[7];
   //
    unsigned char reserved_2[46];                 //保留
    unsigned char Version[3];				//应用版本
    
    unsigned char RiskManData[10];			//风险管理数据
	unsigned char EC_bTermLimitCheck;		//是否支持终端交易限额
	
	unsigned long EC_TermLimit;				//终端交易限额，
	
	unsigned char CL_bStatusCheck;			//是否支持qPBOC状态检查
	
	unsigned long CL_FloorLimit;			//非接触终端最低限额
	unsigned long CL_TransLimit;			//非接触终端交易限额
	unsigned long CL_CVMLimit;				//非接触终端CVM限
	
	unsigned char TermQuali_byte2;			//交易金额与每个AID限额的判断结果，在刷卡前处理，通过此变量缓存判断结果
	unsigned char bOnlinePin;               //此AID是否支持联机PIN
	
	//工行非接交易新加
	unsigned char CL_TermQuali_byte1;		//9f66的第一个字节
	unsigned char CL_CountryCode[2];		//国家代码 缺省0156
	unsigned char CL_TransCurrCode[2];		//交易货币代码, 缺省0156
	unsigned char CL_LimitForNoTicket[6];	//不打印凭条的限额,大于或等于这个限额打印凭条
}EMV_CLAPPLIST;


typedef struct _EMV_CAPK_{
    unsigned char RID[5];				//应用注册服务商ID
    unsigned char KeyID;				//密钥索引
    unsigned char HashInd;				//HASH算法标志，是否已添加test
    unsigned char ArithInd;				//RSA01/SM04算法标志
    unsigned char ModulLen;				//模长度
    unsigned char Modul[248];			//模
    unsigned char ExponentLen;			//指数长度
    unsigned char Exponent[3];			//指数
    unsigned char ExpDate[3];			//有效期(YYMMDD)
    unsigned char CheckSum[20];			//密钥校验和
}EMV_CAPK;

typedef struct _EMV_PARAM_{
	unsigned char MerchName[128];			//商户名把原来的256字节变为128字节
	unsigned long FloorLimit;				//最低限额，对应AID参数中的同名字段
	unsigned char bCheckFloorLimit;			//是否进行最低限额检查
	unsigned char bSupCandFromAidList_CL;	//非接是否支持以AID列表的方式建立候选列表
	unsigned char IfSupportOnline;			//是否支持联机
	unsigned char IfSupportRFPBOC;			//是否支持非接PBOC
	unsigned char IfSupportContactMode;		//是否支持接触模式
	unsigned char IfRequireCVM;				//是否要求CVM
	unsigned char IfSupportOnlinePIN;		//是否支持联机PIN
	unsigned char IfSupportSign;			//是否支持签名
	unsigned char maxNumFashCardRec;		//最大闪卡记录数
	unsigned char FlashCardTimeout;			//闪卡处理超时，默认60
	unsigned char IfSupFlashCardHandle;		//是否支持闪卡处理0-不支持 1-建行闪卡流程 2-银联闪卡流程
	///////////add 20140910
	unsigned char IfSkipCardHolderVerify;   //是否跳过持卡人验证
	unsigned char pureECCSupportState;		//支持纯电子现金卡的状态,不进行纯电子现金卡交易检测设为0xff,
	///////////end
	unsigned char takePriorityForOrg;//优先采用哪个卡组织的AID, 0--不支持，1-银联优先，其他值未定义(注:现在未用这个成员，不排除将来用，所以国内程序最好设为1表示银联优先)
	unsigned char indShowCardNoForOnlineQpboc;   //联机Qpboc显示卡号等待用户确认标志，b1=1:联机显示卡号; b2=1:脱机认证失败转联机显示卡号。
	unsigned char bSupCDCVM; //是否支持CDCVM，设为1表示支持
	//以下为非接快速业务参数
	unsigned char openQPSState; //0--不支持QPS  1--银联  2或其他值--非银联的QPS
	//以下值只对银联QPS协议
	unsigned char stageForQPS;
	unsigned char bOpenNoSign;  //是否开通免签
	unsigned char limitForQPS[6];
	unsigned char limitForNoSign[6];
	////////////////////////////////
	unsigned char currFlashTimeout;			//当前闪卡流程超时时间(s)
	unsigned char bCheckCapkExp;			//是否检测公钥过期
	unsigned char FlashCardTimeoutHigh;		//闪卡超时(高字节)
	unsigned char currFlashTimeoutHigh;		//当前闪卡流程超时时间(高字节s)
	////////////////////////////////////
	unsigned char reserv_1[89];
	unsigned char MerchCateCode[2];			//商户类别码(没要求可不设置)
	unsigned char MerchId[15];				//商户标志(商户号)
	unsigned char TermId[8];				//终端标志(POS号)
	unsigned char TerminalType;				//终端类型
	unsigned char Capability[3];			//终端性能
	unsigned char ExCapability[5];			//终端扩展性能
	unsigned char TransCurrExp;				//交易货币代码指数
	unsigned char ReferCurrExp;				//参考货币指数
	unsigned char ReferCurrCode[2];			//参考货币代码
	unsigned char CountryCode[2];			//终端国家代码
	unsigned char TransCurrCode[2];			//交易货币代码
	unsigned long ReferCurrCon;				//参考货币代码和交易代码的转换系数(交易货币对参考货币的汇率*1000)
	unsigned char TransType;				//当前交易类型 
	unsigned char ForceOnline;				//商户强制联机(1 表示总是联机交易)
	unsigned char GetDataPIN;				//密码检测前是否读重试次数
	unsigned char SupportPSESel;			//是否支持PSE选择方式
	unsigned char TermTransQuali[4];		//终端交易限制
	unsigned char TermIsSupEct;				//终端是否支持电子现金功能
	unsigned char ECTSI;					//电子现金终端支持指示器
	unsigned char bSurportSM;				//是否支持国密
	unsigned char EC_bTermLimitCheck;	//是否支持终端交易限额
	unsigned long EC_TermLimit;			//终端交易限额，
	unsigned char CL_bStatusCheck;		//是否支持qPBOC状态检查
	unsigned long CL_FloorLimit;		//非接触终端最低限额
	unsigned long CL_TransLimit;		//非接触终端交易限额
	unsigned long CL_CVMLimit;			//非接触终端CVM限额

	//
	unsigned char TermVersion[2];		//应用版本
	unsigned char TermTargetPer;		//随机选择目标百分数
	unsigned char TermMaxTargetPer;		//偏置随机选择的最大目标百分数
	unsigned long TermThreshold;		//偏置随机选择阈值
	unsigned char AIDForECCOnly[16];	//纯电子现金应用的aid
	unsigned char AidLenForECCOnly;		//AID的长度
	char	      AcquierId[11+1];		//收单行ID(标识码),从保留的18字节中取12字节，最长11个字节，变成bcd码左补0到12位bcd码n6-11
	unsigned char bSupportQPBOCEx;		//是否支持扩展qpboc的功能
	unsigned char bSupportAccTypeSel;	//是否支持账户类型选择
	unsigned char qpbocExMacKeyIdx;		//作为收款机为行业应用的管理密钥的索引
	unsigned char Reserve[4];			//补位3个字节
}EMV_PARAM;

typedef struct _tagRecNumForFlash
{
	unsigned char flashTm[7];
	unsigned char SFIForPan;
	unsigned char RecNumForPan;
	unsigned char SFIForTrack2;
	unsigned char RecNumForTrack2;
	unsigned char SFIForLastRec;
	unsigned char RecNumForLastRec;
	unsigned char SDASign;
	unsigned char atc[2]; //0x9f36
	unsigned char currCode[2];//save5F2A -->Rd0x9F51  or DF71
	unsigned char eccBal[6]; //dave9f5d or in 9f10-->rd 9f79 or DF79
	unsigned char authAmt[6];
	unsigned char panLen;
	unsigned char pan[10];
	unsigned char aidLen;
	unsigned char aid[16];
	unsigned char unused[2];
} TRecNumForFlash;

typedef struct tagEmvCbFuncs
{
	//int (*pcbfWaitAppSel)(int TryCnt, EMV_APPLIST *AppNameList, int AppNum);
	int (*pcbfWaitAppSel)(int TryCnt, EMV_CLAPPLIST *AppNameList, int AppNum);
	int (*pcbfGetUnknowTLV)(unsigned short Tag, unsigned char *dat, int len);
	int (*pcbfGetDateTime)(unsigned char *DateTime);
	void (*pcbIoCtrl)(unsigned char ioname,unsigned char *iovalue);
	int (*pcbfInputAmt)(unsigned char *AuthAmt, unsigned char *CashBackAmt);
	void (*pcbfAdviceProc)(void);
	int (*pcbfVerifyCert)(void);
	void (*pcbfVerifyPINOK)(void);
	int (*pcbfGetHolderPwd)(int iTryFlag, int iRemainCnt, unsigned char *pszPlainPin);
	int (*pcbfReferProc)(void);
	void  (*pcbfGetAllAmt)(unsigned char *PANData,int PANDataLen, unsigned char *AuthAmt, unsigned char *bcdTotalAmt);
	int (*pcbfDispCardNo)(void);
	int (*pcbfAppConfirmBeforeSelect)(unsigned char *Aid, int aidLen);
	int (*pcbfReadAndHandleQPbocExData)(unsigned long *amt, unsigned char *qpbocExType);
	int (*pcbfUpdateQPbocExData)(void);
	int (*pcbfAccountTypeSelect)(const char **accTypeList, int num, unsigned char *selItemNo);
	int (*pcbfGetIFDSerialNum)(unsigned char *ifdSN);	
	int (*pcbfGetEccSignAndAmt)(unsigned char *eccSign, unsigned char *tradeAmt, const unsigned char *eccTradeLimit);
	int (*pcbfHandleBeforeGPO)(void);
	int (*pcbCardInQPSBinList)(unsigned char stageForQPS);//增加的
	int (*pcbSpecifyQPSHandle)(void);  //小额免密判断
	int (*pcbHandleAfterReadCardNo)(const char *cardNo);

	void (*pcbFlashResultProc)(TRecNumForFlash *pFlashRec, int state);//state = 0表示没有扣钱
	
	//为了适配别的emv接口而用
}TEmvCBFuncs;

extern TEmvCBFuncs 	g_ecbFuns;



// useful macro
#define _MIN(a, b)		( (a)<(b) ? (a) : (b) )
#define _MAX(a, b)		( (a)>(b) ? (a) : (b) )

// macros for analyze EMV TLV string
#define TAGMASK_CLASS		0xC0		// tag mask of tag class
#define TAGMASK_CONSTRUCTED	0x20		// tag mask of constructed/primitive data
#define TAGMASK_FIRSTBYTE	0x1F		// tag mask of first byte
#define TAGMASK_NEXTBYTE	0x80		// tag mask of next byte

#define LENMASK_NEXTBYTE	0x80		// length mask
#define LENMASK_LENBYTES	0x7F		// mask of bytes of lenght

#define TAG_NULL_1			0x00		// null tag
#define TAG_NULL_2			0xFF		// null tag


#define ICC_EMV				0			//emv卡座




#define ENGLISH				0
#define CHINESE				1

#define TYPE_CASH			0x01		//交易类型(现金)
#define TYPE_GOODS			0x02		//交易类型(购物)
#define TYPE_SERVICE		0x04		//交易类型(服务)
#define TYPE_CASHBACK		0x08		//交易类型(反现)
#define TYPE_INQUIRY		0x10		//交易类型(查询)
#define TYPE_PAYMENT		0x20		//交易类型(支付)
#define TYPE_ADMINISTRATIVE	0x40		//交易类型(管理)
#define TYPE_TRANSFER		0x80		//交易类型(转账)

#define MAX_APP_NUM			32			//应用列表最多可存储的应用数
#define MAX_CAPK_NUM		64			//认证公钥表最多可存储的公钥数
#define MAX_CAPKREVOKE_NUM	96			//认证公钥撤回列表的最大个数32*3

#define PART_MATCH			0x00		//ASI(部分匹配)
#define FULL_MATCH			0x01		//ASI(完全匹配)

#define EMV_GET_POSENTRYMODE			0 
#define EMV_GET_BATCHCAPTUREINFO		1 
#define EMV_GET_ADVICESUPPORTINFO		2 

//交易处理函数返回码定义
#define EMV_OK              0			//成功  
#define ERR_EMVRSP         (-2)			//返回码错误
#define ERR_APPBLOCK       (-3)			//应用已锁
#define ERR_NOAPP          (-4)			//卡片里没有EMV应用
#define ERR_USERCANCEL     (-5)			//用户取消当前操作或交易
#define ERR_TIMEOUT        (-6)			//用户操作超时
#define ERR_EMVDATA        (-7)			//卡片数据错误
#define ERR_NOTACCEPT      (-8)			//交易不接受
#define ERR_EMVDENIAL      (-9)			//交易被拒绝
#define ERR_KEYEXP         (-10)		//密钥过期
#define ERR_NOPINPAD       (-11)		//没有密码键盘或键盘不可用
#define ERR_NOPIN          (-12)		//没有密码或用户忽略了密码输入
#define ERR_CAPKCHECKSUM   (-13)		//认证中心密钥校验和错误
#define ERR_NOTFOUND       (-14)		//没有找到指定的数据或元素
#define ERR_NODATA         (-15)		//指定的数据元素没有数据
#define ERR_OVERFLOW       (-16)		//内存溢出
#define ERR_NOTRANSLOG     (-17)		//无交易日志
#define ERR_NORECORD       (-18)		//无记录
#define ERR_NOLOGITEM      (-19)		//目志项目错误
#define ERR_ICCRESET       (-20)		//IC卡复位失败
#define ERR_ICCCMD         (-21)		//IC命令失败
#define ERR_ICCBLOCK       (-22)		//IC卡锁卡 
#define ERR_ICCNORECORD    (-23)		//IC卡无记录
#define ERR_GENAC1_6985    (-24)		//GEN AC命令返回6985
#define ERR_USECONTACT     (-25)		//非接失败，改用接触界面
#define ERR_APPEXP         (-26)		//qPBOC卡应用过期
#define ERR_BLACKLIST      (-27)		//qPBOC黑名单卡
#define ERR_GPORSP         (-28)		//err from GPO
#define ERR_TRANSEXCEEDED		(-30)	//非接交易超限
#define ERR_QPBOCFDDAFAIL		(-31)
///////////////140910增加
#define ERR_UNSUPPORTED			(-32)	//不支持
#define ERR_NOFILE				(-33)	//没有文件
#define ERR_DENIALFORECC		(-34)	//拒绝纯电子现金卡的联机交易
#define ERR_RMAC				(-35)	//安全报文mac校验错
#define ERR_RFNOTAG9F66			(-36)	//非接的PDOL中没有9f66
#define ERR_MACCHECK			(-37)
#define ERR_MEMERR				(-38)	//6581 内存失败
#define ERR_LENERR				(-39)	//6700 长度错误
#define ERR_CONDNOTSATISFIED	(-40)	//6985 条件不满足
#define ERR_CMDNOEXIST			(-41)	//6d00 命令不存在
#define ERR_CMDNOTSUPPORT		(-42)	// 6e00 命令类型不支持
#define ERR_TCUNAVAILABLE		(-43)	//9406 所需TC不可用
#define ERR_READ_LAST_REC		-44		//读最后一条记录失败
#define ERR_ECBALANCE_SHORT		-45		//纯电子现金卡余额不足
#define ERR_FLASHED_CARD		(-46)	//读取最后一条记录出错，进入当笔闪卡处理流程
#define ERR_CURRFLASH_TIMEOUT	(-47)	//当前闪卡流程超时
#define ERR_USEDFLASHED_CARD	(-48)	//提示使用当前发生了闪卡的卡片
#define ERR_ALLFLASH_TIMEOUT	(-49)   //全部闪卡超时，此时应用程序应该调用获取超时的闪卡记录
#define ERR_FLASH_READCARD		(-50)   //闪卡处理中读卡失败
#define ERR_EMVREADFILE			(-51)	//emv库中读文件失败
#define ERR_EMVWRITEFILE		(-52)	//emv库写文件失败
#define ERR_EMVFAIL				(-53)	//emv交易失败
#define ERR_EXCEEDED_CLFLOORLMT			-54  //超过非接脱机限额
#define ERR_UNIMPL_CB 					-55  //未实现的回调



#define REFER_APPROVE		0x01		//参考返回码(选择批准)
#define REFER_DENIAL		0x02		//参考返回码(选择拒绝)
#define ONLINE_APPROVE		0x00		//联机返回码(联机批准)     
#define ONLINE_FAILED		0x01		//联机返回码(联机失败) 
#define ONLINE_REFER		0x02		//联机返回码(联机参考)
#define ONLINE_DENIAL		0x03		//联机返回码(联机拒绝)
#define ONLINE_ABORT		0x04		//兼容PBOC(交易终止)
#define ONLINE_REFERANDFAIL 0x05		//联机拒绝和联机参考


#define PATH_PBOC			0x00		//应用路径:标准PBOC
#define PATH_QPBOC			0x01		//应用路径:qPBOC
#define PATH_MSD			0x02		//应用路径:MSD
#define PATH_ECash			0x03		//应用路径:电子现金







EMV_CLAPPLIST *GetCurrSelectedApp(void);
int EmvUpFlashClearCurrent_Api(void);
int EmvUpFlashGetFailRecForUpload_Api(unsigned char *pBuf);
int EmvCheckQpbocFlashState_Api(void);

//下面是一些测试的宏
#define TESTCASE_QPBOC_SIGN_MASK	0xFC00
#define TESTCASE_QPBOC_SIGN_NOFLASH	0x4000
#define TESTCASE_QPBOC_SIGN_ONCE		0x8000

#define TESTCASE_QPBOC_READLASTREC_FAIL    1  //qpboc读最后一条记录失败
#define TESTCASE_QPBOC_READ_PAN_FAIL			0x4  //闪卡处理中读主账号失败
#define TESTCASE_QPBOC_READ_ATC_FAIL			0x5   ////闪卡处理中读ATC号失败
void SetTestCaseCode(unsigned short caseCode);

//返回当前的闪卡状态
typedef enum tagUPFlashState
{
	UPFLASHSTATE_NONE = 0,                       //正常状态
	UPFLASHSTATE_IN_CURRENT = 1,          //当前闪卡流程中
	UPFLASHSTATE_TMOUT_CURRENT =  2, //当前闪卡流程超时
	UPFLASHSTATE_TMOUT_REC =  3     //有记录超时，要求上送
} TUPFlashState;

#if 0

//emv协议栈初始化
int EmvInit_Api(void);


//
void EmvClear_Api(void);

void EmvSetTradeAmt_Api(const unsigned char *bcdConsumeAmt, const unsigned char *bcdCashbackAmt);


//非接预处理函数
int EmvCLPreProcess_Api(int qpbocTradeChannel, int otherTradeChannel);
//
int EmvAppSel_Api(int Slot, unsigned long TransNo);
//
int EmvReadAppData_Api(void);
//
int EmvCardAuth_Api(void);
///
int EmvProcTrans_Api(unsigned char *bcdConsumeMoney, unsigned char *bcdCashBackMoney, unsigned char *bIfGoOnline);
//
int EmvProcCLTrans_Api(unsigned char *pbGoOnline);
//
int EmvProcTransComplete_Api(unsigned char ucResult, unsigned char *RspCode, 
										 unsigned char *AuthCode, int AuthCodeLen, 
										 unsigned char *IAuthData, int IAuthDataLen, 
										 unsigned char *script, int ScriptLen);

//
unsigned char EmvGetPath_Api(void);
//
int EmvGetScriptResult_Api(unsigned char *Result, int *RetLen);
//
BOOL EmvIsMSMode_Api(void);
//
int EmvGetMSData_Api(char * track1, char *track2);
//
int  EmvGetBalance_Api(unsigned char* BcdBalance);
//
int EmvReadELoadLogRecord_Api(int RecordNo);
//
int EmvGetELoadLogItem_Api(unsigned short Tag, unsigned char *TagData, int *TagLen);
//
int EmvReadLogRecord_Api(int RecordNo);
//
int EmvGetLogItem_Api(unsigned short Tag, unsigned char *TagData, int *TagLen);

//
BOOL EmvNeedSignature_Api(void);
//
BOOL EmvNeedOnlinePin_Api(void);
//
void EmvGetParam_Api(EMV_PARAM *Param);
//
void EmvSetParam_Api(EMV_PARAM *Param);
//
void EmvSaveParam_Api(EMV_PARAM *Param);
//
int EmvSetTLV_Api(unsigned short Tag, unsigned char *Data, int len);
//
int EmvGetTLV_Api(unsigned short Tag, unsigned char *DataOut, int *OutLen);
//
int EmvAddCapk_Api(EMV_CAPK  *capk);
//
int  EmvGetCapk_Api(int Index, EMV_CAPK  *capk);
//
int EmvSearchCapk_Api(EMV_CAPK  *pCapk, const unsigned char *rid, unsigned char keyID);
//
int EmvDelCapk_Api(unsigned char KeyID, unsigned char *RID);
//
void EmvClearCapk_Api(void);
//
int EmvAddApp_Api(EMV_APPLIST *App);
//
void EmvClearApp_Api(void);
//
int EmvGetApp_Api(int Index, EMV_APPLIST *App);
//
int EmvDelApp_Api(unsigned char *AID, int AidLen);
//
int EmvAddCLApp_Api(EMV_CLAPPLIST *App);
//
int EmvDelCLApp_Api(unsigned char *AID, int AidLen);
//
int EmvGetCLApp_Api(int Index, EMV_CLAPPLIST *App);
//
int EmvSetIcCardType_Api(int Mode);
//
int EmvGetIcCardType_Api(void);
//
int EmvSaveLog_Api(char *FileName,int SaveNum);

//
int EmvAddBlackList_Api(const char *cardNo);
//
int EmvDelBlackList_Api(const char *cardNo);
//
void EmvClearBlacklist_Api(void);
//
int EmvGetEmvReleaseVer_Api(char *VerOut);

#endif

//非公开的函数
int EmvSelectApp(unsigned long TransNo, int ReadLogFlag, int *pTryCnt);
//
int EmvInitApp(void);
//
void EMVProcRestric(void);
//
int EMVHolderVerify(void);
//
int EMVRiskManagement(void);
//
int EMVTermActAnalys(unsigned char *bIfGoOnline);

int IccCmd_GetData(unsigned char p2, unsigned char *DataOut, int *OutLen) ;
//
int IccCmd_GetDataEx(unsigned short tag, unsigned char *DataOut, int *OutLen) ; 


#endif

