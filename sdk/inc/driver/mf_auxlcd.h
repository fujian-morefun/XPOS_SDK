#ifndef _MF_AUXLCD_H_
#define _MF_AUXLCD_H_

#ifdef __cplusplus
extern "C" {
#endif


int mf_auxlcd_init(void);
int auxlcd_flush(unsigned char  *data, int len);
int mf_auxlcd_contrast(int contrast);

//
//1/on,0/off
//
int mf_auxlcd_backlight(int status);

int mf_auxlcd_get_backlight(void);
void mf_lcd_set_palette(int *pColorD1, int *pColorD2, int *pColorD3, int *pColorD4, int *pColorD5, int *pColorD6);


enum
{
	MF_LCD_TYPE_MONOCHR,
	MF_LCD_TYPE_TFT,
};

void mf_lcd_select(int type);

void mf_touch_draw(int x ,int y, int pixel);

#ifdef __cplusplus
}
#endif

#endif /* __MF_AUXLCD_H */

