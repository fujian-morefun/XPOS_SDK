#ifdef WIN32
//#include <windows.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define	USE_TLS_SOCK	1

#include "driver/mf_spi_flash.h"

#include "pub/osl/inc/osl_filedef.h"
#include "pub/osl/inc/osl_log.h"
#include "pub/osl/inc/osl_file_comm.h"
#include "pub/osl/inc/osl_time.h"
#include "pub/osl/inc/osl_BaseParam.h"
#include "pub/osl/inc/osl_system.h"

#include "net/inc/mf_sock.h"
#include "net/wifi/wf_sock.h"
#include "net/inc/http_download.h"

#include "xGui/inc/2ddraw.h"
#include "pub/common/misc/inc/mfmalloc.h"

#define HTTP_TRACE      sdk_log_out

static http_download_progress s_progress = 0;

#ifdef WIN32
#define DEV_90M	1
#define DEV_90H	1
#endif

#define HTTPSOCK 0
#ifndef NULL
#define NULL ((void *)0)
#endif
typedef struct http_uri_tag
{
	char             *full;                          /* full URL */
	char             *proto;                         /* protocol */
	char             *host;                          /* copy semantics */
	unsigned short    port;
	char             *resource;                      /* copy semantics */
} http_uri;


typedef enum uri_parse_state_tag
{
	parse_state_read_host = 0,
	parse_state_read_port,
	parse_state_read_resource
} uri_parse_state;


static int http_uri_parse(const char *a_string, http_uri *a_uri)
{
	/* Everyone chant... "we love state machines..." */
	uri_parse_state l_state = parse_state_read_host;
	char *l_start_string = NULL;
	char *l_end_string = NULL;
	char  l_temp_port[6];

	/* init the array */
	memset(l_temp_port, 0, 6);
	/* check the parameters */
	if (a_string == NULL)
		goto ec;
	if (a_uri) {
		a_uri->full = (char *)strdup(a_string);
	}
	l_start_string = (char *)strchr(a_string, ':');
	/* check to make sure that there was a : in the string */
	if (!l_start_string)
		goto ec;
	if (a_uri) {
		a_uri->proto = (char *)malloc(l_start_string - a_string + 1);
		memcpy(a_uri->proto, a_string, (l_start_string - a_string));
		a_uri->proto[l_start_string - a_string] = '\0';
	}
	/* check to make sure it starts with "http://" */
	if (strncmp(l_start_string, "://", 3) != 0)
		goto ec;
	/* start at the beginning of the string */
	l_start_string = l_end_string = &l_start_string[3];
	while(*l_end_string)
	{
		if (l_state == parse_state_read_host)
		{
			if (*l_end_string == ':')
			{
				l_state = parse_state_read_port;
				if ((l_end_string - l_start_string) == 0)
					goto ec;
				/* allocate space */
				if ((l_end_string - l_start_string) == 0)
					goto ec;
				/* only do this if a uri was passed in */
				if (a_uri)
				{
					a_uri->host = (char *)malloc(l_end_string - l_start_string + 1);
					/* copy the data */
					memcpy(a_uri->host, l_start_string, (l_end_string - l_start_string));
					/* terminate */
					a_uri->host[l_end_string - l_start_string] = '\0';
				}
				/* reset the counters */
				l_end_string++;
				l_start_string = l_end_string;
				continue;
			}
			else if (*l_end_string == '/')
			{
				l_state = parse_state_read_resource;
				if ((l_end_string - l_start_string) == 0)
					goto ec;
				if (a_uri)
				{
					a_uri->host = (char *)malloc(l_end_string - l_start_string + 1);
					memcpy(a_uri->host, l_start_string, (l_end_string - l_start_string));
					a_uri->host[l_end_string - l_start_string] = '\0';
				}
				l_start_string = l_end_string;
				continue;
			}
		}
		else if (l_state == parse_state_read_port)
		{
			if (*l_end_string == '/')
			{
				l_state = parse_state_read_resource;
				/* check to make sure we're not going to overflow */
				if (l_end_string - l_start_string > 5)
					goto ec;
				/* check to make sure there was a port */
				if ((l_end_string - l_start_string) == 0)
					goto ec;
				/* copy the port into a temp buffer */
				memcpy(l_temp_port, l_start_string, l_end_string - l_start_string);
				/* convert it. */
				if (a_uri)
					a_uri->port = atoi(l_temp_port);
				l_start_string = l_end_string;
				continue;
			}
			else if (isdigit(*l_end_string) == 0)
			{
				/* check to make sure they are just digits */
				goto ec;
			}
		}
		/* next.. */
		l_end_string++;
		continue;
	}

	if (l_state == parse_state_read_host)
	{
		if ((l_end_string - l_start_string) == 0)
			goto ec;
		if (a_uri)
		{
			a_uri->host = (char *)malloc(l_end_string - l_start_string + 1);
			memcpy(a_uri->host, l_start_string, (l_end_string - l_start_string));
			a_uri->host[l_end_string - l_start_string] = '\0';
			/* for a "/" */
			a_uri->resource = (char *)strdup("/");
		}
	}
	else if (l_state == parse_state_read_port)
	{
		if (strlen(l_start_string) == 0)
			/* oops.  that's not a valid number */
			goto ec;
		if (a_uri)
		{
			a_uri->port = atoi(l_start_string);
			a_uri->resource = strdup("/");
		}
	}
	else if (l_state == parse_state_read_resource)
	{
		if (strlen(l_start_string) == 0)
		{
			if (a_uri)
				a_uri->resource = strdup("/");
		}
		else
		{
			if (a_uri)
				a_uri->resource = strdup(l_start_string);
		}
	}
	else
	{
		/* uhh...how did we get here? */
		goto ec;
	}
	return 0;

ec:
	return -1;
}

static http_uri * http_uri_new(void)
{
	http_uri *l_return = NULL;

	l_return = (http_uri *)malloc(sizeof(http_uri));
	l_return->full = NULL;
	l_return->proto = NULL;
	l_return->host = NULL;
#ifdef	USE_TLS_SOCK
	l_return->port = 443;
#else
	l_return->port = 80;
#endif
	l_return->resource = NULL;
	return l_return;
}

static void http_uri_destroy(http_uri *a_uri)
{
	if (a_uri->full) {
		free(a_uri->full);
		a_uri->full = NULL;
	}
	if (a_uri->proto) {
		free(a_uri->proto);
		a_uri->proto = NULL;
	}
	if (a_uri->host) {
		free(a_uri->host);
		a_uri->host = NULL;
	}
	if (a_uri->resource) {
		free(a_uri->resource);
		a_uri->resource = NULL;
	}
	free(a_uri);
}





static char *http_headvalue( char *heads ,const char *head )
{
	char *pret = strstr( heads ,head );
	if ( pret != 0 )
	{
		pret += strlen(head);
		pret += strlen(": ");
	}
	return pret;

}
static int http_ContentLength(char *heads)
{
	char *pContentLength = http_headvalue( heads ,"Content-Length" );
	if ( pContentLength != 0)
	{
		return atoi( pContentLength );
	}
	return -1;
}

static int http_ContentRange(char *heads)
{	
	char *val = http_headvalue(heads, "Content-Range" );
	if ( val != 0 )
	{
		val = strchr(val,'/');
		if ( val != 0 )
		{
			val++;
			return atoi(val);
		}
	}
	return -1;
}

static int http_StatusCode(char *heads)
{	
	char *rescode = strstr( heads ," " );
	if ( rescode != 0 )
	{
		rescode+=1;
		return atoi( rescode);
	}
	else
	{
		HTTP_TRACE( "http_StatusCode error %s", heads );
	}

	return -1;
}


typedef struct _tag_httpdownload 
{
	http_uri *urlbase;  //请求链接
	http_uri *urllocation; //重定向地址
	const char *fullpathfilename;  //下载地址
	int iscontinue;
	int fdsize;//文件已下载长度	
	int ContentRange; //请求文件长度
	int downloadsize;//本次已下载大小
}httpdownload;

#define RECVTIMEOUT 30000
#define RECVBUFFSIZE 2048

#ifndef OS_LINUX
#define USTEMP			//linux不使用FALSH缓存
#endif

//////////////////////////////////////////////////////////////////////////
//下载临时flash区
#ifdef WIN32
#define EXT_FLASH_TMS_AREA_ADDR			(0x0)
#endif

static void inittotemp( )
{
#ifdef USTEMP
	mf_flash_erase(EXT_FLASH_TMS_AREA_ADDR , 512 * 1024);
#endif
}

static int writetotemp( int index,unsigned char * buff,int datasize)
{
#ifdef USTEMP
	unsigned int write_addr =  EXT_FLASH_TMS_AREA_ADDR + index;
	mf_flash_write((unsigned char *)buff ,write_addr , datasize);
	return datasize;
#endif
}
static int readtemp( int index,void * buff,int datasize)
{
#ifdef USTEMP
	unsigned int read_addr =  EXT_FLASH_TMS_AREA_ADDR + index;
	mf_flash_read((unsigned char *)buff ,read_addr , datasize);
	return datasize;
#endif
}

static int flushtofile( httpdownload *ret  )
{
#ifdef USTEMP

	if ( ret->downloadsize > 0 )
	{//已下载大小
		int downloadfd = FILE_OPEN( ret->fullpathfilename, FILE_WRITE_FLAG,FILE_WRITE_MODE);
		if (  downloadfd == FILE_OPEN_FAIL  )
		{
			downloadfd = FILE_OPEN( ret->fullpathfilename, FILE_CREAT_FLAG,FILE_WRITE_MODE);
		}

		if ( downloadfd != FILE_OPEN_FAIL )
		{
			void *buff = malloc(4096);
			int readindex =  0;

			FILE_LSEEK(downloadfd , 0, SEEK_END);

			while ( readindex < ret->downloadsize )
			{
				int readlen = (ret->downloadsize - readindex) > 4096 ? 4096 : ret->downloadsize - readindex;
				readtemp(readindex,buff , readlen );
				FILE_WRITE( downloadfd, buff ,readlen);

				readindex += readlen;
			}

			free(buff);

			FILE_CLOSE( downloadfd);
		}

		ret->fdsize +=ret->downloadsize;
		ret->downloadsize = 0;
	}
#endif
	return 0;
}


static int closedownfile(httpdownload *ret)
{	
	flushtofile(ret);
	return 0;
}

static int craetenewdownfile(httpdownload *ret)
{
	closedownfile(ret);
	FILE_DELETE(ret->fullpathfilename);
	ret->fdsize = 0;
	return 0;
}

static httpdownload * http_download_create(const char *url,const char *filename,int iscontinue)
{
	httpdownload *ret = (httpdownload *)malloc( sizeof(httpdownload) );
	ret->urlbase =  http_uri_new();
	http_uri_parse( url,ret->urlbase );
	ret->urllocation = NULL;
	ret->fullpathfilename= strdup(filename);
	ret->iscontinue = iscontinue;
	ret->downloadsize = 0;

	inittotemp();

	if ( iscontinue )
	{
		ret->fdsize = File_GetFileLength( filename );
		if ( ret->fdsize < 0)
		{
			craetenewdownfile(ret);
		}		
	}
	else
	{
		craetenewdownfile(ret);
	}

	return ret;
}

static httpdownload * http_download_destroy(httpdownload *d)
{
	closedownfile(d);

	if ( d->urlbase != NULL )
	{
		http_uri_destroy(d->urlbase);
		d->urlbase = NULL;
	}
	if ( d->urllocation != NULL )
	{
		http_uri_destroy(d->urllocation);
		d->urllocation = NULL;
	}
	if ( d->fullpathfilename != NULL )
	{
		free((void *)d->fullpathfilename);
		d->fullpathfilename = NULL;
	}

	free( d );
	return 0;
}

static http_uri *http_download_getconnecturi(httpdownload *d)
{  
	if ( d->urllocation != NULL )
	{
		return d->urllocation;
	}
	else
	{
		return d->urlbase;
	}
}

static int http_download_getreqbuff(httpdownload *d,char *reqbuff)
{
	return sprintf(reqbuff,"GET %s HTTP/1.1\r\nHost: %s:%d\r\nRange: bytes=%d- \r\nConnection: keep-alive\r\n\r\n" , http_download_getconnecturi(d)->resource,d->urlbase->host,d->urlbase->port,d->fdsize);
}


static int writetofile( httpdownload *d ,const char *data,int datasize)
{
	int progressret = 0;
	int ret = -1;
	if ( s_progress != 0)
	{		
		progressret = s_progress( d->fdsize + d->downloadsize, d->ContentRange );
	}

#ifdef USTEMP
	d->downloadsize += writetotemp( d->downloadsize, (unsigned char * )data,datasize );		
#ifdef WIN32
	if ( d->downloadsize > 10240 )
	{
		flushtofile(d);
	}
#endif

#else
	if ( datasize > 0 )
	{//已下载大小
		int write_bytes = 0;
		int downloadfd = FILE_OPEN( d->fullpathfilename, FILE_WRITE_FLAG,FILE_WRITE_MODE);
		if ( downloadfd == FILE_OPEN_FAIL )
		{
			downloadfd = FILE_OPEN( d->fullpathfilename, FILE_CREAT_FLAG,FILE_WRITE_MODE);
		}

		if (FILE_OPEN_FAIL != downloadfd){
			FILE_LSEEK(downloadfd, 0, SEEK_END);
			write_bytes = FILE_WRITE(downloadfd, data, datasize);
			FILE_CLOSE(downloadfd);
			if(write_bytes != datasize){
				HTTP_TRACE("writetofile error %s", d->fullpathfilename);
			}
		}
		d->fdsize += datasize;
		d->downloadsize = 0;
	}

#endif


	return ret;
}


static int http_download_recvtofile( int s,int len,httpdownload * info)
{
	unsigned char *szTemp = (unsigned char *)malloc(RECVBUFFSIZE);
	int nTry = 0;
	int sumlen = 0;
#ifdef USE_TLS_SOCK
	while(sumlen < len && nTry < 300){		
		int nret = mf_ssl_recv2(s,szTemp ,RECVBUFFSIZE);
		if ( nret == 0)
		{
			if(nTry != 0 && nTry % 15 == 1){
				aq_ssl_recv3();
			}
			osl_Sleep(50);
		}
#else
	while(sumlen < len && nTry < 5){		
		int nret = mf_sock_recv(s,szTemp ,RECVBUFFSIZE ,3000 );
#endif
		if ( nret > 0 )
		{
			writetofile( info,(const char *)szTemp,nret);
			sumlen += nret;
			nTry=0;
		}
		else
		{
			nTry++;
			HTTP_TRACE( "http_download_recvtofile: %d/%d nTry = %d",sumlen,len , nTry);           
		}
	}
	free(szTemp);
	return sumlen;
}



static int http_download_recvbody(int sock,char *szTemp,int nRecvLen ,httpdownload *info)
{

	int hret = -1;
	char *bodystart = strstr( szTemp ,"\r\n\r\n" ) + 4;
	if ( bodystart != (char *)4 )
	{
		int nrescode = http_StatusCode(szTemp);
		HTTP_TRACE( "http rescode: %d",nrescode );
		if ( nrescode != -1 )
		{					
			info->ContentRange = http_ContentRange( szTemp );

			if ( nrescode == 200 || nrescode == 206 )
			{
				if ( nrescode == 200 )
				{//服务器不支持断点续传
					craetenewdownfile( info );
				}

				{
					//获取的部分文件内容
					int firstlen = nRecvLen - (bodystart - szTemp);
					int ContentLength = http_ContentLength(szTemp);

					HTTP_TRACE("Content-Length: %d",ContentLength);

					if ( ContentLength >  0)
					{
						if ( firstlen > 0)
						{
							writetofile(info,bodystart,firstlen);
						}
						
						//接收剩下的内容
						ContentLength -= firstlen;
						if ( ContentLength > 0 )
						{
							hret = http_download_recvtofile( sock, ContentLength,info);
							if (hret == ContentLength )
							{
								hret = 0;
							}
							else
							{
								HTTP_TRACE("recvtofileth: error");
								hret = -2;
							}
						}
						else
						{
							hret = 0;
						}
					}	
				}
							
			}
			else if (  nrescode == 416 )
			{//超出请求范围				
				if ( info->fdsize + info->downloadsize >= info->ContentRange )
				{//下载完成
					hret = 0;
				}
			}
			else if ( nrescode == 302 )
			{//重定向
				const char *newurlstr = http_headvalue(szTemp,"Location");
				if ( newurlstr != NULL )
				{
					char *d = strstr( newurlstr,"\r\n");
					if ( d != NULL )
					{
						*d='\0';
						HTTP_TRACE("httpdownload",LOG_LEVEL_INFO,"Location %s",newurlstr);
						if ( info->urllocation != NULL )
						{
							http_uri_destroy( info->urllocation );
							info->urllocation = NULL;
						}
						info->urllocation = http_uri_new();
						http_uri_parse(  newurlstr,info->urllocation);

						hret = 302;
					}
				}
			}
			else
			{
				HTTP_TRACE( "http rescode error : %d",nrescode  );
			}
		}
	}


	return hret;

}


static int http_download_procfile(httpdownload *info)
{
	int hret = -1;
	int nconnect = -1;
	int sock = mf_sock_create();


#ifndef WIN32
	//tms下载
	sock = HTTPSOCK;
#endif

#ifdef USE_TLS_SOCK
	sock = 1;
#endif	

	if ( sock >= 0 )
	{
		http_uri *uritem =  http_download_getconnecturi( info );
#ifdef USE_TLS_SOCK
		mf_ssl_init(sock ,0,0,0,0);
		nconnect = mf_ssl_connect( sock, uritem->host,uritem->port ,0);
#else
		nconnect = mf_sock_connect( sock, uritem->host,uritem->port );
#endif
		if ( nconnect >= 0 )
		{
			char *szTemp = (char *)malloc(RECVBUFFSIZE + 1);
			int ret = http_download_getreqbuff( info ,szTemp);//,"GET %s HTTP/1.1\r\nHost: %s:%d\r\nRange: bytes=%d- \r\nConnection: keep-alive\r\n\r\n" , huri->resource,huri->host,huri->port,fdsize);
#ifdef USE_TLS_SOCK
			int sendret = mf_ssl_send(sock,(unsigned char *)szTemp,ret );
			sendret = ret;
#else
			int sendret = mf_sock_send(sock,(unsigned char *)szTemp,ret );
#endif
			HTTP_TRACE( "mf_sock_send =%d",sendret);
			if ( sendret == ret )
			{
				char *bodystart = 0;
				int nRecvLen = 0;
				
				unsigned int nstarttick = osl_GetTick();
				while (bodystart == 0 && osl_CheckTimeover(nstarttick  ,RECVTIMEOUT) == 0)
				{
#ifdef USE_TLS_SOCK
					int nret = mf_ssl_recv2(sock,(unsigned char *)szTemp + nRecvLen ,RECVBUFFSIZE -nRecvLen);
#else
					int nret = mf_sock_recv(sock,(unsigned char *)szTemp + nRecvLen ,RECVBUFFSIZE -nRecvLen ,1000 );
#endif
					
					if ( nret > 0 )
					{
						nRecvLen += nret;
						szTemp[nRecvLen] = '\0';
						bodystart = strstr( szTemp ,"\r\n\r\n" );
						nstarttick = osl_GetTick();
					}
				}
                if(nRecvLen > 0 && bodystart != 0)
                {		
				  //HTTPTRACE( "%s",szTemp);
				    hret = http_download_recvbody( sock,szTemp,nRecvLen ,info);
                }
			}
			free(szTemp);
		}		
#ifdef USE_TLS_SOCK
		mf_ssl_close(sock);
#else
		mf_sock_close(sock);
#endif
	}

	return hret;
}


static int _http_download( const char *url,const char *fullpathfilename,int iscontinue )
{

	int ret = 0;
	httpdownload *info = http_download_create(url,fullpathfilename ,iscontinue);

	ret = http_download_procfile( info );
	if ( ret == 302 )
	{
		ret = http_download_procfile( info );
	}

	http_download_destroy(info);

	return ret;
}


int sdk_http_download( const char *url,const char *fullpathfilename,int iscontinue )
{
	int ret = -1;
	int nTry = 0;

	mf_sock_fifo_resize(HTTPSOCK,4096);
		
	
	while ( nTry < 5 && ret != 0 )
	{
		ret = _http_download(url,fullpathfilename, nTry == 0 ? iscontinue : 1);	
		nTry++;
	}

	if ( LCD_IS_320 )
	{
		mf_sock_fifo_resize(HTTPSOCK,2048);
	}
	else{

		mf_sock_fifo_resize(HTTPSOCK,1024);
	}

	return ret;
}


/*http download (add retry times)*/
int sdk_http_download_retry( const char *url,const char *fullpathfilename,int iscontinue, int nRetry )
{
	int ret = -1;
	int i;

	mf_sock_fifo_resize(HTTPSOCK,4096);

	if(nRetry<1) nRetry = 1;

	for(i=0; i<nRetry; i++)
	{
		ret = _http_download(url,fullpathfilename, i == 0 ? iscontinue : 1);	
	}

	if ( LCD_IS_320 )
	{
		mf_sock_fifo_resize(HTTPSOCK,2048);
	}
	else{

		mf_sock_fifo_resize(HTTPSOCK,1024);
	}


	return ret;
}

int sdk_http_download_progress_set( http_download_progress progressfun )
{
	s_progress = progressfun;
}
