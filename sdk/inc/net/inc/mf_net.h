#pragma once
#include "pub/pub.h"

#define MODEM_USER_BACK_DIAL	0

LIB_EXPORT void net_func_set_num(char *num1, char * num2, char * num3);
LIB_EXPORT void net_func_link_init();
LIB_EXPORT int net_func_task_op(int timeover , int op);

LIB_EXPORT int  net_func_unlink();
LIB_EXPORT int  net_func_link(char * title, char * apn ,int timetry, int timeover);
LIB_EXPORT int  net_func_link_ex(char * title, char * apn ,int timeover,char * user, char * psw);
LIB_EXPORT int  net_func_link_state();
LIB_EXPORT char * net_func_module_id();
LIB_EXPORT char * net_func_module_ver();