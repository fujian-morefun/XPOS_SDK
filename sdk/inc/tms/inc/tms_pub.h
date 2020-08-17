#pragma once

#include <pub/pub.h>
#ifdef __cplusplus
extern "C"{
#endif

//启动后台TMS
LIB_EXPORT int tms_init();

//升级已下载好的文件
LIB_EXPORT int tms_update(const char *file);



typedef enum eTMSACTION{
	TA_DOWNLOADING,	//准备下载升级程序
	TA_UPDATEING,	//准备升级下载好的程序
}TMSACTION;


//返回  0 取消对应动作  1 允许对应动作
typedef int (*tms_action)(TMSACTION type);


//添加tms事件处理
LIB_EXPORT int tms_set_actionproc( tms_action proc);

//endtime 秒处理如果超过时间后必须退出
typedef int (*_tms_proc)(int endtime);

//设置使用tms线程后台处理函数
LIB_EXPORT void	tms_setproc(_tms_proc proc);


LIB_EXPORT int tms_init2();
LIB_EXPORT int tms_check_update( const char *file);
LIB_EXPORT int tms_heart();

//无后台启动  只有暗码响应
LIB_EXPORT int tms_init3();
#ifdef __cplusplus
}
#endif	