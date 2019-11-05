#include <stdio.h>
#include "xGui/inc/message.h"
#include "pub/osl/inc/osl_log.h"
#include "xGui/inc/xgui_key.h"
#include "xGui/inc/draw_buf.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/mtext.h"
#include "xGui/inc/messagebox.h"
#include "pub/osl/inc/osl_time.h"
#include "libapi_xpos/inc/libapi_system.h"
#include "driver/uart.h"
#include "input_public.h"



#define  APP_TRACE 

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
	int i = keycode - KEY_0 - 2;
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

#ifdef LCD_320_240
	#define LINE_SIZE		20
	#define	LINE_PER_PAGE	4	
#else
	#define LINE_SIZE	16
	#define	LINE_PER_PAGE	2
#endif


int scan_page_proc(char *title, char *buff ,  int min  , int max , int timeover, int scan_time ,int input_mode,int *input_type)
{
	MESSAGE pMsg;
	int len = 0;
	int ret=0;
	unsigned int tick1;
	int state = 0;
	char *msg;
	int it;
	char tmp[32]={0};


	it = 0;	
	tick1 = osl_GetTick();
	len = strlen(buff);



	if(osl_get_is_m69() == 1 ) {
		xgui_PostMessage(XM_KEYPRESS, KEY_F2 , 0);
	}

	xgui_PostMessage(XM_GUIPAINT, 0 , 0);

	while(1){
		if (timeover > 0)		{
			if(osl_CheckTimeover(tick1,timeover) != 0){
				ret = -2;
				break;
			}
		}


		if (xgui_GetMessageWithTime(&pMsg, 100) == MESSAGE_ERR_NO_ERR) {

			if (pMsg.MessageId == XM_SCAN_OK) {
				strcpy(buff, pMsg.WParam);
				len = strlen(buff);
				it = 1; 
				osl_BuzzerSound(200);
				ret = 0;
				break;
			}
			else if (pMsg.MessageId == XM_GUIPAINT) {
				xgui_BeginBatchPaint();
				XGUI_SET_WIN_RC;
				xgui_ClearDC();

				if(state == 0) msg = "wait scan";
				if(state == 1) msg = "scan...";
				
				xgui_SetTitle(title);
				xgui_TextOut_Line_Left(msg,XGUI_LINE_TOP_4);
				xgui_Page_OP_Paint("Cancel" , "");

				xgui_EndBatchPaint();
			}
			else if (pMsg.MessageId == XM_KEYPRESS) {
				tick1 = osl_GetTick();

				if (pMsg.WParam == KEY_QUIT)	{
					ret = -1;
					break;
				}
				else if (pMsg.WParam == KEY_F1 || pMsg.WParam == KEY_F2){
					Sys_scaner_start(0,0);
					state = 1;
					xgui_PostMessage(XM_GUIPAINT, 0 , 0);
				}
			}
			else{
				xgui_proc_default_msg(&pMsg);	
			}
		}

	}	

	Sys_scaner_stop();


	if(input_type != NULL)	*input_type = it; 	
	return	ret ;
}

