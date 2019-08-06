#ifndef __TVRTSI__
#define __TVRTSI__

#include "pub_def.h"
#include "emv_interface.h"

/**<TSI*/
#define TSI_OFFLINE_DA_PERFORMED                       0x0080
#define TSI_CV_PERFORMED                               0x0040
#define TSI_CARD_RISK_MANA_PERFORMED                   0x0020
#define TSI_ISSUER_AUTH_PERFORMED                      0x0010
#define TSI_TERM_RISK_MANA_PERFORMED                   0x0008
#define TSI_SCRIPT_PROCESSING_PERFORMED                0x0004

/**<TVR第0字节*/
#define TVR0_OFFLINE_DA_NOT_PERFORMED                    0x0080
#define TVR0_SDA_FAILED                                  0x0040
#define TVR0_ICC_DATA_MISSING                            0x0020
#define TVR0_CARD_ON_EXCEPTION_FILE                      0x0010
#define TVR0_DDA_FAILED                                  0x0008
#define TVR0_CDA_FAILED                                  0x0004
#define TVR0_SDA_EXECUTE                                 0x0002 //4.3案例要求执行SDA需置位该位

/**<TVR第1字节*/
#define TVR1_APP_VER_NOT_MATCHED                         0x0180
#define TVR1_EXPIRED_APP                                 0x0140
#define TVR1_APP_NOT_EFFECTIVE                           0x0120
#define TVR1_REQUESTED_SERVICE_NOT_ALLOWED               0x0110
#define TVR1_NEW_CARD                                    0x0108

/**<TVR第2字节*/
#define TVR2_CV_NOT_SUCCESSFUL                           0x0280
#define TVR2_UNRECOGNISED_CVM                            0x0240
#define TVR2_PIN_TRY_LIMIT_EXCEEDED                      0x0220
#define TVR2_PIN_PAD_NOT_PRESENT_OR_NOT_WORKING          0x0210
#define TVR2_PIN_PAD_PRESENT_BUT_PIN_NOT_ENTERED         0x0208
#define TVR2_ONLINE_PIN_ENTERED                          0x0204

/**<TVR第3字节*/
#define TVR3_TRANSACTION_EXCEEDS_FLOOR_LIMIT             0x0380
#define TVR3_LOWER_CONSECUTIVE_OFFLINE_LIMIT_EXCEEDED    0x0340
#define TVR3_UPPER_CONSECUTIVE_OFFLINE_LIMIT_EXCEEDED    0x0320
#define TVR3_TRANSACTION_SELECTED_RANDOMLY_FOR_ONLINE    0x0310
#define TVR3_MERCHANT_FORCED_TRANSACTION_ONLINE          0x0308

/**<TVR第4字节*/
#define TVR4_DEFAULT_TDOL_USED                           0x0480
#define TVR4_ISSUER_AUTHENTICATION_FAILED                0x0440
#define TVR4_SCRIPT_PROCESSING_FAILED_BEFORE_2GENAC      0x0420
#define TVR4_SCRIPT_PROCESSING_FAILED_AFTER_2GENAC       0x0410
#define PAYPASS_TRV4_RRP_THRESHOLD_EXCEEDED				 0x0408
#define PAYPASS_TRV4_RRP_TIME_LIMIT_EXCEEDED			 0x0404

/**<终端性能*/
#define TC_MANUAL_KEY_ENTRY          0X0080		/*手工键盘输入*/
#define TC_MAGNETIC_STRIPE            0X0040		/*磁条卡*/
#define TC_IC_WITH_CONTACTS          0X0020		/*接触式IC卡*/

#define TC_PLAINTEXT_PIN             0X0180		/*明文PIN验证*/	
#define TC_ENCIPHERED_PIN_ONLINE     0X0140	/*联机密文PIN验证*/
#define TC_SIGNATURE_PAPER           0X0120		/*签名(纸质)*/
#define TC_ENCIPHERED_PIN_OFFLINE    0X0110	/*脱机密文PIN验证*/
#define TC_NO_CVM_REQUIRED           0X0108		/*无需CVM*/
#define TC_CARDHOLDER_CERT           0X0101		/*持卡人证件出示*/

#define TC_SDA                       0X0280			/*静态数据认证SDA*/
#define TC_DDA                       0X0240			/*动态数据认证DDA*/
#define TC_CARD_CAPTURE        0X0220			/*吞卡*/
#define TC_CDA                       0X0208			/*复合动态数据认证/应用密文生成CDA*/


/**<应用交互特征AIP*/
#define AIP_MSD       	0x80
#define AIP_SDA       	0x40
#define AIP_DDA     	0x20
#define AIP_CV        	0x10

#define AIP_TRM       	0x08
#define AIP_IA        	0x04
#define AIP_CDA       	0x01

LIB_EXPORT void SetTVR( int iSetMask);
LIB_EXPORT void SetTSI( int iSetMask);
LIB_EXPORT void GetTVR( char * pszTvr );
LIB_EXPORT void GetTSI( char * pszTsi );
LIB_EXPORT YESORNO GetTermCap(int nMask,char * pszTermCap);
LIB_EXPORT int CompareTVRandAC(char *pszTag,char cPad);
LIB_EXPORT int PP_CompareTVRandAC(char *pszTag);
#endif

