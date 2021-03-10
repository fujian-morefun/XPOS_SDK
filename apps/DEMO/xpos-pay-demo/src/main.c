#include "app_def.h"

#pragma data_alignment=8
#define LOGOIMG "data\\logo1.bmp"

#define APP_TASK_MIN_PRIO	30
#define APP_TASK_MAX_PRIO	30
#define _APP_TASK_SIZE		(1024+1024+1024+256)			// Thread stack size
#define _APP_TASK_PRIO		(APP_TASK_MIN_PRIO + 3)	// Thread priority
static unsigned int pTaskStk[_APP_TASK_SIZE];					// Thread stack

static void showlogo()
{
	int logowidth;
	int logoheight;
	int logoleft;
	int logotop;
	int logocolor;

	char * pbmp;	  

	pbmp = gui_load_bmp_ex(LOGOIMG, &logowidth , &logoheight, &logocolor);
	//pbmp = xgui_load_bmp4bit(LOGOIMG , &logowidth , &logoheight);

	if (pbmp != 0){
		gui_begin_batch_paint();
		gui_set_win_rc();
		gui_clear_dc();        

		gui_out_bits_ex(0, 0, pbmp , logowidth , logoheight , 0 , logocolor);
		//xgui_out_bits_bmp4bit(0, 0, pbmp , logowidth , logoheight , 0);

		Util_Free(pbmp);
		gui_end_batch_paint(); 
		Sys_Delay(1000); 
	} 
}
static void app_init()
{
	//SYS_TRACE_FILE("app run\r\n");
	//ap_logo_page_show();				// Display boot logo
	Sys_setAppVision(APP_VER);	// Set the application version
	showlogo();		// Display logo
	//Sys_Delay(2000);
	sdk_readcard_init(); //prepare for card reading
	sdk_main_page(); //Start page       
}

int powerkey_proc_page(st_gui_message *pmsg)
{
	if (pmsg->message_id == GUI_POWERDOWN){

		gui_messagebox_show("", "Power down?" , "cancel" , "ok" , 0);

		return 1;
	}
	else if(GUI_POWNLOWER==pmsg->message_id){
		gui_messagebox_show("Power Low", "Pls connect Charger" , "cancel" , "ok" , 0);
	}

	return 0;
}

static void _AppWorkTask(void * pParam)
{
//	xgui_default_msg_func_add((void*)powerkey_proc_page);	// Default message processing
	Sys_init();
	//ap2_mbedtls_init(1,0);
	app_init();
}

void app_main()
{
	int nErrorCode;

	Sys_driverlib_init();			 // Driver initialization					 // ucosii initialization
	// Create an application thread
	Sys_TaskCreate(_AppWorkTask,_APP_TASK_PRIO,(char *)pTaskStk, _APP_TASK_SIZE);				// 	ucosii run
	while(1) Sys_Delay(1000);
}

void main(){
	app_main();
}

