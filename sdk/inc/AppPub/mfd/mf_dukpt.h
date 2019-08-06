#pragma once

#include "pub/pub.h"

LIB_EXPORT void dukpt_init();
LIB_EXPORT int dukpt_get_key(unsigned char gid, unsigned char* key, unsigned char * ksn);
LIB_EXPORT int dukpt_load_init_key(unsigned char gid, unsigned char* init_ksn, unsigned char* init_key);
