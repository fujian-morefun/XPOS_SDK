/*! \file pageproc.h
	\brief 全局消息处理
*	\author lx
*	\date 2014/02/08
*/
#pragma once

#include "xgui_pub.h"
#include "messagedatastruct.h"

/**
* @brief 全局消息处理
* @param pMsg 消息结构
* @return  处理结果，0未处理
*/
LIB_EXPORT int xgui_proc_default_msg(PMESSAGE pMsg);


LIB_EXPORT void xgui_set_return_desktop(unsigned char flag);
LIB_EXPORT unsigned char xgui_get_return_desktop(void);

/**
* @brief 全局处理函数添加 
* @param pfunc 全局处理函数
* @return  0成功
*/
LIB_EXPORT int xgui_default_msg_func_add(void * pfunc);