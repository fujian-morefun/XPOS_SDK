#include "xGui/inc/messagebox.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/message.h"
#include "xGui/inc/xgui_key.h"

#include "net/inc/mf_net.h"
#include "net/inc/mf_sock.h"
#include "json/inc/json_tokener.h"
#include "pub\osl\inc\osl_BaseParam.h"
#include "pub\tracedef.h"
#include "net/inc/mf_ssl.h"

#define COMM_SOCK	m_comm_sock

static int m_connect_tick = 0;
static int m_connect_time = 0;
static int m_connect_exit = 0;
static int m_comm_sock = 1;

// Pack the http header, the following code is the demo code, please refer to the http specification for the specific format.
static void http_pack(char * buff, char * msg)
{
	int index = 0;
	int msgl =strlen(msg);
	index += sprintf(buff + index , "POST %s HTTP/1.1\r\n", "/test");
	index += sprintf(buff + index , "HOST: %s\r\n" , "www.baidu.com" );//www.baidu.com
	index += sprintf(buff + index , "Connection: Keep-Alive\r\n");
	index += sprintf(buff + index , "Content-Length: %d\r\n", msgl);
	index += sprintf(buff + index , "\r\n");

	index += sprintf(buff + index , "%s", msg);
}

// Parse the field of http
static char *http_headvalue( char *heads ,const char *head )
{
	char *pret = (char *)strstr( heads ,head );
	if ( pret != 0 )	{
		pret += strlen(head);
		pret += strlen(": ");
	}
	return pret;

}

// Parsing the status code of http
static int http_StatusCode(char *heads)
{	
	char *rescode = (char *)strstr( heads ," " );
	if ( rescode != 0 )	{
		rescode+=1;
		return atoi( rescode);
	}
	else{
		
	}

	return -1;
}

// Parse the length of http
static int http_ContentLength(char *heads)
{
	char *pContentLength = http_headvalue( heads ,"Content-Length" );
	if ( pContentLength != 0)	{
		return atoi( pContentLength );
	}
	return -1;
}

void comm_page_set_page(char * title , char * msg ,int quit)
{
	xgui_BeginBatchPaint();
	XGUI_SET_WIN_RC;
	xgui_ClearDC();
	xgui_SetTitle(title);

	xgui_TextOut(0 , XGUI_LINE_TOP_1  , msg);
	if (quit == 1){
		xgui_Page_OP_Paint("Cancel" , "");
	}

	xgui_EndBatchPaint();
}

int comm_page_get_exit()
{
	MESSAGE pMsg;
	int ret = MESSAGE_ERR_NO_ERR;
	int get_ret = 0;

	while(ret == MESSAGE_ERR_NO_ERR){
		ret = xgui_GetMessageWithTime(&pMsg, 0);

		if ( ret == MESSAGE_ERR_NO_ERR ){
			if (pMsg.MessageId == XM_KEYPRESS && pMsg.WParam == KEY_QUIT){
				get_ret = 1;
			}
			xgui_proc_default_msg(&pMsg);
		}
	}

	return get_ret;
}

static int _connect_server_func_proc()
{
	char msg[32] = {0};
	int ret = 0;
	int num = 0;
	int time = 30;

	if(comm_page_get_exit() == 1){
		m_connect_exit = 1;
	}

	num = time - osl_GetTickDiff(m_connect_tick) / 1000;
	
	if(num <= 0){
		ret = 1;
	}
	else if(m_connect_exit == 0){
		sprintf(msg , "Link(%d)" , num);
		comm_page_set_page("Http", msg , 1);
	}
	else{
		sprintf(msg , "Canceling...");
		comm_page_set_page("Http", msg , 0);
		ret = 2;
	}
	

	return ret ;
}

// Http receiving processing, the step is to receive the byte stream from the sock to parse out the header status code and length and other fields, and then receive the http body according to the length
static int http_recv(int sock, char *buff, int len, int timeover)
{
	int index = 0;
	unsigned int tick1;
	char msg[32];
	char *phttpbody;
	int nHttpBodyLen;
	int nHttpHeadLen;

	APP_TRACE( "http_recv");

	tick1 = osl_GetTick();

	// Receive http packets cyclically until timeout or reception is complete
	while (osl_CheckTimeover(tick1 , timeover) == 0 && index < len ){	
		int ret;
		int num;

		num = (timeover - osl_GetTickDiff(tick1)) /1000;
		num = num < 0 ? 0 : num;
		sprintf(msg , "%s(%d)" , "Recving" , num);

		comm_page_set_page( "Http", msg , 1);
		ret = comm_page_get_exit();

		if(ret == 1){ 
			return -2;
		}
		// 
		ret = mf_sock_recv( sock, (unsigned char *)(buff + index), len - index , 700);

		if(ret >= 0){
			index += ret;

			buff[index] = '\0';
			phttpbody = (char *)strstr( buff ,"\r\n\r\n" ); // Http headend
			if(phttpbody!=0){
				char *p;				
				int nrescode = http_StatusCode(buff);
				APP_TRACE( "http rescode: %d",nrescode );
				if ( nrescode == 200){	

					nHttpHeadLen = phttpbody + 4 - buff;	

					nHttpBodyLen = http_ContentLength(buff);

					APP_TRACE("HeadLen:%d  Content-Length: %d",nHttpHeadLen,nHttpBodyLen);

					if(nHttpBodyLen<=0) return -1;

					if (index >= nHttpHeadLen+nHttpBodyLen){		
						//The receiving length is equal to the length of the head plus
						memcpy(buff , phttpbody + 4 , nHttpBodyLen);
                        APP_TRACE( "http recv body: %s", buff );
						return nHttpBodyLen;	// Receive completed, return to receive length
					}
				}
				else{  //not 200

					return -1;
				}
			}
                        

		}
		else {
			return -1;
		}	
	}

	return -1;
}

static int https_recv(int sock, char *buff, int len, int timeover)
{
	int index = 0;
	unsigned int tick1;
	char msg[32];
	char *phttpbody;
	int nHttpBodyLen;
	int nHttpHeadLen;

	APP_TRACE( "https_recv");

	tick1 = osl_GetTick();

	// Receive http packets cyclically until timeout or reception is complete
	while (osl_CheckTimeover(tick1 , timeover) == 0 && index < len ){	
		int ret;
		int num;

		num = (timeover - osl_GetTickDiff(tick1)) /1000;
		num = num < 0 ? 0 : num;
		sprintf(msg , "%s(%d)" , "Recving" , num);

		comm_page_set_page( "Https", msg , 1);
		ret = comm_page_get_exit();

		if(ret == 1){ 
			return -2;
		}
		// 
		ret = mf_ssl_recv2( sock, (unsigned char *)(buff + index), len - index );

		if(ret >= 0){
			index += ret;

			buff[index] = '\0';
			phttpbody = (char *)strstr( buff ,"\r\n\r\n" ); // Http headend
			if(phttpbody!=0){
				char *p;				
				int nrescode = http_StatusCode(buff);
				APP_TRACE( "https rescode: %d",nrescode );
				if ( nrescode == 200){	

					nHttpHeadLen = phttpbody + 4 - buff;	

					nHttpBodyLen = http_ContentLength(buff);

					APP_TRACE("HeadLen:%d  Content-Length: %d",nHttpHeadLen,nHttpBodyLen);

					if(nHttpBodyLen<=0) return -1;

					if (index >= nHttpHeadLen+nHttpBodyLen){		
						//The receiving length is equal to the length of the head plus
						memcpy(buff , phttpbody + 4 , nHttpBodyLen);
						APP_TRACE( "https recv body: %s", buff );
						return nHttpBodyLen;	// Receive completed, return to receive length
					}
				}
				else{  //not 200

					return -1;
				}
			}


		}
		else {
			return -1;
		}	
	}

	return -1;
}



static void http_test()
{
	char *msg = "hello world!";
	char buff[1024]={0};
	char recv[1024]={0};
	char *ip = "www.baidu.com";//119.75.217.109
	int port = 80;
	int ret=0;
    int i;
	int nTime;
	char tmp[32] = {0};

	http_pack(buff, msg);		//  Package http data

	ret = net_func_link("Dial","CMNET",1,30*1000);

	if (ret != 0){

		xgui_messagebox_show("Http" , "Dial Fail", "" , "confirm" , 0);
		return;
	}

	mf_set_connnect_server_func(COMM_SOCK , (void*) _connect_server_func_proc);

	for ( i = 0 ; i < nTime ; i ++){
		

		m_connect_tick = osl_GetTick();
		m_connect_exit = 0;

		m_comm_sock = mf_sock_create();
		m_connect_time = i+1;

		APP_TRACE("connect server ip=%s, port=%d\r\n", ip,  port);

		sprintf(tmp , "Connect server%dtimes" , i + 1);
		comm_page_set_page("Http", tmp , 1);

		ret = mf_sock_connect(COMM_SOCK , ip , port);

		if (comm_page_get_exit() || m_connect_exit == 1)	{
			APP_TRACE("comm_func_connect_server Cancel" );
			mf_sock_close(COMM_SOCK);
			ret = -1;
			break;
		}

		if (ret == 0){
		
			break;
		}

		mf_sock_close(COMM_SOCK);
		osl_Sleep(500);
	}

	mf_set_connnect_server_func(COMM_SOCK , (void*) 0);

	APP_TRACE("connect server ret= %d,%s:%d\r\n" , ret , ip , port);
        
	if(ret == 0){
		mf_sock_send(COMM_SOCK , (unsigned char *)buff ,  strlen(buff));	// 		Send http request
		ret = http_recv(COMM_SOCK, recv, sizeof(recv), 30000);		// Receive http response
		sprintf(buff, "recv buff:%s", recv);
		APP_TRACE(buff);
		xgui_messagebox_show("Http" , "recv ok", "" , "confirm" , 0);
	}
    else
    {
        xgui_messagebox_show("Http" , "Connect Fail", "" , "confirm" , 0);
    }
	mf_sock_close(COMM_SOCK);
}


static void https_test()
{
	char *msg = "hello world!";
	char buff[1024]={0};
	char recv[1024]={0};
	char *ip = "www.baidu.com";//14.215.177.38
	int port = 443;
	int ret;
	int nTime;
	char tmp[32] = {0};
	int i;

	http_pack(buff, msg);		//  Package https data

	ret = net_func_link("Dial","CMNET",1,30*1000);

	if (ret != 0){

		xgui_messagebox_show("Https" , "Dial Fail", "" , "confirm" , 0);
		return;
	}

	mf_set_connnect_server_func(COMM_SOCK , (void*) _connect_server_func_proc);

	for ( i = 0 ; i < nTime ; i ++){


		m_connect_tick = osl_GetTick();
		m_connect_exit = 0;

		m_comm_sock = mf_sock_create();
		m_connect_time = i+1;

		APP_TRACE("connect server ip=%s, port=%d\r\n", ip,  port);

		//mf_ssl_mbedtls(1);//Use TLS 1.2
		APP_TRACE("--------------------mf_ssl_init---------------------------" );
		mf_ssl_init(COMM_SOCK ,0,0,0,0);
// #ifndef WIN32
// 		if(aq_set_cfg("sslversion",m_comm_sock,"1") != 0) return;
// #endif
		sprintf(tmp , "Connect server%dtimes" , i + 1);
		comm_page_set_page("Https", tmp , 1);

		mf_sock_fifo_resize(COMM_SOCK, 5*1024);
		ret = mf_ssl_connect(COMM_SOCK, ip, port, (void*) _connect_server_func_proc);	//  Connect to https server
		APP_TRACE( "--------------------mf_ssl_connect: %d ---------------------------", ret );

		if (comm_page_get_exit() || m_connect_exit == 1)	{
			APP_TRACE("comm_func_connect_server Cancel" );
			mf_ssl_close(COMM_SOCK);
			ret = -1;
			break;
		}

		if (ret == 0){
			ret = 0;
			break;
		}

		mf_ssl_close(COMM_SOCK);
		osl_Sleep(500);
	}

	mf_set_connnect_server_func(COMM_SOCK , (void*) 0);

	APP_TRACE("connect server ret= %d,%s:%d\r\n" , ret , ip , port);
	
	if(ret == 0){
		mf_ssl_send(COMM_SOCK , buff ,  strlen(buff));		// 		Send http request
		ret = https_recv(COMM_SOCK, recv, sizeof(recv), 30000);		// Receive http response
		sprintf(buff, "recv buff:%s", recv);
		APP_TRACE(buff);
		xgui_messagebox_show("Https" , "Recv OK", "" , "confirm" , 0);
	}
	else
	{
		xgui_messagebox_show("Https" , "Connect Fail", "" , "confirm" , 0);
	}

	mf_ssl_close(COMM_SOCK);
}

static void json_test()
{
	struct json_object *rootobj = 0;
	struct json_object *itemobj = 0;
	char str[128] = {0};
	char * key = "code";
	char *pdata = 0;

	strcpy(str, "{\"success\":\"false\",\"code\":\"1001\"}");
	rootobj = json_tokener_parse(str);

	if(((int)rootobj) >= 0){
		itemobj = (struct json_object *) json_object_object_get(rootobj, key);	

		if (((int)itemobj)> 0){
			pdata = json_object_to_json_string(itemobj);
		}

		json_object_put(rootobj);
	}
	
}


void sdk_http_test()
{
	http_test();	
	//json_test();

}

void sdk_https_test()
{
	https_test();
	//json_test();

}