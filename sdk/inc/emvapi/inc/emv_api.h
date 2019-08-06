#pragma once
#include "pub/pub.h"

enum{
	READ_CARD_RET_CANCEL,
	READ_CARD_RET_MAGNETIC,
	READ_CARD_RET_IC,
	READ_CARD_RET_RF,
	READ_CARD_RET_TIMEOVER,
	READ_CARD_RET_FAIL
};

enum{
	READ_CARD_MODE_MAG = 0x01,
	READ_CARD_MODE_IC = 0x02,
	READ_CARD_MODE_RF = 0x04
};

typedef struct __st_read_card_in{
	char title[32];
	int trans_type;
	char amt[32];
	int card_mode;
	int card_timeover;
	int pin_input;
	int pin_max_len;
	int pin_timeover;
	int key_pid;
	int pin_key_index;
	char ic_tags[256];
	char card_page_msg[50];
}st_read_card_in;


typedef struct __st_read_card_out{
	int card_type;
	char exp_data[8];
	char ic_data[1024];
	int ic_data_len;
	char pan[32];
	char pan_sn[8];
	char pin_block[32];
	char ksn[10];
	int  pin_len;
	char track2[140];
	int track2_len;
	char track3[140];
	int track3_len;
	char vChName[45 +1];
}st_read_card_out;

//交易结果码
#define EMVAPI_RET_TC	 0	 //TC批准
#define EMVAPI_RET_ARQC	 1	 //请求联机
#define EMVAPI_RET_AAC	 -1	 //交易拒绝
#define EMVAPI_RET_AAR	 -2	 //交易终止
#define EMVAPI_RET_CANCEL	-3	//用户取消
#define EMVAPI_RET_TIMEOUT	-4	//交易超时


/*************************************************************************************
版    权：福建魔方电子科技有限公司
作	  者：zhiyu
功    能：完整的读卡处理流程
输入参数：card_in：读卡需要输入的参数	
输出参数：card_out：读卡完成后输出的参数
返    回：
     	EMVAPI_RET_TC	 0	 //TC批准
		EMVAPI_RET_ARQC	 1	 //请求联机
		EMVAPI_RET_AAC	 -1	 //交易拒绝
		EMVAPI_RET_AAR	 -2	 //交易终止
		EMVAPI_RET_CANCEL	-3	//用户取消
*************************************************************************************/
LIB_EXPORT int emv_read_card(st_read_card_in *card_in, st_read_card_out *card_out);

LIB_EXPORT void EMV_iKernelInit(void);

LIB_EXPORT void bInputPin(int (*InputPin)(char *,char *,char ,char *));