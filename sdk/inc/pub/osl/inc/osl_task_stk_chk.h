/*! \file osl_task_stk_chk.h
	\brief Task Stack Detection
*	\author lx
*	\date 2014/02/08
*/
#pragma once

#include "pub\pub.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief Initialization of task stack detection
* @return 
*/
LIB_EXPORT void osl_task_stk_chk_init();
LIB_EXPORT void osl_task_trace_info();

#ifdef __cplusplus
}
#endif