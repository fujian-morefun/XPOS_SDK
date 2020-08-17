#ifndef _MF_STRIPEREADER_H_
#define _MF_STRIPEREADER_H_

#ifdef __cplusplus
extern "C" {
#endif

int mf_stripe_reader_init(void);
int mf_stripe_reader_swipe_card(unsigned char *bitbuf, unsigned int timeout_ms);

#ifdef __cplusplus
}
#endif

#endif /* __MF_STRIPEREADER_H */

