#include "inputcard_page.h"
#include "driver\mf_magtek.h"
#include "xGui\inc\2ddraw.h"
#include "xGui\inc\messagedatastruct.h"
#include "xGui\inc\message.h"
#include "xGui\inc\xgui_key.h"
#include "pub\osl\inc\osl_time.h"


#define IC_CARD_SOCKET	0

// Prompt with card display
static void inputcard_pagepaint(char * title)
{
	xgui_BeginBatchPaint();
	xgui_ClearDC();
	xgui_SetTitle(title);
	xgui_TextOut_Line_Center("Please use the card" , XGUI_LINE_TOP_2 );
	xgui_EndBatchPaint();
}

// Non-contact detection
static int check_rf()
{
	int ret;
	ret = mf_rfid_tcl_open();
	return ret;
}

// Contact card detection
static int check_ic()
{
	int ret = icc_open(IC_CARD_SOCKET);
	ret = icc_present( IC_CARD_SOCKET );
	icc_close( IC_CARD_SOCKET );
	return ret;
}

// Magnetic stripe card detection
static int check_magtek(struct magtek_track_info *trackinfo)
{
	return mf_magtek_read(trackinfo);
}

int inputcard_page_showd(char * title, struct magtek_track_info *trackinfo)
{  
	MESSAGE pMsg;
	unsigned int tick1 = osl_GetTick();
	int timeover = 60000;
	
	mf_magtek_flush();								// Empty the magnetic stripe card buffer
	xgui_PostMessage(XM_GUIPAINT, 0 , 0);
	
	while(1){
		if (osl_CheckTimeover(tick1 ,timeover ) != 0){		// Detection timeout
			return INPUTCARD_RET_TIME_OVER;	
		}

		if (xgui_GetMessageWithTime(&pMsg, 10) == MESSAGE_ERR_NO_ERR) {
			if (pMsg.MessageId == XM_GUIPAINT) {
				inputcard_pagepaint(title);
			}
			else if (pMsg.MessageId == XM_KEYPRESS) {
				if ( pMsg.WParam == KEY_QUIT ){
					return INPUTCARD_RET_QUIT;
				}
				else if(pMsg.WParam == KEY_C){
					return INPUTCARD_RET_RFID;
				}
			}
			else{
				xgui_proc_default_msg(&pMsg);	//  Let the system handle some common messages
			}
		}
		else{
			if(check_magtek(trackinfo) == 1 ){		// Detecting magnetic stripe card
				return INPUTCARD_RET_MAGTEK;
			}
			else if (check_ic() == 1  ){			// Detecting ic card
				return INPUTCARD_RET_ICC;
			}
			else if (check_rf() >=0){				// Detecting non-contact cards
				return INPUTCARD_RET_RFID;
			}
		}		
	}

	return INPUTCARD_RET_QUIT;

}
