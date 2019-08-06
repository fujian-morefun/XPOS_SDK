#pragma once

//Press ok to return (some interfaces directly return input values)
#define INPUT_INPUT_RET_OK			0
//Press cancel to return
#define INPUT_INPUT_RET_QUIT		-1
//Timeout exit return
#define INPUT_INPUT_RET_TIMEOVER	-2


void input_PaintTitle(char* title);
void input_PaintHeader(char* header);
void input_PaintInput(char* inputContent);
void input_PaintFooter(char* footer);