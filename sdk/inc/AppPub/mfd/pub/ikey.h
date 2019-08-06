#pragma once

typedef struct __mfd_key_func{
	void (*InitKeyFile)(void *);
	void (*SetTransKey)(char * pKey);
	void (*SetMainKey)(char * pKey , int index);
	void (*SetPinEnc)(char * pKey , int index);
	void (*SetMacEnc)(char * pKey , int index);
	void (*SetMagdec)(char * pKey , int index);

	char * (*GetTransKey)();
	char * (*GetMainKey)(int index);
	char * (*GetPinEnc)(int index);
	char * (*GetMacEnc)(int index);
	char * (*GetMagdec)(int index);
}mfd_key_func;