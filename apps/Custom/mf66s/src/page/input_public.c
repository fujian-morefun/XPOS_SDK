#include "../app_def.h"

//Draw the title, the first line
void input_PaintTitle(char* title)
{
	//RECT oldrc;
	if (title!=0 && strlen(title)>6)
	{
		//gui_set_font( UFONT_COURIER );
	}
	//xgui_GetViewPort(&oldrc);
	//XGUI_SET_WIN_RC;
	gui_clear_rect(0, GUI_LINE_TOP(0), gui_get_width() - 1, GUI_LINE_TOP(1), gui_get_bg_color());
	gui_set_title(title);
	//xgui_SetViewPort_RC(&oldrc); 
	//xgui_SetFont( UFONT_NORMAL );
}

static int nLine;
int get_line(void)
{
	return nLine;
}
//Draw the second row
void input_PaintHeader(char* header)
{
	int textHeight = gui_get_text_height("A");
	//RECT oldrc;
	//xgui_GetViewPort(&oldrc);
	//XGUI_SET_WIN_RC;
	int i = 0;
	int nlenth = strlen(header);
	int m = 0;
	char sTip[30]={0};
	nLine = 0;
	for(i=0;i<(nlenth+1);i++)//line break
	{
		if(header[i]==0x7c){
			memset(sTip,0x00,sizeof(sTip));
			memcpy(sTip,header+m,i-m);
			m = i+1;
			gui_clear_rect(0,GUI_LINE_TOP(1)+textHeight*nLine, gui_get_width() - 1,GUI_LINE_TOP(2)+textHeight*nLine, gui_get_bg_color());
			gui_text_out(0, GUI_LINE_TOP(1)+textHeight*nLine, sTip);
			nLine++;
		}
	}
	memset(sTip,0x00,sizeof(sTip));
	memcpy(sTip,header+m,i-m);

	gui_clear_rect(0,GUI_LINE_TOP(1)+textHeight*nLine, gui_get_width() - 1,GUI_LINE_TOP(2)+textHeight*nLine, gui_get_bg_color());
	gui_text_out(0, GUI_LINE_TOP(1)+textHeight*nLine, sTip);
	//xgui_SetViewPort_RC(&oldrc); 
}

//Draw the third row
void input_PaintInput(char* inputContent)
{
	int textHeight = gui_get_text_height("A");

	int textWidth = gui_text_width_ex(inputContent);
	//RECT oldrc;
	//xgui_GetViewPort(&oldrc);
	//XGUI_SET_WIN_RC;
	gui_clear_rect(0, GUI_LINE_TOP(2), gui_get_width() - 1, GUI_LINE_TOP(3), gui_get_bg_color());
	gui_text_out(gui_get_width() - textWidth - 10, GUI_LINE_TOP(3) , inputContent);
	//xgui_SetViewPort_RC(&oldrc); 
}

//Draw the fourth line
void input_PaintFooter(char* footer)
{
	int textHeight = gui_get_text_height("A");
	//RECT oldrc;
	//xgui_GetViewPort(&oldrc);
	//XGUI_SET_WIN_RC;
	gui_clear_rect(0,GUI_LINE_TOP(3), gui_get_width(), gui_get_height(), gui_get_bg_color());
	gui_text_out(0, GUI_LINE_TOP(3), footer);
	//xgui_SetViewPort_RC(&oldrc); 
}