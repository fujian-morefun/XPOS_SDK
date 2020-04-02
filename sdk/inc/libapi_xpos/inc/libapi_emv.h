#ifndef _LIBAPI_EMV__H__
#define _LIBAPI_EMV__H__

#include "def.h"
#include "emvapi/inc/emv_api.h"
#include "libapi_pub.h"

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
Author:zhiyu
Functions:emv kernel data init
return: 
     	
*************************************************************************************/
LIB_EXPORT void EMV_iKernelInit(void);
/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:zhiyu
Functions:Init terminal configure of EMV
Input : ptermconfig £ºTerminal configure of emv
			
Output : Nothing
return: 	UEMV_PRM_ERR =-8, //Wrong parameter
			UEMV_PRM_FAIL=-1, //FAIL
			UEMV_PRM_OK=0 //SUCC
*************************************************************************************/
LIB_EXPORT int EMV_TermConfigInit(const TERMCONFIG *ptermconfig);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:zhiyu
Functions:Get emv kernel version
Input : Size £ºLength of version buffer
		
Output : KernelVersion: Kernel Version
return: Nothing
*************************************************************************************/
LIB_EXPORT void EMV_GetKernelVersion(char *KernelVersion, int size);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:zhiyu
Functions:Get TLV from EMV buffer
Input : Tag: TAG
		
Output : 	Len£ºLength
			Value: Value buffer
return: 	UEMV_PRM_NOT_FOUND=-3, //Not found
			UEMV_PRM_FAIL=-1, //FAIL
			UEMV_PRM_OK=0 //SUCC
*************************************************************************************/
LIB_EXPORT int EMV_GetKernelData (char *Tag, int *Len, byte *Value);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:zhiyu
Functions:Set AID buffer into device
Input : pTerminalApps: Aid buffer
		
Output : Nothing
return: 	UEMV_PRM_ERR =-8, //Wrong parameter
			UEMV_PRM_FAIL=-1, //FAIL
			UEMV_PRM_OK=0 //SUCC
*************************************************************************************/
LIB_EXPORT int EMV_PrmSetAIDPrm(TERMINALAPPLIST *pTerminalApps);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:zhiyu
Functions:Get all aid into memory
Input : Nothing
		
Output : pTerminalApps: The AID buffer
return: 	UEMV_PRM_NOT_FOUND=-3, 
			UEMV_PRM_FAIL=-1, 
			UEMV_PRM_OK=0 
*************************************************************************************/
LIB_EXPORT int EMV_PrmGetAIDPrm(TERMINALAPPLIST *pTerminalApps);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:zhiyu
Functions:Delete the specific AID
Input : AID:	AID 
				AID_Len
		
Output : Nothing
return: 	UEMV_PRM_NOT_FOUND=-3,
			UEMV_PRM_FAIL=-1, 
			UEMV_PRM_OK=0 
*************************************************************************************/
LIB_EXPORT int EMV_PrmDelAIDPrm(byte *AID, byte AID_Len);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:zhiyu
Functions:Clear all AID from device.
Input : Nothing
		
Output : Nothing
return: 	UEMV_PRM_FAIL=-1, 
			UEMV_PRM_OK=0 
*************************************************************************************/
LIB_EXPORT int EMV_PrmClearAIDPrmFile(void);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:zhiyu
Functions:Save CAPK into device
Input : ppkKey: The CAPK buffer
		
Output : Nothing
return: UEMV_PRM_ERR =-8, 
			UEMV_PRM_CAPK_CHK_HASH_FAIL=-2, 
			UEMV_PRM_FAIL=-1, 
			UEMV_PRM_OK=0 
*************************************************************************************/
LIB_EXPORT int EMV_PrmSetCAPK(CAPUBLICKEY *ppkKey);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:zhiyu
Functions:Get the specific index of CAPK
Input : 	RID: RID of CAPK
			PKIndex: Index of CAPK
Output : ppkKey: CAPK buffer
return: UEMV_PRM_NOT_FOUND=-3, 
			UEMV_PRM_FAIL=-1, 
			UEMV_PRM_OK=0 
*************************************************************************************/
LIB_EXPORT int EMV_PrmGetCAPK(CAPUBLICKEY *ppkKey, byte *RID, byte PKIndex);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:zhiyu
Functions:Delete the specific index of CAPK
Input : RID: RID of CAPK
			PKIndex: Index of CAPK
		
Output : Nothing
return: UEMV_PRM_NOT_FOUND=-3, 
			UEMV_PRM_FAIL=-1, 
			UEMV_PRM_OK=0 
*************************************************************************************/
LIB_EXPORT int EMV_PrmDelCAPK(byte *RID, byte PKIndex);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:zhiyu
Functions:Clear all CAPK from device
Input : Nothing
		
Output : Nothing
return: UEMV_PRM_FAIL=-1,
		UEMV_PRM_OK=0 
*************************************************************************************/
LIB_EXPORT int EMV_PrmClearCAPKFile(void);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lxz
Functions:Getting the specified tag value from the resource data
Input :  psTag:Afferent tag 
		 psSrc:Resource data
		 nSrcLen:Resource data length
		
Output : psBuf:Returns the tag value
		nBufLen:Returns the length of the tag value

return: UEMV_PRM_FAIL=-1,
		UEMV_PRM_OK=0 
*************************************************************************************/
LIB_EXPORT int EMV_GetDataByTag(byte *psTag, byte *psSrc, int nSrcLen,byte *psBuf, int *nBufLen);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:ruansj
Functions:Process of pack emv tag
Input : pTagName:		tag name
		TagValue:		tag value 
		iTagValueLen :  tag value length		
Output:
		psBuf :		Returns TLV packed data
		nBufLen:	Returns length of packed data
return: 
     	0	 //SUCC
		-1	 //FAIL
*************************************************************************************/
LIB_EXPORT int EMV_PackTLVData(byte *pTagName,byte *TagValue, int iTagValueLen, byte *psBuf,int *nBufLen);

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
Author:ruansj
Functions: Set ReadingCard Tip CallBack Function
Input :  Callback function   
Output : int param value  1--Indicate contact transactions  2--Indicate contactless transactions
return: Nothing
*************************************************************************************/
LIB_EXPORT void EMV_SetReadingCardDisp(void (*ReadingCardDisp)(int));

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:wuxp
Functions:Set the Offline PIN interface
Input :  Callback function
Output : Nothing
return: Nothing
*//*
Callback(InputPin):(char *psCardNo,char *psAmt,char cMsgType,char *psPin)//Enter password interface function pointer
Input:	char *psCardNo   (PAN)
		char *psAmt      (Amount)
		char cMsgType    1--PIN_LAST   2--PIN_AGAIN   3--PIN_NOMAL
Output:	char *psPin      (Entered password)
return: int	 0--OK   >0--Length of password entered  -ERR_PIN_EMPTY--bypass -ERR_TIMEOUT--timeout -ERR_USR_CANCEL--CANCEL -ERR_KEY_INVALID--INVALID  
*/
/*************************************************************************************/
LIB_EXPORT void EMV_SetInputPin(int (*InputPin)(char *,char *,char ,char *));

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:wuxp
Functions:Set offline PIN prompt interface
Input :  Callback function
Output : Nothing
return: Nothing
*//*
Callback(DispOffPin):
Input:int param value 0--PIN OK  N--Number of re-verifications
Output:Nothing
return:Nothing
*/
/*************************************************************************************/
LIB_EXPORT void EMV_SetDispOffPin(void (*DispOffPin)(int)); 

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:wuxp
Functions:Show AID
Input :  Nothing
Output : Nothing
return: Nothing
*************************************************************************************/
LIB_EXPORT void EMV_ShowAID_Prm(void);
/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:wuxp
Functions:Show CAPK
Input :  Nothing
Output : Nothing
return: Nothing
*************************************************************************************/
LIB_EXPORT void EMV_ShowCAPK_Prm(void);

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

#endif
