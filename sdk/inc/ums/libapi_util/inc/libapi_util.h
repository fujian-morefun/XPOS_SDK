#ifndef __LIBAPI_UTIL_HEADER__
#define __LIBAPI_UTIL_HEADER__

#include "def.h"
#include "PlaySound_api.h"

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.3	获取工具类模块版本号(Util_GetModuleVer)
输入参数：无
输出参数：pszVer   模块版本号
返    回：成功返回模块版本号长度
		UUTIL_FAIL   =-1,           //失败
备	 注: 无
*************************************************************************************/
int Util_GetModuleVer(char *pszVer);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.4	ASCII码转BCD码（Util_Asc2Bcd）
输入参数：AscBuf: 需进行转换的ASCII码数据
		AscLen:  传入的ASCII码数据长度
输出参数：BcdBuf:  转换输出的BCD码数据
返    回：UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0			//成功
备	 注: 左靠BCD码,位数不足后补'F'
*************************************************************************************/
int Util_Asc2Bcd(char *AscBuf, char *BcdBuf, int AscLen);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.5	BCD码转ASCII码（Util_Bcd2Asc）
输入参数：BcdBuf: 需进行转换的BCD码数据
		AscLen:ASCII码数据长度,即BCD码数据的双倍长度
输出参数：AscBuf: 转换输出的ASCII码数据
返    回：UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0			//成功
备	 注: 无
*************************************************************************************/
int Util_Bcd2Asc(char *BcdBuf, char *AscBuf, int AscLen);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.6	int型数据转BCD码（Util_Int2Bcd）
输入参数：IntData:   待转换的int型数据
		BcdLen：   转换后BCD码数据长度
输出参数：BcdBuf：   转换后BCD数据
返    回：UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0			//成功
备	 注: 右靠BCD码,位数不足左补0
*************************************************************************************/
int Util_Int2Bcd(uint IntData, char *BcdBuf, int BcdLen);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.7	BCD码转int型（Util_Bcd2Int）
输入参数：BcdBuf:    待转换的BCD数据
		BcdLen：   BCD码数据长度
输出参数：IntData：  转换后int型数据
返    回：UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0			//成功
 备	 注: 无
*************************************************************************************/
int Util_Bcd2Int(char *BcdBuf, uint *IntData, int BcdLen);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.8	计算LRC（Util_GenLrc）计算并生成LRC校验位（按位异或）
输入参数：Data：    待计算LRC校验位的数据
		DataLen： 数据长度
输出参数：无
返    回：计算生成的LRC校验值
备	 注: 无
*************************************************************************************/
byte Util_GenLrc(char *Data, int DataLen);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.9	DES加解密（Util_Des）对数据进行DES加解密或者3DES加解密
输入参数：bDesType：  DES加解密算法：0表示DES加密、1表示DES解密、2表示3DES加密、3表示3DES解密
		Key：       用作加解密的传输密钥,必须为8的倍数
		InData:      待加解密的密文数据,必须为8字节
输出参数：OutData：    加解密后的密钥,必须为8字节
返    回：UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0			//成功
备	 注: 无
*************************************************************************************/
int Util_Des(byte bDesType, char *Key, char *InData, char *OutData);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.10	中文字符拷贝（Util_StrCopy）,中文智能截断函数, 解决一行中文显示半个汉字的问题
输入参数：scr:源数据串
		len:源数据长度
输出参数：Dst:目标数据串
返    回：返回已拷贝的字符串长度
备	 注: 将数据转成二维码并打印
*************************************************************************************/
int Util_StrCopy(char *dst, cchar *src, int len);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.11	等待按键（Util_WaitKey）在设定时间内等待按键,无按键则等待超时
输入参数：TimeOut:    等待超时时间（秒）,0表示阻塞
输出参数：无
返    回：UUTIL_TIMEOUT或返回按键值
备	 注: 无
*************************************************************************************/
int Util_WaitKey(int TimeOut);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.12	输入法输入（Util_InputMethod）支持输入法切换的数据输入
输入参数：disp_line:     提示信息显示行数
		msgPrompt:     提示信息（左对齐）
		input_line：   输入数据显示行数
		min:           最小输入长度
		max:           最大输入长度
		disp_pattern: 输入数据显示位置,0左对齐;1居中;2右对齐
		timeout:       等待输入超时时间（秒）
输出参数：str:           输入数据
返    回：成功：返回输入数据str字节数
		UUTIL_TIMEOUT  = -3,    //输入超时
		UUTIL_CANCEL   = -2,    //输入取消
		UUTIL_FAIL           = -1,    //失败
备	 注: 无
*************************************************************************************/
int Util_InputMethod(int disp_line, char * msgPrompt, int input_line, char *str, int min, int max, byte disp_pattern,int timeout);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.13	字符串输入（Util_InputText）数字、子母、密码输入
输入参数：disp_line:     提示信息显示行数
		msgPrompt:     提示信息
		input_line:    输入数据显示行数
		min:           最小输入长度
		max:           最大输入长度
		disp_pattern:  显示位置,0左对齐;1居中;2,右对齐
		disp_mode：输入模式,0数字输入;1数字、子母输入;2密码输入
		timeout:       超时时间(秒)
输出参数：str:           输入数据
返    回：成功：返回输入数据str字节数
		UUTIL_TIMEOUT  = -3,    //输入超时
		UUTIL_CANCEL   = -2,    //输入取消
		UUTIL_FAIL           = -1,    //失败
备	 注: 当输入模式为数字、字母输入时,通过连续按某个按键,进行某个数字、大写子母、小写子母间的切换
*************************************************************************************/
int Util_InputText(int disp_line, char * msgPrompt, int input_line, char *str, int min, int max, int disp_pattern,byte disp_mode ,int timeout);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.14	十六进制HEX输入（Util_InputHex）
输入参数：disp_line:     提示信息显示行数
		msgPrompt:     提示信息
		input_line:    输入数据显示行数
		min:           最小输入十六进制字节个数
		max:           最大输入十六进制字节个数
		disp_pattern:  输入数据显示方式,0左对齐;1居中;2,右对齐
		timeout：      超时时间（秒）
输出参数：str:           输入数据
返    回：成功：返回输入数据str字节数
		UUTIL_TIMEOUT  = -3,    //输入超时
		UUTIL_CANCEL   = -2,    //输入取消
		UUTIL_FAIL           = -1,    //失败
备	 注: 连续按某个按键,进行某个数字、大写子母、小写子母间的切换
		输入范围十六进制0-F,一个十六进制字节为两个字符,即只能输入偶数个字符
		比如输入：a123dafa
		出来应该是：\xa1\x23\xda\xfa   返回值是4 
*************************************************************************************/
int Util_InputHex(int disp_line, char *msgPrompt, int input_line, char *str, int min, int max, byte disp_pattern, int timeout);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.15	金额输入（Util_InputAmount）
输入参数：disp_line:     提示信息显示行数
		msgPrompt:     提示信息
		input_line:    输入数据显示行数
		disp_pattern:  显示方式,0左对齐;1居中;2,右对齐
		timeout:       超时时间（秒）
输出参数：amount：输出金额
返    回：成功：返回输出金额amount字节数
		UUTIL_TIMEOUT  = -3,    //输入超时
		UUTIL_CANCEL   = -2,    //输入取消
		UUTIL_FAIL           = -1,    //失败
备	 注: 金额输入精确到分（保留小数点后两位）,并以最大12位ASCII码存入Amount变量
*************************************************************************************/
int Util_InputAmount(int disp_line, char * msgPrompt, int input_line, char *amount,byte disp_pattern,int timeout);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.16	IP输入（Util_InputIp）
输入参数：disp_line:     提示信息显示行数
		msgPrompt:     提示信息
		input_line:    输入数据显示行数
		disp_pattern:  显示位置,0左对齐;1居中;2,右对齐
		timeout:       超时时间（秒）
输出参数：ip:            输入IP地址
返    回：成功：返回输入ip地址字节数
		UUTIL_TIMEOUT  = -3,    //输入超时
		UUTIL_CANCEL   = -2,    //输入取消
		UUTIL_FAIL           = -1,    //失败
备	 注: API内部带IP地址格式判断
*************************************************************************************/
int Util_InputIp(int disp_line, char * msgPrompt, int input_line, char *ip, byte disp_pattern, int timeout);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.17	蜂鸣失败（Util_ErrorBeep）提示失败时的蜂鸣声,阻塞
输入参数：num:  蜂鸣次数
输出参数：无
返    回：无
备    注：无
*************************************************************************************/
void Util_ErrorBeep(int num);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.18	蜂鸣成功（Util_Beep）提示成功时的蜂鸣,非阻塞
输入参数：num:  蜂鸣次数
输出参数：无
返    回：无
备    注：无
*************************************************************************************/
void Util_Beep(int num);
/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.19	生成随机数（Util_Rand）
输入参数：无
输出参数：psRandom   8字节Binary随机数
返    回：UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0		//成功
备	 注: 优先使用真随机数
*************************************************************************************/
int Util_Rand(byte *psRandom);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.20	生成条码二维码（Util_CreateBarCode）用于显示和打印
输入参数：codeType   条码类型
		sizelevel  最小识别模块的行列各为多少个点,比如1,2,4,8等...,厂家根据具体情况调整
		pszData    要生成的数据内容
		iDataLen   数据长度
		pszBmpName 保存的文件名
输出参数：无
返    回：UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0		//成功
备	 注: 生成条码或二维码,用于显示和打印
*************************************************************************************/
int Util_CreateBarCode(BarCode codeType, int sizelevel, const char *pszData, int iDataLen, const char *pszBmpName);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.21	随机生成RSA公私钥对（Util_GenerateRSAKey）
输入参数：nProtoKeyBit  RSA算法密钥长度,参见 enum URSAKeyLen
		nPubEType  RSA算法指数,参见enum URSAEXP
输出参数：pstPublicKey    RSA公钥
		pstPrivateKey   RSA私钥
返    回：UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0		//成功
备	 注: 一般情况下,公私钥对的产生时间随着模长的增加而增加。
		在相同模长的情况下,指数的取值对公私钥对的产生时间影响不大。
*************************************************************************************/
int Util_GeneraterRSAKey(int nProtoKeyBit, int nPubEType, URSAPUBLICKEY *pstPublicKey, URSAPRIVATEKEY *pstPrivateKey);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.22	使用RSA公钥计算（Util_RSAPublicKeyCalc）
输入参数：pstPublicKey    RSA公钥,参见struct URSAPUBLICKEY
		psSrc    输入数据
		nSrcLen  输入数据长度
		pnDstLen 输出数据缓存大小
输出参数：psDst    输出数据
		pnDstLen 输出数据长度
返    回：UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0		//成功
备	 注: 1.RSA公钥计算时,输入数据的长度必须等于模长字节数;
2.输入数据的值必须小于模值,否则函数返回失败,对长度大于等于模长字节数的数据,请分段截取小于模长度字节数的数据并前补0x00;
3.对于合理的输入数据,计算之后的输出数据长度总是和公钥模等长
*************************************************************************************/
int Util_RSAPublicKeyCalc(URSAPUBLICKEY *pstPublicKey, const byte *psSrc, uint nSrcLen, byte *psDst, uint *pnDstLen);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.23	使用RSA私钥计算（Util_RSAPrivateKeyCalc）
输入参数：pstPrivateKey    RSA私钥,参见struct URSAPRIVATEKEY
		psSrc    输入数据
		nSrcLen  输入数据长度
		pnDstLen 输出数据缓存大小
输出参数：psDst    输出数据
		pnDstLen 输出数据长度
返    回：UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0		//成功
备	 注: 1.RSA私钥计算时,输入数据的长度必须等于模长字节数;
2.输入数据的值必须小于模值,否则函数返回失败,对长度大于等于模长字节数的数据,请分段截取小于模长度字节数的数据并前补0x00;
3.对于合理的输入数据,计算之后的输出数据长度总是和私钥模等长
*************************************************************************************/
int Util_RSAPrivateKeyCalc(URSAPRIVATEKEY *pstPrivateKey, const byte *psSrc, uint nSrcLen, byte *psDst, uint *pnDstLen);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.24	SHA1算法（Util_SHA1）
输入参数：psSrc    输入数据
		nSrcLen  输入数据长度
输出参数：psDst    输出数据,20字节HASH结果
返    回：UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0		//成功
备	 注: 使用SHA-1算法计算哈希值
*************************************************************************************/
int Util_SHA1(const byte *psSrc, uint nSrcLen, byte *psDst);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.25	SHA256算法（Util_SHA256）
输入参数：psSrc    输入数据
		nSrcLen  输入数据长度
输出参数：psDst    输出数据,32字节HASH结果
返    回：UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0		//成功
备	 注: 使用SHA-256算法计算哈希值
*************************************************************************************/
int Util_SHA256(const byte *psSrc, uint nSrcLen, byte *psDst);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.26	SHA512算法（Util_SHA512）
输入参数：psSrc    输入数据
		nSrcLen  输入数据长度
输出参数：psDst    输出数据,64字节HASH结果
返    回：UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0		//成功
备	 注: 使用SHA-512算法计算哈希值
*************************************************************************************/
int Util_SHA512(const byte *psSrc, uint nSrcLen, byte *psDst);

#if 0

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.27	电子签名板初始化（Util_SignaturePadInit）
输入参数：nSignaturePad  签名版,参见enum USignaturePad
		nTimeout  初始化超时等待时间,单位秒s
输出参数：无
返    回：UUTIL_TIMEOUT        = -3,    //超时
		UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0		//成功
备	 注: 电子签名板初始化,检测签名板状态
外置密码键盘签名板,需从密码键盘模式切到签名版模式,签名后需重新切回密码键盘模式
*************************************************************************************/
int Util_SignaturePadInit(int nSignaturePad, int nTimeout);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.28	电子签名板切回密码键盘（Util_SignaturePadSwitch2PinPad）将外置密码键盘从签名板模式切回密码键盘模式
输入参数：nSignaturePad  签名版,参见enum USignaturePad
		nTimeout  初始化超时等待时间,单位秒s
输出参数：无
返    回：UUTIL_TIMEOUT        = -3,    //超时
		UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0		//成功
备	 注: 如果是外置密码键盘签名板,调用签名后,必须切回密码键盘模式
*************************************************************************************/
int Util_SignaturePadSwitch2PinPad(int nSignaturePad, int nTimeout);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.29	电子签名（Util_SignatureSign）
输入参数：pszFeatureCode  特征码,可扩展使用,为NULL时表示不需要特征码
		pszBmpName   需要生成的签名BMP图片名
		nTryCount    签名重试次数
		nTimeout     签名超时时间,单位s,单次签名的超时时间
输出参数：无
返    回：UUTIL_TIMEOUT        = -3,    //超时
		UUTIL_CANCEL         = -2,    //取消
		UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0		//成功
备	 注: 电子签名,生成的图片保存在当前应用根目录下
*************************************************************************************/
int Util_SignatureSign(const byte *pszFeatureCode, const byte *pszBmpName, int nTryCount, int nTimeout);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.30	电子签名图片压缩（Util_SignatureCompress）
输入参数：pszBmpName   电子签名图片名称
		pnDataLen    psData缓存大小
输出参数：psData       图片压缩后的数据
		pnDataLen    图片压缩后的数据长度
返    回：UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0		//成功
备	 注: 电子签名图片压缩,按照《中国银联电子签字版规范》要求完成图片压缩
*************************************************************************************/
int Util_SignatureCompress(const byte *pszBmpName, byte *psData, int *pnDataLen);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.31	电子签名图片解压缩（Util_SignatureUnCompress）
输入参数：pszBmpName  解压缩生成的电子签名图片名
		psData      电子签名图片压缩数据
		nDataLen    电子签名图片压缩数据的长度
输出参数：无
返    回：UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0		//成功
备	 注: 电子签名图片解压缩,解压缩按照《中国银联电子签字版规范》要求压缩的图片,生成的图片保存在当前应用根目录
*************************************************************************************/
int Util_SignatureUnCompress(const byte *pszBmpName, const byte *psData, int nDataLen);

#endif
/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.5.32	扫描枪扫描（Util_ScannerScan）内置扫描枪扫描,阻塞
输入参数：pnDataLen    psData缓存大小
		nTimeout     超时时间,单位秒s,0表示不超时,直到扫描完成退出
输出参数：psData扫描到的数据
		pnDataLen    psData数据长度
返    回：UUTIL_TIMEOUT        = -3,      //超时
		UUTIL_CANCEL         = -2,      //取消
		UUTIL_FAIL           = -1,       //失败
		UUTIL_SUCCESS        =  0		//成功
备	 注: 根据终端实际情况支持条码、二维码扫描
*************************************************************************************/
int Util_ScannerScan(byte *psData, int *pnDataLen, int nTimeout);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	  者：张亚博
功    能：2.2.5.33 内置扫描枪扫描， 阻塞
输入参数：
输出参数：BarCode 扫描到的数据
返    回：UUTIL_TIMEOUT = -3, //超时
		  UUTIL_CANCEL = -2, //取消
	  	  UUTIL_FAIL = -1, //失败
		  UUTIL_SUCCESS = 0 //成功
备	 注:  根据终端实际情况支持条码、 二维码扫描
*************************************************************************************/
int Util_ScanBarCode(char *BarCode);

/**
* @fn Scan_Open
* @brief  打开扫码抢
* @param in
* @param 
* @return
* @li  成功：UUTIL_SUCCESS = 0
* @li  UUTIL_FAIL			= -1,			失败
*/

int Scan_Open(void);
/**
* @fn Scan_Close
* @brief  关闭扫码
* @param in
* @param 
* @return
* @li  成功：UUTIL_SUCCESS = 0
* @li  UUTIL_FAIL			= -1,			失败
*/
int Scan_Close(void);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	  者：张亚博
功    能：2.2.5.34 对数据进行 SM4 加解密
输入参数：Type SM4 加解密算法：0 表示 SM4 加密、 1 表示 SM4解密
		  Key 用作加解密的传输密钥， 必须为 16 字节
		  InData 待加解密的密文数据， 必须为 16 字节
输出参数：OutData 加解密后的数据， 16 字节
返    回：UUTIL_FAIL = -1, //失败
		  UUTIL_SUCCESS = 0 //成功
备	 注: 
*************************************************************************************/
int Util_SM4(byte Type, char *Key, char *InData, char *OutData);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	  者：白建中
功    能：2.2.5.35	硬件序列号加密（Util_SNEncrypt） 使用硬件序列号密钥对硬件序列号+随机因子进行加密，并输出硬件序列号及加密结果
输入参数：psFactor 随机因子
		nFactorLen 随机因子长度
输出参数：pszSN   硬件序列号
		psEncrypted 硬件序列号密文，8字节长度
返    回：UUTIL_FAIL = -1, //失败
		  UUTIL_SUCCESS = 0 //成功
备	 注: 使用国密SM4做ECB算法加密
*************************************************************************************/
int Util_SNEncrypt(char *psFactor, int nFactorLen, char *pszSN, char *psEncrypted);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	  者：白建中
功    能：语音播报
参数说明 入参 Msg: 需要语言播放的信息
出    参 无
返 回 值 无
补充说明 语音播放为非阻塞
*************************************************************************************/
void Play_Voice(char *msg);

#endif /*__LIBAPI_UTIL_HEADER__*/
