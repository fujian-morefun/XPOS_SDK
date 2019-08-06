#ifndef __LIBAPI_PINPAD_HEADER__
#define __LIBAPI_PINPAD_HEADER__


#include "def.h"

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.10.3	获取密码键盘类模块版本号(Pp_GetModuleVer)
输入参数：无
输出参数：pszVer   模块版本号
返    回：成功返回模块版本号长度
		UPP_ERROR   =-7,           //失败
备	 注: 无
*************************************************************************************/
int Pp_GetModuleVer(char *pszVer);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.10.4	密码键盘初始化（Pp_Init）连接密码键盘、个性化参数设置等
输入参数：iPinPadType: 密码键盘类型,参见enum PinPadType
输出参数：无
返    回：UPP_ERROR		= -7				// 错误 
		UPP_SUCCESS		= 0				    // 成功 
备	 注: 无
*************************************************************************************/
int Pp_Init();

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.10.5	密钥下装（Pp_LoadKey）主密钥或工作密钥
输入参数：KeyIndex: 密钥组索引(索引号从0开始)
		iKeyType: 密钥类型,参见enum KeyType 
		KeyData: 主密钥明文；工作密钥密文。
		iDesType: 加密算法,表明密钥类型,参见enum DesType
输出参数：无
返    回：UPP_ERROR		= -7				// 错误 
		UPP_SUCCESS		= 0				    // 成功 
备	 注: 密钥组索引:包含了主密钥和三个工作密钥的一组密钥的索引号
*************************************************************************************/
int Pp_LoadKey(ushort KeyIndex, ushort iKeyType, byte *KeyData, ushort iDesType);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.10.6	密钥检测（Pp_CheckMKey）检测密钥是否存在
输入参数：KeyIndex: 密钥组索引
		iKeyType: 密钥类型，参见enum KeyType 
		iDesType: 加密算法,表明密钥类型,参见enum DesType
输出参数：无
返    回：UPP_KEY_EXIST    = -9，              //密钥组已存在
		UPP_ERROR		= -7				// 错误 
		UPP_SUCCESS		= 0				    // 成功 
备	 注: 无
*************************************************************************************/
int Pp_CheckMKey(ushort KeyIndex, ushort iKeyType, ushort iDesType);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.10.7	PIN输入（Pp_GetPin）
输入参数：Title: 金额，0.00格式传入
		Mode: 0-带主账号运算  1-不带主账号运算  2-获取明文
		PAN: 完整的卡号
		MinPINLen: 密码最小长度0
		MaxPINLen: 密码最大长度12
		TimeOut: 输入超时时间单位秒
		KeyIndex: 密钥组索引
		iDesType: 加密算法,表明密钥类型,参见enum DesType 
输出参数：PinData: Mode=0,1时输出的16进制PINDATA数据，Mode=2时输出明文字符串
返    回：UPIN_TIMEOUT     = -3,   //密码输入超时
		UPIN_ABORT		= -2,	// 操作员放弃输入 
		UPIN_ERROR		= -1,   // 输入错误 
		UPIN_ESC			=  0,   // 用户取消输入 
		UPIN_SUCCESS		=  1,   // 输入成功 
		UPIN_NONE		=  2	    // 无密码 
备	 注: 无
*************************************************************************************/
int Pp_GetPin(char *Title, byte Mode, byte *PAN, byte *PinData,byte MinPINLen, byte MaxPINLen, ushort TimeOut, ushort KeyIndex, ushort iDesType);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.10.8	MAC计算（Pp_CalculateMAC）
输入参数：CalMode: MAC算法类型 0-ECB  1-CBC(具体算法见附录A)
		Data: 参与计算MAC的数据
		DataLen: 参与计算MAC的数据长度
		KeyIndex: 密钥组索引
		iDesType: 加密算法,表明密钥类型,参见enum DesType
输出参数：MAC: 输出的MAC值
返    回：UPP_ERROR		= -7				// 错误 
		UPP_SUCCESS		= 0				    // 成功 
备	 注: Data为原始数据，不用补足8的倍数，由API自行补0
*************************************************************************************/
int Pp_CalculateMAC(ushort CalMode, byte *MAC, byte *Data, int DataLen, ushort KeyIndex, ushort iDesType);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.10.9	密钥加密（Pp_DesByKey）
输入参数：InData: 输入数据(8字节)
		KeyIndex:入参key在密码键盘中对应的主密钥索引
		Key: 加密InData的密钥密文
		iDesType: 加密算法,参见enum DesType
输出参数：OutData: 输出数据(8字节)
返    回：UPP_DECLINED     = -8,               //操作被拒绝
		UPP_ERROR		= -7				// 错误 
		UPP_SUCCESS		= 0				    // 成功 
备	 注: 无
*************************************************************************************/
int Pp_DesByKey(byte *InData, byte *OutData, ushort KeyIndex,byte *Key, ushort iDesType);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.10.10	密码键盘显示信息（Pp_DisplayMsg）
输入参数：Msg: 在密码键盘上显示的信息
		Line:显示行数
输出参数：无
返    回：UPP_ERROR		= -7				// 错误 
		UPP_SUCCESS		= 0				    // 成功 
备	 注: 对于内置密码键盘，在终端上显示；对于外置密码键盘，在PINPAD的显示屏上显示。
*************************************************************************************/
int Pp_DisplayMsg(char *Msg,int Line);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.10.11	密文主密钥下装（Pp_LoadEncryptedKey）
输入参数：KeyIndex: 密钥组索引(索引号从0开始),密钥下装索引
		KeyData: 主密钥密文
		iDesType: 加密算法,表明密钥类型,参见enum DesType
		DeccryptionKeyIndex: 用于解密的主密钥索引
		usIsTmsKey: 用于区分密文密钥是否是TMS主控密钥，0-不是，1-是
输出参数：无
返    回：UPP_ERROR		= -7				// 错误 
		UPP_SUCCESS		= 0				    // 成功 
备	 注: 用于TMS主控远程更新主控密钥或下载子应用主密钥
*************************************************************************************/
int Pp_LoadEncryptedKey(ushort KeyIndex, byte *KeyData, ushort iDesType, ushort DeccryptionKeyIndex, ushort usIsTmsKey);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.10.12	主控密钥加密（Pp_DesByMainKey）
输入参数：InData: 输入数据(8字节)
		KeyIndex:主控密钥索引
		iDesType: 加密算法,参见enum DesType
输出参数：OutData: 输出数据(8字节)
返    回：UPP_DECLINED     = -8,               //操作被拒绝
		UPP_ERROR		= -7				// 错误 
		UPP_SUCCESS		= 0				    // 成功 
备	 注: 主控主密钥加密
*************************************************************************************/
int Pp_DesByMainKey(byte *InData, byte *OutData, ushort KeyIndex, ushort iDesType);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.10.13	串口密钥下装（Pp_LoadKeyByCom）通过串口接收密钥，并下装密码键盘
输入参数：nCom   串口号，参见enum ExtPort
		cType  密钥类型，0-主控，1-传统应用，2-TPOS应用
		nPinPadType 密码键盘类型,参见enum PinPadType
输出参数：无
返    回：UPP_ERROR		= -7				// 错误 
		UPP_TIMEOUT		= -4,				// 超时(外置键盘通讯)
		UPP_SUCCESS		= 0				    // 成功 
备	 注: 实现与串口设备(母POS)间的建链、下载、断链，密钥下装
*************************************************************************************/
int Pp_LoadKeyByCom(uint nCom, byte cType, ushort nPinPadType);
int GetTermainSnAndInfo(char *Name, char *Sn);
#endif /*__LIBAPI_PINPAD_HEADER__*/
