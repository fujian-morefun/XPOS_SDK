#pragma once

#include "pub/pub.h"
#include "ikey.h"

#ifdef __cplusplus
extern "C"{
#endif

LIB_EXPORT void F_InitKeyFile(void * p);

LIB_EXPORT void F_SetTransKey(char * pKey);
LIB_EXPORT void F_SetMainKey(char * pKey , int index);
LIB_EXPORT void F_SetPinEnc(char * pKey , int index);
LIB_EXPORT void F_SetMacEnc(char * pKey , int index);
LIB_EXPORT void F_SetMagdec(char * pKey , int index);

LIB_EXPORT char *F_GetTransKey();
LIB_EXPORT char *F_GetMainKey(int index);
LIB_EXPORT char *F_GetPinEnc(int index);
LIB_EXPORT char *F_GetMacEnc(int index);
LIB_EXPORT char *F_GetMagdec(int index);

LIB_EXPORT void fkey_init(mfd_key_func *key_func);

#ifdef __cplusplus
}
#endif
