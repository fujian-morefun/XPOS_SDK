/*! \file 2ddraw.h
	\brief xgui 画图接口
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

//! 字体
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

//! 文本样式
enum UTEXTSTYLE {
	UTEXT_DEFAULT = 0,				///<默认
	UTEXT_SOLID = 0,				///<普通
	UTEXT_TRANSPARENT = 1,			///<透明
	UTEXT_XOR = 2,					///<异或
	UTEXT_UNDERLINE = 3					
};
//!画线样式
enum LINESTYLES {					
    SOLID_LINE   = 0,
    DASHED_LINE  = 1,
	SOLIDXOR_LINE = 2,
	DASHEDXOR_LINE = 3,
    USERBIT_LINE = 4				// User defined line style 
};

//! 线宽
enum LINEWIDTH {					// Line widths for get/setlinestyle 
    NORM_WIDTH  = 1,
    THICK_WIDTH = 3
};

//! 画图方式
enum PUTRESOPTS {		// res operators for putres 
    COPY_PUT = 0,       // MOV 
    XOR_PUT = 1,        // XOR 
    OR_PUT = 2,         // OR
    AND_PUT = 3,        // AND
    NOT_PUT = 4,        // NOT
	TRANS_PUT = 5		// TRANSTARENT 
};

//! 区域结构
typedef struct tagRECT{
    int    left;	///<左
    int    top;		///<上
    int    right;	///<右	
    int    bottom;	///<下
} RECT, *PRECT;

//! 点结构
typedef struct __point_st{
	int x;			///< 横向
	int y;			///< 纵向
} POINT;

typedef struct tagMemDc{
	int nLeft;
	int nTop;
	int nWidth;
	int nHeight;
	int nTimerID;
	char *pMembuf;
}MEMDC;



LIB_EXPORT void xgui_SetTextZoom(int size) ;
LIB_EXPORT void xgui_ResumeTextZoom() ;

LIB_EXPORT int xgui_GetTextZoom() ;


/**
* @brief 初始化绘图
* @param nMode 保留，设成0
* @return 
*/
LIB_EXPORT void xgui_2ddraw_init(int nMode);
/**
* @brief 设置前景色
* @param nColor 颜色值
* @return 
*/
LIB_EXPORT void xgui_SetColor(int nColor);
LIB_EXPORT void xgui_ResumeColor();
/**
* @brief 读取前景色
* @param 
* @return 颜色值
*/
LIB_EXPORT int xgui_GetColor(void) ;
/**
* @brief 设置背景色
* @param nColor 颜色值
* @return 
*/
LIB_EXPORT void xgui_SetBgColor(int nColor);
LIB_EXPORT void xgui_ResumeBgColor();
/**
* @brief 读取背景色
* @param 
* @return 颜色值
*/
LIB_EXPORT int xgui_GetBgColor(void)  ;
/**
* @brief 使用前景色画点
* @param nX 横向偏移
* @param nY 纵向偏移
* @return 
*/
LIB_EXPORT int xgui_Pixel(int nX, int nY) ;
/**
* @brief 从当前位置开始画线
* @param nX 横向偏移
* @param nY 纵向偏移
* @return 
*/
LIB_EXPORT void xgui_LineTo(int nX, int nY);
/**
* @brief 设置线的样式
* @param enuStyle 线样式
* @return 
*/
LIB_EXPORT void xgui_SetLineStyle(enum LINESTYLES enuStyle) ;
/**
* @brief 读取当前线样式
* @param 
* @return 
*/
LIB_EXPORT enum LINESTYLES xgui_GetLineStyle(void)  ;
/**
* @brief 设置线宽度
* @param enuWidth 线宽度
* @return 
*/
LIB_EXPORT void xgui_SetLineWidth(enum LINEWIDTH enuWidth) ;
/**
* @brief 读取线宽度
* @param 
* @return 线宽度
*/
LIB_EXPORT enum LINEWIDTH xgui_GetLineWidth(void)  ;
/**
* @brief 填充一块区域
* @param pRect 区域
* @return 
*/
LIB_EXPORT void xgui_Bar_RC(const RECT *pRect);
/**
* @brief 设置填充样式
* @param nStyle 样式
* @return 
*/
LIB_EXPORT void xgui_SetBarStyle(int nStyle) ;
/**
* @brief 读取填充样式
* @param 
* @return 
*/
LIB_EXPORT int xgui_GetBarStyle(void)  ;
/**
* @brief 设置填充颜色
* @param nColor 颜色值
* @return 
*/
LIB_EXPORT void xgui_SetBarFill(int nColor) ;
LIB_EXPORT void xgui_ResumeBarFill() ;
/**
* @brief 读取填充颜色
* @param 
* @return 颜色值
*/
LIB_EXPORT int xgui_GetBarFill(void)  ;
/**
* @brief 设置文本字体
* @param enuFont 字体
* @return 
*/
LIB_EXPORT void xgui_SetFont(enum UFONT enuFont) ;
LIB_EXPORT void xgui_ResumeFont() ;

/**
* @brief 读取当前字体
* @param 
* @return 
*/
LIB_EXPORT enum UFONT xgui_GetFont(void)  ;
/**
* @brief 设置文本颜色
* @param nColor 颜色值
* @return 
*/
LIB_EXPORT void xgui_SetTextColor(int nColor) ;
LIB_EXPORT void xgui_ResumeTextColor() ;

/**
* @brief 读取当前文本颜色
* @param 
* @return 颜色值
*/
LIB_EXPORT int xgui_GetTextColor(void)  ;
/**
* @brief 设置文本背景颜色
* @param nColor 颜色值
* @return 
*/
LIB_EXPORT void xgui_SetTextBgColor(int nColor) ;
LIB_EXPORT void xgui_ResumeTextBgColor() ;
/**
* @brief 读取当前文本颜色
* @param 
* @return 颜色值
*/
LIB_EXPORT int xgui_GetTextBgColor(void) ;
/**
* @brief 设置文本样式
* @param emuStyle 样式
* @return 
*/
LIB_EXPORT void xgui_SetTextStyle(enum UTEXTSTYLE emuStyle) ;
LIB_EXPORT void xgui_ResumeTextStyle() ;
/**
* @brief 读取文本样式
* @param 
* @return 文本样式 
*/
LIB_EXPORT enum UTEXTSTYLE xgui_GetTextStyle(void) ;
/**
* @brief 设置当前绘图位置
* @param pPoint 点位置
* @return 
*/
LIB_EXPORT void xgui_SetCurrent(const POINT* pPoint);
/**
* @brief 读取当前绘图位置
* @param pPoint 点位置
* @return 
*/
LIB_EXPORT void xgui_GetCurrent(POINT* pPoint) ;
/**
* @brief 读取当前位置横向偏移
* @param 
* @return 偏移值
*/
LIB_EXPORT int xgui_GetCurrentX(void)  ;
/**
* @brief 读取当前位置纵向偏移
* @param 
* @return 偏移值
*/
LIB_EXPORT int xgui_GetCurrentY(void) ;
/**
* @brief 读取当前视图区域
* @param pRect 区域
* @return 
*/
LIB_EXPORT void xgui_GetViewPort(RECT* pRect) ;
/**
* @brief 读取当前视图宽度
* @param 
* @return 宽度
*/
LIB_EXPORT int xgui_GetViewPortWidth(void)  ;
/**
* @brief 读取当前视图高度
* @param 
* @return 高度
*/
LIB_EXPORT int xgui_GetViewPortHeight(void)  ;
LIB_EXPORT int xgui_GetDCMode(void)  ;
LIB_EXPORT void xgui_SetDCMode(int nMode)  ;
/**
* @brief 清除当前视图
* @param 
* @return 
*/
LIB_EXPORT void xgui_ClearDC(void);
LIB_EXPORT void xgui_ClearRectDC(int left , int top , int right , int bottom);
/**
* @brief 画点
* @param nX 横向偏移
* @param nY 纵向偏移
* @param nColor 颜色
* @return 
*/

LIB_EXPORT void  xgui_ClearPartDC(int nPosy, int nHeight);

LIB_EXPORT int xgui_CPixel(int nX, int nY, int nColor);
/**
* @brief 读取点颜色
* @param nX 横向偏移
* @param nY 纵向偏移
* @return 颜色
*/
LIB_EXPORT int xgui_GetPixel(int nX, int nY);
/**
* @brief 设置当前视图
* @param nLeft 左
* @param nTop 上
* @param nRight 右
* @param nBottom 下
* @return 
*/
LIB_EXPORT int xgui_SetViewPort(int nLeft, int nTop, int nRight, int nBottom);
/**
* @brief 设置当前视图
* @param pRect 区域
* @return 
*/
LIB_EXPORT int xgui_SetViewPort_RC(RECT const *pRect);
/**
* @brief 画矩形
* @param pRect 矩形区域
* @return 
*/
LIB_EXPORT void xgui_RectAngle_RC(RECT const *pRect);
/**
* @brief 画矩形
* @param nLeft 左
* @param nTop 上
* @param nRight 右
* @param nBottom 下
* @return 
*/
LIB_EXPORT void xgui_RectAngle(int nLeft, int nTop, int nRight, int nBottom);
/**
* @brief 填充区域
* @param nLeft 左
* @param nTop 上
* @param nRight 右
* @param nBottom 下
* @return 
*/
LIB_EXPORT void xgui_Bar(int nX1, int nY1, int nX2, int nY2);
/**
* @brief 画圆
* @param nX	圆心横向偏移
* @param nY 圆心纵向偏移
* @param nRadius 半径
* @return 
*/
LIB_EXPORT void xgui_Circle(int nX, int nY, int nRadius);
/**
* @brief 输出字符串
* @param nX 横向偏移
* @param nY 纵向偏移
* @param strText 字符串
* @return 
*/
LIB_EXPORT int xgui_TextOut(int nX, int nY, const char *strText);
/**
* @brief 读取字符串宽度
* @param szText 字符串
* @return 宽度
*/
LIB_EXPORT int xgui_GetTextWidth(const char *szText) ;
/**
* @brief 读取字体ID
* @param emuFont 字体ID
* @return ID
*/
LIB_EXPORT int xgui_GetFontId(enum UFONT emuFont);
/**
* @brief 读取字符串宽度
* @param szText 字符串
* @param emuFont 字体ID
* @return 宽度
*/
LIB_EXPORT int xgui_GetTextWidth_font(const char *szText, enum UFONT emuFont);
/**
* @brief 读取字符串高度
* @param szText 字符串
* @return 高度
*/
LIB_EXPORT int xgui_GetTextHeight(const char *szText) ;
/**
* @brief 读取字符串高度
* @param szText 字符串
* @param emuFont 字体id
* @return  高度
*/
LIB_EXPORT int xgui_GetTextHeight_font(const char *szText, enum UFONT emuFont);
/**
* @brief 画线
* @param nX1 横向偏移1
* @param nY1 纵向偏移1
* @param nX2 横向偏移2
* @param nY2 纵向偏移2
* @return 
*/
LIB_EXPORT void xgui_Line(int nX1, int nY1, int nX2, int nY2);
/**
* @brief 画线
* @param nX1 横向偏移1
* @param nY1 纵向偏移1
* @param nX2 横向偏移2
* @param nY2 纵向偏移2
* @param nColor 颜色
* @return 
*/
LIB_EXPORT void xgui_CLine(int nX1, int nY1, int nX2, int nY2, int nColor);
/**
* @brief 画虚线
* @param nX1 横向偏移1
* @param nY1 纵向偏移1
* @param nX2 横向偏移2
* @param nY2 纵向偏移2
* @return 
*/
LIB_EXPORT void xgui_SolidLine(int nX1, int nY1, int nX2, int nY2);
LIB_EXPORT void xgui_XorLine(int nX1, int nY1, int nX2, int nY2);
LIB_EXPORT void xgui_DashedLine(int nX1, int nY1, int nX2, int nY2);
LIB_EXPORT void xgui_DashedXorLine(int nX1, int nY1, int nX2, int nY2);
/**
* @brief 批次刷新开始
* @return 
*/
LIB_EXPORT void xgui_BeginBatchPaint();
/**
* @brief 批次刷新结束
* @return 
*/
LIB_EXPORT void xgui_EndBatchPaint();
/**
* @brief 清除一块区域
* @param nLeft 左
* @param nTop 上
* @param nRight 右
* @param nBottom 下
* @param nColor 颜色
* @return 
*/


LIB_EXPORT int xgui_GetRefreshFlag();
LIB_EXPORT void xgui_SetRefreshFlag(int flag);
LIB_EXPORT void xgui_ClearRect(int nLeft, int nTop, int nRight, int nBottom, int nColor);
LIB_EXPORT void xgui_SetResOutMode(enum PUTRESOPTS nMode);
LIB_EXPORT enum PUTRESOPTS xgui_GetResOutMode(void);
LIB_EXPORT int xgui_DrawImageBW(GUIRES * pImageRes,  enum PUTRESOPTS nDrawMode /*= COPY_PUT*/, int x /*= 0*/, int y/* = 0*/);
LIB_EXPORT int xgui_DrawImage(GUIRES * pImageRes,  enum PUTRESOPTS nDrawMode /*= COPY_PUT*/, int x /*= 0*/, int y/* = 0*/);
LIB_EXPORT void xgui_GetResPos(POINT *pPoint);
/**
* @brief 全屏清除
* @param 
* @return 
*/
LIB_EXPORT void xgui_ClearScreen(void);
/**
* @brief xgui_GetWidth 读取屏幕宽度
* @param 
* @return 
*/
LIB_EXPORT int xgui_GetWidth(void);

/**
* @brief 读取屏幕高度
* @param 
* @return 
*/
LIB_EXPORT int xgui_GetHeight(void);
/**
* @brief 画左右按钮
* @param szLeftOp 左按钮
* @param szRightOp 右按钮
* @return 
*/

LIB_EXPORT int xgui_GetStateHeight(void);
LIB_EXPORT int xgui_GetAllHeight(void);

LIB_EXPORT void xgui_Page_OP_Paint(char * szLeftOp, char * szRightOp);
/**
* @brief 清除全屏
* @return 
*/
LIB_EXPORT void xgui_Clear_Win();
/**
* @brief xgui_ToRect 设置区域
* @param rect 区域
* @param l 左
* @param r 右
* @param t 上
* @param b 下
* @return 
*/
LIB_EXPORT void xgui_ToRect(RECT * rect , int l , int r , int t , int b);

/**
* @brief 在整个屏幕中间输出字符串
* @param pMsg 字符串
* @return 
*/
LIB_EXPORT void xgui_TextOut_Win_Center(char *pMsg);

/**
* @brief 在屏幕横向居中输出字符串
* @param pMsg 字符串
* @param top 纵向位置
* @return 
*/
LIB_EXPORT void xgui_TextOut_Line_Center(char *pMsg , int top);
LIB_EXPORT void xgui_TextOut_Line_Right(char *pMsg , int top);
LIB_EXPORT void xgui_TextOut_Line_Left(char *pMsg , int top);
LIB_EXPORT void xgui_TextOut_Multi_Line(char *str , int linetop, int top, int left, int width);

/**
* @brief 屏幕上画点阵
* @param x 横向偏移
* @param y 纵向偏移
* @param pbits 点阵
* @param width 宽度
* @param height 高度
* @param mode 方式
* @return 
*/
LIB_EXPORT void xgui_out_bits_bmp(int x, int y, unsigned char *pbits, int width , int height, int mode, int color);
LIB_EXPORT void xgui_out_bits(int x, int y, unsigned char *pbits, int width , int height, int mode);
LIB_EXPORT void xgui_out_bits_auto(int x, int y, unsigned char *pbits, int width , int height, int mode);
LIB_EXPORT void xgui_out_bits_zoom(int x, int y, unsigned char *pbits, int width , int height, int mode, int zoom);
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

#define STATE_BMP_COLOR			xgui_GetDefineColor(0)		// 状态栏图标颜色
#define STATE_BACK_FILL_COLOR	xgui_GetDefineColor(1)		// 状态栏背景图	
#define STATE_BACK_LINE_COLOR	xgui_GetDefineColor(2)		//

#define XGUI_COLOR_RED			xgui_GetDefineColor(3)		// 红色
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

#define XGUI_LINE_TOP_0			xgui_GetLineTop(0)		// 标题栏
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
void xgui_init_color();

#define XGUI_TITLE_HEIGHT		xgui_title_height()
#define HZ_WIDTH	xgui_hz_width()
#define HZ_HEIGHT	xgui_hz_height()

#define ASCII_WIDTH		xgui_ascii_width()
#define ASCII_HEIGHT	xgui_ascii_height()
#define XGUI_LINE_TOP_BOTTOM	xgui_line_top_bottom()	

#define LCD_IS_120_160	(xgui_GetWidth() == 120 && xgui_GetAllHeight() == 160)
#define LCD_IS_160_120	(xgui_GetWidth() == 160 && xgui_GetAllHeight() == 120)
#define LCD_IS_128_128	(xgui_GetWidth() == 128 && xgui_GetAllHeight() == 128)
#define LCD_IS_128_32	(xgui_GetWidth() == 128 && xgui_GetAllHeight() == 32)
#define LCD_IS_128_64	(xgui_GetWidth() == 128 && xgui_GetAllHeight() == 64)
#define LCD_IS_240_320	(xgui_GetWidth() == 240 && xgui_GetAllHeight() == 320)
#define LCD_IS_320_240	(xgui_GetWidth() == 320 && xgui_GetAllHeight() == 240)

#define LCD_IS_320 LCD_IS_320_240
#define LCD_IS_128 LCD_IS_128_64
#define LCD_IS_160 LCD_IS_160_120
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