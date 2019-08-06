#pragma once

#include "pub\osl\inc\osl_log.h"

#define ATCTRACE( ...)	osl_log( "json", LOG_LEVEL_WARN , __VA_ARGS__ )