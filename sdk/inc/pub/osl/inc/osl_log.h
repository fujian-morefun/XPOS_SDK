/*! \file osl_log.h
	\brief Log interface
*	\author lx
*	\date 2014/02/08
*/
#ifndef _OSL_LOG_H_____
#define _OSL_LOG_H_____

#include "pub\pub.h"

#ifdef __cplusplus
extern "C"{
#endif



#define LOG_LEVEL_FILE		60	//! Record only to files
#define LOG_LEVEL_FATAL		50	//!<Deadly (Recorded in Documents)
#define LOG_LEVEL_ERROR		40	//!<Error (recorded to file)
#define LOG_LEVEL_WARN		30	//!<warning
#define LOG_LEVEL_INFO		20	//!<information
#define LOG_LEVEL_DEBUG		10	//!<debugging
#define LOG_LEVEL_TRACE		0	//!<Track


//#define SYS_ERR(format, ...) osl_err(__FILE__, __LINE__, format, __VA_ARGS__)
#define SYS_ERR(format, ...) osl_err("", 0, format, __VA_ARGS__)

/**
* @brief System Error Interface
* @param pcFileName Call file
* @param nLine Call file location
* @param fmt
* @param 
* @return 
*/
LIB_EXPORT void osl_err(char * pcFileName , int nLine ,const char *fmt,... );

/**
* @brief System Log Interface
* @param module Filter Characters
* @param level Grade
* @param fmt
* @param 
* @return 
*/
LIB_EXPORT void osl_log(const char *module,int level,const char *fmt,...);

/**
* @brief System log hexadecimal output
* @param module Filter Characters
* @param level Grade
* @param buff buffer
* @param nsize length
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