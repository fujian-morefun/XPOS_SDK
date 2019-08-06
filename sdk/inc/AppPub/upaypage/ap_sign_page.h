#pragma once
#include "pub/pub.h"

#define RET_SIGN_OK  1
#define RET_SIGN_CANCEL  0
#define RET_SIGN_EXIST  2
#define RET_SIGN_TIMEOUT  3


 typedef struct _procs{
	 //界面绘制 水印
	 int (*page_paint)(const char *m_watermark);  
	 int (*page_getbackcount)();  
	 //是否允许取消
	 int (*page_usecancel)(); 

	 //取消是否提示
	 int (*page_usecancelask)();  
	 
	 //取消获取水印
	 int (*page_getwatermark)( char *outwatermark);


	 //轨迹最少点数
	 int (*page_getwritepointcount)();  

	 //是否使用收银员确认页面
	 int (*page_usesigntype)(); 

	 //图片是否使用320*130分辨率
	 int (*page_use320_130)(); 

	 //轨迹最少笔画数
	 int (*page_getpointupcount)();  

	 int (*page_buffwidth)();
	 int (*page_buffheight)();
	 
 }ap_sign_procs;

 //设定处理函数
LIB_EXPORT void ap_setprocs( ap_sign_procs *procs );

//是否已签名
LIB_EXPORT int ap_sign_exist( const char *xlh );

//签名处理
LIB_EXPORT int ap_sign_proc( const char *xlh,const char * date,const char * ckh );

//签名处理
LIB_EXPORT int ap_sign_proc2( const char *xlh,const char * date,const char * ckh , int timeout );


//获取打印字符串
LIB_EXPORT extern const char * ap_sign_print(const char *xlh );

//JBIG编码接口
LIB_EXPORT int ap_sign_encode( const char *xlh,char **jbigencode );

//JBIG结果释放
LIB_EXPORT int ap_sign_encode_free( char *jbigencode );


//清理签名数据
LIB_EXPORT extern int ap_sign_clean();

LIB_EXPORT extern void ap_sign_test();

LIB_EXPORT int ap_sign_savetofile(char * data, const char *xlh);
