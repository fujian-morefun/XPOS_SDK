#include "sdk_settings.h"
#include "libapi_xpos/inc/libapi_gui.h"
#include "libapi_xpos/inc/libapi_system.h"
#include "page/dateTimeInput_page.h"

#define LIGHT_MAX	99999999

// Key tone settings
static void key_sound_page()
{
	char *items[]={"close", "open"};
	int itemcount =  sizeof(items)/ sizeof(items[0]);
	int ret;
	int def = Sys_GetKeySound();  //get the current value
	
	ret = gui_select_page_ex( "key sound" , items,itemcount , 60000, def);
	if(ret >=0){
		Sys_SetKeySound(ret);	// set the current value
	}

}


static void tts_volume_page()
{
	char *items[]={"volume 0", "volume 1", "volume 2" , "volume 3" , "volume 4",
	               "volume 5", "volume 6", "volume 7" , "volume 8" , "volume 9",};
	int itemcount =  sizeof(items)/ sizeof(items[0]);
	int ret;
	int def = Sys_GetTtsVolume();  //get the current value
	char str[64]={0};

	ret = gui_select_page_ex( "tts volume" , items,itemcount , 60000, def);
	if(ret >=0){
		Sys_SetTtsVolume(ret);	// set the current value
		sprintf(str, "volume %d", ret);
		Play_Voice(str);
	}

}


static void tts_speed_page()
{
	char *items[]={"speed 0", "speed 1", "speed 2" , "speed 3" , "speed 4",};
	int itemcount =  sizeof(items)/ sizeof(items[0]);
	int ret;
	static int def = 0;
	char str[64]={0};

	ret = gui_select_page_ex( "tts speed" , items,itemcount , 60000, def);
	if(ret >=0){
		def = ret;
		//Sys_SetTtsSpeed(ret);	// set the current value
		sprintf(str, "speed %d", ret);
		Play_Voice(str);
	}
}




static int power_time_set_page(int nLightTime , char * szMsg)
{
	int presskey;
	char * items[6] = {"30 second", "1 minute", "3 minute", "10 minute", "30 minute", "disable"};
	int time[6] = {30, 60, 3*60, 10*60, 30*60, LIGHT_MAX};
	int nCurIndex = 0;
	int nTotalCount = sizeof(time) / sizeof(int);
	int i;
	int ret;

	items[5] = szMsg;
	for (i = 0; i < nTotalCount; ++ i)	{
		if (nLightTime == time[i])		{
			nCurIndex = i;
			break;
		}
	}

	ret = ap_select_page_ex("" , items, 6, 0 , nCurIndex);
	if(ret >= 0){
		nLightTime= time[ret];
	}
	else{
		nLightTime = -1;
	}

	return nLightTime;
}





static void powerdown_time_page()
{
	int nLightTime = Sys_GetPowerDownTime();
	int nRet = 0;

	nRet = power_time_set_page(nLightTime , "Disable");
	if(nRet != -1){
		Sys_SetPowerDownTime(nRet);
	}
}


static void backlight_time_page()
{
	int nLightTime = Sys_GetBackLightTime();
	int nRet=0;
	nRet = power_time_set_page(nLightTime , "Always");

	if(nRet != -1){
		Sys_SetBackLightTime(nRet);
	}
}


int settings_menu()
{
	int ret = 0;
	char *items[]={
		"net select",
		"wifi Set",
		"key sound",	
		"back light",		
		"power time",	
		"time set",		
		"tts volume",
		"tts speed",
	};
	int itemcount =  sizeof(items)/ sizeof(items[0]);
	while ( ret >=0 && ret < itemcount  ){
		ret = gui_select_page_ex( "Settings" , items,itemcount , 60000,ret );
		if(ret == 0){
			gui_main_menu_show("Net Select", 60000);
		}
		else if(ret == 1){
			gui_main_menu_show("Wifi Menu", 60000);
		}
		else if(ret == 2){
			key_sound_page();
		}
		else if(ret == 3){
			powerdown_time_page();
		}
		else if(ret == 4){
			powerdown_time_page();
		}
		else if(ret == 5){
			time_set_page();
		}
		else if(ret == 6){
			tts_volume_page();
		}
		else if(ret == 7){
			tts_speed_page();
		}
	}
	return ret;

}