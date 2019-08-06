/*! \file ime.h
	\brief 输入法
*	\author lx
*	\date 2014/02/07
*/

#ifndef __T9IME_H__
#define __T9IME_H__

#include "xgui_pub.h"
	
#define IME_MODE_T9PY			(1<<0)		//输入法可切换
#define IME_MODE_ALPHABET_UP	(1<<1)		//仅允许大写字母
#define IME_MODE_ALPHABET_LOW	(1<<2)		//仅允许小写字母	
#define IME_MODE_NUMBER			(1<<3)		//仅允许输入数字
#define IME_MODE_HANDWRITE		(1<<4)
#define IME_MODE_T9BH			(1<<5)		//仅允许拼音输入汉字

#define IME_HANDWRITE_AUP			(0)
#define IME_HANDWRITE_ALOW			(1)
#define IME_HANDWRITE_NUMBER		(2)
#define IME_HANDWRITE_SYMBOL		(3)
#define IME_HANDWRITE_CHS			(4)

#define IME_MODE_DEFAULT	(IME_MODE_T9PY | IME_MODE_ALPHABET_UP | IME_MODE_ALPHABET_LOW | IME_MODE_NUMBER)

#define IME_POS_DEFAULT			-1

#define IME_OPMODE_ONLYEMPTY	0
#define IME_OPMODE_ALWAYS		1

/**
* @brief 设置输入法方式
* @param nDefMode 默认的方式
* @param nAllowMode 允许的输入法切换模式
* @param bPassword 是否密码格式
* @param bSmsInput =1按照字符数 =0按字节数
* @return 
*/
LIB_EXPORT int xgui_ImeSetMode(int nDefMode, int nAllowMode, int bPassword, int bSmsInput);
/**
* @brief 读取输入法方式
* @param pDefMode 默认的方式
* @param pAllowMode 允许的输入法切换模式
* @param pbPassword 是否密码格式
* @return 
*/
LIB_EXPORT int xgui_ImeGetMode(int *pDefMode, int *pAllowMode, int *pbPassword);
/**
* @brief 设置输入提示内容
* @param szLeftOp 左按钮提示
* @param nMode 模式
* @return 
*/
LIB_EXPORT void xgui_ImeSetOpInfo(char * szLeftOp, int nMode);
/**
* @brief 输入法输入
* @param pcInputBuffer 输入缓冲区
* @param nMaxLength 缓冲区大小
* @param pPosition 开始位置
* @param pcHelpString 提示内容
* @return 
*/
LIB_EXPORT int xgui_ImeStartInput(char * pcInputBuffer, int nMaxLength, int * pPosition, char * pcHelpString);





#endif

