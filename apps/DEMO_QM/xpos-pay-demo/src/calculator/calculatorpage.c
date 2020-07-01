#include "calculatorpage.h"
#include "calculator.h"

#include "xGui/inc/mainmenu.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/messagedatastruct.h"
#include "xGui/inc/message.h"
#include "xGui/inc/messagebox.h"
#include "xGui/inc/xgui_key.h"
#include "xGui/inc/pageproc.h"
#include "xGui/inc/xgui_bmp.h"






static int cal_paint(calculator *info )
{
	char full[64];

	memset(full,0x00, sizeof(full));
	
	cal_showfull(info, full );
	xgui_TextOut_Line_Right( full ,XGUI_LINE_TOP_0);

	cal_show(info, full);
	xgui_TextOut_Line_Right( full ,XGUI_LINE_TOP_1);

	return 0;
}

static int cal_keypress(calculator *info , unsigned int keycode )
{
	if (keycode>= KEY_0 && keycode <= KEY_9)	
	{
		return cal_addkeycode(info,keycode);
	}
	else if (keycode == KEY_XING)	
	{
		return cal_addkeycode(info,'.');
	}
	else if (keycode == KEY_BACKSPACE)	
	{
		return cal_backspace(info);
	}
	else if (keycode == KEY_PLUS )	
	{
		cal_addop(info,'+');
	}
	else if (keycode == KEY_SUBTRACT )	
	{
		cal_addop(info,'-');
	}
	else if (keycode == KEY_MULTIPLY )	
	{
		cal_addop(info,'*');
	}
	else if (keycode == KEY_DIVISION )	
	{
		cal_addop(info,'/');
	}
	else if (keycode == KEY_EQUAL)
	{
		return cal_compute(info);
	}
	else if (keycode == KEY_MC )
	{
		return cal_memory_clear(info);
	}	
	else if (keycode == KEY_MR )
	{
		return cal_memory_read(info);
	}	
	else if (keycode == KEY_MP )
	{
		return cal_memory_plus(info);
	}	
	else if (keycode == KEY_MS )
	{
		return cal_memory_subtract(info);
	}

	return 1;
}

int calculatorpage(double *result)
{
	int  ret = RET_CAL_NORESULT;

	MESSAGE pMsg;
	calculator info;
	memset( &info,0x00,sizeof(info));


	xgui_PostMessage(XM_GUIPAINT, 0 , 0);
	while(1){
		if (xgui_GetMessageWithTime(&pMsg, 300) == MESSAGE_ERR_NO_ERR) {

			if (pMsg.MessageId == XM_GUIPAINT) {
				xgui_BeginBatchPaint();
				xgui_Clear_Win();
				cal_paint( &info );
				xgui_EndBatchPaint();
			}
			else if (pMsg.MessageId == XM_KEYPRESS) {
				//argot_keyinput(pMsg.WParam);
				if ( pMsg.WParam == KEY_CANCEL)
				{
					break;
				}
				else if ( pMsg.WParam == KEY_OK)
				{
					if (info.setp != step_result )
					{
						cal_compute(&info);
					}

					if( cal_result( &info, result) == 1)	
					{
						ret = RET_CAL_SUCC;
					}
					break;
				}


				cal_keypress( &info, pMsg.WParam);
				xgui_PostMessage(XM_GUIPAINT, 0 , 0);
			}
		}

	}

	return ret;
}

