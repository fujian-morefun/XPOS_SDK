#ifndef __EMV_OFF_AUTH__
#define __EMV_OFF_AUTH__
//SDA相关数据
#include <emv_interface.h>
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

typedef struct
{
	uchar ucXa[64+1];
	uchar ucYa[64+1];
}STSM;

extern int Dpas_CDA_GAC();
extern int PayPass_OffAuth_CDA_First();
extern int CDA_AC_PAYPASS(int nGacStep, char *pszGacRes, int nGacLen);
extern int CDA_GAC(int nGacStep, char *pszGacRes, int nGacLen);
extern int GetPinPk(XM_RSA_PUBLIC_KEY *pk);

extern int Emv_OffAuth();
extern int CalcSM2(STSM *stSm,unsigned char *r, unsigned char *s, unsigned char *msg, unsigned int msglen);
extern int Emv_SM_OffAuth();

extern int GetCAPK_EX(STRSA *pk);
extern int GetCAPK(STRSA *pk);
extern int GetCertInfo(char cCertType,STCERT *stCert);
extern int GetAuthData(unsigned char cCertType,char *pszData,int *nLen);
extern int OffAuth_SM_DDA(char cCertType);
/******************************************************************************
 *  	函数名称:	Emv_OffAuth: 
 *	函数介绍:	
 *	入口参数:	
 *	出口参数:     
 * 	返回值  :		
 ******************************************************************************/
int Rf_OffAuth(int odatype);
#endif