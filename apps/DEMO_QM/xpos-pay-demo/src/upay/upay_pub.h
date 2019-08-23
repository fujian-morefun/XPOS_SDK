#pragma once

#include "upay_define.h"
#include "pub\tlv\tlv_func.h"


st_tmf_param  * upay_pub_create( int eTransType );
void upay_pub_destory( st_tmf_param  * tmf_param );
