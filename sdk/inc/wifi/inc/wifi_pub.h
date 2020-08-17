#pragma once

#include "pub\pub.h"

#ifdef __cplusplus
extern "C"{
#endif

int  wp_get_str_item(char * line, char * item , int size);
int  wp_get_int_item(char * line, int * val);
void wp_set_esc(char * src, char *dst);
int  wp_get_signal(int rssi);

int wp_get_ap_state();
int wp_get_local_state();

int  wp_send_wait_return(char *cmd , int timeover , char * retstr , int len , int count);
int  wp_send_wait_return_buff(char *cmd , int timeover , char * retstr , int len , int count);

//int  wp_get_model_ver(char *buff , int len);
//int  wp_get_echo();

LIB_EXPORT void wp_set_ap_pwd(char * mac, char *pwd);
LIB_EXPORT void wp_get_ap_pwd(char * mac, char *pwd);
void wp_set_pause(int val);

void wifi_set_link_state(int state);
void _wu_wifi_initproc(void * pParam);
LIB_EXPORT int wifi_init();
LIB_EXPORT char * wifi_model_ver();
LIB_EXPORT int wifi_get_link_state();
LIB_EXPORT int wifi_get_signal();

LIB_EXPORT char * wifi_get_ssid();
LIB_EXPORT char * wifi_get_ap_mac();
LIB_EXPORT int wifi_get_rssi();
LIB_EXPORT int wifi_get_channel();

LIB_EXPORT char * wifi_get_local_mac();
LIB_EXPORT char * wifi_get_local_ip();

LIB_EXPORT int wf_start_smart();
LIB_EXPORT int wf_stop_smart();
LIB_EXPORT int wifi_get_exist();

#ifdef __cplusplus
}
#endif	