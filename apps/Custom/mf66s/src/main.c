
//#include "pub/inc/taskdef.h"
#include "sdk_xgui.h"
#include "libapi_xpos/inc/libapi_gui.h"

#pragma data_alignment=8

#define _APP_TASK_SIZE		(1024*3)

#define APP_TASK_MIN_PRIO	30
#define _APP_TASK_PRIO		(APP_TASK_MIN_PRIO + 3)
#define APPVER				"V1.0.3"

static unsigned int pTaskStk[_APP_TASK_SIZE];					// Thread stack


static void _AppWorkTask(void * pParam)
{
	Sys_init();
	//osl_log_init();
	Sys_setAppVision(APPVER);
	//Sys_Delay(3000);
	device_init_tip();
	sdk_readcard_init(); //prepare for card reading
	sdk_main_page(); //Start page    
}


void app_main()
{
	Sys_driverlib_init();			 // Driver initialization					 // ucosii initialization
	// Create an application thread
	Sys_TaskCreate(_AppWorkTask,_APP_TASK_PRIO,(char *)pTaskStk, _APP_TASK_SIZE);				// 	ucosii run
	while(1) Sys_Delay(1000);
}

void main(){
	app_main();
}

