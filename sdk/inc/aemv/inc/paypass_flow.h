#ifndef __RF_PAYPASS_FLOW__
#define __RF_PAYPASS_FLOW__


#include "emv_interface.h"
#include "paypass_rrp.h"

/**

**与赵进云协调,L1超时错误码暂定-2,后面配合修改
*/
#define PP_ERR_L1_TIME_OUT	-2

/*******************PAYPASS内部返码*****************************************************/
#define PP_LOCAL_SUCC	0
#define PP_LOCAL_FAIL	1
#define PP_LOCAL_NEXT_FLOW	2


#define PP_BALANCE_PRE_GAC1		0
#define PP_BALANCE_POST_GAC1	1
#define PP_PRE_PUT_DATA			2
#define PP_POST_PUT_DATA		3

/* 错误信息索引*/
typedef struct
{
	uchar ucL1;       // L1层错误，参考宏定义:错误类型定位标识
	uchar ucL2;       // L2层错误，参考宏定义:错误类型定位标识
	uchar ucL3;       // L3层错误，参考宏定义:错误类型定位标识
	uchar ucMsgID;    // Message ID，参考宏定义:信息标识 Message ID
	ushort usSW12;    // APDU卡片返回状态码
}PP_tErrorID;

//数据结构体
typedef struct
{
	uchar auData[512];
	uint uiDataLen;
}PP_tTLVString;

//闪开数据结构体
typedef struct
{
	uchar auData[512+1024];	//针对案例3M50-0111闪开记录 1045
	uint uiDataLen;
}PP_TORN_tTLVString;

//IDS状态
typedef enum {
	IDS_NULL,
	IDS_READ,
	IDS_WRITE,
}PP_DE_IDS_STATUS;

//IDS状态
typedef enum {
	IDS_SUMMARY_NULL,
	IDS_SUMMARY_READ,
	IDS_SUMMARY_WRITE,
}PP_DE_IDS_SUMMARY_STATUS;

//DS ODS Info For Reader 信息
typedef enum {
	USE_FOR_TC,
	USE_FOR_ARQC,
	USE_FOR_AAC,
	STOP_NO_DS_ODS_TERM,
	STOP_WRITE_FAILED
}PP_DE_DS_ODS_INFO_READER;

typedef struct
{
	uchar ucPANLen;
	char  szPAN[20];    // 主账户
	char szExpiry[5];  // 有效期
	char szService[4]; // 服务码
	uchar ucDDLen;      // discretionary data Length
	uchar auDData[56];  // discretionary data
	int nPUNATC;      // PUNATC 中非0位的个数
	int nPCVC3;       // PCVC3  中非0位的个数
	int nATC;         // ATC 中非0位的个数
	uchar nUN;          // UN    nPUNATC-nATC
	uchar ucPCVC3_S;    // Start Point of bit 1  从低位到高位,首次出现Bit'1'的位置
	uchar ucPCVC3_E;    // End Point of bit 1 从低位到高位,最后出现Bit'1'的位置
	uchar auBitMap_PCVC3[48];//第i字节的值代表PCVC3非0位在PCVC中的排序
	uchar ucPUNATC_S;   // Start Point of bit 1从低位到高位,首次出现Bit'1'的位置
	uchar ucPUNATC_E;   // End Point of bit 1 从低位到高位,最后出现Bit'1'的位置
	uchar auBitMap_PUNATC[48];//第i字节的值代表PUNATC非0位在PUNATC中的排序
}PayPass_tTrackData;

typedef struct
{
	unsigned long long  ulTranLimit;		//交易限额
	unsigned long long  ulTranAmount;		//交易金额
	uchar ucOPS[8];							//Outcome Parameter Set
	uchar ucUIRD[22];						//User Interface Request Data
	uchar ucTempUIRD[22];					//User Interface Request Data Temp
	int PP_iCurrentTranMode;				//当前交易模式
	ulong ulMeasureTime;					//RRP MeasureTime
	PP_tErrorID stErrorID;					//M_TAG_DF8115_TM_ERR_INDI 错误信息结构体 
	uchar auMsgHoldTime[3];					//Hold Time Value default:\x00\x00\x13
	uchar ucIsSupportIds;					//是否支持Ids
	uchar ucIDS_Status;						//IDS Status
	uchar ucDSSummaryStatus;				//DS Summary Status
	uchar ucPreGacPutDataStatus;			//Pre gac put data status
	uchar ucPostGacPutDataStatus;			//Post gac put data status
	uchar ucIsExecPutdataApdu;				//判断是否执行putdata操作
	uchar ucIsExecPutDataPost;				//判断是否执行post putdata操作
	uchar ucODAStatus;
	uchar ucGac1CdaSign;					//gac1是否执行CDA
	uchar ucIsGacPackDsDol;
	RRP_RESP_DATA tRRPRespData;
	uchar ucRRPUn[4+1];						//RRP UN值
	int	iRRPCounter;						//RRP 计数器
	PayPass_tTrackData tTrack1;
	PayPass_tTrackData tTrack2;			
	E_GAC eCardGacType;						//卡片返回GAC actype
	int iIsStopSignal;						//是否是用户中止信号
	int iIsExecGetDataPostGPO;				//GPO后是否执行GETDATA命令
	int IsTermRecvDetInfo;					//终端收到HostDet标志
	int iCheckExistCDOL1Sign;				//每条读记录后检测CDOL1
	int iCheckExistDSDOLSign;				//每条读记录后检测DSDOL
	int iCheckExistUDOLSign;				//每条读记录后检测UDOL
	int iTornGac2Sign;						//闪开返回非9000执行第二次gac2标志
	int iIsSubmitTornRecord;				//是否提交闪卡记录：针对GAC2-Invalid情况
	PP_TORN_tTLVString tTornRecord;				//恢复的闪卡数据

}PayPass_tParam;


typedef struct
{
	char acDataNeeded[128];
	int iDataNeededLen;
	//char acDataToSend[128];
	char acDataToSend[1024];		//DE数据量--3MX4-4650 update by rsjian at 2018627
	int iDataToSendLen;
	char acTagsToReadYet[128];
	int iTagsToReadYetLen;
	int iMissPdolDataFlag;
	char acTagsToWritePreGac1Yet[512+512+256];			//3MX4-4650 CASE1
	int iTagsToWritePreGac1YetLen;
	char acTagsToWritePostGac1Yet[512+512+256];			//3MX4-8750 CASE1
	int iTagsToWritePostGac1YetLen;
	int iGetDataTagNum;				//Getdata Tag count
	char acGetDataPreGac[128];	
	int iGetDataPreGacLen;
}PayPass_DE_tParam;


/****************PAYPASS交易步骤************************/
int PP_iReadRecord_Step(uchar ucTransMode,uint iActiveSFi);
int PP_iReadBalance_Step(int iType);
int PP_CardHolderVerify_Step(int *piCvmFlag);
int PP_CardActAnaly_Step(E_GAC eGacType,uint iIsPackDsDol,int iIsReqCda,int iCvmFlag);
int PP_CCC_Step();
int PP_RRP_Step(void);
int PP_iRecover_AC_Step(int iCvmFlag);
int PP_CardActAnaly_Ex_Step(E_GAC eGacType,uint iIsPackDsDol,int iIsReqCda,int iCvmFlag);


int PP_MAGModeTrancProc(uint iActiveSFi);
int PP_EMVModeTrancProc(uint iActiveSFi);
//判断标签是否存在
int PP_TAG_iIsNotPresent(char *pTag);
//Table 4.3—Configuration Data in TLV Database that Require Default Value
uchar PP_ucSetDefaultConfigData(void);

int PP_iCheckPdolIsNeedEx2(void);
void PP_vSetStopSignal(void);
int PP_iGetStopSigal(void);
int PP_DE_iUpdateTagToRead(char *pData, int iLen);
int PP_DE_iUpdateTagsToWriteData(int iType,char *pData, int iLen);
int PP_iUpateTornData(char *pData, int iLen);
int PP_iDeleteCurrentTornRecord(void);
uint PP_EMV_iSupportCDA(void);
uchar PP_TLV_ucGetTermCapBit(int uiByteIndex, uchar ucBit);
uchar PP_TLV_ucGetAIPBit(int uiByteIndex, uchar ucBit);
uchar PP_ucGetDataBit(uchar ucData, uchar ucBit);
void PP_vSetActiveAFL(uint iTranMode,uint *ipUseActiveSFI);
void PP_vSetTranLimitAmount(void);
uchar PP_TLV_ucGetKernelCofigBit(int uiByteIndex, uchar ucBit);
uchar PP_TLV_ucGetTmCapBit(int uiByteIndex, uchar ucBit);
uint PP_EMV_bCheckCdaMandatoryData(void);
int PP_iFindCAPKDataBy(void);
int PP_iSetTmCap(int iType);
int PP_iCheckFloorLimit(void);
int PP_iPutData(int iType);
int PP_vInitData(void);
uint PP_bCheckIccMandatoryData(uint uiTranMode);
uint PP_iSupportRRP(void);
int PP_iSupportRecover(void);
int PP_CheckAIPAndAFL(void);
uint PP_iSupportOdv(void);
uint PP_uiGetEmvData(uchar *ucTag,PP_tTLVString *pTlvString);
void PrepareGAC1_Flow_D(E_GAC *pTermAcType);
int PrepareGAC1(E_GAC *pTermAcType);
int PP_iCheckCid(E_GAC eGacType,uchar ucCid);
int PP_iSendOutMsg(int iMsgId);
int PP_TORN_iGetTLV(char *pTag,int iTagLen,PP_tTLVString *pOutTlv);
int PP_iS910_CDA(int iFlowType,char *pOutGACData,uint uiOutLen);
int PP_iS910_NOCDA(int iFlowType,E_GAC eReqGacType,int iIsReqCda);
uchar PP_vAddTornCardRecord(void);
E_GAC PP_iGetActypeMacroByCid(uchar ucCid);
void PP_vConvertTrackDData(uchar ucTrackFlag,  uchar ucCoverFlag, char *paCoverStr);
void PP_vSetRRPPerForm(int iType);		//设置RRP状态
int PP_vStoreRefTornRecord(char *pcTlvData,int iTlvDataLen);		//恢复闪开相关数据
int PP_ucCalPower(int ucCount);
int PP_iPackEmvData(char * packData, char * psTag,YESORNO iIsFlag,int *pnLen);
int PP_DE_uiCheckDataReadYet();
int PP_DE_uiCheckDataReadYetEx();
int PP_DE_iCheck_DEK_Condition();
int PP_DE_iCheck_DEK_Condition_EX();
int PP_DE_iCheck_DEK_Condition_EX2();
void PP_DE_vSetIdsStatus(PP_DE_IDS_STATUS ucIdsStatus);
uint PP_uiIsDolIncludeTag(uint iDolType,uchar *pTag,uint uiTagLen);
int PP_TAG_IsNotEmpty(char *pTag);
void PP_vAddToList(char *pTag,int iTagLen,int iListType);
int PP_TAG_IsPresent(char *pTag);
int PP_iSendDEK(int iIsWait);
int PP_vAddToListEx2(char *pTag,int iTagLen,int iListType);
int PP_DE_vCheckPdolTimerFunc();
void PP_vCheckDekCondition(int iTypeDek);
void PP_vCheckDekCondition_EX(int iTypeDek);
void PP_vCheckDekCondition_EX2(int iTypeDek);
void PP_DE_vSetDsSummaryStatus(PP_DE_IDS_SUMMARY_STATUS ucIdsStatus);
int PP_DE_iGetDsOdsReaderStatus(PP_DE_DS_ODS_INFO_READER ucDsOdsStatus);
int PP_iCheckFirstWriteFlag(void);
int PP_iIsExistStopSignal(void);
void PP_Str_itoa(int num,char *str,int iCount);
/************************************************************************/
/*OUTCOME 相关宏以及api接口*/
/************************************************************************/
#define EMV_UI_MSG_ID                        0x01
#define EMV_UI_STATUS                        0x02
#define EMV_UI_HOLD_TIME                     0x03
#define EMV_UI_LANGUAGE_PRE                  0x04
#define EMV_UI_VALUE_QUAL                    0x05
#define EMV_UI_VALUE                         0x06
#define EMV_UI_CURRENCY_CODE                 0x07

//UIRD
#define EMV_UI_M_CARD_READ_OK				 "\x17"
#define EMV_UI_M_TRY_AGAIN					 "\x21"
#define EMV_UI_M_APPROVED					 "\x03"
#define EMV_UI_M_APPROVED_SIGN			 	 "\x1A"
#define EMV_UI_M_DECLINED				     "\x07"
#define EMV_UI_M_ERR_OTH_CARD			     "\x1C"
#define EMV_UI_M_INSERT_CARD				 "\x1D"
#define EMV_UI_M_SEE_PHONE					 "\x20"
#define EMV_UI_M_AUTH_WAIT					 "\x1B"
#define EMV_UI_M_CLEAR_DISPLAY				 "\x1E"

#define EMV_UI_S_NOT_READY                   "\x00"
#define EMV_UI_S_IDLE                        "\x01"
#define EMV_UI_S_READY_TO_READ               "\x02"
#define EMV_UI_S_PROCESSING                  "\x03"
#define EMV_UI_S_CARD_READ_SUCC              "\x04"
#define EMV_UI_S_PROCESS_ERR                 "\x05"

#define EMV_UI_V_NONE                        "\x00"
#define EMV_UI_V_AMOUNT                      "\x10"
#define EMV_UI_V_BALANCE                     "\x20"


/*L1 Error ID*/
#define PP_L1_ERR_TIMEOUT					  0x01	//TIME OUT ERROR
#define PP_L1_ERR_TRANSERR					  0x02	//TRANSMISSION ERROR
#define PP_L1_ERR_PROERR					  0x03	//PROTOCOL ERROR 

/*L2 Error ID*/
# define PP_L2_ERR_ICC_DATA_MISS			  0x01 // 卡片数据缺失 / ICC Data missing
# define PP_L2_ERR_CAM_FAILED				  0x02 // CAM失败  / CAM Fail
# define PP_L2_ERR_ICC_STATUS				  0x03 // APDU状态码错误 / APDU Status Error
# define PP_L2_ERR_PARSING					  0x04 // 解析错误 / ICC data parsing error.
# define PP_L2_ERR_MAX_EXCEEDED		      	  0x05 // 超过上限 / Exceed max limit.
# define PP_L2_ERR_ICC_DATA			 	  	  0x06 // 卡片数据错误 / ICC data error.
# define PP_L2_ERR_MAG_NOT_SUP			      0x07 // 磁条模式不支持 / Don’t support magnetic
# define PP_L2_ERR_NO_PPSE				      0x08 // PPSE不支持 / Don’t support PPSE
# define PP_L2_ERR_PPSE_FAULT			      0x09 // PPSE错误  / PPSE fault
# define PP_L2_ERR_NO_CAND_AID			      0x0A // 没有候选AID / Candidate AID list is empty.
# define PP_L2_ERR_TERM_DATA			      0x0F // 终端数据错误 / Terminate parameter error
/*DE*/
# define PP_L2_ERR_IDS_READ			   		  0x0B // DE----IDS READ ERROR
# define PP_L2_ERR_IDS_WRITE			      0x0C // DE----IDS WRITE ERROR
# define PP_L2_ERR_IDS_DATA			   		  0x0D // DE----IDS DATA ERROR
# define PP_L2_ERR_IDS_NO_MATCH_AC   		  0x0E // DE----IDS NO MATCHING


/*L3 Error ID*/
# define PP_L3_ERR_TIMEOUT					  0x01 // 通讯超时 / Time out
# define PP_L3_ERR_STOP						  0x02 // 终止交易 / Transaction being terminated
# define PP_L3_ERR_AMOUNT					  0x03 // 金额不存在 / Amount is absent


//OUTCOME  PARAMETER SET
#define EMV_OP_S_APPROVED                    0x0010
#define EMV_OP_S_DECLINED                    0x0020
#define EMV_OP_S_ONLINE_REQ                  0x0030
#define EMV_OP_S_END                         0x0040
#define EMV_OP_S_SELECT_NEXT                 0x0050
#define EMV_OP_S_TRY_OTH_IFC                 0x0060
#define EMV_OP_S_TRY_AGAIN                   0x0070

#define EMV_OP_START_A					  	 0x0100
#define EMV_OP_START_B					     0x0110
#define EMV_OP_START_C					     0x0120
#define EMV_OP_START_D					     0x0130

#define EMV_OP_CVM_NOCVM                     0x0300
#define EMV_OP_CVM_SIGNATURE                 0x0310
#define EMV_OP_CVM_ONLINE_PIN                0x0320
#define EMV_OP_CVM_CCV                       0x0330
#define EMV_OP_CVM_MAG_REQ                   0x03FA
#define EMV_OP_CVM_MAG_NOREQ                 0x03FB

#define EMV_OP_FLAG_UI_OUTCOME               0x0480
#define EMV_OP_FLAG_UI_RESTART               0x0440
#define EMV_OP_FLAG_DATA_RECORD              0x0420
#define EMV_OP_FLAG_DISCRETIONARY            0x0410
#define EMV_OP_FLAG_RECEIPT                  0x0408

#define EMV_OP_FIELDOFF                      0x0600
#define EMV_OP_FIELDOFF_NA                   0x06FF

#define EMV_DDATA_NORMAL                     0x00
#define EMV_DDATA_ERRID                      0x01
#define EMV_DDATA_ERRID_TORN				 0x02

#define EMV_INVALIDRSP_S3                    0x01
#define EMV_INVALIDRSP_S13_14                0x02
#define EMV_INVALIDRSP_S910_1                0x03
#define EMV_INVALIDRSP_S910_2                0x04		//S910 invalid-2  S910.ED61/S910.ED61 ---s11.invalid-2  S11.ED101/S11.ED101
#define EMV_VALIDRSP_S910                    0x01

#define EMV_SEND_OPS                         0x01
#define EMV_SEND_RECORD                      0x02
#define EMV_SEND_DISCRE                      0x03
#define EMV_SEND_OUT_UIRD                    0x04
#define EMV_SEND_MSG_UIRD					 0x05
#define EMV_SEND_SW12                        0x06
#define EMV_SEND_RRP_MEASURE_TIME			 0x07


void PP_vCreateDataRecord(int iType,uchar *pucBuffer,uint *piLen);
void PP_vInitSendOutData(void);
void PP_vSendOut(uchar ucType, uchar ucFlag);
void PP_vSendOut_EX(uchar ucType, uchar ucFlag);
void PP_vSetUIRD(uchar ucFlag, const void *pauValue);
void PP_vSetUIRD_EX(uchar ucFlag, const void *pauValue);
void PP_vSetOPS(ushort usFlag);
void PP_vCreateEMVDiscretionaryData(uchar ucFlag, uchar *pauData, uint *puiDataLen);
uchar PP_bGetApduError_L1(int iErrCode);
PP_tErrorID *PP_pGetErrorId(void);
void PP_vInvalidResponse(uchar ucFlag);
int PP_iValidResponse(uchar ucFlag, E_GAC ucACType);
#endif

