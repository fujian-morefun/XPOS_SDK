#include "pub/osl/inc/osl_init.h"
#include "pub/inc/taskdef.h"
#include "ucosii/ucos_ii.h"
#include "driver/mf_driverlib.h"
#include "sdk_xgui.h"
#include "pub/osl/inc/osl_BaseParam.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/message.h"
#include "xGui/inc/xgui_key.h"
#include "xGui/inc/xgui_bmp.h"
#include "pub/common/misc/inc/mfmalloc.h"
#include "pub/tracedef.h"
#include "pub/osl/inc/osl_filedef.h"
#include "sdk_file.h"

#pragma data_alignment=8
#define LOGOIMG "data\\logo2.bmp"

#define APP_VER "paydemo-V1.1.2"

#ifdef DEV_MF67
	#define _APP_TASK_SIZE		1024*2
#else
	#define _APP_TASK_SIZE		1024*3
#endif

#define _APP_TASK_PRIO		_APP_TASK_MIN_PRIO + 3
static OS_STK pTaskStk[_APP_TASK_SIZE];

static void sys_init()
{
	osl_app_init(1);
	mf_auxlcd_backlight(1);
	osl_set_language(1);
}

static void showlogo()
{
	int logowidth;
	int logoheight;
	int logoleft;
	int logotop;
	int logocolor;

	char * pbmp;	  

	pbmp = xgui_load_bmp_all(LOGOIMG, &logowidth , &logoheight, &logocolor);
	//pbmp = xgui_load_bmp4bit(LOGOIMG , &logowidth , &logoheight);
	logoleft = (xgui_GetWidth()-logowidth)/2;
	if (osl_get_is_m69() || osl_get_is_m66b())
	{
		logotop = XGUI_LINE_TOP_2;
	} 
	else
	{
		logotop = XGUI_LINE_TOP_1;
	}

	if (pbmp != 0){
		xgui_BeginBatchPaint();
		XGUI_SET_WIN_RC;
		xgui_ClearDC();        

		xgui_out_bits_bmp(logoleft, logotop, pbmp , logowidth , logoheight , 1 , logocolor);
		//xgui_out_bits_bmp4bit(0, 0, pbmp , logowidth , logoheight , 0);

		FREE(pbmp);
		xgui_EndBatchPaint(); 
		osl_Sleep(1000); 
	} 
}

static void app_init()
{
	APP_TRACE_FILE("app run\r\n");

	set_malloc_log(0);
	//ap_logo_page_show();			// Display boot logo
	//osl_Sleep(500);
	osl_setAppVision(APP_VER);		// Set the application version
#ifndef DEV_MF67
	EMV_iKernelInit();//Init EMV
#endif
	showlogo();					//Display boot logo
	if (osl_get_is_m66b() == 1)		////MF66B with a small LCD
	{
		lcd_set_index(1);
	}
	sdk_main_page();     
}



static void _AppWorkTask(void * pParam)
{
	sys_init();
	app_init();
}


void app_main()
{
	int nErrorCode;

	mf_driverlib_init();
	OSInit();
	OSTaskCreateExt(_AppWorkTask, 0, &(pTaskStk[_APP_TASK_SIZE -1]), _APP_TASK_PRIO ,_APP_TASK_PRIO ,&(pTaskStk[0]) , _APP_TASK_SIZE , 0 , OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK);
	OSStart();
	while(1) osl_Sleep(1000);
}

#ifndef WIN32
void main()
{
	if(osl_get_is_1903() == 0){
		app_main(0);
	}
	else{
		mf_start_apps(app_main);
	}
}
#endif