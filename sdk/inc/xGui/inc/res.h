#ifndef _RES_H_
#define _RES_H_
#include "xgui_pub.h"

typedef struct _gui_res{
	int nResType;	//资源类型
	int nWidth;		//资源宽度
	int nHeight;	//资源高度
	int nID;		//资源ID
	unsigned char *pData;//资源数据
} GUIRES;

struct _guires_list{
	GUIRES * pGuiRes;
	struct _guires_list * pNext;
	struct _guires_list * pPrev;
	int nPosX;
	int nPosY;
	int nDrawMode;
};

#define  RES_TYPE_IMAGE		0x01
#define  RES_TYPE_TEXT		0x02
#define  RES_TYPE_SOUND		0x03
#define  RES_TYPE_VIDEO		0x04
#define  RES_TYPE_BWIMAGE   0x05


#endif
