#include "pub/pub.h"
#pragma once

LIB_EXPORT void osl_tts_init(int mode, int readsize, int fifosize);
LIB_EXPORT void osl_tts_batch_begin();
LIB_EXPORT void osl_tts_batch_end();
LIB_EXPORT int osl_tts_play(char * sndfile);

LIB_EXPORT void osl_tts_beep_mode(int mode);

LIB_EXPORT void osl_tts_beep(int hz, int ms);

LIB_EXPORT void osl_tts_set_level(int val);
LIB_EXPORT int osl_tts_set_data_path(char flag);
LIB_EXPORT int osl_tts_get_state();
LIB_EXPORT void osl_tts_clear();