#pragma once

#include "xGui/inc/xgui_pub.h"
#include "xGui/inc/2ddraw.h"


typedef struct __st_datetime{
	int nYear;				//year
	int nMonth;				//thmon
	int nDay;				//day
	int nHour;				//hour
	int nMinute;			//minute
	int nSecond;			//second
	int m_currentSel;		//Current focus, 0-year, 1-month, 2-day, 3-hour, 4-minute, 5-second
	char firstTimePress;	//Whether the current focus is the first input after getting focus, 0-yes, 1-no
}DATETIME_ST;

int _dateTimeInput_Show(DATETIME_ST * pdt);