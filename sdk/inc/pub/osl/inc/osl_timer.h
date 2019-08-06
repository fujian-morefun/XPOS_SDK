/*! \file osl_timer.h
	\brief 定时器
*	\author lx
*	\date 2014/02/08
*/
#pragma once

#include "pub\pub.h"

#include "osl_timerdatastruct.h"




/**
* @brief 初始化定时器管理
* @param 
* @return 
*/
LIB_EXPORT unsigned int osl_TimerInit(void);


/**
* @brief 创建一个定时器
* @param 处理函数
* @param pParam 参数
* @param nPeriod 定时周期
* @param nMode 模式
* @param pnErrorCode 错误码
* @return 0失败 大于0定时器句柄
*/
LIB_EXPORT unsigned int osl_TimerCreate(TIMERFUNCTION pWorkFunction, void* pParam, unsigned int nPeriod, unsigned int nMode, unsigned int *pnErrorCode);


/**
* @brief 删除指定的定时器
* @param nTimerNo 定时器句柄
* @return 0成功
*/
LIB_EXPORT unsigned int osl_TimerDelete (unsigned int nTimerNo);		


/**
* @brief 使能指定的定时器
* @param nTimerNo 定时器句柄
* @return 0成功
*/
LIB_EXPORT unsigned int osl_TimerEnable (unsigned int nTimerNo);


/**
* @brief 复位指定的定时器
* @param nTimerNo 定时器句柄
* @return 0成功
*/
LIB_EXPORT unsigned int osl_TimerReset (unsigned int nTimerNo);

//
/**
* @brief 设置指定的定时器的定时周期
* @param nTimerNo 定时器句柄
* @param nPeriod 定时周期
* @return 0成功
*/
LIB_EXPORT unsigned int osl_TimerSetPeriod(unsigned int nTimerNo, unsigned int nPeriod);
/**
* @brief 设置定时器当前时间
* @param nTimerNo 定时器句柄
* @param nCurTime 当前时间
* @return 0成功
*/
LIB_EXPORT unsigned int osl_TimerSetCurTime(unsigned int nTimerNo, unsigned int nCurTime);

/**
* @brief 读取定时器当前时间
* @param nTimerNo 定时器句柄
* @return 当前时间
*/
LIB_EXPORT unsigned int osl_TimerGetCurTime(unsigned int nTimerNo);


/**
* @brief 禁止指定的定时器
* @param nTimerNo 定时器句柄
* @return 0成功
*/
LIB_EXPORT unsigned int osl_TimerDisable (unsigned int nTimerNo);
/**
* @brief 获取定时器状态
* @param nTimerNo 定时器句柄
* @return 0停止
*/
LIB_EXPORT unsigned int osl_TimerGetStatus (unsigned int nTimerNo);










