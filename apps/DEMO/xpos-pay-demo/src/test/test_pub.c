#include "../app_def.h"
#include "test_pub.h"
#include "driver\mf_supply_power.h"
#include "driver\mf_magtek.h"
#include "AppPub\upaypage\ap_sign_page.h"
#include "driver\mf_icc.h"


int test_devinfo( void )
{
	int index = 0;
	char szNum[64];
	char pBuf[512];

	battery_attr_t batterAttr;
	int ret = mf_power_battery_attr(&batterAttr);


	index += sprintf(pBuf + index, "voltage:%0.2fv\n", batterAttr.voltage/1000.00);
	index += sprintf(pBuf + index, "%s:", mf_power_ac_online() == 1 ? "Electricity" : "Battery");
	switch(batterAttr.status)
	{
	case POWER_SUPPLY_STATUS_CHARGING:
		index += sprintf(pBuf + index, "%s\n", "Charging");
		break;
	case POWER_SUPPLY_STATUS_DISCHARGING:
		index += sprintf(pBuf + index, "%s\n", "Discharge");
		break;
	case POWER_SUPPLY_STATUS_NOT_CHARGING:
		index += sprintf(pBuf + index, "%s\n", "No Charge");
		break;
	case POWER_SUPPLY_STATUS_FULL:
		index += sprintf(pBuf + index, "%s\n", "Full");
		break;
	default:
		index += sprintf(pBuf + index, "%s\n", "Unknown");
		break;
	}

	index += sprintf(pBuf + index, "Signal:%d\n",atc_csq());
	if(atc_cpin() > 0){
		index += sprintf(pBuf + index, "SIM:Normal\n");
	}
	else{
		index += sprintf(pBuf + index, "SIM:Abnormal\n");
	}


	index += sprintf(pBuf+index,"Sys:%s\r\n",Sys_getDeviceVision());
	//index += sprintf(pBuf+index,"App:%s\r\n",osl_getAppVision());
	index += sprintf(pBuf+index,"UBOOT:%s\r\n",mf_boot_ver());
	index += sprintf(pBuf+index,"driver:%s\r\n",mf_hal_ver());
	index += sprintf(pBuf+index,"FATFS:%s\r\n",mf_fatfs_ver());
	index += sprintf(pBuf+index,"FAL:%s\r\n",mf_fal_ver());
	index += sprintf(pBuf+index,"hardwware:%d\r\n",mf_hardware_ver());

	Sys_GetTermSn(szNum);
	index += sprintf(pBuf+index,"SN:%s\r\n", szNum );

	Sys_get_psn(szNum);
	index += sprintf(pBuf+index,"PSN:%s\r\n", szNum );


	index += sprintf(pBuf+index,"model_type:%s\r\n",(Sys_model_type() == UCOMM_GPRS) ? "WIRELESS" : "WIFI" );

	if(Sys_model_type() == UCOMM_GPRS){
		index += sprintf(pBuf+index,"model:%s\r\n",atc_model_ver());
		index += sprintf(pBuf+index,"IMEI:%s\r\n",atc_imei());
		index += sprintf(pBuf+index,"IMSI:%s\r\n",atc_imsi());


	}
	else if(Sys_model_type() == UCOMM_WIFI){
		index += sprintf(pBuf+index,"WIFI:%s\r\n",wifi_model_ver());
		index += sprintf(pBuf+index,"MAC:%s\r\n",wifi_get_local_mac());
	}

	gui_messagebox_show("" ,pBuf, "", "", 1000000);

	return 0;
	
}

int test_m1()
{

	st_gui_message pMsg;
	char * pbuff;
	int rc;
	rc = mf_rfid_init();
	
	gui_post_message(GUI_GUIPAINT, 0 , 0);
	while(1){

		if (gui_get_message(&pMsg, 100) == 0) {
			if (pMsg.message_id == GUI_GUIPAINT) {

				gui_begin_batch_paint();
				gui_set_win_rc();
				gui_clear_dc();
				gui_set_title("M1");
				gui_textout_line_left( "Please press your" , GUI_LINE_TOP(1));
				gui_textout_line_left( "M1 card" , GUI_LINE_TOP(2));

				gui_page_op_paint("" , "exit");
				gui_end_batch_paint();
			}
			if (pMsg.message_id == GUI_KEYPRESS) {
				if (pMsg.wparam == GUI_KEY_OK)	{
					break;
				}
			}
		}
		else
		{
			int rc;
			unsigned char uid[16];
			int uidlen = 0;
            int cmd = 0;
            int sector = 0;
            int block = 0;
            char tempbuf[64] = {0};
            unsigned char databuff[16] = {0};
            int datalen = 0;
                        
			rc = mf_rfid_mfcl_open();//Find card
			if(rc >= 0) {

				uidlen = mf_rfid_getuid(uid);//get card sn

				if(uidlen >=0){
					Ex_Str_HexToAsc(uid , uidlen*2 , 0, tempbuf );
					gui_messagebox_show("CardID:" , tempbuf, "" , "confirm" , 0);
					mf_rfid_mfcl_setkey( "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF" );
					cmd = 0x60;//0x60:A key authentication;0x61:B key authentication
					sector = 1;//0--15
					rc = mf_rfid_mfcl_auth(cmd, sector);//Authenticate sector
					if(rc == 0)
					{
						block = sector*4+0;//0--2, fourth blcok is key data  
						rc = mf_rfid_mfcl_read(block, databuff, &datalen);//Reads the data for the specified block
						if(rc == 0)
						{
							Ex_Str_HexToAsc(databuff , datalen*2 , 0, tempbuf );
							gui_messagebox_show("Card info:" , tempbuf, "" , "confirm" , 0);
							memcpy(databuff, "\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\x11\x22\x33\x44\x55\x66", 16);
							datalen = 16;
							rc = mf_rfid_mfcl_write(block, databuff, datalen);//Writes the data for the specified block
							if(rc == 0)
							{
								gui_messagebox_show("rf m1" , "write data succ", "" , "confirm" , 0);                                                                                                                                    
							}
							else
							{
								gui_messagebox_show("rf m1" , "write data fail", "" , "confirm" , 0);                                                                                                                                       
							}
						}
						else
						{
							gui_messagebox_show("rf m1" , "read data fail", "" , "confirm" , 0);                                                                                      
						}
                    }
					else
                    {
						gui_messagebox_show("rf m1" , "authentication fail", "" , "confirm" , 0);
					}
				}
				else
                {
					gui_messagebox_show("rf m1" , "rf get cardid fail", "" , "confirm" , 0);
				}
				gui_post_message(GUI_GUIPAINT, 0 , 0);
			}
		}
	}
	mf_rfid_mfcl_close();
	return 0;

}

static int _sign_page_paint(const char *m_watermark)
{
	gui_textout_line_left( "Sign Page"  , xgui_GetLineTop(0) );
	gui_text_out_win_center( (char*)m_watermark );
}

static int _sign_page_getwritepointcount()
{
	return 0;
}

static int _sign_page_getwatermark( char *outwatermark)
{
	strcpy(outwatermark,"");
	return 0;
}

int test_touch()
{
	ap_sign_procs procs ={0};
	int r;
	int ret = 0;
	//ap_sign_clean();
	//procs.page_usecancel = test_page_usecancel;
	//procs.page_usesigntype = test_page_usesigntype;
	//procs.page_buffwidth = test_buffwidth;
	//procs.page_buffheight = test_buffheight;
	procs.page_paint = _sign_page_paint;
	procs.page_getwritepointcount = _sign_page_getwritepointcount;
	procs.page_getwatermark = _sign_page_getwatermark;

	ap_sign_clean();
	ap_setprocs( &procs);

	ap_sign_proc("A99999","1204" , "123456789012");

	ap_setprocs( 0);	
	//ap_sign_print("A99999");
	UPrint_Str( (char *)ap_sign_print("A99999") ,0,0,1);
	UPrint_Feed(100);
	ret = UPrint_Init();
	UPrint_Start();		

	//ap_setprocs( 0);
}

