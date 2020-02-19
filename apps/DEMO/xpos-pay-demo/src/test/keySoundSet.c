#include "driver/mf_misc.h"
#include "pub/osl/inc/osl_system.h"
#include "pub/osl/inc/osl_BaseParam.h"
#include "xGui/inc/draw_buf.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/xgui_key.h"
#include "xGui/inc/message.h"
#include <stdio.h>
#include <string.h>
#include "xGui/inc/pageproc.h"

static void _keySound_Paint(int value)
{
	xgui_BeginBatchPaint();
	
	xgui_ClearDC();

	xgui_TextOut(0, XGUI_LINE_TOP_0, value == 1 ? "KeySound:On" : "KeySound:Off");

	//xgui_TextOut(0, XGUI_LINE_TOP_2 , "Up to switch");

	xgui_Page_OP_Paint( "Cancel" , "OK");
	
	xgui_EndBatchPaint();
}

int keySoundSet_Show_test()
{
	int presskey;
	MESSAGE pMsg;
	int nOpen = osl_IsKeySoundOpen();
	_keySound_Paint(nOpen);

	while(1){
		if (xgui_GetMessageWithTime(&pMsg, 100) == MESSAGE_ERR_NO_ERR) {

			if (pMsg.MessageId == XM_KEYPRESS) {
				presskey = pMsg.WParam;

				switch(presskey) {
				case KEY_UP: case KEY_DOWN:case KEY_LEFT:case KEY_RIGHT:case KEY_XING:case KEY_JING:
					nOpen = 1 - nOpen;
					_keySound_Paint(nOpen);
					break;
				case KEY_OK:
					//保存，再走quit退出
					osl_SwitchKeySound(nOpen);
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