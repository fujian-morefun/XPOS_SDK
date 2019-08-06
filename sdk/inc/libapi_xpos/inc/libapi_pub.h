#pragma once

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

