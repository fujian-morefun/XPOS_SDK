#include "sdk_showqr.h"
#include "pub/qrencode/QrEncode.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/message.h"
#include "xGui/inc/xgui_key.h"
#include "pub/common/misc/inc/mfmalloc.h"

#include "pub\tracedef.h"
#include "libqr/inc/qr.h"
#include "xGui/inc/xgui_bmp.h"
#include "../usermessage.h"

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
	FREE(bitmap);

	qrDestroy(qr);

	APP_TRACE("qrDestroy nsize = %d\r\n",nsize);

	if ( nsize > 0 )
	{
		*outbitmap = xgui_load_bmp(TEMP,outwidth,&height);
	}
	else{
		
		*outbitmap = 0 ;
		*outwidth = 0;
	}
	//	*outbitmap = bitmap;
	//	*outwidth = lastwidth;

	return 0;
}


void sdk_showQr(const char *qrdata)
{
	int i;
	int msg_ret; 
	MESSAGE pMsg;
	char * bitmap =0;
	int width = 0;
	int ret = 0;
	unsigned int tick1 = osl_GetTick();	
	unsigned int tick2 = osl_GetTick();
	int zoom = 3;
	int left,top;
	
	lcd_set_index(0);

	generate_code( qrdata, &bitmap, &width );


	xgui_BeginBatchPaint();
	xgui_ClearDC();

	left = (xgui_GetWidth() - width * zoom)  / 2;	
	top = (xgui_GetHeight() - width * zoom) / 2;
	xgui_out_bits_zoom(left, top ,(unsigned char *)bitmap , width , width , 0, zoom);	

	xgui_EndBatchPaint();
	
	FREE(bitmap);

	lcd_set_index(1);
	return ;
}
