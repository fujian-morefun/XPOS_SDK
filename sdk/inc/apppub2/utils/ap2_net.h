#pragma once

#include "pub/pub.h"



/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:create SSL socket 
Input : index(0/1)
Output : Nothing
return: >=0 index created
		<0, failure	
*************************************************************************************/
LIB_EXPORT int ap2_sock_create(int index);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:set SSL model type
Input : sock(0/1)
		modeltype -1:auto 0:gprs 2:wifi
Output : Nothing
return: 0 success
		<0, failure	
*************************************************************************************/
LIB_EXPORT int ap2_sock_modeltype( int sock,int modeltype );

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:get SSL model type
Input : sock(0/1)
Output : Nothing
return: modeltype -1:auto 0:gprs 2:wifi
*************************************************************************************/
LIB_EXPORT int ap2_sock_modeltype_get( int sock );

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:SSL set APN
Input :	sock£º socket index(0/1)
		apnname£ºgprs apn
		user:gprs apn user id
		pwd: gprs apn user password
Output : Nothing
return: 0,     success
		Other, failure	
*************************************************************************************/
LIB_EXPORT int ap2_sock_apn(int sock, char * apnname, char * user, char * pwd);

#define AP2_NET_CONNECT_SUCC  0
#define AP2_NET_CONNECT_CANCEL  -1
#define AP2_NET_CONNECT_TIMEOUT -2
typedef int (* connect_server_func)();
/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:SSL connect to the server
Input : sock		sock index
		  ip		server ip
		  port		server port
		  cancelfunc	function pointer of cacel processing
Output : Nothing			
return: refer to AP2_NET_CONNECT_XX
		0,     success
		Other, failure		
*************************************************************************************/
LIB_EXPORT int ap2_sock_connect(int sock,const char *ip,int port,connect_server_func cancelfunc);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:SSL connect to the server with timeout
Input : sock		sock index
		  ip		server ip
		  port		server port
		  timeout	time
		  cancelfunc	function pointer of cacel processing
Output : Nothing			
return: refer to AP2_NET_CONNECT_XX
		0,     success
		Other, failure		
*************************************************************************************/
LIB_EXPORT int ap2_sock_connect_timeout( int sock,const char *ip,int port, int timeout,connect_server_func cancelfunc );
/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:SSL send data
Input : sock		sock index
		  buff		Send buffer
		  datalen		Send length
Output : Nothing			
return: >=0,     the length sent
		<0, failure		
*************************************************************************************/
LIB_EXPORT int ap2_sock_send(int sock,const char *buff,int datalen);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:SSL Receive data
Input : sock		sock index
		  buff		Receive buffer
		  len		Receiving length
		  timeover	overtime time
Output : Nothing			
return: 0,     success
		Other, failure		
*************************************************************************************/
LIB_EXPORT int ap2_sock_recv(int sock, unsigned char * buff, int len, unsigned int timeover);
LIB_EXPORT int ap2_sock_recv2( int sock, unsigned char * buff, int needlen, unsigned int timeover );
/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:SSL disconnect the server
Input : sock		sock index
Output : Nothing			
return: 0,     success
		Other, failure		
*************************************************************************************/
LIB_EXPORT int ap2_sock_close(int sock);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:init mbedtls SSL;init once application run;
Input : use_session		1 use mbedtls session; others will not use
		loglevel		set log level
Output : Nothing			
return:log level set	
*************************************************************************************/
LIB_EXPORT int ap2_mbedtls_init( int use_session,int loglevel );

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:SSL initialization
Input : sock		sock index
	      cacert	Server certificate
		  clientcert Client certificate
		  clientkey	Client key
		  level		Verification level 0=Not verified 1=Verify server certificate
Output : Nothing			
return: 0,     success
		Other, failure		
*************************************************************************************/
LIB_EXPORT int ap2_ssl_init(int sock, char * cacert, char * clientcert, char * clientkey,int level);
/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:SSL initialization
Input : index		sock index
	      ciphersuites	cipher suites for SSL
Output : Nothing			
return: 0,     success
		Other, failure		
*************************************************************************************/
LIB_EXPORT int ap2_ssl_ciphersuites( int index , const int *ciphersuites );

//major  MBEDTLS_SSL_MAJOR_VERSION_3  3
//minor  #define MBEDTLS_SSL_MINOR_VERSION_0             0   /*!< SSL v3.0 */
//       #define MBEDTLS_SSL_MINOR_VERSION_1             1   /*!< TLS v1.0 */
//       #define MBEDTLS_SSL_MINOR_VERSION_2             2   /*!< TLS v1.1 */
//       #define MBEDTLS_SSL_MINOR_VERSION_3             3   /*!< TLS v1.2 */

LIB_EXPORT int ap2_ssl_max_version( int index, int major, int minor );
LIB_EXPORT int ap2_ssl_min_version( int index, int major, int minor );

/*
#define MBEDTLS_SSL_VERIFY_NONE                 0
#define MBEDTLS_SSL_VERIFY_OPTIONAL             1
#define MBEDTLS_SSL_VERIFY_REQUIRED             2
#define MBEDTLS_SSL_VERIFY_UNSET                3 /* Used only for sni_authmode */

LIB_EXPORT int ap2_ssl_authmode(int index , int authmode);

LIB_EXPORT int ap2_ssl_psk(int index , const unsigned char *psk, unsigned int psk_len, const unsigned char *psk_identity,  unsigned int psk_identity_len );
LIB_EXPORT int ap2_ssl_hostname(int index , const char * cn);



LIB_EXPORT int ap2_sock_setproxy(int sock,const char *serveraddr,int serverport);
LIB_EXPORT int ap2_play_net_err();

LIB_EXPORT int ap2_play_net_mode();


LIB_EXPORT int ap2_sock_set_waitactive( int sock,int waitactive );



LIB_EXPORT int ap2_ssl_ca_chain(int index ,const unsigned char *ca,int len);

LIB_EXPORT int ap2_ssl_own_cert(int index 
								,const unsigned char *cert,int certlen
								,const unsigned char *key,int keylen
								);
