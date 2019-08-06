
#pragma once

#include "xgui_pub.h"

void xgui_state_init();
void xgui_state_set_mode(int mode);
LIB_EXPORT int xgui_state_get_mode();
LIB_EXPORT int xgui_state_func_add(void * pfunc);
LIB_EXPORT void xgui_state_set_state(int state);
LIB_EXPORT unsigned int  xgui_statte_timer_proc(void*p);

