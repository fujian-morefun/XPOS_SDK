#ifndef XDK2_GLOBAL_H
#define XDK2_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QApplication>
#include <QDesktopWidget>

#ifdef XDK2_USER_LIB
# define XDK2_USERLIB_EXPORT Q_DECL_EXPORT
#else
# define XDK2_USERLIB_EXPORT Q_DECL_IMPORT
#endif

#include <xtype.h>

#ifdef WIN32
#include <io.h>
#endif
#include <filedef.h>

#include <OSLayer/inc/OSL_Inc.h>

#define PRODUCT_TRACE_Ex(level,  ...) \
	LOG_TraceLow("emv", level, __FILE__, __LINE__, __VA_ARGS__)

#define PRODUCT_TRACEBUF_Ex(level, buffer, size) \
	LOG_TraceBuf("emv", level, __FILE__, __LINE__, buffer, size)

#define TRACE( ...)	PRODUCT_TRACE_Ex(LOG_LEVEL_TRACE,__VA_ARGS__)

#endif // XDK2_GLOBAL_H
