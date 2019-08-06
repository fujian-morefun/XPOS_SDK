#include "upay_consum.h"
#include "pub\osl\inc\osl_log.h"
#include "..\pages\input_public.h"
#include "pub\osl\inc\osl_BaseParam.h"

//#define APP_TRACE(...) 	osl_log("uninpay",LOG_LEVEL_TRACE, __VA_ARGS__);

int upay_barscan( void )
{
	char msg[256]={0};
	char code[256]={0};
	int ret = 0;
	const char *title = "Code Pay";
	long long amt;
	int input_type;


	if (osl_get_dev_mode() != DEV_MODE_SCAN)
	{
		xgui_messagebox_show(title, "Not support", "", "confirm" , 3000);		
		return -1;
	}
	amt = inputamount_page(title, 12, 60000);
	if ( amt <= 0 ) return -1;

	memset(code, 0x00, sizeof(code));
	ret = scan_page_proc(title, code,  2, sizeof(code) -1 , 60000, 5000 , 0, &input_type);

	if ( ret == 0 ){
		sprintf(msg, "amt:%lld\r\n%s", amt, code);
		xgui_messagebox_show(title, msg, "", "confirm" , 5000);
	}

	return ret;

}
