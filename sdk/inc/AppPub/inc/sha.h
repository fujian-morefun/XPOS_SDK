#pragma once

#include "pub/pub.h"

#define uint32_t unsigned int
#define uint8_t unsigned char

LIB_EXPORT void mf_sha1_starts( sha1_context *ctx);
LIB_EXPORT void mf_sha1_update( sha1_context *ctx, _sha1_uint8 *input, _sha1_uint32 length);
LIB_EXPORT void mf_sha1_finish( sha1_context *ctx, _sha1_uint8 digest[20]);

//LIB_EXPORT void sha256_starts(sha256_context * ctx);
//LIB_EXPORT void sha256_update(sha256_context * ctx, uint8_t * input, uint32_t length);
//LIB_EXPORT void sha256_finish(sha256_context * ctx, uint8_t digest[32]);

	