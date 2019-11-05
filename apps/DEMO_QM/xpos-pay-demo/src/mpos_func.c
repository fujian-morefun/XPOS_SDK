#include "driver\uart.h"
#include "xgui\inc\message.h"
#include "mpos_pub.h"
#include "mpos_func.h"
//#include "pub/tracedef.h"
#include "xGui/inc/message.h"
#include "xGui/inc/xgui_key.h"
#include "pub/osl/inc/osl_time.h"
#include "driver/mf_rtc.h"


#define		MPOS_FUNC_RESET				0x0001
#define		MPOS_FUNC_PAY				0x0002

static st_qr_data mpos_qr_data = {0};

extern int g_playtag;

st_qr_data  * mpos_func_get_qr_data()
{
	return &mpos_qr_data;
}


void dev_reset(st_pkt_info *pkt_info)
{
	unsigned char state[1];
	int i = 0,j;

	//APP_TRACE("dev_reset");

	for(i = 0 ; i < 3; i ++){
		for(j = 0; j < 3; j ++){
			xgui_PostMessage(XM_KEYPRESS, KEY_CANCEL, 0);
		}
		osl_Sleep(100);
	}
	//memset(mpos_qr_data.qrdata, 0, sizeof(mpos_qr_data.qrdata));
	memset(&mpos_qr_data, 0, sizeof(mpos_qr_data));

	state[0] = 0x00;
	mpos_pub_send_pkt(state , sizeof(state) , pkt_info);
}

void set_qrdata(st_pkt_info *pkt_info)
{
	unsigned char state[1];
	int n = 0;

	//nAPP_TRACE("set_qrdata:%s", pkt_info->pbuff);

	//memset(mpos_qr_data.amt, 0, sizeof(mpos_qr_data.amt));
	//memset(mpos_qr_data.qrdata, 0, sizeof(mpos_qr_data.qrdata));
	memset(&mpos_qr_data, 0, sizeof(mpos_qr_data));
	mpos_pub_pkt_tlv_get(pkt_info->pbuff, pkt_info->len, MPOS_PAY_ITEM_AMT, mpos_qr_data.amt);
	//APP_TRACE("amt:%s\r\n" , mpos_qr_data.amt);
	//memset(mpos_qr_data.qrdata, 0, sizeof(mpos_qr_data.qrdata));
	mpos_pub_pkt_tlv_get(pkt_info->pbuff, pkt_info->len, MPOS_PAY_ITEM_QRDATA, mpos_qr_data.qrdata);
	//APP_TRACE("qrcode:%s\r\n" , mpos_qr_data.data);

	state[0] = 0x00;
	mpos_pub_send_pkt(state , sizeof(state) , pkt_info);
}

void set_text(st_pkt_info *pkt_info)
{
	unsigned char state[1];
	int n = 0;

	//nAPP_TRACE("set_qrdata:%s", pkt_info->pbuff);

	//memset(mpos_qr_data.text, 0, sizeof(mpos_qr_data.text));
	//memset(mpos_qr_data.qrdata, 0, sizeof(mpos_qr_data.qrdata));
	memset(&mpos_qr_data, 0, sizeof(mpos_qr_data));
	mpos_pub_pkt_tlv_get(pkt_info->pbuff, pkt_info->len, MPOS_PAY_ITEM_TEXT, mpos_qr_data.text);
	//APP_TRACE("amt:%s\r\n" , mpos_qr_data.amt);	

	//memset(mpos_qr_data.amt, 0, sizeof(mpos_qr_data.amt));
	//memset(mpos_qr_data.qrdata, 0, sizeof(mpos_qr_data.qrdata));

	state[0] = 0x00;
	mpos_pub_send_pkt(state , sizeof(state) , pkt_info);
	g_playtag = 1;
}

void set_systime(st_pkt_info *pkt_info)
{
	unsigned char state[1];
	char temp[32] = {0};
	struct rtc_time date_time;	

	//APP_TRACE("set_systime:%s", pkt_info->pbuff);

	mpos_pub_pkt_tlv_get(pkt_info->pbuff, pkt_info->len, MPOS_PAY_ITEM_DATETIME, temp);
	//APP_TRACE("datetime:%s\r\n" , temp);
	mf_rtc_get_time(&date_time);
	date_time.tm_year = mpos_pub_atoi(temp, 4);
	date_time.tm_mday = mpos_pub_atoi(temp+4, 2);
	date_time.tm_mon = mpos_pub_atoi(temp+6, 2);
	date_time.tm_hour = mpos_pub_atoi(temp+8, 2);
	date_time.tm_min = mpos_pub_atoi(temp+10, 2);
	date_time.tm_sec = mpos_pub_atoi(temp+12, 2);

	mf_rtc_set_time(&date_time);

	state[0] = 0x00;
	mpos_pub_send_pkt(state , sizeof(state) , pkt_info);
}


static void pay_proc(st_pkt_info *pkt_info)
{
	unsigned char buff[256]={0};
	int size = 0;
	char type[32] = {0};

	mpos_pub_pkt_tlv_get(pkt_info->pbuff, pkt_info->len, MPOS_PAY_ITEM_TYPE, type);

	if (strcmp(type, "01") == 0)
	{
		set_qrdata(pkt_info);	
	}
	else if (strcmp(type, "02") == 0)
	{
		set_text(pkt_info);
	} 	
	else if (strcmp(type, "03") == 0)
	{
		set_systime(pkt_info);
	}
	else
	{

	}
}


//STX(0x4D46)  Data length	 Instruction number  Command number Serial number Response code Variable data	ETX(0x02)	LRC	
//2bytes		2 bytes			 1 byte				2 bytes			1 byte		 2 bytes	   variable		 1 byte	    1byte
int mpos_func_proc(unsigned char * data, int len)
{
	int ret ;
	st_pkt_info pkt_info;
	extern st_qr_data g_qr_data;

	//APP_TRACE("mpos_func_proc");
	power_key_set_light();
	ret = mpos_pub_pkt_check(data , len , &pkt_info);
	if(ret != 0) return ret;

	if (MPOS_FUNC_RESET == pkt_info.func){
		dev_reset(&pkt_info);
	}
	else if (MPOS_FUNC_PAY == pkt_info.func)
	{
		pay_proc(&pkt_info);
	}
	else
	{
		pkt_info.ret = 1;
		//mpos_pub_send_pkt(&pkt_info);
	}

	xgui_PostMessage(XM_GUIPAINT, 0, 0);	

	return 0;
}
