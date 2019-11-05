/*! \file pageproc.h
	\brief Global message proc
*	\author lx
*	\date 2014/02/08
*/
#pragma once

#include "xgui_pub.h"
#include "messagedatastruct.h"

/**
* @brief Global message proc
* @param pMsg Message structure
* @return  Processing results, 0 
*/
LIB_EXPORT int xgui_proc_default_msg(PMESSAGE pMsg);


LIB_EXPORT void xgui_set_return_desktop(unsigned char flag);
LIB_EXPORT unsigned char xgui_get_return_desktop(void);

/**
* @brief Global Processing Fu 
* @param pfunc Global Processing Fu
* @return  0 success
*/
LIB_EXPORT int xgui_default_msg_func_add(void * pfunc);