#pragma once

#include <pub/pub.h>
#ifdef __cplusplus
extern "C"{
#endif


// https
LIB_EXPORT  int mf_https_comm(char * url , char * body, char * response, void * func);


#ifdef __cplusplus
}
#endif
