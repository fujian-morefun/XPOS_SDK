#ifndef _PUB_DEFINE_H_
#define _PUB_DEFINE_H_

#include<string.h> 
#include<ctype.h>  
//modified by zhiyu 0923
//#include<malloc.h>  
#include<limits.h>  
#include<stdio.h>   
#include<stdlib.h>  
#include<math.h>  
#include "pub/common/misc/inc/mfmalloc.h"
#include "pub_def.h"

//#include "struct_hashtable.h"
//#include "printfdebug.h"
//#include "ex_convert.h"
//#include "dev_file.h"
//#include "ErrorCode.h"
/**<api*/
#include "mf_basic.h"
//#include <mf_rild.h>
//#include <mf_mfd.h>


typedef unsigned char BYTE;

typedef enum
{
	mf_false = 0,
	mf_true = 1,
}mf_bool;
//typedef enum
//{
//	NO='0',
//	YES='1'
//}YESORNO;

#define MAXLEN_FILE		255
//#define MAXLEN_ICCRESP 512 
#define TABLESIZE(table)    (sizeof(table)/sizeof(table[0]))


#define FALSE 0
#define TRUE (!FALSE)


#define SUCC 0
#define FAIL (-1)
#define QUIT (-2)
#define TIMEOUT (-3)
#define GOTO (-4)





#define ASSERT_FAIL(e) \
	if ((e) == FAIL)\
	{\
		return FAIL;\
	}
	
#define ASSERT_QUIT(e) \
	if ((e) == QUIT)\
	{\
		return QUIT;\
	}
#define ASSERT_UNSUCC(e) \
    { int r = (e); if ((r) < SUCC)\
	{\
		return (r);\
	}}

#define EQ(a,b) ((a)==(b))  
#define LT(a,b) ((a)<(b))  
#define LQ(a,b) ((a)<=(b))


//#include "struct_tlv.h"


#endif