#pragma once

#include "pub/pub.h"

#ifdef __cplusplus
extern "C"{
#endif

LIB_EXPORT void set_key_save_type(int type, unsigned int addr);

LIB_EXPORT void InitKeyFile();

LIB_EXPORT void SetTransKey(char * pKey);
LIB_EXPORT void SetMainKey(char * pKey , int index);
LIB_EXPORT void SetPinEnc(char * pKey , int index);
LIB_EXPORT void SetMacEnc(char * pKey , int index);
LIB_EXPORT void SetMagdec(char * pKey , int index);

LIB_EXPORT char *GetTransKey();
LIB_EXPORT char *GetMainKey(int index);
LIB_EXPORT char *GetPinEnc(int index);
LIB_EXPORT char *GetMacEnc(int index);
LIB_EXPORT char *GetMagdec(int index);

#ifdef __cplusplus
}
#endif
