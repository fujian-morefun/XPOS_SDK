#pragma once

#include "pub\pub.h"

#ifdef __cplusplus
extern "C"{
#endif


typedef struct __st_qcamp_data{
	int type;
	int length;
	char outdata[512];
}st_qcamp_data;


LIB_EXPORT int atc_qcamp_open(int height, int width);
LIB_EXPORT int atc_qcamp_close();

LIB_EXPORT int atc_qcamp_start(st_qcamp_data * qcamp_data, int timeover1, void * pfun);
LIB_EXPORT int atc_qcamp_start1();
LIB_EXPORT int atc_qcamp_stop();


LIB_EXPORT int atc_qgpio(int index, int val);
LIB_EXPORT int atc_qgpio_ex(int val);

LIB_EXPORT int atc_qr_decode(char * str, int size);
LIB_EXPORT int atc_qr_encode(char * indata, int size, char *outdata);
LIB_EXPORT void atc_qr_code_test();

/* 扫描流程
	
	atc_qcamp_open_ex	打开扫描，缩短开始扫描时间，可以不打开直接开始扫描

	扫描页面
	{
		atc_qcamp_start_ex	开始扫描
		while		// 循环等待扫描消息
		{
			if (pMsg.MessageId == XM_SCAN_OK) 	
		}
		atc_qcamp_stop_ex
	}

	atc_qcamp_close_ex  关闭扫描，和打开扫描配对，没有打开不需要关闭

*/



LIB_EXPORT int atc_qcamp_open_ex(int width, int height);		//width=0 height =0

LIB_EXPORT int atc_qcamp_close_ex();

//开始扫描
LIB_EXPORT int atc_qcamp_start_ex();
//停止扫描
LIB_EXPORT int atc_qcamp_stop_ex();

#ifdef __cplusplus
}
#endif	