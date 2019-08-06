#ifndef _ICC_OP_
#define _ICC_OP_

#include "define.h"
#include "emv_interface.h"

#define SELECT_FIRST 0x01
#define SELECT_NEXT 0x02
#define SELECT_ZIPMODE 0x08

typedef enum {
	AAC,
	ARQC,
	AAR,
	TC
}GenerateAC;


typedef enum{
	ATC,
	ATCResgister,
	PINTryCounter,
	LogFormat
}GetDataType;

LIB_EXPORT int Icc_External_Authenticate(const char *psData,int nDataLen);
LIB_EXPORT int Icc_Generate_AC(E_GAC genactype, YESORNO bCdaflag,const char *psData,int nDataLen, char * pszOut, int * nOutLen);
LIB_EXPORT int Icc_Verify(YESORNO IsEncypt,const char * pszPin,int nDataLen);
LIB_EXPORT int Icc_Read_Binary(char ucSFI,char *psResponse,int *pnDataLen);
LIB_EXPORT int Icc_Read_Record(const char cSfi,const char cRecordNo,char * psResponse,int *pnDataLen);
LIB_EXPORT int Icc_Get_Data(char *pszTag,char * psResponse,int *pnDataLen);
LIB_EXPORT int Icc_Get_Progress_Op(const char *psData,int nDataLen,char * psResponse,int *pnDataLen);
LIB_EXPORT int Icc_Internal_Auth(const char *psData,int nDataLen,char * psResponse,int *pnDataLen);
LIB_EXPORT int Icc_Select_Aid(int nMode,const char *sAid,int nAidLen,char *psResponse,int *pnDataLen);
LIB_EXPORT int Icc_Select_Directory(int nMode,const char *sAid,int nAidLen,char *psResponse,int *pnDataLen);
LIB_EXPORT int Icc_Get_Challence(char cLen,char *psResponse);
LIB_EXPORT int Icc_Get_BankCardInfo(char cRecordNo, char *psDateTime,char *psResponse, int *pnDataLen);
LIB_EXPORT int Icc_Put_Data(char *pszTag,const char *psData,int nDataLen,char * psResponse,int *pnDataLen);	//paypass新增
LIB_EXPORT int Icc_CCC_Comand(const char *psData,int nDataLen,char * psResponse,int *pnDataLen);			//paypass新增
LIB_EXPORT int Icc_RRP_Comand(const char *psData,char * psResponse,int *pnDataLen);							//paypass新增
LIB_EXPORT int Icc_Recover_AC(const char *psData,int nDataLen,char * psResponse,int *pnDataLen);			//paypass新增	
LIB_EXPORT int SendCmd(const unsigned char *pszCmd,int  nCmdLen,unsigned char *psOutBuf,int *pnOutDataLen);
LIB_EXPORT int Icc_Read_Record_Ex(const char cSfi,const char cRecordNo,char * psResponse,int *pnDataLen);	//rupay 2tap新增



#endif
