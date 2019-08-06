#ifndef __LIBAPI_COMM_HEADER__
#define __LIBAPI_COMM_HEADER__


#include "def.h"

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.3	获取通讯类模块版本号(Comm_GetModuleVer)
输入参数：无
输出参数：pszVer   模块版本号
返    回：成功返回模块版本号长度
		UCOMM_FAIL   =-1,           //失败
备	 注: 无
*************************************************************************************/
int Comm_GetModuleVer(char *pszVer);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.4	GPRS、CDMA、IP、WIFI、MODEM通讯初始化（Comm_Init）
开机初始化设备、初始化终端通讯参数、设备检测、无线注册网络、WIFI连接热点等
输入参数：st_commconfig通讯参数
输出参数：无
返    回：UCOMM_CANCEL     =-3,       //按键取消
		UCOMM_FAIL     = -1,       //失败
		UCOMM_SUCCESS	 =  0    	//成功
备	 注: 开机调用,超时时间API内部控制,WIFI连接到热点
*************************************************************************************/
int Comm_Init( const COMMCONFIG *st_commconfig);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.5	通讯参数操作函数（Comm_Set）
输入参数：st_commconfig通讯参数
输出参数：无
返    回：UCOMM_CANCEL     =-3,       //按键取消
		UCOMM_FAIL     = -1,       //失败
		UCOMM_SUCCESS	 =  0    	//成功
备	 注: 在通讯前调用,提供给需要切换IP和端口或有的厂家在通讯前才做通讯初始化的情况下使用
超时时间API内部控制
改通讯参数/切换网络时调用,连接不同网段
*************************************************************************************/
int Comm_Set( const COMMHOSTCONFIG *st_commconfig);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.6	MODEM预拨号（Comm_PreConnect）
输入参数：st_commconfig通讯参数
输出参数：无
返    回：UCOMM_FAIL           = -1,       //失败
		UCOMM_SUCCESS        =  0			//成功
备	 注: 只拨号,不检查是否连上
*************************************************************************************/
int Comm_PreConnect(MODEMCONFIG *st_modemconfig);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.7	GPRS、CDMA、IP、WIFI通讯连接主机和MODEM拨号（Comm_Connect）
输入参数：st_commconfig通讯参数
		TimeOut 超时时间,单位秒(多次连接总的超时时间)
输出参数：无
返    回：成功时返回通讯句柄
		UCOMM_LOGOFF     = -4,        //通讯链路断开
		UCOMM_CANCEL     =-3,       //按键取消
		UCOMM_TIMEOUT  = -2,       //超时
		UCOMM_FAIL     = -1,       //失败
 备	 注: st_commhostconfig参数,是为了兼容需要在连接时传入参数的部分厂家
		响应取消键KEY_CANCEL
		MODEM拨号,没调用Comm_Close函数,不做挂断处理
		MODEM拨号前,需检查预拨号是否已拨通
		Socket连接,切换IP时,先挂断
*************************************************************************************/
int Comm_Connect(COMMHOSTCONFIG *st_commhostconfig,int TimeOut);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.8	GPRS、CDMA、IP、WIFI、MODEM通讯发送数据（Comm_Send）
输入参数：HandleId   通讯句柄
		Data   发送的数据
		DataLen   发送的数据长度
输出参数：无
返    回：UCOMM_LOGOFF     = -4,        //通讯链路断开
		UCOMM_FAIL     = -1,       //失败
		UCOMM_SUCCESS	 =  0    	//成功
备	 注: MODEM通讯不带长度
		GPRS、CDMA、IP、WIFI通讯带长度,Data格式：长度+数据
*************************************************************************************/
int Comm_Send(int HandleId,byte * Data,int DataLen);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.9	GPRS、CDMA、IP、WIFI、MODEM通讯接收数据（Comm_Recv）在指定时间内接收指定长度数据
输入参数：HandleId   通讯句柄
		DataLen   期望接收的数据长度
		TimeOut    超时时间单位秒,0表示非阻塞
输出参数：Data   接收到的数据
返    回：成功返回收到数据字节数
		UCOMM_LOGOFF     = -4,        //通讯链路断开
		UCOMM_TIMEOUT  = -2,       //超时
		UCOMM_FAIL     = -1,       //失败
备	 注: MODEM通讯不带长度,完整性由底层判断,收到完整数据后直接退出并返回收到数据长度;
GPRS、CDMA、IP、WIFI通讯带长度,先收长度,再收相应长度的数据
*************************************************************************************/
int Comm_Recv(int HandleId,byte * Data,int DataLen,int TimeOut);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.10	GPRS、CDMA、IP、WIFI、MODEM通讯清缓存（Comm_ClrBuf）
输入参数：HandleId   通讯句柄
输出参数：无
返    回：UCOMM_FAIL     = -1,       //失败
		UCOMM_SUCCESS	 =  0    	//成功
备	 注: 无
*************************************************************************************/
int Comm_ClrBuf(int HandleId);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.11	GPRS、CDMA、IP、WIFI、MODEM通讯关闭（Comm_Close）
输入参数：HandleId   通讯句柄
		Type：挂断模式,参见enum HangUpMod
输出参数：无
返    回：UCOMM_FAIL     = -1,       //失败
		UCOMM_SUCCESS	 =  0    	//成功
备	 注: GPRS、CDMA挂断socket或者PPP
		IP挂断socket
		WIFI挂断socket或者断开WIFI热点连接
		MODEM挂断
*************************************************************************************/
int Comm_Close(int HandleId,int Type);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.12	无线网络信号显示（Comm_PPPSignal）实时显示无线网络信号强度
输入参数：isDisp： 0-不显示,1-显示
输出参数：无
返    回：返回信号强度0-100(100为最强信号)
备	 注: 显示的格式、位置可按各家原有的去显示
*************************************************************************************/
int Comm_PPPSignal(int isDisp);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.13	检测GPRS、CDMA网络注册状态（Comm_PPPCheck）
输入参数：无
输出参数：无
返    回：UCOMM_CONNECTING  = -5,       //通讯连接中,PPP拨号中(不支持检测是否拨号中的厂商,不需要返回该值)
		UCOMM_LOGOFF     = -4,        //通讯链路断开
		UCOMM_FAIL     = -1,         //失败
		UCOMM_LINK_OK     = 1        //通讯链路OK
备	 注: 无
*************************************************************************************/
int Comm_PPPCheck(void);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.14	GPRS、CDMA通讯PPP挂断（Comm_PPPClose）
输入参数：无
输出参数：无
返    回：UCOMM_FAIL     = -1,       //失败
		UCOMM_SUCCESS	 =  0    	//成功
备	 注: 无
*************************************************************************************/
int Comm_PPPClose(void);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.15	打开WIFI设备（Comm_WIFIOpen）
输入参数：无
输出参数：无
返    回：UCOMM_DEVICE_UNAVAILABLE = -8, //设备不可用
		UCOMM_FAIL     = -1,       //失败
		UCOMM_SUCCESS	 =  0    	//成功
备	 注: 打开并初始化WIFI设备
*************************************************************************************/
int Comm_WIFIOpen(void);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.16	关闭WIFI设备（Comm_WIFIClose）
输入参数：无
输出参数：无
返    回：UCOMM_DEVICE_UNAVAILABLE = -8, //设备不可用
		UCOMM_FAIL     = -1,       //失败
		UCOMM_SUCCESS	 =  0    	//成功
备	 注: 无
*************************************************************************************/
int Comm_WIFIClose(void);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.17	获取附近WIFI热点列表（Comm_WIFIGetSSIDList）
输入参数：pnNumList     最大允许获取的WIFI热点个数
输出参数：WIFIList      WIFI热点SSID列表
		pnNumList     实际获取到的WIFI热点个数
返    回：UCOMM_DEVICE_UNAVAILABLE = -8, //设备不可用
		UCOMM_FAIL     = -1,       //失败
		UCOMM_SUCCESS	 =  0    	//成功
备    注：无
*************************************************************************************/
int Comm_WIFIGetSSIDList(WIFIINFO WIFIList[], int *pnNumList);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.18	WIFI连接到热点（Comm_WIFIConnect）
输入参数：st_wificonfig  WIFI连接参数
输出参数：无
返    回：UCOMM_DEVICE_UNAVAILABLE = -8, //设备不可用
		UCOMM_PARA_ERR    = -7,       //参数错
		UCOMM_CONNECT_ERR = -6,       //无法连接
		UCOMM_FAIL     = -1,         //失败
		UCOMM_SUCCESS	 =  0,    	//成功
备    注：无
*************************************************************************************/
int Comm_WIFIConnect(const WIFICONFIG *st_wificonfig);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.19	断开WIFI热点连接（Comm_WIFIDisConnect）
输入参数：无
输出参数：无
返    回：UCOMM_DEVICE_UNAVAILABLE = -8, //设备不可用
		UCOMM_PARA_ERR    = -7,       //参数错
		UCOMM_CONNECT_ERR = -6,       //无法连接
		UCOMM_FAIL     = -1,         //失败
		UCOMM_SUCCESS	 =  0,    	//成功
备    注：无
*************************************************************************************/
int Comm_WIFIDisConnect(void);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.20	检测WIFI网络状态（Comm_WIFICheck）
输入参数：无
输出参数：无
返    回：UCOMM_CONNECTING  = -5,       //通讯连接中
		UCOMM_LOGOFF     = -4,        //通讯链路断开
		UCOMM_FAIL     = -1,         //失败
		UCOMM_LINK_OK     = 1        //通讯链路OK
备	 注: 检测终端到路由或者AP之间的网络连接状态
*************************************************************************************/
int Comm_WIFICheck(void);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.21	WIFI信号显示（Comm_WIFISignal）实时显示WIFI网络信号强度
输入参数：isDisp： 0-不显示,1-显示
输出参数：无
返    回：返回信号强度0-100(100为最强信号)
备	 注: 显示的格式、位置可按各家原有的去显示
*************************************************************************************/
int Comm_WIFISignal(int isDisp);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.22	获取终端IP、WIFI通讯本机IP信息（Comm_GetIPInfo）
输入参数：cType   1-以太网,2-WIFI
输出参数：st_terminalipinfo  IP信息
返    回：UCOMM_DEVICE_UNAVAILABLE = -8, //设备不可用
		UCOMM_PARA_ERR    = -7,       //参数错
		UCOMM_FAIL           = -1,       //失败
		UCOMM_SUCCESS        =  0		//成功
备	 注: 无
*************************************************************************************/
int Comm_GetIPInfo(byte cType, TERMINALIPINFO *st_terminalipinfo);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.23	串口初始化（Comm_ComOpen）
输入参数：st_rs232config通讯参数
输出参数：无
返    回：UCOMM_FAIL           = -1,       //失败
		大于0表示成功,并返回串口ID
备	 注: 初始化并打开串口,每次串口通讯前调用
*************************************************************************************/
int Comm_ComOpen( const RS232CONFIG *st_rs232config);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.24	串口发送数据（Comm_ComSend）
输入参数：HandleId   通讯句柄
		Data   发送的数据
		DataLen   发送的数据长度
输出参数：无
返    回：UCOMM_FAIL           = -1,       //失败
		UCOMM_SUCCESS        =  0		//成功
备	 注: 无
*************************************************************************************/
int Comm_ComSend(int HandleId,byte * Data,int DataLen);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.25	串口接收数据（Comm_ComRecv）在指定时间内接收指定长度数据
输入参数：HandleId   通讯句柄
		DataLen   期望接收的数据长度
		TimeOut   超时时间单位秒,0表示非阻塞
输出参数：Data   接收到的数
返    回：成功返回收到数据字节数
		UCOMM_CANCEL     =-3,       //按键取消
		UCOMM_TIMEOUT  = -2,       //超时
		UCOMM_FAIL     = -1,       //失败
备	 注: 响应取消键KEY_CANCEL
*************************************************************************************/
int Comm_ComRecv(int HandleId,byte * Data,int DataLen,int TimeOut);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.26	串口清缓存（Comm_ComClrBuf）
输入参数：HandleId   通讯句柄
输出参数：无
返    回：UCOMM_FAIL           = -1,       //失败
		UCOMM_SUCCESS        =  0		//成功
备	 注: 无
*************************************************************************************/
int Comm_ComClrBuf(int HandleId);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.27	关闭串口（Comm_ComClose）通讯串口断链,释放资源
输入参数：HandleId   通讯句柄
输出参数：无
返    回：UCOMM_FAIL           = -1,       //失败
		UCOMM_SUCCESS        =  0		//成功
备	 注: 无
*************************************************************************************/
int Comm_ComClose(int HandleId);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.28	创建SSL句柄(Comm_SSLNew)
输入参数：无
输出参数：无pnSSL   SSL句柄
返    回：UCOMM_SSL_RESOURCE             = -17, //超过SSL最大限制
		UCOMM_FAIL           = -1,       //失败
		UCOMM_SUCCESS        =  0		//成功
备	 注: 通过USSL_New创建一个SSL句柄,通过USSL_Free释放一个SSL句柄;
		SSL操作之前需要先创建句柄,使用完成注意释放句柄资源
*************************************************************************************/
int Comm_SSLNew(USSL_HANDLE *pnSSL);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.29	释放SSL句柄(Comm_SSLFree)
输入参数：nSSL   SSL句柄
输出参数：无
返    回：UCOMM_FAIL           = -1,       //失败
		UCOMM_SUCCESS        =  0		//成功
备	 注: 通过USSL_New创建一个SSL句柄,通过USSL_Free释放一个SSL句柄;
		SSL操作之前需要先创建句柄,使用完成注意释放句柄资源
*************************************************************************************/
int Comm_SSLFree(USSL_HANDLE nSSL);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.30	加载CA、证书、私钥(Comm_SSLLoadCA_Cert_Key)
输入参数：nSSL      SSL句柄
		pszCA     CA文件名
		pszCert   证书文件名,如果服务端不验证pos,可以置NULL
		pszKey    私钥文件名,如果服务端不验证pos,可以置NULL
		nFormat   CA、证书、私钥文件格式,参见enum USSLFileFormat
输出参数：无
返    回：UCOMM_SSL_NONSUPPORT           = -16, //不支持的文件格式
		UCOMM_SSL_LOAD_KEY_FAIL        = -11,  //加载私钥失败
		UCOMM_SSL_LOAD_CERT_FAIL       = -10,  //加载证书失败
		UCOMM_SSL_LOAD_CA_FAIL         = -9,  //加载CA失败
		UCOMM_DEVICE_UNAVAILABLE       = -8,   //设备不可用
		UCOMM_PARA_ERR                 = -7,   //参数错
		UCOMM_FAIL                     = -1,   //失败
		UCOMM_SUCCESS                  =  0,   //成功
备	 注: 无
*************************************************************************************/
int Comm_SSLLoadCA_Cert_Key(USSL_HANDLE nSSL, const char *pszCA, const char *pszCert, const char *pszKey, int nFormat);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.31	设置SSL连接参数(Comm_SSLSetOption)
输入参数：nSSL      SSL句柄
		nProtocol SSL协议版本,参见enum UProtocolType
		nCipher   SSL密码套件,参见enum USSLStatus
输出参数：无
返    回：UCOMM_SSL_NONSUPPORT       = -16, //不支持的协议版本、密码套件
		UCOMM_PARA_ERR                 = -7,   //参数错
		UCOMM_FAIL                     = -1,   //失败
		UCOMM_SUCCESS                  =  0,   //成功
备	 注: 不支持设置的厂商,使用实际支持的协议、算法套件
*************************************************************************************/
int Comm_SSLSetOption(USSL_HANDLE nSSL, int nProtocol, int nCipher);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.32	建立连接(Comm_SSLConnect),连接到SSL服务器
输入参数：nSSL      SSL句柄
		pszIPAddr IP地址
		nPort     端口号
		nTimeout超时时间,单位毫秒ms
输出参数：无
返    回：UCOMM_SSL_NONSUPPORT    = -16, //不支持的协议版本、密码套件
		UCOMM_SSL_CERT_NOT_YET_VALID   = -15, //对方证书还未生效
		UCOMM_SSL_CERT_HAS_EXPIRED     = -14,  //对方证书已过期
		UCOMM_CANCEL                   = -3,   //按键取消
		UCOMM_TIMEOUT                  = -2,   //超时
		UCOMM_FAIL                     = -1,   //失败
		UCOMM_SUCCESS                  =  0,   //成功
备	 注: 连接成功后必须调用USSL_Disconnect之后再进行新的连接
*************************************************************************************/
int Comm_SSLConnect(USSL_HANDLE nSSL, const char *pszIPAddr, int nPort, int nTimeout);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.33	断开连接(Comm_SSLDisconnect)
输入参数：nSSL      SSL句柄
输出参数：无
返    回：UCOMM_SSL_NOCONNECT            = -13,  //SSL还未连接
		UCOMM_FAIL                     = -1,   //失败
		UCOMM_SUCCESS                  =  0,   //成功
备	 注: 连接成功后必须调用USSL_Disconnect之后再进行新的连接
*************************************************************************************/
int Comm_SSLDisconnect(USSL_HANDLE nSSL);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.34	发送数据(Comm_SSLSend)
输入参数：nSSL      SSL句柄
		psBuf     发送数据缓存
		nBufLen   发送数据长度
输出参数：无
返    回：成功返回实际发送数据长度
		UCOMM_SSL_NOCONNECT            = -13,  //SSL还未连接
		UCOMM_LOGOFF                   = -4,   //通讯链路断开
		UCOMM_FAIL                     = -1,   //失败
备	 注: 无
*************************************************************************************/
int Comm_SSLSend(USSL_HANDLE nSSL, const byte *psBuf, uint nBufLen);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.35	接收数据(Comm_SSLReceive)
输入参数：nSSL      SSL句柄
		nBufLen   期望接收数据长度
		nTimeout  接收超时时间,0表示非阻塞
输出参数：psBuf     接收数据缓存
返    回：成功返回实际接收数据长度
		UCOMM_SSL_NOCONNECT            = -13,  //SSL还未连接
		UCOMM_LOGOFF                   = -4,   //通讯链路断开
		UCOMM_TIMEOUT                  = -2,   //超时
		UCOMM_FAIL                     = -1,   //失败
备	 注: 无
*************************************************************************************/
int Comm_SSLReceive(USSL_HANDLE nSSL, byte *psBuf, uint *pnBufLen, int nTimeout);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.36	域名解析(Comm_GetHostByName)
输入参数：pszDnsName     域名
输出参数：pszIp1主机IP1
		pszIp2主机IP2
返    回：UCOMM_FAIL                     = -1,   //失败
		UCOMM_SUCCESS                  =  0,   //成功
备	 注: 无
*************************************************************************************/
int Comm_GetHostByName(char *pszDnsName, char *pszIp1, char *pszIp2);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.37	获取GSM基站列表（Comm_GetBaseStation_GSM）
输入参数：pnNumList      最大允许获取的基站个数
输出参数：GSMStationList GSM基站列表
		pnNumList      实际获取到的基站个数
返    回：UCOMM_DEVICE_UNAVAILABLE = -8, //设备不可用
		UCOMM_FAIL                     = -1,   //失败
		UCOMM_SUCCESS                  =  0,   //成功
备	 注: 第一个为附着主基站,其他为临近基站
*************************************************************************************/
int Comm_GetBaseStation_GSM(BASESTATIONGSM GSMStationList[], int *pnNumList);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.38	获取CDMA基站信息（Comm_GetBaseStation_CDMA）
输入参数：无
输出参数：pstCDMAStation   CDMA基站信息
返    回：UCOMM_DEVICE_UNAVAILABLE = -8, //设备不可用
		UCOMM_FAIL                     = -1,   //失败
		UCOMM_SUCCESS                  =  0,   //成功
备	 注: 无
*************************************************************************************/
int Comm_GetBaseStation_CDMA(BASESTATIONCDMA *pstCDMAStation);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.39	获取SIM卡ICCID（Comm_GetICCID）
输入参数：无
输出参数：pszICCID    集成电路卡识别码
返    回：UCOMM_DEVICE_UNAVAILABLE = -8, //设备不可用
		UCOMM_FAIL                     = -1,   //失败
		UCOMM_SUCCESS                  =  0,   //成功
备	 注: ICCID为IC卡的唯一识别号码,共有20位数字组成。其编码格式为XXXXXX 0MFSS YYGXX XXXXX
		中国移动编码格式：89860 0MFSS YYGXX XXXXP
		中国联通编码格式：89860 1YYMH AAAXX XXXXP
		中国电信编码格式：89860 3MYYH HHXXX XXXXX
*************************************************************************************/
int Comm_GetICCID(char *pszICCID);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.6.40	获取SIM卡手机号（Comm_GetPhoneNum）
输入参数：无
输出参数：pszPhoneNum  手机号
返    回：UCOMM_DEVICE_UNAVAILABLE = -8, //设备不可用
		UCOMM_FAIL                     = -1,   //失败
		UCOMM_SUCCESS                  =  0,   //成功
备	 注: 新SIM卡可能无法获取,需要SIM卡写入手机号
*************************************************************************************/
int Comm_GetPhoneNum(char *pszPhoneNum);


#endif /*__LIBAPI_COMM_HEADER__*/
