#pragma once

#include "pub/pub.h"


#ifdef __cplusplus
extern "C" {
#endif

// Take the minimum of two values
#define POS_MIN(x,y) ((x)<(y)?(x):(y))

/**********************************************
*Functional description:
*    Computing XOR results of two strings
*Description of parameters
*    input:  str1,str2 Source string 
*           len  Source string length (number of bytes to XOR)
*    output:  dest XOR result string
*Return value:
*    Length of result string
*Modification of records:
*    2011-09-20    sulanhxl     create
**********************************************/
LIB_EXPORT int AcuXor(unsigned char *str1, unsigned char *str2, int len, unsigned char *dest);

/**********************************************
*Functional description:
*   Converting N byte strings to 2*N byte HEX strings
*Description of parameters
*    input:  str  Source byte string
*           len  Source string length
*    output:  psHex Converted 2*len bytes of HEDECIMAL
*Return value:
*    Length of result string
*Modification of records:
*    2011-09-20    sulanhxl     create
**********************************************/
LIB_EXPORT int SplitStrToHexDecimal(unsigned char *str, int len , unsigned char *psHex);

/**********************************************
*Functional description:
*    Converting the amount string input by the user into the 12-byte digital string required by ISO8583 message
*Description of parameters
*    input:  str   Source byte string£¬ 
*           len   Source string length
*    output:  psDest 12-byte digit string after conversion
*Return value:
*    The length of the output string, if correct, should be 12
*Modification of records:
*    2011-09-20    sulanhxl     create
**********************************************/
LIB_EXPORT int AmoutStrToMsgfieldstr(char *str, int len, char *psDest);

/**********************************************
*Functional description:
*    Converting integer values to specified length strings required by ISO8583 messages
*    If len < actual length, output according to actual length
*Description of parameters
*    input:  str Source integer values
*           len  Specify the length of the string to be converted(len <= 9)
*    output:  psDest Converted digital string
*Return value:
*    none
*Modification of records:
*    2011-09-20    sulanhxl     create
**********************************************/
LIB_EXPORT void IntToFixedStr(int nNum, int len, char *psDest);

/**********************************************
*Functional description:
*    Converts the specified length string required by ISO8583 message to an integer value
*Description of parameters
*    input:  psStr  Source integer numeric string(Èç:000123) 
*           len    String Length(len <= 9)
*    output:   
*Return value:
*    Converted integer values
*Modification of records:
*    2011-09-20    sulanhxl     create
**********************************************/
LIB_EXPORT int FixedStrtoInt(int len, char *psStr);

/**********************************************
*Functional description:
*   BCD Compression Conversion of Strings
*   Left-leaning: "12345" converts to {0x01, 0x23, 0x45}
*   Right-leaning: "12345" converts to {0x12, 0x34, 0x50}
*Description of parameters
*    input:  str  Source string value 
*           len  Specify the length of the string to be converted
*           Align Alignment, 0 need not align, 1 left, 2 right
*    output:  psDest Converted BCD Strings
*Return value:
*   Length of converted BCD string
*Modification of records:
*    2011-09-20    sulanhxl     create
**********************************************/
LIB_EXPORT int StrToBcd(char *str, int len, int Align, char *psDest);

/**********************************************
*Functional description:
*    4-byte digit string converted to integer
*Description of parameters
*    input:  str  Source string to be converted 
*    output: 
*Return value:
*    Converted integer values
*Modification of records:
*    2011-09-20    sulanhxl     create
**********************************************/
//int Char4ToInt(unsigned char* str);

/**********************************************
*Functional description:
*   BCD Decompression Conversion of Strings
*    Right-leaning mode: {0x01, 0x23, 0x45} converted to "12345"
*   Left-leaning mode: {0x12,0x34,0x50} converted to "12345"
*Description of parameters
*    input:  Bcd  BCD source string to be converted
*           len  Specify the length of the BCD string to be converted
*         Align alignment, 0 need not align, 1 left, 2 right, default left
*    output:  psDest Converted string
*Return value:
*    The length of the converted String
*Modification of records:
*    2011-09-20    sulanhxl     create
**********************************************/
LIB_EXPORT int BcsToStr(char *Bcd, int len, int Align, char *psDest);

/**********************************************
*Functional description:
*    Converting a 12-byte amount string to a value of the amount
*Description of parameters
*    input:  str  Source byte string£¬ 
*           len  Source string length
*    output:  
*Return value:
*   Value of amount (points)
*Modification of records:
*    2011-09-20    sulanhxl     create
**********************************************/
LIB_EXPORT long long AmoutStrToLongint(char *str, int len);

/**********************************************
*Functional description:
*    Convert the amount value to a 12-byte amount string
*Description of parameters
*    input:  nAmount  Value of amount 
*           
*    output:  str Converted 12-byte string
*Return value:
*    length 12
*Modification of records:
*    2011-09-20    sulanhxl     create
**********************************************/
LIB_EXPORT int LongintToAmoutStr(char *str, long long nAmount);

/**********************************************
*Functional description:
*    Find a character in a string and replace it with the specified character
*Description of parameters
*    input:  str Character string
            cX  Characters to be found in a string 
*           cY  Characters used to replace cX
*    output:   
*Return value:
*   1 Find and replace 0 not found
*Modification of records:
*    2011-09-20    sulanhxl     create
**********************************************/
LIB_EXPORT int FindAndReplaceCharXByCharY(char *str, char cX, char cY);

/**********************************************
*Functional description:
*    Find a byte string in a string
*Description of parameters
*    input:  
*    output:   
*Return value:
*   Find a byte string in a string
*Modification of records:
*    2011-09-20    sulanhxl     create
**********************************************/
LIB_EXPORT int FindStrInString(char *string, int strlen, char *cstr, int clen);

/**********************************************
*Functional description:
*    Remove the space from a string of digits that are backfilled with space
*Description of parameters
*    input:  psStr  Source numeric string
*           len   String Length
*    output:  psDest Processed string
*Return value:
*    Processed string length
*Modification of records:
*    2011-09-20    sulanhxl     create
**********************************************/
LIB_EXPORT int ClearSpaceOfStr(int len, char *psStr, char *psDest);

//YESORNO IsDigitStr(const char *pStr);
/* Gets the position of a character in a string*/
LIB_EXPORT int get_char_num(char *str,char ch);
/************************************************************************/
/*                                                                      */
/************************************************************************/
//YESORNO ValidateIP(char *pIP);
/************************************************************************/
/* Check whether the port is valid                                                                 */
/************************************************************************/
//YESORNO ValidatePort(char *pszPort);
/*-----------------------------------------------------------------------------
Function prototyp:
Function function: Convert char to UTP
Input parameters:
Return value:
Instructions: When receiving a short message, convert two characters into one character example: 34 to 0x34, that is, character 4
-------------------------------------------------------------------------------*/
LIB_EXPORT char UncodeUTP(char * src);
/*-----------------------------------------------------------------------------
Function prototype:
Function Function: Convert the received string into UTP encoding
Input parameters:
Return value:
Instructions for use: (a whole string of conversions)
-------------------------------------------------------------------------------*/
LIB_EXPORT int UCOS_to_UTP(char * src,char * des,int Size);
/*set time*/
LIB_EXPORT int SetTimeChar(char * cSetTime);
LIB_EXPORT int IntToChar_4(char * cDamonSize,int nLen);
/*-----------------------------------------------------------------------------
Function prototype:
Functional functions:
Input:
Return value:
Instructions for Use: Convert Character Type to Shaping
-------------------------------------------------------------------------------*/
LIB_EXPORT long long IntervorCharToInt(char *cEditDataBuff);
/******************************************************************************
* Function name: BCD2ASC:
* Function Introduction: BCD Code to ASC Code
* Entry parameters:
* Export parameters:
* Return value:	
 ******************************************************************************/
LIB_EXPORT int BCD2ASC(char *ascstr, const unsigned char *bcd, int len, int align);
LIB_EXPORT int ConvetAmoutToDis(char * szSource, char * szDes);
LIB_EXPORT void DisAmouont(char *cInAmount,int nLen, char * cOutMount);
//Get the profile path
LIB_EXPORT char *MFPos_GetFilePath(char *pFilePath);

/**********************************************
*Functional description:
*    Setting POS System Time
*Description of parameters
*    input:  psTimeStr Time String Format:YYYYMMDDHHMMSS            
*    output:  
*Return value:
*   Success 1, Failure 0
*Modification of records:
*    2011-09-20    sulanhxl     create
**********************************************/
LIB_EXPORT int MFPosSetSysTime(char *psTimeStr);
/**********************************************
*Functional description:
*    Left complement of string'0'
*Description of parameters
*    input:  str         Input string
*           len         Filling length standard
*           
*    output:  psDest      Output string
*Return value:
*   Success 0, Failure - 1
*Modification of records:
*    2011-09-20    sulanhxl     create
**********************************************/
LIB_EXPORT int MFPos_FillStrZero(char *str, int len, char *psDest);
/**********************************************
*Functional description:
*   Insert separators in strings
*Description of parameters
*    input:  str        Input string
*           cchar      Input char
*           nPos        Insertion position
*    output:  psDest      Output string
*Return value:
*    Success 0, Failure - 1
*Modification of records:
*    2011-09-20    sulanhxl     create
**********************************************/
LIB_EXPORT int MFPos_InsertSeprite(char *str, int nPos,char cchar, char *psDest);
/**********************************************************************
* Function name: MFpos_Publicstrim
*
* Function Description: Despace
***********************************************************************/
LIB_EXPORT char *MFpos_Publicstrim(char *str);
/**********************************************
*Functional description:
*    Left complement space of string
*Description of parameters
*    input:  str       Input string
*           len         Filling length standard
*           
*    output:  psDest      Output string
*Return value:
*    Success 0, Failure - 1

*Modification of records:
*    2011-09-20    sulanhxl     create
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

