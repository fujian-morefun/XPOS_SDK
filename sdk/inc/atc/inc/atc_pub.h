#ifdef  _ATC_PUB_
#define _ATC_PUB_
#pragma once

#include "pub\pub.h"

#ifdef __cplusplus
extern "C"{
#endif


//#define SOCK_HEX_CODE

#define AT_ERROR    -1
#define AT_NO_ECHO  -2

/**
* @brief Setting up APN
* @param apn apn name
* @return 0 success
*/
LIB_EXPORT int ap_set_apn(char *apn);
/**
* @brief Read IMEI
* @param buff buffer
* @param len Buffer location
* @return 0 success
*/
LIB_EXPORT int ap_get_imei(char *buff , int len);
/**
* @brief Read Module Version
* @param buff Buffer
* @param len Buffer length
* @return 0 success
*/
LIB_EXPORT int ap_get_model_ver(char *buff , int len);
/**
* @brief Send at command and wait for return
* @param cmd command
* @param timeover timeout
* @param retstr Return instruction
* @param len Instruction Length
* @param count Number of retransmissions
* @return 0 success
*/
LIB_EXPORT int ag_send_wait_return(char *cmd , int timeover , char * retstr , int len , int count);

LIB_EXPORT int ap_send_tts(char *buff);

/**
* @brief Set Echo
* @param val Echo value
* @return 0 success
*/
LIB_EXPORT int ap_set_e_val(int val);
LIB_EXPORT int ap_get_echo();
/**
* @brief Read CSQ
* @param csq_val buffer
* @return 0 success
*/
LIB_EXPORT int ap_get_csq(int *csq_val);
/**
* @brief read creg
* @param creg_val buffer 
* @return 0 success
*/
LIB_EXPORT int ap_get_creg(int *creg_val);
LIB_EXPORT int ap_get_cgatt();
LIB_EXPORT int ap_set_cgatt();
int ap_set_creg(char * buff);
/**
* @brief read pin
* @return 0 success
*/
LIB_EXPORT int ap_get_cpin();
/**
* @brief read imei
* @param buff buffer
* @param len buffer length
* @return 0 success
*/
LIB_EXPORT int ap_get_imsi(char *buff , int len);


/**
* @brief ATC initialization
* @return 
*/
LIB_EXPORT int atc_init();
LIB_EXPORT void atc_win32_init();
/**
* @brief Get whether the network has been registered
* @return 0 unregistered  1 registered
*/
LIB_EXPORT int atc_isreg();
/**
* @brief Get the CSQ value
* @return  CSQ value
*/
LIB_EXPORT int atc_csq();
/**
* @brief  Get the imei
* @return imei value
*/
LIB_EXPORT const char * atc_imei();
/**
* @brief Getting IMSI
* @return imsi value
*/
LIB_EXPORT const char * atc_imsi();

/**
* @brief Get the number of signal lattices
* @return 0 Unregistered Internet  1-4 Signal Lattice Number
*/
LIB_EXPORT int atc_signal();

/**
* @brief Get CPIN status
* @return 0 Failure 1 Lock Card 2 Normal 3puk
*/
LIB_EXPORT int atc_cpin();


/**
* @brief Get the module version number
* @return Module version number
*/
LIB_EXPORT const char * atc_model_ver();

LIB_EXPORT int atc_cell();
LIB_EXPORT int atc_lac();

typedef enum
{
	MODULE_SIMCOM = 0,		//Simcom Modular
	MODULE_SPREADTRUM = 1,	//Exhibition module(AT188MA)
	MODULE_M62 = 2,			//M62 Modular  ,M35Modular
	MODULE_AT139D = 3,		//AT139D
	MODULE_MC509 = 4,		//Huawei MC509
	MODULE_A8500 = 5,		//A8500

}MODULE_TYPE_E;

LIB_EXPORT MODULE_TYPE_E atc_getModuleType();

#define MODULE_IS_M35	atc_getModuleType() == MODULE_M62
#define MODULE_IS_A8500	atc_getModuleType() == MODULE_A8500



LIB_EXPORT const char * atc_iccid();


//Set the external buffer AT+CCED=0,2 to return content
LIB_EXPORT void atc_setccedbuff(char *pbuff, int nbufflen);

typedef struct _cceditem{
	unsigned short	MCC;					//Mobile country number
	unsigned char	MNC;					//Mobile Network Number
	unsigned short	LAC;					//Location area number
	unsigned short	CELL;					//Block number
	unsigned char	BSIC;					//Base Station Indicator Code
	unsigned char	BCCH_Freq_absolute;		//BCCH Channel number
	unsigned char	RxLev;					//Received signal strength
}ccedItem;

LIB_EXPORT ccedItem * atc_getcceditems( int *outcount);

LIB_EXPORT int atc_modelreset_set();

LIB_EXPORT void atc_set_cpin_lock(int flag,char * str);
LIB_EXPORT void ap_set_cced_flag(int flag);
LIB_EXPORT int ap_get_is4g();

LIB_EXPORT void atc_tts_play(char * str , int level);
LIB_EXPORT void atc_tts_speed(int speed);

#ifdef __cplusplus
}
#endif	

#endif