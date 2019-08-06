#pragma once

#include "pub\pub.h"

LIB_EXPORT void gprs_sock_clear(int s);
LIB_EXPORT int gprs_sock_recv(int s, unsigned char * buff, int len, unsigned int timeover);
LIB_EXPORT int gprs_sock_send(int s, unsigned char * buff , int size, unsigned int flags);
LIB_EXPORT int gprs_sock_close(int s);
LIB_EXPORT int gprs_sock_connect(int s, char * pIp, int nPort);
LIB_EXPORT void gprs_sock_init(void);
LIB_EXPORT void gprs_sock_fifo_resize(int index , int size);

LIB_EXPORT void gprs_set_connnect_server_func(int index, void * func);