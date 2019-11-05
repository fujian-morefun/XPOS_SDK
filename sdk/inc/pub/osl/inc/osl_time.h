/*! \file osl_time.h
	\brief System Time Function
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
* @brief Calculating time difference
* @param tick1 Starting time
* @return time difference
*/
LIB_EXPORT int osl_GetTickDiff(unsigned int tick1);

/**
* @brief Detection of timeout
* @param tick1 Starting time
* @param timeover 
* @return 1 timeover
*/
LIB_EXPORT int osl_CheckTimeover(unsigned int tick1 , unsigned int timeover);
/**
* @brief Get the current time
* @param 
* @return 
*/
LIB_EXPORT unsigned int osl_GetTick(void);
/**
* @brief Sleep for a period of time
* @param ms time
* @return 
*/
LIB_EXPORT void osl_Sleep(int ms);
/**
* @brief Get the system date and time
* @param pstDateTime Date-time pointer
* @return 
*/
LIB_EXPORT int osl_GetDateTime(DATE_TIME_T * pstDateTime);
/**
* @brief Setting System Date and Time
* @param pstDateTime Date-time pointer
* @return 
*/
LIB_EXPORT int osl_SetDateTime(const DATE_TIME_T * pstDateTime);

// ¡ä¨®1970.1.1Seconds
LIB_EXPORT unsigned int osl_GetLongDate();
#ifdef __cplusplus
}
#endif