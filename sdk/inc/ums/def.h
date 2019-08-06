#ifndef _DEF_HEAD_H_
#define _DEF_HEAD_H_

#ifdef WIN32
	#ifdef USE_DLLMODE
		#ifdef UMS_DLL_EXPORTS
		#define UMS_API __declspec(dllexport)
		#else
		#define UMS_API __declspec(dllimport)
		#endif
	#else
		#define UMS_API
	#endif
#else
	#define UMS_API
#endif



#ifdef HX_APP_VARIABLES
    #define EXTERN 
#else
    #define EXTERN extern 
#endif

//#include "struct.h"
//#include "coredef.h"
//#include "poslib.h" 

typedef unsigned char	uchar;
typedef unsigned char	byte;
typedef const char		cchar;
typedef unsigned int	uint;
typedef const int		cint;
typedef unsigned short	ushort;
typedef unsigned long	ulong;


#ifdef WIN32
#define __FUNCTION__	""
#endif

//#define Icc_Close Icc_Release

/**<按键定义*/
typedef enum                    /**<键值根据不同厂商机具定义*/
{
    UKEY_1 = 0x01,              /**<数字键1*/
    UKEY_2 = 0x02,              /**<数字键2*/
    UKEY_3 = 0x03,              /**<数字键3*/
    UKEY_4 = 0x04,              /**<数字键4*/
    UKEY_5 = 0x05,              /**<数字键5*/
    UKEY_6 = 0x06,              /**<数字键6*/
    UKEY_7 = 0x07,              /**<数字键7*/
    UKEY_8 = 0x08,              /**<数字键8*/
    UKEY_9 = 0x09,              /**<数字键9*/
    UKEY_0 = 0x0a,              /**<数字键0*/
    UKEY_ENTER   = 0x10,        /**<确认键*/
    UKEY_CANCEL  = 0x11,        /**<取消键*/
    UKEY_UP      = 0x12,        /**<向上翻页键*/
    UKEY_DOWN    = 0x13,        /**<向下翻页键*/
    UKEY_FUN     = 0x14,        /**<功能键*/
    UKEY_BACK    = 0x15,        /**<退格键*/
    UKEY_POINT   = 0x16,        /**<点键*/
    UKEY_LETTER  = 0x17,        /**<字母键*/
    UKEY_MENU    = 0x18,        /**<菜单键*/
    UKEY_F1  = 0x19,            /**<F1键*/
    UKEY_F2  = 0x1A,            /**<F2键*/
    UKEY_F3  = 0x1B,            /**<F3键*/
    UKEY_F4  = 0x1C             /**<F4键*/
} KEY_VALUE;


//2.2.2	系统类API

//终端信息结构体
typedef struct
{
	byte	Terminal[20];	//终端型号,左对齐(厂商+型号,PAX、XGD、LND、NLD、VFI、HZR、SYD)
	byte	SN[40];			//终端硬件序列号
	int		Disp_X;			//横向最大像素
	int		Disp_Y;			//纵向最大像素
	int		Disp_Line1;		//大字体屏幕显示行数
	int		Disp_Line2;		//小字体屏幕显示行数
	int		Disp_Chinese;	//一行显示中文字符最大个数
	int		Disp_Character;	//一行显示英文、数字字符最大个数(小字体)
}TERMINALINFO;

//主控服务函数类型定义
typedef int (*ServerFunc)(const char *pszAppName, void *pvInData, int iInLen, void *pvOutData, int *piOutLen);

//主控服务属性结构体
typedef struct _ServerAttr
{
    char szServerName[32];    //服务函数名
    ServerFunc pServerFunc;   //服务函数指针
    int iVerSion;             //服务函数版本
} ServerAttr;

//语言类型枚举
typedef enum
{
ULANGUAGE_CHINESE =  0,   //中文
ULANGUAGE_ENGLISH,        //英语
ULANGUAGE_JAPANSES        //日语
}ULanguage;

//系统类API返回枚举
typedef enum
{
	USYS_PARAERROR = -2,  //参数错
	USYS_FAIL      = -1,  //失败
	USYS_SUCCESS    = 0,   //成功
	USYS_FIRST     = 1,   //程序更新后第一次运行
	USYS_NOFIRST   = 2    //程序非第一次运行
}USysStatus;

//2.2.3	显示类API

//显示类API返回码定义
typedef enum
{ 
	SCREEN_MAIN,     //主屏
	SCREEN_GUEST	 //客显
} DispStatus;

typedef enum
{
	UDISP_DEV_FAIL  =-3,		//设备原因失败
	UDISP_FILE_FAIL =-2,		//文件原因失败
	UDISP_FAIL     	=-1,		//未知原因失败
	UDISP_SUCCESS  	=0			//成功
} ScreenType;

//2.2.5	工具类API

#define UMAX_RSA_MODULUS_LEN   512   //RSA最大模长度
#define UMAX_RSA_PRIME_LEN     256   //RSA最大模素数长度
//工具类API返回码定义
typedef enum
{
	UUTIL_TIMEOUT        = -3,    //输入超时
	UUTIL_CANCEL         = -2,    //输入取消
	UUTIL_FAIL           = -1,    //失败
	UUTIL_SUCCESS        =  0	    //成功
} UtilStatus;
//条码二维码格式定义
typedef enum
{
	UCODE_QRCODE,
	UCODE_PDF417,
	UCODE_GMCODE,
	UCODE_CODE128,
	UCODE_CODE39,     
	UCODE_EAN13,     
	UCODE_EAN128
} BarCode;
//RSA公钥结构定义
typedef struct 
{
	uint   uiBits;   //模位数,bit单位
	byte   ucModulus[UMAX_RSA_MODULUS_LEN];   //模
	byte   ucExponent[UMAX_RSA_MODULUS_LEN];  //指数
}URSAPUBLICKEY;
//RSA私钥结构定义
typedef struct 
{
	uint   uiBits;    //模位数,bit单位
	byte   ucModulus[UMAX_RSA_MODULUS_LEN];   //模
	byte   ucPublicExponent [UMAX_RSA_MODULUS_LEN];  //公钥指数
	byte  ucExponent[UMAX_RSA_MODULUS_LEN];   //私钥指数
	byte   ucPrime[2][UMAX_RSA_PRIME_LEN];     //pq素数,素数因子
	byte   ucPrimeExponent[2][UMAX_RSA_PRIME_LEN]; //CRT指数,素数与指数除法值
	byte   ucCoefficient[UMAX_RSA_PRIME_LEN];  //CRT系数,素数与素数除法值
}URSAPRIVATEKEY;
//RSA算法密钥长度枚举
typedef enum 
{
	URSA_KEY_LEN_512,
	URSA_KEY_LEN_1024,
	URSA_KEY_LEN_2048
}URSAKeyLen;
//RSA算法指数枚举
typedef enum 
{
	URSA_EXP_3,       //0x03
	URSA_EXP_10001    //0x10001
}URSAEXP;
//签名版类型枚举
typedef enum
{
	USIGNATURE_INT,         //内置签名版
	USIGNATURE_EXT_COM1,    //外置PinPad口,密码键盘签名版,对应UPORT_COM1
	USIGNATURE_EXT_COM2,    //单独外置COM口签名版,对应UPORT_COM2
	USIGNATURE_EXT_COM3,    //单独外置COM口签名版,对应UPORT_COM3
	USIGNATURE_EXT_COM4,    //单独外置COM口签名版,对应UPORT_COM4
	USIGNATURE_EXT_COM5,    //单独外置COM口签名版,对应UPORT_COM5
	USIGNATURE_EXT_USB1,   //外置PinPad口,密码键盘签名版,对应UPORT_USB1
	USIGNATURE_EXT_USB2,   //单独外置USB口签名版,对应UPORT_USB2
	USIGNATURE_EXT_USB3,   //单独外置USB口签名版,对应UPORT_USB3
}USignaturePad;

//2.2.6	通讯类API

//SSL句柄定义
typedef int USSL_HANDLE;

//通讯方式枚举
typedef enum
{
	UCOMM_GPRS, //GPRS 通讯
	UCOMM_RS232, //RS232 通讯
	UCOMM_WIFI, //WIFI 通讯

	UCOMM_CDMA,       //CDMA通讯
	UCOMM_IP,         //以太网IP通讯
	UCOMM_MODEM,       //MODEM通讯
} CommMode;

//通讯类返回值枚举
typedef enum
{ 
	UCOMM_SSL_RESOURCE             = -17, //超过SSL最大限制
	UCOMM_SSL_NONSUPPORT           = -16, //不支持的文件格式、协议版本、密码套件
	UCOMM_SSL_CERT_NOT_YET_VALID   = -15, //对方证书还未生效
	UCOMM_SSL_CERT_HAS_EXPIRED     = -14,  //对方证书已过期
	UCOMM_SSL_NOCONNECT            = -13,  //SSL还未连接
	UCOMM_SSL_SET_CIPHER_FAIL      = -12,  //设置算法套件失败
	UCOMM_SSL_LOAD_KEY_FAIL        = -11,  //加载私钥失败
	UCOMM_SSL_LOAD_CERT_FAIL       = -10,  //加载证书失败
	UCOMM_SSL_LOAD_CA_FAIL         = -9,  //加载CA失败
	UCOMM_DEVICE_UNAVAILABLE       = -8,   //设不可用
	UCOMM_PARA_ERR                 = -7,   //参数错
	UCOMM_CONNECT_ERR              = -6,  //无法连接
	UCOMM_CONNECTING               = -5,   //通讯连接中,PPP拨号中
	UCOMM_LOGOFF                   = -4,   //通讯链路断开
	UCOMM_CANCEL                   = -3,   //按键取消
	UCOMM_TIMEOUT                  = -2,   //超时
	UCOMM_FAIL                     = -1,   //失败
	UCOMM_SUCCESS                  =  0,  //成功
	UCOMM_LINK_OK                  =  1    //通讯链路OK
} CommStatus;

//挂断模式枚举
typedef enum 	/*挂断模式*/
{
	UHANGUP_FAST,/*快速挂断,如果是针对无线则只挂断SOCKET且不做tcpwait*/
//	UHANGUP_DELAY, /*慢挂断,如果是针对无线则只挂断SOCKET且做tcpwait*/
	UHANGUP_FAST_PPP, /*只是针对无线挂断PPP和SOCKET且不做tcpwait*/
//	UHANGUP_DEALY_PPP, /*只是针对无线挂断PPP和SOCKET且做tcpwait*/
//    UHANGUP_EXIT
}HangUpMode;

//无线网络注册参数结构体(GPRS、CDMA)
typedef struct
{
	char  NetUsername[41] ; /* 无线modem建立PPP链路时要用到的用户名 */
	char  NetPassword[21] ; /* 无线modem建立PPP链路时要用到的密码 */
	char  ModemDialNo[21] ; /*无线modem建立PPP链路时使用的接入号码,采用ATD+号码的形式,如“ATD*99***1#码的形式*/
	char  GprsApn[41] ;	/*移动APN名称*/
	char  SimPin[11] ;	/*SIM卡pin*/
	char  WorkMode ;   /*0x01、长链; 0x02、短链*/
	char  DtrFlag;	/*是否有流控,0x00有流控,0x01无流控*/
    char  PppType;    /*协议类型*/
}PPPLOGINCONFIG;

//以太网通讯参数结构体
typedef struct
{
	byte DHCP;        /*是否开启DHCP,0-否,1-是*/
	char  IP[16] ;	/*本地IP地址*/
	char Gateway[16] ;	/*本地网关*/
	char  Mask[16] ;	/*本地子网掩码*/
    char  Dns1[16];/*DNS*/
    char  Dns2[16];/*DNS*/
}IPCONFIG;

#if 0
//WIFI密码格式
typedef enum
{ 
	WLN_KEY_TYPE_NOKEY,  /*不使用密码*/
	WLN_KEY_TYPE_HEX,    /*使用十六进制的密码格式*/
	WLN_KEY_TYPE_ASCII  /*使用ASCII的密码格式*/
}UWLNKEYTYPE;

//WIFI安全加密模式
typedef enum
{ 
	WLN_NET_SEC_NONE,       /*不使用安全加密模式*/
	WLN_NET_SEC_WEP_OPEN,   /*使用开放密钥的WEP模式*/
	WLN_NET_SEC_WEP_SHARED, /*使用共享密钥的WEP模式*/
	WLN_NET_SEC_WPA,        /*使用WPA模式*/
	WLN_NET_SEC_WPA2,        /*使用WPA2模式*/
	WLN_NET_SEC_WPA_PSK,     /*使用WPA-PSK模式*/
	WLN_NET_SEC_WPA2_PSK     /*使用WPA2-PSK模式*/
}UWLNNETSEC;
#endif

/*WIFI安全加密模式附属属性*/
typedef enum
{
    WLN_NET_WSEC_OFF,
    WLN_NET_WSEC_WEP,
    WLN_NET_WSEC_TKIP,
    WLN_NET_WSEC_WEP128,
    WLN_NET_WSEC_AES,
} UWLNNETWSEC;

/*WIFI安全加密认证方式*/
typedef enum
{
    WLN_NET_AUTH_OPEN,
    WLN_NET_AUTH_WEP,
    WLN_NET_AUTH_Shared,
    WLN_NET_AUTH_IEEE8021X,
    WLN_NET_AUTH_WPA_PSK,
    WLN_NET_AUTH_WPA_EAP,
    WLN_NET_AUTH_WPA2_PSK,
    WLN_NET_AUTH_WPA2_EAP,
    WLN_NET_AUTH_WPA_CCKM,
    WLN_NET_AUTH_WPA2_CCKM,
    WLN_NET_AUTH_NONE,
} UWLNNETWAUTHTYPE;

/**<WIFI通讯参数结构体:*/
typedef struct
{
    byte DHCP;           /**<是否开启DHCP，0x00-否，0x01-是*/
    int  Wsec; /*Contains the numeric value for network security type.参见enum UWLNNETWSEC*/
    int  WAuthType; /*Contains the numeric value for the network authentication type.参见UWLNNETWAUTHTYPE*/
    byte SSID[100];      /**<WIFI用户名*/
    byte Pwd[100];       /**<WIFI密码*/
    char IP[16];        /**<本地IP地址*/
    char Gateway[16];   /**<本地网关*/
    char Mask[16];      /**<本地子网掩码*/
    char Dns1[16];      /**<DNS*/
    char Dns2[16];      /**<DNS*/
} WIFICONFIG;

/**<WIFI热点信息结构体:*/
typedef struct
{
    byte SSID[100];		/*WIFI热点名称*/
    int  Wsec; /*Contains the numeric value for network security type.参见enum UWLNNETWSEC*/
    int  WAuthType; /*Contains the numeric value for the network authentication type.参见UWLNNETWAUTHTYPE*/
} WIFIINFO;

//IP、WIFI通讯本机IP信息
typedef struct
{
	char  IP[16];         /*本地IP地址*/
	char  Gateway[16];	  /*本地网关*/
	char  Mask[16];       /*本地子网掩码*/
    char  Dns1[16];       /*DNS*/
	char  Dns2[16];       /*DNS*/
	char  MAC[18];        /*MAC地址,格式如00-23-5A-15-99-42*/
}TERMINALIPINFO;

//MODEM通讯参数结构体
typedef struct
{
	int     DialMode;      /*拨号模式：0同步,1异步*/
	char	PredialNo[10]; /*外线号码*/
	char	TelNo[3][21]; /*电话号码*/
	int		IsCheckDialTone; /*是否检测拨号音0默认检测,1不检测 */
}MODEMCONFIG;

//外设扩展接口枚举
typedef enum
{
	UPORT_COM1,    //COM口1,做默认的PinPad口
	UPORT_COM2,    //COM口2,做默认的RS232口1
	UPORT_COM3,    //COM口3,做默认的RS232口2
	UPORT_COM4,    //COM口4
	UPORT_COM5,    //COM口5
	UPORT_USB1,   //USB口1,可用作USB PinPad口
	UPORT_USB2,   //USB口2
	UPORT_USB3,   //USB口3
	UPORT_LAN      //以太网TCP/IP口
}ExtPort;

//串口通讯波特率枚举
typedef enum
{
	UBPS9600,
	UBPS115200
}BaudRate;//按照实际支持情况实现

//串口通讯数据位、停止位、校验位参数枚举
typedef enum
{
	UDB8		= 0xc0,		//8位数据位选择
	UDB7		= 0x40,		//7位数据位选择
	UDB6		= 0x80,		//6位数据位选择
	UDB5		= 0x00,		//5位数据位选择
	USTOP2	= 0x20,		//2位停止位
	USTOP15	= 0x10,		//1.5位停止位
	USTOP1	= 0x08,		//1位停止位
	UNP		= 0x04,		//无校验
	UEP		= 0x02,		//偶校验
	UOP		= 0x01		//奇校验
}AuxFlag;

//串口通信参数结构体
typedef struct
{
	int Aux; /*串口号,参见enum ExtPort */	
	int iBaudRate; /*串口波特率,参见enum BaudRate*/
	int iAuxFlag; /*串口特性如数据位,停止位,校验位等*/
}RS232CONFIG;

//建立主机连接通讯参数结构体(以太网、WIFI、GPRS、CDMA)
typedef struct
{
	char	HostIp[2][16]; /*服务器IP地址*/
	int		HostPort[2]; /*服务端口号*/
	char	HostDns[50]; /*服务器域名*/
}HOSTCONFIG;

//通讯参数初始化联合结构体(以太网、WIFI、GPRS、CDMA、MODEM)
typedef struct
{
int iCommMode;	/*通讯方式,读取机器参数里的通讯方式,参见enum CommMode */
	union
	{
		PPPLOGINCONFIG	st_ppploginconfig ;	/*GPRS、CDMA参数,参考PPPLOGINCONFIG */
		IPCONFIG		 st_ipconfig;/*以太网参数,参考IPCONFIG */
		WIFICONFIG      st_wificonfig;/*WIFI参数,参考WIFICONFIG */
		MODEMCONFIG     st_modemconfig;/*MODEM通讯参数,参考MODEMCONFIG */
	} INITCONFIG;
	void ( *ShowFunc )( void ) ;			/*阻塞时显示的界面信息*/
	int   CycCount; /*循环次数*/
}COMMCONFIG;

//建立主机连接通讯参数联合结构体(以太网、WIFI、GPRS、CDMA、MODEM)
typedef struct
{
	int iCommMode;/*通讯方式,读取机器参数里的通讯方式,参见enum CommMode */ 
	
	HOSTCONFIG     st_hostconfig;	//参见 HOSTCONFIG
	
	void ( *ShowFunc )( void ) ;			/*阻塞时显示的界面信息*/
}COMMHOSTCONFIG;

//SSL协议枚举
typedef enum
{
	UPROTOCOL_TLSv1_2    //TLS版本1.2
}UProtocolType;

//SSL证书文件格式枚举
typedef enum
{
	USSL_FILE_DER,  //DER (ASN1) 文件格式 
	USSL_FILE_PEM   //PEM (BASE64) 文件格式 
}USSLFileFormat;

//SSL密码套件枚举
typedef enum
{
	CIPHER_RSA_NULL_MD5,   /*密码套件-RSA_NULL_MD5*/
	CIPHER_RSA_NULL_SHA,   /*密码套件-RSA_NULL_SHA*/
	CIPHER_RSA_RC4_40_MD5, /*密码套件-RSA_RC4_40_MD5*/
	CIPHER_RSA_RC4_128_MD5,  /*密码套件-RSA_RC4_128_MD5*/
	CIPHER_RSA_RC4_128_SHA,  /*密码套件-RSA_RC4_128_SHA*/
	CIPHER_RSA_RC2_40_MD5,  /*密码套件-RSA_RC2_40_MD5*/
	CIPHER_RSA_IDEA_128_SHA,  /*密码套件-IDEA_128_SHA*/
	CIPHER_RSA_DES_40_CBC_SHA,  /*密码套件-DES_40_CBC_SHA*/
	CIPHER_RSA_DES_64_CBC_SHA,  /*密码套件-DES_64_CBC_SHA*/
	CIPHER_RSA_DES_192_CBC3_SHA,  /*密码套件-DES_192_CBC3_SHA*/
	CIPHER_DH_RSA_DES_192_CBC3_SHA,  /*密码套件-DH_DSS_DES_192_CBC3_SHA*/
	CIPHER_DH_DSS_DES_40_CBC_SHA,  /*密码套件-DH_DSS_DES_40_CBC_SHA*/
	CIPHER_DH_DSS_DES_64_CBC_SHA,  /*密码套件-DH_DSS_DES_64_CBC_SHA*/
	CIPHER_DH_DSS_DES_192_CBC3_SHA,  /*密码套件-DH_DSS_DES_192_CBC3_SHA*/
	CIPHER_DH_RSA_DES_40_CBC_SHA,  /*密码套件-DH_RSA_DES_40_CBC_SHA*/
	CIPHER_DH_RSA_DES_64_CBC_SHA,  /*密码套件-DH_RSA_DES_64_CBC_SHA*/
	CIPHER_EDH_DSS_DES_40_CBC_SHA,  /*密码套件-EDH_DSS_DES_40_CBC_SHA*/
	CIPHER_EDH_DSS_DES_64_CBC_SHA,  /*密码套件-EDH_DSS_DES_64_CBC_SHA*/
	CIPHER_EDH_DSS_DES_192_CBC3_SHA,  /*密码套件-EDH_DSS_DES_192_CBC3_SHA*/
	CIPHER_EDH_RSA_DES_40_CBC_SHA,  /*密码套件-EDH_RSA_DES_40_CBC_SHA*/
	CIPHER_EDH_RSA_DES_64_CBC_SHA,  /*密码套件-EDH_RSA_DES_64_CBC_SHA*/
	CIPHER_EDH_RSA_DES_192_CBC3_SHA,  /*密码套件-EDH_RSA_DES_192_CBC3_SHA*/
	CIPHER_ADH_RC4_40_MD5,  /*密码套件-ADH_RC4_40_MD5*/
	CIPHER_ADH_RC4_128_MD5,  /*密码套件-ADH_RC4_128_MD5*/
	CIPHER_ADH_DES_40_CBC_SHA,  /*密码套件-ADH_DES_40_CBC_SHA*/
	CIPHER_FZA_DMS_NULL_SHA,  /*密码套件-FZA_DMS_NULL_SHA*/
	CIPHER_CK_FZA_DMS_FZA_SHA,  /*密码套件-CK_FZA_DMS_FZA_SHA*/
	CIPHER_CK_FZA_DMS_RC4_SHA,  /*密码套件-CK_FZA_DMS_RC4_SHA*/
	CIPHER_CK_ADH_DES_64_CBC_SHA,  /*密码套件-CK_ADH_DES_64_CBC_SHA*/
	CIPHER_CK_ADH_DES_192_CBC_SHA  /*密码套件-CK_ADH_DES_192_CBC_SHA*/
}UCipherSuite;

//GSM基站信息结构
typedef struct
{
	byte szMCC[5];     //移动国家代码,三位数,如中国460
	byte szMNC[5];     //移动网络号,如移动00,联通01
	byte szLAC[5];     //地区码
	byte szCID[5];     //小区码
	int  nSIG;        //信号强度,取到的如果是正值请加110,负值请加220
	int  nTAG;        //时间提前量,范围0-63
}BASESTATIONGSM;

//CDMA基站信息结构
typedef struct
{
	byte szMCC[5];       //移动国家代码,三位数,如中国460
	byte szSID[5];       //系统识别码,每个地级市只有一个sid,
	byte szNID[5];       //网络识别码,由各本地网管理,也就是由地级分公司分配,每个地级市可能有1到3个nid
	byte szBID[5];       //表示的是网络中的某一个小区,可以理解为基站
	int  nSIG;          //信号强度,取到的如果是正值请加110,负值请加220
	int  nTAG;          //时间提前量,0-63
}BASESTATIONCDMA;

//2.2.7	IC卡处理API

//IC卡类型枚举
typedef enum
{
	//	UICC_SLE4442,//预留
	//	UICC_SLE4428, //预留
	//	UICC_SLE4436, //预留
	//	UICC_AT24C64, //预留
	UICC_CPUCARD,
	UICC_MIFARE, //非接MIFARE卡,预留
	//	UICC_RFCPU_1356,      //非接CPU卡13.56M
	//	UICC_RFCPU_24        //非接CPU卡2.4G
} IccType;

//IC卡槽枚举
typedef enum
{
	USLOT_PSAM1,       //接触式PSAM卡槽1
	USLOT_PSAM2,       //接触式PSAM卡槽2
	USLOT_PSAM3,       //接触式PSAM卡槽3
	USLOT_PSAM4,       //接触式PSAM卡槽4
	USLOT_EXCARD,      //接触式用户卡槽
	USLOT_INRF,         //内置非接卡槽
	USLOT_EXRF_COM1,    //外置非接卡槽COM1口
	USLOT_EXRF_COM2,    //外置非接卡槽COM2口
	USLOT_EXRF_COM3,    //外置非接卡槽COM3口
	USLOT_EXRF_USB     //外置非接卡槽USB口
} SlotType;


//IC卡指令结构体
typedef struct
{
	//	byte OperType;	/* 参看enum - OperationType */
	byte CLA;			/* Class byte of the command message*/
	byte INS;			/* Instrution*/
	byte P1;			/* Parameter1*/
	byte P2;			/* Parameter2*/
	byte Lc;			/* length of being sent data*/
	byte Le;			/* length of expected data,实际返回值*/
	byte SW1;			/* status word1*/
	byte SW2;			/* status word2*/
	byte C_Data[256];	/* command data*/
	byte R_Data[256];	/* response data*/
} ICCAPDU;

//IC卡操作返回码枚举
typedef enum 	
{
	UICC_NORF            = -3,   // 无非接卡片
	//	UICC_EMPTY           = -3,   // 卡槽无卡片
	UICC_COMMAND_FAIL    = -2,   // 与卡片通讯错误
	UICC_FAIL            = -1,   // 操作失败
	UICC_OK              =  0    // 操作成功
}ICCStatus;

//2.2.9	文件操作API

//文件句柄重定义
typedef int FILE_HANDLE;
//文件存储位置枚举
typedef enum /*文件存储位置,私有表示存储在当前子应用目录下,仅当前子应用可访问到;公有表示存储在公共位置,所有子应用都可访问*/
{
	FILE_PRIVATE,       //私有,此文件存储在当前子应用目录下,其他子应用不可访问
		FILE_PUBLIC         //共有,此文件存储在公共位置,所有子应用都可访问
}FILELOCATION;
//文件打开模式定义
typedef  enum
{
	FILE_RDONLY = 0, //只读,不存在返回错
		FILE_WRONLY,     //只写,不存在返回错
		FILE_RDWR,       //读写,不存在返回错
		FILE_APPEND,     //追加,不存在则创建,存在时指针指向文件尾
		FILE_CREAT,      //创建,已存在时删除重建
}FileFlags;

//文件指针定位
typedef  enum
{
	FILE_SEEK_SET = 0,       //到文件头
		FILE_SEEK_CUR,           //到当前位置
		FILE_SEEK_END            //到文件尾
}FileSeekFlags;

//文件操作返回值
typedef enum
{
	UFILE_NO_EXIST      = -12,             //指定的文件不存在
	UFILE_PARAERROR     = -11,            //参数错
	UFILE_NO_RECORD		= -10,             //记录未找到
	UFILE_REMOVE_FAIL	= -9,              //移动文件错误
	UFILE_CLOSE_FAIL	= -8,              //关闭文件错误
	UFILE_DELETE_FAIL	= -7,              //删除文件记录错误
	UFILE_SEEK_FAIL		= -6,              //定位文件指针错误
	UFILE_READ_FAIL		= -5,              //读错误
	UFILE_WRITE_FAIL	= -4,              //写错误
	UFILE_CREATE_FAIL 	= -3,              //文件重建错误
	UFILE_OPEN_FAIL  	= -2,              //打开错误
	UFILE_FAIL			= -1,              //文件操作失败
	UFILE_SUCCESS       =  0               //文件操作成功
}FileRet;

//文件操作搜索条件结构
typedef struct
{
	uint   StartOffset;  //从结构的第几个字节开始查找,起始位置为0
	uint   Length;       //比较字节长度
	byte*   SearchKey;    //查找关键字
}DBSEARCOND;

//2.2.10	密码键盘类API

//PinPad类型枚举
typedef enum
{
	UPP_INT		=0,     /* 内置密码键盘 */
	UPP_EXT_COM1,		     /* COM1口外置密码键盘 */
	UPP_EXT_COM2,		     /* COM2口外置密码键盘 */
	UPP_EXT_USB		     /* USB口外置密码键盘 */
}PinPadType;

//加密模式
typedef enum
{
	UDES_TYPE_SINGLE	=1,	/* 单DES */
	UDES_TYPE_TRIPLE,		/* 3DES */
	UDES_TYPE_SM4			/* 国密SM4 */
}DesType;

//密钥类型
typedef enum
{
	UKEY_TYPE_MST		=0,	/* 主密钥 */
	UKEY_TYPE_PIN,			/* PIN工作密钥 */
	UKEY_TYPE_MAC,			/* MAC工作密钥 */
	UKEY_TYPE_TRACK,          /*TRACK工作密钥*/
	UKEY_TYPE_TEST          /*测试工作密钥*/
}KeyType;

//PINPAD密码输入接口返回值
typedef enum
{
	UPIN_TIMEOUT     = -3,   //密码输入超时
	UPIN_ABORT		= -2,	// 操作员放弃输入
	UPIN_ERROR		= -1,	// 输入错误 
	UPIN_ESC			=  0,	// 用户取消输入
	UPIN_SUCCESS		=  1,	// 输入成功 
	UPIN_NONE		=  2	// 无密码,既相当于BYPASS 
}PinInputStatus;

//非PIN输入函数返回值定义
typedef enum
{
	UPP_ERROR_SM	 = -10,				//国密密钥/算法处理失败
	UPP_KEY_EXIST    = -9,              //密钥组已存在
	UPP_DECLINED     = -8,               //操作被拒绝
	UPP_ERROR		= -7,				// 错误 
	UPP_FAILURE		= -6,				// 系统级别的失败 
	UPP_ESCAPE		= -5,				// 操作被退出 
	UPP_TIMEOUT		= -4,				// 超时(外置键盘通讯)
	UPP_MAC_ERROR	= -3,				// 计算MAC出错 
	UPP_ERR_PAN		= -2,				// 主账号有误 
	UPP_ABORT		= -1,				// 用户放弃 
	UPP_SUCCESS		= 0				    // 成功 
}PPStatus;

//2.2.11	EMV类API

#define  UMAX_TERMINAL_APPL    20         //卡片终端共同支持的最大应用数
#define  UMAX_EXCEPTION_BIN_COUNT	100  //卡BIN黑名单最大数
//EMV参数操作返回枚举
typedef enum
{ 
	UEMV_PRM_ERR  =-4,    //EMV参数错
	UEMV_PRM_NOT_FOUND=-3,		    //EMV参数未找到
	UEMV_PRM_CAPK_CHK_HASH_FAIL=-2,	//公钥HASH校验错误
	UEMV_PRM_FAIL=-1,				//EMV参数操作失败
	UEMV_PRM_OK=0             		//EMV参数操作成功
} ParamStatus;

//EMV交易状态枚举
typedef enum
{
	UEMV_QPBOC_DODGE          = -20,       /**<闪卡处理失败*/
	UEMV_EC_DECLINED          = -19,       //电子现金脱机拒绝
	UEMV_APP_NOACCEPT         = -18,       //应用不接受,可重新选择
	UEMV_SCRIPT_FAIL          = -17,		//发卡行脚本执行失败
	UEMV_ARPC_FAIL            = -16,		//发卡行认证失败
	UEMV_DECLINED             = -15,		//交易拒绝
	UEMV_CANCEL               = -14,		//交易取消
	UEMV_ONLINE               = -13,		//交易应联机
	UEMV_CVM_FAIL             = -12,     //持卡人验证失败
	UEMV_APP_EXPIRED          = -11,     //应用已失效
	UEMV_APP_EFFECT           = -10,     //应用尚未生效
	UEMV_AUTH_FAIL            = -9,      //数据认证失败
	UEMV_FALLBACK             = -8,		//交易fallback
	UEMV_APP_BLOCK            = -7,		//应用已锁
	UEMV_CANDIDATELIST_EMPTY  = -6,		//无共同应用
	UEMV_PARA_ERR             = -5,      //参数错
	UEMV_CARD_BLOCK           = -4,      //卡片已锁
	UEMV_COMMAND_FAIL         = -3,      //读卡失败
	UEMV_CARD_REMOVED         = -2,		//交易中卡片被移开
	UEMV_FAIL 				 = -1,		//执行失败
	UEMV_OK					 =  0,		//执行成功
	UEMV_OTHER_INTERFACE= 1,//请尝试其他通信界面
	UEMV_QPBOC_OFFLINE   = 2,//非接触QPBOC交易脱机接受
	UEMV_QPBOC_ONLINE          = 3,  //非接触QPBOC交易联机
	UEMV_PBOC_ONLINE           = 4,//非接触PBOC交易联机
	//UEMV_MSD_ONLINE           = 5//非接触MSD交易联机
	UEMV_EC_ACCEPT             = 6,       //电子现金脱机接受
	UEMV_OFFLINE_ACCEPT        = 7        //标准流程脱机接受
} EmvStatus;

//终端参数结构体
typedef struct { 
    char    TermCap[3] ;           /*终端性能 '9F33'*/
    char    AdditionalTermCap[5] ; /*终端附加性能*/
    char    IFDSerialNum[9] ;    /*IFD序列号 '9F1E'*/
    char    TermCountryCode[2] ;  /*终端国家代码 '9F1A'*/
    char    TermID[9] ;       /*终端标识 '9F1C'*/
    char    TermType ;       /*终端类型 '9F35'*/
    char    TransCurrCode[2] ;   /*交易货币 '5F2A'*/
    char    TransCurrExp;      /*交易货币指数 '5F36'*/
    //PSE Selection
    char    bPSE;          /*是否支持选择PSE 1*/
    char    bCardHolderConfirm;   /*是否支持持卡人确认 1*/
    char    bPreferedOrder;     /*是否支持优选显示 1*/
    char    bPartialAID;       /*是否支持部分AID匹配 1*/
    char    bMultiLanguage;     /*是否支持多语言 0*/
    char    bCommonCharset;     /*是否支持公共字符集 0*/
    //Data Authentication
    char    bIPKCValidtionCheck;   /*是否检查发卡行公钥认证有效性 1*/
    char    bContainDefaultDDOL;   /*是否包含默认DDOL 1*/
    char    bCAPKFailOperAction;   /*CAPK读取出错时是否需要操作员干预 1*/
    char    bCAPKChecksum;      /*是否进行CAPK校验 1*/
    //Cardholder Verification Method
    char    bBypassPIN;       /*是否支持跳过PIN输入 (须改流程,待定)*/
    char    bGetDataForPINCounter;  /*PIN尝试计数器是否支持GetData 1*/
    char    bFailCVM;        /*是否支持错误的CVM(1必须为Yes)*/
    char    bAmountBeforeCVM;     /*CVM前是否已知金额 1*/
    //Term Risk Management
    char    bLimitFloorCheck;    /*是否进行最低限额检查 1*/
    char    bRandomTransSelect;   /*是否进行随机交易选择 1*/
    char    bValocityCheck;     /*是否进行频度检查 1*/
    char    bTransLog;        /*是否记录交易日志 1*/
    char    bExceptionFile;     /*是否支持卡片黑名单 1*/
    char    bTRMBaseOnAIP;      /*终端风险管理是否基于应用交互特征 1*/
    //Terminal Action Analysis
    char    bTerminalActionCodes;  /*是否支持终端行为代码 1*/
    char    bDefActCodesBefore1stGenAC; /*缺省行为代码是否先于FirstGenerateAC ?*/
    char    bDefActCodesAfter1stGenAC;  /*缺省行为代码是否后于FirstGenerateAC ?*/
    //Completion Processing
    char    bForceOnline;      /*是否允许强制联机 1*/
    char    bForceAccept;      /*是否允许强制接受交易 1*/
    char    bAdvices;         /*是否支持通知 0*/
    char    bIISVoiceReferal;    /*是否支持发卡方发起的语音参考 ?*/
    char    bCardVoiceReferal;    /*是否支持发卡方发起的语音参考 ?*/
    char    bBatchDataCapture;    /*是否支持批数据采集*/
    char    bDefaultTDOL;      /*是否有缺省TDOL*/
    //Exception Handling
    char    cEntryModeUsingMagStripe; /*IC卡故障而只能刷卡时POSEntryMode值*/
    char    bAccountSelect;     /*是否支持账号选择*/
}TERMCONFIG; 


//EMV_AID参数结构体
typedef struct
{
	byte AID[16];						//AID
	byte AID_Length;						//AID长度
	byte bAppSelIndicator;				//应用选择指示符
	byte bTerminalPriority;				//终端优先级
	/* Domestic */
	byte bMaxTargetDomestic;				/*偏置随机选择的最大目标百分数*/
	byte bTargetPercentageDomestic;		/*随机选择的目标百分数*/
	byte abTFL_Domestic[4];				/* 终端最低限额 */
	byte abThresholdValueDomestic[4];		/*偏置随机选择的阈值*/
	/* International */
	byte bMaxTargetPercentageInt;			/*偏置随机选择的最大目标百分数*/
	byte bTargetPercentageInt;				/*随机选择的目标百分数*/
	byte abTFL_International[4];			/* 终端最低限额 */
	byte abThresholdValueInt[4];			/*偏置随机选择的阈值*/
	
	byte abTerminalApplVersion[4];			/* 终端应用版本 */
	byte abMerchantCategoryCode[2];		/* 商户类别代码tag: 9F15 */        
	byte bTransactionCategoryCode;		/* 交易类别代码Europay only, tag: 9F53 */
	byte abTrnCurrencyCode[2];			/* 货币代码tag: 5F2A */
	byte abTerminalCountryCode[2];		/* 国家代码终端tag: 9F1A */
	byte TAC_Default[5];					/* TAC缺省data format (n 5) */    
	byte TAC_Denial[5];					/* TAC拒绝data format (n 5) */    
	byte TAC_Online[5];					/* TAC联机data format (n 5) */  
	byte abDDOL[20];					/* DDOL */
	byte DDOL_Length;					/* DDOL长度 */
	byte abTDOL[20];					/* TDOL */
	byte TDOL_Length;					/* TDOL长度 */
	byte abTrnCurrencyExp;				/* tag: 5F36 */
	byte abEC_TFL[6];					/* 终端电子现金交易限额tag: 9F7B n12*/
	byte TerminalType;					/* 终端类型data format (n 3) */
	byte TerminalCap[3];					/* 终端能力data format (n 3) */
	byte AddTerminalCap[5];				/* 终端附加性能data format (n 3) */
	byte abRFOfflineLimit[6];		/*非接触脱机最低限额DF19*/
	byte abRFTransLimit[6];		/*非接触交易限额DF20*/
	byte abRFCVMLimit[6];				/*终端执行CVM限额DF21*/
	byte abTransProp[4];			    /*终端交易属性9F66*/
	byte bStatusCheck;          	    /*非接触状态检查, 0x00-不检查,0x01-检查*/
	byte abAcquirerID[6];         	    /*收单行标识9F01*/
}APPLICATIONPARAMS;

//EMV_AID参数总结构体
typedef struct
{
	byte bTermAppCount;//实际AID参数个数
	APPLICATIONPARAMS TermApp[UMAX_TERMINAL_APPL];
}TERMINALAPPLIST;

//CA公钥结构体
typedef struct
{								
	byte RID[5];						/* Registered Application Provider Identifier */
	byte CA_PKIndex;				/* 认证中心公钥索引 */
	byte CA_HashAlgoIndicator;		/* 认证中心公钥哈什算法标识 */
	byte CA_PKAlgoIndicator;			/* 认证中心公钥算法标识 */
	byte LengthOfCAPKModulus;		/* 认证中心公钥模长度 */
	byte CAPKModulus[248];			/* 认证中心公钥模 */
	byte LengthOfCAPKExponent;		/* 认证中心公钥指数长度 */
	byte CAPKExponent[3];			/* 认证中心公钥指数 */
	byte ChecksumHash[20];			/* 认证中心公钥校验值 */
	byte CAPKExpDate[3];				/* 认证中心公钥有效期 */
}CAPUBLICKEY;

//EMV回调函数
typedef struct
{
	int (*EMV_InputPasswd)(char cType, ushort chance,char *pszPin);
	int (*EMV_InputAmount)(byte *Amount);
}STEMVCALLBACKFUN;
//非接模式枚举
typedef enum
{
	UEMV_RF_PBOC       = 0,     //非接PBOC标准流程
	UEMV_RF_QPBOC      = 1,     //非接qPBOC
	//UEMV_RF_MSD        = 2,//非接MSD
	UEMV_RF_PBOC_SINGLE     = 3      //非接PBOC简化流程
}EmvRFType;

//卡BIN黑名单结构体
typedef struct
{
  byte bBINLen;
  byte abBIN[10];		       /* 5A: BCD */
}EMVEXCEPTIONBIN;

//卡BIN黑名单总结构体
typedef struct
{
  byte            bCount;  //实际数量
  EMVEXCEPTIONBIN ExpBIN[UMAX_EXCEPTION_BIN_COUNT];
}EMVEXCEPTIONBINLIST;

//交易路径类型
#define CLSS_VISA_QVSDC          2   // qPBOC方式
#define CLSS_VISA_VSDC           3   // 完整非接PBOC方式

//AC类型
#define AC_AAC                0x00
#define AC_TC                 0x01
#define AC_ARQC               0x02

//持卡人认证方式
#define RD_CVM_NO             0x00   // no CVM
#define RD_CVM_SIG            0x10   // signature
#define RD_CVM_ONLINE_PIN     0x11   // online PIN

//内核类型
#define KERNTYPE_DEF             0
#define KERNTYPE_JCB             1
#define KERNTYPE_MC              2
#define KERNTYPE_VIS             3
#define KERNTYPE_PBOC            4
#define KERNTYPE_AE              5
#define KERNTYPE_RFU             6

//非接交易预处理结构
typedef struct
{
    ulong ulTermFLmt;       /* 终端脱机限额*/
    ulong ulRdClssTxnLmt;   /* 读卡器非接交易限额 */
    ulong ulRdCVMLmt;       /* 读卡器CVM限额 */
    ulong ulRdClssFLmt;     /* 读卡器非接脱机限额*/
    byte aucAID[17];        /*应用AID */
    byte ucAidLen;          /*应用AID长度*/
    byte ucKernType;        /*应用内核号
	KERNTYPE_DEF: 内核根据RID自行匹配
	KERNTYPE_JCB: JCB.
	KERNTYPE_MC: MASTERCARD.
	KERNTYPE_VIS: VISA.
	KERNTYPE_PBOC: PBOC.
	KERNTYPE_AE: American Express.*/
    // payWave				//QPBOC的参数也设置在这一块
    byte ucCrypto17Flg;		/* MSD CVN17是否支持标志, 0-不支持,1- 支持*/
    byte ucZeroAmtNoAllowed;/* 金额为0检查标志,0-检查金额为0,且金额如果为0则会请求联机;1-检查金额为0,且不允许金额为0 ;2-不检查金额是否为0*/
    byte ucStatusCheckFlg;  /* 状态检查标志, 0-不支持 (不检查金额,不修改TTQ),1- 支持 (此时如果交易金额为1元,则内核需强制修改TTQ为请求联机)*/
    byte aucReaderTTQ[5];   /* 终端交易属性TTQ*/
    // common
    byte ucTermFLmtFlg;		/* 终端脱机限额检查标志,0-不检查, 1-检查且限额存在, 2-检查但限额不存在 */
    byte ucRdClssTxnLmtFlg;		/* 读卡器非接交易限额,检查标志,0-不检查, 1-检查且限额存在, 2-检查但限额不存在*/
    byte ucRdCVMLmtFlg;		/* 读卡器CVM限额检查标志,0-不检查, 1-检查且限额存在, 2-检查但限额不存在*/
    byte ucRdClssFLmtFlg;		/* 读卡器非接脱机限额检查标志,0-不检查, 1-检查且限额存在, 2-检查但限额不存在*/
    byte aucRFU[2];
} Clss_PreProcInfo;

//非接交易相关参数结构
typedef struct
{
    ulong ulAmntAuth;          // 授权金额(ulong)
    ulong ulAmntOther;         // 其他金额(ulong)
    ulong ulTransNo;           // 交易序列计数器(4 BYTE)
    byte ucTransType;          // 交易类型'9C'
    byte aucTransDate[4];      // 交易日期 YYMMDD	3字节BCD结尾补0x00
    byte aucTransTime[4];      // 交易时间 HHMMSS	3字节BCD结尾补0x00
} Clss_TransParam;

//应用信息结构体
typedef struct
{
    char  szAID[32 + 1];          //AID  ASCII格式 "\0"结束
    char  szAppName[32 + 1];      //应用名 ASCII格式 "\0"结束
} STAPPINFO;

//回调函数结构体2
typedef struct
{
    int (*EMV_InputPasswd)(char cType, ushort chance, char *pszPin);
    int (*EMV_InputAmount)(byte *Amount);
    int (*EMV_cVerifyIDCard)(void); //返回值含义 请参考函数原型说明
    int (*EMV_cSelectAapp)(STAPPINFO *pstAPPList, int nAPPNum); //返回值含义请参考函数原型说明
    int (*EMV_cqPBOCDodgeRefresh)(void *psCmdBuf);
    int (*EMV_cqPBOCDogeRemoveTrace)(void);
} STEMVCALLBACKFUN2;

//2.2.12	TMS类API

#define UMAX_APP_COUNT  30  //应用最大数量
#define UMAX_MODULE_COUNT  800  //下载文件最大数量
//应用信息结构体
typedef struct
{
	char AppName[20+1];          //应用名
	char AppDispName[20+1];     //应用显示名,如果存在01000006标签,则送标签内容
	char AppVar[15+1];          //应用版本号,TMS系统只支持15位版本号
	char TerminalID[8+1];//终端号
	char ShopId[15+1];//商户号
	byte bisMainApp;           //是否主控应用,0-否,1-是
}UAPPINFO;

//应用信息总结构体
typedef struct
{
	byte		bCount;                       //实际应用数
	UAPPINFO	AppInfo[UMAX_APP_COUNT];	//参见struct UAPPINFO
}UAPPINFOLIST;

//模块类型枚举
typedef enum
{
	UMODULE_FILE    = 0,       //文件,2-5的文件都可使用0,由主控来区分
	UMODULE_PARAFILE = 1,      //参数文件
	UMODULE_TRADE   = 2,       //业务模块
	UMODULE_PUBLIC  = 3,       //公共模块
	UMODULE_API     = 4,       //API模块
	UMODULE_PRIVATE = 5,       //厂家私有库
	UMODULE_DATA    = 6,       //数据类文件(预留)
	UMODULE_DRIVER  = 7,//硬件驱动(预留)
	UMODULE_OS      = 8,       //底层OS(预留)
	UMODULE_APP     = 9        //应用,可执行文件
}UModuleType;

//模块信息结构体
typedef struct
{
	char ModuleName[50];    //模块名
	int  ModuleType;        //参见enum UModuleType
	char AppName[20+1];      //应用名,表明该文件属于某个应用
}UMODULEINFO;

//模块信息总结构体
typedef struct
{
	ushort	nCount;								//实际下载文件数
	UMODULEINFO ModuleInfo[UMAX_MODULE_COUNT];	//参见struct UMODULEINFO
}UMODULEINFOLIST;

//TMS下载通讯类型枚举
typedef enum
{
	UTMS_BYRS232 = 1,  //串口
	UTMS_BYMODEM     = 2,  //MODEM异步
	UTMS_BYETHENET   = 3,  //有线以太网
	UTMS_BYWIFI      = 4,  //WIFI
	UTMS_BYGPRS      = 5,  //GPRS,WCDMA(wcdma和gprs参数相同)
	UTMS_BYCDMA      = 6,  //CDMA
	UTMS_BYMODEMPPP  = 7,  //MODEMPPP拨号后走TCPIP
	UTMS_BYUSB       = 8   //USB
}UTMSComType;

//TMS下载通讯结构
typedef struct
{
	unsigned char ucCOMMType;  /*通信类型：参见 enum UTMSCOMTYPE*/
	unsigned char ucTPDUFlag;  /*TPDU存在标识: 0-无,1-有*/
	unsigned char aucTPDU[5];  /*TPDU号码(需标识含TPDU)*/
	unsigned int  uiSockID; /*tcpip通讯Socket ID UTMSCOMTYPE中3,4,5,6,7*/
	unsigned long hCommHandle; /*通讯句柄 UTMSCOMTYP中 1,2,8*/
/*以下部分为联迪POS必须用到的参数,其他厂家不用可丢弃,有用到或者需要添加参数请及时反应*/
	unsigned char ucPackNum; /*下载阶段服务器端连续发送下载包个数：最小1,最大8*/
	unsigned int uiFrameLen;/*下载阶段传输数据帧的长度(单位：字节)*/
	unsigned char ucSyncFlag; /*强制终端与服务端执行一收一发的报文交互模式：0-关闭 1-打开*/
	unsigned char ucIfCheck; /*下载阶段数据校验标识：0-不校验  1-校验*/
	unsigned char ucBreakType;  /*下载阶段是否允许按键(取消/清除键)中断下载0-不允许 1-允许*/
	unsigned int  uiReTime; /*通讯报文接收超时后,重新接收次数(即服务器重发报文次数)*/
	unsigned int  uiTimeoutMs; /*单个通讯报文接收超时时间(单位：毫秒)*/
	unsigned int   uiDelayTime; /*终端每个发送数据包之前的延时(单位：毫秒)*/
	unsigned int   uiSlotTime;  /*服务器端连续发包间隔时间(单位：毫秒)*/
	unsigned char  auReserver[100];  /*预留域*/
	unsigned int   uiRFULen; /*扩展空间长度*/
	void        *pvRFU;  /*扩展空间指针*/
	unsigned char DlTxnType;	/*下载交易类型 0-初始化,1-换机,2-联机报到*/
}UTMSPARAMETERS;

//TMS类API返回值枚举
typedef enum
{	
	UTMS_TIMEOUT			= -3,        //超时
	UTMS_QUIT				= -2,	//取消
	UTMS_FAIL                = -1,       //失败
	UTMS_OK                  =  0        //成功
}UTMSStatus;

#define KEY_BUF_SIZE		128		//键盘输入缓冲的长度
#define	ITWELLSYSINFOLEN	40		//用
#define SWIPEDANDINICEVENT	0xFF	//待机界面有磁卡操作
//#define INICEVENT			0xF0	//待机界面插入IC的操作
#define XGDOK				0X01

#define BEEPERROR			1		//蜂鸣器异常叫
#define BEEPNORMAL      	0		//蜂鸣器正常叫
#define DECRYP				0		//解密
#define ENCRYP				1		//加密

//pos的工作状态，用于披上送的处理
#define WORK_STATUS			0		//非批上送状态，工作状态
#define	UPLOGRMB			1		/*用于批上送时选择不同的交易纪录*/
#define UPLOGFRN			2
#define UPLOGALL			3
#define UPLOGDETAILTYPE1	4		//对账平后继的单条上送
#define UPLOGDETAILTYPE2	4		//对账不平后继的单条上送

#define		PIN_PED			0x00	//内置
#define		PIN_PP			0x01	//外置

#define		TIMEOUT			-2		//超时

#define		COM_PAD_NO		0x00			//rs232 A
#define		PINPADCOM		0x01			//pinpad
#define		COM_RS232B_NO	0x02			//rs232 B
#define		USB_DEVICE		0x04
#define		USB_HOST		0x06

#define		MAX_LCD_LINENUM 			5	//LCD可显示的最大行数

#if (defined(V50X_MACHINE))
#define		MAX_LCDWIDTH				26
#else
#define		MAX_LCDWIDTH				20
#endif

#define		MAX_MENUNAME_LEN			14		//菜单名最大长度
#define		SEARCH_DIRECTION_NEXT 		1
#define		SEARCH_DIRECTION_PREV 		0
#define		MCARDNO_MAX_LEN 			19		//卡号的最大长度
#define		MAX_AMT_LEN					12		//最大金额长度
#define		MAX_PWD_LEN 				8		//最大密码长度
#define		BASE_YEAR 					2000	//基准年
#define		INPUT_TIMEOUT_VAL			30		//30s 输入超时值
#define		INPUT_INFINITE				-1
#define		INPUT_TIMEOUT 				-2		//输入超时代码
#define		SCRIPT_SUCCESS				0		//脚本运行成功
#define		SCRIPT_CANCEL 				-1		//脚本被取消
#define		SCRIPT_ERROR				-3		//脚本格式错误
#define		SCRIPT_NONEXIST				-4
#define		SCRIPT_CHECKERR				-5
#define		SCRIPT_MEMLACK				-6

#define MAX_RSA_MODULUS_LEN		512   // RSA最大模长度
#define MAX_RSA_PRIME_LEN		256   // RSA最大模素数长度

// RSA公钥结构定义
typedef struct{
unsigned int uiBits;   //模位数，bit单位
unsigned char ucModulus[MAX_RSA_MODULUS_LEN];   //模
unsigned char ucExponent[MAX_RSA_MODULUS_LEN];  //指数
}RSAPUBLICKEY;
 
//RSA私钥结构定义
typedef struct{
unsigned int uiBits;    //模位数，bit单位
unsigned char ucModulus[MAX_RSA_MODULUS_LEN];   //模
unsigned char ucPublicExponent [MAX_RSA_MODULUS_LEN];  //公钥指数
unsigned char ucExponent[MAX_RSA_MODULUS_LEN];   //私钥指数
unsigned char ucPrime[2][MAX_RSA_PRIME_LEN];     //pq素数，素数因子
unsigned char ucPrimeExponent[2][MAX_RSA_PRIME_LEN]; //CRT指数，素数与指数除法值
unsigned char ucCoefficient[MAX_RSA_PRIME_LEN];  //CRT系数，素数与素数除法值
}RSAPRIVATEKEY;

#endif

