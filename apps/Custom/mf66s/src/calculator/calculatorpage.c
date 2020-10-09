#include "calculatorpage.h"
#include "calculator.h"
#include "libapi_xpos\inc\libapi_gui.h"

static char *s_title = "CalCulator";

static int cal_paint(calculator *info )
{
	char full[64];

	memset(full,0x00, sizeof(full));
	cal_showfull(info, full );
	if ( strlen(full) == 0)
	{
		gui_textout_line_center(  s_title,GUI_LINE_TOP(0));		
	}
	else
	{
		gui_textout_line_right( full ,GUI_LINE_TOP(0));
	}

	cal_show(info, full);
	if ( strlen(full) == 0)
	{
		gui_textout_line_right( "0" ,GUI_LINE_TOP(1));	
	}
	else
	{
		gui_textout_line_right( full ,GUI_LINE_TOP(1));
	}
	
	return 0;
}

static int cal_keypress(calculator *info , unsigned int keycode )
{
	if (keycode>= GUI_KEY_0 && keycode <= GUI_KEY_9)	
	{
		return cal_addkeycode(info,keycode);
	}
	else if (keycode == GUI_KEY_JING)	
	{
		cal_addkeycode(info,GUI_KEY_0);
		cal_addkeycode(info,GUI_KEY_0);
	}
	else if (keycode == GUI_KEY_XING)	
	{
		return cal_addkeycode(info,'.');
	}
	else if (keycode == GUI_KEY_BACKSPACE)	
	{
		return cal_backspace(info);
	}
	else if (keycode == GUI_KEY_PLUS )	
	{
		cal_addop(info,'+');
	}
	else if (keycode == GUI_KEY_SUBTRACT )	
	{
		cal_addop(info,'-');
	}
	else if (keycode == GUI_KEY_MULTIPLY )	
	{
		cal_addop(info,'*');
	}
	else if (keycode == GUI_KEY_DIVISION )	
	{
		cal_addop(info,'/');
	}
	else if (keycode == GUI_KEY_EQUAL)
	{
		return cal_compute(info);
	}
	else if (keycode == GUI_KEY_MC )
	{
		return cal_memory_clear(info);
	}	
	else if (keycode == GUI_KEY_MR )
	{
		return cal_memory_read(info);
	}	
	else if (keycode == GUI_KEY_MP )
	{
		return cal_memory_plus(info);
	}	
	else if (keycode == GUI_KEY_MS )
	{
		return cal_memory_subtract(info);
	}

	return 1;
}

int calculatorpage(double *result)
{
	return calculatorpage2(result, 0, 0);
}
int calculatorpage2( double *result,char firstchr, const char *title )
{
	int  ret = RET_CAL_NORESULT;
	st_gui_message  pMsg;
	calculator info;

	memset( &info,0x00,sizeof(info));
	if (title != 0)
	{
		s_title = (char *)title;
	}
	if ( firstchr != 0)
	{
		cal_keypress( &info, firstchr);
	}

	gui_post_message(GUI_GUIPAINT, 0 , 0);
	while(1){
		if (gui_get_message(&pMsg, 300) == 0) {

			if (pMsg.message_id == GUI_GUIPAINT) {
				gui_begin_batch_paint();
				gui_clear_dc();
				cal_paint( &info );
				gui_end_batch_paint();
			}
			else if (pMsg.message_id == GUI_KEYPRESS) {
				argot_keyinput(pMsg.wparam);
				if ( pMsg.wparam == GUI_KEY_QUIT)
				{
					break;
				}
				else if ( pMsg.wparam == GUI_KEY_OK)
				{
					if (info.setp != step_result )
					{
						cal_compute(&info);
					}

					if( cal_result( &info, result) == 1)	
					{
						ret = RET_CAL_SUCC;
					}
					break;
				}

				cal_keypress( &info, pMsg.wparam);
				gui_post_message(GUI_GUIPAINT, 0 , 0);
			}
		}

	}

	return ret;
}



