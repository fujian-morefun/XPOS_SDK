#ifndef __RF_H__
#define __RF_H__
#include "pub/pub.h"

#define  RF_INIT_ERROR (-5)
/******************************************************************************
 *  函数名称:	Rf_PowerOn
 *	函数介绍:	给非接卡上电
 *	入口参数:	
 *	出口参数:     
 * 	返回值  :		
 ******************************************************************************/
LIB_EXPORT extern int Rf_PowerOn();

/******************************************************************************
 *  函数名称:	Rf_PowerDown
 *	函数介绍:	给非接卡下电
 *	入口参数:	
 *	出口参数:     
 * 	返回值  :		
 ******************************************************************************/
LIB_EXPORT extern int Rf_PowerDown();
/******************************************************************************
 *  函数名称:	Rf_Device_PowerOn
 *	函数介绍:	给非接设备上电
 *	入口参数:	
 *	出口参数:     
 * 	返回值  :		
 ******************************************************************************/
LIB_EXPORT extern int Rf_Device_PowerOn(int nType);

LIB_EXPORT extern int Rf_WriteCmd(const unsigned char * InData,int Insize,unsigned char *OutData,int *OutSize);
LIB_EXPORT extern int Rf_Check_CardIsExist();

LIB_EXPORT extern int Rf_Device_open();
//
//
//extern void test_rfid();
#endif



