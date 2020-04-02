#include "sdk_showqr.h"
#include "pub/qrencode/QrEncode.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/message.h"
#include "xGui/inc/xgui_key.h"
#include "pub/common/misc/inc/mfmalloc.h"

#include "pub\tracedef.h"
#include "libqr/inc/qr.h"
#include "xGui/inc/xgui_bmp.h"

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
	APP_TRACE("qrInit\r\n");

	qrAddData(qr, data,datalen );
	APP_TRACE("qrAddData\r\n");
	qrFinalize(qr);
	APP_TRACE("qrFinalize datalen=%d version = %d  mode=%d\r\n" , datalen, qr->param.version , qr->param.mode );

	nsize = 0;
	bitmap = qrGetSymbol(qr,  QR_FMT_BMP,  sep,  mag,  &nsize);
	APP_TRACE("qrGetSymbol nsize=%d\r\n" , nsize);
	if (  nsize > 0 )
	{
		File_WriteBlockByName( TEMP ,0,bitmap,nsize);
	}
	else{
		FREE(bitmap);
	}
	qrDestroy(qr);

	APP_TRACE("qrDestroy nsize = %d\r\n",nsize);

	if ( nsize > 0 )
	{//生成成功
		*outbitmap = xgui_load_bmp(TEMP,outwidth,&height);
	}
	else{
		//生成失败
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
	MESSAGE pMsg;
	char * bitmap = (char *)MALLOC(QR_HEIGHT*QR_HEIGHT/8);
	int width = 0;
	int ret = 0;
	unsigned int tick1 = osl_GetTick();	
	unsigned int tick2 = osl_GetTick();
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
	xgui_PostMessage(XM_GUIPAINT, 0 , 0);  // Send a paint message

	if(width > 0){

		while(1){
			if (osl_CheckTimeover(tick1 , 60000) != 0)	{	// Check page timeout
				ret = -3;
				break;
			}

			msg_ret = xgui_GetMessageWithTime(&pMsg, 500);		// Get the message 
			if(msg_ret == MESSAGE_ERR_NO_ERR){
				if (pMsg.MessageId == XM_GUIPAINT) {			// 	If it is a paint message, draw the page	
					xgui_BeginBatchPaint();
					xgui_ClearDC();
					
					// Calculate barcode position, centered display
					left = (xgui_GetWidth() - width * zoom)  / 2;	
					top = (xgui_GetHeight() - width * zoom) / 2;
					xgui_out_bits(left, top ,(unsigned char *)bitmap , width , width , 0);	
					
					xgui_EndBatchPaint();
				}
				else if (pMsg.MessageId == XM_KEYPRESS){		// Handling key messages
					if(pMsg.WParam == KEY_OK){
						break;
					}
					else if(pMsg.WParam == KEY_QUIT){
						ret = -2;
						break;
					}
				}
				xgui_proc_default_msg(&pMsg);				//  Let the system handle some common messages
			}


		}
	}
	else{

	}
	FREE(bitmap);



	return ;
}
