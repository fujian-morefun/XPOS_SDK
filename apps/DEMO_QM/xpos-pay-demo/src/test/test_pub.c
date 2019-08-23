#include "test_pub.h"
#include "pub\osl\inc\osl_BaseParam.h"
#include "driver\mf_supply_power.h"
#include "driver\mf_magtek.h"
#include "xGui\inc\messagedatastruct.h"
#include "xGui\inc\2ddraw.h"
#include "xGui\inc\message.h"
#include "xGui\inc\xgui_key.h"
#include "AppPub\upaypage\ap_sign_page.h"
//#include "driver\mf_icc.h"
#define APP_TRACE(...) 	osl_log("uninpay",0, __VA_ARGS__);

int test_devinfo( void )
{
	int index = 0;
	char szNum[64];
	char pBuf[512]= {0};

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


	index += sprintf(pBuf+index,"Sys:%s\r\n",osl_getDeviceVision());
	//index += sprintf(pBuf+index,"App:%s\r\n",osl_getAppVision());
	index += sprintf(pBuf+index,"UBOOT:%s\r\n",mf_boot_ver());
	index += sprintf(pBuf+index,"driver:%s\r\n",mf_hal_ver());
	index += sprintf(pBuf+index,"FATFS:%s\r\n",mf_fatfs_ver());
	index += sprintf(pBuf+index,"FAL:%s\r\n",mf_fal_ver());
	index += sprintf(pBuf+index,"hardwware:%d\r\n",mf_hardware_ver());

	osl_getTerminalID(szNum,sizeof(szNum) -1);
	index += sprintf(pBuf+index,"SN:%s\r\n", szNum );

	osl_get_psn(szNum);
	index += sprintf(pBuf+index,"PSN:%s\r\n", szNum );



	if( osl_get_is_dual_module() == 0){
		index += sprintf(pBuf+index, "model_type:%s\n", (osl_model_type() == MODEL_WIRELESS) ? "WIRELESS" : "WIFI");
		if(osl_model_type() == MODEL_WIRELESS){
			index += sprintf(pBuf+index, "IMEI:%s\n", atc_imei());
			index += sprintf(pBuf+index, "IMSI:%s\n", atc_imsi());
		}
		else if(osl_model_type() == MODEL_WIFI){
#ifndef WIN32
			index += sprintf(pBuf+index, "MAC:%s\n", wifi_get_local_mac());
#endif 
		}

	}
	else {
		index += sprintf(pBuf+index, "model_type:%s\n", "WIRELESS+WIFI");
		index += sprintf(pBuf+index, "IMEI:%s\n", atc_imei());
		index += sprintf(pBuf+index, "IMSI:%s\n", atc_imsi());
		#ifndef WIN32
		index += sprintf(pBuf+index, "MAC:%s\n", wifi_get_local_mac());
		#endif
	}



	
// 	sprintf(szBuf+strlen(szBuf),"À¶ÑÀÀàÐÍ:%d\r\n",bluetooth_get_type());
// 	bluetooth_get_name(szNum);
// 	sprintf(szBuf+strlen(szBuf),"Ãû³Æ:%s\r\n",szNum);
// 	bluetooth_get_addr(szNum);
// 	sprintf(szBuf+strlen(szBuf), "MAC:%s\r\n" , szNum); 


	xgui_messagebox_show("" ,pBuf, "", "", 1000000);

	return 0;
	
}



int test_magcard()
{
	MESSAGE pMsg;
	char * pbuff;

	mf_magtek_flush();
	xgui_PostMessage(XM_GUIPAINT, 0 , 0);
	while(1){

		if (xgui_GetMessageWithTime(&pMsg, 100) == MESSAGE_ERR_NO_ERR) {
			if (pMsg.MessageId == XM_GUIPAINT) {

				xgui_BeginBatchPaint();
				XGUI_SET_WIN_RC;
				xgui_ClearDC();
				xgui_SetTitle("magcard");
				xgui_TextOut_Line_Left( "Please press your" , XGUI_LINE_TOP_1);
				xgui_TextOut_Line_Left( "card" , XGUI_LINE_TOP_2);

				xgui_Page_OP_Paint("" , "confirm");
				xgui_EndBatchPaint();
			}
			if (pMsg.MessageId == XM_KEYPRESS) {
				if (pMsg.WParam == KEY_OK)	{
					break;
				}
			}
		}
		else{
			unsigned char msg[512]={0};
			struct magtek_track_info info;
			if(mf_magtek_read(&info) == 1){
				sprintf(msg + strlen(msg), "track A:%s\r\n", info.a_chars.chars);
				sprintf(msg + strlen(msg), "track B:%s\r\n", info.b_chars.chars);
				sprintf(msg + strlen(msg), "track C:%s\r\n", info.c_chars.chars);
				xgui_messagebox_show("magcard" , msg, "" , "confirm" , 0);


				mf_magtek_flush();
				xgui_PostMessage(XM_GUIPAINT, 0 , 0);
			}
		}

	}	


	return 0;
}


/*
int test_IC()
{

	MESSAGE pMsg;
	char * pbuff;

	xgui_PostMessage(XM_GUIPAINT, 0 , 0);
	while(1){

		if (xgui_GetMessageWithTime(&pMsg, 100) == MESSAGE_ERR_NO_ERR) {
			if (pMsg.MessageId == XM_GUIPAINT) {

				xgui_BeginBatchPaint();
				XGUI_SET_WIN_RC;
				xgui_ClearDC();
				xgui_SetTitle("ic");
				xgui_TextOut_Line_Left( "Please press your" , XGUI_LINE_TOP_1);
				xgui_TextOut_Line_Left( "IC card" , XGUI_LINE_TOP_2);

				xgui_Page_OP_Paint("" , "exit");
				xgui_EndBatchPaint();
			}
			if (pMsg.MessageId == XM_KEYPRESS) {
				if (pMsg.WParam == KEY_OK)	{
					break;
				}
			}
		}
		else
		{
			int icc_socket = ICC_SOCKET1; 
			int ret;
			icc_open(icc_socket);
			ret = icc_present(icc_socket) ;
			icc_close(icc_socket);

			if( ret == 1) {
				sdk_driver_icc();
				xgui_PostMessage(XM_GUIPAINT, 0 , 0);
			}
		}

	}	


	return 0;

}*/


int test_rf()
{

	MESSAGE pMsg;
	char * pbuff;
	int rc;
	
	APP_TRACE("rf1\r\n");
	xgui_PostMessage(XM_GUIPAINT, 0 , 0);
	while(1){
		if (xgui_GetMessageWithTime(&pMsg, 500) == MESSAGE_ERR_NO_ERR) {
			APP_TRACE("rf2:%d\r\n",pMsg.MessageId);
			if (pMsg.MessageId == XM_GUIPAINT) {

				xgui_BeginBatchPaint();
				XGUI_SET_WIN_RC;
				xgui_ClearDC();
				xgui_SetTitle("RF");
				xgui_TextOut_Line_Left( "Please press" , XGUI_LINE_TOP_1);
				xgui_TextOut_Line_Left( "RF card" , XGUI_LINE_TOP_2);

				xgui_Page_OP_Paint("" , "exit");
				xgui_EndBatchPaint();
			}
			if (pMsg.MessageId == XM_KEYPRESS) {
				if (pMsg.WParam == KEY_OK || pMsg.WParam == KEY_QUIT)	{
					break;
				}
			}
		}
		else
		{
			int rc;
			unsigned char *rxbuf;
			unsigned short rxlen = 0;
			unsigned char uid[16];
			int uidlen = 0;
			unsigned char cmd1[19]={"\x00\xa4\x04\x00\x0e\x32\x50\x41\x59\x2e\x53\x59\x53\x2e\x44\x44\x46\x30\x31"};

			
			rc = mf_rfid_tcl_open();

			APP_TRACE("rf3:%d\r\n",rc);
			if(rc >= 0) {

				uidlen = mf_rfid_getuid(uid);

				if(uidlen >=0){
					rc = mf_rfid_tcl_exchange(cmd1, sizeof(cmd1), &rxbuf, &rxlen);
					if(rc == 0 ){
						xgui_messagebox_show("rf ic" , "send apdu succ", "" , "confirm" , 0);
					}
					else{
						xgui_messagebox_show("rf ic" , "send apdu ok", "" , "confirm" , 0);
					}
				}
				else{
					xgui_messagebox_show("rf ic" , "rf get uid fail", "" , "confirm" , 0);
				}

				xgui_PostMessage(XM_GUIPAINT, 0 , 0);
			}
			mf_rfid_tcl_close();
		}

	}
	
	return 0;

}

int test_m1()
{

	MESSAGE pMsg;
	char * pbuff;
	int rc;
	rc = mf_rfid_init();

	xgui_PostMessage(XM_GUIPAINT, 0 , 0);
	while(1){

		if (xgui_GetMessageWithTime(&pMsg, 500) == MESSAGE_ERR_NO_ERR) {
			if (pMsg.MessageId == XM_GUIPAINT) {

				xgui_BeginBatchPaint();
				XGUI_SET_WIN_RC;
				xgui_ClearDC();
				xgui_SetTitle("M1");
				xgui_TextOut_Line_Left( "Please press your" , XGUI_LINE_TOP_1);
				xgui_TextOut_Line_Left( "M1 card" , XGUI_LINE_TOP_2);

				xgui_Page_OP_Paint("" , "exit");
				xgui_EndBatchPaint();
			}
			if (pMsg.MessageId == XM_KEYPRESS) {
				if (pMsg.WParam == KEY_OK || pMsg.WParam == KEY_QUIT)	{
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

				if(uidlen >= 0){
					Ex_Str_HexToAsc(uid , 8 , 0, tempbuf );
					xgui_messagebox_show("CardID:" , tempbuf, "" , "confirm" , 0);
					mf_rfid_mfcl_setkey( "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF" );
					cmd = 0x60;//0x60:A key authentication;0x61:B key authentication
					sector = 1;//0--15
					rc = mf_rfid_mfcl_auth(cmd, sector);//Authenticate sector
					if(rc == 0)
					{
						block = 0;//0--2, fourth blcok is key data  
						rc = mf_rfid_mfcl_read(block, databuff, &datalen);//Reads the data for the specified block
						if(rc == 0)
						{
							Ex_Str_HexToAsc(databuff , datalen*2 , 0, tempbuf );
							xgui_messagebox_show("Card info:" , tempbuf, "" , "confirm" , 0);
							memcpy(databuff, "\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\x11\x22\x33\x44\x55\x66", 16);
							datalen = 16;
							rc = mf_rfid_mfcl_write(block, databuff, datalen);//Writes the data for the specified block
							if(rc == 0)
							{
								xgui_messagebox_show("rf m1" , "write data succ", "" , "confirm" , 0);                                                                                                                                    
							}
							else
							{
								xgui_messagebox_show("rf m1" , "write data fail", "" , "confirm" , 0);                                                                                                                                       
							}
						}
						else
						{
							xgui_messagebox_show("rf m1" , "read data fail", "" , "confirm" , 0);                                                                                      
						}
					}
					else
					{
						xgui_messagebox_show("rf m1" , "authentication fail", "" , "confirm" , 0);
					}
				}
				else
				{
					xgui_messagebox_show("rf m1" , "rf get cardid fail", "" , "confirm" , 0);
				}

				xgui_PostMessage(XM_GUIPAINT, 0 , 0);
			}

		}
	}
	mf_rfid_mfcl_close();
	return 0;

}

static int _sign_page_paint(const char *m_watermark)
{
	xgui_TextOut_Line_Left( "Sign Page"  , xgui_GetLineTop(0) );
	xgui_TextOut_Win_Center( (char*)m_watermark );

}


int test_touch()
{
	ap_sign_procs procs ={0};
	int r;
	//ap_sign_clean();
	//procs.page_usecancel = test_page_usecancel;
	//procs.page_usesigntype = test_page_usesigntype;
	//procs.page_buffwidth = test_buffwidth;
	//procs.page_buffheight = test_buffheight;
	procs.page_paint = _sign_page_paint;

	ap_sign_clean();
	ap_setprocs( &procs);

	ap_sign_proc("A99999","1204" , "123456789012");


	//ap_setprocs( 0);
}

