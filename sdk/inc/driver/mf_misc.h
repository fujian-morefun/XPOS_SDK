#ifndef _MF_MISC_H_
#define _MF_MISC_H_

#ifdef __cplusplus
extern "C" {
#endif

int mf_misc_init(void);

int mf_gsm_status(void);
int mf_gsm_start(void);
int mf_gsm_stop(void);


//
//on:1 off:0
//
int mf_buzzer_control(int status);
int mf_buzzer_control_ext(int freq, int ms);
int mf_wifi_upgrademode(void);

enum
{
	//
	//RFID LED
	//
	MF_LED1,
	MF_LED2,
	MF_LED3,
	MF_LED4,

	//
	//STATUE LED
	//
	MF_LED5
};

enum
{
	MF_LED_RED = 1,
	MF_LED_GREEN,
	MF_LED_YELLOW,
};

int mf_led_control(int led , int status);
int mf_jtag_control(int status);

int mf_jtag_status(void);

int mf_5vout(int status);

void mf_gsm_suspend(void);
void mf_gsm_resume(void);

int mf_get_flash_size(void);

int mf_barcode_trig(int on);

#ifdef __cplusplus
}
#endif

#endif /* __MF_MISC_H */

