#pragma once
#include "pub\pub.h"

#define XGUI_INPUT_RET_OK			0
#define XGUI_INPUT_RET_QUIT			-1
#define XGUI_INPUT_RET_TIMEOVER		-2

enum{
	XGUI_INPUT_MODE_NUM,
	XGUI_INPUT_MODE_ALPHABET,
	XGUI_INPUT_MODE_IP,
	XGUI_INPUT_MODE_PWD,
};

LIB_EXPORT int xgui_input(char *title,  char *buff,int min, int max, int mode, int timeover);
