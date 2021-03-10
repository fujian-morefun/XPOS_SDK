//#include "upay_track.h"
//#include "upay_print.h"
#include "app_def.h"


#define COUNTRYCODE "\x01\x56"//CNY
//#define COUNTRYCODE "\x03\x56"//INR
//#define COUNTRYCODE "\x09\x78"//EUR
//#define COUNTRYCODE "\x08\x40"//USD


void sdk_SetTermConfig()
{
	TERMCONFIG termconfig;
	memset(&termconfig,0,sizeof(TERMCONFIG));

	SYS_TRACE( "TestSetTermConfig" );

	memcpy( termconfig.TermCap, "\xE0\xF8\xC8", 3);	/*Terminal performance '9F33'*/
	memcpy( termconfig.AdditionalTermCap,"\xFF\x80\xF0\x00\x01", 5);/*Terminal additional performance*/
	memcpy( termconfig.szMerID_ans_9F16,"000000000000000",15);	//9F16
	memcpy( termconfig.IFDSerialNum,"morefun1",8);		/*IFD serial number '9F1E'*/ 
	memcpy(termconfig.TermCountryCode, COUNTRYCODE, 2);	/*Terminal country code '9F1A'*/
	memcpy( termconfig.TermID, "12312312", 8);			/*Terminal identification '9F1C'*/
	termconfig.TermType = 0x22;						/*Terminal type '9F35'*/
	memcpy( termconfig.TransCurrCode,COUNTRYCODE, 2);	/*Transaction currency '5F2A'*/
	termconfig.TransCurrExp = 0x02;					/*Transaction currency index '5F36'*/
	memcpy(termconfig.szTransProp,"\x36\x00\xC0\x00",4);				/*TTQ'9F66'*/

	termconfig.bPSE = YES;					/*Whether to support the choice PSE 1*/
	termconfig.bCardHolderConfirm = YES;	/*Whether to support cardholder confirmation 1*/
	termconfig.bPreferedOrder = YES;		/*Whether to support the preferred display 1*/
	termconfig.bPartialAID = YES;			/*Whether to support partial AID matching 1*/
	termconfig.bMultiLanguage  = YES;		/*Whether to support multiple languages 0*/
	termconfig.bCommonCharset = YES;		/*Whether to support public character sets 0*/	
	termconfig.bIPKCValidtionCheck = YES;	/*Whether to check the validity of the issuer's public key authentication 1*/
	termconfig.bContainDefaultDDOL = YES;	/*Whether to include the defaultDDOL 1*/
	termconfig.bCAPKFailOperAction = NO;	/*CAPK Is operator intervention required when reading an error? 1*/
	termconfig.bCAPKChecksum = YES;		/*Whether to perform CAPK check 1*/
	/**<Cardholder Verification Method*/
	termconfig.bBypassPIN = YES;			/*Whether to support skipping PIN input (requires change process, to be determined)*/
	termconfig.bGetDataForPINCounter =YES;	/*PIN Try to check if the counter is supportedGetData 1*/
	termconfig.bFailCVM = YES;				/*Whether to support the wrong CVM (must be Yes)*/
	termconfig.bAmountBeforeCVM = YES;		/*CVM Whether the amount is known before 1*/
	/**<Term Risk Management*/
	termconfig.bLimitFloorCheck = YES;		/*Whether to perform a minimum check 1*/
	termconfig.bRandomTransSelect = YES;	/*Whether to make random trading choices 1*/
	termconfig.bValocityCheck = YES;		/*Whether to check the frequency 1*/
	termconfig.bTransLog = YES;			/* Whether to record the transaction log 1*/
	termconfig.bExceptionFile = YES;		/*Whether to support card blacklist 1*/
	termconfig.bTRMBaseOnAIP = NO;			/*Whether terminal risk management is based on application interaction characteristics 1*/
	/**<Terminal Action Analysis*/
	termconfig.bTerminalActionCodes = YES;	/*Whether to support terminal behavior code 1*/
	termconfig.bDefActCodesBefore1stGenAC = NO;/*Is the default behavior code prior to FirstGenerateAC ?*/
	termconfig.bDefActCodesAfter1stGenAC = NO;/*Is the default behavior code after FirstGenerateAC ?*/
	/**<Completion Processing*/
	termconfig.bForceOnline= NO;			/*Whether to allow forced online 1*/
	termconfig.bForceAccept = NO;			/*Whether to allow forced acceptance of transactions 1*/
	termconfig.bAdvices = YES;				/*Whether to support notification 0*/
	termconfig.bIISVoiceReferal = YES;		/*Whether to support the voice reference initiated by the card issuer ?*/
	termconfig.bBatchDataCapture = YES;	/*Whether to support batch data collection*/
	termconfig.bDefaultTDOL = YES;			/*Is there a default? TDOL*/
	termconfig.bAccountSelect = YES;		/*Whether to support account selection*/
	//visa check value
	termconfig.checkAmtZore=1;
	termconfig.checkRCTL=1;
	termconfig.checkStatus=1;
	termconfig.checkFloorLimit=1;
	termconfig.optionAmtZore=0;
	termconfig.checkCVMLimit=1;
	termconfig.checkOnPIN=1;
	termconfig.checkSig=1;

	EMV_TermConfigInit(&termconfig);//Init EMV terminal parameter
}


static void sdk_add_demo_aids(TERMINALAPPLIST *TerminalApps)
{
	int i = 0;
	int n = 0;

	if(TerminalApps==0)
		return;

	SYS_TRACE( "TestDownloadAID" );
	memset(TerminalApps,0x00,sizeof(TERMINALAPPLIST));	
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x00\x01\x10\x10", 7);//AID
	TerminalApps->TermApp[n++].AID_Length = 7;//1
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x00\x03\x10\x10", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//2
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x00\x03\x20\x10", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//3
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x00\x03\x20\x20", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//4
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x00\x03\x80\x10", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//5
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x00\x04\x10\x10", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//6
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x00\x04\x99\x99", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//7
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x00\x04\x30\x60", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//8
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x00\x04\x60\x00", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//9
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x00\x05\x00\x01", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//10
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x00\x25\x01", 6);
	TerminalApps->TermApp[n++].AID_Length = 6;//11
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x00\x29\x10\x10", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//12
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x00\x42\x10\x10", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//13
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x00\x42\x20\x10", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//14
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x00\x65\x10\x10",7);
	TerminalApps->TermApp[n++].AID_Length = 7;//15
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x01\x21\x10\x10", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//16
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x01\x21\x47\x11", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//17
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x01\x41\x00\x01", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//18
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x01\x52\x30\x10", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//19
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x03\x33\x01\x01", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//20
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x05\x24\x10\x10", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//21
	memcpy(TerminalApps->TermApp[n].AID, "\xA0\x00\x00\x05\x24\x10\x11", 7);
	TerminalApps->TermApp[n++].AID_Length = 7;//22	

	TerminalApps->bTermAppCount = n>UMAX_TERMINAL_APPL ? UMAX_TERMINAL_APPL : n;//The number of AID
	for(i=0; i<n; i++)
	{
		TerminalApps->TermApp[i].bTerminalPriority = 0x03;	//Terminal priority
		TerminalApps->TermApp[i].bTargetPercentageInt = 0x00;/*Randomly selected target percentage DF17*/
		memcpy(TerminalApps->TermApp[i].TAC_Default, "\x00\x00\x00\x00\x00", 5);/* TAC Default data format (n5) DF11*/ 
		memcpy(TerminalApps->TermApp[i].TAC_Denial, "\x00\x00\x00\x00\x00", 5);/* TAC Refuse: data format (n5) DF12*/
		memcpy(TerminalApps->TermApp[i].TAC_Online, "\x00\x00\x00\x00\x00", 5);/* TAC Online: data format (n5) DF13*/
		memcpy(TerminalApps->TermApp[i].abTrnCurrencyCode, COUNTRYCODE, 2);/* Currency code tag: 5F2A */
		//memcpy(TerminalApps->TermApp[i].abTerminalCountryCode, COUNTRYCODE, 2);/* Country code terminal tag: 9F1A */
		TerminalApps->TermApp[i].abTrnCurrencyExp = 0x02;/* tag: 5F36 */
		memcpy(TerminalApps->TermApp[i].abRFCVMLimit, "\x00\x00\x00\x10\x00", 6);/*Terminal performs CVM quota: DF21*/
		memcpy(TerminalApps->TermApp[i].abDDOL, "\x9F\x37\x04", 3);/* TDOL DF14*/
		TerminalApps->TermApp[i].DDOL_Length = 0x03;/* TDOL Length */
		//TerminalApps->TermApp[i].TerminalType = 0x22;/* Terminal type: data format (n 3) */
		//memcpy(TerminalApps->TermApp[i].TerminalCap, "\xE0\xF8\xC8", 3);/* Terminal capability: data format (n 3) */		
	}

	for(i=0; i<20; i++)
	{
		TerminalApps->TermApp[i].bMaxTargetPercentageInt = 0x00;/*Offset randomly selected maximum target percentage DF16*/
		memcpy(TerminalApps->TermApp[i].abTFL_International, "\x00\x00\x3A\x98", 4);/* Terminal minimum 9F1B//*/
		memcpy(TerminalApps->TermApp[i].abThresholdValueInt, "\x00\x00\x13\x88", 4);/*Offset randomly selected threshold DF15*/
		memcpy(TerminalApps->TermApp[i].abTerminalApplVersion, "0096", 2);/* Terminal application version 9F09 9F08 */
		memcpy(TerminalApps->TermApp[i].abEC_TFL, "\x00\x00\x00\x20\x00", 6);/* Terminal electronic cash transaction limit tag: 9F7B n12*/
		memcpy(TerminalApps->TermApp[i].abRFOfflineLimit, "\x00\x00\x00\x20\x00", 6);/*Contactless offline minimum :DF19*/
		memcpy(TerminalApps->TermApp[i].abRFTransLimit, "\x00\x00\x02\x00\x00", 6);/*Contactless transaction limit:DF20*/
		TerminalApps->TermApp[i].cOnlinePinCap = 0x01;/* Terminal online pin capability DF18*/
	}

	for(i=20; i<n; i++)
	{
		memcpy(TerminalApps->TermApp[i].abTerminalApplVersion, "0002", 2);/* Terminal application version 9F09 9F08 */
		memcpy(TerminalApps->TermApp[i].abTFL_International, "\x00\x01\x86\xA0", 4);/* Terminal minimum 9F1B//*/
		memcpy(TerminalApps->TermApp[i].abThresholdValueInt, "\x00\x00\x00\x00", 4);/*Offset randomly selected threshold DF15*/
		TerminalApps->TermApp[i].bMaxTargetPercentageInt = 0x05;/*Offset randomly selected maximum target percentage DF16*/
		TerminalApps->TermApp[i].cOnlinePinCap = 0x31;/* Terminal online pin capability DF18*/
		memcpy(TerminalApps->TermApp[i].abEC_TFL, "\x00\x00\x01\x00\x00", 6);/* Terminal electronic cash transaction limit tag: 9F7B n12*/
		memcpy(TerminalApps->TermApp[i].abRFOfflineLimit, "\x00\x00\x01\x00\x00", 6);/*Contactless offline minimum :DF19*/
		memcpy(TerminalApps->TermApp[i].abRFTransLimit, "\x00\x00\x05\x00\x00", 6);/*Contactless transaction limit:DF20*/
	}
}

void m_DispOffPin(int Count)	
{
	if (Count == 0)
	{
		gui_messagebox_show("", "PIN OK" , "" , "ok" , 2000);
	}
    else if (Count == 1 || Count == 2)
	{
		gui_messagebox_show("", "WRONG PIN!" , "" , "ok" , 4000);
	}
	else 
	{
		gui_messagebox_show("", "INCORRECT PIN!" , "" , "ok" ,4000);
	}
}

void m_ReadingCardDisp(int iTranMode)
{
	if(iTranMode == 1)
	{
		//contect
		gui_messagebox_show("", "Reading card,pls don't pull the card!" , "" , "" ,10);
	}
	else if(iTranMode == 2)
	{
		//uncontect
		gui_messagebox_show("", "Reading card,pls don't take the card!" , "" , "" ,10);
	}
}

//Online processing
static int sdk_send_carddata(char *sendbuf,int nsendlen, char *recvbuf,int*nrecvlen)
{
	int nret = EMVAPI_RET_SUCC;
	//todo
	{
		;//Send EMV data (sendbuf)to the host and receive the returned data(recvbuf).
		//nrecvlen is The length of the returned data
	}
	return nret;
}
static void unpack_ic_online_data(char*host_Rsp,int len_Rsp,char*szAuthCode,char*sField55)
{
	//todo:unpack, Fill the parsed data into szAuthCode and sField55
	//int nLen=0;
	//Ex_TLV_GetDataByTag((BYTE *)EMV_TAG_8A_TM_ARC, (BYTE *) host_Rsp, len_Rsp, (BYTE *)szAuthCode, &nLen);
	;
}
#define  TLV_MAX_LEN	256
//IC card secondary authorization
int sdk_online_proc(int ic_online_resp)
{
	char *msg_Buf = NULL;
	char *host_Rsp = NULL;
	int	len_Send = 0;
	int	len_Rsp = 0;
	int nOnlineRes = -1;			
	int iRet = EMVAPI_RET_SUCC;

	char szAuthCode[2+1]={0};
	char *sField55;
	char *sTLVtags="9F269F10";//pack tags example
	char *sPackValue;
	int nPacklen;

	SYS_TRACE( "sdk_online_proc:ic_online_resp=%d\r\n",ic_online_resp);

	;//todo:Allocate space:msg_Buf,host_Rsp

	iRet = sdk_send_carddata(msg_Buf, len_Send,host_Rsp,&len_Rsp);
	;//todo:Free up space:msg_Buf

	if(ic_online_resp == 0)
	{
		if(EMVAPI_RET_SUCC != iRet) 
		{
			iRet = EMVAPI_RET_AAR;
		}
		;//todo:Free up space:host_Rsp
		return iRet;
	}

	if(EMVAPI_RET_SUCC==iRet) 
		nOnlineRes = SUCC;
	else
		nOnlineRes = FAIL;
	
	sField55=(char*)Util_Malloc(TLV_MAX_LEN);
	unpack_ic_online_data(host_Rsp,len_Rsp,szAuthCode,sField55);
	;//todo:Free up space:host_Rsp
	
	sPackValue=(char*)Util_Malloc(TLV_MAX_LEN);
	iRet = emv_onlineresp_proc_pack(nOnlineRes,szAuthCode,sField55,sTLVtags,sPackValue,&nPacklen);//IC card secondary authorization request
	Util_Free(sField55);
	//todo:save and process
	;;


	Util_Free(sPackValue);
	SYS_TRACE( "sdk_online_proc:iRet=%d\r\n",iRet);

	return iRet;
}

static void add_capkByAid(unsigned char* cAID,unsigned char Index)
{
	CAPUBLICKEY ppkKey;
	char *szBuf = NULL;
	char szHash[20]={0};

	int nLen = 0;
	int npacklen = 0;
	nLen = sizeof(CAPUBLICKEY)+30;
	szBuf = (char *)Util_Malloc(nLen);
	if(NULL == szBuf) {
		return ;
	}
	memset(&ppkKey,0,sizeof(CAPUBLICKEY));
	memcpy(ppkKey.RID,cAID,5);
	ppkKey.CA_PKIndex=Index;
	memcpy(ppkKey.CAPKModulus,
		"\x81\xCC\xF2\xD6\xE5\xCD\x28\xE4\xE1\x21\x05\xB5\x05\xAA\x16\x1D\x98\x30\xDE\xFE\x2A"
		"\xBD\x8F\xFF\xA5\x00\x83\x9E\x34\x52\x76\xCD\x3C\xCD\xF6\x1B\x0F\xDE\x18\xAE\x48\xE1"
		"\xEA\x1A\x5C\xD7\xDA\x7A\x11\x9B\xEF\xAE\x31\x6C\x1F\x91\xD7\x4B\xB7\x7C\xD5\xC4\xE2"
		"\xEB\x91\xC3\xC3\x56\x05\x7D\x78\x56\x1D\x1C\x66\x13\x13\xD9\x54\x08\x37\xCC\xDF\x93"
		"\x69\xC1\x8E\x41\x7E\x96\x4C\x26\x8B\x7F\xE6\x0A\x38\x74\x64\xC3\x1A\x11\x35\x8F\x30"
		"\x3C\x18\xFB\x7C\x18\x2B\xB3\xBD\x04\x14\x8E\x09\x73\xA9\xFA\x8A\x12\x8D\xA7\xB8\xF4"
		"\xE4\x75\xC2\x9A\x5C\xC5\xF2\xA2\x89\x11\x4F\xE7\xA3\xB3\x4E\x1F\xEC\xDA\xBC\x8F\x85"
		"\x24\xA9\xC2\x23\x0C\x77\x80\x38\xB9\x16\x10\x6F\xF9\x1E\xB7\x7D\xBB\xF5\xAC\x97\x3F"
		"\x3F\x2A\x35\x07\x59\x0F\x5B\xF7\x7C\xF9\x4F\x39\xAF\x6F\x9D\x97\x1B\x92\x07\x51\x6A"
		"\x08\xF1\x09\xB1\x6D\xF1\xD1\xB4\xE6\x73\x90\x5E\xBC\x7B\x78\x56\x19\x02\xB2\xC4\xC3"
		"\x9C\xA8\x64\xF4\xF4\x22\xFA\xE9\xFE\x59\xCB\x11\x2F\x82\xFF\xAB\xBC\x9A\xCC\xB2\x46"
		"\xEC\x46\xF0\x02\x0B\xED\xBF\x98\xEE\x76\x8C\x20\x6A\x0F\x13\xB5\xB3",248);
	memcpy(ppkKey.CAPKExponent,"\x00\x00\x03",3);
	memcpy(ppkKey.CAPKExpDate,"\x20\x20\x12\x31",4);
	ppkKey.LengthOfCAPKModulus=0xF8;
	ppkKey.LengthOfCAPKExponent=3;

	memcpy(szBuf, cAID, 5);
	szBuf[5]=Index;
	//memcpy(szBuf+5, (char *)stCAPK->cCAPKIndex_b_9F22, 1);
	memcpy(szBuf+6, (char *)ppkKey.CAPKModulus,ppkKey.LengthOfCAPKModulus);
	nLen = ppkKey.LengthOfCAPKModulus + 6;
	if(ppkKey.CAPKExponent[2]==0x03) {
		memcpy(szBuf+nLen, (char *)&(ppkKey.CAPKExponent[2]), 1);
		nLen += 1;
	}
	else {
		memcpy(szBuf+nLen, (char *)ppkKey.CAPKExponent, 3);
		nLen += 3;
	}
	memset(szHash, 0, sizeof(szHash));
	Util_SHA1((unsigned char *)szBuf, nLen, (unsigned char *)szHash);
	memcpy(ppkKey.ChecksumHash,szHash,20);
	EMV_PrmSetCAPK(&ppkKey);
	Util_Free(szBuf);
}

static void init_capk_param(int binitial)
{
	if(binitial)
		EMV_PrmClearCAPKFile();
	add_capkByAid("\xA0\x00\x00\x00\x04",0x7A); //mastercard
	add_capkByAid("\xA0\x00\x00\x03\x24",0x7A); //dpas
	add_capkByAid("\xA0\x00\x00\x00\x03",0x7A); //visa
	add_capkByAid("\xA0\x00\x00\x01\x52",0x7A); //dpas
	add_capkByAid("\xA0\x00\x00\x00\x65",0x7A); //jcb
	add_capkByAid("\xA0\x00\x00\x00\x25",0x7A);//amex
	add_capkByAid("\xA0\x00\x00\x00\x29",0x7A);//amex
	add_capkByAid("\xA0\x00\x00\x03\x33",0x7A);//quics
}
static void init_aid_param(int binitial)
{
	int nret = UEMV_PRM_OK;
	TERMINALAPPLIST *TerminalApps=NULL;

	if(binitial)
		EMV_PrmClearAIDPrmFile();

	TerminalApps=(TERMINALAPPLIST*)Util_Malloc(sizeof(TERMINALAPPLIST));
	if(TerminalApps==NULL)
		return;
	/*EMV_PrmGetAIDPrm(TerminalApps);
	if(UEMV_PRM_OK==nret)
	{
		Util_Free(TerminalApps);
		return;
	}*/
	memset(TerminalApps,0,sizeof(TERMINALAPPLIST));
	sdk_add_demo_aids(TerminalApps);
	EMV_PrmSetAIDPrm(TerminalApps);//Set AID
	Util_Free(TerminalApps);
}

static void sdk_add_demo_rupay_prmacqkey(RUPAYPRMACQKEYLIST *pRuPayPRMacqKeyList)
{
	int i = 0;
	int n = 0;
	//char cServiceData1[] = "DF16021010DF24050810109500df453b09101506150101112233445566778800000100010061150406125703000000010000020000000A0101000A01020502000102010206000A01010302";

	if(pRuPayPRMacqKeyList==0)
		return;

	//01
	SYS_TRACE( "TestDownloadPRMacqKey" );
	memset(pRuPayPRMacqKeyList,0x00,sizeof(RUPAYPRMACQKEYLIST));

	memcpy(pRuPayPRMacqKeyList->PRMacqKey[n].ucServiceId,"\x10\x10",2);
	pRuPayPRMacqKeyList->PRMacqKey[n].ucPRMacqKeyIndex = 1;
	pRuPayPRMacqKeyList->PRMacqKey[n].ucPRMacqKeyLen = 8;
	memcpy(pRuPayPRMacqKeyList->PRMacqKey[n].ucPRMacqKey,"\x01\x02\x03\x04\x05\x06\x07\x08",8);
	memcpy(pRuPayPRMacqKeyList->PRMacqKey[n].ucPRMacqKCV,"\x00\x00\x01",3);
	
	n++;
	//02
	memcpy(pRuPayPRMacqKeyList->PRMacqKey[n].ucServiceId,"\x10\x11",2);
	pRuPayPRMacqKeyList->PRMacqKey[n].ucPRMacqKeyIndex = 2;
	pRuPayPRMacqKeyList->PRMacqKey[n].ucPRMacqKeyLen = 8;
	memcpy(pRuPayPRMacqKeyList->PRMacqKey[n].ucPRMacqKey,"\x01\x02\x03\x04\x05\x06\x07\x09",8);
	memcpy(pRuPayPRMacqKeyList->PRMacqKey[n].ucPRMacqKCV,"\x00\x00\x02",3);

	pRuPayPRMacqKeyList->bPRMacqKeyCount =2;
	
	return;
}

static void sdk_add_demo_rupay_service(RUPAYSERVICELIST *pRuPayServiceList)
{
	int i = 0;
	int n = 0;

	if(pRuPayServiceList==0)
		return;

	SYS_TRACE( "TestDownloadRuPayService" );

	//1
	memcpy(pRuPayServiceList->ServiceData[n].ucServiceId,"\x10\x10",2);
	memcpy(pRuPayServiceList->ServiceData[n].auServiceQualifier,"\x01\x02\x03\x04\x05",5);
	pRuPayServiceList->ServiceData[n].iServiceLen = 5;
	memcpy(pRuPayServiceList->ServiceData[n].auServiceData,"\x01\x02\x03\x04\x05",5);

	n++;
	//2
	memcpy(pRuPayServiceList->ServiceData[n].ucServiceId,"\x10\x11",2);
	memcpy(pRuPayServiceList->ServiceData[n].auServiceQualifier,"\x01\x02\x03\x04\x06",5);
	pRuPayServiceList->ServiceData[n].iServiceLen = 5;
	memcpy(pRuPayServiceList->ServiceData[n].auServiceData,"\x01\x02\x03\x04\x06",5);

	pRuPayServiceList->bServiceCount = 2;
	return;
}

void clear_service_prmacqkey(void)
{
	if(SUCC == EMV_ClearRuPayServiceFile() &&  SUCC == EMV_ClearRuPayPRMacqKeyFile())
	{
		xgui_messagebox_show("", "clear succ!" , "" , "ok" , 0);
	}
	else
	{
		xgui_messagebox_show("", "clear fail!" , "" , "ok" , 0);
	}
}

void init_service_prmacqkey(int binitial)
{
	int nret = UEMV_PRM_OK;
	RUPAYPRMACQKEYLIST *pRuPayPRMacqKeyList = NULL;
	RUPAYSERVICELIST *pRuPayServiceList=NULL;

	if(binitial)
	{
		EMV_ClearRuPayServiceFile();
		EMV_ClearRuPayPRMacqKeyFile();
	}
		

	//PRMacqKey
	pRuPayPRMacqKeyList=(RUPAYPRMACQKEYLIST*)Util_Malloc(sizeof(RUPAYPRMACQKEYLIST));
	if(pRuPayPRMacqKeyList==NULL)
		return;
	
	memset(pRuPayPRMacqKeyList,0,sizeof(RUPAYPRMACQKEYLIST));
	sdk_add_demo_rupay_prmacqkey(pRuPayPRMacqKeyList);
	nret = EMV_SetRuPayPRMacqKeyList(pRuPayPRMacqKeyList);	//Set PRMacqKey
	Util_Free(pRuPayPRMacqKeyList);

	if(nret != SUCC)
	{
		xgui_messagebox_show("", "download fail!" , "" , "ok" , 0);
		return;
	}

	//Service
	pRuPayServiceList=(RUPAYSERVICELIST*)Util_Malloc(sizeof(RUPAYSERVICELIST));
	if(pRuPayServiceList==NULL)
		return;

	memset(pRuPayServiceList,0,sizeof(RUPAYSERVICELIST));
	sdk_add_demo_rupay_service(pRuPayServiceList);
	nret = EMV_SetRuPayServiceList(pRuPayServiceList);		//Set rupay service
	Util_Free(pRuPayServiceList);

	if(nret == SUCC)
	{
		xgui_messagebox_show("", "download succ!" , "" , "ok" , 0);
	}
	else
	{
		xgui_messagebox_show("", "download fail!" , "" , "ok" , 0);
	}
	return;
}

static int sdk_readcard_config(void)
{
	//EMV_SetInputPin( m_InputPin );//Set offline PIN verification interface
	//EMV_SetDispOffPin( m_DispOffPin );//Set offline PIN prompt interface
	//EMV_SetReadingCardDisp(m_ReadingCardDisp);

	sdk_SetTermConfig();

	init_aid_param(1);

	init_capk_param(1);

	return SUCC;
}


int upay_readcard_proc(st_read_card_in *card_in, st_read_card_out *card_out)
{
	int ret=EMVAPI_RET_CANCEL;

	SYS_TRACE( "upay_readcard_proc" );

loop_card:
	memset(card_out, 0, sizeof(st_read_card_out));
	//dukpt_prepare_key(0, card_out->pin_ksn);//ksn?????????????????????

	ret = emv_read_card(card_in, card_out);

	SYS_TRACE( "-----------------------sdk_readcard Ret:%d-------------------------",ret);
	//emv_read_card return value processing
	if(EMVAPI_RET_FALLBACk==ret){//fallback mode
		card_in->card_mode = READ_CARD_MODE_MAG;
		card_in->forceIC=0;
		memset(card_in->card_page_msg,0x00,sizeof(card_in->card_page_msg));
		strcpy(card_in->card_page_msg,"please try to swipe");
			goto loop_card;
	}
	else if(EMVAPI_RET_FORCEIC==ret){//force to use chip card
		if(card_in->card_mode == READ_CARD_MODE_MAG)
			ret =EMVAPI_RET_ARQC;
		else{
			card_in->card_mode = READ_CARD_MODE_IC | READ_CARD_MODE_RF;//DIP and TAP
			memset(card_in->card_page_msg,0x00,sizeof(card_in->card_page_msg));
			strcpy(card_in->card_page_msg,"don't swipe,please tap/insert the card");
			goto loop_card;
		}
	}
	else if(EMVAPI_RET_OTHER==ret){//contactless require turn to other interface
		card_in->card_mode = READ_CARD_MODE_IC;
		memset(card_in->card_page_msg,0x00,sizeof(card_in->card_page_msg));
		strcpy(card_in->card_page_msg,"please insert card");
		goto loop_card;
	}
	else if(EMVAPI_RET_SEEPHONE==ret)//visa require see phone and retry
	{
		Sys_Delay(60000);//delay 1 minute
		card_in->card_mode = READ_CARD_MODE_RF;
		memset(card_in->card_page_msg,0x00,sizeof(card_in->card_page_msg));
		strcpy(card_in->card_page_msg,"See Phone and Retry");
		goto loop_card;
	}

	if(EMVAPI_RET_ARQC == ret)//online
	{
		gui_messagebox_show("", "Online Request" , "" , "ok" , 0);
		ret = sdk_online_proc(card_in->ic_online_resp);//online processing
	}

	if(EMVAPI_RET_TC == ret)//approved 
	{
		gui_messagebox_show("", "Approved" , "" , "ok" , 0);
	}
	else if(EMVAPI_RET_AAC == ret)//decline
	{
		gui_messagebox_show("", "Declined" , "" , "ok" , 0);
	}
	else if(EMVAPI_RET_AAR == ret)//terminate
	{
		gui_messagebox_show("", "Terminate" , "" , "ok" , 0);
	}
	else if(EMVAPI_RET_TIMEOUT == ret)//timeout
	{
		gui_messagebox_show("", "time out" , "" , "ok" , 0);
	}
	else if(EMVAPI_RET_CANCEL == ret)//Cancel
	{
		gui_messagebox_show("", "Cancel" , "" , "ok" , 0);
	}

	SYS_TRACE( "-----------------------card_info---------------------------" );
	SYS_TRACE( "card_type:%d\r\n", card_out->card_type );
	SYS_TRACE("trackb:%s\r\n", card_out->track2);
	SYS_TRACE("trackc:%s\r\n", card_out->track3);
	SYS_TRACE("pan:%s\r\n", card_out->pan);
	SYS_TRACE("expdate:%s\r\n", card_out->exp_data);
	SYS_TRACE_BUFF(card_out->pin_block, sizeof(card_out->pin_block), "pin_block:");
	Sys_Delay(50);
	SYS_TRACE_BUFF(card_out->pin_ksn, sizeof(card_out->pin_ksn), "KSN:");
	Sys_Delay(50);	
	SYS_TRACE("vChName:%s\r\n", card_out->vChName);
	SYS_TRACE("ic_data_len:%d\r\n", card_out->ic_data_len);
	SYS_TRACE_BUFF(card_out->ic_data, card_out->ic_data_len, "ic_data:");
	//Due to interface memory limitations, large data log output, can not use SYS_TRACE, should use SYS_TRACE_BUFF_TIP.
	//xgui_messagebox_show("track2", card_out->track2 , "" , "ok" , 0);

	//just for show testing
	if(EMVAPI_RET_TC == ret||EMVAPI_RET_SUCC == ret){
		gui_messagebox_show("pan", card_out->pan , "" , "ok" , 0);
		gui_messagebox_show("expdate", card_out->exp_data , "" , "ok" , 0);
	}

	return ret;
}


int sdk_readcard_init(void)
{
	EMV_iKernelInit();//Init EMV relate data and file
	sdk_readcard_config();//init readcard_config
	return SUCC;
}