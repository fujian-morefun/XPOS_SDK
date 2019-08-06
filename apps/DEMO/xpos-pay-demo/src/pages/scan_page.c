#include <stdio.h>
#include "xGui/inc/message.h"
#include "pub/osl/inc/osl_log.h"
#include "xGui/inc/xgui_key.h"
#include "xGui/inc/draw_buf.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/messagebox.h"
#include "pub/osl/inc/osl_time.h"
#include "pub/osl/inc/osl_scaner.h"



int scan_page_proc(char *title, char *buff, int size,  int timeover)
{
	
	int ret;

	// Display scan
	xgui_BeginBatchPaint();
	xgui_ClearDC();
	xgui_SetTitle(title);
	xgui_TextOut_Line_Left("scan..." , XGUI_LINE_TOP_1);
	xgui_EndBatchPaint();

	osl_scaner_open();			// Open the scanning device
	//Read the barcode, read it back immediately, can't read the timeout and return
	ret = osl_scaner_get(buff, size, timeover);		
	osl_scaner_close();			// Close the scanning device
	return ret ;
}

