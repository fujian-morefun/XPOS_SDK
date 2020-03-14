/*! \file xgui_key.h
	\brief 按键功能
*	\author lx
*	\date 2014/02/08
*/
#pragma once

#include "xgui_pub.h"

#define KEY_0		'0'
#define KEY_1		'1'
#define KEY_2		'2'
#define KEY_3		'3'
#define KEY_4		'4'
#define KEY_5		'5'
#define KEY_6		'6'
#define KEY_7		'7'
#define KEY_8		'8'
#define KEY_9		'9'
#define KEY_XING	'*'
#define KEY_JING		'#'


#define KEY_A		'A'
#define KEY_B		'B'
#define KEY_C		'C'
#define KEY_D		'D'
#define KEY_E		'E'
#define KEY_F		'F'
#define KEY_G		'G'
#define KEY_H		'H'
#define KEY_I		'I'
#define KEY_J		'J'
#define KEY_K		'K'

#define KEY_PLUS			'+'
#define KEY_SUBTRACT		'-'
#define KEY_MULTIPLY		'*'
#define KEY_DIVISION		'/'


#define KEY_CONTROL		0x80

#define KEY_UP			(KEY_CONTROL + 0x1)
#define KEY_DOWN		(KEY_CONTROL + 0x2)
#define KEY_LEFT		(KEY_CONTROL + 0x3)
#define KEY_RIGHT		(KEY_CONTROL + 0x4)
#define KEY_BACKSPACE	(KEY_CONTROL + 0x5)
#define KEY_DELETE		(KEY_CONTROL + 0x6)
#define KEY_TAB			(KEY_CONTROL + 0x7)
#define KEY_ENTER		(KEY_CONTROL + 0x8)
#define KEY_HOME		(KEY_CONTROL + 0x9)

#define KEY_END			(KEY_CONTROL + 0xA)
#define KEY_SHIFT		(KEY_CONTROL + 0xB)
#define KEY_ESCAPE		(KEY_CONTROL + 0xC)
#define KEY_INSERT		(KEY_CONTROL + 0xD)
#define KEY_CANCEL 		(KEY_CONTROL + 0xE)

#define KEY_FUNC		(KEY_CONTROL + 0x10)
#define KEY_OK			(KEY_CONTROL + 0x11)
#define KEY_QUIT		(KEY_CONTROL + 0x12)
#define KEY_F1			(KEY_CONTROL + 0x13)
#define KEY_F2			(KEY_CONTROL + 0x14)
#define KEY_POWER		(KEY_CONTROL + 0x15)

#define KEY_IM_UP		(KEY_CONTROL + 0x16)
#define KEY_IM_DOWN		(KEY_CONTROL + 0x17)



/**
* @brief 添加按键处理函数
* @param pfunc
* @return 
*/
LIB_EXPORT int xgui_key_proc_func_add(void * pfunc);

LIB_EXPORT void xgui_key_reset_key();

LIB_EXPORT void xgui_key_init();


LIB_EXPORT void xgui_key_set_proc(int val);


LIB_EXPORT int xgui_key_getlast();
LIB_EXPORT int xgui_key_clrlast();

LIB_EXPORT int xgui_key_pin_data(char * data);
LIB_EXPORT void xgui_key_pin_mode(int mode, int size);


