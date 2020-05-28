#pragma once
#include "pub/pub.h"
typedef void * ap2_ws;


LIB_EXPORT ap2_ws ap2ws_create();
LIB_EXPORT int ap2ws_destory( ap2_ws s );

LIB_EXPORT int ap2ws_head_begin( ap2_ws s ,const char *host ,int port ,const char *path);
LIB_EXPORT int ap2ws_head_protocol( ap2_ws s , const char *protocol );
LIB_EXPORT int ap2ws_head_end( ap2_ws s );


LIB_EXPORT const char * ap2ws_head_data( ap2_ws s );
LIB_EXPORT int ap2ws_head_len( ap2_ws s );

LIB_EXPORT int ap2ws_acceptkey( ap2_ws s , const char *recv,int recvlen );

LIB_EXPORT int ap2ws_packframe(unsigned char *data, unsigned int dataLen, unsigned char *p);


typedef int (*socket_read)(void* p, unsigned char* buffer, int len, int timeout_ms);
LIB_EXPORT int ap2ws_readframe( void *fd, int timeout_ms,  socket_read readlen );