/*! \file osl_time.h
	\brief 系统时间函数
*	\author lx
*	\date 2014/02/08
*/

#pragma once

#include "pub\pub.h"
#ifdef __cplusplus
extern "C"{
#endif
typedef struct tagDATE_TIME_T
{
	int nYear;
	int nMonth;
	int nDay;
	int nHour;
	int nMinute;
	int nSecond;
}DATE_TIME_T;

//#define _TRACE_TICK_BEGIN	unsigned int tick1= osl_GetTick();
//#define _TRACE_TICK_END(a)	printf( #a ":%d\r\n" , osl_GetTick() - tick1);

LIB_EXPORT int osl_GetLevelSec(int timeover ,unsigned int tick1);

/**
* @brief 计算时间差
* @param tick1 起始时间
* @return 时间差
*/
LIB_EXPORT int osl_GetTickDiff(unsigned int tick1);

/**
* @brief 检测是否超时
* @param tick1 起始时间
* @param timeover 超时时间
* @return 1超时
*/
LIB_EXPORT int osl_CheckTimeover(unsigned int tick1 , unsigned int timeover);
/**
* @brief 获取当前时间
* @param 
* @return 
*/
LIB_EXPORT unsigned int osl_GetTick(void);
/**
* @brief 休眠一段时间
* @param ms 时间
* @return 
*/
LIB_EXPORT void osl_Sleep(int ms);
/**
* @brief 获取系统日期时间
* @param pstDateTime 日期时间指针
* @return 
*/
LIB_EXPORT int osl_GetDateTime(DATE_TIME_T * pstDateTime);
/**
* @brief 设置系统日期时间
* @param pstDateTime 日期时间指针
* @return 
*/
LIB_EXPORT int osl_SetDateTime(const DATE_TIME_T * pstDateTime);

// 从1970.1.1秒数
LIB_EXPORT unsigned int osl_GetLongDate();
#ifdef __cplusplus
}
#endif