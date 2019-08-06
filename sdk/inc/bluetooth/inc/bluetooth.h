#pragma once

#include "pub\pub.h"

LIB_EXPORT int bluetooth_is_connect(void);
LIB_EXPORT int bluetooth_recv_count();
LIB_EXPORT int bluetooth_recv(char *buff, int size);
LIB_EXPORT int bluetooth_send(char *buff, int size);
LIB_EXPORT void bluetooth_drop();
LIB_EXPORT void bluetooth_set_gkey_state(int state);		// 1 ∆•≈‰ 2 ≤ª∆•≈‰
LIB_EXPORT int bluetooth_set_name(char *name);
LIB_EXPORT int bluetooth_set_name_ex(char *name,char * mac);
LIB_EXPORT int bluetooth_get_name(char *name);
LIB_EXPORT int bluetooth_get_addr(char *addr);

LIB_EXPORT int bluetooth_state_proc_func(int flag);
LIB_EXPORT void bluetooth_init(void);
LIB_EXPORT void bluetooth_run_proc();
LIB_EXPORT void bluetooth_set_pause(int mode);
LIB_EXPORT int  bluetooth_get_pause();

LIB_EXPORT char *bluetooth_get_type();








