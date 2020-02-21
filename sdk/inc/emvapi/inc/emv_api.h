#pragma once
#include "pub/pub.h"
//reference to emv_interface.h
#define MODE_API_UNKNOW			0x00
#define	MODE_API_PBOC			0x01
#define MODE_API_VCPS			0x02
#define MODE_API_QPBOC			MODE_API_VCPS
#define MODE_API_MSD			0x04
#define MODE_API_PBOC_EC		0x10		
#define	MODE_API_RF				0x20	
#define	MODE_API_DPAS			0x30		
#define	MODE_API_AMEX			0x40		
#define MODE_API_M_CHIP			0x21	//MasterCard CHIP mode
#define MODE_API_M_STRIPE		0x22	//MasterCard MagStripe mode
#define MODE_API_R_LEGACY		0x23	//RUPAY LEGACY mode
#define MODE_API_R_NON_LEGACY	0x24	//RUPAY NON LEGACY mode

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
	char other_amt[32];
	int card_mode;
	int card_timeover;
	int pin_input;
	int pin_max_len;
	int pin_timeover;
	int key_pid;
	int pin_dukpt_gid;
	int des_mode;
	int data_dukpt_gid;
	int pin_mksk_gid;
	int forceIC;
	int show_PAN;
	int bByPassPin;		//0x00  NotSupport ByPassPin	0x01 Support ByPassPin
	char ic_tags[256];
	char card_page_msg[50];	
}st_read_card_in;

#define TRACK_MAX_LENTH		144
typedef struct __st_read_card_out{
	int card_type;  //0x01 READ_CARD_RET_MAGNETIC 0x02 READ_CARD_RET_IC 0x03 READ_CARD_RET_RF,  
	char exp_data[8];
	char ic_data[1024];
	int ic_data_len;
	char pan[32];
	char pan_sn[8];
	char pin_block[32];
	char pin_ksn[10];
	char data_ksn[10];
	int  pin_len;
	char track2[TRACK_MAX_LENTH];
	int track2_len;
	char track3[TRACK_MAX_LENTH];
	int track3_len;
	char vChName[45 +1];
	int nEmvMode;
	char signature_flag;//0x01 Need signature;0x00 No signature
}st_read_card_out;


#define EMVAPI_VER				"EMVAPI20200218XP"
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


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:ruansj
Functions:Process of emv online resp proc
Input : nOnlineRes : 0--online success  -1--online fail  -2--Not online
		sResp39: Online Response Code
		sField55: contain 91/8A/71/72 Tag Data
		nFieldLen : sField55 Length
return: 
     	EMVAPI_RET_TC	 0	 //TC
		EMVAPI_RET_AAC	 -1	 //AAC
		EMVAPI_RET_AAR	 -2	 //Terminate
*************************************************************************************/
LIB_EXPORT int emv_online_resp_proc(int nOnlineRes,char *sResp39,char *sField55,int nFieldLen);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:wuxp
Functions:Free EMV global buffer
Input : Nothing
return: Nothing
*************************************************************************************/
LIB_EXPORT void EMV_online_cardemv_free(void);

LIB_EXPORT int emv_card_begin(st_read_card_in *card_in);
LIB_EXPORT int emv_card_loop( int card_mode );
LIB_EXPORT int emv_card_end( int ret, st_read_card_in *card_in,st_read_card_out *card_out);
LIB_EXPORT void Emvapi_Version(char *pszVersion);
LIB_EXPORT void EMV_iKernelInit(void);


LIB_EXPORT void EMV_SetInputPin(int (*InputPin)(char *,char *,char ,char *));
LIB_EXPORT void EMV_SetDispOffPin(void (*DispOffPin)(int));
LIB_EXPORT void EMV_SetReadingCardDisp(void (*ReadingCardDisp)(int));

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:wuxp
Functions:Get the EMV kernel version
Input :  Nothing
Output : Nothing
return: emv version
*************************************************************************************/
LIB_EXPORT char * EMV_GetVersion(void);

