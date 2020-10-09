#include "sdk_pay.h"

#include "libapi_xpos/inc/libapi_system.h"
#include "libapi_xpos/inc/libapi_gui.h"
#include "libapi_xpos/inc/libapi_util.h"
#include "pub/code/Unicode.h"

#define QR_HEIGHT	64

static void sdk_text_out_center(int top , char * msg)
{
	int left = (gui_get_width() -  gui_get_text_width(msg)) / 2;
	gui_text_out(left, top,  msg);
}


int pay_start( char *amt)
{
	Util_QR_INFO qr_info;
	int i;
	int msg_ret; 
	st_gui_message pmsg;
	char * bitmap = (char *)malloc(QR_HEIGHT*QR_HEIGHT/8);
	int width = 0;
	int temp = 0;
	int nQr_width = 0;
	int nQr_heith = 0;
	int ret = 0;
	unsigned int tick1 = Sys_TimerOpen(60000);
	unsigned int tick2 = Sys_TimerOpen(60000);
	int zoom;
	int left,top;
	char *data= "http://en.morefun-et.com";
	int length = strlen(data);
	char *title = "pay";
	int keycode;
	char line1[64];

	qr_info.moudleWidth = 1;		// gain
	qr_info.nLevel = 1;				// Error correction level
	qr_info.nVersion = 0;			// Qr version


	//Play_Voice("Please scan the code");

	memset(bitmap , 0 , QR_HEIGHT*QR_HEIGHT/8);

	width = Util_GeneCodePic(data , strlen(data) , &qr_info , bitmap);
	gui_post_message(GUI_GUIPAINT, 0 , 0);  // Send a paint message

	Sys_scaner_open();			// Open the scanning device
	Sys_scaner_start();

	while(1){
		if (Sys_TimerCheck(tick1) == 0)	{	// Check page timeout
			ret = -3;
			printf("timeout \r\n");
			break;
		}

		msg_ret = gui_get_message(&pmsg, 500);		// Get the message 

		if(msg_ret == 0){
			if (pmsg.message_id == GUI_GUIPAINT) {			// 	If it is a paint message, draw the page	
				
				lcd_set_index(0);	// lcd0 480*320
				gui_begin_batch_paint();
				gui_clear_dc();
				if(width > 0) {
					zoom = (gui_get_height() - 50) / width;
					left = 30;	//(gui_get_width() - width * zoom)  / 2;	
					top = (gui_get_height() - width * zoom) / 2;
					gui_out_bits_zoom(left, top,(unsigned char *)bitmap , width , width , 0, zoom);	
				}
				
				
				gui_text_out(320, 60,  G2U("Amount:"));
				gui_text_out(320, 90,  amt);
				gui_text_out(320, 120,  G2U("Please scan"));
				gui_text_out(320, 150,  G2U("Or swipe"));
				

				gui_end_batch_paint();

				lcd_set_index(1);
				gui_begin_batch_paint();
				gui_clear_dc();
				sprintf(line1, "Amount:%s", amt);
				sdk_text_out_center(2,  G2U(line1));
				sdk_text_out_center(18, G2U("swipe the card"));
				gui_end_batch_paint();
			}
			else if (pmsg.message_id == GUI_KEYPRESS){		// Handling key messages
				keycode = pmsg.wparam;
				if(keycode == GUI_KEY_OK){
					ret = 1;
					break;
				}
				else if(pmsg.wparam == GUI_KEY_QUIT){
					ret = -2;
					break;
				}
			}
			else if(pmsg.message_id == GUI_SCAN_OK){
				ret = 2;
				//gui_messagebox_show("", pmsg.wparam, "" , "ok", 0);	
				break;
			}
			else{
				gui_proc_default_msg(&pmsg);				//  Let the system handle some common messages
			}
			
		}

		if (Rf_Check_CardIsExist() == 0){
			ret = 2;
			//xgui_messagebox_show("Prompt","Find a card","","confirm", 1000 );
			break;
		}		
	}

	free(bitmap);

	Sys_scaner_stop();
	Sys_scaner_close();			// Close the scanning device

	return ret;
}



void sdk_show_msg(int mode)
{
	gui_begin_batch_paint();
	gui_clear_dc();

	sdk_text_out_center(8,  G2U("Communicating..."));

	gui_end_batch_paint();
}

void sdk_pay(int key)
{
	int ret =0;
	double result;
	char amt[32]={0};
	char line1[64]={0};

	ret = calculatorpage2(&result, key, "");
	if(ret == 0){
		sprintf(amt,"%0.2f", result);
		ret = pay_start(amt);
		if(ret >= 0){
			Util_BuzzerSound(50);
			sdk_show_msg(ret);
			osl_Sleep(1000);
			sprintf(line1,"Amount:%s", amt);
			//Play_Voice("payment successful");
			gui_messagebox_show(G2U(line1), G2U("Payment successful"), "", "confirm", 1000);
		}	
	}

}