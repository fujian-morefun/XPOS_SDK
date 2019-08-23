#include "upay_consum.h"
#include "upay_track.h"
#include "../pages/input_num_page.h"
#include "../pages/inputcard_page.h"
#include "xGui/inc/messagebox.h"
#include "../sdk_log.h"
#include "upay_define.h"
//#include "emvapi/inc/emv_api.h"
//#include "aemv/inc/emv_interface.h"
#include "lib_emvpub/inc/emv_interface.h"
#include "libapi_xpos/inc/def.h"
#include "libapi_xpos/inc/libapi_emv.h"
#include "pub/tracedef.h"
#include "AppPub/mfd/mf_security.h"

static int first = 0;

#define COUNTRYCODE "\x01\x56"//CNY
//#define COUNTRYCODE "\x03\x56"//INR
//#define COUNTRYCODE "\x09\x78"//EUR

void TestSetTermConfig(TERMCONFIG *termconfig)
{
	//char szBuf[100] = {0};

	APP_TRACE( "TestSetTermConfig" );

	memset(termconfig,0x00,sizeof(TERMCONFIG));	
	memcpy( termconfig->TermCap, "\xE0\xE1\xC8", 3);	/*Terminal performance '9F33'*/
	memcpy( termconfig->AdditionalTermCap,"\xFF\x80\xF0\x00\x01", 5);/*Terminal additional performance*/	
	memcpy( termconfig->IFDSerialNum,"mf90_01",8);		/*IFD serial number '9F1E'*/ 
	memcpy(termconfig->TermCountryCode, COUNTRYCODE, 2);	/*Terminal country code '9F1A'*/
	memcpy( termconfig->TermID, "12312312", 8);			/*Terminal identification '9F1C'*/
	termconfig->TermType = 0x22;						/*Terminal type '9F35'*/
	memcpy( termconfig->TransCurrCode,COUNTRYCODE, 2);	/*Transaction currency '5F2A'*/
	termconfig->TransCurrExp = 0x02;					/*Transaction currency index '5F36'*/

	termconfig->bPSE = YES;					/*Whether to support the choice PSE 1*/
	termconfig->bCardHolderConfirm = YES;	/*Whether to support cardholder confirmation 1*/
	termconfig->bPreferedOrder = YES;		/*Whether to support the preferred display 1*/
	termconfig->bPartialAID = YES;			/*Whether to support partial AID matching 1*/
	termconfig->bMultiLanguage  = NO;		/*Whether to support multiple languages 0*/
	termconfig->bCommonCharset = YES;		/*Whether to support public character sets 0*/	
	termconfig->bIPKCValidtionCheck = YES;	/*Whether to check the validity of the issuer's public key authentication 1*/
	termconfig->bContainDefaultDDOL = YES;	/*Whether to include the defaultDDOL 1*/
	termconfig->bCAPKFailOperAction = NO;	/*CAPK Is operator intervention required when reading an error? 1*/
	termconfig->bCAPKChecksum = YES;		/*Whether to perform CAPK check 1*/
	/**<Cardholder Verification Method*/
	termconfig->bBypassPIN = YES;			/*Whether to support skipping PIN input (requires change process, to be determined)*/
	termconfig->bGetDataForPINCounter =YES;	/*PIN Try to check if the counter is supportedGetData 1*/
	termconfig->bFailCVM = YES;				/*Whether to support the wrong CVM (must be Yes)*/
	termconfig->bAmountBeforeCVM = YES;		/*CVM Whether the amount is known before 1*/
	/**<Term Risk Management*/
	termconfig->bLimitFloorCheck = YES;		/*Whether to perform a minimum check 1*/
	termconfig->bRandomTransSelect = YES;	/*Whether to make random trading choices 1*/
	termconfig->bValocityCheck = YES;		/*Whether to check the frequency 1*/
	termconfig->bTransLog = YES;			/* Whether to record the transaction log 1*/
	termconfig->bExceptionFile = YES;		/*Whether to support card blacklist 1*/
	termconfig->bTRMBaseOnAIP = NO;			/*Whether terminal risk management is based on application interaction characteristics 1*/
	/**<Terminal Action Analysis*/
	termconfig->bTerminalActionCodes = YES;	/*Whether to support terminal behavior code 1*/
	termconfig->bDefActCodesBefore1stGenAC = NO;/*Is the default behavior code prior to FirstGenerateAC ?*/
	termconfig->bDefActCodesAfter1stGenAC = YES;/*Is the default behavior code after FirstGenerateAC ?*/
	/**<Completion Processing*/
	termconfig->bForceOnline= YES;			/*Whether to allow forced online 1*/
	termconfig->bForceAccept = NO;			/*Whether to allow forced acceptance of transactions 1*/
	termconfig->bAdvices = YES;				/*Whether to support notification 0*/
	termconfig->bIISVoiceReferal = YES;		/*Whether to support the voice reference initiated by the card issuer ?*/
	termconfig->bBatchDataCapture = YES;	/*Whether to support batch data collection*/
	termconfig->bDefaultTDOL = YES;			/*Is there a default? TDOL*/
	termconfig->bAccountSelect = NO;		/*Whether to support account selection*/
}


void TestDownloadAID(TERMINALAPPLIST *TerminalApps)
{
	int i = 0;
	int count = 20;

	APP_TRACE( "TestDownloadAID" );
	memset(TerminalApps,0x00,sizeof(TERMINALAPPLIST));	
	TerminalApps->bTermAppCount = 20;//AID length
	memcpy(TerminalApps->TermApp[0].AID, "\xA0\x00\x00\x00\x01\x10\x10", 7);//AID
	TerminalApps->TermApp[0].AID_Length = 7;
	memcpy(TerminalApps->TermApp[1].AID, "\xA0\x00\x00\x00\x03\x10\x10", 7);
	TerminalApps->TermApp[1].AID_Length = 7;
	memcpy(TerminalApps->TermApp[2].AID, "\xA0\x00\x00\x00\x03\x20\x10", 7);
	TerminalApps->TermApp[2].AID_Length = 7;
	memcpy(TerminalApps->TermApp[3].AID, "\xA0\x00\x00\x00\x03\x20\x20", 7);
	TerminalApps->TermApp[3].AID_Length = 7;
	memcpy(TerminalApps->TermApp[4].AID, "\xA0\x00\x00\x00\x03\x80\x10", 7);
	TerminalApps->TermApp[4].AID_Length = 7;
	memcpy(TerminalApps->TermApp[5].AID, "\xA0\x00\x00\x00\x04\x10\x10", 7);
	TerminalApps->TermApp[5].AID_Length = 7;
	memcpy(TerminalApps->TermApp[6].AID, "\xA0\x00\x00\x00\x04\x99\x99", 7);
	TerminalApps->TermApp[6].AID_Length = 7;
	memcpy(TerminalApps->TermApp[7].AID, "\xA0\x00\x00\x00\x04\x30\x60", 7);
	TerminalApps->TermApp[7].AID_Length = 7;
	memcpy(TerminalApps->TermApp[8].AID, "\xA0\x00\x00\x00\x04\x60\x00", 7);
	TerminalApps->TermApp[8].AID_Length = 7;
	memcpy(TerminalApps->TermApp[9].AID, "\xA0\x00\x00\x00\x05\x00\x01", 7);
	TerminalApps->TermApp[9].AID_Length = 7;
	memcpy(TerminalApps->TermApp[10].AID, "\xA0\x00\x00\x00\x25\x01", 6);
	TerminalApps->TermApp[10].AID_Length = 6;
	memcpy(TerminalApps->TermApp[11].AID, "\xA0\x00\x00\x00\x29\x10\x10", 7);
	TerminalApps->TermApp[11].AID_Length = 7;
	memcpy(TerminalApps->TermApp[12].AID, "\xA0\x00\x00\x00\x42\x10\x10", 7);
	TerminalApps->TermApp[12].AID_Length = 7;
	memcpy(TerminalApps->TermApp[13].AID, "\xA0\x00\x00\x00\x42\x20\x10", 7);
	TerminalApps->TermApp[13].AID_Length = 7;
	memcpy(TerminalApps->TermApp[14].AID, "\xA0\x00\x00\x00\x65\x10\x10", 7);
	TerminalApps->TermApp[14].AID_Length = 7;
	memcpy(TerminalApps->TermApp[15].AID, "\xA0\x00\x00\x01\x21\x10\x10", 7);
	TerminalApps->TermApp[15].AID_Length = 7;
	memcpy(TerminalApps->TermApp[16].AID, "\xA0\x00\x00\x01\x21\x47\x11", 7);
	TerminalApps->TermApp[16].AID_Length = 7;
	memcpy(TerminalApps->TermApp[17].AID, "\xA0\x00\x00\x01\x41\x00\x01", 7);
	TerminalApps->TermApp[17].AID_Length = 7;
	memcpy(TerminalApps->TermApp[18].AID, "\xA0\x00\x00\x01\x52\x30\x10", 7);
	TerminalApps->TermApp[18].AID_Length = 7;
	memcpy(TerminalApps->TermApp[19].AID, "\xA0\x00\x00\x03\x33\x01\x01\x01", 8);
	TerminalApps->TermApp[19].AID_Length = 8;
	for(i=0; i<20; i++)
	{
		TerminalApps->TermApp[i].bTerminalPriority = 0x03;	//Terminal priority
		TerminalApps->TermApp[i].bMaxTargetPercentageInt = 0x00;/*Offset randomly selected maximum target percentage*/
		TerminalApps->TermApp[i].bTargetPercentageInt = 0x00;/*Randomly selected target percentage*/
		memcpy(TerminalApps->TermApp[i].abTFL_International, "\x00\x00\x3A\x98", 4);/* Terminal minimum */
		memcpy(TerminalApps->TermApp[i].abThresholdValueInt, "\x00\x00\x13\x88", 4);/*Offset randomly selected threshold*/
		memcpy(TerminalApps->TermApp[i].abTerminalApplVersion, "\x00\x96", 2);/* Terminal application version */
		memcpy(TerminalApps->TermApp[i].TAC_Default, "\x00\x00\x00\x00\x00", 5);/* TAC Default data format (n5) */ 
		memcpy(TerminalApps->TermApp[i].TAC_Denial, "\x00\x00\x00\x00\x00", 5);/* TAC Refuse: data format (n5) */
		memcpy(TerminalApps->TermApp[i].TAC_Online, "\x00\x00\x00\x00\x00", 5);/* TAC Online: data format (n5) */
		memcpy(TerminalApps->TermApp[i].abTrnCurrencyCode, COUNTRYCODE, 2);/* Currency code tag: 5F2A */
		memcpy(TerminalApps->TermApp[i].abTerminalCountryCode, COUNTRYCODE, 2);/* Country code terminal tag: 9F1A */
		TerminalApps->TermApp[i].abTrnCurrencyExp = 0x02;/* tag: 5F36 */
		memcpy(TerminalApps->TermApp[i].abEC_TFL, "\x00\x00\x00\x20\x00", 6);/* Terminal electronic cash transaction limit tag: 9F7B n12*/
		memcpy(TerminalApps->TermApp[i].abRFOfflineLimit, "\x00\x00\x00\x20\x00", 6);/*Contactless offline minimum :DF19*/
		memcpy(TerminalApps->TermApp[i].abRFTransLimit, "\x00\x00\x02\x00\x00", 6);/*Contactless transaction limit:DF20*/
		memcpy(TerminalApps->TermApp[i].abRFCVMLimit, "\x00\x00\x00\x10\x00", 6);/*Terminal performs CVM quota: DF21*/
		memcpy(TerminalApps->TermApp[i].abDDOL, "\x9F\x37\x04", 3);/* TDOL */
		TerminalApps->TermApp[i].DDOL_Length = 0x03;/* TDOL Length */
		TerminalApps->TermApp[i].TerminalType = 0x22;/* Terminal type: data format (n 3) */
		memcpy(TerminalApps->TermApp[i].TerminalCap, "\xE0\xE1\xC8", 3);/* Terminal capability: data format (n 3) */		
		TerminalApps->TermApp[i].cOnlinePinCap = 0x01;/* Terminal online pin capability */
	}

}

int upay_consum( void )
{
	const char *title = "SALE";
	int ret;
	long long amt;
	char samt[20] = {0};
	st_read_card_in *card_in =NULL;
	st_read_card_out *card_out =NULL;
	TERMCONFIG termconfig={0};
	TERMINALAPPLIST TerminalApps={0};
// 	CAPUBLICKEY pkKey={0};

	APP_TRACE( "upay_consum" );

	//input amount
	//amt = inputamount_page(title, 6, 60000);
	//if ( amt <= 0 ) return -1;
	amt = inputamount_page(title, 6, 90000);
	if(amt <= 0)
	{
		return -1;
	}

	sprintf(samt, "%.02f", amt/100.00);
	if (lcd_get_sublcd_probe() == 1)
	{
		xgui_messagebox_show("Scan code", "See the big LCD", "", "confirm" , 300);		
		lcd_set_index(0);
	}	
	ret = showQr2(samt);	
	if (ret == 1)//Scan the code successfully and press the confirm button
	{

	}
	else if (ret == 2)//Find a non-contact card
	{
		card_in=(st_read_card_in *)MALLOC(sizeof(st_read_card_in));
		memset(card_in,0x00,sizeof(st_read_card_in));
		//Set card_in
		card_in->trans_type=EMV_SALE;
		card_in->pin_input=0;
		strcpy(card_in->title, title);
		strcpy(card_in->card_page_msg, "Pls swipe card");//Swipe interface prompt information, a line of 20 characters, up to two lines, automatic branch.
		sprintf(card_in->amt, "%lld" , amt);
		card_in->card_mode = READ_CARD_MODE_RF;	// Card reading method
		card_in->card_timeover = 60000;	// Card reading timeout ms

		if (first == 0)
		{
			first = 1;
			TestSetTermConfig(&termconfig);
			EMV_TermConfigInit(&termconfig);//Init EMV terminal parameter
			TestDownloadAID(&TerminalApps);
			EMV_PrmClearAIDPrmFile();
			EMV_PrmSetAIDPrm(&TerminalApps);//Set AID
			// 	EMV_PrmSetCAPK(&pkKey);//Set CAPK	
		}

		APP_TRACE( "emv_read_card" );
		card_out= (st_read_card_out *)MALLOC(sizeof(st_read_card_out));
		memset(card_out, 0, sizeof(st_read_card_out));

		ret = emv_read_card(card_in, card_out);

		if (lcd_get_sublcd_probe() == 1)
		{
			lcd_set_index(1);
		}

		if(EMVAPI_RET_ARQC == ret)
		{
			xgui_messagebox_show("", "Online Request" , "" , "ok" , 0);
		}
		else if(EMVAPI_RET_TC == ret)
		{
			xgui_messagebox_show("", "Approved" , "" , "ok" , 0);
		}
		else if(EMVAPI_RET_AAC == ret)
		{
			xgui_messagebox_show("", "Declined" , "" , "ok" , 0);
			FREE(card_in);
			FREE(card_out);
			return 0;
		}
		else if(EMVAPI_RET_AAR == ret)
		{
			xgui_messagebox_show("", "Terminate" , "" , "ok" , 0);
			FREE(card_in);
			FREE(card_out);
			return 0;
		}
		else
		{
			xgui_messagebox_show("", "Cancel" , "" , "ok" , 0);
			FREE(card_in);
			FREE(card_out);
			return 0;
		}

		APP_TRACE( "-----------------------card_info---------------------------" );
		APP_TRACE( "card_type:%d\r\n", card_out->card_type );
		APP_TRACE("trackb:%s\r\n", card_out->track2);
		APP_TRACE("trackc:%s\r\n", card_out->track3);
		APP_TRACE("pan:%s\r\n", card_out->pan);
		APP_TRACE("expdate:%s\r\n", card_out->exp_data);
		APP_TRACE("vChName:%s\r\n", card_out->vChName);
		APP_TRACE("ic_data_len:%d\r\n", card_out->ic_data_len);
		APP_TRACE_BUFF_TIP(card_out->ic_data, card_out->ic_data_len, "ic_data:");

		xgui_messagebox_show("track2", card_out->track2 , "" , "ok" , 0);
		xgui_messagebox_show("pan", card_out->pan , "" , "ok" , 0);
		xgui_messagebox_show("expdate", card_out->exp_data , "" , "ok" , 0);

		FREE(card_in);
		FREE(card_out);

		xgui_messagebox_show("Sale", "OK" , "" , "confirm" ,  15000);
	}

	if (lcd_get_sublcd_probe() == 1)
	{
		lcd_set_index(1);
	}
}

