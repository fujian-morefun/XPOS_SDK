/* 
 * Copyright (c) 2015 MoreFun
 *
 * @date 2015-2-18
 * @author ZhaoJinYun
 *
*/

#ifndef __MF_SIMPLE_RFID_H
#define __MF_SIMPLE_RFID_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef RFID_CMD_MIFARE_AUTH1A
#define RFID_CMD_MIFARE_AUTH1A	0x60
#define RFID_CMD_MIFARE_AUTH1B	0x61
#endif

struct mf_rfid_hal_arg {
	int CWGSP;				//0X30

	int RXTRESHOLD_B;		//0X5A
	int RFCFG_B;			//0X78
	int MODGSP_B;			//0X10

	int RXTRESHOLD_A;		//0X9A
	int RFCFG_A;			//0X78
};


int mf_rfid_init(void);
int mf_rfid_fini(void);

int mf_rfid_probe(void);

int mf_rfid_getuid(unsigned char *uid);

int mf_rfid_tcl_open(void);

int mf_rfid_tcl_close(void);

int mf_rfid_tcl_exchange(unsigned char *tbuf, unsigned short tlen, unsigned char **rbuf, unsigned short *rlen);

int mf_rfid_hal_config(struct mf_rfid_hal_arg *arg);

int mf_rfid_mfcl_open(void);
int mf_rfid_mfcl_close(void);
int mf_rfid_mfcl_atqa(void);
int mf_rfid_mfcl_setkey( unsigned char *key);
int mf_rfid_mfcl_auth(int cmd, int sector);
int mf_rfid_mfcl_read(int block, unsigned char *buf, int *len);
int mf_rfid_mfcl_write(int block, unsigned char *buf, int len);
int mf_rfid_mfcl_increment(int block, int operand);
int mf_rfid_mfcl_transfer(int block);
int mf_rfid_mfcl_restore(int block);
int mf_rfid_mfcl_decrement(int block, int operand);

int mf_rfid_rid_open(void);
int mf_rfid_rid_close(void);
int mf_rfid_rid_exchange(unsigned char *tbuf, unsigned short tlen, unsigned char **rbuf, unsigned short *rlen);


#ifdef __cplusplus
}
#endif

#endif /* __MF_SIMPLE_RFID_H */



