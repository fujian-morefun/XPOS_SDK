#pragma once

#include "libapi_pub.h"

#define GUI_IME_MODE_T9PY			(1<<0)		//Allow pinyin input method
#define GUI_IME_MODE_ALPHABET_UP	(1<<1)		//Allow uppercase letters
#define GUI_IME_MODE_ALPHABET_LOW	(1<<2)		//Allow lowercase letters	
#define GUI_IME_MODE_NUMBER			(1<<3)		//Allow input of numbers


//#define GUI_LINE_TOP(a)		(33 * a)
#define GUI_LINE_TOP(a)						xgui_GetLineTop(a)

#define GUI_GUIFIRST				0x000A0000
#define GUI_GUIPAINT				0x000A0001
#define GUI_KEYPRESS				0x00050001
#define GUI_SCAN_OK					0x000E0021

#define GUI_KEY_0		'0'
#define GUI_KEY_1		'1'
#define GUI_KEY_2		'2'
#define GUI_KEY_3		'3'
#define GUI_KEY_4		'4'
#define GUI_KEY_5		'5'
#define GUI_KEY_6		'6'
#define GUI_KEY_7		'7'
#define GUI_KEY_8		'8'
#define GUI_KEY_9		'9'
#define GUI_KEY_XING	'*'
#define GUI_KEY_JING		'#'

#define GUI_KEY_CONTROL		0x80

#define GUI_KEY_UP			(GUI_KEY_CONTROL + 0x1)
#define GUI_KEY_DOWN		(GUI_KEY_CONTROL + 0x2)
#define GUI_KEY_LEFT		(GUI_KEY_CONTROL + 0x3)
#define GUI_KEY_RIGHT		(GUI_KEY_CONTROL + 0x4)
#define GUI_KEY_BACKSPACE	(GUI_KEY_CONTROL + 0x5)

#define GUI_KEY_OK			(GUI_KEY_CONTROL + 0x11)
#define GUI_KEY_QUIT		(GUI_KEY_CONTROL + 0x12)
#define GUI_KEY_F1			(GUI_KEY_CONTROL + 0x13)
#define GUI_KEY_F2			(GUI_KEY_CONTROL + 0x14)
#define GUI_KEY_POWER		(GUI_KEY_CONTROL + 0x15)



#define GUI_KEY_MC			'A'
#define GUI_KEY_MR			'B'
#define GUI_KEY_MP			'C'
#define GUI_KEY_MS			'D'


#define GUI_KEY_PLUS			'+'
#define GUI_KEY_SUBTRACT		'-'
#define GUI_KEY_MULTIPLY		'M'
#define GUI_KEY_DIVISION		'/'
#define GUI_KEY_EQUAL			'='
#define GUI_KEY_DOT				'.'



#define GUI_COLOR_BACK		(0xCCCCCC)
#define GUI_COLOR_FORE		(0x222222)

typedef struct __st_gui_rect{
	int    left;	
	int    top;		
	int    right;	
	int    bottom;	
} st_gui_rect;


typedef struct __st_gui_point{
	int    x;	
	int    y;		
} st_gui_point;


typedef struct __st_gui_menu_item_def{
	char *parent;	
	char *name;		
	char *id;		
}st_gui_menu_item_def;


typedef struct __st_gui_message{
	void * dest;
	unsigned int message_id;
	unsigned int wparam;
	unsigned int lparam;
	unsigned int time;
}st_gui_message;






/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Batch refresh starts
Input : Nothing			
Output : Nothing			
return: Nothing			
*************************************************************************************/
LIB_EXPORT void gui_begin_batch_paint();


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:End of batch refresh
Input : Nothing			
Output : Nothing			
return: Nothing			
*************************************************************************************/
LIB_EXPORT void gui_end_batch_paint();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Set the foreground color
Input : color :the foreground color			
Output : Nothing			
return: Nothing			
*************************************************************************************/
LIB_EXPORT void gui_set_color(int color);



/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Get the foreground color
Input : Nothing		
Output : Nothing			
return: the foreground color				
*************************************************************************************/
LIB_EXPORT int gui_get_color();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Set the background color
Input : color :the background color			
Output : Nothing			
return: Nothing			
*************************************************************************************/
LIB_EXPORT void gui_set_bg_color(int color);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Get the background color
Input : Nothing		
Output : Nothing			
return: the background color				
*************************************************************************************/
LIB_EXPORT int gui_get_bg_color();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Set text display style
Input : style: 0 normal 1 transparent
Output : Nothing			
return: 				
*************************************************************************************/
LIB_EXPORT void gui_set_text_style(int style);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Set text display style
Input : 
Output : Nothing			
return: style: 0 normal 1 transparent				
*************************************************************************************/
LIB_EXPORT int gui_get_text_style();


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:linzhu
Functions:Set to full screen display 
Input : full:1set full screen display, cancel full screen display			
Output : Nothing			
return: Nothing			
*************************************************************************************/
LIB_EXPORT void gui_set_full_screen(int full);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Draw a point
Input : x :x coordinate
		y: y coordinate
Output : Nothing			
return: 0,     success
		Other, failure
*************************************************************************************/
LIB_EXPORT int gui_pixel(int x, int y);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Draw line
Input : x :x coordinate
		y: y coordinate
Output : Nothing			
return: Nothing
*************************************************************************************/
LIB_EXPORT void gui_line_to(int x, int y);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Gui filled area
Input : left		Left border
	      top		Upper boundary
		  right		Right border
		  bottom	Lower boundary
Output : Nothing			
return: 0,     success
		Other, failure	
*************************************************************************************/
LIB_EXPORT void gui_bar_rc(int left, int top, int right, int bottom);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Set the fill color
Input : color		Color format 0x00RRGGBB
Output : Nothing			
return: 0,     success
		Other, failure	
*************************************************************************************/
LIB_EXPORT void gui_set_bar_color(int color);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Get the fill color
Input : Nothing
Output : Nothing			
return: Fill color
*************************************************************************************/
LIB_EXPORT int gui_get_bar_color();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Set display font
Input : font 0=12 lattice 1=16 lattice
Output : Nothing			
return: 
*************************************************************************************/
LIB_EXPORT void gui_set_font(int font);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Get display font
Input : Nothing
Output : Nothing			
return: Font
*************************************************************************************/
LIB_EXPORT int gui_get_font(void);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Set text color
Input : color text color
Output : Nothing			
return: 
*************************************************************************************/
LIB_EXPORT void gui_set_text_color(int color);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Get text color
Input : Nothing
Output : Nothing			
return: Text color
*************************************************************************************/
LIB_EXPORT int gui_get_text_color(void);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Set the text background color
Input : cloro text color
Output : Nothing			
return: 
*************************************************************************************/
LIB_EXPORT void gui_set_text_bg_color(int color) ;

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Get the text background color
Input : Nothing
Output : Nothing			
return: Text background color
*************************************************************************************/
LIB_EXPORT int gui_get_text_bg_color(void);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Clear screen display
Input : Nothing
Output : Nothing			
return: Nothing
*************************************************************************************/
LIB_EXPORT void gui_clear_dc(void);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Set text magnification
Input : size		Multiple, the default value is 2
Output : Nothing			
return: 0			success
*************************************************************************************/
LIB_EXPORT void gui_set_text_zoom(int size) ;

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Get text magnification
Input : Nothing
Output : Nothing			
return: Multiple
*************************************************************************************/
LIB_EXPORT int gui_get_text_zoom() ;


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Draw on the screen
Input : x			x coordinate
		  y			y coordinate
		  color		Point color
Output : Nothing			
return: 0			success
*************************************************************************************/
LIB_EXPORT int gui_set_pixel(int x, int y, int color);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:The color of the point on the screen
Input : x			x coordinate
		  y			y coordinate
Output : Nothing			
return: 0			Point color
*************************************************************************************/
LIB_EXPORT int gui_get_pixel(int x, int y);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Display text on the screen ,Show only English
Input : x			x coordinate
		  y			y coordinate
		  text		Text content
Output : Nothing			
return: 0			success
*************************************************************************************/
LIB_EXPORT int gui_text_out(int x, int y, char * text);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Get the display width of the text 
Input : text		Text content
Output : Nothing			
return: 			Text width
*************************************************************************************/
LIB_EXPORT int gui_get_text_width(char *text);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Get the display height of the text
Input : text		Text content
Output : Nothing			
return: 			Text height
*************************************************************************************/
LIB_EXPORT int gui_get_text_height(char *text);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Draw line
Input : x1		Point 1 X coordinate
		  x2		Point 2 X coordinate	
		  y1		Point 1 Y coordinate
		  y2		Point 2 Y coordinate
		  color		Line color	
Output : Nothing			
return: Nothing			
*************************************************************************************/
LIB_EXPORT void gui_cline(int x1, int y1, int x2, int y2, int color);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Get screen width
Input : 
Output : Nothing			
return: Screen width
*************************************************************************************/
LIB_EXPORT int gui_get_width(void);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Get screen height
Input : 
Output : Nothing			
return: Screen height
*************************************************************************************/
LIB_EXPORT int gui_get_height(void);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Display characters at the bottom left and bottom of the screen
Input : left_str		The character displayed in the lower left corner
		  right_str		The character displayed in the lower right corner	
Output : Nothing			
return: Nothing
*************************************************************************************/
LIB_EXPORT void gui_page_op_paint(char * left_str, char * right_str);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Set input method parameters
Input : def_mode		Default input method
		  allow_mode	Support input method
		  password      enter password
Output : Nothing			
return: Nothing
*************************************************************************************/
LIB_EXPORT int gui_ime_set_mode(int def_mode, int allow_mode, int password);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Open the input method page
Input : buffer		Input buffer
		  max			Maximum input character
		  position		Cursor position
		  help			Enter page title
Output : Nothing			
return: Input length
*************************************************************************************/
LIB_EXPORT int gui_ime_start_input(char * buffer, int max, int * position, char * help);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Add menu handler
Input : pfunc		Menu handler
Output : Nothing			
return: 0 success
*************************************************************************************/
LIB_EXPORT int gui_main_menu_func_add(void * pfunc);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Add menu item
Input : menu_item		Menu data
Output : Nothing			
return: 0 success
*************************************************************************************/
LIB_EXPORT int gui_main_menu_item_add(st_gui_menu_item_def * menu_item);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Display menu
Input : id		menu id
		timeover overtime time 
Output : Nothing			
return: 
*************************************************************************************/
LIB_EXPORT void gui_main_menu_show(char *id , int timeover);
LIB_EXPORT void gui_main_menu_show_ex(char *title,char *id , int timeover);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Send a message
Input : msg_id		Message id
		  wparam		parameter 1
		  lparam		parameter 2
Output : Nothing			
return: 0 success
*************************************************************************************/
LIB_EXPORT unsigned int gui_post_message(unsigned int msg_id, unsigned int wparam, unsigned int lparam);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:recv a message
Input : timeover		overtime time
Output : pmsg			Message structure			
return: 0 success
*************************************************************************************/
LIB_EXPORT unsigned int gui_get_message( st_gui_message * pmsg , int timeover);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Let the system process the default message
Input : pmsg			Message structure
Output : Nothing			
return: 0 success
*************************************************************************************/
LIB_EXPORT int gui_proc_default_msg( st_gui_message * pmsg );


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Display dialog
Input : title			Message title
		  msg			Message content
		  pszLeftOp		Bottom left corner
		  pszRightOp	Tip in the lower right corner
		  timeover		overtime time
Output : Nothing			
return:   1			Confirm return
		  2			Cancel back
		  3			Timeout		
*************************************************************************************/
LIB_EXPORT int gui_messagebox_show(char *title, char *msg , char* pszLeftOp, char* pszRightOp , int timeover);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Load bmp into memory
Input : filename		Image name
Output : width			Image width
		  height		Picture height
return: Image content array, which needs to be released after use
*************************************************************************************/
LIB_EXPORT char * gui_load_bmp(char * filename , int *width , int *height);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Load bmp into memory
Input : filename		Image name
Output : width			Image width
		  height		Picture height
		  color         Color bits
return: Image content array, which needs to be released after use
*************************************************************************************/
LIB_EXPORT char * gui_load_bmp_ex(char * filename , int *width , int *height, int * color);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Load bmp into memory
Input : pbmp		Image content array
return: Nothing
*************************************************************************************/
LIB_EXPORT void gui_bmp_free(char * pbmp);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:display image
Input : x				X coordinate
		y				Y coordinate	
		pbits			Image data
		width			Image width
		height			Picture height
		mode			0 Positive display, 1 Reverse display
Output: Nothing
return: Nothing£¬Show attention to release pbits
*************************************************************************************/
LIB_EXPORT void gui_out_bits(int x, int y, unsigned char *pbits, int width , int height, int mode);



/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:linzhu
Functions:display image
Input : x				X coordinate
		  y				Y coordinate	
		  pbits			Image data
		  width			Image width
		  height		Picture height
		  mode			0 Positive display, 1 Reverse display
		  color			Bit color of the picture(1,4,24)		
Output : Nothing
return: Nothing£¬Show attention to release pbits
*************************************************************************************/
LIB_EXPORT void gui_out_bits_ex(int x, int y, unsigned char *pbits, int width , int height, int mode , int color);



/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lxz
Functions:display image
Input : x				X coordinate
		  y				Y coordinate	
		  pbits			Image data
		  width			Image width
		  height		Picture height
		  mode			0 Positive display, 1 Reverse display
		  zoom			Amplification factor
Output : Nothing
return: Nothing£¬Show attention to release pbits
*************************************************************************************/
LIB_EXPORT void gui_out_bits_zoom(int x, int y, unsigned char *pbits, int width , int height, int mode, int zoom);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:display text  Display different languages
Input : x				X coordinate
		y				Y coordinate	
		str				text
Output: Nothing
return: Nothing
*************************************************************************************/
LIB_EXPORT int gui_text_out_ex(int x, int y,char * str);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lxz
Functions:Setting Text Styles
Input : textStyle	TextStyle = 0 opaque, textStyle = 1 transparent	
Output: Nothing
return: Nothing
*************************************************************************************/

LIB_EXPORT void gui_settextstyle(int textStyle);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:linz
Functions:select page
Input : title:	the title of the select page
		items:	Menu items
		itemscount: Number of menu items 
		timeout:	Menu timeout
		select:	Default menu item
Output: Nothing
return: Nothing
*************************************************************************************/
LIB_EXPORT int gui_select_page_ex(char *title , char *items[],int itemscount,int timeover, int select);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Display text on the screen ,Show only English
Input :   pMsg		pmsg content
		  top		top  coordinate
		
Output : Nothing			
return: 0			success
*************************************************************************************/
LIB_EXPORT void  gui_textout_line_center(char *pMsg , int top);

LIB_EXPORT void  gui_textout_line_right(char *pMsg , int top);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lxz
Functions:Refresh the specified area
Input : left		Left border
		top		Upper boundary
		right		Right border
		bottom	Lower boundary
		color  Refresh with specified color	
Output : Nothing			
return: 0			success
*************************************************************************************/
LIB_EXPORT void gui_clear_rect(int left, int top, int right, int bottom, int color);


enum{
	GUI_LCD_INDEX_1,
	GUI_LCD_INDEX_2,
};
LIB_EXPORT void gui_lcd_set_index( int index);
