/* 
 * Copyright (c) 2015 MoreFun
 *
 * @date 2015-01-20
 * @author ZhaoJinYun
 *
*/

#ifndef __BITMAP_H
#define __BITMAP_H


#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif

#define BITS_PER_LONG 32
#define	DIV_ROUND_UP(x,y)	(((x) + ((y) - 1)) / (y))
#define BIT(nr)			(1UL << (nr))
#define BIT_MASK(nr)		(1UL << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr)		((nr) / BITS_PER_LONG)
#define BITS_PER_BYTE		8
#define BITS_TO_LONGS(nr)	DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))



#define BITMAP_LAST_WORD_MASK(nbits)					\
(									\
	((nbits) % BITS_PER_LONG) ?					\
		(1UL<<((nbits) % BITS_PER_LONG))-1 : ~0UL		\
)

static inline void bitmap_zero(unsigned long *dst, int nbits)
{
	if (nbits <= BITS_PER_LONG)
		*dst = 0UL;
	else {
		int len = BITS_TO_LONGS(nbits) * sizeof(unsigned long);
		memset(dst, 0, len);
	}
}
static inline int test_bit(unsigned int nr, const unsigned long *addr)
{
	return ((1UL << (nr % BITS_PER_LONG)) &
		(((unsigned long *)addr)[nr / BITS_PER_LONG])) != 0;
}


#define DECLARE_BITMAP(name,bits) \
	unsigned long name[BITS_TO_LONGS(bits)]


void bitmap_set(unsigned long *map, int start, int nr);
void bitmap_clear(unsigned long *map, int start, int nr);
unsigned long find_first_bit(const unsigned long *addr, unsigned long size);

unsigned long find_next_bit(const unsigned long *addr, unsigned long size,
			    unsigned long offset);



#ifdef __cplusplus
}
#endif


#endif /* __BITMAP_H */

