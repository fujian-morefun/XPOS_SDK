#ifndef __LIBAPI_MAG_HEADER__
#define __LIBAPI_MAG_HEADER__

#include "libapi_pub.h"

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.8.3	获取磁条卡类模块版本号(Mag_GetModuleVer)
Input : Nothing
Output : pszVer   模块版本号
return: 成功返回模块版本号长度
		UTRACK_FAIL   =-1,           Fail
Remarks: Nothing
*************************************************************************************/
int Mag_GetModuleVer(char *pszVer);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.8.4	磁条读卡器初始化（Mag_Init）
Input : Nothing
Output : Nothing
return: UTRAC_MAG_FAIL        = -5,     //磁条卡读卡器操作失败
		UTRAC_MAG_OK        = 1,      //磁条卡读卡器操作成功
Remarks: Nothing
*************************************************************************************/
int Mag_Init(void);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.8.5	磁条读卡器读卡（Mag_GetAllTrack）可读取1、2、3磁道信息SCII码格式
Input : LrcFlag: 参考enum TrackLrc，如LRC_TRACK2 | LRC_TRACK3，表示同时校验磁道2、3LRC(不支持的厂商Nothing效)
		WaitFlag：等待标识，0为不等待立即返回；>0为等待时间单位为秒
Output : CardBuf1：一磁数据
		CardBuf2：二磁数据
		CardBuf3：三磁数据
return: UTRACK_MAG_FAIL        = -5,      //磁条卡读卡器操作失败
		UTRACK_NOEVENT   = -4,     //不等待时才会返回，说明本次调用未检测到刷卡
		UTRACK_CONTROL       = -3,     // 用户退出 
		UTRACK_TIMEOUT   = -2,     // 刷卡超时 
		UTRACK_FAIL      = -1,     // 刷卡但失败 
		UTRACK_OK        = 0,      //等待时,返回此值则认为刷卡成功(至少刷出了一个磁道); 不等待时,为检测到刷卡并读取成功
		UTRACK_NUM       = 2      // 手输卡号(预留) 
Remarks: 各厂商保持原刷卡处理方式不变；
		如果未读到磁道数据则相应的缓冲区Nothing数据；
		输出磁道数据已去掉起始符号、结束符号、校验值；
		根据LrcFlag值对相应磁道进行LRC校验，校验失败返回UTRACK_FAIL
*************************************************************************************/
int Mag_GetAllTrack(byte *CardBuf1, byte *CardBuf2, byte *CardBuf3, int LrcFlag, ushort WaitFlag);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.8.6	关闭磁条卡设备（Mag_Close）
Input : Nothing
Output : Nothing
return: UTRAC_MAG_FAIL        = -5,     //磁条卡读卡器操作失败
		UTRAC_MAG_OK        = 1,      //磁条卡读卡器操作成功
Remarks: Nothing
*************************************************************************************/
int Mag_Close(void);


#endif /*__LIBAPI_MAG_HEADER__*/
