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
Author:wuxp
Functions:Get the EMV kernel version
Input :  Nothing
Output : Nothing
return: emv version
*************************************************************************************/
LIB_EXPORT char * EMV_GetVersion(void);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:wuxp
Functions:Set the online PIN interface
Input :  Callback function
Output : Nothing
return: Nothing
*************************************************************************************/
LIB_EXPORT void EMV_SetInputPin(int (*InputPin)(char *,char *,char ,char *));

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:wuxp
Functions:Set offline PIN prompt interface
Input :  Callback function
Output : Nothing
return: Nothing
*************************************************************************************/
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

#endif
