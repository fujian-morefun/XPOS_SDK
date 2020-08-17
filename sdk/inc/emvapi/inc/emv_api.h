#pragma once
#include "pub/pub.h"
#include "driver/mf_magtek.h"
//reference to emv_interface.h


#define MODE_API_UNKNOW			0x00
#define	MODE_API_PBOC			0x01
#define MODE_API_VCPS			0x02
#define MODE_API_QPBOC			MODE_API_VCPS
#define MODE_API_MSD			0x04
//#define MODE_API_PBOC_EC		0x10		
//#define	MODE_API_RF				0x20	
//#define	MODE_API_DPAS			0x30		
#define	MODE_API_AMEX			0x40		
#define MODE_API_M_CHIP			0x21	//MasterCard CHIP mode
#define MODE_API_M_STRIPE		0x22	//MasterCard MagStripe mode
#define MODE_API_R_LEGACY		0x23	//RUPAY LEGACY mode
#define MODE_API_R_NON_LEGACY	0x24	//RUPAY NON LEGACY mode
#define MODE_API_EMV_MODE		0x25	//EMV_MODE 	(for AMEX,DPAS)
#define MODE_API_MS_MODE		0x26	//MS_MODE	(for AMEX,DPAS)
#define MODE_API_ZIP_MODE		0x27	//ZIP_MODE	(for DPAS)


//card_type value of card_out
enum{
	READ_CARD_RET_CANCEL,  
	READ_CARD_RET_MAGNETIC,
	READ_CARD_RET_IC,
	READ_CARD_RET_RF,
	READ_CARD_RET_TIMEOVER,
	READ_CARD_RET_FAIL
};

//card_mode of card_in
enum{
	READ_CARD_MODE_MAG = 0x01,
	READ_CARD_MODE_IC = 0x02,
	READ_CARD_MODE_RF = 0x04
};

typedef struct __st_read_card_in{
	char title[32];//title of card reading pages
	int trans_type;//Transaction Type refer DE3.1(ISO 8583). example 0x00 as SALE;
	char amt[32];//Amount 9F02
	char other_amt[32];//Cash back Amount 9F03
	int card_mode;//READ_CARD_MODE_MAG , READ_CARD_MODE_IC , READ_CARD_MODE_RF
	int card_timeover;//Time over of  card reading page,normally 60000;
	int pin_input;  //For DIP and TAP cards. 0x01: enter the PIN interface according to the emv_read_card internal; 0x02:forces the PIN interface  of online transactions 
	int mag_mode;	//For magnetic stripe cards. 0x01: The application determines whether to enter the PIN interface according to the service_code; 0x00:require a PIN from emv_read_card internal
	int pin_min_len;//min length of pin 
	int pin_max_len;//max length of PIN,range 4-12
	int pin_timeover;//Time over of PIN inputting page,normally 60000;
	int key_pid;	//SEC_DUKPT_FIELD,SEC_MKSK_FIELD,SEC_FIXED_FIELD
	int pin_dukpt_gid;//group ID of DUKPT mode, used for PIN encryption; gid<0 means not support;
	int des_mode;		//DES_TYPE_ENCRYPT,DES_TYPE_DECRYPT
	int data_dukpt_gid;//group ID of DUKPT mode, used for track or account data encryption; gid<0 means not support;
	int pin_mksk_gid;	//group ID of MKSK mode, used for PIN encryption; gid<0 means not support;
	int forceIC;		//0x00:not forced chip read priority; 0x01:chip card takes priority over magnetic stripe
	int show_PAN;		//0x00:not show PAN during card reading; 0x01:show PAN during card reading;
	int bByPassPin;		//0x00  NotSupport ByPassPin	0x01 Support ByPassPin
	char ic_tags[256];	//ASCII code; TAGs need get value from card reading; example:9F0282...;NULL value, will get default TAG list
	char card_page_msg[50];	//Message of card reading page
	int ic_online_resp;		//0:not support; 1:chip card reading support online response processing
	int nTransSerial_9f41;	//Transcation Sequence Counter of chip card reading
	int pin_format;//refer to SEC_PIN_FORMAX in libapi_security.h
	char sDccCurrency[2];//DCC Currency
}st_read_card_in;

#define TRACK_MAX_LENTH		144
typedef struct __st_read_card_out{
	int card_type;		//0x01 READ_CARD_RET_MAGNETIC 0x02 READ_CARD_RET_IC 0x03 READ_CARD_RET_RF,  
	char exp_data[8];	//Expiration Date of card
	char ic_data[1024];	//HEX code, TLV data of card_in.ic_tags
	int ic_data_len;	//Length of ic_data
	char pan[32];		//PAN of card
	char pan_sn[8];		//5F34 PAN Sequence Number,DE23(ISO 8583)
	char pin_block[32];	//PINBLOCK
	char pin_ksn[10];	//KSN of PIN encryption KEY in DUKPT mode
	char data_ksn[10];	//KSN of track or account data encryption KEY in DUKPT mode
	int  pin_len;		//Length of online PIN plaintext, return 0 when bypass PIN
	char track2[TRACK_MAX_LENTH];//plaintext of track2 when data_dukpt_gid<0; encryption track2 when data_dukpt_gid>=0;
	int track2_len;		//length of track2
	char track3[TRACK_MAX_LENTH];//plaintext of track3 when data_dukpt_gid<0; encryption track3 when data_dukpt_gid>=0;
	int track3_len;		//length of track3
	char vChName[45 +1];//Card holder Name
	int nEmvMode;		//refer to MODE_API_XX
	char signature_flag;//0x01 Need signature;0x00 No signature
	char service_code[3+1];//service code of card
}st_read_card_out;


#define  UMAX_RUPAY_SERVICE_COUNT   20		//The maximum number of service supported by card terminals
#define  UMAX_RUPAY_PRMACQKEY_COUNT	20		//The maximum number of service prmacqkey supported by card terminals
//RUPAYSERVICE  structure
typedef struct
{
	char ucServiceId[2];		 //service id
	char auServiceQualifier[5];	 //service qualifier
	char auServiceData[96];      //service data
	int iServiceLen;			 //service data length
}RUPAYSERVICEDATA;


//RUPAYSERVICELIST structure
typedef struct
{
	char bServiceCount;	//number of rupay service
	RUPAYSERVICEDATA ServiceData[UMAX_RUPAY_SERVICE_COUNT];
}RUPAYSERVICELIST;

//RUPAYPRMACQKEY structure
typedef struct
{
	char ucServiceId[2];		//service id
	char ucPRMacqKeyIndex;		//service PRMacqKey Index
	char ucPRMacqKey[16];		//service PRMacqKey
	char ucPRMacqKeyLen;		//service PRMacqKey length
	char ucPRMacqKCV[3];		//service PRMacqKCV
}RUPAYPRMACQKEY;

//RUPAYPRMACQKEYLIST  structure
typedef struct
{
	char bPRMacqKeyCount;	//number of rupay PRMacqKey
	RUPAYPRMACQKEY PRMacqKey[UMAX_RUPAY_PRMACQKEY_COUNT];
}RUPAYPRMACQKEYLIST;

typedef struct _st_input_pin
{
	char szFirstLine[30];		// first line show message
	char szSecLine[30];			//seccond line show message
	char szThirdLine[30];		//third line show message
	char szFourthLine[30];		//if this param is not null, input pin will show 5th line
	char PinType;				//pinType 0:online PIN   1:offline pin 2:clear online msg (use default) 3:clear offline msg(use default)
}st_input_pin;

typedef struct _st_read_card_show
{
	char szFirstLine[30];		//first line show message
	char FirstShowType;			//show type 0:Left 1:center 2:right
	char szSecLine[30];			//seccond line show message
	char SecShowType;			//show type 0:Left 1:center 2:right
	char szThirdLine[30];		//third line show message
	char ThirdShowType;			//show type 0:Left 1:center 2:right
	char szFourLine[30];		//four line show message
	char FourShowType;			//show type 0:Left 1:center 2:right
}st_read_card_show;

//Transaction Result return value define
#define EMVAPI_RET_TC	 0	 //TC Approval
#define EMVAPI_RET_ARQC	 1	 //Request Online
#define EMVAPI_RET_AAC	 -1	 //Transaction rejection
#define EMVAPI_RET_AAR	 -2	 //Termination of transaction
#define EMVAPI_RET_CANCEL	-3	//User Cancel
#define EMVAPI_RET_TIMEOUT	-4	//Transaction timeout
#define EMVAPI_RET_FORCEIC	-5	//Transaction force IC
#define EMVAPI_RET_OTHER	-6	//Contactless turn to other interface
#define EMVAPI_RET_FALLBACk	-7	//Fallback
#define EMVAPI_RET_SEEPHONE -8	//visa "See Phone and Retry"
#define EMVAPI_RET_SUCC		0	 //process success

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
Input : nOnlineRes : 0--online success  -1--connect successfully, no response, online fail  -2--connect fail,not online
		sResp39: Online Response Code
		sField55: contain 91/8A/71/72 Tag Data
		nFieldLen : sField55 Length
return: 
		EMVAPI_RET_TC	 0	 //TC
		EMVAPI_RET_AAC	 -1	 //AAC
		EMVAPI_RET_AAR	 -2	 //Terminate
Attention:can call EMV_GetKernelData get tags,then must call EMV_online_cardemv_free() to free memory
*************************************************************************************/
LIB_EXPORT int emv_online_resp_proc(int nOnlineRes,char *sResp39,char *sField55,int nFieldLen);
LIB_EXPORT void EMV_online_cardemv_free(void);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:George
Functions:Process of emv online resp proc and pack tlv data
Input : nOnlineRes : 0--online success  -1--online fail  -2--Not online
		sResp39: Online Response Code
		sField55: ASCC code;contain 91/8A/71/72 Tag Data
		nFieldLen : sField55 Length
		emvtags: ASCC code;the tags want to get
Output: packvalue: HEX code,the tlv data match emvtags 
		packlen:length of packvalue
return: 
		EMVAPI_RET_TC	 0	 //TC
		EMVAPI_RET_AAC	 -1	 //AAC
		EMVAPI_RET_AAR	 -2	 //Terminate
Attention:Don't need to call EMV_online_cardemv_free() 
*************************************************************************************/
LIB_EXPORT int emv_onlineresp_proc_pack(int nOnlineRes,char *sResp39,char *sField55,char*emvtags, char*packvalue,int*packlen);


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

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:George
Functions:Process online pin entering and output encrypted PIN block
Input : bByPassPin : 0--not support bypass  1--support bypass
		key_pid: SEC_MKSK_FIELD,SEC_DUKPT_FIELD;refer to libapi_security.h
		pin_gid: index of key;match with key_pid
		amt : amount
		pan: pan of this transaction
Output: pin_len: length of pin
		pin_ksn: ksn of KF_DUKPT mode;
		pin_block: encrypted PIN
return: 
		EMVAPI_RET_SUCC
		EMVAPI_RET_TIMEOUT	 
		EMVAPI_RET_CANCEL	
*************************************************************************************/
LIB_EXPORT int emvapi_onlinpin_proc_page(int bByPassPin,int key_pid,int pin_gid,char*amt,char *pan, int*pin_len,char*pin_ksn, char*pin_block);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:ruansj
Functions:Set rupay service data into device
Input : pRuPayServiceList: rupay sevice data list buffer
		
Output : Nothing
return: 	
			FAIL=-1,	//FAIL
			SUCC=0		//SUCC
*************************************************************************************/
LIB_EXPORT int EMV_SetRuPayServiceList(RUPAYSERVICELIST *pRuPayServiceList);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:ruansj
Functions:Get all rupay service data into memory
Input : Nothing
		
Output : pRuPayServiceList: rupay sevice data list buffer
return: 	
			FAIL=-1,	//FAIL
			SUCC=0		//SUCC
*************************************************************************************/
LIB_EXPORT int EMV_GetRuPayServiceList(RUPAYSERVICELIST *pRuPayServiceList);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:ruansj
Functions:Set rupay PRMacqKey list into device
Input : pRuPayPRMacqKeyList: rupay PRMacqKeylist buffer
		
Output : Nothing
return: 	
			FAIL=-1,	//FAIL
			SUCC=0		//SUCC
*************************************************************************************/
LIB_EXPORT int EMV_SetRuPayPRMacqKeyList(RUPAYPRMACQKEYLIST *pRuPayPRMacqKeyList);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:ruansj
Functions:Get all rupay service PRMacqKey into memory
Input : Nothing
		
Output : pRuPayServicePRMacqKeyList: rupay sevice PRMacqKey list buffer
return: 	
			FAIL=-1,	//FAIL
			SUCC=0		//SUCC
*************************************************************************************/
LIB_EXPORT int EMV_GetRuPayPRMacqKeyList(RUPAYPRMACQKEYLIST *pRuPayPRMacqKeyList);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:ruansj
Functions:Show RuPay PRMacq Key
Input :  Nothing
Output : Nothing
return: Nothing
*************************************************************************************/
LIB_EXPORT void EMV_ShowRuPayPRMacqKey(void);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:ruansj
Functions:Show RuPay Service
Input :  Nothing
Output : Nothing
return: Nothing
*************************************************************************************/
LIB_EXPORT void EMV_ShowRuPayService(void);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:ruansj
Functions:Clear all rupay service from device
Input : Nothing
		
Output : Nothing
return: FAIL = -1,
		SUCC =  0 
*************************************************************************************/
LIB_EXPORT int EMV_ClearRuPayServiceFile(void);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:ruansj
Functions:Clear all rupay PRMacq Key from device
Input : Nothing
		
Output : Nothing
return: FAIL = -1,
		SUCC =  0 
*************************************************************************************/
LIB_EXPORT int EMV_ClearRuPayPRMacqKeyFile(void);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:ruansj
Functions:set other param (tlv format)
Input : pOtherParam : other param content
		iLength : 	other param conten length	
		
Output : Nothing
return: FAIL = -1,
		SUCC =  0 
*************************************************************************************/
LIB_EXPORT void EMVAPI_vSetOtherParamTlv(char *pOtherParam,int iLength);

LIB_EXPORT int emvapi_check_ic();

LIB_EXPORT int emvapi_check_magtek(struct magtek_track_info *trackinfo);
LIB_EXPORT int emvapi_check_rf();

LIB_EXPORT int EMV_SetPinInputMsg(st_input_pin st_msg);

LIB_EXPORT int EMV_SetReadCardShow(st_read_card_show st_msg);