/************************************************************************/
// Filename: QrEncode.h

// Describe：简要描述CQR_Encode类的功能及相关定义
/************************************************************************/

#pragma once
#include "pub/pub.h"

#ifdef __cplusplus
extern "C"{
#endif 

#include "QrGlobalVar.h"

/************************************************************************/
#define		HorizontalDPI	600
#define		VerticalDPI		600

//Qr条码的参数
typedef PACKED struct QRParam
{
	int nVersion;		//版本号:1~40
	int nLevel;			//纠错级别:0-低,1-中,2-较高,3-最高,
	int moudleWidth;	//模块宽度（单位：像素）
} Param_QR_INFO; 

LIB_EXPORT int mfGeneCodePic(char * chData, int iLen, Param_QR_INFO *QRParam , char * bitmap);
LIB_EXPORT void mfSetQrSize(int size);

#ifdef __cplusplus
}
#endif 

