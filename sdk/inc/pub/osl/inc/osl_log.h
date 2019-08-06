/*! \file osl_log.h
	\brief 日志接口
*	\author lx
*	\date 2014/02/08
*/
#ifndef _OSL_LOG_H_____
#define _OSL_LOG_H_____

#include "pub\pub.h"

#ifdef __cplusplus
extern "C"{
#endif



#define LOG_LEVEL_FILE		60	//! 只记录到文件
#define LOG_LEVEL_FATAL		50	//!<致命  (记录到文件)
#define LOG_LEVEL_ERROR		40	//!<错误  (记录到文件)
#define LOG_LEVEL_WARN		30	//!<警告
#define LOG_LEVEL_INFO		20	//!<信息
#define LOG_LEVEL_DEBUG		10	//!<调试
#define LOG_LEVEL_TRACE		0	//!<跟踪


//#define SYS_ERR(format, ...) osl_err(__FILE__, __LINE__, format, __VA_ARGS__)
#define SYS_ERR(format, ...) osl_err("", 0, format, __VA_ARGS__)

/**
* @brief 系统错误接口
* @param pcFileName 调用文件
* @param nLine 调用文件位置
* @param fmt
* @param 
* @return 
*/
LIB_EXPORT void osl_err(char * pcFileName , int nLine ,const char *fmt,... );

/**
* @brief 系统日志接口
* @param module 过滤字符
* @param level 等级
* @param fmt
* @param 
* @return 
*/
LIB_EXPORT void osl_log(const char *module,int level,const char *fmt,...);

/**
* @brief 系统日志16进制输出
* @param module 过滤字符
* @param level 等级
* @param buff 缓冲区
* @param nsize 大小
* @return 
*/
LIB_EXPORT void osl_log_buff(const char *module,int level,const void *buff,int nsize);
LIB_EXPORT void osl_log_buff_tip( const char *module,int level,const void *Buffer,int nSize  , char *  tip , int breakline);

LIB_EXPORT void osl_log_pause();
LIB_EXPORT void osl_log_resume();
LIB_EXPORT void osl_log_init();

LIB_EXPORT int osl_log_set_auto_break_line(unsigned char auto_break_line);
LIB_EXPORT void osl_log_set_bluetooth_init(int flag);

LIB_EXPORT int osl_log_sound_set(int val);
LIB_EXPORT void osl_log_set_func(void * func);
LIB_EXPORT void osl_log_set_val(int val);

#ifdef __cplusplus
}
#endif

#endif