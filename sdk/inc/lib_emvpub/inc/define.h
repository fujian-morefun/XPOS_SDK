#ifndef _DEFINE_H_
#define _DEFINE_H_

#include<string.h> 
#include<ctype.h>  
//modified by zhiyu 0923
//#include<malloc.h>  
#include<limits.h>  
#include<stdio.h>   
#include<stdlib.h>  
#include<math.h>  
#include<time.h>
/**<api*/

//#include "mf_basic.h"
#include "pub_define.h"

#include "emv_tag.h"
#include "emv_err_code.h"

/**<publib*/
#include "struct_hashtable.h"
#include "ex_convert.h"
#include "dev_file.h"
#include "printfdebug.h"


//包含malloc的头文件 add by zhiyu 0929 
#include "pub/common/misc/inc/mfmalloc.h"

//typedef unsigned char BYTE;

#define ENTRY_POINT_VERSION			"EntryPoint_2019-08-27_XP"
#define EMV_VERSION			"EMV4.3H_2019-08-27_XP"	
//#define EMV_PINPAD_VERSION	"EMV4.3G_PINPAD-V1.01"
//#define  L2_APPROVE  1  //1 - L2认证时宏定义开启   0-默认提交生产用（SVN只上传为0的版本）此前第三方应用发现有卡片返回tag一样导致中止

//#define AUTO_APPROVE	1 //自动化测试开关 （连BCTC的测试后台时开启）
#ifndef AUTO_APPROVE
//#define		QUICS	1	//QUICS宏定义
#ifndef		QUICS		
#define		VCPS		//vcps宏定义
#endif
#endif
#define AMEX

#define MAXLEN_PAN 19
#define MAXLEN_TRACK2 37

#define MAXLEN_FILE		255
#define MAXDOL_LEN		256
#define MAXLEN_ICCRESP  MAXDOL_LEN//512 
 
#define TABLESIZE(table)    (sizeof(table)/sizeof(table[0]))

typedef enum {
	GAC_AAC = 0,	
	GAC_ARQC,
	GAC_TC,
	GAC_AAR,
	GAC_TOTAL
}E_GAC;

#define FALSE 0
#define TRUE (!FALSE)


#define SUCC		0
#define FAIL		(-1)
#define QUIT		(-2)
#define TIMEOUT		(-3)
#define GOTO		(-4)
#define UNKNOW		(-5)
#define UNSUPPORT	(-6)
#define TERMINATE	(-7)
#define GOTOCONTACT (-8)
#define GOTOOTHER	(-9)
#define	GOTOUPCARD	(-10)
#define GOTO_TRYAGAIN		(-11)		//重新挥卡
#define GOTO_CDV_TRYAGAIN	(-12)		//移动设备重新挥卡
#define L1_ERROR	(-13)				//L1错误码--保存L1错误码,L1的错误码是负值,可能会和nRet重复

#define GOTO_DPAS_ZIP	(-14)
#define GOTO_DPAS_MS	(-15)
#define GOTOOTHERCARD	(-16)
#define RP_GOTO_2_TAP	(-17)
//#define ASSERT_FAIL(e) \
//	if ((e) == FAIL)\
//	{\
//		return FAIL;\
//	}
//	
//#define ASSERT_QUIT(e) \
//	if ((e) == QUIT)\
//	{\
//		return QUIT;\
//	}
//#define ASSERT_UNSUCC(e) \
//	if ((e) != SUCC)\
//	{\
//		return FAIL;\
//	}\
//

#define EQ(a,b) ((a)==(b))  
#define LT(a,b) ((a)<(b))  
#define LQ(a,b) ((a)<=(b))


//#define MAXLEN_AUTHDATA   1500  
#define MAXLEN_AUTHDATA   2048+512		//paypass案例脱机签名数据2048--恢复IC卡公钥计算hash空间2048+512

#ifdef M919_DEVICE
	#define MAXNUM_AIDLIST 5		//根据PBOC3.0终端送检指南要求，终端AID最多不超过20个
#else
	#define MAXNUM_AIDLIST 20		//根据PBOC3.0终端送检指南要求，终端AID最多不超过20个
#endif


#ifdef WIN32
//#define __func__ "func" 
#endif

typedef enum {
	ERR_NONE = 0,	
	ERR_PARAM,	
	ERR_COMM,		
	ERR_MEM,		

	ERR_TIMEOUT,	
	ERR_INTR,	

	ERR_UNSUPPORT,	
	ERR_USR_CANCEL,	

	ERR_I2C,			

	ERR_KEY_INVALID,	
	ERR_KEY_FETCH,	
	ERR_KEY_SAVE,		
	ERR_AUTH_FAILED,	
	ERR_COND_NOTMET,	
	ERR_KEY_LIMIT,		

	ERR_RSA_FAILED,	
	ERR_ICC_DEV,		
	ERR_OFFLINE_PIN_FAILED,	
	ERR_PIN_EMPTY,	

	ERR_CONNECT, 
	ERR_SENDDATA, 
	ERR_NODATA, 
	ERR_MEMOPER, 
	ERR_DATATOOBIG, 

	ERR_MAX
}ERR_CODE;

//char szEmvData[8000];

/**< --------------------------emv_off_auth-------------------------------------------------------------*/
#define MAXLEN_MODULUS 		248
#define CERT_HEADER		0x6A	/**<证书数据头*/
#define CERT_TAILER		0xBC	/**<数据尾*/

/**<证书类型，其中低4字节为证书格式*/
#define TYPE_CERT_ISSPK		0x02		/**<发卡行公钥证书格式*/
#define TYPE_CERT_SSAD		0x03		/**<签名静态应用数据格式*/
#define TYPE_CERT_ICCPK		0x04		/**<IC卡公钥证书格式*/
#define TYPE_CERT_DSD		0x05		/**<动态认证动态签名数据格式*/
#define TYPE_CERT_FDSD		0x06		/**<快速动态认证动态签名数据格式*/
#define TYPE_CERT_ODADSD		0x95		/**<ODA动态认证动态签名数据格式*/
#define TYPE_CERT_CDSD		0x25		/**<复合认证动态签名数据格式*/
#define TYPE_CERT_PIN		0x24		/**<PIN证书格式*/
#define TYPE_CERT_QDDA		0x26		/**RUPAY QDDA认证*/

#define	TYPE_CERT_SM_ISSPK	0x12		/**< 采用SM2算法的发卡行公钥证书格式*/
#define	TYPE_CERT_SM_SSAD	0x13		/**< SM2签名静态应用格式*/
#define TYPE_CERT_SM_ICCPK	0x14		/**<SM2算法IC卡公钥证书格式*/
#define TYPE_CERT_SM_DSD	0x15		/**<SM2算法动态认证动态签名数据格式*/
#define TYPE_CERT_SM_ODADSD	0xA5		/**SM2<ODA动态认证动态签名数据格式*/
#define TYPE_CERT_SM_FDSD	0x16		/**<快速动态认证动态签名数据格式*/
#define ALG_PK_NONE	Ox00
#define ALG_PK_RSA		0x01
#define ALG_PK_SM2		0x04

#define ALG_HASH_SHA1	0x01
#define ALG_HASH_SM3	0x07

typedef struct
{
	char cIndex; 				/**<注册中心公钥索引*/
	char szCert[248];		/**<公钥证书*/
	int	 nCertLen;		/**<公钥证书长度*/
	char szpkRemainder[248];	/**<公钥余项*/
	int	nRemainderLen;		/**<公钥余项长度*/
	char	szIsspkExp[3];			/**<公钥指数*/
	int	nExpLen;			/**<公钥指数长度*/
	char	szpan[10];			/**<IC卡主帐号*/
	int	nPanLen;			/**<主帐号长度*/
}STCERT;

typedef struct
{
	uchar uiLen;
	uchar ucModulus[MAXLEN_MODULUS];  
	uchar ucExponent[3];
}STRSA;

/**< --------------------------emv_cardholder_verify-----------------------------------------------------*/
#define MAXLEN_CVM	252

#define CVM0_CON_FAIL				0x00	/**<CVM处理失败*/
#define CVM0_CON_PLAINPIN			0x01	/**<IC卡进行的明文PIN验证*/
#define CVM0_CON_ONLINEPIN			0x02	/**<联机加密PIN验证*/
#define CVM0_CON_PLAINPIN_SIG		0x03	/**<IC卡进行的明文PIN验证和签名（纸上）*/
#define CVM0_CON_ENCIPHPIN			0x04	/**<IC卡进行的加密PIN验证*/
#define CVM0_CON_ENCIPHPIN_SIG		0x05	/**<IC卡进行的加密PIN验证和签名（纸上）*/
#define CVM0_CON_SIG				0x1E	/**<签名（纸上）*/
#define CVM0_CON_NOCVM				0x1F	/**<无需CVM*/
#define CVM0_CON_CERT				0x20	/**<持卡人出示证件*/

#define CVM1_CON_ALL		0x00	/**<总是*/
#define CVM1_CON_ATM		0x01	/**<ATM如果是现金或返现*/
#define CVM1_CON_NOCASH	0x02	/**<如果不是现金或返现*/
#define CVM1_CON_CVM		0x03	/**<如果终端支持CVM*/
#define CVM1_CON_MANUAL	0x04	/**<如果是人工值守现金交易*/
#define CVM1_CON_CASHBACK	0x05	/**<如果是返现交易*/
#define CVM1_CON_LX			0x06	/**<如果交易以应用币种进行且数值小于X*/
#define CVM1_CON_GX		0x07	/**<如果交易以应用币种进行且数值大于X*/
#define CVM1_CON_LY			0x08	/**<如果交易以应用币种进行且数值小于Y*/
#define CVM1_CON_GY		0x09	/**<如果交易以应用币种进行且数值大于Y*/

#define VERIFY_PLAIN	0x00	/**<明文PIN验证*/
#define VERIFY_ENCYPT	0x01	/**<密文PIN验证*/

/**<CVM结果第3字节*/
#define CVM_RESULT_SUCC	0x02		/**<成功*/
#define CVM_RESULT_FAIL	0x01		/**<失败*/
#define CVM_RESULT_UNKNOW	0x00		/**<未知(签名)*/

#define CVMR3_UNKNOW_ONLINE		0x10	/**<联机*/	
#define CVMR3_UNKNOW_SIGNATRUE	0x20	/**<签名*/
#define CVMR3_UNKNOW_OTHER		0x30	/**<其他*/

#define VISA_AAC	1
#define	VISA_ARQC	2
#define	VISA_TC		3
#define	VISA_OTHER	4//转其他界面

#define SCRIPT_RES_SIZE		10//最大脚本条数
#define MAXLEN_ISSSCRIPT 128


#define ISS_IDD_ECBAL			0x01	/**< 电子现金余额*/
#define ISS_IDD_CTTA			0x02	/**< 累积交易总额*/
#define ISS_IDD_ECBAL_CTTA		0x03	/**< 电子现金余额和CTTA*/
#define ISS_IDD_CTTA_CTTAL		0x04	/**< CTTA和CTTAL*/
#define ISS_IDD_OFFBAL			0x05	/**< 可用脱机消费金额*/



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



#endif