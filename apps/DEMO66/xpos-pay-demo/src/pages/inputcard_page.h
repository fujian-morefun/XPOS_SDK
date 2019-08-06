#pragma once

#include "driver\mf_magtek.h"

enum{
	INPUTCARD_RET_QUIT,
	INPUTCARD_RET_MAGTEK,
	INPUTCARD_RET_ICC,
	INPUTCARD_RET_RFID,
	INPUTCARD_RET_TIME_OVER ,
};


int inputcard_page_showd(char * title, struct magtek_track_info *trackinfo);


