/*! \file osl_system.h
	\brief 系统功能
*	\author lx
*	\date 2014/02/08
*/
#ifndef _OSL_SYSTEM_H_____
#define _OSL_SYSTEM_H_____

#include "pub\pub.h"

#ifdef OS_LINUX
	#define EX_FLASH_BASE_ADDR	(0x0)
#else
	#define EX_FLASH_BASE_ADDR	(0x0)
#endif

#define EXT_FLASH_DEV_DATA1_ADDR				(EX_FLASH_BASE_ADDR + 0x000000)
#define EXT_FLASH_DEV_DATA2_ADDR				(EX_FLASH_BASE_ADDR + 0x001000)

#define EXT_FLASH_TMS_MD5_ADDR					(EX_FLASH_BASE_ADDR + 0x010000)
#define EXT_FLASH_TMS_AREA_ADDR					(EX_FLASH_BASE_ADDR + 0x011000)
#define EXT_FLASH_HZ_12_ADDR					(EX_FLASH_BASE_ADDR + 0x091000)
#define EXT_FLASH_HZ_16_ADDR					(EX_FLASH_BASE_ADDR + 0x11E000)
#define EXT_FLASH_ASC_12_24_ADDR				(EX_FLASH_BASE_ADDR + 0x1DA000)
#define EXT_FLASH_ASC_16_32_ADDR				(EX_FLASH_BASE_ADDR + 0x1DD000)
#define EXT_FLASH_UC2GBK_ADDR					(EX_FLASH_BASE_ADDR + 0x1E2000)
#define EXT_FLASH_GBK2UC_ADDR					(EX_FLASH_BASE_ADDR + 0x1FB000)
#define EXT_FLASH_ASC_06_12_ADDR				(EX_FLASH_BASE_ADDR + 0x213000)

#define EXT_FLASH_HZ_24_ADDR					(EX_FLASH_BASE_ADDR + 0x20C000)
#define EXT_FLASH_HZ_32_ADDR					(EX_FLASH_BASE_ADDR + 0x3B1000)



#ifdef __cplusplus
extern "C"{
#endif

/**
* @brief 获取程序路径
* @param outpath 路径
* @param nMaxLen 路径大小
* @return 
*/
LIB_EXPORT void osl_getAppPath( char *outpath ,int nMaxLen);

//
/**
* @brief 文件名前面填充程序路径
* @param szFileName 文件名
* @param outpath 路径
* @param nMaxLen 路径大小
* @return 填充好的路径
*/
LIB_EXPORT const char * osl_fillAppPath( const char *szFileName,char *outpath ,int nMaxLen);

//设置序列号
LIB_EXPORT void osl_setTerminalID(char* tid );

LIB_EXPORT int osl_check_sn_sig();
LIB_EXPORT int osl_check_pk_sig();
LIB_EXPORT int osl_check_sc_sig();
LIB_EXPORT int osl_check_tms_lock();
LIB_EXPORT void osl_setTmsLock(int flag);

//读取序列号
/**
* @brief 读取序列号
* @param outdata
* @param nMaxLen
* @return 
*/
LIB_EXPORT const char* osl_getTerminalID( char *outdata ,int nMaxLen );


//读取带厂商编号+终端类型 序列号（银联21号文）
/**
* @brief 读取序列号
* @param outdata
* @param nMaxLen
* @return 
*/
LIB_EXPORT int get_vendor_TerminalID(char*outdata ,int nMaxLen);

//读取公钥开关和厂品代码
/**
* @brief 读取公钥代码
* @param outdata
* @param nMaxLen
* @return 
*/
LIB_EXPORT int osl_getKeyPubID( char *outdata ,int nMaxLen );
LIB_EXPORT void osl_getKeyPub(char *buff, int len);
LIB_EXPORT void osl_setKeyPub(char *buff, int len );
LIB_EXPORT void osl_get_log_data(char * buff , int len);
LIB_EXPORT void osl_set_log_data(char * buff , int len);

LIB_EXPORT int osl_set_imei(char *imei);
LIB_EXPORT int osl_check_imei(char *imei);

LIB_EXPORT int osl_set_sc_enable(int val);
LIB_EXPORT int osl_get_sc_enable();

LIB_EXPORT void osl_set_snkey(char *key,int mode);
LIB_EXPORT int osl_get_snkey(char *key);
LIB_EXPORT int osl_get_snkey_mode();
LIB_EXPORT int osl_get_snkey_check();

int osl_get_module_type();
int osl_set_module_type(int val);

LIB_EXPORT int osl_set_psn(char * psn);
LIB_EXPORT void osl_get_psn(char * psn);



/**
* @brief 设置应用是否忙
* @param val 忙状态
* @return 
*/
LIB_EXPORT void osl_set_app_busy(char val);
/**
* @brief 读取应用是否忙
* @return 忙状态
*/
LIB_EXPORT char osl_get_app_busy();


LIB_EXPORT void osl_power_off();
LIB_EXPORT void osl_system_authorize(int val);

LIB_EXPORT int osl_refresh_lock(int status);

LIB_EXPORT int osl_get_onchip_flag();

void osl_get_ts(int * left, int *right, int *top, int *bottom);
void osl_set_ts(int left, int right, int top, int bottom);

LIB_EXPORT int osl_get_scan_support();
LIB_EXPORT void osl_set_scan_support(int scan_support);

LIB_EXPORT const char* osl_getTerminalID_real( char *outdata ,int nMaxLen );
LIB_EXPORT const char* get_vendor_type();//设备类型 02：传统POS 03：mPOS 04：智能POS 
LIB_EXPORT const char* get_vendor_code();//终端入网认证编号 MF90入网编号P3278
LIB_EXPORT int get_vendor_factor(char*SrcFactor,int nSrclen,char *sEnFactor);//加密随机因子

#ifdef __cplusplus
}
#endif

#endif