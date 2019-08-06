/*! \file osl_uart.h
	\brief 串口数据发送
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
* @brief 串口数据发送
* @param nCom 串口号
* @param pBuffer 缓冲区
* @param nLength 长度
* @return 已发送的长度
*/
LIB_EXPORT int osl_uart_send(unsigned int nCom, unsigned char *pBuffer, unsigned int nLength);


#ifdef __cplusplus
}
#endif	