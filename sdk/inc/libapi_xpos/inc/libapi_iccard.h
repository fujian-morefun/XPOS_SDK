#ifndef __LIBAPI_ICCARD_HEADER__
#define __LIBAPI_ICCARD_HEADER__

#include "libapi_pub.h"

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.7.3	Get File module version (Icc_GetModuleVer)
Input : Nothing
Output : pszVer   Get File module version 
return:  > 0 Successfully returns module version number length
		UICC_FAIL   =-1,           Fail
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int Icc_GetModuleVer(char *pszVer);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.7.4	Detection card��Icc_GetCardStatus��
Input : ISlotType: see enum SlotType
Output : Nothing
return: UICC_EMPTY         = -3,   // no card
		UICC_FAIL        = -1,   // Fail
		UICC_OK            =  0    // Success
Remarks: Contact card: Check if the card is in the card slot
		Please call the IC card device (Icc_Open) first.
*************************************************************************************/
LIB_EXPORT int Icc_GetCardStatus(int iSlotType);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.7.5	Icc_PowerUp��Icc_PowerUp��
Input : iCardType��IC card type, see enum IccType
		ISlotType: see enum SlotType
Output : Nothing
return: UICC_EMPTY         = -3,   // no card
		UICC_FAIL        = -1,   // Fail
		UICC_OK            =  0    // Success
Remarks: Including card reset operation
*************************************************************************************/
LIB_EXPORT int Icc_PowerUp(int iCardType, int iSlotType);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.7.6	Contact card Power down��Icc_PowerDown��
Input : iCardType��IC card type, see enum IccType
		ISlotType: see enum SlotType
Output : Nothing
return: UICC_FAIL        = -1,   // Fail
		UICC_OK          =  0		      Success
Remarks: Pay attention to calling off IC card device (Icc_Close) after power off.
*************************************************************************************/
LIB_EXPORT int Icc_PowerDown(int iCardType , int iSlotType);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.7.7	Contact card communication��Icc_ICComm��
Input : iCardType��IC card type, see enum IccType
		ISlotType: see enum SlotType
		Apdu��See ICCAPDU structure
Output : Apdu��See ICCAPDU structure
		The data returned depends on the type of OperType operation in the ICCAPDU structure and is placed in R_Data.
return: UICC_COMMAND_FAIL    = -2,   // Communication error
		UICC_FAIL        = -1,   // Fail
		UICC_OK            =  0    // Success
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int Icc_ICComm (int iCardType,int iSlotType, ICCAPDU *Apdu);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.7.8	RF Seek��Icc_CTLSPowerUpAndSeek��
Input : ICardType: non card type, see enum IccType
		iSlotType��Card slot number, see enum SlotType
		Output : psUID��Card serial number. The first byte is the serial number length.
return: UICC_NORF         = -4,   // No Card
		UICC_FAIL        = -1,   // Fail
		UICC_OK            =  0    // Success
Remarks: Please call the IC card device (Icc_Open) first.
		Includes card reset operation application layer loop call
*************************************************************************************/
LIB_EXPORT int Icc_CTLSPowerUpAndSeek (int iCardType, char *psUID);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.7.9	RF CARD Power down��Icc_CTLSPowerDown��
Input : iSlotType��Card slot number, see enum SlotType
Output : Nothing
return: UICC_FAIL        = -1,   // Fail
		UICC_OK          =  0		      Success
Remarks: Pay attention to calling off IC card device (Icc_Close) after power off.
*************************************************************************************/
LIB_EXPORT int Icc_CTLSPowerDown ();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.7.10	Non connected card communication��Icc_CTLSComm��
Input : ICardType: non card type, see enum IccType
		iSlotType��Card slot number, see enum SlotType
		Apdu: see the ICCAPDU structure specification
Output : Apdu: see the ICCAPDU structure specification
		The data returned depends on the type of OperType operation in the ICCAPDU structure and is placed in R_Data.
return: UICC_COMMAND_FAIL    = -2,   // Communication error
		UICC_FAIL        = -1,   // Fail
		UICC_OK            =  0    // Success
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int Icc_CTLSComm(int iCardType,ICCAPDU *Apdu);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: Open IC card ��Icc_Open��
Input : iSlotType��Card slot number, see enum SlotType
Output : Nothing
return: UICC_FAIL        = -1,   // Fail
		UICC_OK            =  0    // Success
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int Icc_Open(int iSlotType);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: Close IC card��Icc_Close��
Input : iSlotType��Card slot number, see enum SlotType
Output : Nothing
return: UICC_FAIL        = -1,   // Fail
		UICC_OK            =  0    // Success
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int Icc_Close(int iSlotType);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.7.13 Get IC card reset information ATR��Answer To Reset��
Input : iCardType��IC card type, see enum IccType
		iSlotType��Card slot number, see enum SlotType
		  pnATRLen��psATR Cache size
Output : Nothing
return: UICC_FAIL        = -1,   // Fail
		UICC_OK            =  0    // Success
Remarks: Used to obtain IC card reset information ATR (Answer To Reset), which is called 
			after resetting Icc_PowerUp, Icc_CTLSPowerUp and AndSeek on the card by power.
*************************************************************************************/
LIB_EXPORT int Icc_GetCardATR(int iCardType, int iSlotType, byte *psATR, int*pnATRLen);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:ruansj
Functions: Check if the terminal is inserted into the IC card
Input :	 Nothing
Output : Nothing
return: UICC_FAIL			= -1,   // Fail
		UICC_OK            =  0    // Success
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int Icc_CardInsertDetect();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:ruansj
Functions: Check whether the user swipes the card at the terminal
Input :	 Nothing
Output : Nothing
return: UICC_FAIL			= -1,   // Fail
		UICC_OK            =  0    // Success
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int Icc_CardRfDetect();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:George
Functions: Clear magtek buffer
Input :	 Nothing
Output : nothing
return: nothing
Remarks: must call card_magtek_flush before card_MagStripeDetect
*************************************************************************************/
LIB_EXPORT void card_magtek_flush(void);
/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:ruansj
Functions: Check if the terminal is swiping
Input :	 Nothing
Output : trackinfo ,If successful, the magnetic stripe card data is returned.
return: UICC_FAIL			= -1,   // Fail
		UICC_OK            =  0    // Success
Remarks: must call card_magtek_flush before card_MagStripeDetect
*************************************************************************************/
LIB_EXPORT int card_MagStripeDetect(card_magtek_track_info *trackinfo);

LIB_EXPORT int mf_rfid_mfcl_open(void);
LIB_EXPORT int mf_rfid_mfcl_close(void);
LIB_EXPORT int mf_rfid_mfcl_getuid(unsigned char *uid);
LIB_EXPORT int mf_rfid_mfcl_atqa(void);
LIB_EXPORT int mf_rfid_mfcl_setkey( unsigned char *key);
LIB_EXPORT int mf_rfid_mfcl_auth(int cmd, int block);
LIB_EXPORT int mf_rfid_mfcl_read(int block, unsigned char *buf, int *len);
LIB_EXPORT int mf_rfid_mfcl_write(int block, unsigned char *buf, int len);
LIB_EXPORT int mf_rfid_mfcl_increment(int block, int operand);
LIB_EXPORT int mf_rfid_mfcl_transfer(int block);
LIB_EXPORT int mf_rfid_mfcl_restore(int block);
LIB_EXPORT int mf_rfid_mfcl_decrement(int block, int operand);


#endif /*__LIBAPI_ICCARD_HEADER__*/
