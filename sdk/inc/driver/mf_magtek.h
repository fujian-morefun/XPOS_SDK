/* 
 * Copyright (c) 2015 MoreFun
 *
 * @date 2015-3-6
 * @author ZhaoJinYun
 *
*/

#ifndef __MF_MAGTEK_H
#define __MF_MAGTEK_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAGTEK_TRACK_7BIT_MAX_CHARS		(100)
#define MAGTEK_TRACK_5BIT_MAX_CHARS		(140)
#define MAGTEK_TRACK_BUFFER_BITS		(704)

struct magtek_track_a_chars {
	unsigned char chars[MAGTEK_TRACK_7BIT_MAX_CHARS];
};

struct magtek_track_b_chars {
	unsigned char chars[MAGTEK_TRACK_5BIT_MAX_CHARS];
};

struct magtek_track_c_chars {
	unsigned char chars[MAGTEK_TRACK_5BIT_MAX_CHARS];
};

struct magtek_track_info {
	struct magtek_track_a_chars a_chars;
	struct magtek_track_b_chars b_chars;
	struct magtek_track_c_chars c_chars;
};


int mf_magtek_init(void);

int mf_magtek_read(struct magtek_track_info *info);

int mf_magtek_flush(void);

int mf_magtek_swipe_timeout(int ms);

int mf_magtek_event_sync(int (*sync)(int code));


enum {
	MF_MAGNETIC_CARD_NORMAL,
	MF_MAGNETIC_CARD_SEC,
};

void mf_magtek_select(int type);


#ifdef __cplusplus
}
#endif

#endif /* __MF_MAGTEK_H */


