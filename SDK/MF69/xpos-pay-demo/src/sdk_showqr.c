#include "sdk_showqr.h"
#include "pub/qrencode/QrEncode.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/message.h"
#include "xGui/inc/xgui_key.h"
#include "pub/common/misc/inc/mfmalloc.h"

#define QR_WIDTH	getQR_WIDTH()
#define QR_HEIGHT	getQR_HEIGHT()

int getQR_WIDTH()
{
	if ( LCD_IS_320_240 ) return 320;
	else if ( LCD_IS_128_128 ) return 128;
	else if ( LCD_IS_120_160 ) return 80;
	else if ( LCD_IS_320_240 ) return 320;
	else return 128;
}

int getQR_HEIGHT()
{
	if ( LCD_IS_320_240 ) return 240;
	else if ( LCD_IS_128_128 ) return 128;
	else if ( LCD_IS_120_160 ) return 80;
	else if ( LCD_IS_240_320 ) return 240;
	else return 128;
}

int showQr(char *amt, char *data)
{
	Param_QR_INFO qr_info;
	//int i;
	//int msg_ret; 
	//MESSAGE pMsg;
	char * bitmap = (char *)MALLOC(QR_HEIGHT*QR_HEIGHT/8);
	//char bitmap[128*128/8] = {0};
	int width = 0;
	int temp = 0;
	int nQr_width = 0;
	int nQr_heith = 0;
	int ret = 0;
	//unsigned int tick1 = osl_GetTick();	
	//unsigned int tick2 = osl_GetTick();
	int zoom = LCD_IS_TFT_SCREEN ? 2 : 1;
	int left,top;
	//char *data= "http://en.morefun-et.com";
	int length = strlen(data);

	nQr_width = xgui_GetWidth();
	nQr_heith = xgui_GetHeight()-xgui_line_height()*2-10;

	if (LCD_IS_320_240)
	{
		qr_info.moudleWidth = 3;
		qr_info.nLevel = 1;
		qr_info.nVersion = 0;	
	}
	else if (LCD_IS_120_160)
	{
		qr_info.moudleWidth = 1; 
		qr_info.nLevel = 0;     
		qr_info.nVersion = 0;  
		mfSetQrSize(48);
	}
	else if (LCD_IS_240_320)
	{
		qr_info.moudleWidth = 3; 
		qr_info.nLevel = 1;     
		qr_info.nVersion = 0; 
	}
	else
	{
		qr_info.moudleWidth = 3;
		qr_info.nLevel = 1;
		qr_info.nVersion = 0;	
	}

	memset(bitmap , 0 , QR_HEIGHT*QR_HEIGHT/8);
	while(qr_info.moudleWidth > 0 && (width <= 0 || width > nQr_heith)){ 
		memset(bitmap , 0 , QR_HEIGHT*QR_HEIGHT/8);
		width = mfGeneCodePic(data , length, &qr_info , bitmap);
		if (LCD_IS_128_128)
		{
			qr_info.moudleWidth --;
			qr_info.nLevel ++;
		}
		else
		{
			qr_info.moudleWidth --;
		}
	}	

	//xgui_PostMessage(XM_GUIPAINT, 0 , 0);

	if(width > 0){

// 		while(1){
// 			if (osl_CheckTimeover(tick1 , 60000) != 0)	{	//判断是否超时退出
// 				ret = -3;
// 				break;
// 			}
// 
// 			msg_ret = xgui_GetMessageWithTime(&pMsg, 500);
// 			if(msg_ret == MESSAGE_ERR_NO_ERR){
// 				if (pMsg.MessageId == XM_GUIPAINT) {
					xgui_BeginBatchPaint();
					xgui_Clear_Win();
					
					xgui_SetTitle(amt);

					if (LCD_IS_120_160)
					{
						temp = width * zoom;
						while(1)
						{ 
							if (temp < nQr_heith)
							{
								zoom++;
								temp = width * zoom;
							} 
							else if (temp == nQr_heith)
							{
								break;
							}
							else
							{
								zoom--;
								temp = width * zoom;
								break;
							}
						}
					} 
					left = (xgui_GetWidth() - width * zoom)  / 2;
      				if (LCD_IS_320_240)
       				{
						top = XGUI_LINE_TOP_1-2; 
     				} 
       				else
       				{
						top = XGUI_LINE_TOP_1+5; 
     				}
					
					xgui_out_bits_zoom(left, top ,(unsigned char *)bitmap , width , width , 0, zoom);	
                                        
					if (LCD_IS_320_240)
					{
						xgui_TextOut_Line_Center("Scan code", XGUI_LINE_TOP_5+15);
					}
					else if (LCD_IS_120_160)
					{
						xgui_TextOut_Line_Center("Scan code", XGUI_LINE_TOP_10);
					}
					else if (LCD_IS_240_320)
					{
						xgui_TextOut_Line_Center("Scan code", XGUI_LINE_TOP_7);
					}					
					else if (osl_get_is_m68())
					{
						xgui_TextOut_Line_Center("Scan code", XGUI_LINE_TOP_5+10);
					}
					else
					{
						xgui_TextOut_Line_Center("Scan code", XGUI_LINE_TOP_8);
					}

					xgui_EndBatchPaint();
// 				}
// 				else if (pMsg.MessageId == XM_KEYPRESS){
// 					if(pMsg.WParam == KEY_OK){
// 						break;
// 					}
// 					else if(pMsg.WParam == KEY_QUIT){
// 						ret = -2;
// 						break;
// 					}
// 				}
// 				xgui_proc_default_msg(&pMsg);
// 			}
// 			if (Rf_Check_CardIsExist() == 0)
// 			{
// 				ret = 2;
// 				xgui_messagebox_show("Prompt","Find a card","","confirm", 3000 );
// 				break;
// 			}		
// 		}
	}
	else{
		xgui_messagebox_show("Prompt","Failed to generate QR code","","confirm", 3000 );
		ret = -1;
	}
	FREE(bitmap);

	return ret;
}

int showQr2(char *title)
{
	Param_QR_INFO qr_info;
	int i;
	int msg_ret; 
	MESSAGE pMsg;
	char * bitmap = (char *)MALLOC(QR_HEIGHT*QR_HEIGHT/8);
	int width = 0;
	int temp = 0;
	int nQr_width = 0;
	int nQr_heith = 0;
	int ret = 0;
	unsigned int tick1 = osl_GetTick();	
	unsigned int tick2 = osl_GetTick();
	int zoom = LCD_IS_TFT_SCREEN ? 2 : 1;
	int left,top;
	char *data= "http://en.morefun-et.com";
	int length = strlen(data);

	nQr_width = xgui_GetWidth();
	nQr_heith = xgui_GetHeight()-xgui_line_height()*2-10;

	if (LCD_IS_320_240)
	{
		qr_info.moudleWidth = 3;
		qr_info.nLevel = 1;
		qr_info.nVersion = 0;	
	}
	else if (LCD_IS_120_160)	
	{
		qr_info.moudleWidth = 1; 
		qr_info.nLevel = 0;     
		qr_info.nVersion = 0;   
		mfSetQrSize(48);
	}
	else if (LCD_IS_240_320)
	{
		qr_info.moudleWidth = 3; 
		qr_info.nLevel = 1;     
		qr_info.nVersion = 0; 
	}
	else
	{
		qr_info.moudleWidth = 4;
		qr_info.nLevel = 1;
		qr_info.nVersion = 0;	
	}

	memset(bitmap , 0 , QR_HEIGHT*QR_HEIGHT/8);
	while(qr_info.moudleWidth > 0 && (width <= 0 || width > nQr_heith)){ 
		memset(bitmap , 0 , QR_HEIGHT*QR_HEIGHT/8);
		width = mfGeneCodePic(data , length, &qr_info , bitmap);
		if (LCD_IS_128_128)
		{
			qr_info.moudleWidth --;
			qr_info.nLevel ++;
		}
		else
		{
			qr_info.moudleWidth --;
		}
	}	

	xgui_PostMessage(XM_GUIPAINT, 0 , 0);

	if(width > 0){

		while(1){
			if (osl_CheckTimeover(tick1 , 60000) != 0)	{	//判断是否超时退出
				ret = -3;
				break;
			}

			msg_ret = xgui_GetMessageWithTime(&pMsg, 500);
			if(msg_ret == MESSAGE_ERR_NO_ERR){
				if (pMsg.MessageId == XM_GUIPAINT) {
					xgui_BeginBatchPaint();
					xgui_Clear_Win();

					xgui_SetTitle(title);

					if (LCD_IS_120_160)
					{
						temp = width * zoom;
						while(1)
						{ 
							if (temp < nQr_heith)
							{
								zoom++;
								temp = width * zoom;
							} 
							else if (temp == nQr_heith)
							{
								break;
							}
							else
							{
								zoom--;
								temp = width * zoom;
								break;
							}
						}
					} 
					left = (xgui_GetWidth() - width * zoom)  / 2;

					if (LCD_IS_320_240)
					{
						top = XGUI_LINE_TOP_1-2; 
					} 
					else
					{
						top = XGUI_LINE_TOP_1+5; 
					}

					xgui_out_bits_zoom(left, top ,(unsigned char *)bitmap , width , width , 0, zoom);	

					if (LCD_IS_320_240)
					{
						xgui_TextOut_Line_Center("Scan code", XGUI_LINE_TOP_5+15);
					}
					else if (LCD_IS_120_160)
					{
						xgui_TextOut_Line_Center("Scan code", XGUI_LINE_TOP_10);
					}
					else if (LCD_IS_240_320)
					{
						xgui_TextOut_Line_Center("Scan code", XGUI_LINE_TOP_7);
					}					
					else if (osl_get_is_m68())
					{
						xgui_TextOut_Line_Center("Scan code", XGUI_LINE_TOP_5+10);
					}
					else
					{
						xgui_TextOut_Line_Center("Scan code", XGUI_LINE_TOP_8);
					}
					xgui_EndBatchPaint();
				}
				else if (pMsg.MessageId == XM_KEYPRESS){
					if(pMsg.WParam == KEY_OK){
						ret = 1;
						break;
					}
					else if(pMsg.WParam == KEY_QUIT){
						ret = -2;
						break;
					}
				}
				xgui_proc_default_msg(&pMsg);
			}
			if (Rf_Check_CardIsExist() == 0)
			{
				ret = 2;
				//xgui_messagebox_show("Prompt","Find a card","","confirm", 1000 );
				break;
			}		
		}
	}
	else{
		xgui_messagebox_show("Prompt","Failed to generate QR code","","confirm", 3000 );
		ret = -1;
	}
	FREE(bitmap);

	return ret;
}
