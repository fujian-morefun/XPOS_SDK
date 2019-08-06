/*! \file osl_rfid.h
	\brief RFID功能
*	\author lx
*	\date 2014/02/08
*/
#ifndef _DEV_RFID_H_
#define _DEV_RFID_H_

#include "pub/pub.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
* @brief 获取卡id
* @param outUID
* @return 
*/
LIB_EXPORT int  osl_Rfid_GetUID(unsigned long *outUID);

#ifdef __cplusplus
}
#endif

#endif	//_DEV_RFID_H_

