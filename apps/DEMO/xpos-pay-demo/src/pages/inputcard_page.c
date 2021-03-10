#include "../app_def.h"
#include "driver\mf_magtek.h"

//#include "pub\osl\inc\osl_time.h"


#define IC_CARD_SOCKET	0

// Prompt with card display
static void inputcard_pagepaint(char * title)
{
	gui_begin_batch_paint();
	gui_clear_dc();
	gui_set_title(title);
	gui_textout_line_center("Please use the card" , GUI_LINE_TOP(2) );
	gui_end_batch_paint();
}





int inputcard_page_showd(char * title, card_magtek_track_info *trackinfo, int timeover)
{  
	st_gui_message pMsg;
	unsigned int tick1 = Sys_TimerOpen(timeover);
	int nret=0;
	Sys_magtek_open();
	card_magtek_flush();								// Empty the magnetic stripe card buffer
	gui_post_message(GUI_GUIPAINT, 0 , 0);
	
	while(1){
		if (Sys_TimerCheck(tick1) == 0){		// Detection timeout
			nret = READ_CARD_RET_TIMEOVER;	
			break;
		}

		if (xgui_GetMessageWithTime(&pMsg, 10) == 0) {
			if (pMsg.message_id == GUI_GUIPAINT) {
				inputcard_pagepaint(title);
			}
			else if (pMsg.message_id == GUI_KEYPRESS) {
				if ( pMsg.wparam == GUI_KEY_QUIT ){
					nret = READ_CARD_RET_CANCEL;
					break;
				}
			}
			else{
				gui_proc_default_msg(&pMsg);	//  Let the system handle some common messages
			}
		}
		else{
			if(card_MagStripeDetect(trackinfo) == 0){		// Detecting magnetic stripe card
				nret = READ_CARD_RET_MAGNETIC;
				break;
			}
			else if (Icc_CardInsertDetect() == 0){			// Detecting ic card
				nret = READ_CARD_RET_IC;
				break;
			}
			else if (Icc_CardRfDetect()==0){				// Detecting non-contact cards
				nret = READ_CARD_RET_RF;
				break;
			}
		}		
	}
	Sys_magtek_close();
	return nret;
}
