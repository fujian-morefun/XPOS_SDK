#include "../app_def.h"

//#include "pub/osl/inc/osl_time.h"

#include "driver/uart.h"


static char keybuff[][2] = {
	{'A',3},//2
	{'D',3},//3
	{'G',3},//4
	{'J',3},//5
	{'M',3},//6
	{'P',4},//7
	{'T',3},//8
	{'W',4},//9
};



static char newchar(char oldchar,int keycode)
{
	int i = keycode - GUI_KEY_0 - 2;
	if ( i < 0 ){
		return oldchar;
	}
	else{
		char startchar = keybuff[i][0];
		char charcount = keybuff[i][1];

		if ( keycode == oldchar  ){
			return startchar;
		}
		else{	
			int coffset = (oldchar - startchar) % charcount;
			if ( coffset == charcount - 1 )	{
				return keycode;
			}
			else{
				return startchar + coffset + 1;
			}
		}
	}
}

#define LINE_SIZE		20
#define	LINE_PER_PAGE	4	

int scan_page_proc(char *title, char *buff, int size,  int timeover)
{
	st_gui_message pMsg;
	int len = 0;
	int ret=0;
	unsigned int tick1;
	int state = 0;
	char *msg;
	char tmp[32]={0};


	tick1 = Sys_TimerOpen(timeover);
	len = strlen(buff);

	SYS_TRACE("begtin sacn --------------------");
	gui_post_message(GUI_GUIPAINT, 0 , 0);

	while(1){
		if (timeover > 0)		{
			if(Sys_TimerCheck(tick1) == 0){
				ret = -2;
				break;
			}
		}


		if (gui_get_message(&pMsg, 100) == 0) {

			if (pMsg.message_id == GUI_SCAN_OK) {
				strcpy(buff, (char *)pMsg.wparam);
				len = strlen(buff);
				Util_BuzzerSound(200);
				ret = 0;
				break;
			}
			else if (pMsg.message_id == GUI_GUIPAINT) {
				SYS_TRACE("&&&&&&&&&&&&enter_GUI_GUIPAINT&&&&&&");
				gui_begin_batch_paint();
				gui_set_win_rc();
				gui_clear_dc();

				if(state == 0) msg = "wait scan";
				if(state == 1) msg = "scan...";

				gui_set_title(title);
				gui_textout_line_left(msg,GUI_LINE_TOP(4));
				gui_page_op_paint("Cancel" , "");

				gui_end_batch_paint();
			}
			else if (pMsg.message_id == GUI_KEYPRESS) {
				tick1 = Sys_TimerOpen(timeover);

				if (pMsg.wparam == GUI_KEY_QUIT)	{
					ret = -1;
					break;
				}
				else if (pMsg.wparam == GUI_KEY_F1 || pMsg.wparam == GUI_KEY_F2){
					Sys_scaner_start(0,0);
					state = 1;
					gui_post_message(GUI_GUIPAINT, 0 , 0);
				}
			}
			else{
				gui_proc_default_msg(&pMsg);	
			}
		}

	}	

	Sys_scaner_stop();

	return	ret ;
}

