#include "sdk_log.h"
#include <stdarg.h>
#include <string.h>
#include "driver/mf_misc.h"
#include "pub/osl/inc/osl_system.h"
#include "pub/osl/inc/osl_BaseParam.h"
#include "xGui/inc/draw_buf.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/xgui_key.h"
#include "xGui/inc/message.h"
#include <stdio.h>
#include "xGui/inc/pageproc.h"

static int init = 0;
static char buff[512];


void sdk_log_out(const char *fmt,... )
{
	int ret;
	va_list vargs;

	if(init == 0){
		mf_console_switch(1);	// Initialize log
		init = 1;
	}

	va_start(vargs, fmt);
	ret = vsprintf(buff, fmt, vargs);
	va_end(vargs);
	buff[ret] = 0;
	mf_stdout(buff, ret);
}

static void _LogOut_Paint(int value)
{
	xgui_BeginBatchPaint();

	xgui_ClearDC();

	xgui_TextOut(0, XGUI_LINE_TOP_0, value == 1 ? "LogOut:On" : "LogOut:Off");

	//xgui_TextOut(0, XGUI_LINE_TOP_2 , "Up to switch");

	xgui_Page_OP_Paint( "Cancel" , "OK");

	xgui_EndBatchPaint();
}

void openlog(int nOpen)
{
	char set[512] = {0};
	char setbuf[512] = {0};
	int dl = 0;

	if (nOpen == 1)
	{
		strcpy(set, "logto=1 malloc=0 pub_file=0 demo=0 mxml=0 print_dev=0 atc_gprs=0 gprs=0 atc_uart=0 modem=0 uninpay=0 pub=0 xgui=0 atc=0 net=0 httpdownload=0 tms=0 sc=0 app_pub=0 emv=0 rpc=0 product=0 wifi=0");
	} 
	else
	{
		strcpy(set, "logto=0 malloc=0 pub_file=0 demo=0 mxml=0 print_dev=0 atc_gprs=0 gprs=0 atc_uart=0 modem=0 uninpay=0 pub=0 xgui=0 atc=0 net=0 httpdownload=0 tms=0 sc=0 app_pub=0 emv=0 rpc=0 product=0 wifi=0");
	}
	dl = strlen(set);
	setbuf[0] = (dl >> 0) & 0xff;
	setbuf[1] = (dl >> 8) & 0xff;
	setbuf[2] = (dl >> 16) & 0xff;
	setbuf[3] = (dl >> 24) & 0xff;
	strcpy(setbuf+4, set);

	osl_set_log_data(setbuf, dl+4);
}

int LogOutSet_Show()
{
	int presskey;
	MESSAGE pMsg;
	int nOpen = 0;


	_LogOut_Paint(nOpen);

	while(1){
		if (xgui_GetMessageWithTime(&pMsg, 100) == MESSAGE_ERR_NO_ERR) {

			if (pMsg.MessageId == XM_KEYPRESS) {
				presskey = pMsg.WParam;

				switch(presskey) {
				case KEY_UP: case KEY_DOWN:case KEY_LEFT:case KEY_RIGHT:case KEY_XING:case KEY_JING:
					nOpen = 1 - nOpen;
					_LogOut_Paint(nOpen);
					break;
				case KEY_OK:
					//保存，再走quit退出
					openlog(nOpen);
					Sys_Reboot();
					break;
				case KEY_QUIT:
					break;
				}

				if ( presskey == KEY_QUIT || KEY_OK == presskey )
				{
					break;
				}
			}
		}
	} 

	return nOpen;
}