#pragma once

//按确认键返回(有些界面直接返回输入的值)
#define INPUT_INPUT_RET_OK			0
//按取消键返回
#define INPUT_INPUT_RET_QUIT		-1
//超时退出返回
#define INPUT_INPUT_RET_TIMEOVER	-2


void input_PaintTitle(char* title);
void input_PaintHeader(char* header);
void input_PaintInput(char* inputContent);
void input_PaintFooter(char* footer);