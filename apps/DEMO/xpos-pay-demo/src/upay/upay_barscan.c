
#include "../app_def.h"

int upay_barscan( void )
{
	char code[64]={0};
	char amt[16]={0};
	int ret;
	char msg[128];
	char *title = "Code Pay";
	long long namt = 0;
	
	//ret = input_num_page(amt, "input the amount", 1, 9, 0, 0, 1);		//Enter the amount
	//if(ret != INPUT_NUM_RET_OK) return -1;
	namt = inputamount_page(title, 9, 90000);
	SYS_TRACE("namt:%lld",namt);
	if(namt <= 0)
	{
		return -1;
	}
	sprintf(amt, "%lld" , namt);

	memset(code, 0x00, sizeof(code));
	ret = scan_page_proc(title , code,  sizeof(code), 5000);	// Get scanned barcode

	if ( ret >0 ){
		sprintf(msg, "amt:%s\r\ncode:%s", amt, code);
		gui_messagebox_show(title, msg, "" , "ok", 0);	// Prompt result
	}

	return ret;

}
