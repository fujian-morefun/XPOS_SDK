#pragma once

#include "xGui/inc/xgui_pub.h"
#include "xGui/inc/2ddraw.h"


typedef struct __st_datetime{
	int nYear;				//年
	int nMonth;				//月
	int nDay;				//日
	int nHour;				//时
	int nMinute;			//分
	int nSecond;			//秒
	int m_currentSel;		//当前焦点，0-年，1-月，2-日，3-时，4-分，5-秒
	char firstTimePress;	//当前焦点是否是获取到焦点后第一次输入,0-是，1-否
}DATETIME_ST;

int dateTimeInput_Show(DATETIME_ST * pdt);