#ifndef _MF_SYSTEM_H_
#define _MF_SYSTEM_H_

#ifdef __cplusplus
extern "C" {
#endif

int mf_hardware_ver(void);
char *mf_fatfs_ver(void);
char *mf_fal_ver(void);
char *mf_hal_ver(void);
char *mf_boot_ver(void);
//
//FAL
//
int MF_FAL_StartCompactor(void);

int mf_printf_syncobj(int (*lock)(int status));

int mf_stdout(const unsigned char * buffer, int size);
int mf_stdout_irq(const unsigned char * buffer, int size);

void mf_log_debug(const char *pcString, ...);


enum
{
	MF_LCD_IC_ILI9342,	//2.3
	MF_LCD_IC_ST7789V,	//2.4
	MF_LCD_IC_ST75256,	//16096
};

enum
{
	MF_LCD_TYPE_MONO_128_64,
	MF_LCD_TYPE_MONO_160_96,
	MF_LCD_TYPE_TFT_320_240,
};

int mf_get_lcd_type(void);
int mf_get_lcd_fulltype(void);
int mf_get_lcd_ic(void);

enum {
	DEVICE_TYPE_M60A_ST,
	DEVICE_TYPE_M60A_K21,
	DEVICE_TYPE_M60B_ST,
	DEVICE_TYPE_M60B_K21,
	DEVICE_TYPE_M90L,
	DEVICE_TYPE_M90L_K21,
	DEVICE_TYPE_M90L_BCM5892,
	DEVICE_TYPE_M60C_GD,
	DEVICE_TYPE_MP60_K21,
	DEVICE_TYPE_MP60_TMC3100,
	DEVICE_TYPE_MP60_MH1901C,
	DEVICE_TYPE_M90_MH1901C,
	DEVICE_TYPE_MP60_MH1902,
};


int mf_get_device_type(void);

void mf_console_switch(int on);

void mf_suspend_ucos(int suspend);

unsigned int mf_get_jiffies(void);

enum {
	VENDOR_MOREFUN = 1,
	VENDOR_UNKNOWN = 10,
};

int mf_board_vendor(void);

int mf_android_is_sleep(void);

void mf_get_cpuid(unsigned char *id);

void mf_icc_enforce_clk(int clk);

int mf_android_run_normal(void);
int mf_android_run_lock(void);

int mf_get_syscode(void);

#ifdef __cplusplus
}
#endif


#endif /* __MF_SYSTEM_H */
