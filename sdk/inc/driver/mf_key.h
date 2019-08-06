/* 
 * Copyright (c) 2015 MoreFun
 *
 * @date 2015-3-24
 * @author ZhaoJinYun
 *
*/

#ifndef __MF_KEY_H
#define __MF_KEY_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Keys define
 *
 */

#define KEY_ESC				(1)
#define KEY_1				(2)
#define KEY_2				(3)
#define KEY_3				(4)
#define KEY_4				(5)
#define KEY_5				(6)
#define KEY_6				(7)
#define KEY_7				(8)
#define KEY_8				(9)
#define KEY_9				(10)
#define KEY_0				(11)
#define KEY_BACKSPACE		(14)
#define KEY_ENTER			(28)

#define KEY_F1				(59)
#define KEY_F2				(60)
#define KEY_F3				(61)
#define KEY_F4				(62)
#define KEY_F5				(63)
#define KEY_F6				(64)
#define KEY_F7				(65)
#define KEY_F8				(66)
#define KEY_F9				(67)
#define KEY_F10				(68)

#define KEY_STAR			(69)  //*
#define KEY_POUND			(70)	 //#

#define KEY_POWER			(116)


/*********************************
		05 03 01 33
		 65 66 67
		 68 69 97
		 98 99 100
		 02 04 35
		 34 36 37
		   116
 *********************************/

struct mf_key_event {
	int keycode;
	int status;		/*1 down, 0 up*/
};

int mf_key_init(void);

int mf_get_key(struct mf_key_event *keyev);
int mf_key_flush();

int mf_key_setmap(unsigned short scancode, unsigned short keycode);

#ifdef __cplusplus
}
#endif

#endif /* __MF_KEY_H */

