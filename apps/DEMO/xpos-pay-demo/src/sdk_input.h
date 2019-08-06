#pragma once
#include "pub\pub.h"

#define SDK_INPUT_RET_OK			0
#define SDK_INPUT_RET_QUIT			-1
#define SDK_INPUT_RET_TIMEOVER		-2

enum{
	SDK_INPUT_MODE_NUM,
	SDK_INPUT_MODE_ALPHABET,
	SDK_INPUT_MODE_IP,
	SDK_INPUT_MODE_PWD,
};

 int sdk_input(char *title,  char *buff,int min, int max, int mode, int timeover);
 int sdk_input_test();
