/*! \file http_download.h
	\brief http下载
*	\author lx
*	\date 2014/02/08
*/
#pragma once

#include <pub/pub.h>
#ifdef __cplusplus
extern "C"{
#endif



/**
* @brief http 下载
* @param url 地址
* @param fullpathfilename 下载的完整文件名
* @param iscontinue 是否续传  1续传 0重新下载
* @return 0成功  <0失败
*/
LIB_EXPORT int http_download(const char *url,const char *fullpathfilename,int iscontinue);

/**
* @brief http 下载
* @param url 地址
* @param fullpathfilename 下载的完整文件名
* @param iscontinue 是否续传  1续传 0重新下载
* @param nRetry 重试次数
* @return 0成功  <0失败
*/
LIB_EXPORT int http_download_retry( const char *url,const char *fullpathfilename,int iscontinue, int nRetry );



//进度处理
typedef int (*http_download_progress)( int current, int total);
LIB_EXPORT int http_download_progress_set(http_download_progress progressfun);

#ifdef __cplusplus
}
#endif

