#include "app_def.h"
#include "pub/qrencode/QrEncode.h"
#include "libqr/inc/qr.h"

#define QR_WIDTH	240
#define QR_HEIGHT	240

#define QRBMP "xxxx\\qr.bmp"


static int generate_code( char *data,char **outbitmap,int *outwidth,int *height )
{

	int version = -1;
	int mode = QR_EM_AUTO;
	int eclevel = QR_ECL_M;
	int masktype = -1;

	int errcode = QR_ERR_NONE;

	char * bitmap = 0;
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
		UFile_WriteBlockByName( QRBMP, 0, bitmap, nsize);
	}
	
	Util_Free(bitmap);

	qrDestroy(qr);

	SYS_TRACE("qrDestroy nsize = %d\r\n",nsize);

	if ( nsize > 0 )
	{
		*outbitmap = gui_load_bmp(QRBMP,outwidth,height);
	}
	else{
		*outbitmap = 0 ;
		*outwidth = 0;
		*height=0;
	}
	return nsize;
}


void showQrTest()
{
	int msg_ret=0;
	st_gui_message pMsg;
	char * bitmap;// = (char *)Util_Malloc(QR_HEIGHT*QR_HEIGHT/8);
	int width = 0;
	int height = 0;
	int ret = 0;
	unsigned int tick1 = Sys_TimerOpen(60000);	
	int zoom =  1;
	int left,top;
	char *data= "test qr code";


	generate_code( data, &bitmap, &width,&height);

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
					zoom = (gui_get_height() - 10) / height;
					// Calculate barcode position, centered display
					left = (gui_get_width() - width * zoom)  / 2;	
				top = (gui_get_height() - height * zoom) / 2;
					gui_out_bits(left, top ,(unsigned char *)bitmap , width , height , zoom);	
					
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
		Util_Free(bitmap);
	}
	else
		gui_messagebox_show( "QR test", "QR generate FAIL!" ,"","Confirm" ,0);

	return ;
}
