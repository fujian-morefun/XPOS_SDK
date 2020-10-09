#include "status_page.h"
#include "../usermessage.h"
#include "libapi_xpos/inc/libapi_gui.h"
#include "xGui/inc/draw_buf.h"
#include "pub/code/Unicode.h"

typedef struct _pageinfo{
	char data[256];

	int  timer;
}pageinfo;

static e_pagemode s_mode;
static pageinfo s_info;


int enterAmount()
{
	int ret =0;
	const char msgstr[64];
	char oid[32];
	double result;

	ret = calculatorpage2(&result,0x31, G2U("CalCulator") );
	//ret = 0;
	//result = 20.1;
	if ( ret == 0)
	{
		Sys_GetDateTime(oid);
		
		sprintf(msgstr,"{\"cmd\":3, \"oid\":\"%s\", \"amt\":\"%0.02f\"}" ,oid , result);
		ret = mqtt_proc_publish( msgstr);
		if ( ret == 0)
		{
			status_page_showwaiting("waiting qr");
		}
		else{
			gui_messagebox_show("Erorr", "Please log in to the server first", "","",0);		
		}
	}
	return ret;
	
}
static void paint_status()
{
	gui_begin_batch_paint();
	gui_clear_dc();
	
	gui_textout_line_center( "Status", GUI_LINE_TOP(0));
	gui_textout_line_center( (char*)mqtt_status_text() , GUI_LINE_TOP(1));

	gui_end_batch_paint();
}

static void paint_waiting()
{
	gui_begin_batch_paint();
	gui_clear_dc();
	gui_textout_line_center( (char*)mqtt_status_text() , GUI_LINE_TOP(0));
	gui_textout_line_center( s_info.data  , GUI_LINE_TOP(1));

	gui_end_batch_paint();
}
static void paint_qr()
{
	gui_lcd_set_index(LCD_INDEX_1);
	sdk_showQr( s_info.data);
	gui_lcd_set_index(LCD_INDEX_2);

	gui_begin_batch_paint();
	gui_clear_dc();
	gui_textout_line_center( (char*)mqtt_status_text() , GUI_LINE_TOP(0));
	gui_textout_line_center( "Main screen"  , GUI_LINE_TOP(1));
	gui_end_batch_paint();
}

void standby_page_status()
{
	s_mode = page_status;
	s_info.timer = Sys_TimerOpen(1000);
	gui_post_message(GUI_GUIPAINT, 0 , 0);
}


void status_page_showqr(const char *qr)
{
	s_mode = page_qr;
	strcpy(s_info.data, qr );
	s_info.timer = Sys_TimerOpen(30000);
	gui_post_message(GUI_GUIPAINT, 0 , 0);
}


void status_page_showwaiting(const char *msg)
{
	s_mode = page_waiting;
	strcpy(s_info.data, msg );
	s_info.timer  = Sys_TimerOpen(3000);
	gui_post_message(GUI_GUIPAINT, 0 , 0);
}


char data[1 * 1024*1024];

void status_page()
{
	st_gui_message pMsg;
	s_mode = page_status;
	memset(s_info,0x00, sizeof(s_info));
#ifdef WIN32
	
#endif
	setpowersuspend(1);
	standby_page_status();

	while(1){
		if (gui_get_message(&pMsg,200) == 0) {

			if (pMsg.message_id == GUI_GUIPAINT) {
				if ( s_mode == page_status )
				{
					paint_status();
				}
				else if ( s_mode == page_waiting)
				{
					paint_waiting();
				}
				else if ( s_mode == page_qr)
				{
					paint_qr();
				}
			}
			else if (pMsg.message_id == GUI_KEYPRESS) {
				argot_keyinput(pMsg.wparam);
				//test
				if (pMsg.wparam == GUI_KEY_OK)	
				{
					if ( page_status == s_mode)
					{
						enterAmount();
					}
				}
				else if (pMsg.wparam == GUI_KEY_QUIT)	
				{
					break;
				}
				gui_post_message(GUI_GUIPAINT, 0 , 0);
			}
			else if ( pMsg.message_id == XM_PAYMENTEND)
			{
				standby_page_status();
			}
			else{
				mqtt_proc_default_msg( &pMsg);
			}
		}
		else{
			if ( Sys_TimerCheck( s_info.timer ) == 0)
			{
				standby_page_status();
			}
		}
	}
}


