#include "driver/uart.h"
#include "driver/mf_serial.h"
#include "app_def.h"

enum{
	DRIVER_TYPE_MAG,
	DRIVER_TYPE_ICC,
	DRIVER_TYPE_RF,
};

static void sdk_show_msg(char *title, char *msg)
{
	// Batch refresh, because the LCD refresh takes a long time, all systems provide xgui_EndBatchPaint interface to uniformly send display data to the LCD screen
	gui_begin_batch_paint();				
	gui_clear_dc();			//  Clear the entire screen
	gui_textout_line_center(title , GUI_LINE_TOP(0));		// Display the content of title at line 0
	gui_text_out(0, GUI_LINE_TOP(2), msg);   // Display msg content on line 2
	gui_end_batch_paint();     
}
void sdk_driver_magtek()
{
	unsigned char msg[512]={0};
	struct magtek_track_info info;

	card_magtek_flush();			// Empty the magnetic stripe card buffer
	// Waiting for credit card
	gui_messagebox_show("magcard" , "Please brush your cards", "" , "confirm" , 0); 
	if(emvapi_check_magtek(&info) == 1){		// Determine if you are all on the card
		sprintf(msg + strlen(msg), "track A:%s\r\n", info.a_chars.chars);
		sprintf(msg + strlen(msg), "track B:%s\r\n", info.b_chars.chars);
		sprintf(msg + strlen(msg), "track C:%s\r\n", info.c_chars.chars);
		gui_messagebox_show("magcard" , msg, "" , "confirm" , 0);	// Display card information
	}
}

void sdk_driver_icc()
{
	int ret, atrlen;
	unsigned char atr[64], rbuffer[64];
	unsigned char buffer[128];
	int icc_socket = SLOT_ICC_SOCKET1; 
	unsigned char test_cmd[] = {0x00,0xA4,0x04,0x00,0x08,0xA0,0x00,0x00,0x03,0x33,0x01,0x01,0x01,0x00}; 


	atrlen = -1;
	ret = 0;
	Icc_Open(icc_socket);		// Open the card reader

	if(icc_present(icc_socket) == 1) {		// Check if the card is in place
		ret = icc_powerup(icc_socket, atr, sizeof(atr));	// Card power up
		if(ret >=0){
			ret = icc_send_apdu(icc_socket, test_cmd, sizeof(test_cmd), rbuffer);	// Tpdu data exchange
			if(ret >=0 ){
				gui_messagebox_show("icc" , "send apdu succ", "" , "confirm" , 0);
			}
			else{
				gui_messagebox_show("icc" , "send apdu ok", "" , "confirm" , 0);
			}
		}
		else{
			gui_messagebox_show("icc" , "power fail", "" , "confirm" , 0);
		}
		icc_powerdown(icc_socket);	// Card power down
	}
	else{
		gui_messagebox_show("icc" , "icc_present fail", "" , "confirm" , 0);
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

	rc = emvapi_check_rf();			// Open the card reader,Check whether the card is powered on successfully.
	if(rc >= 0) {
		uidlen = mf_rfid_getuid(uid);	// Read cpuid
		
		if(uidlen >=0){
			rc = mf_rfid_tcl_exchange(cmd1, sizeof(cmd1), &rxbuf, &rxlen);		// Tpdu data exchange
			if(rc == 0 ){
				gui_messagebox_show("rf ic" , "send apdu succ", "" , "confirm" , 0);
			}
			else{
				gui_messagebox_show("rf ic" , "send apdu ok", "" , "confirm" , 0);
			}
		}
		else{
			gui_messagebox_show("rf ic" , "rf get uid fail", "" , "confirm" , 0);
		}
	}
	else{
		gui_messagebox_show("rf ic" , "rf open fail", "" , "confirm" , 0);
	}
}


void sdk_driver_led()
{
	int i;
	char msg[32];

	for(i =0 ; i < 4; i ++){
		sprintf(msg, "test led:%d", i);
		sdk_show_msg("led", msg);
		Util_Led(i, 1);		// led power on
		Sys_Delay(500);
		Util_Led(i, 0);		// led power off
		Sys_Delay(500);
	}
	gui_post_message(GUI_GUIPAINT, 0 , 0);
	
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
		gui_messagebox_show("barcode" , rbuf, "" , "confirm" , 0);
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

	SYS_TRACE( "wifi_link_test" );

	sdk_show_msg("wifi", "scan...");

	count = comm_wifi_list_ap(ap_list);
	SYS_TRACE( "comm_wifi_list_ap:%d", count);

	if(count > 0){
		for(i = 0; i< count ; i ++){
			sprintf(temp, "%d.%s(%d)\r\n", i+1, ap_list[i].ssid, ap_list[i].rssi);
			SYS_TRACE( temp );
			strcat(name, temp);
		}
		gui_messagebox_show("WiFi List" , name, "" , "confirm" , 5000);
		
		comm_wifi_link_ap(&ap_list[0], "12345678");
		comm_wifi_unlink_ap();
	}
}



#define RECV_BUFF_SIZE		256//(1024 * 5)
#define RECV_TMP_SIZE		128

#define	STX_CODE_1 			0x4D
#define	STX_CODE_2 			0x46
#define	ETX_CODE 			0x02

static unsigned char recv_tmp[RECV_TMP_SIZE+1];
static unsigned char m_recv_buff[RECV_BUFF_SIZE+1];

static int driver_get_ll_len(unsigned char *pbuff)
{
	int len = 0;
	len = (pbuff[0] & 0xf0) / 16 * 1000 + (pbuff[0] & 0x0f) * 100;
	len +=	(pbuff[1] & 0xf0) / 16 * 10 + (pbuff[1] & 0x0f);
	return len;
}
static void driver_check_sum_update(unsigned char * check_value , unsigned char *buff , int length)
{
	int i ; 
	for(i = 0 ; i < length ; i++){
		*check_value = *check_value ^ buff[i];
	}
}
static int test_func_proc(unsigned char * data , int len)
{
	int ret ;
	char messge[128]={0};
	memcpy(messge,data,len);
	gui_messagebox_show( "Uart Test" , messge, "" , "confirm" , 0);

	return 0;
}
static int uart_test_proc (void * pParam)
{
	int i;
	int recv_count ; 
	int m_recv_index = 0;
	int data_len = 0;

	int m_log_count = 0;
	unsigned char check_sum = 0;
	//\x4d\x46\x00\x05\x68\x65\x6C\x6C\x6F\x02\x65
	while(UartGetRXBufCount(APP_COM) > 0){
		memset(recv_tmp, 0x00, RECV_TMP_SIZE);
		recv_count = UartRecv(APP_COM , recv_tmp, RECV_TMP_SIZE ,1);
		printf("\r\nm_recv_buff>>>%d %x%x%x\r\n", recv_count, recv_tmp[0],recv_tmp[1],recv_tmp[2]);
		SYS_TRACE_BUFF(recv_tmp,recv_count,"UartRecv>>DATA");
		for (i = 0 ; i < recv_count; i ++)	{
			m_recv_buff[m_recv_index] = recv_tmp[i];
			m_log_count ++;

			if (m_recv_index == 0 ){			
				if (m_recv_buff[m_recv_index] == STX_CODE_1)	
					m_recv_index ++;			
				else
					m_recv_index = 0;			
			}
			else if (m_recv_index == 1 ){			
				if (m_recv_buff[m_recv_index] == STX_CODE_2)	
					m_recv_index ++;			
				else
					m_recv_index = 0;			
			}
			else if (m_recv_index == 2 ){						
				m_recv_index++;
			}
			else if (m_recv_index == 3 ){						
				data_len = driver_get_ll_len(&m_recv_buff[2]) + 2;

				if (data_len > RECV_BUFF_SIZE - 10)				
					m_recv_index = 0;
				else
					m_recv_index ++;
			}
			else if (m_recv_index > 3)	{						
				data_len --;
				m_recv_index ++;
				if (data_len == 0){						
					check_sum = 0;
					driver_check_sum_update(&check_sum , m_recv_buff + 2 , m_recv_index - 3);
					if (m_recv_buff[m_recv_index -2] == ETX_CODE && check_sum == m_recv_buff[m_recv_index -1])	{
						SYS_TRACE_BUFF(recv_tmp,recv_count,"m_recv_buff>>DATA");
						printf("m_recv_buff>>>\r\n");
						if (m_log_count > 0 ){
							m_log_count = 0;
						}
						return test_func_proc(m_recv_buff + 4, m_recv_index - 6);
					}
					else{
						if (m_log_count > 0 ){
							m_log_count = 0;
						}							
					}
					m_recv_index = 0;			
					memset(m_recv_buff,0x00,sizeof(m_recv_buff));
				}
			}
		}
	}
	return 0;
}

int uart_test_page()
{
	int ret =0;
	st_gui_message pmsg;
	unsigned int quitTick = Sys_TimerOpen(60000);	//Timeout exit timer
	UartOpen(APP_COM,115200,UART_DATABIT8,UART_STOPBIT1,UART_NOPARITY);
	gui_post_message(GUI_GUIPAINT, 0 , 0);

	while(1){
		if (Sys_TimerCheck(quitTick) == 0){		// Detection timeout
			ret = READ_CARD_RET_TIMEOVER;	
			break;
		}
		if (gui_get_message(&pmsg, 100) == 0) {
			if (pmsg.message_id == GUI_GUIPAINT){
				gui_begin_batch_paint();
				gui_clear_dc();
				gui_text_out(0,0, "uart test");
				gui_text_out(0, GUI_LINE_TOP(2), "receiving..");	
				gui_end_batch_paint();
			}
			else if (pmsg.message_id == GUI_KEYPRESS){
				if ( pmsg.wparam == GUI_KEY_QUIT ){
					ret =  READ_CARD_RET_CANCEL;
					break;
				}
			}
			else{
				gui_proc_default_msg(&pmsg);	//  Let the system handle some common messages
			}
		}
		else{
			uart_test_proc(0);
			gui_post_message(GUI_GUIPAINT, 0 , 0);
		}		
	}
	UartClose(APP_COM);
	return ret;
}


typedef struct{
	char sRsaKey[2048];
	char sToken[20];
}ST_SecurityData;
void test_flash_api()
{
	ST_SecurityData * sSdata;
	sSdata=(ST_SecurityData *)Util_Malloc(sizeof(ST_SecurityData));
	memset(sSdata,0x00,sizeof(ST_SecurityData));
	Sys_ReadFlashData((char*)sSdata,sizeof(ST_SecurityData));
	memcpy(sSdata->sToken,"12345678901234567890",20);
	memcpy(sSdata->sRsaKey,"\xff",2048);
	Sys_WriteFlashData((char*)sSdata,sizeof(ST_SecurityData));
}
