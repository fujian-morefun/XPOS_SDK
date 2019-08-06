#ifndef __PRINTF_DEBUG__
#define __PRINTF_DEBUG__
#include "pub/osl/inc/osl_log.h"
#include "pub/pub.h"
#include "struct_tlv.h"
#include "struct_hashtable.h"


#define APPPUB_TRACE(...) 	osl_log("app_pub",LOG_LEVEL_TRACE, __VA_ARGS__);
#define APPPUB_TRACE_FILE(...) 	osl_log("app_pub",LOG_LEVEL_FILE, __VA_ARGS__);
#define APPPUB_TRACE_BUFF(a,b) 	osl_log_buff("app_pub",LOG_LEVEL_TRACE,a,b);
#define APPPUB_TRACE_BUFF_TIP(a,b,c) 	osl_log("app_pub",LOG_LEVEL_TRACE, c);	osl_log_buff("app_pub",LOG_LEVEL_TRACE,a,b);	

#ifdef WIN32
#define APPPUB_TRACE_BUFF_LOG(a,b,c) 	osl_log_buff_tip("app_pub",LOG_LEVEL_TRACE,a,b , c , 1);	
#else
#define APPPUB_TRACE_BUFF_LOG(a,b,c) 	osl_log_buff_tip("app_pub",LOG_LEVEL_TRACE,a,b , c , 0);	
#endif


#define  Debug_fprintf(...) 	osl_log("app_pub",LOG_LEVEL_TRACE, __VA_ARGS__)

#define  DebugPrint Debug_fprintf

LIB_EXPORT extern void DebugPrintHash(int nAddress,HashData elem);
LIB_EXPORT extern void DebugPrintBuf(char *pszTitle,char *pszBuf,int nLen);
LIB_EXPORT void DebugPrintTlv(char *pszTitle,pTlvData tlv,int count);


LIB_EXPORT void start_icc_log();
LIB_EXPORT void save_icc_log(unsigned char * send , int slen , unsigned char * recv , int rlen);
LIB_EXPORT void save_tag_log(unsigned char * buff , int len , char * tip);
LIB_EXPORT void save_tag_log_ex(unsigned char * buff , int len , int tag);
#endif