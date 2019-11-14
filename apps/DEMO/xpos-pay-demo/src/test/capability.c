#include "capability.h"
#include "xGui\inc\mainmenu.h"
#include <string.h>
#include "xGui\inc\2ddraw.h"
#include "pub\osl\inc\osl_filedef.h"
#include "pub\common\misc\inc\mfmalloc.h"
#include "driver\uart.h"
#include "pub\osl\inc\osl_log.h"
#include "pub\tracedef.h"
#include "xGui\inc\messagedatastruct.h"
#include "xGui\inc\message.h"
#include "xGui\inc\xgui_key.h"




#define CAPABILITY_ARGOT_KEY "#3334#"

#define CAPABILITY_CFG_FILE	"xxxx\\captest.ini"

#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) < (b)) ? (b) : (a))


static void _argot_proc(const char *argot)
{
	if (strcmp(argot , CAPABILITY_ARGOT_KEY) == 0){	
		xgui_main_menu_show2("性能测试","性能测试" , 0);		
	}
}

static  const st_main_menu_item_def _menu_def[] = {

	{"性能测试" , "通讯性能" , ""},
	{"性能测试" , "存储性能" , ""},
	{"性能测试" , "非接性能" , ""},
	{"性能测试" , "扫码性能" , ""},

	{"性能测试" , "参数设置" , "性能测试.参数设置"},


	{"性能测试.参数设置" , "测试次数" , "comm_count"},
	{"性能测试.参数设置" , "数据大小" , "comm_datalen"},
	{"性能测试.参数设置" , "出错停止" , "errorstop"},
	{"性能测试.参数设置" , "WIFI" ,	"WIFI主菜单"},



	{"通讯性能" , "开始测试" , "通讯性能.开始测试"},
	{"通讯性能" , "结果查看" , "通讯性能.结果查看"},

	{"通讯性能" , "通讯方式" , "comm_type"},
	{"通讯性能" , "服务器地址" , "comm_addr"},
	{"通讯性能" , "服务器端口" , "comm_port"},


	{"存储性能" , "添加记录" , ""},
	{"存储性能" , "更改记录" , ""},
	{"存储性能" , "查询记录" , ""},
	{"存储性能" , "删除记录" , ""},

};




static void showmsg(const char * msg)
{
	xgui_BeginBatchPaint();
	XGUI_SET_WIN_RC;
	xgui_ClearDC();

	xgui_TextOut(0 , XGUI_LINE_TOP_1  , msg);

	xgui_EndBatchPaint();
}


#define tickfail -99999

typedef struct _ticksinfo
{
	int row;
	int col;
	int *ticks;

}ticksinfo;

static ticksinfo * ticksinfo_create(int row,int col)
{
	ticksinfo *ret = MALLOC(sizeof(ticksinfo));

	ret->col = col;
	ret->row = row;
	ret->ticks = (int*)MALLOC(  (row * col) * sizeof( int ) );


	memset( ret->ticks, 0x00,  (row * col) * sizeof( int )   );
	return ret;
}

static void ticksinfo_destory(ticksinfo *  t)
{
	FREE(t->ticks );

	FREE(t );
}

static void ticksinfo_settick(ticksinfo *  t , int row, int col , int val)
{
	t->ticks[ row * t->col + col ] = val;
}


static void  ticksinfo_handle(ticksinfo *  t, const char *file)
{
	int i = 0;

	int *t_min = (int*)MALLOC( t->col * sizeof(int));
	int *t_max = (int*)MALLOC( t->col * sizeof(int));
	int *t_total = (int*)MALLOC( t->col * sizeof(int));
	int *succ = (int*)MALLOC( t->col * sizeof(int));

	for ( i = 0; i < t->col ; i++ )
	{
		succ[i] = 0;
		t_max[i] = 0;
		t_total[i] = 0;
		t_min[i] = 99999999;
	}

	for ( i = 0; i < t->col ; i++ )
	{
		int index;


		for ( index = 0; index < t->row; index++)
		{
			int ctick = t->ticks[index * t->col + i ];

			if ( ctick  != tickfail )
			{//有效计时
				t_max[i] = MAX( t_max[i] , ctick ); 
				t_min[i] =  MIN( t_min[i] , ctick ); 
				t_total[i] += ctick;

				if ( t_total[i] != 0 )
				{
					//成功次数
					succ[i]++;
				}
			}
			else
			{//失败 不计算

			}
		}
	}


	i = 0;
	write_profile_int("set" , "row" , t->row , file);
	write_profile_int("set" , "col" , t->col , file);

	for ( i = 0 ; i < t->col; i++)
	{
		char temp[5];
		sprintf( temp, "v%d", i);

		write_profile_int("max" , temp , t_max[i] , file);
		write_profile_int("min" , temp , t_min[i] , file);
		write_profile_int("total" , temp , t_total[i] , file);
		write_profile_int("succ" , temp , succ[i] , file);
	}


	FREE(t_min );
	FREE(t_max );
	FREE(t_total );
	FREE(succ );
}



static int ticksinfo_msg(const char *file , int i, char *title ,char *outmsg)
{
	int index = 0;
	char temp[5];
	int succ,max,min,total;

	sprintf(temp,"v%d", i);

	succ = read_profile_int("succ" ,temp  , 0, file );
	max = read_profile_int("max" ,temp  , 0, file);
	min = read_profile_int("min" ,temp  , 0, file);
	total = read_profile_int("total" ,temp  , 0, file);

	if ( succ == 0 )
	{
		index += sprintf( outmsg + index , "%s:\r\n  %d - - -\r\n" 
			,title
			, succ			
			);
	}
	else
	{
		index += sprintf( outmsg + index , "%s:\r\n  %d %d %d %d\r\n" 
			,title
			, succ
			, max
			, min
			, total / succ
			);
	}

	return index;
}


static int comm_conn( int index , const char *comm_addr, int comm_port, int  comm_type, int  comm_datalen  )
{
	int ret = -1;
			
	if ( comm_type == 1 || comm_type == 0 )
	{
#ifndef WIN32
		int sock = 1;
#else
		int sock = mf_sock_create();
#endif

#ifndef WIN32
		if ( comm_datalen > 2048 && sock != -1)
		{
			mf_sock_fifo_resize(sock,comm_datalen+256);
		}
#endif
		if ( comm_type == 0)
		{
			mf_ssl_mbedtls(1);
		}
		else{
			mf_ssl_mbedtls(0);
		}
		mf_ssl_init(sock, 0,0,0,0);

		ret = mf_ssl_connect( sock, comm_addr, comm_port ,0);

		if ( ret == 0)
		{
			return sock;
		}
		else
		{
			mf_ssl_close(sock);
			return -1;
		}
	}
	else if ( comm_type == 2)
	{
		int sock = mf_sock_create();

#ifndef WIN32
		if ( comm_datalen > 2048 && sock != -1 )
		{
			mf_sock_fifo_resize(sock,comm_datalen+256);
		}
#endif
		ret = mf_sock_connect( sock, comm_addr, comm_port ,0);

		if ( ret == 0)
		{
			return sock;
		}
		else
		{
			mf_sock_close(sock);
			return -1;
		}
	}
	return ret;
}

static int comm_send( int index , int sock,int  comm_type , int comm_datalen )
{
	char buf[128];
	int len;
	int ret = 0;

	len = sprintf(buf, "GET /?length=%d HTTP/1.0\r\n\r\n", comm_datalen );

	if ( comm_type == 1 || comm_type == 0  )
	{
		ret = mf_ssl_send2(sock , buf,len);
	}
	else if ( comm_type == 2 )
	{
		ret = mf_sock_send(sock, buf,len);
	}
	return ret;
}



static char *http_headvalue( char *heads ,const char *head )
{
	char *pret = strstr( heads ,head );
	if ( pret != 0 )	{
		pret += strlen(head);
		pret += strlen(": ");
	}
	return pret;

}
static int http_ContentLength(char *heads)
{
	char *pContentLength = http_headvalue( heads ,"Content-Length" );
	if ( pContentLength != 0)	{
		return atoi( pContentLength );
	}
	return -1;
}

static int ssl_recv( int sock,int  comm_type,char *buf , int len)
{
	int ret;
	
	if ( comm_type == 1 || comm_type == 0  )
	{
		ret = mf_ssl_recv2(sock , buf,len);
	}
	else if ( comm_type == 2 )
	{
		ret = mf_sock_recv( sock, buf, len , 10);
	}

	return ret;
}

static int ssl_recv_timeout( int sock,int  comm_type,char *buf , int size, int timeover)
{
	int ret;

	{
		int tick= osl_GetTick();
		int index = 0;
		ret = 0;

		while( index < size )
		{
			if ( osl_CheckTimeover(tick, timeover )  )
			{
				return -2;
			}

			ret = ssl_recv( sock, comm_type,buf + index, size - index );
			if ( ret > 0 )
			{
				index += ret;
			}

			if( ret < 0 )
			{
				return -1;
			}
		}

		return 1;
	}
}

static int comm_recv(int index , int sock,int  comm_type,char *recv , int *rlen)
{
	int hret = -1;

	int ContentLength = 0;
	char *bodystart = 0;
	int nrecvctime = 20000;

	unsigned int tick;
	
	int ntry = 0;
	int recvlen = 0;

	int nret;


	tick = osl_GetTick();

	while (osl_CheckTimeover(tick  ,nrecvctime) == 0 ){

		nret = ssl_recv(sock,comm_type,(unsigned char *)recv + recvlen ,*rlen - recvlen );

		if (nret >0){

			ntry = 0;
			recvlen += nret;

			ContentLength = http_ContentLength(recv);
			if ( ContentLength != -1  )
			{
				bodystart = strstr( recv, "\r\n\r\n");
				if ( bodystart != 0 )
				{
					int headlen = 0;
					int bodylen = 0;
					int endlen = 0;
					bodystart+=4;
					headlen = bodystart - recv;
					bodylen =  recvlen - headlen;

					endlen = ContentLength - bodylen;

					if ( endlen > 0 )
					{
						if( ssl_recv_timeout( sock,comm_type, recv + recvlen , endlen ,nrecvctime ) == 1  )
						{
							*rlen = recvlen + endlen;
							hret= 0;
						}
						else
						{
							hret=-3;
						}
					}
					else
					{
						*rlen = recvlen;
						hret= 0;
					}

					break;
				}
			}

		}
		else{
			osl_Sleep(10);
		}
	}

	return  hret;
}

static int comm_close( int index , int sock,int  comm_type,int comm_datalen )
{
	if ( comm_type == 1 || comm_type == 0  )
	{
		mf_ssl_close(sock);
	}
	else if ( comm_type == 2 )
	{
		mf_sock_close(sock);
	}

#ifndef WIN32
	if ( comm_datalen > 2048 && sock != -1)
	{
		mf_sock_fifo_resize(sock,2048);
	}
#endif
	return 0;
}


#define CAPABILITY_RESULT_FILE	"xxxx\\capcomm.ini"
static int comm_result()
{
	char msg[256];
	int index = 0;
	int total = 0;
	int count = read_profile_int("set" , "row" , 0, CAPABILITY_RESULT_FILE) ;

	index += sprintf( msg+index, "次数:%d 大小:%d 模式:%d\r\n" 
		, count
		, read_profile_int("set" , "comm_datalen" , 0, CAPABILITY_RESULT_FILE) 
		, read_profile_int("set" , "comm_type" , 0, CAPABILITY_RESULT_FILE) 
		);

	index += ticksinfo_msg(CAPABILITY_RESULT_FILE , 0 ,"连接", msg+index);
	index += ticksinfo_msg(CAPABILITY_RESULT_FILE , 1 ,"发送", msg+index);
	index += ticksinfo_msg(CAPABILITY_RESULT_FILE , 2 ,"接收", msg+index);


	xgui_messagebox_show("",msg,"","确认", 0);

	return 0;
}



static int comm_test()
{
	int ret;
	int len;
	int sock = 0;

	int comm_type = read_profile_int("set" , "comm_type" , 0, CAPABILITY_CFG_FILE);
	int comm_port = read_profile_int("set" , "comm_port" , 8011, CAPABILITY_CFG_FILE);
	int comm_datalen = read_profile_int("set" , "comm_datalen" , 32, CAPABILITY_CFG_FILE);
	int comm_count = read_profile_int("set" , "comm_count" , 10, CAPABILITY_CFG_FILE);
	int errorstop = read_profile_int("set" , "errorstop" , 0, CAPABILITY_CFG_FILE);

	char comm_addr[50];
	char *recvbuf;
	int rlen;

	int tickstart;


	ticksinfo *tinfo = ticksinfo_create(comm_count,3);
	
	int index = 0;

	//ws_sock_set_send_mode(1);
	//mbed_ssl_set_log(10);

	read_profile_string("set" , "comm_addr" , comm_addr , sizeof(comm_addr) ,"mf.ghttps.com", CAPABILITY_CFG_FILE);

	if ( comm_type == 0 )
	{
		mf_ssl_mbedtls(1);
	}
	for ( index = 0; index < comm_count; index++)
	{
		int succ = 0;
		char msg[32];

		sprintf(msg,"测试:%d/%d", index, comm_count);

		showmsg(msg);

		tickstart = osl_GetTick();
		sock = comm_conn( index , comm_addr, comm_port, comm_type,comm_datalen);

		if( sock >= 0 )
		{
			ticksinfo_settick( tinfo, index, 0 ,osl_GetTickDiff(tickstart) );

			tickstart = osl_GetTick();

			comm_send(index ,sock, comm_type , comm_datalen);

			ticksinfo_settick( tinfo, index, 1 ,osl_GetTickDiff(tickstart) );

			rlen = (comm_datalen + 256 + 1024) ;
			recvbuf = MALLOC( rlen * sizeof(char) );
			

			tickstart = osl_GetTick();
			if ( comm_recv(index ,sock, comm_type , recvbuf, &rlen) == 0)
			{
				int tickdiff = osl_GetTickDiff(tickstart);

				ticksinfo_settick( tinfo, index, 2 ,tickdiff);
				succ = 1;
			}
			else
			{
				ticksinfo_settick( tinfo, index, 2 ,tickfail);	
			}			
			//recvbuf[rlen] = 0;

			FREE(recvbuf);
		}
		else
		{
			ticksinfo_settick( tinfo, index, 0 ,tickfail);
			ticksinfo_settick( tinfo, index, 1 ,tickfail);
			ticksinfo_settick( tinfo, index, 2 ,tickfail);
		}

		comm_close(  index ,  sock,  comm_type , comm_datalen); 


		if (succ != 1 && errorstop == 1 )
		{
			break;
		}
	}


	ticksinfo_handle(tinfo , CAPABILITY_RESULT_FILE );

	write_profile_int("set" , "comm_type" , comm_type  , CAPABILITY_RESULT_FILE);
	write_profile_int("set" , "comm_datalen" ,comm_datalen , CAPABILITY_RESULT_FILE);

	//xgui_messagebox_show("提示","测试完成","","确认", 0);

	ticksinfo_destory(tinfo);

	comm_result();

	return 0;
}


static int config_page(const char *pid , const char *defaultstr)
{
// 	int ret;
// 	char val[64];
// 	int len = 0;
// 	len = sizeof(val)-1;
// 
// 	memset(val,0x00, sizeof(val));
// 	read_profile_string("set" , pid , val , len ,defaultstr, CAPABILITY_CFG_FILE);
// 	xgui_ImeSetMode(IME_MODE_NUMBER, IME_MODE_ALPHABET_UP | IME_MODE_ALPHABET_LOW | IME_MODE_NUMBER, 0,0 );
// 	xgui_ImeSetOpInfo(0, IME_OPMODE_ALWAYS);
// 	ret = xgui_ImeStartInput(val , len, 0, (char*)pid );
// 	if ( ret > 0 )
// 	{
// 		write_profile_string("set" , pid , val , CAPABILITY_CFG_FILE);
// 	}
// 	return ret;
}

#define RESULT_FILE "xxxx\\capfile.ini"

#define TEST_FILE "xxxx\\ftest.dat"
static int file_add_test()
{
	int ret;
	int len;

	char data[32];
	int comm_datalen = read_profile_int("set" , "comm_datalen" , 32, CAPABILITY_CFG_FILE);
	int comm_count = read_profile_int("set" , "comm_count" , 10, CAPABILITY_CFG_FILE);

	int tickstart;

	ticksinfo *tinfo = ticksinfo_create(comm_count,1);

	int index = 0;

	char *buff = (char*)MALLOC(comm_datalen+1);
	
	File_Delete( TEST_FILE );

	for ( index = 0; index < comm_count; index++)
	{
		sprintf(data,"添加:%d/%d", index, comm_count);
		showmsg(data);
		
		sprintf( buff, "%0*d", comm_datalen, index);
		tickstart = osl_GetTick();
		ret = File_Append(  TEST_FILE,buff,comm_datalen  );
		if ( ret == 1)
		{
			ticksinfo_settick( tinfo, index,0 ,osl_GetTickDiff(tickstart) );
		}
		else
		{
			ticksinfo_settick( tinfo, index,0 , tickfail );
		}
	}

	FREE(buff);

	ticksinfo_handle(tinfo , RESULT_FILE );
	write_profile_int("set" , "comm_datalen" ,comm_datalen , RESULT_FILE);

	ticksinfo_destory(tinfo);

	
	{
		char msg[256];
		int index = 0;
		int total = 0;
		int count = read_profile_int("set" , "row" , 0, RESULT_FILE) ;
		int comm_datalen = read_profile_int("set" , "comm_datalen" , 0, RESULT_FILE) ;

		index += sprintf( msg+index, "次数:%d 大小:%d\r\n" 	, count	, comm_datalen);

		index += ticksinfo_msg(RESULT_FILE , 0 ,"添加", msg+index);

		xgui_messagebox_show("",msg,"","确认", 0);
	}
	return 0;


}


static int file_update_test()
{
	int ret;
	int len;

	char data[32];
	int comm_datalen = read_profile_int("set" , "comm_datalen" , 32, CAPABILITY_CFG_FILE);
	int comm_count = read_profile_int("set" , "comm_count" , 10, CAPABILITY_CFG_FILE);

	int tickstart;

	ticksinfo *tinfo = ticksinfo_create(comm_count,1);

	int index = 0;

	char *buff = (char*)MALLOC(comm_datalen+1);

	for ( index = 0; index < comm_count; index++)
	{
		sprintf(data,"更新:%d/%d", index, comm_count);
		showmsg(data);

		sprintf( buff, "% *d", comm_datalen, index);
		tickstart = osl_GetTick();
		ret = File_WriteBlockByName(  TEST_FILE, index*comm_datalen,buff,comm_datalen  );
		if ( ret == comm_datalen)
		{
			ticksinfo_settick( tinfo, index,0 ,osl_GetTickDiff(tickstart) );
		}
		else
		{
			ticksinfo_settick( tinfo, index,0 , tickfail );
		}
	}
	FREE(buff);

	ticksinfo_handle(tinfo , RESULT_FILE );
	write_profile_int("set" , "comm_datalen" ,comm_datalen , RESULT_FILE);

	ticksinfo_destory(tinfo);

	{
		char msg[256];
		int index = 0;
		int total = 0;
		int count = read_profile_int("set" , "row" , 0, RESULT_FILE) ;
		int comm_datalen = read_profile_int("set" , "comm_datalen" , 0, RESULT_FILE) ;

		index += sprintf( msg+index, "次数:%d 大小:%d\r\n" 	, count	, comm_datalen);
		index += ticksinfo_msg(RESULT_FILE , 0 ,"更新", msg+index);
		xgui_messagebox_show("",msg,"","确认", 0);
	}
	return 0;
}
static int file_query_test()
{
	int ret;
	int len;

	char data[32];
	int comm_datalen = read_profile_int("set" , "comm_datalen" , 32, CAPABILITY_CFG_FILE);
	int comm_count = read_profile_int("set" , "comm_count" , 10, CAPABILITY_CFG_FILE);

	int tickstart;

	ticksinfo *tinfo = ticksinfo_create(comm_count,1);

	int index = 0;

	char *buff = (char*)MALLOC(comm_datalen+1);

	for ( index = 0; index < comm_count; index++)
	{
		sprintf(data,"查询:%d/%d", index, comm_count);
		showmsg(data);

		tickstart = osl_GetTick();
		ret = File_ReadBlockByName( TEST_FILE, index*comm_datalen,buff,comm_datalen );
		buff[comm_datalen] = 0;

		if ( ret == comm_datalen)
		{
			ticksinfo_settick( tinfo, index,0 ,osl_GetTickDiff(tickstart) );
		}
		else
		{
			ticksinfo_settick( tinfo, index,0 , tickfail );
		}
	}
	FREE(buff);

	ticksinfo_handle(tinfo , RESULT_FILE );
	write_profile_int("set" , "comm_datalen" ,comm_datalen , RESULT_FILE);

	ticksinfo_destory(tinfo);

	{
		char msg[256];
		int index = 0;
		int total = 0;
		int count = read_profile_int("set" , "row" , 0, RESULT_FILE) ;
		int comm_datalen = read_profile_int("set" , "comm_datalen" , 0, RESULT_FILE) ;

		index += sprintf( msg+index, "次数:%d 大小:%d\r\n" 	, count	, comm_datalen);
		index += ticksinfo_msg(RESULT_FILE , 0 ,"查询", msg+index);
		xgui_messagebox_show("",msg,"","确认", 0);
	}
	return 0;
}


static int file_delete_test()
{

	int ret;
	char data[32];
	int handle;
	int comm_datalen = read_profile_int("set" , "comm_datalen" , 32, CAPABILITY_CFG_FILE);
	int comm_count = read_profile_int("set" , "comm_count" , 10, CAPABILITY_CFG_FILE);
	int tickstart;

	ticksinfo *tinfo = ticksinfo_create(comm_count,1);
	int index = 0;
	int filesize;

	for ( index = 0; index < comm_count; index++)
	{
		sprintf(data,"删除:%d/%d", index, comm_count);
		showmsg(data);


		tickstart = osl_GetTick();


		ret = -1;
		handle = FILE_OPEN( TEST_FILE  , FILE_WRITE_FLAG, FILE_WRITE_MODE);
	
		if ( handle != FILE_OPEN_FAIL )
		{
			filesize = 	File_GetLength( handle );
			if ( filesize >= comm_datalen)
			{
				ret = mf_file_truncate(handle ,  filesize-comm_datalen);
			}
			FILE_CLOSE(handle);
		}

		if (  ret != -1)
		{
			ticksinfo_settick( tinfo, index,0 ,osl_GetTickDiff(tickstart) );
		}
		else
		{
			ticksinfo_settick( tinfo, index,0 ,tickfail );
		}
	}
	ticksinfo_handle(tinfo , RESULT_FILE );
	write_profile_int("set" , "comm_datalen" ,comm_datalen , RESULT_FILE);

	ticksinfo_destory(tinfo);


	{
		char msg[256];
		int index = 0;
		int total = 0;
		int count = read_profile_int("set" , "row" , 0, RESULT_FILE) ;
		int comm_datalen = read_profile_int("set" , "comm_datalen" , 0, RESULT_FILE) ;

		index += sprintf( msg+index, "次数:%d 大小:%d\r\n" 	, count	, comm_datalen);

		index += ticksinfo_msg(RESULT_FILE , 0 ,"删除", msg+index);

		xgui_messagebox_show("",msg,"","确认", 0);
	}
	return 0;
}
#define RESULT_RF "xxxx\\caprf.ini"


static int Icc_CTLSPowerUpAndSeek(int iCardType, char *psUID)
{
	if ( Rf_Check_CardIsExist() == 0)
	{
		//int tick = osl_GetTick();
		mf_rfid_getuid( psUID);
		//APP_TRACE("mf_rfid_getuid  %d", osl_GetTickDiff(tick) );
		return 0;
	}
	//APP_TRACE("Rf_Check_CardIsExist() == 0 ");
	osl_Sleep(10);
	return -1;
}

static int rf_test()
{
	int ret;
	char data[32];
	int handle;
	int comm_count = read_profile_int("set" , "comm_count" , 10, CAPABILITY_CFG_FILE);
	int tickstart;

	ticksinfo *tinfo = ticksinfo_create(comm_count,1);
	int index = 0;
	int filesize;
	char szUID[23];

	for ( index = 0; index < comm_count; index++)
	{
		sprintf(data,"读卡:%d/%d", index, comm_count);
		showmsg(data);

		tickstart = osl_GetTick();

		ret = Icc_CTLSPowerUpAndSeek(0, szUID);
		while ( ret != 0) 
		{
			if ( osl_CheckTimeover(tickstart,3000)  )
			{
				break;
			}
			ret = Icc_CTLSPowerUpAndSeek(0, szUID);
		}

		if (  ret == 0 )
		{
			ticksinfo_settick( tinfo, index,0 ,osl_GetTickDiff(tickstart) );
		}
		else
		{
			ticksinfo_settick( tinfo, index,0 ,tickfail );
		}
	}
	ticksinfo_handle(tinfo , RESULT_RF );	
	ticksinfo_destory(tinfo);
	osl_BuzzerSound(500);

	{
		char msg[256];
		int index = 0;
		int total = 0;
		int count = read_profile_int("set" , "row" , 0, RESULT_RF) ;

		index += sprintf( msg+index, "次数:%d \r\n" 	, count	);

		index += ticksinfo_msg(RESULT_RF , 0 ,"读卡", msg+index);

		xgui_messagebox_show("",msg,"","确认", 0);
	}
	return 0;
}




//#define SCANSOFT  


static int _menu_proc(char *pid)
{
	if (strcmp(pid , "通讯性能.开始测试") == 0){
		comm_test();
	}
	else if (strcmp(pid , "通讯性能.结果查看") == 0){
		comm_result();
	}
	else if (strcmp(pid , "添加记录") == 0){
		file_add_test();
	}
	else if (strcmp(pid , "更改记录") == 0){
		file_update_test();
	}
	else if (strcmp(pid , "查询记录") == 0){
		file_query_test();
	}
	else if (strcmp(pid , "删除记录") == 0){
		file_delete_test();
	}
	else if (strcmp(pid , "非接性能") == 0){
		rf_test();
	}
	else if (strcmp(pid , "扫码性能") == 0){
		//scan_test();
	}
	else if (strcmp(pid , "comm_type") == 0){
		config_page(pid,"0");
	}
	else if (strcmp(pid , "comm_addr") == 0){
		config_page(pid,"mf.ghttps.com");
	}
	else if (strcmp(pid , "comm_port") == 0){
		config_page(pid,"8011");
	}
	else if (strcmp(pid , "comm_datalen") == 0){
		config_page(pid,"32");
	}
	else if (strcmp(pid , "comm_count") == 0){
		config_page(pid,"100");
	}
	else if (strcmp(pid , "errorstop") == 0){
		config_page(pid,"0");
	}
	return 0;
}
int capability_init()
{
	int i = 0;

	mbedtls_init();

	xgui_main_menu_func_add((void *)_menu_proc);

	//file_delete_test();
	//comm_test();
	//comm_result();

	for (i = 0; i < sizeof(_menu_def) / sizeof(st_main_menu_item_def) ; i ++)	{		
		xgui_main_menu_item_add(&_menu_def[i]);		
	}

	argot_regisert(CAPABILITY_ARGOT_KEY , _argot_proc);

	return 0;
}

int capability_page()
{
	MESSAGE pMsg;
	int len = 0;

	xgui_PostMessage(XM_GUIPAINT, 0 , 0);
	while(1){


		if (xgui_GetMessageWithTime(&pMsg, 300) == MESSAGE_ERR_NO_ERR) {

			if (pMsg.MessageId == XM_GUIPAINT) {

				xgui_BeginBatchPaint();
				XGUI_SET_WIN_RC;
				xgui_ClearDC();

				xgui_TextOut_Win_Center("性能测试" );


				xgui_EndBatchPaint();
			}
			else if (pMsg.MessageId == XM_KEYPRESS) {
				argot_keyinput(pMsg.WParam);

				if (pMsg.WParam == KEY_OK || pMsg.WParam == KEY_QUIT)	
				{
					osl_set_app_busy(1);
					xgui_main_menu_show2("性能测试","性能测试" , 0);	
				}

				xgui_PostMessage(XM_GUIPAINT, 0 , 0);
			}
		}
	}


}