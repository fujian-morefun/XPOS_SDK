#ifndef __SM_H__
#define __SM_H__

#ifdef __cplusplus
extern "C"{
#endif

#ifndef TESTDLL_API

#define TESTDLL_API

#else

#ifdef TESTDLL_EXPORTS

#define TESTDLL_API __declspec(dllexport)

#else

#define TESTDLL_API __declspec(dllimport)

#endif

#endif



typedef struct{
	unsigned char m_ENTLa[2];	/*bits of IDa, format sample: if a IDa is "abcd" 32 bits, then the ENTLa is "0x00, 0x20"*/
	unsigned char *m_IDa;		/*a pointer point to IDa*/
	unsigned char *m_p;			/*hex string format*/
	unsigned char *m_n;			/*hex string format*/
	unsigned char *m_a;			/*hex string format*/
	unsigned char *m_b;			/*hex string format*/
	unsigned char *m_Xg;		/*hex string format*/
	unsigned char *m_Yg;		/*hex string format*/
	unsigned char *m_Xa;		/*public key Pa, hex string format*/
	unsigned char *m_Ya;		/*public key Pa, hex string format*/
	unsigned char *m_da;		/*private key, hex string format*/
}SM2KEY;


/*=============================================================================
** public function:
**   Verify the signature r||s by the sm2 public key.
** args:    [in] key: a sm2 key, the member m_da is the private key that can be NULL;
** args:    [in] r,s: the signature of a msg, r || s, they are HEX string format;
** args:    [in] msg: a pointer point of the original msg;
** args:    [in] msglen: the length of msg;
** return 0: verify ok; -1: failure.
**============================================================================*/
TESTDLL_API int SM2Verify(SM2KEY *key, unsigned char *r, unsigned char *s, unsigned char *msg, unsigned int msglen);
TESTDLL_API void SM2Sample(void);

/*=============================================================================
** public function:
**   Calculating encryption/decryption contents.
** args:    [out] output: a pointer point to hash contents, 32 bytes;
** args:    [in] input: a pointer point to original contents;
** args:    [in] len: the length of original contents;
** return 0: success; -1: failure.
**============================================================================*/
TESTDLL_API int SM3Calc(unsigned char *output, unsigned char *input, int len);
TESTDLL_API void SM3Sample(void);

/*=============================================================================
** public function:
**   Calculating encryption/decryption contents.
** args:    [out] output: a pointer point to encryption contents, 16 bytes;
** args:    [in] input: a pointer point to plaintext contents, 16 bytes;
** args:    [in] key: a pointer point to encryption/decryption key, 16 bytes;
** args:    [in] direction: 0: encrypt, 1: decrypt;
** return 0: success; -1: failure.
**============================================================================*/
TESTDLL_API int SM4Calc(unsigned char *output, unsigned char *input, unsigned char *key, unsigned int direction);
TESTDLL_API void SM4Sample(void);


#ifdef __cplusplus
}
#endif//end of #ifdef __cplusplus

#else

#endif//end of #ifndef __SM_H__