#ifndef _MD5_H_
#define _MD5_H_

#include "pub/pub.h"
/////////////////////////////////////////////////////////////////   
/////////////////////////////////////////////////////////////////
#ifndef PROTOTYPES
#define PROTOTYPES 0
#endif

/* POINTER defines a generic pointer type */
typedef unsigned char *POINTER;

/* UINT2 defines a two byte word */
typedef unsigned short int UINT2;

/* UINT4 defines a four byte word */
typedef unsigned long int UINT4;

/* PROTO_LIST is defined depending on how PROTOTYPES is defined above.
If using PROTOTYPES, then PROTO_LIST returns the list, otherwise it
returns an empty list.
*/
#if PROTOTYPES
#define PROTO_LIST(list) list
#else
#define PROTO_LIST(list) ()
#endif
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////


/* MD5 context. */
typedef struct {
	UINT4 state[4];                                   /* state (ABCD) */
	UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
	unsigned char buffer[64];                         /* input buffer */
} MD5_CTX;


LIB_EXPORT void MD5Init (MD5_CTX *context);

LIB_EXPORT void MD5Update(MD5_CTX * context, unsigned char * input, unsigned int inputLen);

LIB_EXPORT void MD5Final(unsigned char * digest, MD5_CTX * context);

#endif
