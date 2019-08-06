/* 
 * Copyright (c) 2015 MoreFun
 *
 * @date 2015-3-16
 * @author ZhaoJinYun
 *
*/

#ifndef __MF_AUDIO_RAW_H
#define __MF_AUDIO_RAW_H


#ifdef __cplusplus
extern "C" {
#endif

int mf_audio_raw_init(void);

int mf_audio_raw_write(unsigned char *buf, int size);
int mf_audio_raw_read(unsigned char *buf, int size);

void mf_audio_raw_flush(void);
int mf_audio_raw_data_avail(int *txlen, int *rxlen);

struct mf_audio_tx_config {
	int sync_clock;
	int txmax;
	int amplitude;
	int r47;
};

int mf_audio_set_txconfig(struct mf_audio_tx_config *config);

#ifdef __cplusplus
}
#endif

#endif /* __MF_AUDIO_RAW_H */
