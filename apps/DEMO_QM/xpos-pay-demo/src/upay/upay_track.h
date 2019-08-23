#pragma once

#include "driver\mf_magtek.h"

int upay_track_get_expdate(struct magtek_track_info * track_info , char *expdate);
int upay_track_get_service_code24(struct magtek_track_info * track_info ,char * code24 );
int upay_track_get_pan(struct magtek_track_info * track_info , char * pan );
int upay_track_is_valid(struct magtek_track_info * track_info);
int upay_track_get_chname(struct magtek_track_info * track_info , char *chname );
int upay_track_is_icc(struct magtek_track_info * track_info);