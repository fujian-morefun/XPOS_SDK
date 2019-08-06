#include "sdk_img.h"
#include "sdk_print.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/message.h"
#include "xGui/inc/xgui_key.h"
#include "xGui/inc/xgui_bmp.h"
#include "pub/common/misc/inc/mfmalloc.h"

void showbmptest()
{
	int logowidth;
	int logoheight;
	char * pbmp;
	int ret;
	MESSAGE pMsg;

	creat_bmp();
	
	pbmp = xgui_load_bmp("data\\test.bmp" , &logowidth , &logoheight);
	if (pbmp != 0){
		xgui_Clear_Win();
		xgui_out_bits(20, 10 ,pbmp , logowidth , logoheight , 0);
		FREE(pbmp);
	}	

	while(1){
		ret = xgui_GetMessageWithTime(&pMsg, 500);		// Get the message 
		if(ret == MESSAGE_ERR_NO_ERR){
			if (pMsg.MessageId == XM_KEYPRESS){		// Handling key messages
				if(pMsg.WParam == KEY_OK || pMsg.WParam == KEY_QUIT){
					break;
				}
			}
			xgui_proc_default_msg(&pMsg);				//  Let the system handle some common messages
		}
	}

}

