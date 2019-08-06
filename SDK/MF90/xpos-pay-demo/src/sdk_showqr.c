#include "sdk_showqr.h"
#include "pub/qrencode/QrEncode.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/message.h"
#include "xGui/inc/xgui_key.h"
#include "pub/common/misc/inc/mfmalloc.h"


#define QR_WIDTH	240
#define QR_HEIGHT	240

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


	qr_info.moudleWidth = 8;		// gain
	qr_info.nLevel = 1;				// Error correction level
	qr_info.nVersion = 0;			// Qr version
	
	memset(bitmap , 0 , QR_HEIGHT*QR_HEIGHT/8);

	width = mfGeneCodePic(data , strlen(data) , &qr_info , bitmap);

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
