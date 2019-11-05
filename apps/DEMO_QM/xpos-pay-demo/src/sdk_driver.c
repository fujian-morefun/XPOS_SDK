#include "sdk_driver.h"
#include "driver/mf_driverlib.h"
#include "driver/mf_simple_rfid.h"
#include "driver/uart.h"
#include "driver/mf_serial.h"
#include "xGui/inc/messagebox.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/message.h"
#include "libapi_xpos/inc/libapi_util.h"
#include "bluetooth/inc/bluetooth.h"
#include "pub/common/misc/inc/mfmalloc.h"
#include "xGui/inc/xgui_key.h"
#include "mpos_func.h"

#define LOGOIMG "data\\logo2.bmp"

int g_playtag = 0;

static void sdk_show_msg(char *title, char *msg)
{
	xgui_BeginBatchPaint();
	xgui_ClearDC();
	xgui_TextOut_Line_Center(title , XGUI_LINE_TOP_0);
	xgui_TextOut(0, XGUI_LINE_TOP_1, msg);
	xgui_EndBatchPaint();
}


void sdk_driver_magtek()
{
	unsigned char msg[512]={0};
	struct magtek_track_info info;

	mf_magtek_flush();
	xgui_messagebox_show("magcard" , "Please brush your cards", "" , "confirm" , 0);
	if(mf_magtek_read(&info) == 1){
		sprintf(msg + strlen(msg), "track A:%s\r\n", info.a_chars.chars);
		sprintf(msg + strlen(msg), "track B:%s\r\n", info.b_chars.chars);
		sprintf(msg + strlen(msg), "track C:%s\r\n", info.c_chars.chars);
		xgui_messagebox_show("magcard" , msg, "" , "confirm" , 0);
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
	icc_open(icc_socket);

	if(icc_present(icc_socket) == 1) {
		ret = icc_powerup(icc_socket, atr, sizeof(atr));	
		if(ret >=0){
			ret = icc_send_apdu(icc_socket, test_cmd, sizeof(test_cmd), rbuffer);
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
		icc_powerdown(icc_socket);	
	}
	else{
		xgui_messagebox_show("icc" , "icc_present fail", "" , "confirm" , 0);
	}
	icc_close(icc_socket);
}

void sdk_driver_rf()
{
	int rc;
	unsigned char *rxbuf;
	unsigned short rxlen = 0;
	unsigned char uid[16];
	int uidlen = 0;
	unsigned char cmd1[19]={"\x00\xa4\x04\x00\x0e\x32\x50\x41\x59\x2e\x53\x59\x53\x2e\x44\x44\x46\x30\x31"};

	rc = mf_rfid_tcl_open();
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
	}
	else{
		xgui_messagebox_show("rf ic" , "rf open fail", "" , "confirm" , 0);
	}
}


void sdk_driver_led()
{
	int i;
	char msg[32];

	for(i =0 ; i < 4 ; i ++){
		sprintf(msg, "test led:%d", i + 1);
		sdk_show_msg("led", msg);
		mf_led_control(i + 1, 1);		// open
		osl_Sleep(500);
		mf_led_control(i + 1, 0);		// close
		osl_Sleep(500);
	}
	xgui_PostMessage(XM_GUIPAINT, 0 , 0);
	
}



void sdk_driver_barcode()
{
	char msg[128];
	int ret;
	int com = MF_UART_COM22;
	unsigned char rbuf[256]={0};
	int count = 0;
	int flag = 0;
	int tick1 = osl_GetTick();

	sdk_show_msg("barcode", "scan...");

	UartOpen(com, 115200, MF_UART_WordLength_8b, MF_UART_StopBits_1, MF_UART_Parity_No);
	mf_barcode_trig(1);
	UartClear(com);

	while(osl_CheckTimeover(tick1 , 5000) == 0){
		ret = UartGetRXBufCount(com);
		if(ret > 0){
			ret = UartRecv(com, rbuf + count, sizeof(rbuf) - count, 10);
			count += ret;
			flag = 1;
		}
		else if(flag == 1){
			break;
		}
		osl_Sleep(50);
	}
	
	mf_barcode_trig(0);
	UartClose(com);

	if(count>0) {
		xgui_messagebox_show("barcode" , rbuf, "" , "confirm" , 30000);
	}
	
}

void VoiceTest()
{
	Play_Voice("payok");//payment suceesfull
	//Play_Voice("NoSpike");
}

void pagepaint(char *title, char *msg, int logo)
{
	int len = 0;
	char temp[20] = {0};
	int logowidth;
	int logoheight;
	int logoleft;
	int logotop;
	int logocolor;

	char * pbmp;

	len = strlen(msg);

	xgui_BeginBatchPaint();
	XGUI_SET_WIN_RC;
	xgui_ClearDC();


	if (logo == 1)
	{
		pbmp = (char *)xgui_load_bmp_all(LOGOIMG , &logowidth , &logoheight, &logocolor);

		logoleft = (xgui_GetWidth()-logowidth)/2;
		logotop = XGUI_LINE_TOP_1+5;

		if (pbmp != 0){
			xgui_out_bits_bmp(logoleft, logotop, pbmp , logowidth , logoheight , 1 , logocolor);
			FREE(pbmp);
		}	
	} 
	else
	{
		xgui_SetTitle(title);

		if (len > 0 && len <= 15)
		{
			xgui_TextOut_Line_Center(msg, XGUI_LINE_TOP_3);
		}
		else if (len>15 && len<=30)
		{
			memcpy(temp, msg, 15);
			xgui_TextOut_Line_Center(temp, XGUI_LINE_TOP_3);
			xgui_TextOut_Line_Center(msg+15, XGUI_LINE_TOP_4);
		}
		else if (len>30 && len<=45)
		{
			memcpy(temp, msg, 15);
			xgui_TextOut_Line_Center(temp, XGUI_LINE_TOP_3);
			memcpy(temp, msg+15, 15);
			xgui_TextOut_Line_Center(temp, XGUI_LINE_TOP_4);
			xgui_TextOut_Line_Center(msg+30, XGUI_LINE_TOP_5);
		}
		else if (len > 45)
		{
			memcpy(temp, msg, 15);
			xgui_TextOut_Line_Center(temp, XGUI_LINE_TOP_3);
			memcpy(temp, msg+15, 15);
			xgui_TextOut_Line_Center(temp, XGUI_LINE_TOP_4);
			memcpy(temp, msg+30, 15);
			xgui_TextOut_Line_Center(temp, XGUI_LINE_TOP_5);
			xgui_TextOut_Line_Center(msg+45, XGUI_LINE_TOP_6);
		}	
	}

	xgui_EndBatchPaint();
}

void BluetoothTest()
{
#define RECV_BUFF_SIZE		1280
#define RECV_TMP_SIZE		128

	static unsigned char * m_recv_buff;
	static int m_recv_index = 0;
	static unsigned int m_last_recv_tick = 0;
	char buffer[256] = {0};
	MESSAGE pMsg;

	bluetooth_init();
	bluetooth_set_pause(1);
	m_recv_buff = (unsigned char *)MALLOC(RECV_BUFF_SIZE+1);
	osl_Sleep(100);
	
	strcpy(buffer, "Waiting to Recv");
	xgui_PostMessage(XM_GUIPAINT, 0 , 0);

	while(1)
	{
		if (xgui_GetMessageWithTime(&pMsg, 300) == MESSAGE_ERR_NO_ERR) {

			if (pMsg.MessageId == XM_GUIPAINT) {
				pagepaint("BluetoothTest", buffer, 0);
			}
			else if (pMsg.MessageId == XM_KEYPRESS){
				if (pMsg.WParam == KEY_QUIT)
				{
					break;
				}
			}
			else{
				xgui_proc_default_msg(&pMsg);
			} 
		}

		bluetooth_run_proc();

		if(bluetooth_recv_count() <=0 ){
			if(osl_CheckTimeover(m_last_recv_tick , 5000) != 0){
				m_recv_index = 0;
				m_last_recv_tick = osl_GetTick();	
			}
			continue;
		}

		m_last_recv_tick = osl_GetTick();

		memset(m_recv_buff, 0x00, RECV_BUFF_SIZE);
		m_recv_index = bluetooth_recv(m_recv_buff, RECV_TMP_SIZE);
		if (m_recv_index > 0)
		{
			sprintf(buffer, "Recv:%s", m_recv_buff);
			xgui_PostMessage(XM_GUIPAINT, 0 , 0);
		}			
	}

	bluetooth_set_pause(0);
	FREE(m_recv_buff);
}

void SerialPortTest()
{
	MESSAGE pMsg;
	st_qr_data  * qr_data = mpos_func_get_qr_data();
	char buffer[20] = {0};
	char time_cur[20];
	char time_last[20];
	char msg[128] = {0};
	int logo = 1;

	get_hhmmss_str(time_last);

	init_com();
	strcpy(buffer, "Waiting to Recv");
	//strcpy(qr_data->amt, "1.00");
	//strcpy(qr_data->qrdata, "http://en.morefun-et.com");
	//strcpy(mpos_qr_data->text, "payment successful!");
	xgui_PostMessage(XM_GUIPAINT, 0 , 0);

	while(1)
	{
		if (xgui_GetMessageWithTime(&pMsg, 300) == MESSAGE_ERR_NO_ERR) {

			if (pMsg.MessageId == XM_GUIPAINT) {
				if (strlen(qr_data->qrdata) > 0)
				{
					mf_led_digit_show(qr_data->amt);	
					showQr(qr_data->amt, qr_data->qrdata);
					//showQr("1.00", "http://en.morefun-et.com");
				} 
				else if (strlen(qr_data->text) > 0)
				{
					if (strstr(qr_data->text, "success") != 0 && g_playtag == 1)
					{
						Play_Voice("payok");
						mf_led_digit_show("1");	
					} 
					else if (strstr(qr_data->text, "fail") != 0 && g_playtag == 1)
					{
						Play_Voice("payerr");
						mf_led_digit_show("0");	
					} 
					g_playtag = 0;

					sprintf(msg, "\n\n%s", qr_data->text);

					xgui_messagebox_show(" ",  msg, "" , "" ,  500);
					//memset(mpos_qr_data->text, 0, sizeof(mpos_qr_data->text));
				}
				else
				{
					mf_led_digit_show("");	
					if (logo < 3)
					{
						pagepaint("SerialPortTest", buffer, 0);
					} 
					else
					{
						pagepaint("SerialPortTest", buffer, 1);
					}
				}
			}
			else if (pMsg.MessageId == XM_KEYPRESS){
				if (pMsg.WParam == KEY_QUIT)
				{
					break;
				}
			}
			else{
				xgui_proc_default_msg(&pMsg);
			} 
		}

		_mpos_proc();

		if (Rf_Check_CardIsExist() == 0)
		{
			xgui_messagebox_show("Prompt","Find a card","","confirm", 3000 );
		}
		get_hhmmss_str(time_cur);
		if ( strcmp(time_last,time_cur) != 0 ){
			logo++;
			logo %= 6;
			strcpy(time_last, time_cur );
			xgui_PostMessage(XM_GUIPAINT, 0 , 0);
		}
	}

	close_com();
}

