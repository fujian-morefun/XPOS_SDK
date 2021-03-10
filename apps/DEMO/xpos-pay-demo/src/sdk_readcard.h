#pragma once

#include "emvapi/inc/emv_api.h"

#ifndef NULL
#define NULL 0
#endif
#ifndef SUCC
#define SUCC 0
#endif
#ifndef FAIL
#define FAIL (-1)
#endif

typedef enum
{
	NO='0',
	YES='1'
}YESORNO;

void add_capk();

int upay_readcard_proc(st_read_card_in *card_in, st_read_card_out *card_out);

void init_service_prmacqkey(int binitial);
void clear_service_prmacqkey(void);

int sdk_readcard_init(void);

