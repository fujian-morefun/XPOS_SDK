#pragma once

#include "pub/pub.h"


#ifdef __cplusplus
extern "C" {
#endif

// 取两个数值的最小值
#define POS_MIN(x,y) ((x)<(y)?(x):(y))

/**********************************************
*函数功能描述:
*    计算两个串的异或结果
*参数说明
*    输入:  str1,str2 源串， 
*           len  源串长度(要异或的字节数)
*    输出:  dest 异或结果串
*返回值:
*    结果串的长度
*修改记录:
*    2011-09-20    sulanhxl     创建
**********************************************/
LIB_EXPORT int AcuXor(unsigned char *str1, unsigned char *str2, int len, unsigned char *dest);

/**********************************************
*函数功能描述:
*    将N个字节的串转换成2*N个字节的HEX串
*参数说明
*    输入:  str  源字节串， 
*           len  源串长度
*    输出:  psHex 转换后的2*len个字节的HEXDECIMAL
*返回值:
*    结果串的长度
*修改记录:
*    2011-09-20    sulanhxl     创建
**********************************************/
LIB_EXPORT int SplitStrToHexDecimal(unsigned char *str, int len , unsigned char *psHex);

/**********************************************
*函数功能描述:
*    将用户输入的金额串转换成ISO8583报文要求的12字节数字串
*参数说明
*    输入:  str  源字节串， 
*           len  源串长度
*    输出:  psDest 转换后12字节数字串
*返回值:
*    输出串的长度，正确的话应该为12
*修改记录:
*    2011-09-20    sulanhxl     创建
**********************************************/
LIB_EXPORT int AmoutStrToMsgfieldstr(char *str, int len, char *psDest);

/**********************************************
*函数功能描述:
*    将整数数值转换成ISO8583报文要求的指定长度的串
*    如果len<实际长度，则按实际长度输出
*参数说明
*    输入:  str  源整数数值 
*           len  指定要转换的串长度(len <= 9)
*    输出:  psDest 转换后的数字串
*返回值:
*    无
*修改记录:
*    2011-09-21    sulanhxl     创建
**********************************************/
LIB_EXPORT void IntToFixedStr(int nNum, int len, char *psDest);

/**********************************************
*函数功能描述:
*    将ISO8583报文要求的指定长度的串转换成整数数值
*参数说明
*    输入:  psStr  源整数数值串(如:000123) 
*           len    串长度(len <= 9)
*    输出:   
*返回值:
*    转换后的整型数值
*修改记录:
*    2011-09-21    sulanhxl     创建
**********************************************/
LIB_EXPORT int FixedStrtoInt(int len, char *psStr);

/**********************************************
*函数功能描述:
*    字符串的BCD压缩转换
*    左靠方式:"12345"转换成{0x01,0x23,0x45}
*    右靠方式:"12345"转换成{0x12,0x34,0x50}
*参数说明
*    输入:  str  源字符串值 
*           len  指定要转换的串长度
*           Align 对齐方式，0无需对齐，1左靠，2右靠
*    输出:  psDest 转换后的BCD串
*返回值:
*    转换后的BCD串的长度
*修改记录:
*    2011-09-22    sulanhxl     创建
**********************************************/
LIB_EXPORT int StrToBcd(char *str, int len, int Align, char *psDest);

/**********************************************
*函数功能描述:
*    4字节的数字串转换成整型
*参数说明
*    输入:  str  要转换的源串 
*    输出: 
*返回值:
*    转换后的整型值
*修改记录:
*    2011-09-29    sulanhxl     创建
**********************************************/
//int Char4ToInt(unsigned char* str);

/**********************************************
*函数功能描述:
*    字符串的BCD解压缩转换
*    右靠方式:{0x01,0x23,0x45}转换成"12345"
*    左靠方式:{0x12,0x34,0x50}转换成"12345"
*参数说明
*    输入:  Bcd  要转换的BCD源串 
*           len  指定要转换的BCD串长度
*           Align 对齐方式，0无需对齐，1左靠，2右靠，默认左靠
*    输出:  psDest 转换后的串
*返回值:
*    转换后的串的长度
*修改记录:
*    2011-09-22    sulanhxl     创建
**********************************************/
LIB_EXPORT int BcsToStr(char *Bcd, int len, int Align, char *psDest);

/**********************************************
*函数功能描述:
*    将12字节金额串转换成金额数值
*参数说明
*    输入:  str  源字节串， 
*           len  源串长度
*    输出:  
*返回值:
*    金额值(分)
*修改记录:
*    2011-10-17    sulanhxl     创建
**********************************************/
LIB_EXPORT long long AmoutStrToLongint(char *str, int len);

/**********************************************
*函数功能描述:
*    将金额数值转换成12字节金额串
*参数说明
*    输入:  nAmount  金额数值 
*           
*    输出:  str  转换后的12字节串 
*返回值:
*    长度12
*修改记录:
*    2011-10-17    sulanhxl     创建
**********************************************/
LIB_EXPORT int LongintToAmoutStr(char *str, long long nAmount);

/**********************************************
*函数功能描述:
*    查找一个串中的某个字符并将其替换为指定的字符
*参数说明
*    输入:  str 字符串
            cX  在串中要找的字符 
*           cY  用于替换cX的字符
*    输出:   
*返回值:
*    1找到并替换  0未找到
*修改记录:
*    2011-10-18    sulanhxl     创建
**********************************************/
LIB_EXPORT int FindAndReplaceCharXByCharY(char *str, char cX, char cY);

/**********************************************
*函数功能描述:
*    查找一个串中的某个字节串
*参数说明
*    输入:  
*    输出:   
*返回值:
*    1找到并替换  0未找到
*修改记录:
*    2011-10-18    sulanhxl     创建
**********************************************/
LIB_EXPORT int FindStrInString(char *string, int strlen, char *cstr, int clen);

/**********************************************
*函数功能描述:
*    将一串后补空格的数字串去掉空格
*参数说明
*    输入:  psStr  源数值串
*           len    串长度
*    输出:  psDest 处理后的串
*返回值:
*    处理后的串长度
*修改记录:
*    2011-09-21    sulanhxl     创建
**********************************************/
LIB_EXPORT int ClearSpaceOfStr(int len, char *psStr, char *psDest);

//YESORNO IsDigitStr(const char *pStr);
/*获取字符在字符串中的位置*/
LIB_EXPORT int get_char_num(char *str,char ch);
/************************************************************************/
/*                                                                      */
/************************************************************************/
//YESORNO ValidateIP(char *pIP);
/************************************************************************/
/* 检查端口是否有效                                                                      */
/************************************************************************/
//YESORNO ValidatePort(char *pszPort);
/*-----------------------------------------------------------------------------
函数原型：  
函数功能：将char 转换为UTP
输入参数：
返 回 值：
使用说明：在收到短息时，将两个字符转为一个字符 例：34 转为 0x34,即字符4
-------------------------------------------------------------------------------*/
LIB_EXPORT char UncodeUTP(char * src);
/*-----------------------------------------------------------------------------
函数原型：  
函数功能：将接受到的字符串 转换成UTP编码
输入参数：
返 回 值：
使用说明：(一整串进行转换)
-------------------------------------------------------------------------------*/
LIB_EXPORT int UCOS_to_UTP(char * src,char * des,int Size);
/*设置时间*/
LIB_EXPORT int SetTimeChar(char * cSetTime);
LIB_EXPORT int IntToChar_4(char * cDamonSize,int nLen);
/*-----------------------------------------------------------------------------
函数原型：  
函数功能：
输入参数：
返 回 值：
使用说明: 将字符型转为整形
-------------------------------------------------------------------------------*/
LIB_EXPORT long long IntervorCharToInt(char *cEditDataBuff);
/******************************************************************************
 *  函数名称:	BCD2ASC: 
 *	函数介绍:	BCD码转为ASC码
 *	入口参数:	
 *	出口参数:     
 * 	返回值  :		
 ******************************************************************************/
LIB_EXPORT int BCD2ASC(char *ascstr, const unsigned char *bcd, int len, int align);
LIB_EXPORT int ConvetAmoutToDis(char * szSource, char * szDes);
LIB_EXPORT void DisAmouont(char *cInAmount,int nLen, char * cOutMount);
//获取配置文件路径
LIB_EXPORT char *MFPos_GetFilePath(char *pFilePath);

/**********************************************
*函数功能描述:
*    设置POS系统时间
*参数说明
*    输入:  psTimeStr  时间串 格式:YYYYMMDDHHMMSS            
*    输出:  
*返回值:
*    成功1 ，失败0
*修改记录:
*    2011-11-25    sulanhxl     创建
**********************************************/
LIB_EXPORT int MFPosSetSysTime(char *psTimeStr);
/**********************************************
*函数功能描述:
*    字符串左补'0'
*参数说明
*    输入:  str         输入字符串
*           len         填充长度标准
*           
*    输出:  psDest      输出字符串
*返回值:
*    成功0 ，失败-1
*修改记录:
*    2011-12-06    chenqy     创建
**********************************************/
LIB_EXPORT int MFPos_FillStrZero(char *str, int len, char *psDest);
/**********************************************
*函数功能描述:
*    字符串中插入分隔符
*参数说明
*    输入:  str         输入字符串
*           cchar       插入的字符
*           nPos        插入位置
*    输出:  psDest      输出字符串
*返回值:
*    成功0 ，失败-1
*修改记录:
*    2011-12-06    chenqy     创建
**********************************************/
LIB_EXPORT int MFPos_InsertSeprite(char *str, int nPos,char cchar, char *psDest);
/**********************************************************************
* 函数名称: MFpos_Publicstrim
*
* 功能描述: 去空格
***********************************************************************/
LIB_EXPORT char *MFpos_Publicstrim(char *str);
/**********************************************
*函数功能描述:
*    字符串左补空格
*参数说明
*    输入:  str         输入字符串
*           len         填充长度标准
*           
*    输出:  psDest      输出字符串
*返回值:
*    成功0 ，失败-1
*修改记录:
*    2011-12-13    chenqy     创建
**********************************************/
LIB_EXPORT int MFPos_FillStrim(char *str, int len, char *psDest);


LIB_EXPORT int ConvertTimeFormat(char *szTime);

//LIB_EXPORT int Ex_File_GetParam(char *pszFileName,char *pszOutData, int nOff, int nLen);
//LIB_EXPORT void DebugPrintBuf(char *pszTitle,char *pszBuf,int nLen);
//LIB_EXPORT int Ex_Get_Public_ErrCode();

LIB_EXPORT int mf_TLV_GetDataByTag(unsigned char *psTag, unsigned char *psSrc, int nSrcLen,unsigned char *psBuf, int *nBufLen);


#ifdef __cplusplus
}
#endif

