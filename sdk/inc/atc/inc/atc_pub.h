/*! \file atc_pub.h
	\brief AT命令封装
*	\author lx
*	\date 2014/02/08
*/
#pragma once

#include "pub\pub.h"

#ifdef __cplusplus
extern "C"{
#endif


//#define SOCK_HEX_CODE

#define AT_ERROR    -1
#define AT_NO_ECHO  -2

/**
* @brief 设置apn
* @param apn apn名称
* @return 0成功
*/
LIB_EXPORT int ap_set_apn(char *apn);
/**
* @brief 读取imei
* @param buff 缓冲区
* @param len 缓冲区位置
* @return 0成功
*/
LIB_EXPORT int ap_get_imei(char *buff , int len);
/**
* @brief 读取模块版本
* @param buff 缓冲区
* @param len 缓冲区长度
* @return 0成功
*/
LIB_EXPORT int ap_get_model_ver(char *buff , int len);
/**
* @brief 发送at命令等待返回
* @param cmd 命令
* @param timeover 超时时间
* @param retstr 返回指令
* @param len 指令长度
* @param count 重发次数
* @return 0成功
*/
LIB_EXPORT int ag_send_wait_return(char *cmd , int timeover , char * retstr , int len , int count);
/**
* @brief 设置回显
* @param val 回显值
* @return 0成功
*/
LIB_EXPORT int ap_set_e_val(int val);
LIB_EXPORT int ap_get_echo();
/**
* @brief 读取csq
* @param csq_val 缓冲区
* @return 0成功
*/
LIB_EXPORT int ap_get_csq(int *csq_val);
/**
* @brief 读取creg
* @param creg_val 缓冲区
* @return 0成功
*/
LIB_EXPORT int ap_get_creg(int *creg_val);
/**
* @brief 读取pin
* @return 0成功
*/
LIB_EXPORT int ap_get_cpin();
/**
* @brief 读取imei
* @param buff 缓冲区
* @param len 缓冲区长度
* @return 0成功
*/
LIB_EXPORT int ap_get_imsi(char *buff , int len);


/**
* @brief ATC初始化
* @return 
*/
LIB_EXPORT int atc_init();
LIB_EXPORT void atc_win32_init();
/**
* @brief 获取是否已注册网络
* @return 0未注册  1已注册
*/
LIB_EXPORT int atc_isreg();
/**
* @brief 获取csq 值
* @return csq值
*/
LIB_EXPORT int atc_csq();
/**
* @brief 获取imei
* @return imei值
*/
LIB_EXPORT const char * atc_imei();
/**
* @brief 获取imsi
* @return imsi值
*/
LIB_EXPORT const char * atc_imsi();

/**
* @brief 获取信号格数
* @return 0 未注册上网络  1-4信号格数
*/
LIB_EXPORT int atc_signal();

/**
* @brief 获取CPIN状态
* @return 0失败 1锁卡 2正常 3puk
*/
LIB_EXPORT int atc_cpin();


/**
* @brief 获取模块版本号
* @return 模块版本号
*/
LIB_EXPORT const char * atc_model_ver();

LIB_EXPORT int atc_cell();
LIB_EXPORT int atc_lac();

typedef enum
{
	MODULE_SIMCOM = 0,		//Simcom模块
	MODULE_SPREADTRUM = 1,	//展讯模块(AT188MA)
	MODULE_M62 = 2,			//M62模块 ,M35模块
	MODULE_AT139D = 3,		//AT139D
	MODULE_MC509 = 4,		//华为MC509
	MODULE_A8500 = 5,		//A8500

}MODULE_TYPE_E;

LIB_EXPORT MODULE_TYPE_E atc_getModuleType();

#define MODULE_IS_M35	atc_getModuleType() == MODULE_M62
#define MODULE_IS_A8500	atc_getModuleType() == MODULE_A8500



LIB_EXPORT const char * atc_iccid();


//设定外部缓冲区 AT+CCED=0,2  用于返回内容
LIB_EXPORT void atc_setccedbuff(char *pbuff, int nbufflen);

typedef struct _cceditem{
	unsigned short	MCC;					//移动国家号码
	unsigned char	MNC;					//移动网络号码
	unsigned short	LAC;					//位置区域号
	unsigned short	CELL;					//小区号
	unsigned char	BSIC;					//基站标示码
	unsigned char	BCCH_Freq_absolute;		//BCCH 信道号
	unsigned char	RxLev;					//接收信号强度
}ccedItem;

LIB_EXPORT ccedItem * atc_getcceditems( int *outcount);

LIB_EXPORT int atc_modelreset_set();

#ifdef __cplusplus
}
#endif	