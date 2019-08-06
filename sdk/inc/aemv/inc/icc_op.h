#ifndef _ICC_OP_
#define _ICC_OP_

#define SELECT_FIRST 0x01
#define SELECT_NEXT 0x02
#define SELECT_ZIPMODE 0x08

#include <define.h>

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

extern int Icc_External_Authenticate(const char *psData,int nDataLen);
extern int Icc_Generate_AC(E_GAC genactype, YESORNO bCdaflag,const char *psData,int nDataLen, char * pszOut, int * nOutLen);
extern int Icc_Verify(YESORNO IsEncypt,const char * pszPin,int nDataLen);
extern int Icc_Read_Binary(char ucSFI,char *psResponse,int *pnDataLen);
extern int Icc_Read_Record(const char cSfi,const char cRecordNo,char * psResponse,int *pnDataLen);
extern int Icc_Get_Data(char *pszTag,char * psResponse,int *pnDataLen);
extern int Icc_Get_Progress_Op(const char *psData,int nDataLen,char * psResponse,int *pnDataLen);
extern int Icc_Internal_Auth(const char *psData,int nDataLen,char * psResponse,int *pnDataLen);
extern int Icc_Select_Aid(int nMode,const char *sAid,int nAidLen,char *psResponse,int *pnDataLen);
extern int Icc_Select_Directory(int nMode,const char *sAid,int nAidLen,char *psResponse,int *pnDataLen);
extern int Icc_Get_Challence(char cLen,char *psResponse);
extern int Icc_Get_BankCardInfo(char cRecordNo, char *psDateTime,char *psResponse, int *pnDataLen);
extern int Icc_Put_Data(char *pszTag,const char *psData,int nDataLen,char * psResponse,int *pnDataLen);	//paypass新增
extern int Icc_CCC_Comand(const char *psData,int nDataLen,char * psResponse,int *pnDataLen);			//paypass新增
extern int Icc_RRP_Comand(const char *psData,char * psResponse,int *pnDataLen);							//paypass新增
extern int Icc_Recover_AC(const char *psData,int nDataLen,char * psResponse,int *pnDataLen);			//paypass新增	
extern int SendCmd(const unsigned char *pszCmd,int  nCmdLen,unsigned char *psOutBuf,int *pnOutDataLen);



#endif
