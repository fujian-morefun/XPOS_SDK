#include "../app_def.h"
#include "dateTimeInput.h"



static void _dateTime_Paint(DATETIME_ST * pdt)
{
	int nFourNumWidth;		//4 number width
	int nTwoNumWidth;		//2 number width
	int nTipWidth;			//Prompt width between time
	int tipTopPos;			//The top starting point of the year, month, and day prompts
	int tipLeftPos;			//The left starting point of the year, month, and day prompts
	int textLeftPos;		//Left starting point of text
	int nTextHeight;		//Text height
	char buf[32] = {0};
	char* dateTimeTip[] = {"-","-", "  ", ":", ":", "  "};
//	RECT oldrc;
//	RECT newRc;
	int i = 0;

	if (pdt == 0) {
		return;
	}
	
//	newRc.left = 0;
//	newRc.top  = 0;
//	newRc.right  = xgui_GetWidth() - 1;
//	newRc.bottom = xgui_GetHeight() - 1;

	nFourNumWidth = gui_text_width_ex("0000");
	nTwoNumWidth = gui_text_width_ex("00");
	nTipWidth = gui_text_width_ex("-");
	nTextHeight = xgui_line_height();

//	xgui_GetViewPort(&oldrc);
//	xgui_SetViewPort_RC(&newRc);	//set dc viewport
	
	gui_settextstyle(UTEXT_SOLID);
	gui_begin_batch_paint();
	
	//Set background white, font black
	//xgui_SetTextBgColor(0);
	//xgui_SetTextColor(255);
	gui_clear_dc();

	//Processing date, taking October 11, 2013 as an example
	for (i = 0; i < 6; ++ i)	{
		if (i == pdt->m_currentSel)		{
			//The currently selected item is white on a black background
			gui_set_text_bg_color(XGUI_COLOR_FORE);
			gui_set_text_color(XGUI_COLOR_BACK);
		}

		if (i == 0)		{
			sprintf(buf, "%4d", pdt->nYear);
			textLeftPos = 0;						//2013  On the far left
			tipTopPos = 0;							//Year  On the first line
			tipLeftPos = textLeftPos + nFourNumWidth;		//Year		Left Starting Point = 2013 Left Starting Point + 2013 Occupied Width
		}
		else if (i == 1)		{
			sprintf(buf, "%2d", pdt->nMonth);
			textLeftPos = 0 + nFourNumWidth + nTipWidth;	//10	Left starting point = 2013 left starting point + 2013 occupation width + "year" occupation width
			tipTopPos = 0;									//Month On the first line
			tipLeftPos = textLeftPos + nTwoNumWidth;		//Month Left Starting Point = 10 Left Starting Point + 10 Occupied Width
		}
		else if (i == 2)		{
			sprintf(buf, "%2d", pdt->nDay);
			textLeftPos = 0 + nFourNumWidth + 2 * nTipWidth + nTwoNumWidth;	//11	Left starting point = 2013 left starting point + 2013 occupation width + 10 occupation width + "year" "month" occupation width
			tipTopPos = 0;													//Day	On the first line
			tipLeftPos = textLeftPos + nTwoNumWidth;						//Day	Left starting point = 11 Left starting point + 11 Occupied width
		}
		else if (i == 3)		{
			sprintf(buf, "%4d", pdt->nHour);
			textLeftPos = 0;
			tipTopPos = 0 + nTextHeight;
			tipLeftPos = textLeftPos + nFourNumWidth;
		}
		else if (i == 4)		{
			sprintf(buf, "%2d", pdt->nMinute);
			textLeftPos = 0 + nFourNumWidth + nTipWidth;
			tipTopPos = 0 + nTextHeight;
			tipLeftPos = textLeftPos + nTwoNumWidth;
		}
		else if (i == 5)		{
			sprintf(buf, "%2d", pdt->nSecond);
			textLeftPos = 0 + nFourNumWidth + 2 * nTipWidth + nTwoNumWidth;
			tipTopPos = 0 + nTextHeight;
			tipLeftPos = textLeftPos + nTwoNumWidth;
		}

		gui_text_out(textLeftPos, tipTopPos, buf);

		if (i == pdt->m_currentSel)		{
			gui_set_text_bg_color(XGUI_COLOR_BACK);
			gui_set_text_color(XGUI_COLOR_FORE);
		}

		gui_text_out(tipLeftPos, tipTopPos, dateTimeTip[i]);
	}

	xgui_ResumeTextStyle();
	gui_set_text_bg_color(XGUI_COLOR_BACK);
	gui_set_text_color(XGUI_COLOR_FORE);
	gui_page_op_paint("cancel", "confirm");
	gui_end_batch_paint();
}

//Select the next one to cycle. When the selected item is switched, it also sets the status of the currently selected item to receive key messages for the first time.
static void _incCurrentSel(DATETIME_ST* pdt)
{
	if (pdt == 0) {
		return;
	}

	pdt->m_currentSel = (pdt->m_currentSel + 1) % 6;
	pdt->firstTimePress = 0;
}

//Select the previous one to cycle. When the selected item is switched, it also sets the status of the currently selected item to receive key messages for the first time.
static void _desCurrentSel(DATETIME_ST* pdt)
{
	if (pdt == 0) {
		return;
	}

	-- pdt->m_currentSel;

	if (pdt->m_currentSel < 0)
	{
		pdt->m_currentSel = 5;
	}

	pdt->firstTimePress = 0;
}

static void _dealInputNumKey(DATETIME_ST* pdt, int keyValue)
{
	if (pdt == 0) {
		return;
	}

	switch(keyValue)
	{
	case 1:	case 2:	case 3:	case 4:	case 5:
	case 6: case 7: case 8: case 9: case 0:
		{
			if (pdt->m_currentSel == 0)	//year
			{
				if (pdt->firstTimePress == 0)
				{
					pdt->nYear = keyValue;
					pdt->firstTimePress = 1;
				}
				else
				{
					pdt->nYear  = pdt->nYear * 10 + keyValue;
				}

				if (pdt->nYear > 999)
				{
					_incCurrentSel(pdt);
				}
			}
			else if (pdt->m_currentSel == 1)	//month
			{
				if (pdt->firstTimePress == 0)
				{
					pdt->nMonth = keyValue;
					pdt->firstTimePress = 1;
				}
				else
				{
					pdt->nMonth  = pdt->nMonth * 10 + keyValue;
					if (pdt->nMonth > 9)
					{
						if(pdt->nMonth > 12)
						{
							pdt->nMonth = 12;
						}						
					}
					if(pdt->nMonth != 0)
						_incCurrentSel(pdt);
				}

			
			}
			else if (pdt->m_currentSel == 2)	//day
			{
				if (pdt->firstTimePress == 0)
				{
					pdt->nDay = keyValue;
					pdt->firstTimePress = 1;
				}
				else
				{
					pdt->nDay  = pdt->nDay * 10 + keyValue;

					if (pdt->nDay > 9)
					{
						if(pdt->nDay > 31)
						{
							pdt->nDay = 31;
						}						
					}
					if(pdt->nDay != 0)
						_incCurrentSel(pdt);

				}

				
			}
			else if (pdt->m_currentSel == 3)	//hour
			{
				if (pdt->firstTimePress == 0)
				{
					pdt->nHour = keyValue;
					pdt->firstTimePress = 1;
				}
				else
				{
					pdt->nHour  = pdt->nHour * 10 + keyValue;
					if (pdt->nHour > 9)
					{
						if(pdt->nHour > 23)
						{
							pdt->nHour = 0;
						}

					}
					//if(pdt->nHour !=)
					_incCurrentSel(pdt);
				}

			
			}
			else if (pdt->m_currentSel == 4)	//minute
			{
				if (pdt->firstTimePress == 0)
				{
					pdt->nMinute = keyValue;
					pdt->firstTimePress = 1;
				}
				else
				{
					pdt->nMinute  = pdt->nMinute * 10 + keyValue;
					if (pdt->nMinute > 9)
					{
						if(pdt->nMinute > 59)
						{
							pdt->nMinute = 0;
						}
						
					}
					_incCurrentSel(pdt);
				}

				
			}
			else if (pdt->m_currentSel == 5)	//second
			{
				if (pdt->firstTimePress == 0)
				{
					pdt->nSecond = keyValue;
					pdt->firstTimePress = 1;
				}
				else
				{
					pdt->nSecond  = pdt->nSecond * 10 + keyValue;
					if (pdt->nSecond > 9)
					{
						if(pdt->nSecond > 59)
						{
							pdt->nSecond = 0;
						}
					
					}
						_incCurrentSel(pdt);
				}

				
			}
		}
	}
}


static int checkDateTime(DATETIME_ST * pdt)
{
	int monlen[13] ={0,31,28,31,30,31,30,31,31,30,31,30,31};
	int leap=0;
	if (pdt->nYear<2000 || pdt->nYear>2099) return 1;		// year
	if (pdt->nMonth<=0 || pdt->nMonth>12) return 2;			// month
	if (pdt->nYear % 4 == 0  && pdt->nMonth==2) leap= 1;	// It's February of the following year
	if (pdt->nDay<=0 || pdt->nDay>(monlen[pdt->nMonth]+leap)) return 3;	//day
	

	return 0;
}


static int dateTime_Key(DATETIME_ST* pdt, int presskey)
{
	switch(presskey) {
	case GUI_KEY_UP:case GUI_KEY_LEFT:
		_desCurrentSel(pdt);
		_dateTime_Paint(pdt);
		break;
	case GUI_KEY_DOWN:case GUI_KEY_RIGHT:case GUI_KEY_JING:
		_incCurrentSel(pdt);
		_dateTime_Paint(pdt);
		break;
	case GUI_KEY_QUIT:
		return -1;
		break;
	case GUI_KEY_XING:
		break;
	case GUI_KEY_1:	case GUI_KEY_2:	case GUI_KEY_3:	case GUI_KEY_4:	case GUI_KEY_5:
	case GUI_KEY_6:case GUI_KEY_7:case GUI_KEY_8:case GUI_KEY_9:case GUI_KEY_0:
		_dealInputNumKey(pdt, presskey - '0');
		_dateTime_Paint(pdt);
		break;
	case GUI_KEY_OK:
		return 1;
		break;
	default:
		break;
	}
	
	return 0;
}
int _dateTimeInput_Show(DATETIME_ST * pdt)
{
	int presskey;
	st_gui_message pMsg;
	DATETIME_ST  npdt;
	memcpy(&npdt, pdt, sizeof(DATETIME_ST));
	if (pdt == 0)
	{
		return -1;
	}
	
	_dateTime_Paint(pdt);

	while(1){
		if (gui_get_message(&pMsg, 100) == 0) {
			if (pMsg.message_id == GUI_GUIPAINT)		{
				_dateTime_Paint(pdt);
			}

			if (pMsg.message_id == GUI_KEYPRESS) {
				presskey = pMsg.wparam;

				switch(presskey) {
				case GUI_KEY_0: case GUI_KEY_1: case GUI_KEY_2: case GUI_KEY_3: case GUI_KEY_4: 
				case GUI_KEY_5: case GUI_KEY_6: case GUI_KEY_7: case GUI_KEY_8: case GUI_KEY_9: 
				case GUI_KEY_UP: case GUI_KEY_DOWN:case GUI_KEY_LEFT:case GUI_KEY_RIGHT:case GUI_KEY_JING:
					dateTime_Key(pdt, presskey);
					break;
				case GUI_KEY_OK:
					if(checkDateTime(pdt) != 0)
					{
						gui_messagebox_show("prompt",  "Input format error", "", "cancel", 100000);
						memcpy(pdt,&npdt,sizeof(DATETIME_ST));
						_dateTime_Paint(pdt);
						break;
					}
					else
						return 	dateTime_Key(pdt, presskey);
					break;
				case GUI_KEY_QUIT:
					return -1;
					break;
				default:
					gui_proc_default_msg(&pMsg);
					break;
				}
			}
			else{
				gui_proc_default_msg(&pMsg);
			}
		}
	} 
	
	return -1;
}