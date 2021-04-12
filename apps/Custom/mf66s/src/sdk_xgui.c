#include "sdk_xgui.h"
#include "sdk_settings.h"

#include "driver/mf_rtc.h"
#include "libapi_xpos/inc/libapi_gui.h"
#include "libapi_xpos/inc/libapi_system.h"
#include "bmpdef.h"
#include "driver/mf_supply_power.h"

#define LOGO_RF_BMP	"data\\rf.bmp"
#define LOGO_BMP "data\\logo2.bmp"
#define LOGO_PNG "data\\logo2.png"  


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
static int colordef_3bit[] = {
	0x00ff00,	// 0
	0x0000ff,
	0xff0000,
	0xffffff,
	0x000000,
};

#define SFLASH_BLOCK_SIZE				4096
#define FLASH_CA_ADDR					(0x1097000)
#define FLASH_KEY_ADDR					(FLASH_CA_ADDR+2048)

#define FLASH_TOKEN_ADDR				(0x1097000+4096)
#define FLASH_SEC_ADDR					(FLASH_TOKEN_ADDR+256)

void test_flash(void)
{
	char *sCaBuff;
	char*skeyBuff;
	char sWriteBuff[SFLASH_BLOCK_SIZE];
	mf_onchip_flash_erase(FLASH_CA_ADDR,SFLASH_BLOCK_SIZE);
	memcpy(sWriteBuff,sCaBuff,2048);
	memcpy(sWriteBuff+2048,skeyBuff,2048);
	mf_onchip_flash_write(sWriteBuff, FLASH_CA_ADDR , SFLASH_BLOCK_SIZE);

	mf_onchip_flash_read(sCaBuff,FLASH_CA_ADDR,2048);
	mf_onchip_flash_read(skeyBuff,FLASH_KEY_ADDR,2048);
}
void paytm_app_readflash(char * pdata, int nblock, int size)
{
	int addr = 0x1097000 + SFLASH_BLOCK_SIZE * nblock;
	if(nblock<0 || nblock>3)
		return;
	mf_onchip_flash_read(pdata, addr , size);
}
void paytm_app_writeflash(char * pdata, int nblock, int size)
{
	int addr =  0x1097000 + SFLASH_BLOCK_SIZE * nblock;
	if(nblock<0 || nblock>3)
		return;
	mf_onchip_flash_erase(addr , SFLASH_BLOCK_SIZE);
	mf_onchip_flash_write(pdata, addr , size);
}
extern unsigned int FMD_GetFalFlashSize(void);
int main_menu()
{
	int ret = 0;
	char *items[]={
		"CodePay",
		"ShowCode",
		"Sale",		
		"Test",
        "Version",		
		"others",
		"Settings",
	};

	int itemcount =  sizeof(items)/ sizeof(items[0]);
	while ( ret >=0 && ret < itemcount  ){
		ret = gui_select_page_ex( "main" , items,itemcount , 60000,ret );
		if(ret==0){
			upay_barscan();
		}
		else if(ret == 1)
		{
			sdk_showQr();
		}
		else if(ret == 2){
			upay_consum();
		}	
		else if(ret == 3){
			test_menu();
		}	
		else if(ret == 4){
			int i=0;
			int nret =0;
			char msg[512] = {0};

			Sys_lcd_set_index(0);
			getversions(msg + strlen(msg));
			nret =gui_messagebox_show( "Version" , msg , "" , "confirm" , 0);
			main_page_lcd0_paint();
			Sys_lcd_set_index(1);
		}
		else if(ret == 5)
		{
			others_menu();
		}
		else if(ret == 6)
		{			
			settings_menu();
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

	SYS_TRACE("power_state = %d\r\n",power_state);

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

void rf_icon_lcd0_paint()
{
	char data[32]={0};
	int logoleft;
	int logotop;

	static char * pbmp = (char *) -1;	
	static int logowidth;
	static int logoheight;
	static int logocolor;	
	unsigned int tick1 = 0;

	Sys_lcd_set_index(0);	
	gui_begin_batch_paint();
	gui_clear_dc();

	if(pbmp == (char *)-1){		
		pbmp = (char *)gui_load_bmp(LOGO_RF_BMP , &logowidth , &logoheight);

	}	

	if (pbmp > 0){
		logoleft = (gui_get_width() - logowidth) / 2;
		logotop = (gui_get_height() - GUI_LINE_TOP(2)  - logoheight) / 2;
		gui_out_bits(logoleft, logotop+30,pbmp , logowidth , logoheight, 1);
	}

	gui_end_batch_paint();
	Sys_lcd_set_index(1);	
}

void device_init_tip()
{
	Sys_lcd_set_index(0);	
	{
		gui_begin_batch_paint();
		gui_clear_dc();
		gui_set_text_style(1);
		gui_textout_line_center("init data ...", GUI_LINE_TOP(4));
		gui_end_batch_paint();
	}
	
	Sys_lcd_set_index(1);
	{
		gui_begin_batch_paint();
		gui_clear_dc();
		gui_set_text_style(1);
		gui_textout_line_center("init data...", GUI_LINE_TOP(1));
		gui_end_batch_paint();
	}

	return;
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

	Sys_lcd_set_index(0);	
	gui_begin_batch_paint();
	gui_clear_dc();


	if(pbmp == (char *)-1){
		pbmp = (char *)gui_load_bmp_ex(LOGO_BMP , &logowidth , &logoheight, &logocolor);		
	}
	
	logoleft = (gui_get_width() - logowidth) / 2;
	logotop = 0;

	if (pbmp > 0){
		gui_out_bits_ex(logoleft, logotop, pbmp , logowidth , logoheight, 1, logocolor);
	}
		
	gui_set_text_style(1);
	memset(data,0x00,sizeof(data));
	sprintf(data,"AppVer: %s",Sys_GetAppVer());
	gui_textout_line_center(data, GUI_LINE_TOP(3));

	get_yyyymmdd_str(data);	
	gui_textout_line_center(data, GUI_LINE_TOP(1));
	get_hhmmss_str(data);	
	gui_textout_line_center(data, GUI_LINE_TOP(2)) ;
	gui_set_text_style(0);
	
	gui_end_batch_paint();
	Sys_lcd_set_index(1);
	

}


void sdk_main_page()
{
	st_gui_message pMsg;
	char time_cur[20];
	char time_last[20];
	int keycode;

	//status_page();
	Sys_lcd_set_index(0);
	gui_set_full_screen(1);
	Sys_lcd_set_index(1);
	gui_set_full_screen(1);
	
	gui_post_message(GUI_GUIPAINT, 0 , 0);
	while(1){

		get_hhmmss_str(time_cur);
		if ( strcmp(time_last,time_cur) != 0 ){
			strcpy(time_last, time_cur );
			gui_post_message(GUI_GUIPAINT, 0 , 0);
		}


		if (gui_get_message(&pMsg, 300) == 0) {
			if (pMsg.message_id == GUI_GUIPAINT) {
				
				main_page_lcd0_paint();
				main_page_lcd1_paint();
			}
			else if (pMsg.message_id == GUI_KEYPRESS) {
				keycode = pMsg.wparam;
				argot_keyinput(pMsg.wparam);
				if (keycode == GUI_KEY_OK){
					main_menu();
					gui_post_message(GUI_GUIPAINT, 0 , 0);
				}

				else if(GUI_KEY_MC==keycode)
				{
					set_malloc_log(0);
					ap2_mbedtls_init(0,0);
					mqtt_proc_init();			//MQTT APP initialization
				}
				else if(keycode >= GUI_KEY_0  && keycode <= GUI_KEY_9){
					//sdk_pay(keycode);
				}
			}
			else{
				mqtt_proc_default_msg( &pMsg);
				gui_proc_default_msg(&pMsg);
			}
		}

	}
}


