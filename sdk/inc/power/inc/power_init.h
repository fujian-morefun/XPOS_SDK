/*! \file power_init.h
	\brief 电源管理
*	\author lx
*	\date 2014/02/08
*/
#pragma once

#include "pub\pub.h"


/**
* @brief 电源管理初始化
* @param 
* @return 
*/
LIB_EXPORT void power_init(void);

/**
* @brief 重新计时背光灭后休眠或关机时间
* @param 
* @return 
*/
LIB_EXPORT void resetpowersuspendtimeout();


/**
* @brief 是否关闭背光
* @param 0不关闭背光  1自动关闭背光
* @return 
*/
LIB_EXPORT void setbacklightflag(int bpowersuspend);

/**
* @brief 是否自动休眠
* @param 0关闭自动休眠  1自动休眠
* @return 
*/
LIB_EXPORT void setpowersuspend(int bpowersuspend);