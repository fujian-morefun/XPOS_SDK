/*! \file 2ddraw.h
	\brief xgui Drawing interface
*	\author lx
*	\date 2014/02/07
*/
#ifndef ___2DDRAW_H___
#define ___2DDRAW_H___

#include "xgui_pub.h"
#include "res.h"

#define XGUI_WIN_WIDTH		xgui_GetWidth()
#define XGUI_WIN_HEIGHT		xgui_GetHeight()
#define XGUI_WIN_RIGHT		(xgui_GetWidth() - 1)
#define XGUI_WIN_BOTTOM		(xgui_GetHeight() - 1)
#define XGUI_SET_WIN_RC		xgui_SetViewPort(0 , 0, XGUI_WIN_RIGHT , XGUI_WIN_BOTTOM)

#define UPUTDC	0
#define UMEMDC	1

//BAR STYLES
#define SOLID_BAR 1					// normal style 
#define TRANSPARENT_BAR 2			// transparent style 
#define BAR_WITH_FRAME 4			// with two rectangle frames 
#define BAR_WITH_SHADOW 8			// with shadow 
#define BAR_WITH_SINGLE_FRAME 16	// bar with single frame 
#define BAR_WITH_3D	32				// draw bar with 3D 

//bitblt attribute
#define COPYSRC		0
#define XORCOPY		1

#define SCROLL_BIT_PERCERT	8		// move bit at percent time

//! Font
enum UFONT {
	UFONT_COURIER = 0,				///<12-
	UFONT_FIXEDSYS = 1,				///<12-
	UFONT_NORMAL = 2,				///<16-   default font is UFONT_TERMINAL
	UFONT_SYSTEM = 3,				///<12-
	UFONT_TERMINAL = 4,				///<12-
	UFONT_VGAROM = 5,				///<16-
	UFONT_TITLE = 6,				///<12-
	UFONT_SANSSERIF = 7,
	UFONT_SMM = 8
};

//! Text Style
enum UTEXTSTYLE {
	UTEXT_DEFAULT = 0,				///<default
	UTEXT_SOLID = 0,				///<normal
	UTEXT_TRANSPARENT = 1,			        ///<transparency
	UTEXT_XOR = 2					///<xor
};
//!Line drawing style
enum LINESTYLES {					
    SOLID_LINE   = 0,
    DASHED_LINE  = 1,
	SOLIDXOR_LINE = 2,
	DASHEDXOR_LINE = 3,
    USERBIT_LINE = 4				// User defined line style 
};

//! line weight
enum LINEWIDTH {				// Line widths for get/setlinestyle 
    NORM_WIDTH  = 1,
    THICK_WIDTH = 3
};

//! Drawing way
enum PUTRESOPTS {		// res operators for putres 
    COPY_PUT = 0,       // MOV 
    XOR_PUT = 1,        // XOR 
    OR_PUT = 2,         // OR
    AND_PUT = 3,        // AND
    NOT_PUT = 4,        // NOT
	TRANS_PUT = 5		// TRANSTARENT 
};

//! domain structure
typedef struct tagRECT{
    int    left;	///<left
    int    top;		///<up
    int    right;	///<right	
    int    bottom;	///<down
} RECT, *PRECT;

//! dot structure
typedef struct __point_st{
	int x;			///< landscape
	int y;			///< lengthways
} POINT;

typedef struct tagMemDc{
	int nLeft;
	int nTop;
	int nWidth;
	int nHeight;
	int nTimerID;
	char *pMembuf;
}MEMDC;


LIB_EXPORT int xgui_IsGbkChar(const unsigned char *ch);

LIB_EXPORT void xgui_SetTextZoom(int size) ;
LIB_EXPORT void xgui_ResumeTextZoom() ;

LIB_EXPORT int xgui_GetTextZoom() ;


/**
* @brief Initialization drawing
* @param nMode retain，set 0
* @return 
*/
LIB_EXPORT void xgui_2ddraw_init(int nMode);
/**
* @brief set foreground color
* @param nColor color value
* @return 
*/
LIB_EXPORT void xgui_SetColor(int nColor);
LIB_EXPORT void xgui_ResumeColor();
/**
* @brief get foreground color
* @param 
* @return color value
*/
LIB_EXPORT int xgui_GetColor(void) ;
/**
* @brief set background color
* @param nColor color value
* @return 
*/
LIB_EXPORT void xgui_SetBgColor(int nColor);
LIB_EXPORT void xgui_ResumeBgColor();
/**
* @brief get background color
* @param 
* @return color value
*/
LIB_EXPORT int xgui_GetBgColor(void)  ;
/**
* @brief Create point use foreground color
* @param nX lateral offset
* @param nY longitudinal offset
* @return 
*/
LIB_EXPORT int xgui_Pixel(int nX, int nY) ;
/**
* @brief Draw the line from the current position
* @param nX lateral offset
* @param nY longitudinal offset
* @return 
*/
LIB_EXPORT void xgui_LineTo(int nX, int nY);
/**
* @brief Sets the style of the line
* @param enuStyle Line Style
* @return 
*/
LIB_EXPORT void xgui_SetLineStyle(enum LINESTYLES enuStyle) ;
/**
* @brief Get the style of the line
* @param 
* @return 
*/
LIB_EXPORT enum LINESTYLES xgui_GetLineStyle(void)  ;
/**
* @brief Set line width
* @param enuWidth line width
* @return 
*/
LIB_EXPORT void xgui_SetLineWidth(enum LINEWIDTH enuWidth) ;
/**
* @brief Get line width
* @param 
* @return line width
*/
LIB_EXPORT enum LINEWIDTH xgui_GetLineWidth(void)  ;
/**
* @brief Fill one area
* @param pRect area
* @return 
*/
LIB_EXPORT void xgui_Bar_RC(const RECT *pRect);
/**
* @brief Set fill style
* @param nStyle style
* @return 
*/
LIB_EXPORT void xgui_SetBarStyle(int nStyle) ;
/**
* @brief Get fill style
* @param 
* @return 
*/
LIB_EXPORT int xgui_GetBarStyle(void)  ;
/**
* @brief Set fill color
* @param nColor color value
* @return 
*/
LIB_EXPORT void xgui_SetBarFill(int nColor) ;
LIB_EXPORT void xgui_ResumeBarFill() ;
/**
* @brief Get fill color
* @param 
* @return color value
*/
LIB_EXPORT int xgui_GetBarFill(void)  ;
/**
* @brief Set text font
* @param enuFont font
* @return 
*/
LIB_EXPORT void xgui_SetFont(enum UFONT enuFont) ;
LIB_EXPORT void xgui_ResumeFont() ;

/**
* @brief Get current font
* @param 
* @return 
*/
LIB_EXPORT enum UFONT xgui_GetFont(void)  ;
/**
* @brief Set text color
* @param nColor color value
* @return 
*/
LIB_EXPORT void xgui_SetTextColor(int nColor) ;
LIB_EXPORT void xgui_ResumeTextColor() ;

/**
* @brief Get the current text color
* @param 
* @return color value
*/
LIB_EXPORT int xgui_GetTextColor(void)  ;
/**
* @brief Set the text background color
* @param nColor color value
* @return 
*/
LIB_EXPORT void xgui_SetTextBgColor(int nColor) ;
LIB_EXPORT void xgui_ResumeTextBgColor() ;
/**
* @brief Get the current text color
* @param 
* @return color value
*/
LIB_EXPORT int xgui_GetTextBgColor(void) ;
/**
* @brief Set text style
* @param emuStyle 样式
* @return 
*/
LIB_EXPORT void xgui_SetTextStyle(enum UTEXTSTYLE emuStyle) ;
LIB_EXPORT void xgui_ResumeTextStyle() ;
/**
* @brief Get text style
* @param 
* @return text style 
*/
LIB_EXPORT enum UTEXTSTYLE xgui_GetTextStyle(void) ;
/**
* @brief Set the current drawing position
* @param pPoint Point Location
* @return 
*/
LIB_EXPORT void xgui_SetCurrent(const POINT* pPoint);
/**
* @brief Get the current drawing position
* @param pPoint Point Location
* @return 
*/
LIB_EXPORT void xgui_GetCurrent(POINT* pPoint) ;
/**
* @brief Get the current position transverse offset
* @param 
* @return Offsets
*/
LIB_EXPORT int xgui_GetCurrentX(void)  ;
/**
* @brief  the current position longitudinal offset
* @param 
* @return Offsets
*/
LIB_EXPORT int xgui_GetCurrentY(void) ;
/**
* @brief Get the current view area
* @param pRect area
* @return 
*/
LIB_EXPORT void xgui_GetViewPort(RECT* pRect) ;
/**
* @brief Get the current view width
* @param 
* @return width
*/
LIB_EXPORT int xgui_GetViewPortWidth(void)  ;
/**
* @brief Get the current view height
* @param 
* @return height
*/
LIB_EXPORT int xgui_GetViewPortHeight(void)  ;
LIB_EXPORT int xgui_GetDCMode(void)  ;
LIB_EXPORT void xgui_SetDCMode(int nMode)  ;
/**
* @brief Clear current view
* @param 
* @return 
*/
LIB_EXPORT void xgui_ClearDC(void);
LIB_EXPORT void xgui_ClearRectDC(int left , int top , int right , int bottom);
/**
* @brief Create Point
* @param nX lateral offset
* @param nY longitudinal offset
* @param nColor color
* @return 
*/

LIB_EXPORT void  xgui_ClearPartDC(int nPosy, int nHeight);

LIB_EXPORT int xgui_CPixel(int nX, int nY, int nColor);
/**
* @brief Get point colo
* @param nX lateral offset
* @param nY longitudinal offset
* @return color
*/
LIB_EXPORT int xgui_GetPixel(int nX, int nY);
/**
* @brief Set current View
* @param nLeft left
* @param nTop up
* @param nRight right
* @param nBottom down
* @return 
*/
LIB_EXPORT int xgui_SetViewPort(int nLeft, int nTop, int nRight, int nBottom);
/**
* @brief Set current View
* @param pRect area
* @return 
*/
LIB_EXPORT int xgui_SetViewPort_RC(RECT const *pRect);
/**
* @brief drawRect
* @param pRect Rectangular Area
* @return 
*/
LIB_EXPORT void xgui_RectAngle_RC(RECT const *pRect);
/**
* @brief drawRect
* @param nLeft left
* @param nTop up
* @param nRight right
* @param nBottom down
* @return 
*/
LIB_EXPORT void xgui_RectAngle(int nLeft, int nTop, int nRight, int nBottom);
/**
* @brief fill area
* @param nLeft left
* @param nTop up
* @param nRight right
* @param nBottom down
* @return 
*/
LIB_EXPORT void xgui_Bar(int nX1, int nY1, int nX2, int nY2);
/**
* @brief draw a circle
* @param nX center lateral offset
* @param nY center longitudinal offset
* @param nRadius radius
* @return 
*/
LIB_EXPORT void xgui_Circle(int nX, int nY, int nRadius);
/**
* @brief output string
* @param nX lateral offset
* @param nY longitudinal offset
* @param strText string
* @return 
*/
LIB_EXPORT int xgui_TextOut(int nX, int nY, const char *strText);
/**
* @brief Get string width
* @param szText string
* @return width
*/
LIB_EXPORT int xgui_GetTextWidth(const char *szText) ;
/**
* @brief Get font ID
* @param emuFont font ID
* @return ID
*/
LIB_EXPORT int xgui_GetFontId(enum UFONT emuFont);
/**
* @brief  Get string width
* @param szText string
* @param emuFont font ID
* @return width
*/
LIB_EXPORT int xgui_GetTextWidth_font(const char *szText, enum UFONT emuFont);
/**
* @brief Get the height of the string
* @param szText string
* @return height
*/
LIB_EXPORT int xgui_GetTextHeight(const char *szText) ;
/**
* @brief Get the height of the string
* @param szText string
* @param emuFont font id
* @return  height
*/
LIB_EXPORT int xgui_GetTextHeight_font(const char *szText, enum UFONT emuFont);
/**
* @brief Line Drawing
* @param nX1 lateral offset 1
* @param nY1 longitudinal offset 1
* @param nX2 lateral offset 2
* @param nY2 longitudinal offset 2
* @return 
*/
LIB_EXPORT void xgui_Line(int nX1, int nY1, int nX2, int nY2);
/**
* @brief Line Drawing
* @param nX1 lateral offset 1
* @param nY1 longitudinal offset 1
* @param nX2 lateral offset 2
* @param nY2 longitudinal offset 2
* @param nColor color
* @return 
*/
LIB_EXPORT void xgui_CLine(int nX1, int nY1, int nX2, int nY2, int nColor);
/**
* @brief Painting Dotted Line
* @param nX1 lateral offset 1
* @param nY1 longitudinal offset 1
* @param nX2 lateral offset 2
* @param nY2 longitudinal offset 2
* @return 
*/
LIB_EXPORT void xgui_SolidLine(int nX1, int nY1, int nX2, int nY2);
LIB_EXPORT void xgui_XorLine(int nX1, int nY1, int nX2, int nY2);
LIB_EXPORT void xgui_DashedLine(int nX1, int nY1, int nX2, int nY2);
LIB_EXPORT void xgui_DashedXorLine(int nX1, int nY1, int nX2, int nY2);
/**
* @brief Batch refresh begins
* @return 
*/
LIB_EXPORT void xgui_BeginBatchPaint();
/**
* @brief Batch refresh ends
* @return 
*/
LIB_EXPORT void xgui_EndBatchPaint();
/**
* @brief Clear an area
* @param nLeft left
* @param nTop up
* @param nRight right
* @param nBottom down
* @param nColor color
* @return 
*/
LIB_EXPORT void xgui_ClearRect(int nLeft, int nTop, int nRight, int nBottom, int nColor);
LIB_EXPORT void xgui_SetResOutMode(enum PUTRESOPTS nMode);
LIB_EXPORT enum PUTRESOPTS xgui_GetResOutMode(void);
LIB_EXPORT int xgui_DrawImageBW(GUIRES * pImageRes,  enum PUTRESOPTS nDrawMode /*= COPY_PUT*/, int x /*= 0*/, int y/* = 0*/);
LIB_EXPORT int xgui_DrawImage(GUIRES * pImageRes,  enum PUTRESOPTS nDrawMode /*= COPY_PUT*/, int x /*= 0*/, int y/* = 0*/);
LIB_EXPORT void xgui_GetResPos(POINT *pPoint);
/**
* @brief Full screen clear
* @param 
* @return 
*/
LIB_EXPORT void xgui_ClearScreen(void);
/**
* @brief xgui_GetWidth get screen width
* @param 
* @return 
*/
LIB_EXPORT int xgui_GetWidth(void);

/**
* @brief get screen height
* @param 
* @return 
*/
LIB_EXPORT int xgui_GetHeight(void);
/**
* @brief Draw left and right buttons
* @param szLeftOp left button
* @param szRightOp right button
* @return 
*/

LIB_EXPORT int xgui_GetStateHeight(void);
LIB_EXPORT int xgui_GetAllHeight(void);

LIB_EXPORT void xgui_Page_OP_Paint(char * szLeftOp, char * szRightOp);
/**
* @brief clear full screen
* @return 
*/
LIB_EXPORT void xgui_Clear_Win();
/**
* @brief xgui_ToRect Set Region
* @param rect region
* @param l left
* @param r right
* @param t up
* @param b down
* @return 
*/
LIB_EXPORT void xgui_ToRect(RECT * rect , int l , int r , int t , int b);

/**
* @brief Output the string across the screen
* @param pMsg character string
* @return 
*/
LIB_EXPORT void xgui_TextOut_Win_Center(char *pMsg);

/**
* @brief Horizontally center the output string across the screen
* @param pMsg character string
* @param top longitudinal offset
* @return 
*/
LIB_EXPORT void xgui_TextOut_Line_Center(char *pMsg , int top);
LIB_EXPORT void xgui_TextOut_Line_Right(char *pMsg , int top);
LIB_EXPORT void xgui_TextOut_Line_Left(char *pMsg , int top);

/**
* @brief Draw a grid on the screen
* @param x lateral offset
* @param y longitudinal offset
* @param pbits dot matrix
* @param width 
* @param height 
* @param mode 
* @return 
*/
LIB_EXPORT void xgui_out_bits_bmp(int x, int y, unsigned char *pbits, int width , int height, int mode, int color);
LIB_EXPORT void xgui_out_bits(int x, int y, unsigned char *pbits, int width , int height, int mode);
LIB_EXPORT void xgui_out_bits_bmp24bit(int x, int y, unsigned char *pbits, int width , int height, int mode);
LIB_EXPORT void xgui_out_bits_bmp4bit( int x, int y, unsigned char *pbits, int width , int height, int mode );
LIB_EXPORT int xgui_get_color_size();

LIB_EXPORT void xgui_cleart_state(int left , int width);

LIB_EXPORT void xgui_set_lcd_mode(int mode);
LIB_EXPORT int xgui_get_lcd_mode(int mode);

LIB_EXPORT void xgui_out_state_bits(int x, int y, unsigned char *pbits, int width , int height, int mode);
LIB_EXPORT void xgui_out_state_bits_color(int x, int y, unsigned char *pbits, int width , int height, int mode , int fc ,int bc);

LIB_EXPORT void xgui_BeginStatePaint();
LIB_EXPORT void xgui_EndStatePaint();


LIB_EXPORT void xgui_set_text_color_state(int color);
LIB_EXPORT int xgui_text_out_state(int nX, int nY, const char *strText);


LIB_EXPORT void xgui_SetTitle(char *title);

LIB_EXPORT int xgui_GetDefineColor(int index);

#define STATE_BMP_COLOR			xgui_GetDefineColor(0)		// Status bar icon color
#define STATE_BACK_FILL_COLOR	xgui_GetDefineColor(1)		        // Status bar background map
#define STATE_BACK_LINE_COLOR	xgui_GetDefineColor(2)		        //

#define XGUI_COLOR_RED			xgui_GetDefineColor(3)		// red
#define XGUI_COLOR_GREEN		xgui_GetDefineColor(4)		// 
#define XGUI_COLOR_BLUE			xgui_GetDefineColor(5)

#define XGUI_COLOR_BACK			xgui_GetDefineColor(6)
#define XGUI_COLOR_FORE			xgui_GetDefineColor(7)

#define XGUI_COLOR_FONT_BACK	xgui_GetDefineColor(8)
#define XGUI_COLOR_FONT_FORE	xgui_GetDefineColor(9)

#define XGUI_COLOR_FILL			xgui_GetDefineColor(10)

#define XGUI_COLOR_TITLE_FORE	xgui_GetDefineColor(11)
#define XGUI_COLOR_TITLE_BACK	xgui_GetDefineColor(12)


LIB_EXPORT int xgui_GetLineTop(int index);
LIB_EXPORT int xgui_GetLineSize(int index);
LIB_EXPORT int xgui_GetLineTotal();

#define XGUI_TEXT_LINE1			0
#define XGUI_TEXT_LINE2			12
#define XGUI_TEXT_LINE3			24
#define XGUI_TEXT_LINE4			36

#define XGUI_LINE_TOP_0			xgui_GetLineTop(0)		// title bar
#define XGUI_LINE_TOP_1			xgui_GetLineTop(1)		// 
#define XGUI_LINE_TOP_2			xgui_GetLineTop(2)		// 
#define XGUI_LINE_TOP_3			xgui_GetLineTop(3)		// 
#define XGUI_LINE_TOP_4			xgui_GetLineTop(4)		// 
#define XGUI_LINE_TOP_5			xgui_GetLineTop(5)		// 
#define XGUI_LINE_TOP_6			xgui_GetLineTop(6)		// 
#define XGUI_LINE_TOP_7			xgui_GetLineTop(7)		// 
#define XGUI_LINE_TOP_8			xgui_GetLineTop(8)		// 
#define XGUI_LINE_TOP_9			xgui_GetLineTop(9)		// 
#define XGUI_LINE_TOP_10		xgui_GetLineTop(10)
#define XGUI_LINE_TOP_11		xgui_GetLineTop(11)

#define XGUI_RGB(r,g,b)          ((int) ( ((int)(r) << 16)|((int)((int)(g))<< 8) | ((int)(b)) ))			

LIB_EXPORT int xgui_line_height();
LIB_EXPORT int xgui_line_base();
LIB_EXPORT int xgui_title_height();
LIB_EXPORT int xgui_hz_width();
LIB_EXPORT int xgui_hz_height();
LIB_EXPORT int xgui_ascii_width();
LIB_EXPORT int xgui_ascii_height();
LIB_EXPORT int xgui_line_top_bottom();
LIB_EXPORT void xgui_lcd2_show_msg(char * line1, char *line2);
void xgui_init_zoom();

#ifdef LCD_320_240
	#define XGUI_TITLE_HEIGHT		xgui_title_height()
	#define HZ_WIDTH	xgui_hz_width()
	#define HZ_HEIGHT	xgui_hz_height()
	
	#define ASCII_WIDTH		xgui_ascii_width()
	#define ASCII_HEIGHT	xgui_ascii_height()
	#define XGUI_LINE_TOP_BOTTOM	xgui_line_top_bottom()	
#else
	#define XGUI_TITLE_HEIGHT		12
	#define HZ_WIDTH	12
	#define HZ_HEIGHT	12
	
	#define ASCII_WIDTH		8
	#define ASCII_HEIGHT	12
	#define XGUI_LINE_TOP_BOTTOM	XGUI_LINE_TOP_4
#endif

#define LCD_IS_120_160	(xgui_GetWidth() == 120 && xgui_GetAllHeight() == 160)
#define LCD_IS_160_120	(xgui_GetWidth() == 160 && xgui_GetAllHeight() == 120)
#define LCD_IS_128	(xgui_GetWidth() == 128 )
#define LCD_IS_128_128	(xgui_GetWidth() == 128 && xgui_GetAllHeight() == 128)
#define LCD_IS_128_32	(xgui_GetWidth() == 128 && xgui_GetAllHeight() == 32)
#define LCD_IS_240_320	(xgui_GetWidth() == 240 && xgui_GetAllHeight() == 320)
#define LCD_IS_320_240	(xgui_GetWidth() == 320 && xgui_GetAllHeight() == 240)

#define LCD_IS_TFT_SCREEN	(LCD_IS_240_320 || LCD_IS_320_240)

#define LCD_GET_ZOOM	((LCD_IS_TFT_SCREEN) ? 2 : 1)

#define LCD_IS_16_BIT	(xgui_get_color_size() == 16)									// 16位色
#define LCD_IS_4_BIT	(xgui_get_color_size() == 3 || xgui_get_color_size() == 4)
#define LCD_IS_1_BIT	(xgui_get_color_size() == 1)

#define XGUI_128_32_LINE1			3
#define XGUI_128_32_LINE2			18
#define XGUI_128_32_LINE_LEFT		0
#define XGUI_128_32_LINE_CENTER		64

#define LCD_IS_LCD2		(xgui_GetWidth() == 128 && xgui_GetAllHeight() == 32)

#endif