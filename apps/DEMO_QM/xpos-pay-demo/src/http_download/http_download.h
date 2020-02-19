/*! \file http_download.h
	\brief http download
*	\author lx
*	\date 2014/02/08
*/
#pragma once

#include <pub/pub.h>
#ifdef __cplusplus
extern "C"{
#endif



/**
* @brief http download
  * @param url :        address
  * @param fullpathfilename:    Downloaded Full File Name
  * @param iscontinue :   Resume or not   1 Resume 0 Re-download
* @return 0 success <0 fail
*/
LIB_EXPORT int http_download(const char *url,const char *fullpathfilename,int iscontinue);

/**
* @brief http download (add retry times)
* @param url address
* @param fullpathfilename :     Downloaded Full File Name
* @param iscontinue :   Resume or not   1 Resume 0 Re-download
* @param nRetry retry times
* @return 0 success <0 fail
*/
LIB_EXPORT int http_download_retry( const char *url,const char *fullpathfilename,int iscontinue, int nRetry );



//Progress processing
typedef int (*http_download_progress)( int current, int total);
LIB_EXPORT int http_download_progress_set(http_download_progress progressfun);

#ifdef __cplusplus
}
#endif

