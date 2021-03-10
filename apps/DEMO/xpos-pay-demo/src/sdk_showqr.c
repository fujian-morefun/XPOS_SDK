#include "app_def.h"
#include "pub/qrencode/QrEncode.h"
#include "libqr/inc/qr.h"

#define QR_WIDTH	240
#define QR_HEIGHT	240



int generate_code( char *data,char **outbitmap,int *outwidth  )
{
#define TEMP "xxxx\\qr.tmp"

	int version = -1;
	int mode = QR_EM_AUTO;
	int eclevel = QR_ECL_M;
	int masktype = -1;

	int errcode = QR_ERR_NONE;
	int has_data = 0;

	char * bitmap = 0;
	int width = 0;
	int height = 0;
	int datalen;
	int nsize = 0;
	int sep = 1;
	int mag=8;

	QRCode *qr = 0 ;

	datalen = strlen(data);

	qr = qrInit(version, mode, eclevel, masktype, &errcode);
	SYS_TRACE("qrInit\r\n");

	qrAddData(qr, data,datalen );
	SYS_TRACE("qrAddData\r\n");
	qrFinalize(qr);
	SYS_TRACE("qrFinalize datalen=%d version = %d  mode=%d\r\n" , datalen, qr->param.version , qr->param.mode );

	nsize = 0;
	bitmap = qrGetSymbol(qr,  QR_FMT_BMP,  sep,  mag,  &nsize);
	SYS_TRACE("qrGetSymbol nsize=%d\r\n" , nsize);
	if (  nsize > 0 )
	{
		File_WriteBlockByName( TEMP ,0,bitmap,nsize);
	}
	else{
		Util_Free(bitmap);
	}
	qrDestroy(qr);

	SYS_TRACE("qrDestroy nsize = %d\r\n",nsize);

	if ( nsize > 0 )
	{//??????
		*outbitmap = gui_load_bmp(TEMP,outwidth,&height);
	}
	else{
		//???????
		*outbitmap = 0 ;
		*outwidth = 0;
	}
	//	*outbitmap = bitmap;
	//	*outwidth = lastwidth;

	return 0;
}


void showQrTest()
{
	Param_QR_INFO qr_info;
	int i;
	int msg_ret; 
	st_gui_message pMsg;
	char * bitmap = (char *)Util_Malloc(QR_HEIGHT*QR_HEIGHT/8);
	int width = 0;
	int ret = 0;
	unsigned int tick1 = Sys_TimerOpen(60000);	
	//unsigned int tick2 = osl_GetTick();
	int zoom =  1;
	int left,top;
	char *data= "test qr code";

#define USELIBQR
#ifndef USELIBQR
	qr_info.moudleWidth = 8;		// gain
	qr_info.nLevel = 1;				// Error correction level
	qr_info.nVersion = 0;			// Qr version
	
	memset(bitmap , 0 , QR_HEIGHT*QR_HEIGHT/8);

	width = mfGeneCodePic(data , strlen(data) , &qr_info , bitmap);

#else
	generate_code( data, &bitmap, &width );
#endif
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
					gui_out_bits(left, top ,(unsigned char *)bitmap , width , width , 0);	
					
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



	return ;
}
