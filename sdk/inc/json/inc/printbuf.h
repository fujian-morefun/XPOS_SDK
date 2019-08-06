/*
 * $Id: printbuf.h,v 1.4 2006/01/26 02:16:28 mclark Exp $
 *
 * Copyright (c) 2004, 2005 Metaparadigm Pte. Ltd.
 * Michael Clark <michael@metaparadigm.com>
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See COPYING for details.
 *
 */

#ifndef _printbuf_h_
#define _printbuf_h_

#undef PRINTBUF_DEBUG

#include "pub\osl\inc\osl_log.h"
#define DEMO1_TRACE(...) 	osl_log("demo",LOG_LEVEL_TRACE, __VA_ARGS__);
#define DEMO1_TRACE_BUFF(b,s) 	osl_log_buff("demo",LOG_LEVEL_TRACE, b,s);


struct printbuf {
  char *buf;
  int bpos;
  int size;
};

LIB_EXPORT struct printbuf*
printbuf_new();

LIB_EXPORT int
printbuf_memappend(struct printbuf *p, char *buf, int size);

LIB_EXPORT int
sprintbuf(struct printbuf *p, const char *msg, ...);

LIB_EXPORT void
printbuf_reset(struct printbuf *p);

LIB_EXPORT void
printbuf_free(struct printbuf *p);

#endif
