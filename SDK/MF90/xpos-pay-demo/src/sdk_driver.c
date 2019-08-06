#include "sdk_driver.h"
#include "driver/mf_driverlib.h"
#include "driver/mf_simple_rfid.h"
#include "driver/uart.h"
#include "driver/mf_serial.h"
#include "xGui/inc/messagebox.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/message.h"
#include "libapi_xpos/inc/libapi_comm.h"
#include "pub\tracedef.h"
#include "libapi_xpos\inc\libapi_util.h"

static void sdk_show_msg(char *title, char *msg)
{
	// Batch refresh, because the LCD refresh takes a long time, all systems provide xgui_EndBatchPaint interface to uniformly send display data to the LCD screen
	xgui_BeginBatchPaint();				
	xgui_ClearDC();			//  Clear the entire screen
	xgui_TextOut_Line_Center(title , XGUI_LINE_TOP_0);		// Display the content of title at line 0
	xgui_TextOut(0, XGUI_LINE_TOP_2, msg);   // Display msg content on line 2
	xgui_EndBatchPaint();     
}


void sdk_driver_magtek()
{
	unsigned char msg[512]={0};
	struct magtek_track_info info;

	mf_magtek_flush();			// Empty the magnetic stripe card buffer
	// Waiting for credit card
	xgui_messagebox_show("magcard" , "Please brush your cards", "" , "confirm" , 0); 
	if(mf_magtek_read(&info) == 1){		// Determine if you are all on the card
		sprintf(msg + strlen(msg), "track A:%s\r\n", info.a_chars.chars);
		sprintf(msg + strlen(msg), "track B:%s\r\n", info.b_chars.chars);
		sprintf(msg + strlen(msg), "track C:%s\r\n", info.c_chars.chars);
		xgui_messagebox_show("magcard" , msg, "" , "confirm" , 0);	// Display card information
	}
}

void sdk_driver_icc()
{
	int ret, atrlen;
	unsigned char atr[64], rbuffer[64];
	unsigned char buffer[128];
	int icc_socket = ICC_SOCKET1; 
	unsigned char test_cmd[] = {0x00,0xA4,0x04,0x00,0x08,0xA0,0x00,0x00,0x03,0x33,0x01,0x01,0x01,0x00}; 


	atrlen = -1;
	ret = 0;
	icc_open(icc_socket);		// Open the card reader

	if(icc_present(icc_socket) == 1) {		// Check if the card is in place
		ret = icc_powerup(icc_socket, atr, sizeof(atr));	// Card power up
		if(ret >=0){
			ret = icc_send_apdu(icc_socket, test_cmd, sizeof(test_cmd), rbuffer);	// Tpdu data exchange
			if(ret >=0 ){
				xgui_messagebox_show("icc" , "send apdu succ", "" , "confirm" , 0);
			}
			else{
				xgui_messagebox_show("icc" , "send apdu ok", "" , "confirm" , 0);
			}
		}
		else{
			xgui_messagebox_show("icc" , "power fail", "" , "confirm" , 0);
		}
		icc_powerdown(icc_socket);	// Card power down
	}
	else{
		xgui_messagebox_show("icc" , "icc_present fail", "" , "confirm" , 0);
	}
	icc_close(icc_socket);   // close the card reader
}

void sdk_driver_rf()
{
	int rc;
	unsigned char *rxbuf;
	unsigned short rxlen = 0;
	unsigned char uid[16];
	int uidlen = 0;
	unsigned char cmd1[19]={"\x00\xa4\x04\x00\x0e\x32\x50\x41\x59\x2e\x53\x59\x53\x2e\x44\x44\x46\x30\x31"};

	rc = mf_rfid_tcl_open();			// Open the card reader,Check whether the card is powered on successfully.
	if(rc >= 0) {
		uidlen = mf_rfid_getuid(uid);	// Read cpuid
		
		if(uidlen >=0){
			rc = mf_rfid_tcl_exchange(cmd1, sizeof(cmd1), &rxbuf, &rxlen);		// Tpdu data exchange
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
	}
	else{
		xgui_messagebox_show("rf ic" , "rf open fail", "" , "confirm" , 0);
	}
}


void sdk_driver_led()
{
	int i;
	char msg[32];

	for(i =0 ; i < 4; i ++){
		sprintf(msg, "test led:%d", i);
		sdk_show_msg("led", msg);
		mf_led_control(i, 1);		// led power on
		osl_Sleep(500);
		mf_led_control(i, 0);		// led power off
		osl_Sleep(500);
	}
	xgui_PostMessage(XM_GUIPAINT, 0 , 0);
	
}



void sdk_driver_barcode()
{
	char msg[128];
	int ret;
	int com = MF_UART_COM22;
	unsigned char rbuf[256];

	sdk_show_msg("barcode", "scan...");
	// The scanner is receiving data through the serial port.
	mf_serial_open(com, 9600, MF_UART_WordLength_8b, MF_UART_StopBits_1, MF_UART_Parity_No); 
	mf_barcode_trig(1);		//  Trigger scan
	ret = mf_serial_read(com, rbuf, sizeof(rbuf), 1000 * 2);		// Read scanned data
	mf_barcode_trig(0);		// Stop scanning
	mf_serial_close(com);

	if(ret>0) {
		xgui_messagebox_show("barcode" , rbuf, "" , "confirm" , 0);
	}	
}


void wifi_link_test()
{
	int count = 0;
	st_wifi_ap_list ap_list[10];
	int i;
	char temp[128];
	char name[1024];
	int ret = 0;

	APP_TRACE( "wifi_link_test" );

	sdk_show_msg("wifi", "scan...");

	count = comm_wifi_list_ap(ap_list);
	APP_TRACE( "comm_wifi_list_ap:%d", count);

	if(count > 0){
		for(i = 0; i< count ; i ++){
			sprintf(temp, "%d.%s(%d)\r\n", i+1, ap_list[i].ssid, ap_list[i].rssi);
			APP_TRACE( temp );
			strcat(name, temp);
		}
		xgui_messagebox_show("WiFi List" , name, "" , "confirm" , 5000);
		
		comm_wifi_link_ap(&ap_list[0], "12345678");
		comm_wifi_unlink_ap();
	}
}

// void input_test()
// {
// 	char str[128] = {0};
// 
// 	Util_InputMethod(0, "input_test", 1, str, 0, 64, 0, 60000);
// 
// }

#define ADMIN_PWD "88888888"

void SetDukptKey()
{
	char ksn_str[21] = {0};
	char key_str[33] = {0};
	char ksn[11] = {0};
	char key[17] = {0};
	int ret = 0;
	char pwd[9] = {0};
	
	ret = input_num_page(pwd, "input password", 1, 8, 60000, 1, 0);

	if (ret==0 && memcmp(pwd, ADMIN_PWD, 8) == 0)
	{
		memcpy(ksn_str, "FFFF", 4);
		ret = Util_InputMethod(0, "input ksn", 1, ksn_str, 16, 16, 4, 60000);
		if (ret == 16)
		{
			memcpy(ksn_str+16, "0000", 4);
			Util_Asc2Bcd(ksn_str, ksn, 20);

			ret = Util_InputMethod(0, "input key", 1, key_str, 32, 32, 0, 60000);
			if (ret == 32)
			{
				Util_Asc2Bcd(key_str, key, 32);
				dukpt_init_key(0, ksn, key);

				xgui_messagebox_show("SetKey" , "Set DUKPT Init Key OK!", "" , "confirm" , 0);
			}
		}
	}
	else
	{
		xgui_messagebox_show("SetKey" , "Please enter the correct administrator password!", "" , "confirm" , 0);
	}
}