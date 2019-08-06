#ifndef __EMV_SEL_APP__
#define __EMV_SEL_APP__

#include <emv_data.h>
#include <emv_interface.h>
extern int Emv_Sel_App(char cTransType,int nEmvTransSerial,E_INPUTAMT eInputAMT);

/******************************************************************************
 *  	函数名称:	SelectIcFile: 
 *	函数介绍:	
 *	入口参数:	
 *	出口参数:     
 * 	返回值  :		
 ******************************************************************************/
int SelectIcFile(char cSelMode,char *pszFileName,int nLenFileName,ST_ICFILE *stIcFile);
int PP_ADF_iSelectIcFile(char cSelMode,char *pszFileName,int nLenFileName,ST_ICFILE *stIcFile);
int PP_PPSE_iSelectIcFile(char cSelMode,char *pszFileName,int nLenFileName,ST_ICFILE *stIcFile);
int LC_PPSE_SelectIcFile(char cSelMode,char *pszFileName,int nLenFileName,ST_ICFILE *stIcFile);
/******************************************************************************
 *  	函数名称:	GetICCAID: 
 *	函数介绍:	获取IC卡AID
 *	入口参数:	
 *	出口参数:     
 * 	返回值  :		
 ******************************************************************************/
 int GetICCAID(pTlvData tlv,int nNum,ST_ICCAID *stICCAID,YESORNO bIssCodeIndex);
 /******************************************************************************
 *  	函数名称:	RF_GetICCAID: 
 *	函数介绍:	获取IC卡AID
 *	入口参数:	
 *	出口参数:     
 * 	返回值  :		
 ******************************************************************************/
  int RF_GetICCAID(pTlvData tlv,int nNum,ST_RF_ICCAID *stICCAID);
 /******************************************************************************
 *  	函数名称:	SortAIDList: 
 *	函数介绍:	对候选AID列表根据优先级进行排序
 					这里采用冒泡排序
 *	入口参数:	ST_ICCAID  stICCAID[]: 候选列表
 					int nAIDNum: 候选列表条数
 *	出口参数:     ST_ICCAID  stICCAID[]:按优先级排序好的候选列表
 * 	返回值  :		无
 ******************************************************************************/
void SortAIDList(ST_ICCAID stICCAID[],int nAIDNum);

 /******************************************************************************
 *  	函数名称:	SortAIDListEx: 
 *	函数介绍:	对候选AID列表根据优先级进行排序
 					这里采用冒泡排序
 *	入口参数:	ST_ICCAID  stICCAID[]: 候选列表
 					int nAIDNum: 候选列表条数
 *	出口参数:     ST_ICCAID  stICCAID[]:按优先级排序好的候选列表
 * 	返回值  :		无
 ******************************************************************************/
void SortAIDListEx(ST_RF_ICCAID stICCAID[],int nAIDNum);
#endif