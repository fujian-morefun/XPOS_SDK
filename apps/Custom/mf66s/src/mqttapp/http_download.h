/*! \file app_http_download.h
	\brief http download
*	\author lx
*	\date 2014/02/08
*/
#pragma once

#ifdef __cplusplus
extern "C"{
#endif

	enum {	 	
		HTTP_ERR_SUCC		= 0,
		HTTP_ERR_CANCEL,		
		HTTP_ERR_NETLINK	,	
		HTTP_ERR_CONNECT,		
		HTTP_ERR_RECVHEAD,		
		HTTP_ERR_RECVBODY,		
		HTTP_ERR_OVERFLOW,		
		HTTP_ERR_STATUS	,		
		HTTP_ERR_URLPARSE,		
	};

/**
* @brief http download
  * @param url :        address
  * @param body:   body buff
  * @param bodysize : body  buff size
  * @param outbodylen :  output  http  body len
* @return 0 success   <0 fail
*/
int app_http_download( const char *url, char *body,int bodysize,int *outbodylen );

//Progress processing
typedef int (*app_http_download_progress)( int current, int total);
int app_http_download_progress_set(app_http_download_progress progressfun);

int app_http_download_test();

#ifdef __cplusplus
}
#endif

