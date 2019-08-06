#pragma once

#include "pub\pub.h"

LIB_EXPORT void wifi_sock_clear(int s);
LIB_EXPORT int wifi_sock_recv(int s, unsigned char * buff, int len, unsigned int timeover);
LIB_EXPORT int wifi_sock_recv2(int s, unsigned char * buff, int len, unsigned int timeover);
LIB_EXPORT int wifi_sock_send(int s, unsigned char * buff , int size, unsigned int flags);
LIB_EXPORT int wifi_sock_close(int s);
LIB_EXPORT int wifi_sock_connect(int s, char * pIp, int nPort);
LIB_EXPORT int wifi_sock_connect_ex(int s, char * pIp, int nPort, char * type);
LIB_EXPORT void wifi_sock_init(void);
LIB_EXPORT void wifi_sock_fifo_resize(int index , int size);
LIB_EXPORT void wifi_set_connnect_server_func(int index, void * func);