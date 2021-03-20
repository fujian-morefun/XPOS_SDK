#include "app_def.h"
#include "driver/mf_rtc.h"

#define LOGOIMG "data\\logo2.bmp"
#define MAIN_MENU_PAGE	"main"
// #define STR_MENU_MAIN			"Horizon Pay"
// #define STR_MENU_PURCHASE		"Purchase"
// #define STR_MENU_BALANCE			"Balance"
// #define STR_MENU_REVERSAL		"Reversal"
// #define STR_MENU_SETUP			"Setup"

// Define the menu array, the first parameter is the name of the parent menu, 
// the second parameter is the name of the current menu,
// and the second parameter is set when the name is duplicated.
static  st_gui_menu_item_def _menu_def[] = {
	{MAIN_MENU_PAGE ,	"Sale",			""},
	{MAIN_MENU_PAGE ,	"CodePay",		""},
	{MAIN_MENU_PAGE ,	"Version",		""},
	{MAIN_MENU_PAGE ,	"Test",			""},
	{MAIN_MENU_PAGE ,	"Settings",		""},
	{MAIN_MENU_PAGE ,	"Others",		""},

	{"Test" ,	"DevInfo",		""},
	{"Test" ,	"Print",		""},
	{"Test" ,	"ReadCard",		""},
	{"Test" ,	"MallocTest",		""},
	{"Test",	"KeyCheck",		""},
	{"Test",	"Touch",		""},
	{"Test",	"Barcode",		""},
	{"Test",	"Security",		""},
	{"Test",	"Http",		    ""},
	{"Test",	"Https",		""},
	{"Test",	"ShowQr",		""},
	{"Test",	"File",		    ""},
	{"Test",	"ShowBmp",		""},	
    {"Test",    "Led",          ""},
	{"Test",    "uart test",          ""},
	{"Test",	"Wifi Link",    ""},
	{"Test",	"ICC PSAM",    ""},

	{"Settings",	"Net Select",	""},
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
	{"Others",		"View Service",		""},
	{"Others",		"View PRMacqKey",	""},
	{"Others",		"RP SrData Clear",	""},
	{"Others",		"RP SrData DlTest",	""},
};

static int getversions( char *buff)
{
	int i = 0;

	i += sprintf(buff + i, "api:%s\r\n", libapi_version());
	i += sprintf(buff + i, "emv:%s\r\n", EMV_GetVersion());
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


extern int keySoundSet_Show_test();
extern void PowerDownTimeSet_Show();

static int _menu_proc(char *pid)
{
	int ret;
	char buff[20];
	int pos = 0;
	char msg[512];

	if (strcmp(pid , "Sale") == 0){
		upay_consum();
	}
	else if (strcmp(pid , "Version") == 0){
		sprintf(msg , "app:%s\r\n", APP_VER);
		sprintf(msg + strlen(msg), "hardware:%s\r\n", sec_get_hw_ver());
		sprintf(msg + strlen(msg), "fireware:%s\r\n", sec_get_fw_ver());
		getversions(msg + strlen(msg));
		gui_messagebox_show( "Version" , msg , "" , "confirm" , 0);
	}

	else if(strcmp(pid , "MallocTest") == 0){
		unsigned char* a2;
		unsigned char* a3;
		unsigned char* a1 = (unsigned char*) Util_Malloc(1000);
		Util_Free(a1);
		a1 = (unsigned char*) Util_Malloc(10000);
		//Util_Free(a1);
		a2 = (unsigned char*) Util_Malloc(10001);
		//Util_Free(a1);
		//a3 = (unsigned char*) Util_Malloc(10002);
		Util_Free(a1);
		Util_Free(a2);
		//Util_Free(a3);
		gui_messagebox_show( pid,"Success" , "" , "confirm" , 0);
	}
	else if(strcmp(pid,"uart test")==0)
	{
		uart_test_page();
	}
	else if(strcmp("ReadCard",pid)==0){
		card_magtek_track_info stMagtek;
		ret = inputcard_page_showd(pid,&stMagtek,60000);
		if(READ_CARD_RET_MAGNETIC==ret)
			gui_messagebox_show( pid , "Detect Magstripe" , "" , "confirm" , 0);
		else if(READ_CARD_RET_IC==ret)
			gui_messagebox_show( pid , "Detect ICC" , "" , "confirm" , 0);
		else if(READ_CARD_RET_RF==ret)
			gui_messagebox_show( pid , "Detect NFC" , "" , "confirm" , 0);
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
		sdk_driver_magtek();
	}
	else if (strcmp(pid , "Ic") == 0){
		sdk_driver_icc(SLOT_ICC_SOCKET1);
	}
	else if (strcmp(pid , "RF") == 0){
		sdk_driver_rf();
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
	else if(strcmp(pid,"ICC PSAM")==0){
		sdk_driver_icc(SLOT_ICC_SOCKET4);
	}
	else if(strcmp(pid, "KeyCheck")==0){
		char szMac[21]={0};
		int ret =0;
		//sec_mac_proc(SEC_DUKPT_FIELD,0,SEC_MAC_X919_FORMAT,"data1data247584data3484884qwerty",32,szMac,DUKPT_DES_KEY_MAC1);
		ret = check_app_key("\x73\x61\x2a\x03\xfc\x98\xa3\xdd\x75\x81\xd2\x04\xba\x17\x61\xbd\x4c\x79\xfa\xeb");
		if(ret==0)
			gui_messagebox_show( "app key", "check fail!" ,"","Confirm" ,0);
		else if(ret==1)
			gui_messagebox_show( "app key", "check succ" ,"","Confirm" ,0);

		ret = check_app_key("\x06\x8A\x5E\x39\xD0\xF0\xE9\x17\x13\x1A\xBA\x62\xA3\xB2\x3A\xCE\xA9\x40\xE5\x4D");
		if(ret==0)
			gui_messagebox_show( "app key1", "check fail!" ,"","Confirm" ,0);
		else if(ret==1)
			gui_messagebox_show( "app key1", "check succ" ,"","Confirm" ,0);
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
	else if(strcmp(pid , "View PRMacqKey") == 0){
		EMV_ShowRuPayPRMacqKey();
	}
	else if(strcmp(pid , "View Service") == 0){
		EMV_ShowRuPayService();
	}
	else if(strcmp(pid , "RP SrData DlTest") == 0)
	{
		init_service_prmacqkey(1);
	}
	else if(strcmp(pid , "RP SrData Clear") == 0)
	{
		clear_service_prmacqkey();
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

	gui_begin_batch_paint();
	gui_set_win_rc();
	gui_clear_dc();

	//xgui_SetTitle("Pay Demo");
	{
		int logowidth;
		int logoheight;
		int logoleft;
		int logotop;
		int logocolor;

		char * pbmp;	
                
        logoleft = 30;
		logotop = GUI_LINE_TOP(1);

		pbmp = gui_load_bmp_ex(LOGOIMG , &logowidth , &logoheight, &logocolor);

		if (pbmp != 0){
			gui_out_bits_ex(logoleft, logotop, pbmp , logowidth , logoheight , 0 , logocolor);
			Util_Free(pbmp);
		}
	}

	xgui_TextOut_Line_Center("welcome", GUI_LINE_TOP(0));
	//gui_text_out_ex(0, GUI_LINE_TOP(1), "\xD9\x84\xD8\xA7\xDA\xAF\x20\xD8\xA2\xD9\x86\x20\xD8\xA7\xD8\xB3\xD8\xAA");
	//gui_textout_line_right("\xD9\x84\xD8\xA7\xDA\xAF", GUI_LINE_TOP(2));
	get_yyyymmdd_str(data);	
	//sprintf(data, "%s",/* APP_VER,*/Sys_GetAppVer());
	gui_textout_line_center(data, GUI_LINE_TOP(3));
	get_hhmmss_str(data);	
	//sprintf(data, "%s",/* APP_VER,*/mfs_get_fw_ver());
	gui_textout_line_center(data, GUI_LINE_TOP(4));
	//sprintf(data, "%d",/* APP_VER,*/Sys_GetDeviceType());
	sprintf(data, "%s", APP_VER);
	gui_textout_line_center(data, GUI_LINE_TOP(5));

	gui_end_batch_paint();
}


void sdk_main_page()
{
	st_gui_message pMsg;
	static int xgui_init_flag = 0;
	char time_cur[20];
	char time_last[20];
	int i;
	int ret = -1;

	get_hhmmss_str(time_last);

	sdk_timer_init();

	ret = lcd_get_index();
	lcd_set_index(1);
	ret = lcd_get_index();
	lcd_set_index(0);
	ret = lcd_get_index();

	if(xgui_init_flag == 0){
		xgui_init_flag = 1;
		gui_main_menu_func_add((void *)_menu_proc);		// Registration menu callback processing
		for(i = 0; i < GUI_MENU_ITEM_COUNT(_menu_def); i ++){	// Add menu items cyclically
			gui_main_menu_item_add(_menu_def + i);	
		}
	}
	gui_post_message(GUI_GUIPAINT, 0 , 0);
	while(1){
		if (gui_get_message(&pMsg, 300) == 0) {

			if (pMsg.message_id == GUI_GUIPAINT) {
				standby_pagepaint();
			}
			else if (pMsg.message_id == GUI_KEYPRESS) {
				argot_keyinput(pMsg.wparam);

				if (pMsg.wparam == GUI_KEY_OK || pMsg.wparam == GUI_KEY_QUIT)	
				{
					gui_main_menu_show(MAIN_MENU_PAGE , 0);	

					gui_post_message(GUI_GUIPAINT, 0 , 0);
				}
			}
			else{
				gui_proc_default_msg(&pMsg);
			}
		}	

		get_hhmmss_str(time_cur);
		if ( strcmp(time_last,time_cur) != 0 ){
			strcpy(time_last, time_cur );
			gui_post_message(GUI_GUIPAINT, 0 , 0);
		}
	}
}