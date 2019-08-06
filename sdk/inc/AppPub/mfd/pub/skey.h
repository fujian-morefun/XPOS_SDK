#pragma once

#include "pub/pub.h"
#include "ikey.h"

#ifdef __cplusplus
extern "C"{
#endif

LIB_EXPORT void S_InitKeyFile(void * p);

LIB_EXPORT void S_SetTransKey(char * pKey);
LIB_EXPORT void S_SetMainKey(char * pKey , int index);
LIB_EXPORT void S_SetPinEnc(char * pKey , int index);
LIB_EXPORT void S_SetMacEnc(char * pKey , int index);
LIB_EXPORT void S_SetMagdec(char * pKey , int index);

LIB_EXPORT char *S_GetTransKey();
LIB_EXPORT char *S_GetMainKey(int index);
LIB_EXPORT char *S_GetPinEnc(int index);
LIB_EXPORT char *S_GetMacEnc(int index);
LIB_EXPORT char *S_GetMagdec(int index);

LIB_EXPORT void skey_init(mfd_key_func *key_func);

#ifdef __cplusplus
}
#endif
