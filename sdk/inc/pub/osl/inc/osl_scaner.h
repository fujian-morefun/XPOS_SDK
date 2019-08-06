#include "pub\pub.h"
/*! \file osl_uart.h
	\brief 串口数据发送
*	\author lx
*	\date 2014/02/08
*/
#pragma once


LIB_EXPORT int osl_scaner_open();
LIB_EXPORT int osl_scaner_close();

LIB_EXPORT int osl_scaner_get( char *outbuff,int maxlen ,int timeout);

LIB_EXPORT void osl_scan_set_proc(void * func);