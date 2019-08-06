/* 
 * Copyright (c) 2015 MoreFun
 *
 * @date 2015-02-12
 * @author ZhaoJinYun
 *
*/

#ifndef __MF_BLUETOOTH_H
#define __MF_BLUETOOTH_H

#ifdef __cplusplus
extern "C" {
#endif

enum 
{
	BT_LINK_STATE,
	BT_LINK_TXD_STATE,
	BT_ACCESS_STATUS,
	BT_POWERDEFAULT_SHUTDOWN_STATE,
};

enum
{
	BT_MODE_APP,
	BT_MODE_BOOT,
	BT_MODE_CONFIG,
};

enum
{
	BT_DEVICE_BM77 = 1,
	BT_DEVICE_I482E,
	BT_DEVICE_B710_BF,
	BT_DEVICE_DM501_B,
	BT_DEVICE_TC35661_502,
};

int mf_bluetooth_init(void);
int mf_bluetooth_droplink(void);
int mf_bluetooth_status(void);

int mf_bluetooth_start(int mode);
int mf_bluetooth_shutdown();

int mf_bluetooth_get_type(void);
int mf_bluetooth_set_name(char *name);
int mf_bluetooth_get_name(char *name);

int mf_bluetooch_get_mac(char *addr);

#ifdef __cplusplus
}
#endif

#endif /* __MF_BLUETOOTH_H */


