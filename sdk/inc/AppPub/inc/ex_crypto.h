#ifndef _CRYPTO_H_
#define _CRYPTO_H_

#include "mf_basic.h"
#include "pub/pub.h"
/******************************************************************************
* crypto
******************************************************************************/
/******************************************************************************
* crypto RSA
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*指数*/
#define XM_RSA_EXP_3	0x03
#define XM_RSA_EXP_10001	0x010001
/*模长*/
#define XM_MIN_RSA_MODULUS_BITS	1024
#define XM_MAX_RSA_MODULUS_BITS	2048
#define XM_MIN_RSA_MODULUS_LEN	128 //128 BYTES
#define XM_MAX_RSA_MODULUS_LEN	256 //256 BYTES

#define XM_MIN_RSA_PRIME_LEN	XM_MIN_RSA_MODULUS_LEN
#define XM_MAX_RSA_PRIME_LEN	XM_MAX_RSA_MODULUS_LEN
/*加解密模式*/
#define XM_RSA_ENCRYPT	0x00
#define XM_RSA_DECRYPT	0x01

/**/
#define XM_RSA_PKCS1_PADDING	1
#define XM_RSA_SSLV23_PADDING	2
#define XM_RSA_NO_PADDING		3
#define XM_RSA_PKCS1_OAEP_PADDING	4
#define XM_RSA_X931_PADDING	5

typedef struct {
	uint uiBits; //公钥模长  xx bits
	uchar ucModulus[XM_MAX_RSA_MODULUS_LEN];  //公钥内容, 后对齐，前补0x00
	uchar ucExponent[XM_MAX_RSA_MODULUS_LEN]; //公钥指数内容
} XM_RSA_PUBLIC_KEY;

typedef struct {
	unsigned short int bits;                     /* length in bits of modulus */
	unsigned char modulus[XM_MAX_RSA_MODULUS_LEN];  /* modulus */
	unsigned char publicExponent[XM_MAX_RSA_MODULUS_LEN];     /* public exponent */
	unsigned char exponent[XM_MAX_RSA_MODULUS_LEN]; /* private exponent */
	unsigned char prime[2][XM_MAX_RSA_PRIME_LEN];   /* prime factors */
	unsigned char primeExponent[2][XM_MAX_RSA_PRIME_LEN];     /* exponents for CRT */
	unsigned char coefficient[XM_MAX_RSA_PRIME_LEN];          /* CRT coefficient */
} XM_RSA_PRIVATE_KEY;


#define _sha1_uint8  unsigned char

#define _sha1_uint32 unsigned long int


typedef struct {
	_sha1_uint32 total[2];
	_sha1_uint32 state[5];
	_sha1_uint8 buffer[64];
}
sha1_context;
LIB_EXPORT extern int mf_sha1(const u8 *inbuf, int inlen, u8 *outbuf);

LIB_EXPORT int mf_RSAPubCalc(const XM_RSA_PUBLIC_KEY *ptPublicKey, u8 ucCryptType, int uPadingType, const void *pvDataIn, uint uiLenIn, void *pvDataOut, uint *puiLenOut);
LIB_EXPORT int mf_RSAPrivateCalc(const XM_RSA_PRIVATE_KEY *ptPublicKey, u8 ucCryptType, int uPadingType, const void *pvDataIn, uint uiLenIn, void *pvDataOut, uint *puiLenOut);

LIB_EXPORT int mf_random(uint uiLen, void *pvRandom);

#ifdef __cplusplus
}
#endif
#endif