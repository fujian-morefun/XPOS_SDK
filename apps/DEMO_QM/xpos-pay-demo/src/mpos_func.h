#pragma once

#include "mpos_pub.h"

typedef struct __st_qr_data{
	st_pkt_info pkt_info;

	char amt[20];	  //The transaction amount
	char qrdata[129]; //qr data
	char text[64];	//Payment success message
	//int x;		//byte
	//int y;		//Row 1-8
	//int size;		//0(small),1(normal),2(big)
}st_qr_data;


#define	MPOS_RESULT_SUCC			"00"	//Successful processing
#define	MPOS_RESULT_NOT_SUPPORTED	"01"	//Instruction number is not supported
#define	MPOS_RESULT_PARAM_ERR		"02"	//Parameter error
#define MPOS_RESULT_LRC_ERR			"03"  	//LRC Verification failed
#define MPOS_RESULT_TIMEOUT			"04"	//Time out
#define MPOS_RESULT_OTHER_ERR		"05"	//Other errors

enum{
	MPOS_PAY_ITEM_TYPE = 0,				// Transaction type  01 Set QR code data 02 Set device date time 03 Payment success message    
	MPOS_PAY_ITEM_TIMEOVER,				// Overtime time
	MPOS_PAY_ITEM_AMT,					// The transaction amount
	MPOS_PAY_ITEM_QRDATA,				// QR data
	MPOS_PAY_ITEM_TEXT,					// Payment success message
	MPOS_PAY_ITEM_DATETIME,				// Device date time

	//	MPOS_PAY_ITEM_RESULE = 50,		// Transaction result
};

st_qr_data  * mpos_func_get_qr_data();
int mpos_func_proc(unsigned char * data , int len);