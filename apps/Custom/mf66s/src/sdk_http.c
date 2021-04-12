//#include "sdk_log.h"
#include "sdk_http.h"
#include "libapi_xpos/inc/libapi_comm.h"
#include "libapi_xpos/inc/libapi_gui.h"
#include "libapi_xpos/inc/libapi_system.h"

#define COMM_SOCK	m_comm_sock

static int m_connect_tick = 0;
static int m_connect_time = 0;
static int m_connect_exit = 0;
static int m_comm_sock = 1;

// Pack the http header, the following code is the demo code, please refer to the http specification for the specific format.
static void sdk_http_pack(char * buff, char * msg)
{
	int index = 0;
	int msgl =strlen(msg);

	index += sprintf(buff + index , "POST %s HTTP/1.1\r\n", "/mpos/handshake");
	index += sprintf(buff + index , "HOST: %s\r\n" , "test.mosambee.in" );//www.baidu.com
	//index += sprintf(buff + index , "Connection: Keep-Alive\r\n");
	index += sprintf(buff + index , "Content-Length: %d\r\n", msgl);
	//index += sprintf(buff + index , "Content-Type: text/plain;charset=UTF-8\r\n");	
	index += sprintf(buff + index , "Content-Type: application/x-www.form-urlencoded;charset=UTF-8\r\n");	
	index += sprintf(buff + index , "\r\n");

	index += sprintf(buff + index , "%s", msg);
}

// Parse the field of http
static char *sdk_http_headvalue( char *heads ,const char *head )
{
	char *pret = (char *)strstr( heads ,head );
	if ( pret != 0 )	{
		pret += strlen(head);
		pret += strlen(": ");
	}
	return pret;

}

// Parsing the status code of http
static int sdk_http_StatusCode(char *heads)
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
static int sdk_http_ContentLength(char *heads)
{
	char *pContentLength = sdk_http_headvalue( heads ,"Content-Length" );
	if ( pContentLength != 0)	{
		return atoi( pContentLength );
	}
	return -1;
}

void comm_page_set_page(char * title , char * msg ,int quit)
{
	gui_begin_batch_paint();
	
	gui_clear_dc();

	gui_text_out((gui_get_width() - gui_get_text_width(title)) / 2, GUI_LINE_TOP(0), title);
	gui_text_out(0 , GUI_LINE_TOP(1)  , msg);

	if (quit == 1){
		gui_page_op_paint("Cancel" , "");
	}

	gui_end_batch_paint();
}

int comm_page_get_exit()
{
	st_gui_message pmsg;
	int ret = 0;
	int get_ret = 0;

	while(ret == 0){
		ret = gui_get_message(&pmsg, 0);

		if ( ret == 0 ){
			if (pmsg.message_id == GUI_KEYPRESS && pmsg.wparam == GUI_KEY_QUIT){
				get_ret = 1;
			}
			gui_proc_default_msg(&pmsg);
		}
	}

	return get_ret;
}


static int _connect_server_func_proc()
{
	char msg[32] = {0};
	int ret = 0;
	int num = 0;

	if(comm_page_get_exit() == 1){
		m_connect_exit = 1;
	}

	num =  Sys_TimerCheck(m_connect_tick) / 1000;
	
	if(num <= 0){
		ret = 1;
	}
	else if(m_connect_exit == 0){
		sprintf(msg , "Connect(%d)" , num);
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
static int sdk_http_recv(int sock, char *buff, int len, int timeover)
{
	int index = 0;
	unsigned int tick1;
	char msg[32];
	char *phttpbody;
	int nHttpBodyLen;
	int nHttpHeadLen;

	tick1 = Sys_TimerOpen(timeover);

	// Receive http packets cyclically until timeout or reception is complete
	while (Sys_TimerCheck(tick1) > 0 && index < len ){	
		int ret;
		int num;

		num = Sys_TimerCheck(tick1) /1000;
		num = num < 0 ? 0 : num;
		sprintf(msg , "%s(%d)" , "Recving" , num);

		comm_page_set_page( "Http", msg , 1);
		ret = comm_page_get_exit();

		if(ret == 1){ 
			return -2;
		}
		// 
		ret = comm_sock_recv( sock, (unsigned char *)(buff + index), len - index , 700);

		if(ret >= 0){
			index += ret;

			buff[index] = '\0';
			phttpbody = (char *)strstr( buff ,"\r\n\r\n" ); // Http headend
			if(phttpbody!=0){
				//char *p;				
				int nrescode = sdk_http_StatusCode(buff);
				SYS_TRACE( "http rescode: %d",nrescode );
				if ( nrescode == 200){	

					nHttpHeadLen = phttpbody + 4 - buff;	

					nHttpBodyLen = sdk_http_ContentLength(buff);

					SYS_TRACE("HeadLen:%d  Content-Length: %d",nHttpHeadLen,nHttpBodyLen);

					//if(nHttpBodyLen<=0) return -1;

					if (index >= nHttpHeadLen+nHttpBodyLen){		
						//The receiving length is equal to the length of the head plus
						memcpy(buff , phttpbody + 4 , nHttpBodyLen);
                        SYS_TRACE( "http recv body: %s", buff );
						return nHttpBodyLen;	// Receive completed, return to receive length
					}
					return ret;
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

	SYS_TRACE( "https_recv");

	tick1 = Sys_TimerOpen(timeover);

	// Receive http packets cyclically until timeout or reception is complete
	while (Sys_TimerCheck(tick1) > 0 && index < len ){	
		int ret;
		int num;

		num = (timeover - Sys_TimerCheck(tick1)) /1000;
		num = num < 0 ? 0 : num;
		sprintf(msg , "%s(%d)" , "Recving" , num);

		comm_page_set_page( "Https", msg , 1);
		ret = comm_page_get_exit();

		if(ret == 1){ 
			return -2;
		}
		// 
		ret = comm_ssl_recv( sock, (unsigned char *)(buff + index), len - index );

		if(ret >= 0){
			index += ret;

			buff[index] = '\0';
			phttpbody = (char *)strstr( buff ,"\r\n\r\n" ); // Http headend
			if(phttpbody!=0){
				//char *p;				
				int nrescode = sdk_http_StatusCode(buff);
				SYS_TRACE( "https rescode: %d",nrescode );
				if ( nrescode == 200){	

					nHttpHeadLen = phttpbody + 4 - buff;	

					nHttpBodyLen = sdk_http_ContentLength(buff);

					SYS_TRACE("HeadLen:%d  Content-Length: %d",nHttpHeadLen,nHttpBodyLen);

					//if(nHttpBodyLen<=0) return -1;

					if (index >= nHttpHeadLen+nHttpBodyLen){		
						//The receiving length is equal to the length of the head plus
						memcpy(buff , phttpbody + 4 , nHttpBodyLen);
						SYS_TRACE( "https recv body: %s", buff );
						return nHttpBodyLen;	// Receive completed, return to receive length
					}
					return ret;
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


static void http_comm_tip()
{
	gui_begin_batch_paint();
	gui_clear_dc();
	gui_textout_line_center("communicating...", GUI_LINE_TOP(4));
	gui_end_batch_paint();
	return;
}

void sdk_http_test()
{
	char *msg = "hello world!";
	char buff[2048]={0};
	char recv[2048]={0};
	char *ip = "www.baidu.com";//119.75.217.109
	int port = 80;
	int ret = -1;
	int sock = 0;
	char apn[32]="CMNET";
    int i;
    int nret;	
	int nTime = 3;

	SYS_TRACE("sdk_http_test:---->\r\n");
	sdk_http_pack(buff, msg);		//  Package http data

	http_comm_tip();
	nret = comm_net_link("", apn ,5000);		// 30s
	SYS_TRACE("comm_net_link = %d\r\n",nret);
	if (nret != 0)
	{
		gui_messagebox_show("Http" , "Link Fail", "" , "confirm" , 0);		
		return;
	}

	COMM_SOCK = comm_sock_create(0);	//  Create sock


	for ( i = 0 ; i < nTime ; i ++)
	{		
		char tmp[32] = {0};

		m_connect_tick = Sys_TimerOpen(30000);
		m_connect_exit = 0;
		m_connect_time = i+1;

		SYS_TRACE("connect server ip=%s, port=%d\r\n", ip,  port);
		
		sprintf(tmp , "Connect server:%d" , i + 1);
		comm_page_set_page("Http", tmp , 1);

		ret = comm_sock_connect(sock, ip, port);	//  Connect to http server
		SYS_TRACE( "--------------------comm_sock_connect: %d ---------------------------\r\n", ret );
		if (ret == 0)			
			break;
		
		comm_sock_close(COMM_SOCK);
		Sys_Delay(500);
	}

	

	SYS_TRACE("connect server ret= %d,%s:%d\r\n" , ret , ip , port);

	if(ret == 0){
		comm_sock_send(sock , (unsigned char *)buff ,  strlen(buff));	// 		Send http request
		ret = sdk_http_recv(sock, recv, 1024, 30000);		// Receive http response
		if (ret > 0)
		{
			sprintf(buff, "recv buff:%s", recv);
			SYS_TRACE("recv buff:%s", recv);
			gui_messagebox_show("Http" , buff, "" , "confirm" , 0);		
		}
		else
		{
			gui_messagebox_show("Http" , "Recv Fail", "" , "confirm" , 0);
		}
	}
	else {
		gui_messagebox_show("Http" , "Connect Fail", "" , "confirm" , 0);
	}

	comm_sock_close(sock);	   

	comm_net_unlink();
}


static void https_test()
{
	char *msg = "requestMessage=imeiNumber=865789024229520|osId=80dad2df0e73f8dc|applicationId=31|imsiNumber=8991921802931780305|qposSerialNo=171257333221017301489555|make=INGENICO|model=Move2500|appVersion=1.0.0|androidVersion=11.16.05 Patch(b54)|versionCode=0|&deviceSerialNumber=0000000000";//080022380000008000009A00000530081329000001081329053020390013
	char buff[2048]={0};
	char recv[2048]={0};
	char *ip = "www.baidu.com";//104.27.134.11
	int port = 443;
	int ret = - 1;
	char apn[32]="CMNET";
	int i;
	int nret;	
	int nTime = 3;

	//mbed_ssl_set_log(10); 
	sdk_http_pack(buff, msg);		//  Package http data
	
	http_comm_tip();
	nret = comm_net_link( "" , apn,  5000);
	if (nret != 0)
	{
		gui_messagebox_show("Https" , "Link Fail", "" , "confirm" , 0);
		return;
	}

	COMM_SOCK = comm_sock_create(0);	//  Create sock
	

	for ( i = 0 ; i < nTime ; i ++)
	{
		
		char tmp[32] = {0};

		m_connect_tick = Sys_TimerOpen(30000);
		m_connect_exit = 0;
		m_connect_time = i+1;

		SYS_TRACE("connect server ip=%s, port=%d\r\n", ip,  port);
		SYS_TRACE("--------------------comm_ssl_init---------------------------\r\n" );

		comm_ssl_init(COMM_SOCK ,0,0,0,0);	
		sprintf(tmp , "Connect server%dtimes" , i + 1);
		comm_page_set_page("Https", tmp , 1);

		//c_ret = comm_ssl_connect(COMM_SOCK, ip, port);	//  Connect to http server
		ret = comm_ssl_connect2(COMM_SOCK, ip, port, (void *)_connect_server_func_proc);	//  Connect to http server
		SYS_TRACE( "--------------------comm_ssl_connect: %d ---------------------------\r\n", ret );

		if (comm_page_get_exit() || m_connect_exit == 1)	{
			SYS_TRACE("comm_func_connect_server Cancel" );
			comm_ssl_close(COMM_SOCK);
			ret = -1;
			break;
		}

		if (ret == 0){	
			break;
		}

		comm_ssl_close(COMM_SOCK);
		Sys_Delay(500);
	}	


	SYS_TRACE("connect server ret= %d,%s:%d\r\n" , ret , ip , port);

	if(ret == 0){
		comm_ssl_send(COMM_SOCK , buff ,  strlen(buff));		// 		Send http request		
		ret = https_recv(COMM_SOCK, recv, 2048, 30000);		// Receive http response
		if (ret > 0)
		{
			sprintf(buff, "recv buff:%s", recv);
			SYS_TRACE("recv buff:%s", recv);
			gui_messagebox_show("Https" , buff, "" , "confirm" , 0);
		}
		else
		{
			gui_messagebox_show("Https" , "Recv Fail", "" , "confirm" , 0);
		}
	}
	else
	{
		gui_messagebox_show("Https" , "Connect Fail", "" , "confirm" , 0);
	}		

	comm_ssl_close(COMM_SOCK);

	comm_net_unlink();
}



void sdk_https_test()
{
	https_test();
}