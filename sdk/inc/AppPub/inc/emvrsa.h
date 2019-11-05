#ifndef _RSA_H_
#define _RSA_H_

#include "pub/pub.h"
//#include "platform.h"

/* Type definitions.
 */
/* POINTER defines a generic pointer type */
typedef unsigned char *POINTER;

/* UINT2 defines a two byte word */
typedef unsigned short int UINT2;

/* UINT4 defines a four byte word */
typedef unsigned long int UINT4;



#define PROTO_LIST(list) list

#define MIN_RSA_MODULUS_BITS 508
#define MAX_RSA_MODULUS_BITS 2048
#define MAX_RSA_MODULUS_LEN ((MAX_RSA_MODULUS_BITS + 7) / 8)
#define MAX_RSA_PRIME_BITS ((MAX_RSA_MODULUS_BITS + 1) / 2)
#define MAX_RSA_PRIME_LEN ((MAX_RSA_PRIME_BITS + 7) / 8)




#define RE_LEN 0x0406
#define RE_MODULUS_LEN 0x0407
#define RE_PRIVATE_KEY 0x0409
#define RE_PUBLIC_KEY 0x040a
#define RE_DATA 0x0401


/* RSA public and private key.
 */
typedef struct {
	unsigned int bits;                           							/* length in bits of modulus */
	unsigned char modulus[MAX_RSA_MODULUS_LEN];                    	/* modulus */
	unsigned char exponent[MAX_RSA_MODULUS_LEN];           		/* public exponent When filling the die, fill right and fill front with 0.*/
} R_RSA_PUBLIC_KEY;

typedef struct {
	unsigned short int bits;                     /* length in bits of modulus */
	unsigned char modulus[MAX_RSA_MODULUS_LEN];  /* modulus */
	unsigned char publicExponent[MAX_RSA_MODULUS_LEN];     /* public exponent */
	unsigned char exponent[MAX_RSA_MODULUS_LEN]; /* private exponent */
	unsigned char prime[2][MAX_RSA_PRIME_LEN];   /* prime factors */
	unsigned char primeExponent[2][MAX_RSA_PRIME_LEN];     /* exponents for CRT */
	unsigned char coefficient[MAX_RSA_PRIME_LEN];          /* CRT coefficient */
} R_RSA_PRIVATE_KEY;

LIB_EXPORT int RSAPublicEncrypt PROTO_LIST
((unsigned char *, unsigned int *, unsigned char *, unsigned int,
  R_RSA_PUBLIC_KEY *));
LIB_EXPORT int RSAPublicDecrypt PROTO_LIST
((unsigned char *, unsigned int *, unsigned char *, unsigned int,
  R_RSA_PUBLIC_KEY *));

//Fill in the middle with chFill
LIB_EXPORT int RSAPublicEncrypt_ex(unsigned char *output, unsigned int * outputLen, unsigned char *input, unsigned int inputLen, R_RSA_PUBLIC_KEY *publicKey, unsigned char chFill); 

//Special Filling Requirements of Guangdong Huantong Payment PKCS#1
LIB_EXPORT int RSAPublicEncryptEx PROTO_LIST
((unsigned char *, unsigned int *, unsigned char *, unsigned int,
 R_RSA_PUBLIC_KEY *));

//Private key decryption, special filling (non-PKCS standard), non-zero data from the back
LIB_EXPORT int RSAPrivateDecryptEx PROTO_LIST 
((unsigned char *, unsigned int *, unsigned char *,unsigned int, R_RSA_PRIVATE_KEY *));

LIB_EXPORT int RSAPublicDecrypt (unsigned char *output, unsigned int *outputLen, unsigned char *input, unsigned int inputLen, R_RSA_PUBLIC_KEY *publicKey);
LIB_EXPORT int RSAPrivateEncrypt (unsigned char *output,unsigned int * outputLen,unsigned char *input,unsigned int inputLen,R_RSA_PRIVATE_KEY *privateKey);
LIB_EXPORT int RSAPrivateDecrypt (unsigned char *output, unsigned int * outputLen, unsigned char *input, unsigned int inputLen, R_RSA_PRIVATE_KEY *privateKey);


LIB_EXPORT int RSAPublicBlock (unsigned char *output, unsigned int * outputLen, unsigned char *input,unsigned int inputLen, R_RSA_PUBLIC_KEY *publicKey);
LIB_EXPORT int RSAPrivateBlock (unsigned char *output, unsigned int * outputLen, unsigned char *input, 	unsigned int inputLen, R_RSA_PRIVATE_KEY *privateKey);

#endif

