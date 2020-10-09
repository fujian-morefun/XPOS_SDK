#ifdef WIN32
//#include <windows.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "http_download.h"


#include "pub/common/misc/inc/mfmalloc.h"
#include "pub/tracedef.h"

#define HTTP_TRACE      APP_TRACE

static app_http_download_progress s_progress = 0;


typedef struct app_http_uri_tag
{
	char             *full;                          /* full URL */
	char             *proto;                         /* protocol */
	char             *host;                          /* copy semantics */
	unsigned short    port;
	char             *resource;                      /* copy semantics */

} app_http_uri;


typedef enum uri_parse_state_tag
{
	parse_state_read_host = 0,
	parse_state_read_port,
	parse_state_read_resource
} uri_parse_state;


static int app_http_uri_parse(const char *a_string, app_http_uri *a_uri)
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

static app_http_uri * app_http_uri_new(void)
{
	app_http_uri *l_return = NULL;

	l_return = (app_http_uri *)malloc(sizeof(app_http_uri));
	l_return->full = NULL;
	l_return->proto = NULL;
	l_return->host = NULL;
	l_return->port = 80;
	l_return->resource = NULL;
	return l_return;
}

static void app_http_uri_destroy(app_http_uri *a_uri)
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





static char *app_http_headvalue( char *heads ,const char *head )
{
	char *pret = strstr( heads ,head );
	if ( pret != 0 )
	{
		pret += strlen(head);
		pret += strlen(": ");
	}
	return pret;

}
static int app_http_ContentLength(char *heads)
{
	char *pContentLength = app_http_headvalue( heads ,"content-length" );
	if ( pContentLength != 0)
	{
		return atoi( pContentLength );
	}
        
        pContentLength = app_http_headvalue( heads ,"Content-Length" );
	if ( pContentLength != 0)
	{
		return atoi( pContentLength );
	}
        
	return -1;
}

static int app_http_ContentRange(char *heads)
{	
	char *val = app_http_headvalue(heads, "Content-Range" );
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

static int app_http_StatusCode(char *heads)
{	
	char *rescode = strstr( heads ," " );
	if ( rescode != 0 )
	{
		rescode+=1;
		return atoi( rescode);
	}
	else
	{
		HTTP_TRACE( "app_http_StatusCode error %s", heads );
	}

	return -1;
}


#define RECVTIMEOUT 30000
#define RECVBUFFSIZE 2048


static int app_http_uri_getreqbuff( app_http_uri *d,int offset,char *reqbuff)
{
	return sprintf(reqbuff,"GET %s HTTP/1.1\r\nHost: %s:%d\r\nRange: bytes=%d- \r\nConnection: keep-alive\r\nCache-Control: no-cache\r\n\r\n" 
		, d->resource,d->host,d->port,offset
	);
}

static int connectitck;
static int _connect_server_func( int sock)
{
	if ( osl_CheckTimeover(connectitck ,RECVTIMEOUT ) )
	{
		return -2;
	}
	return 0;

}
static int app_http_uri_connect( app_http_uri *uritem ,int sock )
{
	int ret;
	connectitck = osl_GetTick();

	HTTP_TRACE("comm_ssl_init\r\n" );
	comm_ssl_init(sock, 0, 0, 0,0);
	HTTP_TRACE("comm_ssl_connect2 %d %s %d\r\n" , sock, uritem->host,uritem->port );

	ret = comm_ssl_connect2( sock, uritem->host,uritem->port ,_connect_server_func );

	HTTP_TRACE("comm_ssl_connect2 =%d\r\n" , ret );

	return ret;
}
static int app_http_uri_send(app_http_uri *uritem ,int sock, char * pdata, int size)
{

	int sendret = comm_ssl_send( sock,(unsigned char *)pdata,size );
	
	return size;
}

static int app_http_uri_recv(app_http_uri *uritem ,int sock, char * pdata, int size)
{
	int ret;
	static int timer = 0;
	if ( Sys_TimerCheck( timer ) == 0)
	{
		mf_ssl_recv3(sock);
		timer = Sys_TimerOpen( 1000 );
	}

	ret = comm_ssl_recv(sock,(unsigned char *)pdata ,size);

	return ret;
}

static int app_http_uri_close(app_http_uri *uritem ,int sock)
{
	int ret;
	ret = comm_ssl_close(sock);
	return ret;
}

static int app_http_progress( int bodyindex, int ContentLength)
{
	if (s_progress !=0 )
	{
		int iscancel = 0;
		iscancel=s_progress( bodyindex, ContentLength);
		if ( iscancel != 0)
		{
			return iscancel;
		}
	}
	return 0;
}

int app_http_download_uri( app_http_uri *uritem ,char *data,int datasize,int *inout_offset )
{	
	int hret = HTTP_ERR_NETLINK;
	int inoffset = *inout_offset;
	int offset = inoffset;

	HTTP_TRACE("app_http_download_uri datasize=%d ,offset=(%d,%d,%d)\r\n" , datasize,inoffset,offset,*inout_offset );

	hret = comm_net_link("Dial","CMNET",30*1000);
	if ( hret == 0 )
	{
		int nconnect = -1;
		int sock = 0;
		sock = comm_sock_create(0);


		nconnect = app_http_uri_connect( uritem,sock );
		if ( nconnect >= 0 )
		{
			char *pdst = data + offset;
			int dstsize = datasize - offset;

			char *bodystart = 0;
			int index = 0;
			int ContentLength = 0;
			int nStatusCode = 0;

			int bodyindex = 0;
			int nRecvLen = 0;
			unsigned int nstarttick = 0;

			char *szTemp = (char *)malloc(RECVBUFFSIZE + 1);

			int ret = app_http_uri_getreqbuff( uritem , *inout_offset ,szTemp);

			int sendret = app_http_uri_send( uritem , sock,(unsigned char *)szTemp,ret );
			szTemp[sendret] = 0;

			memset(szTemp,0x00, RECVBUFFSIZE);
			bodystart = 0;
			ContentLength = 0;

			hret = HTTP_ERR_RECVHEAD;
			nstarttick = osl_GetTick();
			index = 0;
			//http head
			while (osl_CheckTimeover(nstarttick  ,RECVTIMEOUT) == 0)
			{
				int nret = app_http_uri_recv( uritem ,sock,(unsigned char *)szTemp + index ,RECVBUFFSIZE -index);
				if ( nret > 0)
				{
					index += nret;
					szTemp[index] = 0;
					if ( bodystart == 0)
					{
						bodystart = strstr( szTemp ,"\r\n\r\n" );
						if ( bodystart != 0 )
						{//head
							int len;
							ContentLength = app_http_ContentLength(szTemp);
							nStatusCode = app_http_StatusCode(szTemp);
							if ( nStatusCode == 200 || nStatusCode == 206 )
							{
								int ContentRange = app_http_ContentRange( szTemp );
								if ( ContentRange == -1)
								{//is not supported
									offset = 0;
									pdst = data;
									dstsize = datasize - offset;
								}
								if ( dstsize < ContentLength)
								{
									hret = HTTP_ERR_OVERFLOW;
								}
								else
								{
									bodystart += 4;	
									len = index - (bodystart - szTemp);
									memcpy( pdst , bodystart, len);
									bodyindex = len;
									hret = HTTP_ERR_SUCC;
								}
								break;
							}
							else{
								hret = HTTP_ERR_STATUS;
								break;
							}
						}
					}
				}
				else{
					Sys_Delay(200);
				}
			}
			free(szTemp);

			if ( hret == HTTP_ERR_SUCC && bodyindex < ContentLength )
			{//	http body
				hret = HTTP_ERR_RECVBODY;
				nstarttick = osl_GetTick();		
				while( bodyindex < ContentLength && osl_CheckTimeover(nstarttick  ,RECVTIMEOUT) == 0)
				{		
					int nret;
					nret = app_http_uri_recv( uritem ,sock,(unsigned char *)pdst + bodyindex ,dstsize - bodyindex );
					if ( nret > 0)
					{
						bodyindex += nret;
						nstarttick = osl_GetTick();

						if ( app_http_progress(bodyindex, ContentLength) != 0)
						{
							hret = HTTP_ERR_CANCEL;
							break;
						}
					}
					else{
						Sys_Delay(500);
					}
				}
			}
			*inout_offset = offset + bodyindex;
			if ( bodyindex == ContentLength)
			{
				hret = HTTP_ERR_SUCC;
			}
		}
		else{
			hret = HTTP_ERR_CONNECT;
		}
		app_http_uri_close( uritem , sock);
	}
	else{
		hret = HTTP_ERR_NETLINK;
	}
	
	HTTP_TRACE("app_http_download_uri ContentLength=%d ,hret = %d\r\n" , datasize,hret );

	return hret;
}


int app_http_download( const char *url, char *data,int datasize,int *outlen )
{
	int ret = -1;
	int offset = 0;
	int trycount = 3;
	int recvlen;

	app_http_uri *a_uri = app_http_uri_new();

	ret = app_http_uri_parse(url,a_uri);
	if ( ret != 0)
	{
		ret = HTTP_ERR_URLPARSE;
	}
	
	recvlen = 0;
	while ( trycount > 0)
	{
		ret = app_http_download_uri( a_uri, data, datasize, &recvlen );
		if ( ret == HTTP_ERR_SUCC
			|| ret == HTTP_ERR_OVERFLOW
			|| ret == HTTP_ERR_CANCEL
			)
		{
			break;
		}

		trycount--;
	}
	*outlen = recvlen;
	app_http_uri_destroy(a_uri);

	return ret;

}


int app_http_download_progress_set( app_http_download_progress progressfun )
{
	s_progress = progressfun;
}

int app_http_download_test()
{
	char data[1024*512];
	int datalen;
	//const char *url = "https://www.baidu.com/img/baidu_jgylogo3.gif";
	const char *url = "https://mf.ghttps.com:8433/paytm-api/otaupdate/tms";
	int ret = app_http_download( url
		,data, sizeof(data) , &datalen
		);

	if ( ret == 0 )
	{
		//File_WriteBlockByName( )
	}
}
