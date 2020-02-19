#pragma once


#include "pub/pub.h"

#ifdef __cplusplus
extern "C"{
#endif

#define G2U(astr)	astr2utf8str_ex(astr)

LIB_EXPORT char * astr2utf8str_ex(char * astr);		
LIB_EXPORT int astr2ucstr(unsigned char *astr, int astrlen, unsigned char *ucstr , int buffsize);
LIB_EXPORT int ucstr2astr(unsigned short *ucstr, int ucchars, unsigned char *astr, int buffsize);
LIB_EXPORT int utf8str2astr( char *utfstr, int utfchars, unsigned char *astr, int buffsize);
LIB_EXPORT int astr2utf8str(unsigned char *astr, int astrlen, unsigned char *utfstr , int buffsize);
LIB_EXPORT void creat_table(int type);
LIB_EXPORT void ucicode_set_type(int val);
LIB_EXPORT int osl_utf8_to_unicode(unsigned char *instr, unsigned char *outstr);
LIB_EXPORT int osl_unicode_to_utf8 (unsigned short codepoint, char *outstr);

#ifdef __cplusplus
}
#endif




