#pragma once

#define PAY_RET_EXIT		-1
#define PAY_RET_TIMEOVER	-2
#define PAY_RET_OK			0
#define PAY_RET_RFCARD		1
#define PAY_RET_SCAN		2



void sdk_pay(int key);
int upay_barscan();