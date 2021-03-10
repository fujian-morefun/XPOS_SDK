
#include "../app_def.h"

static int amt_type;
static void input_PaintFooter0(char*footer)
{
	int textHeight = gui_get_text_height("A");
	gui_clear_rect(0,GUI_LINE_TOP(3), gui_get_width(), textHeight, gui_get_bg_color());
	gui_text_out(0, GUI_LINE_TOP(3), footer);
}


//Draw the third line, the amount
static void _inputamount_PaintAmount(char* amount)
{
	int textHeight = gui_get_text_height("A");
	int textWidth = gui_text_width_ex(amount);
	//RECT oldrc;
	//xgui_GetViewPort(&oldrc);
	//XGUI_SET_WIN_RC;
	xgui_ClearRect(0, GUI_LINE_TOP(2) , gui_get_width() , GUI_LINE_TOP(3), gui_get_bg_color());
	xgui_TextOut(gui_get_width() - textWidth - 10, GUI_LINE_TOP(2), amount);

	//xgui_SetViewPort_RC(&oldrc); 
}
static void _setAmount(long long nAmount)
{
	char buf[32] = {0};
    double famt;
    
    famt = nAmount / 100.00;
	sprintf(buf, "%0.2f", famt);
	_inputamount_PaintAmount(buf);
}

static void _inputamount_PanitAll(char* title, int nAmount)
{
	//RECT oldrc;
	
	//xgui_GetViewPort(&oldrc);
	gui_begin_batch_paint();
	gui_clear_win();
	input_PaintTitle(title);
	if (strcmp(title , "CASHBACK") == 0){
		input_PaintHeader("Input Cashback AMT:");	
	}
	else{
		input_PaintHeader("Input the amount:");
	}
	_setAmount(nAmount);
	input_PaintFooter0("Backspace if wrong");

	gui_end_batch_paint();
	//xgui_SetViewPort_RC(&oldrc);
}

static long long _keyPressProc(long long nAmount, int maxLength, int presskey)
{
	switch (presskey)
	{
	case GUI_KEY_0:
	case GUI_KEY_1:
	case GUI_KEY_2:
	case GUI_KEY_3:
	case GUI_KEY_4:
	case GUI_KEY_5:
	case GUI_KEY_6:
	case GUI_KEY_7:
	case GUI_KEY_8:
	case GUI_KEY_9:
		{
			char buf[32] = {0};
			int bufLen = sprintf(buf, "%lld", nAmount);

			if ( bufLen < maxLength  )
			{
				nAmount = nAmount * 10 + (presskey- GUI_KEY_0);
				_setAmount(nAmount);
				input_PaintFooter0("backspace if wrong");
			}
			else
			{
				sprintf(buf, "amount cannot >%d digit", maxLength);
				input_PaintFooter0(buf);
			}		
		}		
		break;
	case GUI_KEY_BACKSPACE:
		{
			nAmount = nAmount / 10;
			_setAmount(nAmount);
			
			input_PaintFooter0("backspace if wrong");
		}
		break;
	default:
		{
			input_PaintFooter0("Enter correct amount");
		}
		break;
	}

	return nAmount;
}

long long inputamount_page(char* title, int maxLength, int timeover)
{
	long long nAmount = 0;
	long long ntestamt = 255;
	static long long amnt_0 = 1;
	st_gui_message pMsg;
	unsigned int quitTick = Sys_TimerOpen(timeover);	//Timeout exit timer
	maxLength = maxLength > 12 ? 12 : maxLength;

	_inputamount_PanitAll(title, nAmount);

	while(1){

		//Determine if the timeout has expired
		if (Sys_TimerCheck(quitTick) == 0)	{
			nAmount = INPUT_INPUT_RET_TIMEOVER;
			break;
		}

		if (gui_get_message(&pMsg , 10) == 0) {
			quitTick = Sys_TimerOpen(timeover);

			if (pMsg.message_id == GUI_GUIPAINT) {
				_inputamount_PanitAll( title,nAmount);
			}
			else if (pMsg.message_id == GUI_KEYPRESS) {
				int presskey = pMsg.wparam;
				if(presskey== GUI_KEY_QUIT)
				{
					nAmount = INPUT_INPUT_RET_QUIT;
					break;
				}
				else if(presskey == GUI_KEY_OK)
				{
					if (nAmount == 0)
					{
						input_PaintFooter0("amount cannot be 0");
					}
					else
					{
						break;
					}
				}
				else
				{
					nAmount = _keyPressProc(nAmount, maxLength, presskey);
				}
			}
			else{
				gui_proc_default_msg(&pMsg);
			}

			quitTick = Sys_TimerOpen(timeover);
		}

		Sys_Delay(10);
	}

	return nAmount;
}

