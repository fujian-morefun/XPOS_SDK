#pragma once
#include "libapi_xpos\inc\libapi_gui.h"

typedef enum {
	status_WaitNetwork,
	status_Connecting,
	status_Recving,
	status_Paused,
}e_status;

int mqtt_proc_init();

int mqtt_proc_Pause();
int mqtt_proc_Resume();

int mqtt_proc_default_msg(st_gui_message * pmsg);


const char * mqtt_status_text();

e_status mqtt_status();


int mqtt_proc_publish(const char *payload);