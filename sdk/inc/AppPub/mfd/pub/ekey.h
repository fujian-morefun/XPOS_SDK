#pragma once

#include "pub/pub.h"
#include "ikey.h"

#ifdef __cplusplus
extern "C"{
#endif

LIB_EXPORT void E_InitKeyFile(void * p);

LIB_EXPORT void E_SetTransKey(char * pKey);
LIB_EXPORT void E_SetMainKey(char * pKey , int index);
LIB_EXPORT void E_SetPinEnc(char * pKey , int index);
LIB_EXPORT void E_SetMacEnc(char * pKey , int index);
LIB_EXPORT void E_SetMagdec(char * pKey , int index);

LIB_EXPORT char *E_GetTransKey();
LIB_EXPORT char *E_GetMainKey(int index);
LIB_EXPORT char *E_GetPinEnc(int index);
LIB_EXPORT char *E_GetMacEnc(int index);
LIB_EXPORT char *E_GetMagdec(int index);

LIB_EXPORT void ekey_init(mfd_key_func *key_func);

#ifdef __cplusplus
}
#endif
