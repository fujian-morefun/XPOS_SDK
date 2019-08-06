#pragma once

#include "driver/mf_icc.h"
#include "pub/pub.h"

typedef enum
{
	DEV_ICC_ICCID = ICC_SOCKET1,  //读卡器
	DEV_ICC_PSAM1 = ICC_SOCKET2,  //pasm1
	DEV_ICC_PSAM2 = ICC_SOCKET3	  //pasm2
}ICC_TYPE;


/**
* iccid,psam1,psam2读取接口
* @param type[IN]: 参见上面
* @param psaIcc[OUT]: 读取到的数据缓冲区
* @param return: 
* -1: 设备打开失败
* -2: 卡在位检测失败
* -3: 上电失败
* -4: sim卡里文件选择错误
* -5: 读取数据错误
*/
LIB_EXPORT int osl_ReadIcc(ICC_TYPE type, char *pszIcc);	

