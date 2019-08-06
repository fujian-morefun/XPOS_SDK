#pragma once

#include "mpos_pub.h"

typedef struct __st_qr_data{
	char amt[20];	//title
	char data[128]; //qr data
	//int x;		//byte
	//int y;		//Row 1-8
	//int size;		//0(small),1(normal),2(big)
}st_qr_data;


#define	MPOS_RESULT_SUCC			"00"	//Successful processing
#define	MPOS_RESULT_NOT_SUPPORTED	"01"	//Instruction number is not supported
#define	MPOS_RESULT_PARAM_ERR		"02"	//Parameter error
#define MPOS_RESULT_LRC_ERR			"03"  	//LRC Verification failed
#define MPOS_RESULT_TIMEOUT			"04"	//Time out
#define MPOS_RESULT_OTHER_ERR		"05"	//Other errors


st_qr_data  * mpos_func_get_qr_data();
int mpos_func_proc(unsigned char * data , int len);