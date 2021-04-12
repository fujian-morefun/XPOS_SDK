#include "app_def.h"
#include "pub/qrencode/QrEncode.h"
#include "libqr/inc/qr.h"

#define QR_WIDTH	240
#define QR_HEIGHT	240



int generate_code(const char *data,char **outbitmap,int *outwidth  )
{
#define TEMP "xxxx\\qr.tmp"

	int version = 13;
	int mode = QR_EM_AUTO;
	int eclevel = QR_ECL_Q;
	int masktype = -1;

	int errcode = QR_ERR_NONE;
	int has_data = 0;

	char * bitmap = 0;
	int width = 0;
	int height = 0;
	int datalen;
	int nsize = 0;
	int sep = 1;
	int mag=1;

	QRCode *qr = 0 ;

	//strcpy(data,"1ABCDEFGHIJKLMNOPQRSTUVWXYZ2ABCDEFGHIJKLMNOPQRSTUVWXYZ3ABCDEFGHIJKLMNOPQRSTUVWXYZ4ABCDEFGHIJKLMNOPQRSTUVWXYZ5ABCDEFGHIJKLMNOPQRSTUVWXYZ6ABCDEFGHIJKLMNOPQRSTUVWXYZ7ABCDEFGHIJKLMNOPQRSTUVWXYZ8ABCDEFGHIJKLMNOPQRSTUVWXYZ9ABCDEFGHIJKLMNOPQRSTUVWXYZ10ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	datalen = strlen(data);

	qr = qrInit(version, mode, eclevel, masktype, &errcode);
	//APP_TRACE("qrInit\r\n");

	qrAddData(qr, data,datalen );
	//APP_TRACE("qrAddData\r\n");
	qrFinalize(qr);
	//APP_TRACE("qrFinalize datalen=%d version = %d  mode=%d\r\n" , datalen, qr->param.version , qr->param.mode );

	nsize = 0;
	bitmap = qrGetSymbol(qr,  QR_FMT_BMP,  sep,  mag,  &nsize);
	//APP_TRACE("qrGetSymbol nsize=%d\r\n" , nsize);
	if (  nsize > 0 )
	{
		File_WriteBlockByName( TEMP ,0,bitmap,nsize);
	}
	Util_Free(bitmap);

	qrDestroy(qr);

	//APP_TRACE("qrDestroy nsize = %d\r\n",nsize);

	if ( nsize > 0 )
	{
		*outbitmap = gui_load_bmp(TEMP,outwidth,&height);
	}
	else{
		
		*outbitmap = 0 ;
		*outwidth = 0;
	}
	//	*outbitmap = bitmap;
	//	*outwidth = lastwidth;

	return 0;
}

void sdk_showQr()
{
	Param_QR_INFO qr_info;
	int i;
	int msg_ret; 
	st_gui_message pMsg;
	char * bitmap = (char *)Util_Malloc(QR_HEIGHT*QR_HEIGHT/8);
	int width = 0;
	int ret = 0;
	unsigned int tick1 = Sys_TimerOpen(60000);	
	int zoom =  3;
	int left,top;
	char qrdata[128] ={0};
	{//input amount by calculator
		double result;
		char code[64]={0};
		char amt[16]={0};
		int ret;
		char msg[128];
		char *title = "Code Pay";
		long long namt = 0;

		ret = calculatorpage2(&result,0, "");
		if(ret != 0)
		{
			return;
		}

		sprintf(qrdata,"Amount:%0.2f|Merchan id:123456789", result);
		{
			Sys_lcd_set_index(1);
			gui_begin_batch_paint();	
			gui_clear_dc();									
			gui_textout_line_center("wait scan ",GUI_LINE_TOP(1));
			gui_end_batch_paint();
			Sys_lcd_set_index(0);
		}		
	}
	
	Sys_lcd_set_index(0);
	generate_code( qrdata, &bitmap, &width );
	gui_post_message(GUI_GUIPAINT, 0 , 0);  // Send a paint message

	if(width > 0){

		while(1){
			if (Sys_TimerCheck(tick1) == 0)	{	// Check page timeout
				ret = -3;
				break;
			}

			msg_ret = gui_get_message(&pMsg, 500);		// Get the message 
			if(msg_ret == 0){
				if (pMsg.message_id == GUI_GUIPAINT) {			// 	If it is a paint message, draw the page	
					gui_begin_batch_paint();
					gui_clear_dc();

					// Calculate barcode position, centered display
					left = (gui_get_width() - width * zoom)  / 2;	
					top = (gui_get_height() - width * zoom) / 2;
					gui_out_bits_zoom(left, top ,(unsigned char *)bitmap , width , width , 0,zoom);	
					gui_textout_line_right("confirm", GUI_LINE_TOP(8));
					gui_end_batch_paint();
				}
				else if (pMsg.message_id == GUI_KEYPRESS){		// Handling key messages
					if(pMsg.wparam == GUI_KEY_OK){
						break;
					}
					else if(pMsg.wparam == GUI_KEY_QUIT){
						ret = -2;
						break;
					}
				}
				gui_proc_default_msg(&pMsg);				//  Let the system handle some common messages
			}
		}
	}
	else{

	}
	Util_Free(bitmap);
	Sys_lcd_set_index(1);
	main_page_lcd0_paint();
	return ;
}


