#include "inputnumberString_page.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/message.h"
#include "xGui/inc/xgui_key.h"
#include "input_public.h"

#include "pub\common\misc\inc\mfmalloc.h"


//绘制第三行，即金额
static void _inputamount_PaintNumber(char* number)
{
	//RECT oldrc;
	//xgui_GetViewPort(&oldrc);
	//XGUI_SET_WIN_RC;
	xgui_ClearRect(0, XGUI_LINE_TOP_2, XGUI_WIN_WIDTH - 1, XGUI_LINE_TOP_3, xgui_GetBgColor());
	xgui_TextOut(0, XGUI_LINE_TOP_2, number);
	//xgui_SetViewPort_RC(&oldrc); 
}


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
	if ( i < 0 )
	{
		return oldchar;
	}
	else
	{
		char startchar = keybuff[i][0];
		char charcount = keybuff[i][1];

		if ( keycode == oldchar  )
		{
			return startchar;
		}
		else
		{	
			int coffset = (oldchar - startchar) % charcount;
			if ( coffset == charcount - 1 )
			{
				return keycode;
			}
			else
			{
				return startchar + coffset + 1;
			}
		}
	}
}


//XM_GUIPAINT lParam 带参数
//0: 整个页面重画
//1~4，分别画对应的行数
int inputNumberString_page(INPUTNUM_ST* inputNumSt)
{
	MESSAGE pMsg;
	int len = 0;
	int ret;
	unsigned int tick1 = osl_GetTick();
	unsigned char *pwdbuff;
	char szFooter[32] = "              ";
	unsigned char lastinputcode = 0x00;
	unsigned int ticklastkeyinput = osl_GetTick();

	

	xgui_PostMessage(XM_GUIPAINT, 0 , 0);
	len = strlen(inputNumSt->outBuff);
	len = len > inputNumSt->maxLength ? inputNumSt->maxLength : len;

	pwdbuff = MALLOC(inputNumSt->maxLength + 1);
	memset(pwdbuff , 0, inputNumSt->maxLength + 1);

	xgui_ClearScreen();
	while(1){

		if (inputNumSt->timeout > 0)		{
			if(osl_CheckTimeover(tick1,inputNumSt->timeout) != 0){
				ret = INPUT_INPUT_RET_TIMEOVER;
				break;
			}
		}

		if (xgui_GetMessageWithTime(&pMsg, 100) == MESSAGE_ERR_NO_ERR) {
			if (pMsg.MessageId == XM_GUIPAINT) {
				switch(pMsg.LParam)
				{
				case 0:
					{
						xgui_BeginBatchPaint();
						input_PaintTitle(inputNumSt->title);
						input_PaintHeader(inputNumSt->header);

						if (inputNumSt->pwType == 0){
							_inputamount_PaintNumber(inputNumSt->outBuff);
						}
						else{
							memset(pwdbuff , '*' , len);
							pwdbuff[len] = 0;
							_inputamount_PaintNumber( pwdbuff);
						}

						if (inputNumSt->showFooter == 1)
						{
							input_PaintFooter(szFooter);
						}
						xgui_EndBatchPaint();
					}
					break;
				case 1:
					input_PaintTitle(inputNumSt->title);
					break;
				case 2:
					input_PaintHeader(inputNumSt->header);
					break;
				case 3:
					{
						if (inputNumSt->pwType == 0){
							_inputamount_PaintNumber(inputNumSt->outBuff);
						}
						else{
							memset(pwdbuff , '*' , len);
							pwdbuff[len] = 0;
							_inputamount_PaintNumber( pwdbuff);
						}
					}
					break;
				case 4:
					if (inputNumSt->showFooter == 1)
					{
						input_PaintFooter(szFooter);
					}
					break;
				}
			}
			else if (pMsg.MessageId == XM_KEYPRESS) {

				if (inputNumSt->argot == 1){
					argot_keyinput(pMsg.WParam);
				}

				if (pMsg.WParam >= KEY_0 && pMsg.WParam <= KEY_9){
					char changed = 0;
					if ( inputNumSt->inputEN == 1)
					{
						if (lastinputcode != KEY_0 && lastinputcode != KEY_1 &&  lastinputcode ==  pMsg.WParam )
						{				
							if ( !osl_CheckTimeover( ticklastkeyinput , 500 ) )
							{//没有超时，更改为其他字符

								inputNumSt->outBuff[len - 1] = newchar(inputNumSt->outBuff[len - 1],pMsg.WParam );
								xgui_PostMessage(XM_GUIPAINT, 0 , 3);
								changed = 1;
							}
						}
					}

					if ( changed == 0 )
					{//未替换字符
						if (len < inputNumSt->maxLength)	{
							inputNumSt->outBuff[len] = pMsg.WParam;
							len ++;
							inputNumSt->outBuff[len] = 0;
							xgui_PostMessage(XM_GUIPAINT, 0 , 3);
						}
						else{
							sprintf(szFooter, "length limit %d", inputNumSt->maxLength); 
							xgui_PostMessage(XM_GUIPAINT, 0 , 4);
						}
					}

					ticklastkeyinput = osl_GetTick();
					lastinputcode = pMsg.WParam;					

				}
				else if (pMsg.WParam == KEY_BACKSPACE)	{
					if (len > 0)	{
						len --;
						inputNumSt->outBuff[len] = 0;
						sprintf(szFooter, "%s", "              ");
						xgui_PostMessage(XM_GUIPAINT, 0 , 3); 
						xgui_PostMessage(XM_GUIPAINT, 0 , 4);
					}
				}
				else if (pMsg.WParam == KEY_OK)	{
					if(len == 0 && inputNumSt->len_null ==1){
						ret = INPUT_INPUT_RET_OK;
						break;
					}
					else if (len <inputNumSt->minLength ){
						sprintf(szFooter, "at least %d", inputNumSt->minLength); 
						xgui_PostMessage(XM_GUIPAINT, 0 , 4);
					}
					else if (len > inputNumSt->maxLength){
						sprintf(szFooter, "not more than %d", inputNumSt->minLength); 
						xgui_PostMessage(XM_GUIPAINT, 0 , 4);
					}
					else{
						ret = INPUT_INPUT_RET_OK;
						break;
					}
				}
				else if (pMsg.WParam == KEY_QUIT)	{
					ret = INPUT_INPUT_RET_QUIT;
					break;
				}
			}

			tick1 = osl_GetTick();

			osl_Sleep(1);
		}

	}	

	FREE(pwdbuff);
	return ret ;
}



int input_pin_page(const char *title, char *outpin)
{
	INPUTNUM_ST input_num ={0};
	char pin[13] = {0};
	int ret;
	long long amt;

	input_num.title = (char*)title;
	input_num.header = "Input password:";
	input_num.timeout = 60000;
	input_num.len_null = 1;
	input_num.minLength = 4;
	input_num.maxLength = 12;
	input_num.outBuff = outpin;
	input_num.argot = 0;
	input_num.pwType = 1;
	input_num.showFooter = 0;

	ret  = inputNumberString_page(&input_num);

	return ret;
}
