#pragma once

#include "pub/pub.h"

#define MAX_AP_LIST_SIZE	10

typedef struct __st_ap_list{
	int ecn;
	char ssid[64];
	char utf8ssid[64];
	int rssi;
	char mac[20];
	int channel;
	int freq;
}st_ap_list;

LIB_EXPORT void wf_proc_ap_line_test();
LIB_EXPORT int wf_list_ap(st_ap_list * ap_list);
LIB_EXPORT int wf_link_ap(st_ap_list * ap_list , char * pwd);
LIB_EXPORT int wf_link_ap_ex(st_ap_list * ap_list , char * pwd,int flag);
LIB_EXPORT int wf_unlink_ap();
