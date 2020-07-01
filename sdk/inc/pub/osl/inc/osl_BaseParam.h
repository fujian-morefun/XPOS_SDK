#pragma once
/*! \file osl_BaseParam.h
	\brief Basic parameters
*	\author lx
*	\date 2014/02/07
*/
#include "pub/pub.h"

#define TS_DATA_FILE		"data\\ts_data.ini"
#define SYSTEM_PROFILE		"data\\sysCfg.ini"		//System Configuration File Name
#define TAMPER_INI_FILENAME	"data\\Tamper.ini"

#if OS_LINUX | WIN32
#define DATAVERSION_FILENAME  "xxxx\\data.ini"    //Data Version Number
#else
#define DATAVERSION_FILENAME  "data\\data.ini"    //Data Version Number
#endif

#define BASEPARAM_SECTION	"BaseParam"			//The segment name in the configuration file for the base parameter
#define LCDCONTRAST			"lcdContrast"		//Contrast of liquid crystal,0~63
#define KEYSOUNDOPEN		"keySoundOpen"		//Key Tone Switch,0 close 1 open
#define TTSSOUNDOPEN		"ttsSoundOpen"		//TTS switch, 0 off, 1 on
#define LCDLIGHTTIME		"lcdLightTime"		//Backlight duration in seconds
#define ENERCYTIME          "enercyTime"		//Energy saving time
#define POWER_DOWN_TIME		"PowrDownTime"		//Shutdown time
#define NET_MODE			"netMode"			//Network Model

#define POWER_SECTION		"Power"				//Section Name of Power Management Section in Configuration File
#define POWER_KEY_DOWN_TIME	"PowerKeyDownTime"		//Power button press shutdown time

#define TS_PARAM_SECTION	"param_section"
#define TS_LEFT_KEY			"ts_left_key"
#define TS_RIGHT_KEY		"ts_right_key"
#define TS_TOP_KEY			"ts_top_key"
#define TS_BOTTOM_KEY		"ts_bottom_key"
#define KEY_DOWNLOAD_STATE	"key_downlaod_state"

#define LCD_LIGHT_MAX	99999999

LIB_EXPORT void osl_ts_get(int *left , int *right , int * top, int * bottom);
LIB_EXPORT void osl_ts_set(int left , int right , int top, int bottom);
LIB_EXPORT int osl_get_language();
LIB_EXPORT void osl_set_language(int val);

#define DEVICE_VISION	 osl_getDeviceVision()  //System Version Number


/**
* @brief Getting System Version Number
* @return System Version Number
*/
LIB_EXPORT const char * osl_getDeviceVision();



#define APP_VISION	 osl_getAppVision()  //Application Version Number




/**
* @brief Get the application version number
* @return Application Version Number
*/
LIB_EXPORT const char * osl_getAppVision();
LIB_EXPORT const char * osl_getAppVersion2();
/**
* @brief Setting Application Version Number
* @param Application Version Number
* @return 
*/
LIB_EXPORT void osl_setAppVision(const char *appvision);

#define DATA_VISION	 osl_GetDataVision()  //Data Version Number

/**
* @brief Get the application version number
* @return 
*/
LIB_EXPORT  const char * osl_GetDataVision(); //Get the version number of the data
/*
* [BaseParam]
* lcdContrast=60
* keySoundOpen=1
* lcdLightTime=120
*
*Read directly through read_profile_int, write_profile_int
*/


/**
* @brief Buzzer rings
* @param time
* @return 
*/
LIB_EXPORT int osl_BuzzerSound(int nMillisecond);


/**
* @brief Set whether to turn on the key tone
* @param 1oepn  0close
* @return 
*/
LIB_EXPORT int osl_SwitchKeySound(int nOpen);


/**
* @brief Gets whether the current key tone is turned on
* @return 1oepn  0close 
*/
LIB_EXPORT int osl_IsKeySoundOpen();


LIB_EXPORT void osl_set_tts_sound(int nOpen );
LIB_EXPORT int osl_get_tts_sound();
/**
* @brief LCD backlight time in seconds
* @return Backlight duration
*/
LIB_EXPORT int osl_lcd_BackLightTime();


LIB_EXPORT int osl_get_lcd_contrast();
LIB_EXPORT int osl_set_lcd_contrast(int val);



/**
* @brief Set LCD backlight time in seconds
* @param nTime Backlight duration
* @return 
*/
LIB_EXPORT int osl_lcd_SetBackLightTime(int nTime);


/**
* @brief Obtain hardware model
* @return 
*/
LIB_EXPORT int osl_GetDeviceType();
LIB_EXPORT const char *osl_getDeviceTypeName();

LIB_EXPORT int osl_get_is_mh();
LIB_EXPORT int osl_get_is_k21();
LIB_EXPORT int osl_get_is_m90();
LIB_EXPORT int osl_get_is_printer();
LIB_EXPORT int osl_get_is_power2quit();
LIB_EXPORT int osl_get_is_m90_key_map();

LIB_EXPORT int osl_get_is_dual_module();
LIB_EXPORT int osl_get_is_h9();
LIB_EXPORT int osl_get_is_m66();
LIB_EXPORT int osl_get_is_m67();
LIB_EXPORT int osl_get_is_m68();
LIB_EXPORT int osl_get_is_m69();
LIB_EXPORT int osl_get_is_m66b();
LIB_EXPORT int osl_get_is_128k_ram();



enum{
	DEV_MODE_QR = 0,		// Code board
	DEV_MODE_SCAN,			// Scanning gun
};

// 
LIB_EXPORT int osl_get_dev_mode();

/**
* Setting Hardware Equipment Type
*@return Equipment type 
* 
*/
LIB_EXPORT int ols_SetDeviceType(int  nDeviceType);

//! Communication module type
enum{
	MODEL_WIRELESS = 0,		///<wireless
	MODEL_MODEM,			///<Wired
	MODEL_WIFI,				///<wifi
	MODEL_WIN32_SOCK,	///<simulator

};
enum{
	MODEL_MODE_ONLY_WIRELESS = 0,		// Wireless only
	MODEL_MODE_ONLY_WIFI,				// wifi only
	MODEL_MODE_FRIST_WIRELESS,		//Priority Wireless
	MODEL_MODE_FRIST_WIFI,				// Priority WiFi
};

/**
* @brief osl_model_type
* @return MODEL_WIRELESS 无线 MODEL_MODEM有线
*/
LIB_EXPORT int osl_model_type();
LIB_EXPORT void osl_model_set(int type);
/**
* @brief Initialization security correlation
* @return 
*/
LIB_EXPORT void osl_initTamper();
/**
* @brief Set energy saving time in seconds
* @param nTime time
* @return 
*/
LIB_EXPORT int osl_Enercy_SetTime( int nTime );

/**
* @brief Energy saving time in seconds
* @return Energy saving time
*/
LIB_EXPORT int osl_Enercy_Time();

/**
* @brief Shutdown time in seconds
* @return Shutdown time
*/
LIB_EXPORT int osl_lcd_PowerDownTime();

/**
* @brief Set shutdown time in seconds
* @param nTime time
* @return 
*/
LIB_EXPORT int osl_lcd_SetPowerDownTime( int nTime );


LIB_EXPORT int osl_get_net_mode();
LIB_EXPORT void osl_set_net_mode(int mode);
