#include "pub/osl/inc/osl_time.h"
#include "dateTimeInput.h"
#include "xGui/inc/messagebox.h"
#include <string.h>
#include <stdio.h>


int timeTest()
{
	int nRet = 0;
	//测试数据
	DATETIME_ST testDateTime = {0};
	DATE_TIME_T rtcDateTime = {0};

	//读取当前时间，作为默认时间
	osl_GetDateTime(&rtcDateTime);
	testDateTime.nYear = rtcDateTime.nYear;
	testDateTime.nMonth = rtcDateTime.nMonth;
	testDateTime.nDay = rtcDateTime.nDay;
	testDateTime.nHour = rtcDateTime.nHour;
	testDateTime.nMinute = rtcDateTime.nMinute;
	testDateTime.nSecond = rtcDateTime.nSecond;

	nRet = dateTimeInput_Show(&testDateTime);

	
	if (nRet == 1)
	{
		int msgBoxRet = MSGBOX_RET_QUIT;
		char szTip[128] = {0};
		rtcDateTime.nYear = testDateTime.nYear;
		rtcDateTime.nMonth = testDateTime.nMonth;
		rtcDateTime.nDay = testDateTime.nDay;
		rtcDateTime.nHour = testDateTime.nHour;
		rtcDateTime.nMinute = testDateTime.nMinute;
		rtcDateTime.nSecond = testDateTime.nSecond;

		osl_SetDateTime(&rtcDateTime);
		//保存，并再次从rtc读取显示
		osl_Sleep(50);
		memset(&rtcDateTime, 0x00, sizeof(DATE_TIME_T));
		osl_GetDateTime(&rtcDateTime);

		sprintf(szTip, "New Time:\n%d-%d-%d \n%d:%d:%d", rtcDateTime.nYear, rtcDateTime.nMonth, rtcDateTime.nDay, rtcDateTime.nHour, rtcDateTime.nMinute, rtcDateTime.nSecond);
		msgBoxRet = xgui_messagebox_show("" ,szTip, "", "OK", 10000);

		nRet = (msgBoxRet == MSGBOX_RET_OK ? 1 : 0);
	}

	return nRet;
}
