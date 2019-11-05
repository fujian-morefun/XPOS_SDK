/************************************************************************/
// Filename: QrEncode.h

// Describe£ºBrief description of CQR_Encode class functions and related definitions
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

//QrBarcode parameters
typedef PACKED struct QRParam
{
	int nVersion;		//version:1~40
	int nLevel;			//Error correction level: 0-low, 1-medium, 2-high, 3-highest.
	int moudleWidth;	//Module width (in units: pixels)
} Param_QR_INFO; 

LIB_EXPORT int mfGeneCodePic(char * chData, int iLen, Param_QR_INFO *QRParam , char * bitmap);
LIB_EXPORT void mfSetQrSize(int size);

#ifdef __cplusplus
}
#endif 

