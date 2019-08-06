#pragma once

#include "pub/pub.h"

LIB_EXPORT int aq_ssl_init(int index, char * cacert, char * clientcert, char * clientkey,int level);
LIB_EXPORT int aq_ssl_connect(int index , char * ip , int port, void * func);
LIB_EXPORT int aq_ssl_send(int index, char * pdata, int size);

//到达size长度后才收
LIB_EXPORT int aq_ssl_recv(int index, char * pdata, int size);

//有多少收多少
LIB_EXPORT int aq_ssl_recv2(int index, char * pdata, int size);
LIB_EXPORT int aq_ssl_recv3(int index);

LIB_EXPORT int aq_ssl_close(int index);