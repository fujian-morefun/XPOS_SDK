#pragma once

#include "libapi_pub.h"


#define MKSK_MAINKEY_TYPE			0x00
#define MKSK_PINENC_TYPE			0x01
#define MKSK_MACENC_TYPE			0x02
#define MKSK_MAGDEC_TYPE			0x03
#define MKSK_TRANSKEY_TYPE			0x04

#define MKSK_ENCRYPT				0x00
#define MKSK_DECRYPT				0x01



#define SEC_FIXED_FIELD				0x00
#define SEC_MKSK_FIELD				0x01
#define SEC_DUKPT_FIELD				0x02

#define SEC_MAC_UPAY_FORMAT			0x01
#define SEC_MAC_X99_FORMAT			0x02
#define SEC_MAC_X919_FORMAT			0x03
#define SEC_MAC_XOR_FORMAT			0x04


#define SEC_PIN_FORMAT0				0x00
#define SEC_PIN_FORMAT1				0x01
#define SEC_PIN_FORMAT2				0x02
#define SEC_PIN_FORMAT3				0x03
#define SEC_PIN_FORMAT4				0x04

#define DES_TYPE_ENCRYPT			0x00
#define DES_TYPE_DECRYPT			0x01

#define DES_MODE_ECB				0x00
#define DES_MODE_CBC				0x01

#define DUKPT_DES_KEY_PIN			0x00
#define DUKPT_DES_KEY_MAC1			0x01
#define DUKPT_DES_KEY_MAC2			0x02
#define DUKPT_DES_KEY_DATA1			0x03
#define DUKPT_DES_KEY_DATA2			0x04

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
Functions:Use key 3des operation
Input : 	type£º		Key type(0x00-0x04)
			gid	£º		Key grouping(0-9)
			mode:		Operation type (encryption/decryption)
			ind:		Raw data
			size:		Data length (8-byte multiple)
			des_mode:	Data padding(DES_MODE_ECB/DES_MODE_CBC)
Output :   outd:		Calculation results
return: 0,     success
		Other, failure	
*************************************************************************************/
LIB_EXPORT int mksk_3des_run_ex(int type, int gid, int mode, unsigned char *ind, int size, unsigned char *outd, int des_mode);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Get a set of dukpt keys
Input : 	gid	£º		Key grouping(0)
Output :   ksn:		Key corresponds to ksn
return: 0,     success
		Other, failure	
*************************************************************************************/
LIB_EXPORT int dukpt_prepare_key(unsigned char gid, unsigned char * ksn);

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
Functions:Use the previously obtained key 3des operation
Input : 	mode:		Operation type (encryption/decryption)
			ind:		Raw data
			size:		Data length (8-byte multiple)
			des_mode:	Data padding(DES_MODE_ECB/DES_MODE_CBC)
			key_tpye:	DUKPT_DES_KEY_PIN/DUKPT_DES_KEY_MAC1/DUKPT_DES_KEY_MAC2/DUKPT_DES_KEY_DATA1/DUKPT_DES_KEY_DATA2
Output :   outd:		Calculation results
return: 0,     success
		Other, failure	
*************************************************************************************/
LIB_EXPORT int dukpt_3des_run_ex(int mode, char *ind, int size, char *outd, int des_mode, int key_tpye);



/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Initialize the dukpt key use IPEK
Input : 	type:		Initial key type
						0 = ipek 1= bdk
			mode:		Encryption method of initial key
						0=Plaintext 1= tmk encryption 2= kek encryption
			gid:		Key grouping£¬0
			init_ksn:	Initial ksn	
			init_key:	Initial key
			kvc		:	Key kvc(Key plaintext encryption 8 0x00)
Output :   Nothing
return: 0,     success
		Other, failure
*************************************************************************************/
LIB_EXPORT int dukpt_load_key(int mode, int type, int gid, unsigned char* init_ksn, unsigned char* init_key, char * kvc);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Initialize the dukpt key use IPEK
Input : 	gid:		Key grouping£¬0
			init_ksn:	Initial ksn	
			init_key:	Initial key
Output :   Nothing
return: 0,     success
		Other, failure
*************************************************************************************/
LIB_EXPORT int dukpt_init_ipek(unsigned char gid, unsigned char* init_ksn, unsigned char* init_key);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Initialize the dukpt key use IPEK  Ciphertext
Input : 	gid:		Key grouping£¬0
			key:		ipek Ciphertext
			kvc:		Key kvc(Key plaintext encryption 8 0x00)
Output :   Nothing
return: 0,     success
		Other, failure
*************************************************************************************/
LIB_EXPORT int dukpt_init_ciphertext_ipek(unsigned char gid, unsigned char* key, char * kvc);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Initialize the dukpt key use BDK
Input : 	gid:		Key grouping£¬0
			init_ksn:	Initial ksn	
			init_key:	BDK
Output :   Nothing
return: 0,     success
		Other, failure
*************************************************************************************/
LIB_EXPORT int dukpt_init_bdk(unsigned char gid, unsigned char* init_ksn, unsigned char* init_key);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:	Computing mac
Input : 	fid:		SEC_MKSK_FIELD/SEC_DUKPT_FIELD
			gid:		Key grouping, 0-9
			format:		SEC_MAC_UPAY_FORMAT/SEC_MAC_X99_FORMAT/SEC_MAC_X919_FORMAT/SEC_MAC_XOR_FORMAT
			data:		mac source data
			len:		data length
			key_tpye:	DUKPT_DES_KEY_MAC1/DUKPT_DES_KEY_MAC2
Output :    mac:		result
return: 0,     success
		Other, failure
*************************************************************************************/
LIB_EXPORT int sec_mac_proc(int fid, int gid, int format, char *data, int len, char *mac, int key_tpye);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Read pin ciphertext from the security keyboard
Input : 	fid:		SEC_MKSK_FIELD/SEC_DUKPT_FIELD
			gid:		Key grouping, 0-9
			format:		SEC_PIN_FORMAT0-SEC_PIN_FORMAT4
			pan:		card number
			pin:		pin plaintext
			pinblock:	Pinblock ciphertext
return: 0,     success
		Other, failure
*************************************************************************************/
LIB_EXPORT int sec_encrypt_pin_proc(int fid, int format, int gid, char * pan, char *pinblock, char * pin);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions:Set enable/disable pin input mode
Input : 	mode:		1 open 0 close
			length:		Pin input length
return: 0,     success
		Other, failure
*************************************************************************************/
LIB_EXPORT void sec_set_pin_mode(int mode, int length);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions: Save the private key to the security module
Input : 	index:		key index(0-9)
			length:		rsa byte size(128/256)
			p:			Private key P component
			q:			Private key Q component
return: 0,     success
		Other, failure
*************************************************************************************/
LIB_EXPORT int sec_save_rsa_pri_key(int index, int length, char * p, char * q);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions: Save the public key to the security module
Input : 	index:		key index(0-9)
			length:		rsa key byte size(128/256)
			n:			Public  key N component
return: 0,     success
		Other, failure
*************************************************************************************/
LIB_EXPORT int sec_save_rsa_puk_key(int index, int length, char * n);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:lx
Functions: RSA block calculation
Input : 	index:		key index(0-9)
			length:		rsa key byte size(128/256)
			ind:		in data
Output£º	outd:		out data
return: 0,     success
		Other, failure
*************************************************************************************/
LIB_EXPORT int sec_rsa_block(int index, char * ind, char *outd, int length);


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

LIB_EXPORT int dukpt_get_ksn(unsigned char gid, unsigned char * ksn);
LIB_EXPORT int dukpt_init_key(unsigned char gid, unsigned char* init_ksn, unsigned char* init_key);

