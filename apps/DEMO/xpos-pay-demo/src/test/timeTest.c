#include "../app_def.h"
#include "dateTimeInput.h"



int timeTest()
{
	int nRet = 0;
	DATETIME_ST testDateTime = {0};
	char rtcDateTime[255] = {0};

	//Read the current time as the default time
	Sys_GetDateTime(rtcDateTime);
	sscanf(rtcDateTime , "%04d%02d%02d%02d%02d%02d" , 
		&testDateTime.nYear , &testDateTime.nMonth , &testDateTime.nDay,
		&testDateTime.nHour , &testDateTime.nMinute , &testDateTime.nSecond);

	nRet = _dateTimeInput_Show(&testDateTime);

	
	if (nRet == 1)
	{
		int msgBoxRet = 2;
		char szTip[128] = {0};
		sprintf(szTip , "%d%02d%02d%02d%02d%02d" , 
		testDateTime.nYear , testDateTime.nMonth , testDateTime.nDay,
		testDateTime.nHour , testDateTime.nMinute , testDateTime.nSecond);

		Sys_SetDateTime(szTip);
		//Save and read from rtc again and display 
		Sys_Delay(50);
		memset(rtcDateTime, 0x00, sizeof(rtcDateTime));
		Sys_GetDateTime(rtcDateTime);
		sscanf(rtcDateTime , "%04d%02d%02d%02d%02d%02d" , 
		&testDateTime.nYear , &testDateTime.nMonth , &testDateTime.nDay,
		&testDateTime.nHour , &testDateTime.nMinute , &testDateTime.nSecond);
		sprintf(szTip, "New Time:\n%d-%d-%d \n%d:%d:%d", testDateTime.nYear, testDateTime.nMonth, testDateTime.nDay, testDateTime.nHour, testDateTime.nMinute, testDateTime.nSecond);
		msgBoxRet = gui_messagebox_show("" ,szTip, "", "OK", 10000);

		nRet = (msgBoxRet == 1 ? 1 : 0);
	}

	return nRet;
}
