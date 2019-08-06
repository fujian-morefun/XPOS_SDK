#ifndef ___DRAW_BUF_H___
#define ___DRAW_BUF_H___

#include "xgui_pub.h"

#if defined(__cplusplus)
extern "C" {    
#endif

int lcd_GetStateHeight();
int lcd_GetAllHeight();

void lcd_set_mode(int mode);
int lcd_OpenDevice(void);
int lcd_GetWidth(void);
int lcd_GetHeight(void);

static int lcd_color24to16(int color);
static int lcd_color16to24(int color);

//LIB_EXPORT unsigned char * xGui_GetLcdBuff();

void lcd_SetPixel(int nX, int nY, int nColor);
int lcd_GetPixel(int nX, int nY);
void lcd_SetHLine(int nX, int nY, int nLength, int nColor);
//void lcd_SetVLine(int nX, int nY, int nLength, int nColor);
//void lcd_Clear(int nColor);
LIB_EXPORT void lcd_Refresh(void);
void lcd_clear_refresh_task_count();

void lcd_SetStatePixel(int nX, int nY, int nColor);
int lcd_GetStatePixel(int nX, int nY);
//void lcd_ClearStateBuff(int nColor);
void lcd_SetStateHLine(int nX, int nY, int nLength, int nColor);

LIB_EXPORT void lcd_set_palette(int * cd1, int *cd2, int *cd3, int *cd4, int *cd5, int *cd6);

LIB_EXPORT void lcd_set_refresh();
LIB_EXPORT void lcd_set_auxlcd_func(void * func);

LIB_EXPORT int lcd_get_buff_width();
LIB_EXPORT int lcd_get_all_height();
LIB_EXPORT int lcd_get_color_size();

#if defined(__cplusplus)
}
#endif 

#endif
