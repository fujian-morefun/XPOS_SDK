/*! \file osl_uart.h
	\brief Serial port data transmission
*	\author lx
*	\date 2014/02/08
*/
#pragma once
#include "pub/pub.h"
#include "pub\pub.h"

#include "driver\uart.h"
#include "pub/pub.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
* @brief Serial port data transmission
* @param nCom Serial slogans
* @param pBuffer buffer
* @param nLength lengtth
* @return Sended length
*/
LIB_EXPORT int osl_uart_send(unsigned int nCom, unsigned char *pBuffer, unsigned int nLength);


#ifdef __cplusplus
}
#endif	