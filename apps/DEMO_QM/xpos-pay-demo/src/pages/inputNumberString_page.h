#pragma once

#include "input_public.h"

/*
*	只输入数字的界面。也可以用来输入数字密码。无输入法。页面一共分为四行，其中标题为第一行，第二行和第四行皆是提示语，第三行用来显示输入的数字
*/
 
typedef struct _inputNum_st
{
	char* title;	//标题，即第一行
	char* header;	//第一行提示语
	int timeout;	//超时时间,ms为单位
	int maxLength;	//允许输入的最大长度
	int minLength;	//允许输入的最小长度
	int len_null;	//是否允许0长度
	char* outBuff;	//[OUT] 输入内容缓冲区。由外部分配
	char argot;		//是否需要将按键值传给暗码处理函数
	char pwType;	//是否是密码类型，1是，0否。如果是密码类型，则输入内容显示*
	char showFooter;//是否显示第四行的提示内容
	char inputEN;	//是否支持输入英文字母
}INPUTNUM_ST;

int inputNumberString_page(INPUTNUM_ST* inputNumSt);

int input_pin_page(const char *title, char *outpin);