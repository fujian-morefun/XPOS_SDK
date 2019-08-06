#include "input_public.h"
#include "xGui/inc/2ddraw.h"

//Draw the title, the first line
void input_PaintTitle(char* title)
{
	//RECT oldrc;
	if (title!=0 && strlen(title)>6)
	{
		//xgui_SetFont( UFONT_COURIER );
	}
	//xgui_GetViewPort(&oldrc);
	//XGUI_SET_WIN_RC;
	xgui_ClearRect(0, XGUI_LINE_TOP_0, XGUI_WIN_WIDTH - 1, XGUI_LINE_TOP_1, xgui_GetBgColor());
#ifdef LCD_320_240
	xgui_SetTitle(title);
#else
	xgui_TextOut_Line_Center(title, 0);
#endif

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
	int textHeight = xgui_GetTextHeight("A");
	//RECT oldrc;
	//xgui_GetViewPort(&oldrc);
	//XGUI_SET_WIN_RC;
	int i = 0;
	int nlenth = strlen(header);
	int m = 0;
	char sTip[30]={0};
	nLine = 0;

	if (lcd_get_sublcd_probe() == 1)
	{
		memset(sTip,0x00,sizeof(sTip));
		memcpy(sTip,header, 16);
		xgui_ClearRect(0,XGUI_LINE_TOP_0, XGUI_WIN_WIDTH - 1,XGUI_LINE_TOP_1, xgui_GetBgColor());
		xgui_TextOut(0, XGUI_LINE_TOP_0, sTip);
	} 
	else
	{
		for(i=0;i<(nlenth+1);i++)//line break
		{
			if(header[i]==0x7c){
				memset(sTip,0x00,sizeof(sTip));
				memcpy(sTip,header+m,i-m);
				m = i+1;
				xgui_ClearRect(0,XGUI_LINE_TOP_1+textHeight*nLine, XGUI_WIN_WIDTH - 1,XGUI_LINE_TOP_2+textHeight*nLine, xgui_GetBgColor());
				xgui_TextOut(0, XGUI_LINE_TOP_1+textHeight*nLine, sTip);
				nLine++;
			}
		}
		memset(sTip,0x00,sizeof(sTip));
		memcpy(sTip,header+m,i-m);

		xgui_ClearRect(0,XGUI_LINE_TOP_1+textHeight*nLine, XGUI_WIN_WIDTH - 1,XGUI_LINE_TOP_2+textHeight*nLine, xgui_GetBgColor());
		xgui_TextOut(0, XGUI_LINE_TOP_1+textHeight*nLine, sTip);
	}

	//xgui_SetViewPort_RC(&oldrc); 
}

//Draw the third row
void input_PaintInput(char* inputContent)
{
	int textHeight = xgui_GetTextHeight("A");
	int textWidth = xgui_GetTextWidth(inputContent);
	//RECT oldrc;
	//xgui_GetViewPort(&oldrc);
	//XGUI_SET_WIN_RC;
	xgui_ClearRect(0, XGUI_LINE_TOP_2, XGUI_WIN_WIDTH - 1, XGUI_LINE_TOP_3, xgui_GetBgColor());
	xgui_TextOut(XGUI_WIN_WIDTH - textWidth - 10, XGUI_LINE_TOP_3 , inputContent);
	//xgui_SetViewPort_RC(&oldrc); 
}

//Draw the fourth line
void input_PaintFooter(char* footer)
{
	int textHeight = xgui_GetTextHeight("A");
	//RECT oldrc;
	//xgui_GetViewPort(&oldrc);
	//XGUI_SET_WIN_RC;
	xgui_ClearRect(0,XGUI_LINE_TOP_3, XGUI_WIN_WIDTH, XGUI_WIN_HEIGHT, xgui_GetBgColor());
	xgui_TextOut(0, XGUI_LINE_TOP_3, footer);
	//xgui_SetViewPort_RC(&oldrc); 
}