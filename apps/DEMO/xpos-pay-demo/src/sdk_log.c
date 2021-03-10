

#include "app_def.h"
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
	gui_begin_batch_paint();

	gui_clear_dc();

	gui_text_out(0, GUI_LINE_TOP(0), value == 1 ? "LogOut:On" : "LogOut:Off");

	//xgui_TextOut(0, XGUI_LINE_TOP_2 , "Up to switch");

	gui_page_op_paint( "Cancel" , "OK");

	gui_end_batch_paint();
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

	Sys_set_log_data(setbuf, dl+4);
}

int LogOutSet_Show()
{
	int presskey;
	st_gui_message pMsg;
	int nOpen = 0;


	_LogOut_Paint(nOpen);

	while(1){
		if (gui_get_message(&pMsg, 100) == 0) {

			if (pMsg.message_id == GUI_KEYPRESS) {
				presskey = pMsg.wparam;

				switch(presskey) {
				case GUI_KEY_UP: case GUI_KEY_DOWN:case GUI_KEY_LEFT:case GUI_KEY_RIGHT:case GUI_KEY_XING:case GUI_KEY_JING:
					nOpen = 1 - nOpen;
					_LogOut_Paint(nOpen);
					break;
				case GUI_KEY_OK:
					//save and restart
					openlog(nOpen);
					Sys_Reboot();
					break;
				case GUI_KEY_QUIT:
					break;
				}

				if ( presskey == GUI_KEY_QUIT || GUI_KEY_OK == presskey )
				{
					break;
				}
			}
		}
	} 

	return nOpen;
}