#pragma once

#include "libapi_pub.h"


#define MKSK_MAINKEY_TYPE			0x00
#define MKSK_PINENC_TYPE			0x01
#define MKSK_MACENC_TYPE			0x02
#define MKSK_MAGDEC_TYPE			0x03
#define MKSK_TRANSKEY_TYPE			0x04

#define MKSK_ENCRYPT				0x00
#define MKSK_DECRYPT				0x01


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Save key plaintext
Input : 	type£º		Key type(0x00-0x04)
			gid	£º		Key grouping(0-9)
			key	:		Key plaintext
Output :	kvc			Key kvc(Key plaintext encryption 8 0x00)
return: 0,     success
		Other, failure	
*************************************************************************************/
LIB_EXPORT int mksk_save_plaintext_key(int type, int gid, unsigned char * key, unsigned char *kvc);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Save key ciphertext
Input : 	type£º		Key type(0x00-0x04)
			gid	£º		Key grouping(0-9)
			key	:		Key plaintext
Output :	kvc:		Key kvc(Key plaintext encryption 8 0x00)
return: 0,     success
		Other, failure	
*************************************************************************************/
LIB_EXPORT int mksk_save_encrypted_key(int type, int gid, unsigned char * key, unsigned char *kvc);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Use key 3des operation
Input : 	type£º		Key type(0x00-0x04)
			gid	£º		Key grouping(0-9)
			mode:		Operation type (encryption/decryption)
			ind:		Raw data
			size:		Data length (8-byte multiple)
Output :   outd:		Calculation results
return: 0,     success
		Other, failure	
*************************************************************************************/
LIB_EXPORT int mksk_3des_run(int type, int gid, int mode, unsigned char *ind, int size, unsigned char *outd);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Get a set of dukpt keys
Input : 	gid	£º		Key grouping(0)
Output :   ksn:		Key corresponds to ksn
return: 0,     success
		Other, failure	
*************************************************************************************/
LIB_EXPORT int dukpt_get_ksn(unsigned char gid, unsigned char * ksn);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Use the previously obtained key 3des operation
Input : 	mode:		Operation type (encryption/decryption)
			ind:		Raw data
			size:		Data length (8-byte multiple)
Output :   outd:		Calculation results
return: 0,     success
		Other, failure	
*************************************************************************************/
LIB_EXPORT int dukpt_3des_run(int mode, char *ind, int size, char *outd);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Initialize the dukpt key
Input : 	gid:		Key grouping£¬0
			init_ksn:	Initial ksn	
			init_key:	Initial key
Output :   Nothing
return: 0,     success
		Other, failure
*************************************************************************************/
LIB_EXPORT int dukpt_init_key(unsigned char gid, unsigned char* init_ksn, unsigned char* init_key);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions: get pci hardware version
Input : 	
Output£º	
return: hardware version
*************************************************************************************/
LIB_EXPORT char * sec_get_hw_ver();

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions: get pci firmware version
Input : 	
Output£º	
return: firmware version
*************************************************************************************/
LIB_EXPORT char * sec_get_fw_ver();