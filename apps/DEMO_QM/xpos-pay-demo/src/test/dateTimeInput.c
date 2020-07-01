#include "xGui/inc/message.h"
#include "pub/osl/inc/osl_log.h"
#include "xGui/inc/xgui_key.h"
#include "xGui/inc/draw_buf.h"
#include <stdio.h>
#include <xGui/inc/pageproc.h>
#include "dateTimeInput.h"

static void _dateTime_Paint(DATETIME_ST * pdt)
{
	int nFourNumWidth;		//4个数字的宽度
	int nTwoNumWidth;		//2个数字的宽度
	int nTipWidth;			//时间之间提示语的宽度
	int tipTopPos;			//年月日等提示语的起始点
	int tipLeftPos;			//年月日等提示语的起始点
	int textLeftPos;		//文本左起始点
	int nTextHeight;		//文本高度
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

	nFourNumWidth = xgui_GetTextWidth("0000");
	nTwoNumWidth = xgui_GetTextWidth("00");
	nTipWidth = xgui_GetTextWidth("-");
	nTextHeight = xgui_line_height();

//	xgui_GetViewPort(&oldrc);
//	xgui_SetViewPort_RC(&newRc);	//set dc viewport
	
	xgui_SetTextStyle(UTEXT_SOLID);
	xgui_BeginBatchPaint();
	
	//设置背景白，字体黑
	//xgui_SetTextBgColor(0);
	//xgui_SetTextColor(255);
	xgui_ClearDC();

	//处理年月日，以2013年10月11日为例
	for (i = 0; i < 6; ++ i)	{
		if (i == pdt->m_currentSel)		{
			//当前选中项为黑底白字
			xgui_SetTextBgColor(XGUI_COLOR_FORE);
			xgui_SetTextColor(XGUI_COLOR_BACK);
		}

		if (i == 0)		{
			sprintf(buf, "%4d", pdt->nYear);
			textLeftPos = 0;						//2013  放在最左边
			tipTopPos = 0;							//年	放在首行
			tipLeftPos = textLeftPos + nFourNumWidth;		//年	左起始点=2013左起始点+2013占用宽度
		}
		else if (i == 1)		{
			sprintf(buf, "%2d", pdt->nMonth);
			textLeftPos = 0 + nFourNumWidth + nTipWidth;	//10	左起始点=2013左起始点+2013占用宽度+“年”占用宽度
			tipTopPos = 0;									//月	放在首行
			tipLeftPos = textLeftPos + nTwoNumWidth;				//月	左起始点=10左起始点+10占用宽度
		}
		else if (i == 2)		{
			sprintf(buf, "%2d", pdt->nDay);
			textLeftPos = 0 + nFourNumWidth + 2 * nTipWidth + nTwoNumWidth;	//11	左起始点=2013左起始点+2013占用宽度+10占用宽度+“年”“月”占用宽度
			tipTopPos = 0;														//日	首行
			tipLeftPos = textLeftPos + nTwoNumWidth;									//日	左起始点=11左起始点+11占用宽度
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

		xgui_TextOut(textLeftPos, tipTopPos, buf);

		if (i == pdt->m_currentSel)		{
			xgui_SetTextBgColor(XGUI_COLOR_BACK);
			xgui_SetTextColor(XGUI_COLOR_FORE);
		}

		xgui_TextOut(tipLeftPos, tipTopPos, dateTimeTip[i]);
	}

	xgui_ResumeTextStyle();
	xgui_SetTextBgColor(XGUI_COLOR_BACK);
	xgui_SetTextColor(XGUI_COLOR_FORE);
	xgui_Page_OP_Paint("Cancel", "OK");
	xgui_EndBatchPaint();
}

//选中下一个，可循环。选中项切换时，同时设置当前选中项状态为首次接收按键消息
static void _incCurrentSel(DATETIME_ST* pdt)
{
	if (pdt == 0) {
		return;
	}

	pdt->m_currentSel = (pdt->m_currentSel + 1) % 6;
	pdt->firstTimePress = 0;
}

//选中上一个，可循环。选中项切换时，同时设置当前选中项状态为首次接收按键消息
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
			if (pdt->m_currentSel == 0)	//年
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
			else if (pdt->m_currentSel == 1)	//月
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
			else if (pdt->m_currentSel == 2)	//日
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
			else if (pdt->m_currentSel == 3)	//时
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
			else if (pdt->m_currentSel == 4)	//分
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
			else if (pdt->m_currentSel == 5)	//秒
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
	if (pdt->nYear<2000 || pdt->nYear>2099) return 1;		// 年
	if (pdt->nMonth<=0 || pdt->nMonth>12) return 2;		// 月
	if (pdt->nYear % 4 == 0  && pdt->nMonth==2) leap= 1;	// 是闰年的2月
	if (pdt->nDay<=0 || pdt->nDay>(monlen[pdt->nMonth]+leap)) return 3;	//日
	

	return 0;
}


static int dateTime_Key(DATETIME_ST* pdt, int presskey)
{
	switch(presskey) {
	case KEY_UP:case KEY_LEFT:
		_desCurrentSel(pdt);
		_dateTime_Paint(pdt);
		break;
	case KEY_DOWN:case KEY_RIGHT:case KEY_JING:
		_incCurrentSel(pdt);
		_dateTime_Paint(pdt);
		break;
	case KEY_QUIT:
		return -1;
		break;
	case KEY_XING:
		break;
	case KEY_1:	case KEY_2:	case KEY_3:	case KEY_4:	case KEY_5:
	case KEY_6:case KEY_7:case KEY_8:case KEY_9:case KEY_0:
		_dealInputNumKey(pdt, presskey - '0');
		_dateTime_Paint(pdt);
		break;
	case KEY_OK:
		return 1;
		break;
	default:
		break;
	}
	
	return 0;
}
int dateTimeInput_Show(DATETIME_ST * pdt)
{
	int presskey;
	MESSAGE pMsg;
	DATETIME_ST  npdt;
	memcpy(&npdt, pdt, sizeof(DATETIME_ST));
	if (pdt == 0)
	{
		return -1;
	}
	
	_dateTime_Paint(pdt);

	while(1){
		if (xgui_GetMessageWithTime(&pMsg, 100) == MESSAGE_ERR_NO_ERR) {
			if (pMsg.MessageId == XM_GUIPAINT)		{
				_dateTime_Paint(pdt);
			}

			if (pMsg.MessageId == XM_KEYPRESS) {
				presskey = pMsg.WParam;

				switch(presskey) {
				case KEY_0: case KEY_1: case KEY_2: case KEY_3: case KEY_4: 
				case KEY_5: case KEY_6: case KEY_7: case KEY_8: case KEY_9: 
				case KEY_UP: case KEY_DOWN:case KEY_LEFT:case KEY_RIGHT:case KEY_JING:
					dateTime_Key(pdt, presskey);
					break;
				case KEY_OK:
					if(checkDateTime(pdt) != 0)
					{
						xgui_messagebox_show("prompt",  "Input format error", "", "cancel", 100000);
						memcpy(pdt,&npdt,sizeof(DATETIME_ST));
						_dateTime_Paint(pdt);
						break;
					}
					else
						return 	dateTime_Key(pdt, presskey);
					break;
				case KEY_QUIT:
					return -1;
					break;
				default:
					xgui_proc_default_msg(&pMsg);
					break;
				}
			}
			else{
				xgui_proc_default_msg(&pMsg);
			}
		}
	} 
	
	return -1;
}