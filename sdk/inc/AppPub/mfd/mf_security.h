#ifndef _MF_SECURITY_
#define _MF_SECURITY_
#pragma once



#ifdef __cplusplus
extern "C"{
#endif


#include <time.h>

/******************************************************************************
* PIN FORMAT
******************************************************************************/
#define	ISO9564_FORMAT0		0x00
#define	ISO9564_FORMAT1		0x01
#define	ISO9564_FORMAT2		0x02
#define	ISO9564_FORMAT3		0x03
/******************************************************************************
* SCKEY FIELD
******************************************************************************/
#define KF_FIXED		0x00
#define KF_MKSK			0x01
#define KF_DUKPT		0x02
#define KF_FIELD		0x03
#define KF_SM			0x04
/******************************************************************************
* SCKEY TYPE
******************************************************************************/
#define KT_MAINKEY		0x00
#define KT_PINENC		0x01
#define KT_MACENC		0x02
#define KT_MAGDEC		0x03
#define KT_TRANSKEY		0x04
#define KT_DUKPTINITKEY	0x05
#define KT_TYPE			0x06

/******************************************************************************
* SCKEY ALGORITHM TYPE
******************************************************************************/
#define KA_DES		0x00
#define KA_AES		0x01

/******************************************************************************
* SCKEY SAVE TYPE
******************************************************************************/
#define KF_KEYLOAD_KC	0x00	/**< use password and plaintext key component*/
#define KF_MANUAL_KC	0x01	/**< manual input password and plaintext key component*/
#define KF_CRYPTO		0x02	/**< crypted key */
#define KF_CLEARTEXT	0x03	/**< cleartext key */
#define KF_FORM			0x04

#define ALGO_MAC_X919	0x00

#include "pub/pub.h"

LIB_EXPORT void mfs_set_key_save_type(int type, unsigned int addr);
LIB_EXPORT int mfs_security_init(void);
LIB_EXPORT int mfs_setkeylen(int keylen);
LIB_EXPORT int mfs_setwkeylen(int keylen);
LIB_EXPORT int mfs_setkeklen(int len);

LIB_EXPORT int mfs_security_close(void);

LIB_EXPORT int mfs_clear_pci_key(void);

LIB_EXPORT int mfs_delete_key(unsigned int fid, unsigned int gid);

LIB_EXPORT int mfs_save_plaintext_key(unsigned int fid, unsigned int gid, unsigned int type, const unsigned char *psw,
							const unsigned char *key, const unsigned char *ksn, unsigned char *kvc);

LIB_EXPORT int mfs_save_encrypted_key(unsigned int fiD, unsigned int giD, unsigned int type,const unsigned char * key,
							const unsigned char * ksn, unsigned char * kvc);

LIB_EXPORT int mfs_get_des(unsigned int fid, unsigned int gid, unsigned char *inData, unsigned char *outData);

//没有异或，直接算DES
LIB_EXPORT int mfs_get_mac(unsigned int fid, unsigned int gid, unsigned int algo, unsigned char *data, 
				 unsigned int len, unsigned char *mac, unsigned char *ksn);

//有异或而且算DES
LIB_EXPORT int mfs_get_mac_ex(unsigned int fid, unsigned int gid, unsigned int algo, unsigned char *data, 
						   unsigned int len, unsigned char *mac, unsigned char *ksn);

LIB_EXPORT int mfs_get_online_pin(const unsigned char *pin, int pin_len, unsigned int fid, unsigned int gid,
						unsigned int format, const unsigned char *pan, unsigned char *ksn, unsigned char *pinblock);
LIB_EXPORT int mfsm_get_online_pin(const unsigned char *pin, int pin_len, unsigned int fid, unsigned int gid,
						unsigned int format, const unsigned char *pan, unsigned char *ksn, unsigned char *pinblock);

LIB_EXPORT int mfs_get_random_number(unsigned int len, void *pbuf);

LIB_EXPORT int mfs_get_security_status(unsigned int *drs);

LIB_EXPORT int mfs_get_rsa(unsigned int exp_len, unsigned char *exponent, unsigned int mod_len, unsigned char *modulus,
				 unsigned int *len, unsigned char *data);

LIB_EXPORT int mfs_get_hash(unsigned char *data, unsigned int len, unsigned char *sum);

LIB_EXPORT int mfs_get_rtc(struct tm *pTime);

LIB_EXPORT int mfs_set_rtc(struct tm *pTime);

LIB_EXPORT int mfs_get_3des(char *inData, char *outData , int len , char * key , int keylen);

LIB_EXPORT int mfs_set_security_status(int flag);

LIB_EXPORT int mfs_save_encrypted_mk(int encrytype, unsigned int gid,const unsigned char * key, unsigned char * kvc);

//根据类型获取MAC

#define  MFS_ENCRYPTION_UCB 1
#define  MFS_ENCRYPTION_ECB 2
#define  MFS_ENCRYPTION_X919 3

//MFS_ENCRYPTION_X919 算法有异或
LIB_EXPORT int mfs_get_macex(int nType, unsigned int gid,char *psData,int nDataLen,char * sMac);



LIB_EXPORT int mfs_mac_ansix919(const char *pKey ,const char *data,int len,char *mac );

LIB_EXPORT int mfs_mac_ansix919_index(unsigned int keyindex ,const char *data,int len,char *mac );

/*------------security pin-------------------------------------------------*/
//MFD_API int mf_security_pin_open(void);
//MFD_API void mf_security_pin_close(void);
//MFD_API int mf_security_pin_read(int fd ,void *buf, int size, int timeout);			//timeout(ms)


//mac 新算法
LIB_EXPORT int mfs_set_mac_upay(int gid, char *data, int len, unsigned char *mac);
LIB_EXPORT int mf_sm_mac_upay(int gid, char *data, int len, unsigned char *mac);
LIB_EXPORT int mfs_set_mac_x99(int gid, char *data, int len, unsigned char *mac);
LIB_EXPORT int mfs_set_mac_x919(int gid, char *data, int len, unsigned char *mac);
LIB_EXPORT int mfs_set_mac_xor(int gid, char *data, int len, unsigned char *mac);





#define MFSDK_KT_MAINKEY		0x00
#define MFSDK_KT_PINENC			0x01
#define MFSDK_KT_MACENC			0x02
#define MFSDK_KT_MAGDEC			0x03
#define MFSDK_KT_TRANSKEY		0x04


#define MFSDK_ENCRYPT			0x00
#define MFSDK_DECRYPT			0x01


/**
* @brief Save the key in plaintext
* @param [type] Key type, one of MFSDK_KT_MAINKEY to MFSDK_KT_TRANSKEY
* @param [gid] Key Index 0-9
* @param [key] 16-byte key plaintext
* @param [kvc] 4 bytes kvc
* @return 0 succ
*/
LIB_EXPORT int mfsdk_save_plaintext_key(int type, int gid, unsigned char * key, unsigned char *kvc);


/**
* @brief Save the key ciphertext
* @param [type] Key type, one of MFSDK_KT_MAINKEY to MFSDK_KT_MAGDEC
* @param [gid] Key Index 0-9
* @param [key] 16-byte key ciphertext
* @param [kvc] 4 bytes kvc
* @return 0 succ
*/
LIB_EXPORT int mfsdk_save_encrypted_key(int type, int gid, unsigned char * key, unsigned char *kvc);

/**
* @brief Encryption and decryption operation
* @param [type] Key type, one of MFSDK_KT_MAINKEY to MFSDK_KT_MAGDEC
* @param [gid] Key Index 0-9
* @param [mode] MFSDK_ENCRYPT or MFSDK_DECRYPT
* @param [ind] Input data
* @param [size] Data size
* @param [outd] Output Data
* @return 0 succ
*/
LIB_EXPORT int mfsdk_3des_run(int type, int gid, int mode, unsigned char *ind, int size, unsigned char *outd);

#ifdef __cplusplus
}
#endif

#endif