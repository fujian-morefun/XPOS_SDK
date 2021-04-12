
#include <string.h>
#include "messagearrived.h"
//#include "driver/mf_supply_power.h"
#include "mqtt_proc.h"
#include "usermessage.h"
//#include "pub/common/misc/inc/mfmalloc.h"

static int _getval(const char *data, const char *key, char *outbuff, int size)
{
	char *pstart;

	char temp[32];
	sprintf(temp,"\"%s\":", key);
	pstart = strstr(data, temp);
	if ( pstart != 0 )
	{
		char *pend;
		pstart += strlen(temp);
		pend = strstr( pstart,",");
		if ( pend == 0)
		{
			pend = strstr( pstart,"}");
		}
		if ( pend != 0)
		{
			int rlen = 0;
			while ( *pstart == ' ')
			{
				pstart++;
			}

			if ( *pstart == '\"')
			{
				pstart++;
				pend--;
			}

			rlen = pend - pstart;
			memcpy( outbuff, pstart, rlen);
			outbuff[rlen] = 0;

			return rlen;
		}
	}

	return -1;
}
static int _getvalint(const char *data, const char *key)
{
	char temp[10];
	if ( _getval(data, key, temp, sizeof(temp)) > 0 )
	{
		return atoi(temp);
	}
	return -1;
}




static int download_pro( int current, int total)
{
	gui_begin_batch_paint();
	gui_clear_dc();
	gui_textout_line_center("Download" , GUI_LINE_TOP(0));
	if ( total != 0 )
	{
		char str[32] = {0};
		sprintf(str, "%d / %d", current, total);
		gui_textout_line_center(str, GUI_LINE_TOP(1));
	}
	gui_end_batch_paint();

}
#define BODYSIZE   512*1024
static void on_otaurl(const char *payload,int payloadlen)
{
	char temp[256];
	if( _getval( payload,"Url", temp, sizeof(temp)) > 0 )
	{
		int ret = 0;
		char filename[40] = "data\\tms.bin";
		char fname[32];
		int datalen = 0;
		char *pbody = (char *)Util_Malloc(BODYSIZE);

		int firmware = _getvalint( payload, "firmware");
		_getval( payload,"fname", fname, sizeof(fname));
		sprintf(filename,"data\\%s", fname);


		download_pro(0,0);
		http_download_progress_set(download_pro);
	
		//mqtt_proc_Pause();
		ret = http_download(temp, pbody, BODYSIZE , &datalen);
		//mqtt_proc_Resume();
		if ( ret == 0 )
		{
			File_WriteBlockByName( filename, 0, pbody, datalen );
		}
		Util_Free(pbody);

		if ( firmware == 1)
		{
			if(ret == 0)
			{
				if( tms_update(filename) == 0 )
				{
					Sys_Reboot();
				}
			}
		}


	}
}




static void on_showqr(const char *payload,int payloadlen)
{
	char temp[256];
	if( _getval( payload,"qr", temp, sizeof(temp)) > 0 )
	{
		status_page_showqr( temp );
	}
}

static void on_paymentend(const char *payload,int payloadlen)
{
	int st = _getvalint( payload,"st");
	if( st == 1){//player
	}
	else{
	}
	gui_post_message( XM_PAYMENTEND, st, 0);
}



int onmessageArrived_thread( const char *payload,int payloadlen )
{
	return 0;
}


/*
{"cmd":3,"qr":"upi://pay?pa=paytm-41607@paytm&pn=IOT%20Testing%20Merchant&mc=5641&tr=20200904182027&am=1.44&cu=INR&paytmqr=281005050101J72QZHGZ5VJT", "oid":"20200904182027", "amt":"1.44"}
{"retries": 10, "cmd": 5, "Url": "https://iot-dev.paytm.in/paytm-api/otaupdate/tms", "oId": "1234", "firmware": 1, "version": "d1.1", "fname": "tms.bin", "Restart": 1}
{"cmd":2,"amt":"1.40","st":1, "oid":"20200904175129"}
*/

void onmessageArrived(const char *payload,int payloadlen)
{
	int i = 0;
	int cmd = _getvalint(payload,"cmd");
	if ( cmd == 2)
	{
		on_paymentend(payload, payloadlen);
	}
	else if ( cmd == 3)
	{
		on_showqr(payload, payloadlen);
	}
	else if ( cmd == 5)
	{
		on_otaurl(payload, payloadlen);
	}
}
