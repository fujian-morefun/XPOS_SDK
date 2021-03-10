
#include "app_def.h"

void showbmptest()
{
	int logowidth;
	int logoheight;
	char * pbmp;
	int ret;
	st_gui_message pMsg;

	creat_bmp();
	
	pbmp = gui_load_bmp("data\\test.bmp" , &logowidth , &logoheight);
	if (pbmp != 0){
		gui_clear_win();
		gui_out_bits(20, 10 ,pbmp , logowidth , logoheight , 0);
		Util_Free(pbmp);
	}	
	else{
		gui_messagebox_show( "ShowBmp", "No bmp file!" ,"","Confirm" ,0);
		return;
	}

	while(1){
		ret = gui_get_message(&pMsg, 500);		// Get the message 
		if(ret == 0){
			if (pMsg.message_id == GUI_KEYPRESS){		// Handling key messages
				if(pMsg.wparam == GUI_KEY_OK || pMsg.wparam == GUI_KEY_QUIT){
					break;
				}
			}
			gui_proc_default_msg(&pMsg);				//  Let the system handle some common messages
		}
	}

}

