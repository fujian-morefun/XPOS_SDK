#ifndef __LIBAPI_UTIL_HEADER__
#define __LIBAPI_UTIL_HEADER__

#include "libapi_pub.h"

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.5.3	Get util module version(Util_GetModuleVer)
Input : Nothing
Output : pszVer   module version
return:  > 0 Successfully returns module version number length
		UUTIL_FAIL   =-1,           Fail
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int Util_GetModuleVer(char *pszVer);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: ASCII code to BCD code (Util_Asc2Bcd)
Input: AscBuf: ASCII code data to be converted
AscLen: incoming ASCII code data length
Output: BcdBuf: conversion output BCD code data
return: UUTIL_FAIL           = -1,       Fail
		UUTIL_SUCCESS        =  0			Success
Remarks: The left is BCD code, and the digit is insufficient to supplement'F'
*************************************************************************************/
LIB_EXPORT int Util_Asc2Bcd(char *AscBuf, char *BcdBuf, int AscLen);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: BCD code to ASCII code (Util_Bcd2Asc)
Input: BcdBuf: BCD code data to be converted
The length of AscLen:ASCII code data, that is, the double length of BCD code data.
Output: AscBuf: conversion output ASCII code data
return: UUTIL_FAIL           = -1,       Fail
		UUTIL_SUCCESS        =  0			Success
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int Util_Bcd2Asc(char *BcdBuf, char *AscBuf, int AscLen);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:  int data transfer to BCD code (Util_Int2Bcd)
Input: IntData: int data to be converted
BcdLen: length of BCD code data after conversion
Output: BcdBuf: BCD data after conversion
return: UUTIL_FAIL           = -1,       Fail
		UUTIL_SUCCESS        =  0			Success
Remarks: The BCD code is on the right, and the number is not enough to add 0 to the left.
*************************************************************************************/
LIB_EXPORT int Util_Int2Bcd(uint IntData, char *BcdBuf, int BcdLen);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: BCD code to int type (Util_Bcd2Int)
Input: BcdBuf: BCD data to be converted
BcdLen:BCD code data length
Output: IntData: int data after conversion
return: UUTIL_FAIL           = -1,       Fail
		UUTIL_SUCCESS        =  0			Success
 Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int Util_Bcd2Int(char *BcdBuf, uint *IntData, int BcdLen);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: calculates LRC (Util_GenLrc) and generates LRC parity bits (bitwise exclusive or).
Input: Data: data to be calculated for LRC check bits.
		DataLen: data length
Output: Nothing
return: The LRC check value generated by calculation
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT byte Util_GenLrc(char *Data, int DataLen);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:  DES encryption and decryption (Util_Des) to DES data encryption and decryption, 
		or 3DES encryption and decryption.
Input: bDesType: DES encryption and decryption algorithm: 
				0 denotes DES encryption, 
				1 denotes DES decryption, 
				2 denotes 3DES encryption, 
				3 denotes 3DES decryption.
	    Key: used for encryption and decryption of transmission keys, must be 8 times.
InData: encrypted data to be decrypted must be 8 bytes.
Output: OutData: the key after encryption and decryption must be 8 bytes.
return: UUTIL_FAIL           = -1,       Fail
		UUTIL_SUCCESS        =  0			Success
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int Util_Des(byte bDesType, char *Key, char *InData, char *OutData);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: Character Copy (Util_StrCopy)
Input : scr: source data string
		len: source data length
Output  Dst: target data string

return: the length of the copied string
Remarks: 
*************************************************************************************/
LIB_EXPORT int Util_StrCopy(char *dst, cchar *src, int len);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: Waiting button (Util_WaitKey) waits for the 
			button within the set time, while the Nothing button waits for the timeout.
Input : TimeOut:    Waiting timeout time (seconds), 0 means blocking.
Output : Nothing
return: key value.
		UUTIL_TIMEOUT
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int Util_WaitKey(int TimeOut);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.5.12	 input method input (Util_InputMethod) supports data input from input method switching.
Input : disp_line:     the number of rows displayed
		msgPrompt:     prompt information (left justified)
		input_line��   number of rows displayed in input data
		min:           minimum input length
		max:           maximum input length
		disp_pattern:  input data display position, 0 left alignment, 1 center; 2 right alignment
		timeout:       waiting for input timeout time (seconds)
Output : str:          input data
return: success: returns the str byte number of input data.
		UUTIL_TIMEOUT  = -3,    // input timeout
		UUTIL_CANCEL   = -2,    //input cancelled
		UUTIL_FAIL           = -1,    Fail
Remarks: Nothing
*************************************************************************************/
LIB_EXPORT int Util_InputMethod(int disp_line, char * msgPrompt, int input_line, char *str, int min, int max, byte disp_pattern, int timeout);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:2.2.5.13	string input (Util_InputText) number, child, password input
Input : disp_line:     the number of rows displayed
		msgPrompt:     prompt information (left justified)
		input_line��   number of rows displayed in input data
		min:           minimum input length
		max:           maximum input length
		disp_pattern:  input data display position, 0 left alignment, 1 center; 2 right alignment
		disp_mode��    input mode, 0 digit input; 1 digit, child input; 2 password input.
		timeout:       waiting for input timeout time (seconds)
Output : str:          input data
return: success: returns the str byte number of input data.
		UUTIL_TIMEOUT  = -3,    // input timeout
		UUTIL_CANCEL   = -2,    //input cancelled
		UUTIL_FAIL           = -1,    Fail
Remarks: When the input mode is numeric and alphabetic input, the switching between numeric,
		capitalized and lowercase letters is carried out by pressing a button continuously.
*************************************************************************************/
LIB_EXPORT int Util_InputText(int disp_line, char * msgPrompt, int input_line, char *str, int min, int max, int disp_pattern, byte disp_mode ,int timeout);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:	amount input��Util_InputAmount��
Input : disp_line:     the number of rows displayed
		msgPrompt:     prompt information (left justified)
		input_line��   number of rows displayed in input data
		disp_pattern:  input data display position, 0 left alignment, 1 center; 2 right alignment
		timeout:       waiting for input timeout time (seconds)
Output : amount��output amount
return: success: returns the str byte number of input data.
		UUTIL_TIMEOUT  = -3,    // input timeout
		UUTIL_CANCEL   = -2,    //input cancelled
		UUTIL_FAIL           = -1,    Fail
Remarks: The amount input is accurate to the score (two decimal points are reserved) 
		and the Amount variable is stored in the maximum 12-bit ASCII code.
*************************************************************************************/
LIB_EXPORT int Util_InputAmount(int disp_line, char * msgPrompt, int input_line, char *amount, byte disp_pattern, int timeout);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: IP  input��Util_InputIp��
Input : disp_line:     the number of rows displayed
		msgPrompt:     prompt information (left justified)
		input_line��   number of rows displayed in input data
		disp_pattern:  input data display position, 0 left alignment, 1 center; 2 right alignment
		timeout:       waiting for input timeout time (seconds)
Output : ip:           IP address
return: success: returns the str byte number of input data.
		UUTIL_TIMEOUT  = -3,    // input timeout
		UUTIL_CANCEL   = -2,    //input cancelled
		UUTIL_FAIL           = -1,    Fail
Remarks:  with IP address format to judge internally
*************************************************************************************/
LIB_EXPORT int Util_InputIp(int disp_line, char * msgPrompt, int input_line, char *ip, byte disp_pattern, int timeout);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: Buzz failure (Util_ErrorBeep) indicates buzz and obstruction during failure.
Input : num:  Buzz times
Output : Nothing
return: Nothing
Remarks:Nothing
*************************************************************************************/
LIB_EXPORT void Util_ErrorBeep(int num);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: Buzzing success (Util_Beep) indicates buzzing when successful, non blocking.
Input : num:    Buzz times
Output : Nothing
return: Nothing
Remarks:Nothing
*************************************************************************************/
LIB_EXPORT void Util_Beep(int num);
LIB_EXPORT void Util_BuzzerSound(int nMillisecond);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: Generating random numbers (Util_Rand)
Input : Nothing
Output : psRandom   8 byte Binary random number
return: UUTIL_FAIL           = -1,       Fail
		UUTIL_SUCCESS        =  0		Success
Remarks: Priority of true random numbers
*************************************************************************************/
LIB_EXPORT int Util_Rand(byte *psRandom);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:  Internal scanning gun scanning, obstruction
Input : maxlen maximum scan length
		timeout waiting for scan timeout time (seconds)
Output : BarCode Data scanned

return: UUTIL_TIMEOUT = -3,  
		  UUTIL_CANCEL = -2,  
	  	  UUTIL_FAIL = -1,  
		  UUTIL_SUCCESS = 0 Success
Remarks:  Support bar code and two-dimensional code scanning according to actual situation of terminal.
*************************************************************************************/
LIB_EXPORT int Util_ScanBarCode(char *BarCode, int maxlen, int timeout);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:  Open scan code dev
Input : 
Output : 
return: UUTIL_SUCCESS
	  	  UUTIL_FAIL = -1, Fail
		  UUTIL_SUCCESS = 0 Success
Remarks:  
*************************************************************************************/
LIB_EXPORT int Scan_Open(void);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions:  Close scan code dev
Input : 
Output : 
return: UUTIL_SUCCESS
	  	UUTIL_FAIL = -1, Fail
Remarks:  
*************************************************************************************/
LIB_EXPORT int Scan_Close(void);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: Voice Play
Input : msg  Audio file
Output : 
return: Nothing
Remarks:   Voice playback is non blocking.
*************************************************************************************/
LIB_EXPORT int Play_Voice(char *msg);


//QR code parameters
typedef struct _QRParam
{
	int nVersion;		//version number:1~40
	int nLevel;			//Error correction level: 0-low, 1-in, 2-high, 3-maximum,
	int moudleWidth;	//Module width (unit: pixel)
} Util_QR_INFO;
/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:LinZhu
Functions: QR code generation
Input : chData QR code data, iLen data length, qrparam QR code parameters
Output : bitmap Generated two-dimensional code dot matrix data
return: <=0 fail, >0 Successfully generated QR code width 
Remarks:   Voice playback is non blocking.
*************************************************************************************/
LIB_EXPORT int Util_GeneCodePic(char * chData, int iLen, Util_QR_INFO *qrparam , char * bitmap);

/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:yangjy
Functions: LED light control
Input : num LED light number(0 red, 1 blue, 2 yellow, 3 green), type LED light switch(0 close, 1 open)
Output : Nothing
return: Nothing
Remarks:   Voice playback is non blocking.
*************************************************************************************/
LIB_EXPORT void Util_Led(int num, int type);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:luoxizhu
Functions: Request memory
Input : size memory size
Output : Nothing
return: Application Memory Pointer
*************************************************************************************/
LIB_EXPORT void * Util_Malloc(int size);


/*************************************************************************************
Copyright: Fujian MoreFun Electronic Technology Co., Ltd.
Author:luoxizhu
Functions: Release memory
Input :A pointer to release memory
Output : Nothing
return: 
*************************************************************************************/
LIB_EXPORT void Util_Free( void * p);
LIB_EXPORT int Util_hzk_is_gbk_char(unsigned char *ch1);

LIB_EXPORT int Util_SHA1(const byte *psSrc, uint nSrcLen, byte *psDst);

#endif /*__LIBAPI_UTIL_HEADER__*/
