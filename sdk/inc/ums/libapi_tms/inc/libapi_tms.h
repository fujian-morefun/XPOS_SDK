#ifndef __LIBAPI_TMS_HEADER__
#define __LIBAPI_TMS_HEADER__

#include "def.h"



//HINSTANCE g_hInst=NULL;

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.12.3	获取TMS类模块版本号(UTMS_GetModuleVer)
输入参数：无
输出参数：pszVer   模块版本号
返    回：成功返回模块版本号长度
		UTMS_FAIL   =-1,           //失败
备	 注: 无
*************************************************************************************/
int UTMS_GetModuleVer(char *pszVer);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.12.4	获取本机应用列表(UTMS_GetAllApp)
输入参数：无
输出参数：st_UAppInfoList：应用信息参见struct UAPPINFOLIST
返    回：UTMS_FAIL       = -1,       //失败
		UTMS_OK         =  0        //成功 
备	 注: 获取到的应用信息包含主控本身，无需获取子应用的商户号、终端号
*************************************************************************************/
int UTMS_GetAllApp(UAPPINFOLIST *st_UAppInfoList);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.12.5	运行子应用(UTMS_RunApp)
输入参数：AppName: 子应用名
		TLVPara: TLV格式的参数
		ParaLen：参数缓冲数组的大小
输出参数：无
返    回：UTMS_FAIL       = -1,       //失败
		UTMS_OK         =  0        //成功
备	 注: 子应用切回主控再回子应用，不用回到原点，即切出、切入两个过程是独立的；
		由主控应用程序控制子应用对应的中文名、排序、是否禁用等可修改信息；
		主控和子应用的参数传递使用TLV方式，通过umsmain函数的argv传入子应用，
		argv的第一个值为ParaLen即缓冲数组的大小，argv的第二个值为TLVPara的内容
*************************************************************************************/
int UTMS_RunApp(cchar *AppName, char *TLVPara, uint ParaLen);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.12.6	TMS应用下载(UTMS_DownLoadApp)
输入参数：pt_TmsParameters:参见UTMSPARAMETERS
输出参数：st_ModuleList：struct UMODULEINFOLIST
		pvSave：TMS下载库传出需要主控保存的内容
		puiSaveLen：需要主控保存的长度
		pvSave和puiSaveLen主控保存后在应用安装UTMS_SetupApp的时候使用，目前这2个参数联迪有用
返    回：UTMS_FAIL       = -1,       //失败
		UTMS_OK         =  0        //成功
备	 注: API内部实现与后台动态库对比各个模块版本号，并下载版本号高的模块，下载完成后传出下载列表
*************************************************************************************/
int UTMS_DownLoadApp(const UTMSPARAMETERS *pt_TmsParameters,UMODULEINFOLIST *st_ModuleList, void *pvSave, uint *puiSaveLen);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.12.7	应用安装(UTMS_SetupApp)
输入参数：st_ModuleList：UMODULEINFOLIST数组
		pvSave：TMS下载库传出需要主控保存的内容
		puiSaveLen：需要主控保存的长度
		pvSave和uiSaveLen是主控在UTMS_DownLoadApp后保存后在应用安装UTMS_SetupApp的时候使用，目前这2个参数联迪有用
输出参数：无
返    回：UTMS_FAIL       = -1,       //失败
		UTMS_OK         =  0        //成功
备	 注: 自动判断应用是否存在，不存在则安装，存在则覆盖更新；
		下载结束后调用；
		目前考虑所有应用一次性安装，预留应用分批更新的功能；
		如果后台配置的是应用删除任务，需要在此API内实现应用删除功能
*************************************************************************************/
int UTMS_SetupApp(const UMODULEINFOLIST *st_ModuleList, void *pvSave, uint uiSaveLen);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.12.8	删除子应用(UTMS_RemoveApp)
输入参数：AppName: 子应用名
输出参数：无
返    回：UTMS_FAIL       = -1,       //失败
		UTMS_OK         =  0        //成功
备	 注: 同时删除此应用的私有文件，不删除公有文件
*************************************************************************************/
int UTMS_RemoveApp(cchar *AppName);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.12.9	获取终端硬件信息(UTMS_GetTermMessage)
输入参数：无
输出参数：TermMessage：下文注明
返    回：UTMS_FAIL       = -1,       //失败
		UTMS_OK         =  0        //成功
备	 注: 获取终端硬件信息，TMS交易报文中使用
*************************************************************************************/
int UTMS_GetTermMessage(char *TermMessage);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.12.10	设置TMS下载debug信息(UTMS_SetDebug)
输入参数：ucShowFlag:日志输出模式 
		0 不生成日志
		1少量关键日志 通过UTMS_SendDebugLog获取
		2 所有日志实时发出
		pcDeviceName：输出设备端口名称例如COM1
		ucBaudRate:输出信息波特率
输出参数：无
返    回：UTMS_FAIL       = -1,       //失败
		UTMS_OK         =  0        //成功
备	 注: 不支持的可以预留
*************************************************************************************/
int UTMS_SetDebug(unsigned char ucShowFlag, const char* pcDeviceName, unsigned char ucBaudRate);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.12.11	输出TMS下载debug信息(UTMS_SendDebugLog)
输入参数：无
输出参数：无
返    回：UTMS_FAIL       = -1,       //失败
		UTMS_OK         =  0        //成功
备	 注: 不支持的可以预留
输出TMS下载debug信息，输出信息使用端口和波特率在UTMS_SetDebug函数中设置
*************************************************************************************/
int UTMS_SendDebugLog(void);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.12.12	获取TMS参数标签内容(UTMS_GetTmsPara)
输入参数：AppName：应用名
		ParaName：参数标签名
输出参数：DataLength：参数长度
		ParaValue：参数内容
返    回：UTMS_FAIL       = -1,       //失败
		UTMS_OK         =  0        //成功
备	 注: 同时支持主控、子应用调用
根据应用名AppName，以及ParaName的参数标签，来获取TMS下载的参数内容
*************************************************************************************/
int UTMS_GetTmsPara(cchar *AppName , cchar *ParaName, int *DataLength, void *ParaValue);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.12.13	检测TMS参数是否需要更新(UTMS_CheckTmsPara)
输入参数：AppName：应用名
输出参数：IsUpdate：更新标识，0-无需更新，1-需要更新
返    回：UTMS_FAIL       = -1,       //失败
		UTMS_OK         =  0        //成功
备	 注: 进入应用后检测TMS参数是否需要更新，如需更新则调用UTMS_GetTmsPara，
		并调用UTMS_CompleteTmsPara结束更新
*************************************************************************************/
int UTMS_CheckTmsPara(cchar *AppName, byte *IsUpdate);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：yangjy
功    能：2.2.12.14	TMS参数更新完成(UTMS_CompleteTmsPara)
输入参数：AppName：应用名
输出参数：无
返    回：UTMS_FAIL       = -1,       //失败
		UTMS_OK         =  0        //成功
备	 注: 实现参数文件删除功能
*************************************************************************************/
int UTMS_CompleteTmsPara(cchar *AppName);

/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	 者：白建中
功    能：设置TMS参数标签内容
输入参数：AppName：应用名
		ParaName：参数标签名
		ParaValue：参数内容
		DataLength：参数长度
返    回：UTMS_FAIL       = -1,       //失败
		UTMS_OK         =  0        //成功
备	 注: 同时支持主控、子应用调用
*************************************************************************************/
int UTMS_SetTmsPara(cchar *AppName , cchar *ParaName, void *ParaValue, int DataLength);

#endif /*__LIBAPI_TMS_HEADER__*/
