#include <stdio.h>
#include "dateTimeInput_page.h"
#include "libapi_xpos/inc/libapi_gui.h"
#include "libapi_xpos/inc/libapi_system.h"

typedef struct __st_datetime{
	int nYear;				//year
	int nMonth;				//month
	int nDay;				//date
	int nHour;				//hour
	int nMinute;			//minute
	int nSecond;			//second
	int m_currentSel;		//Current focus, 0-year, 1-month, 2-day, 3-hour, 4-minute, 5-second
	char firstTimePress;	//Whether the current focus is the first input after the focus is acquired, 0-yes, 1-No
}DATETIME_ST;

static int dateTimeInput_Show(DATETIME_ST * pdt);

static void _dateTime_Paint(DATETIME_ST * pdt)
{
	int nFourNumWidth;		//4 digit width
	int nTwoNumWidth;		//2 digit width
	int nTipWidth;			//The width of the prompt between time
	int tipTopPos;			//The starting point of the prompt, such as the year, month, and day.Y
	int tipLeftPos;			//The starting point of the prompt, such as the year, month, and day.X
	int textLeftPos;		//Text start point. X
	int nTextHeight;		//Text height.
	char buf[32] = {0};
	char* dateTimeTip[] = {"-","-", " ", ":", ":", ""};
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



	nFourNumWidth = gui_get_text_width("0000");
	nTwoNumWidth = gui_get_text_width("00");
	nTipWidth = gui_get_text_width("Y");
	nTextHeight = gui_get_text_height("Y");

	gui_begin_batch_paint();
	gui_clear_dc();


	for (i = 0; i < 6; ++ i)	{

		if (i == 0)		{
			sprintf(buf, "%4d", pdt->nYear);
			textLeftPos = 0;						
			tipTopPos = 0;							
			tipLeftPos = textLeftPos + nFourNumWidth;	
		}
		else if (i == 1)		{
			sprintf(buf, "%2d", pdt->nMonth);
			textLeftPos = 0 + nFourNumWidth + nTipWidth;
			tipTopPos = 0;								
			tipLeftPos = textLeftPos + nTwoNumWidth;	
		}
		else if (i == 2)		{
			sprintf(buf, "%2d", pdt->nDay);
			textLeftPos = 0 + nFourNumWidth + 2 * nTipWidth + nTwoNumWidth;	
			tipTopPos = 0;												
			tipLeftPos = textLeftPos + nTwoNumWidth;					
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



		if (i == pdt->m_currentSel)	{
			gui_set_text_bg_color(0xffffff);
			gui_set_text_color(0x000000);
		}

		gui_text_out(textLeftPos, tipTopPos, buf);
		
		if (i == pdt->m_currentSel)	{
			gui_set_text_bg_color(0x000000);
			gui_set_text_color(0xffffff);
		}

		gui_text_out(tipLeftPos, tipTopPos, dateTimeTip[i]);
	}

	gui_end_batch_paint();
}

//Select the next one, which can be recycled. When the selected item is switched, the current selected item status is set to receive the key message for the first time.
static void _incCurrentSel(DATETIME_ST* pdt)
{
	if (pdt == 0) {
		return;
	}

	pdt->m_currentSel = (pdt->m_currentSel + 1) % 6;
	pdt->firstTimePress = 0;
}

//Select the last one, which can be recycled. When the selected item is switched, the current selected item status is set to receive the key message for the first time.
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

	switch(keyValue){
	case 1:	case 2:	case 3:	case 4:	case 5:
	case 6: case 7: case 8: case 9: case 0:	
		if (pdt->m_currentSel == 0){	//year
			if (pdt->firstTimePress == 0){
				pdt->nYear = keyValue;
				pdt->firstTimePress = 1;
			}
			else{
				pdt->nYear  = pdt->nYear * 10 + keyValue;
			}
			if (pdt->nYear > 999){
				_incCurrentSel(pdt);
			}
		}
		else if (pdt->m_currentSel == 1){	//month
			if (pdt->firstTimePress == 0){
				pdt->nMonth = keyValue;
				pdt->firstTimePress = 1;
			}
			else{
				pdt->nMonth  = pdt->nMonth * 10 + keyValue;
				if (pdt->nMonth > 9){
					if(pdt->nMonth > 12){
						pdt->nMonth = 12;
					}						
				}
				if(pdt->nMonth != 0)_incCurrentSel(pdt);
			}
		}
		else if (pdt->m_currentSel == 2){	//date
			if (pdt->firstTimePress == 0){
				pdt->nDay = keyValue;
				pdt->firstTimePress = 1;
			}
			else{
				pdt->nDay  = pdt->nDay * 10 + keyValue;
				if (pdt->nDay > 9){
					if(pdt->nDay > 31){
						pdt->nDay = 31;
					}						
				}
				if(pdt->nDay != 0)	_incCurrentSel(pdt);
			}
		}
		else if (pdt->m_currentSel == 3){	//hour
			if (pdt->firstTimePress == 0){
				pdt->nHour = keyValue;
				pdt->firstTimePress = 1;
			}
			else{
				pdt->nHour  = pdt->nHour * 10 + keyValue;
				if (pdt->nHour > 9){
					if(pdt->nHour > 23)	{
						pdt->nHour = 0;
					}

				}
				_incCurrentSel(pdt);
			}
		}
		else if (pdt->m_currentSel == 4){	//minute
			if (pdt->firstTimePress == 0){
				pdt->nMinute = keyValue;
				pdt->firstTimePress = 1;
			}
			else{
				pdt->nMinute  = pdt->nMinute * 10 + keyValue;
				if (pdt->nMinute > 9){
					if(pdt->nMinute > 59){
						pdt->nMinute = 0;
					}
				}
				_incCurrentSel(pdt);
			}
		}
		else if (pdt->m_currentSel == 5){	//second
			if (pdt->firstTimePress == 0){
				pdt->nSecond = keyValue;
				pdt->firstTimePress = 1;
			}
			else{
				pdt->nSecond  = pdt->nSecond * 10 + keyValue;
				if (pdt->nSecond > 9){
					if(pdt->nSecond > 59){
						pdt->nSecond = 0;
					}
				}
				_incCurrentSel(pdt);
			}
		}
	}
}


static int checkDateTime(DATETIME_ST * pdt)
{
	int monlen[13] ={0,31,28,31,30,31,30,31,31,30,31,30,31};
	int leap=0;
	if (pdt->nYear<2000 || pdt->nYear>2099) return 1;		// year
	if (pdt->nMonth<=0 || pdt->nMonth>12) return 2;		// month
	if (pdt->nYear % 4 == 0  && pdt->nMonth==2) leap= 1;	// It's February in leap year.
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

static int dateTimeInput_Show(DATETIME_ST * pdt)
{
	int presskey;
	st_gui_message pmsg;

	DATETIME_ST  npdt;
	memcpy(&npdt, pdt, sizeof(DATETIME_ST));
	if (pdt == 0)
	{
		return -1;
	}

	gui_post_message(GUI_GUIPAINT, 0 , 0);

	while(1){
		if (gui_get_message(&pmsg, 100) == 0) {
			if (pmsg.message_id == GUI_GUIPAINT)		{
				_dateTime_Paint(pdt);
			}

			if (pmsg.message_id == GUI_KEYPRESS) {
				presskey = pmsg.wparam;

				switch(presskey) {
				case GUI_KEY_0: case GUI_KEY_1: case GUI_KEY_2: case GUI_KEY_3: case GUI_KEY_4: 
				case GUI_KEY_5: case GUI_KEY_6: case GUI_KEY_7: case GUI_KEY_8: case GUI_KEY_9: 
				case GUI_KEY_UP: case GUI_KEY_DOWN:case GUI_KEY_LEFT:case GUI_KEY_RIGHT:case GUI_KEY_JING:
					dateTime_Key(pdt, presskey);
					break;
				case GUI_KEY_OK:
					if(checkDateTime(pdt) != 0)	{
						gui_messagebox_show("prompt",  "Input format error", "", "return", 100000);
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
					gui_proc_default_msg(&pmsg);
					break;
				}
			}
			else{
				gui_proc_default_msg(&pmsg);
			}
		}
	} 

	return -1;
}



static int get_int(char *buff , int size)
{
	char str[16]={0};
	memcpy(str, buff, size);
	return atoi(str);
}

int time_set_page()
{
	int nRet = 0;
	DATETIME_ST dt = {0};
	char str[32]={0};

	Sys_GetDateTime(str);

	dt.nYear = get_int(str, 4);
	dt.nMonth = get_int(str + 4, 2);
	dt.nDay = get_int(str + 6, 2);
	dt.nHour = get_int(str + 8, 2);
	dt.nMinute = get_int(str + 10, 2);
	dt.nSecond = get_int(str + 12, 2);

	nRet = dateTimeInput_Show(&dt);

	if (nRet == 1){
		sprintf(str, "%04d%02d%02d%02d%02d%02d", 
			dt.nYear, dt.nMonth, dt.nDay,dt.nHour,dt.nMinute,dt.nSecond);
		Sys_SetDateTime(str);
	}

	return nRet;
}
