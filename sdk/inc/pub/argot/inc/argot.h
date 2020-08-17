#ifndef _ARGOT_H_____
#define _ARGOT_H_____

#include "pub/pub.h"

#ifdef __cplusplus
extern "C"{
#endif


LIB_EXPORT void argot_set_post_func(void * pfun);

LIB_EXPORT void argot_init(char enterval,char cleanchar);

LIB_EXPORT void argot_keyinput( char key);

typedef void (*argot_proc)(const char *argot);


LIB_EXPORT int argot_regisert(const char *key,argot_proc proc);


#ifdef __cplusplus
}
#endif

#endif