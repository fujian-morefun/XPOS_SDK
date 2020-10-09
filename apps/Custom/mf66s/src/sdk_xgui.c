#include "sdk_xgui.h"
#include "sdk_settings.h"

#include "driver/mf_rtc.h"
#include "libapi_xpos/inc/libapi_gui.h"
#include "libapi_xpos/inc/libapi_system.h"
#include "bmpdef.h"

#define LOGO_BMP "data\\logo2.bmp"
#define LOGO_PNG "data\\logo2.png"



int main_menu()
{
	int ret = 0;
	char *items[]={
		"Amount",    
		"Status Page",    
		"Settings",
		"Test"
	};

	int itemcount =  sizeof(items)/ sizeof(items[0]);
	while ( ret >=0 && ret < itemcount  ){
		ret = gui_select_page_ex( "main" , items,itemcount , 60000,ret );
		if(ret==0){
			enterAmount();
		}
		else if(ret ==1){
			status_page();
		}
		else if(ret ==2){
			settings_menu();
		}	
		else if(ret ==3){
			test_menu();
		}	
		
	}
	return ret;

}



void get_hhmmss_str(char *buff)
{
	struct rtc_time date_time;
	mf_rtc_get_time(&date_time);
	sprintf(buff, "%02d:%02d:%02d", date_time.tm_hour, date_time.tm_min, date_time.tm_sec);
}
void get_yyyymmdd_str(char *buff)
{
	struct rtc_time dt;
	mf_rtc_get_time(&dt);
	sprintf(buff , "%04d-%02d-%02d", dt.tm_year, dt.tm_mon, dt.tm_mday);
}


void main_page_lcd1_paint()
{
	char data[32]={0};
	int logowidth;
	int logoheight;
	int logoleft;
	int logotop;
	int logocolor;
	int power_state = Sys_get_power();
	int atc_state = comm_atc_signal();
	int wifi_state = comm_wifi_get_signal();

	gui_begin_batch_paint();
	gui_clear_dc();

	logotop = 2;

	logoleft = 3;
	gui_out_bits(logoleft, logotop, (unsigned char *)m_atc_signal_buff_128[atc_state] , ATC_SIGNAL_BMP_WIDTH_128 , ATC_SIGNAL_BMP_HEIGHT_128 , 0);

	logoleft = 25;
	gui_out_bits(logoleft, logotop, (unsigned char *)m_wifi_signal_buff_128[wifi_state] , WIFI_SIGNAL_BMP_WIDTH_128 , WIFI_SIGNAL_BMP_HEIGHT_128 , 0);

	logoleft = 108;
	gui_out_bits(logoleft, logotop, (unsigned char *)m_batter_buff_128[power_state] , BATTER_BMP_WIDTH_128 , BATTER_BMP_HEIGHT_128 , 0);

	get_hhmmss_str(data);	
	gui_textout_line_center(data , 18);

	gui_end_batch_paint();
}



void main_page_lcd0_paint()
{
	char data[32]={0};
	int logoleft;
	int logotop;

	static char * pbmp = (char *) -1;	
	static int logowidth;
	static int logoheight;
	static int logocolor;
	
	unsigned int tick1 = 0;

	lcd_set_index(0);
	
	gui_begin_batch_paint();
	gui_clear_dc();

	tick1 = osl_GetTick();

	if(pbmp == (char *)-1){
		pbmp = (char *)gui_load_bmp_ex(LOGO_BMP , &logowidth , &logoheight, &logocolor);

		//pbmp = (char *)png_load_bmp(LOGO_PNG , &logowidth , &logoheight, &logocolor);
	}
	
	SYS_TRACE("tick1:%d,%x\r\n", osl_GetTick()- tick1, pbmp);



	logoleft = (gui_get_width() - logowidth) / 2;
	logotop = 0;

	if (pbmp > 0){
		gui_out_bits_ex(logoleft, logotop, pbmp , logowidth , logoheight, 1, logocolor);
		//gui_bmp_free(pbmp);
	}
		
	gui_set_text_style(1);
	get_yyyymmdd_str(data);	
	gui_text_out(300, 50, data);
	get_hhmmss_str(data);	
	gui_text_out(300, 80, data) ;
	gui_set_text_style(0);
	
	gui_end_batch_paint();
	lcd_set_index(1);
	

}


void sdk_main_page()
{
	st_gui_message pMsg;
	char time_cur[20];
	char time_last[20];
	int keycode;
#ifdef WIN32
#endif
	//status_page();
	lcd_set_index(0);
	xgui_set_lcd_mode(1);
	lcd_set_index(1);
	xgui_set_lcd_mode(1);
	
	gui_post_message(GUI_GUIPAINT, 0 , 0);
	while(1){

		get_hhmmss_str(time_cur);
		if ( strcmp(time_last,time_cur) != 0 ){
			strcpy(time_last, time_cur );
			xgui_PostMessage(GUI_GUIPAINT, 0 , 0);
		}


		if (gui_get_message(&pMsg, 300) == 0) {
			if (pMsg.message_id == GUI_GUIPAINT) {
				
				main_page_lcd0_paint();
				main_page_lcd1_paint();
			}
			else if (pMsg.message_id == GUI_KEYPRESS) {
				keycode = pMsg.wparam;
				argot_keyinput(pMsg.wparam);
				if (keycode == GUI_KEY_OK || keycode == GUI_KEY_QUIT){
					main_menu();
					gui_post_message(GUI_GUIPAINT, 0 , 0);
				}
#ifdef WIN32
				else if(GUI_KEY_0==keycode)
#else
				else if(GUI_KEY_MC==keycode)
#endif
				{
					set_malloc_log(0);
					ap2_mbedtls_init(0,0);
					mqtt_proc_init();			//MQTT APP initialization
				}
				else if(keycode >= GUI_KEY_0  && keycode <= GUI_KEY_9){
					sdk_pay(keycode);
				}
			}
			else{
				mqtt_proc_default_msg( &pMsg);
				gui_proc_default_msg(&pMsg);
			}
		}

	}
}


