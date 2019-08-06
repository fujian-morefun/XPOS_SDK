/*! \file osl_task_stk_chk.h
	\brief 任务栈检测
*	\author lx
*	\date 2014/02/08
*/
#pragma once

#include "pub\pub.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief 任务栈检测初始化
* @return 
*/
LIB_EXPORT void osl_task_stk_chk_init();
LIB_EXPORT void osl_task_trace_info();

#ifdef __cplusplus
}
#endif