#include "inputamount_page.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/message.h"
#include "xGui/inc/xgui_key.h"
#include "input_public.h"
//#include "pub/pub_misc.h"
//#include "normal/upay/base/upay_auto_test.h"
#include <string.h>

static int amt_type;
static void input_PaintFooter0(char*footer)
{
	int textHeight = xgui_GetTextHeight("A");
	xgui_ClearRect(0,XGUI_LINE_TOP_3, XGUI_WIN_WIDTH, textHeight, xgui_GetBgColor());
	xgui_TextOut(0, XGUI_LINE_TOP_3, footer);
}


//Draw the third line, the amount
static void _inputamount_PaintAmount(char* amount)
{
	int textHeight = xgui_GetTextHeight("A");
	int textWidth = xgui_GetTextWidth(amount);
	//RECT oldrc;
	//xgui_GetViewPort(&oldrc);
	//XGUI_SET_WIN_RC;
	xgui_ClearRect(0, XGUI_LINE_TOP_2 , XGUI_WIN_WIDTH , XGUI_LINE_TOP_3, xgui_GetBgColor());
	xgui_TextOut(XGUI_WIN_WIDTH - textWidth - 10, XGUI_LINE_TOP_2, amount);

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
	xgui_BeginBatchPaint();
	xgui_Clear_Win();
	input_PaintTitle(title);
	if (strcmp(title , "CASHBACK") == 0){
		input_PaintHeader("Input Cashback AMT:");	
	}
	else{
		input_PaintHeader("Input the amount:");
	}
	_setAmount(nAmount);
	input_PaintFooter0("Backspace if wrong");

	xgui_EndBatchPaint();
	//xgui_SetViewPort_RC(&oldrc);
}

static long long _keyPressProc(long long nAmount, int maxLength, int presskey)
{
	switch (presskey)
	{
	case KEY_0:
	case KEY_1:
	case KEY_2:
	case KEY_3:
	case KEY_4:
	case KEY_5:
	case KEY_6:
	case KEY_7:
	case KEY_8:
	case KEY_9:
		{
			char buf[32] = {0};
			int bufLen = sprintf(buf, "%lld", nAmount);

			if ( bufLen < maxLength  )
			{
				nAmount = nAmount * 10 + (presskey- KEY_0);
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
	case KEY_BACKSPACE:
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
	static long long amnt_0 = 1;
	MESSAGE pMsg;
	unsigned int quitTick = osl_GetTick();	//Timeout exit timer
	maxLength = maxLength > 12 ? 12 : maxLength;

	_inputamount_PanitAll(title, nAmount);

	while(1){

		//Determine if the timeout has expired
		if (osl_CheckTimeover(quitTick , timeover) != 0)	{
			nAmount = INPUT_INPUT_RET_TIMEOVER;
			break;
		}

		if (xgui_GetMessageWithTime(&pMsg , 10) == MESSAGE_ERR_NO_ERR) {
			quitTick = osl_GetTick();

			if (pMsg.MessageId == XM_GUIPAINT) {
				_inputamount_PanitAll( title,nAmount);
			}
			else if (pMsg.MessageId == XM_KEYPRESS) {
				int presskey = pMsg.WParam;
				if(presskey== KEY_QUIT)
				{
					nAmount = INPUT_INPUT_RET_QUIT;
					break;
				}
				else if(presskey == KEY_OK)
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
				xgui_proc_default_msg(&pMsg);
			}

			quitTick = osl_GetTick();
		}

		osl_Sleep(10);
	}

	return nAmount;
}

