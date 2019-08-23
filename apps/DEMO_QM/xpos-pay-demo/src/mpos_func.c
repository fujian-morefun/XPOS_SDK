#include "driver\uart.h"
#include "xgui\inc\message.h"
#include "mpos_pub.h"
#include "mpos_func.h"
#include "pub/tracedef.h"
#include "xGui/inc/message.h"
#include "xGui/inc/xgui_key.h"
#include "pub/osl/inc/osl_time.h"
#include "driver/mf_rtc.h"


#define	MPOS_FUNC_RESET			0x01
#define	MPOS_FUNC_SET_TIME		0x02
#define	MPOS_FUNC_SET_QR		0x03

static st_qr_data mpos_qr_data = {0};

st_qr_data  * mpos_func_get_qr_data()
{
	return &mpos_qr_data;
}


void dev_reset(st_pkt_info *pkt_info)
{
	unsigned char state[1];
	int i = 0,j;
	
	APP_TRACE("dev_reset");

	for(i = 0 ; i < 3; i ++){
		for(j = 0; j < 3; j ++){
			xgui_PostMessage(XM_KEYPRESS, KEY_CANCEL, 0);
		}
		osl_Sleep(100);
	}
	memset(mpos_qr_data.data, 0, sizeof(mpos_qr_data.data));

	//mpos_pub_send_pkt(pkt_info);
}

void set_systime(st_pkt_info *pkt_info)
{
	unsigned char state[1];
	struct json_object *rootobj=0;
	char temp[32] = {0};
	struct rtc_time date_time;	

	APP_TRACE("set_systime:%s", pkt_info->pbuff);

	rootobj = (struct json_object *)json_tokener_parse((char *)pkt_info->pbuff);
	if ((int)rootobj > 0)
	{
		mpay_pub_get_json(rootobj, "DT", temp, 20);
		APP_TRACE("datetime:%s\r\n" , temp);
		mf_rtc_get_time(&date_time);
		date_time.tm_year = mpos_pub_atoi(temp, 4);
		date_time.tm_mon = mpos_pub_atoi(temp+4, 2);
		date_time.tm_mday = mpos_pub_atoi(temp+6, 2);
		date_time.tm_hour = mpos_pub_atoi(temp+8, 2);
		date_time.tm_min = mpos_pub_atoi(temp+10, 2);
		date_time.tm_sec = mpos_pub_atoi(temp+12, 2);

		mf_rtc_set_time(&date_time);
		json_object_put(rootobj);
	}
	else
	{
		pkt_info->ret = 2;
	}
	
	//mpos_pub_send_pkt(pkt_info);
}

void set_qrdata(st_pkt_info *pkt_info)
{
	unsigned char state[1];
	struct json_object *rootobj=0;
	char temp[256] = {0};
	int n = 0;

	APP_TRACE("set_qrdata:%s", pkt_info->pbuff);

	rootobj = (struct json_object *)json_tokener_parse((char *)pkt_info->pbuff);
	if ((int)rootobj > 0)
	{
		mpay_pub_get_json(rootobj, "A", temp, 16);
		strcpy(mpos_qr_data.amt, temp);
		APP_TRACE("amt:%s\r\n" , mpos_qr_data.amt);
		memset(temp, 0, sizeof(temp));
		mpay_pub_get_json(rootobj, "D", temp, 128);
		strcpy(mpos_qr_data.data, temp);
		APP_TRACE("qrcode:%s\r\n" , mpos_qr_data.data);
// 		memset(temp, 0, sizeof(temp));
// 		mpay_pub_get_json(rootobj, "X", temp, 1);
// 		n = strlen(temp);
// 		if (n > 0)
// 		{
// 			mpos_qr_data.x = atoi(temp);
// 		} 
// 		else
// 		{
// 			mpos_qr_data.x = 3;
// 		}
// 		APP_TRACE("locationX:%d\r\n" , mpos_qr_data.x);
// 		memset(temp, 0, sizeof(temp));
// 		mpay_pub_get_json(rootobj, "Y", temp, 1);
// 		n = strlen(temp);
// 		if (n > 0)
// 		{
// 			mpos_qr_data.y = atoi(temp);
// 		} 
// 		else
// 		{
// 			mpos_qr_data.y = 1;
// 		}
//		APP_TRACE("locationY:%d\r\n" , mpos_qr_data.y);
// 		memset(temp, 0, sizeof(temp));
// 		mpay_pub_get_json(rootobj, "S", temp, 1);
// 		n = strlen(temp);
// 		if (n > 0)
// 		{
// 			mpos_qr_data.size= atoi(temp);
// 		} 
// 		else
// 		{
// 			mpos_qr_data.size = 1;
// 		}
// 		APP_TRACE("size:%d\r\n" , mpos_qr_data.size);

		json_object_put(rootobj);
	}
	else
	{
		pkt_info->ret = 2;
	}

	//mpos_pub_send_pkt(pkt_info);
}

//STX(0x4D46)  Data length	 Instruction number  Variable data		ETX(0x02)		
//2bytes		2bytes			 1 byte				variable		1bytes	
int mpos_func_proc(unsigned char * data, int len)
{
	int ret ;
	st_pkt_info pkt_info;
//	extern st_qr_data g_qr_data;

	APP_TRACE("mpos_func_proc");
	power_key_set_light();
	ret = mpos_pub_pkt_check(data , len , &pkt_info);
	if(ret != 0) return ret;

	if (MPOS_FUNC_RESET == pkt_info.func){
		dev_reset(&pkt_info);
	}
	else if (MPOS_FUNC_SET_TIME == pkt_info.func){	
		set_systime(&pkt_info);
	}
	else if (MPOS_FUNC_SET_QR == pkt_info.func)
	{
		set_qrdata(&pkt_info);
	}
	else
	{
		pkt_info.ret = 1;
		//mpos_pub_send_pkt(&pkt_info);
	}



	// 	strcpy(qr_data->title, data);
	// 	APP_TRACE("title:%s\r\n" , qr_data->title);
	// 	strcpy(qr_data->data, data);
	// 	APP_TRACE("qrcode:%s\r\n" , qr_data->data);
// 	 	mpos_qr_data.x = 3;
// 	 	APP_TRACE("locationX:%d\r\n" , mpos_qr_data.x);
// 	 	mpos_qr_data.y = 1;
// 	 	APP_TRACE("locationY:%d\r\n" , mpos_qr_data.y);
// 	 	mpos_qr_data.size = 1;
// 	 	APP_TRACE("size:%d\r\n" , mpos_qr_data.size);
        xgui_PostMessage(XM_GUIPAINT, 0, 0);	
        
	return 0;
}
