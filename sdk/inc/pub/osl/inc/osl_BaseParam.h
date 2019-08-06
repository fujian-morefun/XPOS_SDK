#pragma once
/*! \file osl_BaseParam.h
	\brief 基础参数
*	\author lx
*	\date 2014/02/07
*/
#include "pub/pub.h"

#define TS_DATA_FILE		"data\\ts_data.ini"
#define SYSTEM_PROFILE		"data\\sysCfg.ini"		//系统配置文件名称
#define TAMPER_INI_FILENAME	"data\\Tamper.ini"

#if OS_LINUX | WIN32
#define DATAVERSION_FILENAME  "xxxx\\data.ini"    //数据版本号
#else
#define DATAVERSION_FILENAME  "data\\data.ini"    //数据版本号
#endif

#define BASEPARAM_SECTION	"BaseParam"			//在基础参数在配置文件中的段名称
#define LCDCONTRAST			"lcdContrast"		//液晶对比度,0~63
#define KEYSOUNDOPEN		"keySoundOpen"		//按键音开关,0关1开
#define TTSSOUNDOPEN		"ttsSoundOpen"		//tts开关,0关1开
#define LCDLIGHTTIME		"lcdLightTime"		//背光时长，以秒为单位
#define ENERCYTIME          "enercyTime"		//节能时间
#define POWER_DOWN_TIME		"PowrDownTime"		//关机时间
#define NET_MODE			"netMode"			//网络模式

#define POWER_SECTION		"Power"				//电源管理部分在配置文件中的段名称
#define POWER_KEY_DOWN_TIME	"PowerKeyDownTime"		//电源键按下关机时长

#define TS_PARAM_SECTION	"param_section"
#define TS_LEFT_KEY			"ts_left_key"
#define TS_RIGHT_KEY		"ts_right_key"
#define TS_TOP_KEY			"ts_top_key"
#define TS_BOTTOM_KEY		"ts_bottom_key"

#define LCD_LIGHT_MAX	99999999

LIB_EXPORT void osl_ts_get(int *left , int *right , int * top, int * bottom);
LIB_EXPORT void osl_ts_set(int left , int right , int top, int bottom);
LIB_EXPORT int osl_get_language();
LIB_EXPORT void osl_set_language(int val);

#define DEVICE_VISION	 osl_getDeviceVision()  //系统版本号


/**
* @brief 获取系统版本号
* @return 系统版本号
*/
LIB_EXPORT const char * osl_getDeviceVision();



#define APP_VISION	 osl_getAppVision()  //应用版本号




/**
* @brief 获取应用版本号
* @return 应用版本号
*/
LIB_EXPORT const char * osl_getAppVision();
/**
* @brief 设置应用版本号
* @param 应用版本号
* @return 
*/
LIB_EXPORT void osl_setAppVision(const char *appvision);

#define DATA_VISION	 osl_GetDataVision()  //应用版本号

/**
* @brief 获取应用版本号
* @return 
*/
LIB_EXPORT  const char * osl_GetDataVision(); //获取数据版本号
/*
* [BaseParam]
* lcdContrast=60
* keySoundOpen=1
* lcdLightTime=120
*
*直接通过read_profile_int读，write_profile_int写
*/


/**
* @brief 蜂鸣器响铃
* @param 时间
* @return 
*/
LIB_EXPORT int osl_BuzzerSound(int nMillisecond);


/**
* @brief 设置是否开启按键音
* @param 1开 0关
* @return 
*/
LIB_EXPORT int osl_SwitchKeySound(int nOpen);


/**
* @brief 获取当前按键音是否开启
* @return 1开 0关
*/
LIB_EXPORT int osl_IsKeySoundOpen();


/**
* @brief 液晶背光时长秒为单位
* @return 背光时长
*/
LIB_EXPORT int osl_lcd_BackLightTime();


LIB_EXPORT int osl_get_lcd_contrast();
LIB_EXPORT int osl_set_lcd_contrast(int val);



/**
* @brief 设置液晶背光时长，秒为单位
* @param nTime 背光时长
* @return 
*/
LIB_EXPORT int osl_lcd_SetBackLightTime(int nTime);


/**
* @brief 获取硬件设备型号
* @return 
*/
LIB_EXPORT int osl_GetDeviceType();
LIB_EXPORT const char *osl_getDeviceTypeName();

LIB_EXPORT int osl_get_is_mh();
LIB_EXPORT int osl_get_is_k21();
LIB_EXPORT int osl_get_is_m90();
LIB_EXPORT int osl_get_is_printer();
LIB_EXPORT int osl_get_is_power2quit();
LIB_EXPORT int osl_get_is_dual_module();
LIB_EXPORT int osl_get_is_m66();
LIB_EXPORT int osl_get_is_m67();
LIB_EXPORT int osl_get_is_m68();
LIB_EXPORT int osl_get_is_m90_key_map();
LIB_EXPORT int osl_get_is_m69();
enum{
	DEV_MODE_QR = 0,		// 码牌
	DEV_MODE_SCAN,			// 扫描枪
};

// 设备
LIB_EXPORT int osl_get_dev_mode();


/**
* 设置硬件设备型号
*@return 设备型号 
* 
*/
LIB_EXPORT int ols_SetDeviceType(int  nDeviceType);

//! 通讯模块类型
enum{
	MODEL_WIRELESS = 0,		///<无线
	MODEL_MODEM,			///<有线
	MODEL_WIFI,				///<wifi
	MODEL_WIN32_SOCK,	///<模拟器

};
enum{
	MODEL_MODE_ONLY_WIRELESS = 0,		// 仅 无线
	MODEL_MODE_ONLY_WIFI,				// 仅 wifi
	MODEL_MODE_FRIST_WIRELESS,		// 优先 无线
	MODEL_MODE_FRIST_WIFI,				// 优先 wifi
};

/**
* @brief osl_model_type
* @return MODEL_WIRELESS 无线 MODEL_MODEM有线
*/
LIB_EXPORT int osl_model_type();
LIB_EXPORT void osl_model_set(int type);
/**
* @brief 初始化安全相关
* @return 
*/
LIB_EXPORT void osl_initTamper();
/**
* @brief 设置节能时长，秒为单位
* @param nTime 时长
* @return 
*/
LIB_EXPORT int osl_Enercy_SetTime( int nTime );

/**
* @brief 节能时长秒为单位
* @return 节能时长
*/
LIB_EXPORT int osl_Enercy_Time();

/**
* @brief 关机时间秒为单位
* @return 关机时间
*/
LIB_EXPORT int osl_lcd_PowerDownTime();

/**
* @brief 设置关机时间，秒为单位
* @param nTime 时间
* @return 
*/
LIB_EXPORT int osl_lcd_SetPowerDownTime( int nTime );
LIB_EXPORT int osl_get_net_mode();
LIB_EXPORT void osl_set_net_mode(int mode);
