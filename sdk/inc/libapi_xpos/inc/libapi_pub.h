#ifndef _LIBAPI_PUB_H_
#define _LIBAPI_PUB_H_

#ifdef WIN32
#ifdef DLL_EXPORTS
#define LIB_EXPORT __declspec(dllexport)
#else
#define LIB_EXPORT __declspec(dllimport)
#endif
#else
#define LIB_EXPORT

#endif

#include "def.h"

#endif

