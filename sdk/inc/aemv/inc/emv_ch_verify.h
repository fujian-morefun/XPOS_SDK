#ifndef __EMV_CH_VERIFY__
#define __EMV_CH_VERIFY__
#include <emv_interface.h>
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

#define OFFLINE_PIN_NOMAL		0x03	/**<提示输入脱机PIN*/
#define OFFLINE_PIN_AGAIN		0x02	/**<提示再次输入脱机PIN*/
#define OFFLINE_PIN_LAST		0x01	/**<最后一次输入脱机PIN*/

/**<CVM结果第3字节*/
#define CVM_RESULT_SUCC	0x02		/**<成功*/
#define CVM_RESULT_FAIL	0x01		/**<失败*/
#define CVM_RESULT_UNKNOW	0x00		/**<未知(签名)*/

#define CVMR3_UNKNOW_ONLINE		0x10	/**<联机*/	
#define CVMR3_UNKNOW_SIGNATRUE	0x20	/**<签名*/
#define CVMR3_UNKNOW_OTHER		0x30	/**<其他*/

extern int Emv_Ch_Verify(STEMVPROC *stProc);
extern int PayPass_Ch_Verify(int iType,int *piCvmFlag);
/******************************************************************************
 *  	函数名称:	GetOnlinePin: 
 *	函数介绍:	获取联机PIN
 *	入口参数:	
 *	出口参数:     
 * 	返回值  :		SUCC
 					FAIL
 					QUIT 取消退出
 ******************************************************************************/
extern int GetOnlinePin(void);
#endif