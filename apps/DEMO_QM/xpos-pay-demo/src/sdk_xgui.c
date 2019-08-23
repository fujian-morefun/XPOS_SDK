#include "xGui/inc/mainmenu.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/ime.h"
#include "xGui/inc/messagedatastruct.h"
#include "xGui/inc/message.h"
#include "xGui/inc/messagebox.h"
#include "xGui/inc/xgui_key.h"
#include "xGui/inc/pageproc.h"
#include "sdk_http.h"
#include "sdk_showqr.h"
#include "sdk_file.h"
#include "sdk_img.h"
#include "driver/mf_rtc.h"
#include "pub/common/misc/inc/mfmalloc.h"
#include "xGui/inc/xgui_bmp.h"
#include "pub/osl/inc/osl_BaseParam.h"
#include "mpos_func.h"
#include "test/test_pub.h"
#include "driver/mf_supply_power.h"
#include "atc/inc/atc_pub.h"
#include "wifi/inc/wifi_pub.h"
#include "power_bmp.h"
#include "atc_bmp.h"
#include "wifi_bmp.h"

//Upgrade downloaded files
LIB_EXPORT int tms_update(const char *file);

#define LOGOIMG "data\\logo2.bmp"

#define MAIN_MENU_PAGE	"main"


#ifdef DEV_MF67
	#define BLUETOOTH 1
	#define SERIALPORT 1
#else
	#define COSUME 1	//MF67 memory is relatively small, remove the bank card EMV code
	//#define TMS	1
#endif




enum{
	DRIVER_TYPE_MAG,
	DRIVER_TYPE_ICC,
	DRIVER_TYPE_RF,
};

static  const st_main_menu_item_def _menu_def[] = {
	{MAIN_MENU_PAGE ,	"Test",			""},
#ifdef COSUME
	{MAIN_MENU_PAGE ,	"Sale",			""},
#endif
	{MAIN_MENU_PAGE ,	"CodePay",		""},
	{MAIN_MENU_PAGE ,	"Version",		""},
	{MAIN_MENU_PAGE ,	"Settings",		""},

	{"Test" ,	"DevInfo",		""},
	//{"Test" ,	"Print",		""},
	//{"Test",	"magcard",		""},
	//{"Test",	"Ic",			""},
#ifdef COSUME
	{"Test",	"RF",			""},
#endif
	{"Test",	"M1",			""},
	//{"Test",	"Touch",		""},
	//{"Test",	"Barcode",		""},
	{"Test",	"Security",		""},
	{"Test",	"Http",		    ""},
	{"Test",	"Https",		""},
	{"Test",	"ShowQr",		""},
	{"Test",	"File",		    ""},
	{"Test",	"ShowBmp",		""},	
	{"Test",    "Led",          ""},
	{"Test",    "Voice",        ""},
#ifdef BLUETOOTH 
	{"Test",    "Bluetooth",    ""},
#endif

#ifdef SERIALPORT
	{"Test",    "SerialPort",   ""},
#endif

#ifdef TMS
	{"Test",    "TMS",			""},
#endif

	{"Settings",	"Wifi Set",	""},
	{"Settings",	"keySound",		""},
	{"Settings",	"lcdLight",		""},
	{"Settings",	"powerTime",	""}, 
	//{"Settings",	"TimeSet",		""},
	//{"Settings",	"Open Log",		""},	
};


static int _menu_proc(char *pid)
{
	int ret;
	char buff[20];
	int pos = 0;

	if (strcmp(pid , "Sale") == 0){
#ifdef COSUME
		upay_consum();
#else
		xgui_messagebox_show("Sale", "Not support", "", "confirm" , 3000);		
#endif
	}
	else if (strcmp(pid , "Version") == 0){
		if (lcd_get_sublcd_probe() == 1)
		{
			xgui_messagebox_show( "Version" , (char *)APP_VISION+5 , "" , "confirm" , 0);
		}
		else
		{
			xgui_messagebox_show( "Version" , (char *)APP_VISION , "" , "confirm" , 0);
		}
	}
	else if (strcmp(pid , "CodePay") == 0){	
		upay_barscan();
	}
	else if (strcmp(pid , "DevInfo") == 0)
	{
		test_devinfo();
	}
// 	else if (strcmp(pid , "Print") == 0)
// 	{
// 		sdk_print();
// 	}
// 	else if (strcmp(pid , "magcard") == 0)
// 	{
// 		test_magcard();
// 	}
// 	else if (strcmp(pid , "Ic") == 0)
// 	{
// 		test_IC();
// 	}
	else if (strcmp(pid , "RF") == 0)
	{
#ifdef COSUME
		if (lcd_get_sublcd_probe() == 1)
		{
			xgui_messagebox_show("RF Test", "See the big LCD", "", "confirm" , 300);		
			lcd_set_index(0);
		}
		test_rf();
		if (lcd_get_sublcd_probe() == 1)
		{
			lcd_set_index(1);
		}
#else
		xgui_messagebox_show("RF Test", "Not support", "", "confirm" , 3000);		
#endif
	}
	else if (strcmp(pid , "M1") == 0){
		if (lcd_get_sublcd_probe() == 1)
		{
			xgui_messagebox_show("RF M1", "See the big LCD", "", "confirm" , 300);		
			lcd_set_index(0);
		}	
		test_m1();
		if (lcd_get_sublcd_probe() == 1)
		{
			lcd_set_index(1);
		}
	}
// 	else if (strcmp(pid , "Touch") == 0)
// 	{
// 		test_touch();
// 	}
//	else if (strcmp(pid , "Barcode") == 0)
//	{
//		sdk_driver_barcode();
//	}
	else if (strcmp(pid , "keySound") == 0)
	{
		keySoundSet_Show_test();
	}
	else if (strcmp(pid , "lcdLight") == 0)
	{
		lcdLightSet_Show();
	}
	else if (strcmp(pid , "powerTime") == 0)
	{
		PowerDownTimeSet_Show();
	}
	else if (strcmp(pid , "TimeSet") == 0)
	{
		timeTest();
	}
	else if (strcmp(pid , "Security") == 0)
	{
// 		if (lcd_get_sublcd_probe() == 1)
// 		{
// 			lcd_set_index(0);
// 		}
		securityTest();
// 		if (lcd_get_sublcd_probe() == 1)
// 		{
// 			lcd_set_index(1);
// 		}
	}
	else if (strcmp(pid , "ShowQr") == 0){
		if (lcd_get_sublcd_probe() == 1)
		{
			xgui_messagebox_show("ShowQr", "See the big LCD", "", "confirm" , 300);		
			lcd_set_index(0);
		}
		showQr2("0.01");
		if (lcd_get_sublcd_probe() == 1)
		{
			lcd_set_index(1);
		}
	}	
	else if (strcmp(pid , "Http") == 0)	{
		sdk_http_test();
	}
	else if (strcmp(pid , "Https") == 0)	{
		sdk_https_test();
	}	
	else if (strcmp(pid , "File") == 0){
		fileTest();
	}
	else if (strcmp(pid , "ShowBmp") == 0){
		if (lcd_get_sublcd_probe() == 1)
		{
			xgui_messagebox_show("ShowBmp", "See the big LCD", "", "confirm" , 300);		
			lcd_set_index(0);
		}
		showbmptest();
		if (lcd_get_sublcd_probe() == 1)
		{
			lcd_set_index(1);
		}
	}
	else if(strcmp(pid, "Led") == 0){
		sdk_driver_led();
	}
	else if (strcmp(pid, "Open Log") == 0)
	{
		LogOutSet_Show();
	}
	else if (strcmp(pid, "Voice") == 0)
	{
		VoiceTest();
	}
	else if (strcmp(pid, "Bluetooth") == 0)
	{
#ifdef BLUETOOTH
		BluetoothTest();
#else
		xgui_messagebox_show("BluetoothTest", "Not support", "", "confirm" , 3000);	
#endif
	}
	else if (strcmp(pid, "SerialPort") == 0)
	{
#ifdef SERIALPORT
		if (lcd_get_sublcd_probe() == 1)
		{
			xgui_messagebox_show("SerialPortTest", "See the big LCD", "", "confirm" , 300);		
			lcd_set_index(0);
		}
		SerialPortTest();
		if (lcd_get_sublcd_probe() == 1)
		{
			lcd_set_index(1);
		}
#else
		xgui_messagebox_show("SerialPortTest", "Not support", "", "confirm" , 3000);		
#endif
	}
	else if (strcmp(pid, "Wifi Set") == 0)
	{
		xgui_main_menu_show2("Wifi Menu", "Wifi Menu", 60000);
	}
	else if (strcmp(pid, "TMS") == 0)
	{
#ifdef TMS
		xgui_messagebox_show("TMS Update", "Waiting...", "", "confirm" , 3000);		
		tms_update("data\\tms.bin");
		mf_system_power_state(POWER_STATE_RESET);
#else
		xgui_messagebox_show("TMSTest", "Not support", "", "confirm" , 3000);		
#endif
	}


	return 0;
}




void get_yyyymmdd_str(char *buff)
{
	struct rtc_time dt;
	mf_rtc_get_time(&dt);
	sprintf(buff , "%04d-%02d-%02d", dt.tm_year, dt.tm_mon, dt.tm_mday);
}


void get_hhmmss_str(char *buff)
{
	struct rtc_time date_time;
	mf_rtc_get_time(&date_time);
	sprintf(buff, "%02d:%02d:%02d", date_time.tm_hour, date_time.tm_min, date_time.tm_sec);
}

void standby_pagepaint()
{
	char data[32]={0};
	int logowidth;
	int logoheight;
	int logoleft;
	int logotop;
	int logocolor;

	char * pbmp;	

	if (lcd_get_sublcd_probe() == 1)
	{
		lcd_set_index(0);
	}
	xgui_BeginBatchPaint();
	XGUI_SET_WIN_RC;
	xgui_ClearDC();

	xgui_SetTitle("Pay Demo");

	{
		logoleft = 15;
		logotop = XGUI_LINE_TOP_1;

		pbmp = (char *)xgui_load_bmp_all(LOGOIMG , &logowidth , &logoheight, &logocolor);

		if (pbmp != 0){
			xgui_out_bits_bmp(logoleft, logotop, pbmp , logowidth , logoheight , 0 , logocolor);
			FREE(pbmp);
		}
	}

	get_yyyymmdd_str(data);	
	xgui_TextOut_Line_Center(data, XGUI_LINE_TOP_4);
	get_hhmmss_str(data);	
	xgui_TextOut_Line_Center(data, XGUI_LINE_TOP_5);


	xgui_EndBatchPaint();
	if (lcd_get_sublcd_probe() == 1)
	{
		lcd_set_index(1);
	}
}

static int get_power()
{ 
	battery_attr_t batterAttr;
	int ret;
	int state = -1;

	ret = mf_power_battery_attr(&batterAttr);	

	if (ret < 0){
		return state;
	}

	if (batterAttr.status == POWER_SUPPLY_STATUS_CHARGING){
		state = 5;
	}
	else{
		state = batterAttr.voltage_level -1;
		if (state < 0 || state > 5){
			state = 0;
		}
	}

	return state;
}

void standby_pagepaint2()
{
	char data[32]={0};
	int logowidth;
	int logoheight;
	int logoleft;
	int logotop;
	int logocolor;
	int power_state = get_power();
	int atc_state = atc_signal();
	int wifi_state = wifi_get_signal();

	//lcd_set_index(1);
	xgui_BeginBatchPaint();
	XGUI_SET_WIN_RC;
	xgui_ClearDC();

	logotop = XGUI_LINE_TOP_0-3;

	logoleft = 5;
	xgui_out_bits(logoleft, logotop, (unsigned char *)m_atc_signal_buff_128[atc_state] , SIGNAL_BMP_WIDTH_128 , SIGNAL_BMP_HEIGHT_128 , 0);

	logoleft = 30;
	xgui_out_bits(logoleft, logotop, (unsigned char *)m_wifi_signal_buff_160[wifi_state] , SIGNAL_BMP_WIDTH_160 , SIGNAL_BMP_HEIGHT_160 , 0);

	logoleft = BATTER_BMP_LEFT_128;
	xgui_out_bits(logoleft, logotop, (unsigned char *)m_batter_buff_128[power_state] , BATTER_BMP_WIDTH_128 , BATTER_BMP_HEIGHT_128 , 0);
	get_yyyymmdd_str(data);	
 	xgui_TextOut_Line_Center(data, XGUI_LINE_TOP_0+7);
 	get_hhmmss_str(data);	
 	xgui_TextOut_Line_Center(data, XGUI_LINE_TOP_1+3);

	xgui_EndBatchPaint();
	//lcd_set_index(0);
}


void sdk_main_page()
{
	MESSAGE pMsg;
	static int xgui_init_flag = 0;
	char time_cur[20];
	char time_last[20];
	int i;
	//st_qr_data  * mpos_qr_data = mpos_func_get_qr_data();

	get_hhmmss_str(time_last);

	sdk_timer_init();

	

	if(xgui_init_flag == 0){
		xgui_init_flag = 1;
		xgui_main_menu_func_add((void *)_menu_proc);		// Registration menu callback processing
		for(i = 0; i < MENU_ITEM_COUNT(_menu_def); i ++){	// Add menu items cyclically
			xgui_main_menu_item_add(_menu_def + i);	
		}
	}
	
// 	if (osl_get_is_m67())//only MF67 use serial communication
// 	{
// 		init_com();
// 	}
	//strcpy(mpos_qr_data->amt, "1.00");
	//strcpy(mpos_qr_data->data, "http://en.morefun-et.com");
	//strcpy(mpos_qr_data->data, "00020101021244510013sa.com.stcpay0106STCPAY02116123795286403051111k5204606053036825405100.05502015802SA5919Food 123 brand name60010624350390013sa.com.stcpay021010109944661004true63048BBD");
	xgui_PostMessage(XM_GUIPAINT, 0 , 0);
	while(1){
		if (xgui_GetMessageWithTime(&pMsg, 500) == MESSAGE_ERR_NO_ERR) {

			if (pMsg.MessageId == XM_GUIPAINT) {
// 				if (strlen(mpos_qr_data->data) > 0)
// 				{
// 					showQr(mpos_qr_data->amt, mpos_qr_data->data);
// 				} 
// 				else
// 				{
					standby_pagepaint();
					if (lcd_get_sublcd_probe() == 1)//Whether with a small LCD
					{
						standby_pagepaint2();
					}
//				}
			}
			else if (pMsg.MessageId == XM_KEYPRESS /*&& osl_get_is_m67()==0*/) {//MF67 Shield button function
				argot_keyinput(pMsg.WParam);

				if (pMsg.WParam == KEY_OK || pMsg.WParam == KEY_QUIT)	
				{
// 					if (lcd_get_sublcd_probe() == 1)
// 					{
// 						lcd_set_index(1);
// 					}
					xgui_main_menu_show(MAIN_MENU_PAGE , 0);	// Loop processing menu
// 					if (lcd_get_sublcd_probe() == 1)
// 					{
// 						lcd_set_index(0);
// 					}	

					xgui_PostMessage(XM_GUIPAINT, 0 , 0);
				}
			}
			else{
				xgui_proc_default_msg(&pMsg);
			} 
		}

// 		if (osl_get_is_m67())//only MF67 use serial communication
// 		{
// 			//_mpos_proc();
// 
// 			if (Rf_Check_CardIsExist() == 0)
// 			{
// 				xgui_messagebox_show("Prompt","Find a card","","confirm", 3000 );
// 			}
// 		} 
	
		get_hhmmss_str(time_cur);
		if ( strcmp(time_last,time_cur) != 0 ){
			strcpy(time_last, time_cur );
			xgui_PostMessage(XM_GUIPAINT, 0 , 0);
		}
	}
}



