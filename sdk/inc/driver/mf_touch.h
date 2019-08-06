/* 
 * Copyright (c) 2012 MoreFun
 *
 * @date 2012-3-6
 * @author ZhaoJinYun
 *
*/

#ifndef __MF_TOUCH_H
#define __MF_TOUCH_H

#ifdef __cplusplus
extern "C" {
#endif

#define CONFIG_TS_MAX_POINTS		(5)

struct mf_ts_sample {
	int		x;
	int		y;
	unsigned int pressure;
	unsigned int timeval;
};

struct mf_ts_raw_sample {
	unsigned char data[3 + 6 * CONFIG_TS_MAX_POINTS];
};

int mf_ts_init(void);
int mf_ts_read(struct mf_ts_sample *samp);
int mf_ts_flush(void);

int mf_ts_read_raw(struct mf_ts_raw_sample *sample);

int mf_ts_probe(void);

#ifdef __cplusplus
}
#endif

#endif /* __MF_TOUCH_H*/


