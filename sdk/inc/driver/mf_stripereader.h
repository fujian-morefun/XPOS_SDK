/* 
 * Copyright (c) 2015 MoreFun
 *
 * @date 2015-03-16
 * @author ZhaoJinYun
 *
*/

#ifndef __MF_STRIPEREADER_H
#define __MF_STRIPEREADER_H

#ifdef __cplusplus
extern "C" {
#endif

int mf_stripe_reader_init(void);
int mf_stripe_reader_swipe_card(unsigned char *bitbuf, unsigned int timeout_ms);

#ifdef __cplusplus
}
#endif

#endif /* __MF_STRIPEREADER_H */

