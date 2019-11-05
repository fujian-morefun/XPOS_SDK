/*! \file power_init.h
	\brief Power management
*	\author lx
*	\date 2014/02/08
*/
#pragma once

#include "pub\pub.h"


/**
* @brief Initialization of Power Management
* @param 
* @return 
*/
LIB_EXPORT void power_init(void);

/**
* @brief Re-timed dormancy or shutdown time after backlight extinction
* @param 
* @return 
*/
LIB_EXPORT void resetpowersuspendtimeout();


/**
* @brief Whether to turn off the backlight
* @param0 does not turn off the backlight 1 automatically turns off the backlight
* @return 
*/
LIB_EXPORT void setbacklightflag(int bpowersuspend);

/**
* @brief Whether to sleep automatically
* @param 0 turn off automatic sleep 1 automatic sleep
* @return 
*/
LIB_EXPORT void setpowersuspend(int bpowersuspend);