/*! \file osl_system.h
	\brief system function
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
* @brief Get the program path
* @param outpath Route
* @param nMaxLen Path size
* @return 
*/
LIB_EXPORT void osl_getAppPath( char *outpath ,int nMaxLen);

//
/**
* @brief Fill in the program path before the file name
* @param szFileName file name
* @param outpath Route
* @param nMaxLen  Path size
* @return Filled paths
*/
LIB_EXPORT const char * osl_fillAppPath( const char *szFileName,char *outpath ,int nMaxLen);

//Setting Sequence Number
LIB_EXPORT void osl_setTerminalID(char* tid );

LIB_EXPORT int osl_check_sn_sig();
LIB_EXPORT int osl_check_pk_sig();
LIB_EXPORT int osl_check_sc_sig();
LIB_EXPORT int osl_check_tms_lock();
LIB_EXPORT void osl_setTmsLock(int flag);

//Read Sequence Number
/**
* @brief Read Sequence Number
* @param outdata
* @param nMaxLen
* @return 
*/
LIB_EXPORT const char* osl_getTerminalID( char *outdata ,int nMaxLen );
LIB_EXPORT void osl_getTerminalID_EX( char *outdata ,int nMaxLen );

//Read serial number with manufacturer number + terminal type (UnionPay No. 21)
/**
* @brief Read Sequence Number
* @param outdata
* @param nMaxLen
* @return 
*/
LIB_EXPORT int get_vendor_TerminalID(char*outdata ,int nMaxLen);

//Read Public Key Switches and Factory Codes
/**
* @brief Read public key code
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
* @brief Set whether the application is busy
* @param val Busy state
* @return 
*/
LIB_EXPORT void osl_set_app_busy(char val);
/**
* @brief Read application busy
* @return Busy state
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
LIB_EXPORT const char* get_vendor_type();//Device Type 02: Traditional POS 03: mPOS 04: Intelligent POS 
LIB_EXPORT const char* get_vendor_code();//Terminal Access Authentication Number MF90 Access Number P3278
LIB_EXPORT int get_vendor_factor(char*SrcFactor,int nSrclen,char *sEnFactor);//Encryption Random Factor


LIB_EXPORT void osl_magtek_open();
LIB_EXPORT void osl_magtek_close();


LIB_EXPORT int osl_init();
LIB_EXPORT int osl_start();


LIB_EXPORT int osl_lock( int * fd , int timeover);
LIB_EXPORT int osl_unlock( int * fd );

LIB_EXPORT int osl_task_create(void * pfun, int prio ,unsigned int stackbuff[],int stacksize);
#ifdef __cplusplus
}
#endif

#endif