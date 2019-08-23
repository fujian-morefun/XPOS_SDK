#pragma once

#include <pub\osl\inc\osl_log.h>

#define TRACE(...) 	osl_log("uninpay",LOG_LEVEL_TRACE, __VA_ARGS__);

#define APP_TRACE(...) 	osl_log("uninpay",LOG_LEVEL_TRACE, __VA_ARGS__);
#define APP_TRACE_FILE(...) 	osl_log("uninpay",LOG_LEVEL_FILE, __VA_ARGS__);
#define APP_TRACE_BUFF(a,b) 	osl_log_buff("uninpay",LOG_LEVEL_TRACE,a,b);

#define APP_TRACE_BUFF_TIP(a,b,c) 	osl_log_buff_tip("uninpay",LOG_LEVEL_TRACE,a,b , c ,1 );


#ifdef WIN32
#define APP_TRACE_BUFF_LOG(a,b,c) 	osl_log_buff_tip("uninpay",LOG_LEVEL_TRACE,a,b , c ,1);	
#else
#define APP_TRACE_BUFF_LOG(a,b,c) 	osl_log_buff_tip("uninpay",LOG_LEVEL_TRACE,a,b , c ,0);	
#endif


#define TIMEBEGIN { int start = osl_GetTick();
#define TIMEEND( k )  osl_log("uninpay",LOG_LEVEL_TRACE, k##" %d\r\n" , osl_GetTick()-start ); }
