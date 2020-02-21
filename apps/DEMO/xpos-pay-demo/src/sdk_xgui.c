#include "sdk_xgui.h"
#include "xGui/inc/mainmenu.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/messagedatastruct.h"
#include "xGui/inc/message.h"
#include "xGui/inc/messagebox.h"
#include "xGui/inc/xgui_key.h"
#include "xGui/inc/pageproc.h"
#include "xGui/inc/xgui_bmp.h"
#include "sdk_http.h"
#include "sdk_showqr.h"
#include "sdk_file.h"
#include "sdk_img.h"
#include "driver/mf_rtc.h"
#include "pub/common/misc/inc/mfmalloc.h"
#include "libapi_xpos/inc/libapi_gui.h"
#include "sdk_driver.h"
#include "libapi_xpos/inc/libapi_emv.h"

#define LOGOIMG "data\\logo2.bmp"

#include "sdk_timer.h"

#define MAIN_MENU_PAGE	"main"
// #define STR_MENU_MAIN			"Horizon Pay"
// #define STR_MENU_PURCHASE		"Purchase"
// #define STR_MENU_BALANCE			"Balance"
// #define STR_MENU_REVERSAL		"Reversal"
// #define STR_MENU_SETUP			"Setup"

enum{
	DRIVER_TYPE_MAG,
	DRIVER_TYPE_ICC,
	DRIVER_TYPE_RF,
};


// Define the menu array, the first parameter is the name of the parent menu, 
// the second parameter is the name of the current menu,
// and the second parameter is set when the name is duplicated.
static  const st_main_menu_item_def _menu_def[] = {
	{MAIN_MENU_PAGE ,	"Sale",			""},
	{MAIN_MENU_PAGE ,	"CodePay",		""},
	{MAIN_MENU_PAGE ,	"Version",		""},
	{MAIN_MENU_PAGE ,	"Test",			""},
	{MAIN_MENU_PAGE ,	"Settings",		""},
	{MAIN_MENU_PAGE ,	"Others",		""},

	{"Test" ,	"DevInfo",		""},
	{"Test" ,	"Print",		""},
	//{"Test",	"magcard",		""},
	//{"Test",	"Ic",			""},
	//{"Test",	"RF",			""},
	{"Test",	"M1",			""},
//	{"Test",	"Touch",		""},
	{"Test",	"Barcode",		""},
	{"Test",	"Security",		""},
	{"Test",	"Http",		    ""},
	{"Test",	"Https",		""},
	{"Test",	"ShowQr",		""},
	{"Test",	"File",		    ""},
	{"Test",	"ShowBmp",		""},	
    {"Test",    "Led",          ""},
//	{"Test",    "Input",        ""},
//	{"Test",	"Wifi Link",    ""},

	{"Settings",	"Wifi Set",	""},
	{"Settings",	"keySound",		""},
	{"Settings",	"lcdLight",		""},
	{"Settings",	"powerTime",    ""},	
	{"Settings",	"TimeSet",		""},	
	{"Settings",	"Open Log",		""},	
	{"Settings",	"Set Dukpt Key",		""},	
	{"Others",		"View AID",		""},
	{"Others",		"View CAPK",	""},
	{"Others",		"View emv",	""},
};

/*static  const st_main_menu_item_def _menu_def[] = 
{
	{STR_MENU_MAIN ,	STR_MENU_PURCHASE,			""},
	{STR_MENU_MAIN ,	STR_MENU_BALANCE,			""},
	{STR_MENU_MAIN ,	STR_MENU_REVERSAL,			""},
	{STR_MENU_MAIN ,	"Test",			""},
	{STR_MENU_MAIN ,	STR_MENU_SETUP,			""},

	{"Test" ,	"DevInfo",		""},
	{"Test" ,	"Print",		""},
	{"Test",	"magcard",		""},
	{"Test",	"Ic",			""},
	{"Test",	"RF",			""},
	//{"Test",	"Touch",		""},
	{"Test",	"Barcode",		""},
	{"Test",	"Security",		""},
	{"Test",	"Http",		""},
	{"Test",	"ShowQr",		""},
	{"Test",	"File",		""},
	{"Test",	"ShowBmp",		""},


	{STR_MENU_SETUP,	"Wifi Menu",	""},
	{STR_MENU_SETUP,	"keySound",		""},
	{STR_MENU_SETUP,	"lcdLight",		""},
	{STR_MENU_SETUP,	"powerTime",	""},
	{STR_MENU_SETUP,	"TimeSet",		""},
	
};*/


static int getversions( char *buff)
{
	int i = 0;

	i += sprintf(buff + i, "api:%s\r\n", libapi_version());
	i += sprintf(buff + i, "apppub:%s\r\n", apppub_version());
	i += sprintf(buff + i, "atc:%s\r\n", atc_version());
	i += sprintf(buff + i, "json:%s\r\n", json_version());
	i += sprintf(buff + i, "net:%s\r\n", net_version());
	i += sprintf(buff + i, "power:%s\r\n", power_version());
	i += sprintf(buff + i, "producttest:%s\r\n", producttest_version());
	i += sprintf(buff + i, "pub:%s\r\n", pub_version());
	i += sprintf(buff + i, "switchcheck:%s\r\n", switchcheck_version());
	i += sprintf(buff + i, "tms:%s\r\n", tms_version());
	i += sprintf(buff + i, "wifi:%s\r\n", wifi_version());
	i += sprintf(buff + i, "xgui:%s\r\n", xgui_version());

	return i;
}

// The menu callback function, as long as all the menu operations of this function are registered, 
// this function will be called, and the selected menu name will be returned. 
// It is mainly determined in this function that the response menu name is processed differently.
static int _menu_proc(char *pid)
{
	int ret;
	char buff[20];
	int pos = 0;
	char msg[512];

	if (strcmp(pid , "Sale") == 0){
		upay_consum();
		//tt_upay_consum();
	}
	else if (strcmp(pid , "Version") == 0){
		sprintf(msg , "app:%s\r\n", APP_VER);
		sprintf(msg + strlen(msg), "hardware:%s\r\n", sec_get_hw_ver());
		sprintf(msg + strlen(msg), "fireware:%s\r\n", sec_get_fw_ver());
		getversions(msg + strlen(msg));
		
		gui_messagebox_show( "Version" , msg , "" , "confirm" , 0);
	}
	else if (strcmp(pid , "CodePay") == 0){	
		upay_barscan();
	}
	else if (strcmp(pid , "DevInfo") == 0){
		test_devinfo();
	}
	else if (strcmp(pid , "Print") == 0)	{
		sdk_print();
	}
	else if (strcmp(pid , "magcard") == 0){
		//test_magcard();
	}
	else if (strcmp(pid , "Ic") == 0){
		//test_IC();
	}
	else if (strcmp(pid , "RF") == 0){
		//test_rf();
	}
	else if (strcmp(pid , "M1") == 0){
		test_m1();
	}
	else if (strcmp(pid , "Touch") == 0){
		test_touch();
	}
	else if (strcmp(pid , "Barcode") == 0){
		sdk_driver_barcode();
	}
	else if (strcmp(pid , "keySound") == 0)	{
		keySoundSet_Show_test();
	}
	else if (strcmp(pid , "lcdLight") == 0)	{
		lcdLightSet_Show();
	}
	else if (strcmp(pid , "powerTime") == 0)	{
		PowerDownTimeSet_Show();
	}
	else if (strcmp(pid , "TimeSet") == 0)	{
		timeTest();
	}
	else if (strcmp(pid , "Security") == 0)	{
		securityTest();
	}
	else if (strcmp(pid , "Http") == 0)	{
		sdk_http_test();
	}
	else if (strcmp(pid , "Https") == 0)	{
		sdk_https_test();
	}
	else if (strcmp(pid , "ShowQr") == 0){
		showQrTest();
	}
	else if (strcmp(pid , "File") == 0){
		fileTest();
	}
	else if (strcmp(pid , "ShowBmp") == 0){
		showbmptest();
	}
    else if(strcmp(pid, "Led") == 0){
        sdk_driver_led();
    }
	else if (strcmp(pid, "Open Log") == 0)
	{
		LogOutSet_Show();
	}
	else if (strcmp(pid, "Wifi Set") == 0)
	{
		xgui_main_menu_show("Wifi Menu", 0);
	}	
	else if (strcmp(pid, "Wifi Link") == 0)
	{
		wifi_link_test();
	}
// 	else if (strcmp(pid, "Input") == 0)
// 	{
// 		input_test();
// 	}
	else if (strcmp(pid, "Set Dukpt Key") == 0)
	{
		SetDukptKey();
	}
	else if (strcmp(pid, "View AID") == 0)
	{
		EMV_ShowAID_Prm();
	}
	else if (strcmp(pid, "View CAPK") == 0)
	{
		EMV_ShowCAPK_Prm();
	}
	else if (strcmp(pid , "View emv") == 0){
		sprintf(msg + strlen(msg), "%s\r\n", EMV_GetVersion());
		gui_messagebox_show( "View emv" , msg , "" , "confirm" , 0);
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

	xgui_BeginBatchPaint();
	XGUI_SET_WIN_RC;
	xgui_ClearDC();

	//xgui_SetTitle("Pay Demo");

	{
		int logowidth;
		int logoheight;
		int logoleft;
		int logotop;
		int logocolor;

		char * pbmp;	
                
        logoleft = 30;
		logotop = XGUI_LINE_TOP_1;

		pbmp = xgui_load_bmp_all(LOGOIMG , &logowidth , &logoheight, &logocolor);

		if (pbmp != 0){
			xgui_out_bits_bmp(logoleft, logotop, pbmp , logowidth , logoheight , 0 , logocolor);
			FREE(pbmp);
		}
	}

	get_yyyymmdd_str(data);	
	xgui_TextOut_Line_Center(data, XGUI_LINE_TOP_3);
	get_hhmmss_str(data);	
	xgui_TextOut_Line_Center(data, XGUI_LINE_TOP_4);
	sprintf(data, "%s", APP_VER);
	xgui_TextOut_Line_Center(data, XGUI_LINE_TOP_5);

	xgui_EndBatchPaint();
}


void sdk_main_page()
{
	MESSAGE pMsg;
	static int xgui_init_flag = 0;
	char time_cur[20];
	char time_last[20];
	int i;
	int ret = -1;

	get_hhmmss_str(time_last);

	sdk_timer_init();
#ifdef WIN32
	//upay_consum();
	//upay_barscan();
	//test_devinfo();
	//test_touch();
	//sdk_https_test();
#endif

	ret = lcd_get_index();
	lcd_set_index(1);
	ret = lcd_get_index();
	lcd_set_index(0);
	ret = lcd_get_index();

	if(xgui_init_flag == 0){
		xgui_init_flag = 1;
		xgui_main_menu_func_add((void *)_menu_proc);		// Registration menu callback processing
		for(i = 0; i < MENU_ITEM_COUNT(_menu_def); i ++){	// Add menu items cyclically
			xgui_main_menu_item_add(_menu_def + i);	
		}
	}
	xgui_PostMessage(XM_GUIPAINT, 0 , 0);
	while(1){
		if (xgui_GetMessageWithTime(&pMsg, 300) == MESSAGE_ERR_NO_ERR) {

			if (pMsg.MessageId == XM_GUIPAINT) {
				standby_pagepaint();
			}
			else if (pMsg.MessageId == XM_KEYPRESS) {
				argot_keyinput(pMsg.WParam);

				if (pMsg.WParam == KEY_OK || pMsg.WParam == KEY_QUIT)	
				{
					xgui_main_menu_show(MAIN_MENU_PAGE , 0);	// 循环处理菜单

					xgui_PostMessage(XM_GUIPAINT, 0 , 0);
				}
			}
			else{
				xgui_proc_default_msg(&pMsg);
			}
		}	

		get_hhmmss_str(time_cur);
		if ( strcmp(time_last,time_cur) != 0 ){
			strcpy(time_last, time_cur );
			xgui_PostMessage(XM_GUIPAINT, 0 , 0);
		}
	}
}


