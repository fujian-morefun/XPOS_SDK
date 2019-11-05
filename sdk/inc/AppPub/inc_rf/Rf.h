#ifndef __RF_H__
#define __RF_H__
#include "pub/pub.h"

#define  RF_INIT_ERROR (-5)
/******************************************************************************
 *  Function name:	Rf_PowerOn
 * Function Introduction:	Power on the non-adapter card
 * Entry parameters:
 * Export parameters:
 * Return value::		
 ******************************************************************************/
LIB_EXPORT extern int Rf_PowerOn();

/******************************************************************************
* Function name: Rf_PowerDown
* Function Introduction: Call off the non-receiving card
* Entry parameters:
* Export parameters:
* Return value::		
 ******************************************************************************/
LIB_EXPORT extern int Rf_PowerDown();
/******************************************************************************
* Function name: Rf_Device_PowerOn
* Function introduction: power on non-connected equipment
* Entry parameters:
* Export parameters:
* Return value:	
 ******************************************************************************/
LIB_EXPORT extern int Rf_Device_PowerOn(int nType);

LIB_EXPORT extern int Rf_WriteCmd(const unsigned char * InData,int Insize,unsigned char *OutData,int *OutSize);
LIB_EXPORT extern int Rf_Check_CardIsExist();

LIB_EXPORT extern int Rf_Device_open();
//
//
//extern void test_rfid();
#endif



