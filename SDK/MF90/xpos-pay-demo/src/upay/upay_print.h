#pragma once

typedef struct __st_card_info{
	char title[32];
	char pan[32];
	char amt[32];
	char expdate[32];
}st_card_info;

int upay_print_proc(st_card_info *card_info);
