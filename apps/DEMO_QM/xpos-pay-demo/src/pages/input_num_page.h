#pragma once


#define INPUT_NUM_RET_OK		0
#define INPUT_NUM_RET_QUIT		-1
#define INPUT_NUM_RET_TIMEOVER	-2

int input_num_page(char *buff , char *title , int min  , int max , int timeover , char pw, char argot);
int m_InputPin(char *psCardNo,char *psAmt,char cMsgType,char *psPin);
