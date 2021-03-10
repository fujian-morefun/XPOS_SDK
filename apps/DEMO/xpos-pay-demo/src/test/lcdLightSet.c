#include "../app_def.h"
#include "driver/mf_misc.h"



static void _paint_msg(char* msg)
{
	char* pstr;
	int yPos = 0;
	while ((pstr = strstr(msg, "\n")) != 0)
	{
		pstr[0] = '\0';
		gui_text_out(0, GUI_LINE_TOP(yPos) , msg);
		pstr ++;
		msg = pstr;
		yPos ++;
	}

	gui_text_out(0, GUI_LINE_TOP(yPos) , msg);

}

static void _lcdLight_paint(int nTime ,char * szMsg)
{
	char szContent[128] = {0};
	switch(nTime)	{
	case 30:
		sprintf(szContent,"->30 sec   1 min\n  3 min   10 min\n  30 min   %s",szMsg);
		break;
	case 60:
		sprintf(szContent, "  30 sec ->1 min\n  3 min   10 min\n  30 min   %s",szMsg);
		break;
	case 3 * 60:
		sprintf(szContent, "  30 sec   1 min\n->3 min   10 min\n  30 min   %s",szMsg);
		break;
	case 10 * 60:
		sprintf(szContent, "  30 sec   1 min\n  3 min ->10 min\n  30 min   %s",szMsg);
		break;
	case 30 * 60:
		sprintf(szContent,"  30 sec   1 min\n  3 min   10 min\n->30 min   %s",szMsg);
		break;
	case GUI_LCD_LIGHT_MAX:
		sprintf(szContent, "  30 sec   1 min\n  3 min   10 min\n  30 min ->%s",szMsg);
		break;
	default:
		sprintf(szContent,"->30 sec   1 min\n  3 min   10 min\n  30 min   %s",szMsg);
		break;
	}

	gui_begin_batch_paint();

	gui_clear_dc();

	_paint_msg(szContent);

	gui_page_op_paint( "Cancel" , "Save");

	gui_end_batch_paint();
}

int TimeSet_Show(int nLightTime , char * szMsg)
{
	int presskey;

	int time[6] = {30, 60, 3 * 60, 10 * 60, 30 * 60, GUI_LCD_LIGHT_MAX};
	int nCurIndex = 0;
	int nTotalCount = sizeof(time) / sizeof(int);
	int i;
	st_gui_message pMsg;

	_lcdLight_paint(nLightTime , szMsg);

	for (i = 0; i < nTotalCount; ++ i)	{
		if (nLightTime == time[i])		{
			nCurIndex = i;
			break;
		}
	}

	while(1){
		if (gui_get_message(&pMsg, 100) == 0) {

			if (pMsg.message_id == GUI_KEYPRESS) {
				presskey = pMsg.wparam;

				switch(presskey) {
					case GUI_KEY_UP:case GUI_KEY_LEFT: case GUI_KEY_1 : case GUI_KEY_XING:
						nCurIndex = (-- nCurIndex < 0 ? nTotalCount - 1 : nCurIndex);
						_lcdLight_paint(time[nCurIndex] , szMsg);
						break;
					case GUI_KEY_DOWN:case GUI_KEY_RIGHT: case GUI_KEY_2 : case GUI_KEY_JING:
						nCurIndex = (++ nCurIndex % nTotalCount);
						_lcdLight_paint(time[nCurIndex] , szMsg);
						break;
					case GUI_KEY_QUIT:
						return -1;
					case GUI_KEY_OK:	
						return time[nCurIndex];
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

void PowerDownTimeSet_Show()
{
	int nLightTime = Sys_GetPowerDownTime();
	int nRet = 0;

	nRet = TimeSet_Show(nLightTime , "Disable");
	if(nRet != -1){
		Sys_SetPowerDownTime(nRet);
	}
}

void eneyTimeSet_Show()
{
	int nLightTime = Sys_Enercy_Time();
	int nRet=0;
	
	nRet = TimeSet_Show(nLightTime , "Disable");
	if(nRet != -1){
		Sys_Enercy_SetTime(nRet);
	}
}

void lcdLightSet_Show()
{
	int nLightTime = Sys_GetBackLightTime();
	int nRet=0;
	nRet = TimeSet_Show(nLightTime , "Always");

	if(nRet != -1){
		Sys_SetBackLightTime(nRet);
	}
}