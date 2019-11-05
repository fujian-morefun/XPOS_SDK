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
	int forceIC;
	int show_PAN;
	char ic_tags[256];
	char card_page_msg[50];
}st_read_card_in;


typedef struct __st_read_card_out{
	int card_type;  //0x01 READ_CARD_RET_MAGNETIC 0x02 READ_CARD_RET_IC 0x03 READ_CARD_RET_RF,  
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

//Transaction Result Code
#define EMVAPI_RET_TC	 0	 //TC Approval
#define EMVAPI_RET_ARQC	 1	 //Request Online
#define EMVAPI_RET_AAC	 -1	 //Transaction rejection
#define EMVAPI_RET_AAR	 -2	 //Termination of transaction
#define EMVAPI_RET_CANCEL	-3	//User Cancel
#define EMVAPI_RET_TIMEOUT	-4	//Transaction timeout
#define EMVAPI_RET_FORCEIC	-5	//Transaction force IC
#define EMVAPI_RET_OTHER	-6	//Contactless turn to other interface
#define EMVAPI_RET_FALLBACk	-7	//Fallback

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:zhiyu
Functions:Process of emv card trans
Input : card_in£ºThe parameter of EMV trans
Output : card_out£ºOut buffer of EMV trans
return: 
     	EMVAPI_RET_TC	 0	 //TC
		EMVAPI_RET_ARQC	 1	 //ARQC
		EMVAPI_RET_AAC	 -1	 //AAC
		EMVAPI_RET_AAR	 -2	 //Terminate
		EMVAPI_RET_CANCEL	-3	//Cancel
*************************************************************************************/
LIB_EXPORT int emv_read_card(st_read_card_in *card_in, st_read_card_out *card_out);


LIB_EXPORT int emv_card_begin(st_read_card_in *card_in);
LIB_EXPORT int emv_card_loop( int card_mode );
LIB_EXPORT int emv_card_end( int ret, st_read_card_in *card_in,st_read_card_out *card_out);

LIB_EXPORT void EMV_iKernelInit(void);

LIB_EXPORT void EMV_SetInputPin(int (*InputPin)(char *,char *,char ,char *));

LIB_EXPORT void EMV_SetDispOffPin(void (*DispOffPin)(int)); 

