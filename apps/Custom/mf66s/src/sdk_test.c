#include "sdk_test.h"
#include "sdk_tts.h"
#include "sdk_http.h"
#include "sdk_file.h"
#include "sdk_security.h"

int test_menu()
{
	int ret = 0;
	char *items[]={
		"tts test",
		"file test",
		"http test",
		"https test",
		"Mksk test",
		"Dukpt test",


	};

	int itemcount =  sizeof(items)/ sizeof(items[0]);
	while ( ret >=0 && ret < itemcount  ){
		ret = gui_select_page_ex( "test" , items,itemcount , 60000, ret );
		gui_lcd_set_index(0);
		if(ret == 0){
			sdk_tts_test();
		}
		else if(ret == 1){
			fileTest();
		}
		else if(ret == 2){
			
			sdk_http_test();
		}
		else if(ret == 3){
			sdk_https_test();
		}
		else if(ret == 4)
		{
			mkskTest();
		}
		else if(ret == 5)
		{
			dukptTest();
		}

		gui_lcd_set_index(1);
		main_page_lcd0_paint();
		
	}
	return ret;

}

int others_menu()
{
	int ret = 0;
	char *items[]={
		"View AID",
		"View CAPK",
		"View emv",
	};

	int itemcount =  sizeof(items)/ sizeof(items[0]);
	while ( ret >=0 && ret < itemcount  ){
		ret = gui_select_page_ex( "others" , items,itemcount , 60000, ret );
		gui_lcd_set_index(0);
		if(ret == 0){
			EMV_ShowAID_Prm();
		}
		else if(ret == 1){
			EMV_ShowCAPK_Prm();
		}
		else if(ret == 2){
			char msg[512] ={0};
			sprintf(msg + strlen(msg), "%s\r\n", EMV_GetVersion());
			gui_messagebox_show( "View emv" , msg , "" , "confirm" , 0);
		}

		gui_lcd_set_index(1);
		main_page_lcd0_paint();

	}
	return ret;

}