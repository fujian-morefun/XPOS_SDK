#ifndef _HASHFUN_H_
#define _HASHFUN_H_

#include "pub/pub.h"

LIB_EXPORT extern unsigned int BKDRHash(char *str);
LIB_EXPORT extern unsigned int SDBMHash(char *str);
LIB_EXPORT extern unsigned int RSHash(char *str);
LIB_EXPORT extern unsigned int JSHash(char *str);
LIB_EXPORT extern unsigned int PJWHash(char *str);
LIB_EXPORT extern unsigned int ELFHash(char *str);
LIB_EXPORT extern unsigned int DJBHash(char *str);
LIB_EXPORT extern unsigned int APHash(char *str);
#endif
