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


static void tts_volume_page_paint(int value)
{
	char acBuf[32+1] ={0};
	gui_begin_batch_paint();
	gui_clear_dc();

	sprintf(acBuf,"volume:%d",value);
	gui_text_out(0, GUI_LINE_TOP(0),acBuf);
	gui_text_out(0, GUI_LINE_TOP(1),"Up or Down");

	gui_page_op_paint( "Cancel" , "Ok");
	gui_end_batch_paint();
}

void tts_volume_page()
{
	int presskey;
	int iIndex;
	st_gui_message pMsg;

	iIndex = Sys_GetTtsVolume();
	tts_volume_page_paint(iIndex);
	while(1)
	{
		if (gui_get_message(&pMsg, 100) == 0) 
		{

			if (pMsg.message_id == GUI_KEYPRESS) 
			{
				presskey = pMsg.wparam;

				switch(presskey) {
				case GUI_KEY_UP:
					if(iIndex != 9)
					{
						iIndex++;
					}
					
					tts_volume_page_paint(iIndex);
					break;
				case GUI_KEY_DOWN:
					if(iIndex != 0)
					{
						iIndex--;
					}

					tts_volume_page_paint(iIndex);
					break;
				}
				
				if (presskey == GUI_KEY_UP || GUI_KEY_DOWN == presskey)
				{
					Sys_SetTtsVolume(iIndex);
					Play_Voice("TTSTEST");
				}
				else if(presskey == GUI_KEY_QUIT || GUI_KEY_OK == presskey)
				{
					break;
				}
			}
		}
	} 

	return;
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
			backlight_time_page();
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
	}
	return ret;

}