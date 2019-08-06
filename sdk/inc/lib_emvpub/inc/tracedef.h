#pragma once

#include "pub/osl/inc/osl_log.h"

#define EMV_TRACE( ...)	osl_log( "emv", LOG_LEVEL_WARN , __VA_ARGS__ )

#define EMV_TRACE_BUFF_TIP(a,b,c) 	osl_log_buff_tip("emv",LOG_LEVEL_TRACE,a,b , c , 1);	

#ifdef WIN32
	#define EMV_TRACE_BUFF_LOG(a,b,c) 	osl_log_buff_tip("emv",LOG_LEVEL_TRACE,a,b , c ,1);	
#else
	#define EMV_TRACE_BUFF_LOG(a,b,c) 	osl_log_buff_tip("emv",LOG_LEVEL_TRACE,a,b , c ,0);	
#endif
