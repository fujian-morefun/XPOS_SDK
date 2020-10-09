
#include "pub/inc/taskdef.h"
#include "sdk_xgui.h"
#include "libapi_xpos/inc/libapi_gui.h"


#pragma data_alignment=8


#define _APP_TASK_SIZE		1024*3

#define _APP_TASK_PRIO		_APP_TASK_MIN_PRIO + 3
#define APPVER				"V1.07"

static unsigned int pTaskStk[_APP_TASK_SIZE];					// Thread stack


static void openlog(int nOpen)
{
	char set[512] = {0};
	char setbuf[512] = {0};
	int dl = 0;

	if (nOpen == 1)
	{
		strcpy(set, "logto=1 pub_file=0 demo=0 mxml=0 print_dev=0 atc_gprs=0 gprs=0 atc_uart=0 modem=0 uninpay=0 pub=0 xgui=0 atc=0 net=0 httpdownload=0 tms=0 sc=0 app_pub=0 emv=0 rpc=0 product=0 wifi=0");
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
static void _AppWorkTask(void * pParam)
{
	osl_app_init(0);					// Application initialization
	osl_tts_init(0, 2408, 2048);
	osl_set_language(1);					// Set the English language

	Sys_setAppVision(APPVER);
	openlog(1);
	osl_Sleep(3000);
	sdk_main_page(); //Start page    
}


void app_main()
{
	int nErrorCode;

	mf_driverlib_init();			 // Driver initialization
	osl_init();
	// Create an application thread
	osl_task_create((void*)_AppWorkTask, _APP_TASK_PRIO , pTaskStk , _APP_TASK_SIZE);
	osl_start();						// 	ucosii run
	while(1) osl_Sleep(1000);
}


#ifndef WIN32
void main(){
	app_main();
}
#endif

