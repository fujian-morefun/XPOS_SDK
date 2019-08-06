/* 
 * Copyright (c) 2015 MoreFun
 *
 * @date 2015-3-7
 * @author ZhaoJinYun
 *
*/

#ifndef __MF_DRIVERLIB_H
#define __MF_DRIVERLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mf_key.h"
#include "mf_spi_flash.h"
#include "mf_serial.h"
#include "mf_misc.h"
#include "mf_auxlcd.h"
#include "mf_icc.h"
#include "mf_magtek.h"
#include "mf_supply_power.h"
#include "mf_thermal_printer.h"
#include "mf_tamper.h"
#include "mf_rtc.h"
#include "mf_simple_rfid.h"
#include "mf_system.h"
#include "mf_touch.h"
#include "mf_bluetooth.h"
#include "mf_usb_cdc.h"
#include "mf_audio_raw.h"
#include "mf_stripereader.h"
#include "mf_onchip_flash.h"

int mf_driverlib_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __MF_DRIVERLIB_H */



