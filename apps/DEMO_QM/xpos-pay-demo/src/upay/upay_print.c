#include "upay_consum.h"
#include "pub\osl\inc\osl_log.h"
#include "pub\osl\inc\osl_print.h"
//#include "emv\inc\emv_tag.h"

#define PRINT_LINE_SEPARATE ("-----------------------------\r\n")
/*
static void getprintstytle(int s)
{
	if(s == 1){	//16
		osl_print_add(PRINT_FONT_TYPE(111111));
	}
	else if(s == 2){	//24
		osl_print_add(PRINT_FONT_TYPE(062211));
	}
	else if(s == 3){	//32
		osl_print_add(PRINT_FONT_TYPE(062412));
	}			
	else if(s == 4){	//48
		osl_print_add(PRINT_FONT_TYPE(163322));
	}
	else if(s == 5){	//8-16
		osl_print_add(PRINT_FONT_TYPE(151111));
	}
}


static void getprintitemline(char * head, char* val)
{
	getprintstytle(2);
	osl_print_addex(head);
	osl_print_add(" ");

	getprintstytle(2);
	osl_print_add(val);
	osl_print_add("\r\n");
}


int upay_print( cardreader *info )
{
	char tmp[512];
	char *p;
	char * field_44;
	char * field_63;

	if(osl_get_is_printer() == 0){
		comm_page_msg_box("Prompt", "Successful trade" , "" , "confirm" ,  15000);
		return 0;
	}

	getprintstytle(4);
	osl_print_add(PRINT_ALIGN(1));


	osl_print_add("Sales Slip\r\n");

	osl_print_add(PRINT_ALIGN(0));

	getprintstytle(2);
	osl_print_add(PRINT_LINE_SEPARATE);

	//get_setting_str(TERM_MERCHANT_NAME , tmp , sizeof(tmp));
	getprintitemline("MERCHANT NAME:", "test");

	getprintitemline("MERCHANT NO.:", "123456789012345");
	getprintitemline("TERMINAL NO.:", "32565412");

	getprintitemline("OPERATOR NO.:", "01");

	//44域为空的情况不发卡行和收单行打印空出；
	getprintitemline("ISS NO.:", "0201");
	getprintitemline("ACQ NO.:", "0301");

	//getprintitem("卡号(CARD NUMBER)", tmp);
	getprintstytle(2);
	osl_print_addex("CARD NO.:\r\n");
	getprintstytle(3);
	osl_print_add(info->sPan ); 
	osl_print_add("\r\n");

	getprintstytle(2);
	osl_print_addex("TRANS TYPE\r\n");
	getprintstytle(3);
	osl_print_add( info->title ); 
	osl_print_add("\r\n");

	getprintitemline("EXP DATE:", "0729");


	getprintitemline("BATCH NO.:", "000001");
	getprintitemline("VOUCHER NO.:", "000023");
	getprintitemline("AUTH NO.:", "125023");
	getprintitemline("REFER NO.:", "125023125023");

	getprintitemline("DATE/TIME:", "2018-03-02 10:11:06");

	getprintstytle(2);
	osl_print_addex("AMOUNT\r\n");

	getprintstytle(4);
	osl_print_add("RMB ");	
	sprintf(tmp , "%0.2f",  info->amt/100.0);
	osl_print_add(tmp);
	osl_print_add("\r\n");


	getprintstytle(2);
	osl_print_add(PRINT_LINE_SEPARATE);

	getprintitem("REFERENCE", "");

	cardreader_icdata_asc(info ,  EMV_TAG_9F06_TM_AID , tmp);
	getprintitemline("AID", tmp);

	cardreader_icdata_asc(info ,  EMV_TAG_9F26_IC_AC , tmp);
	getprintitemline("TC", tmp);


	cardreader_icdata_asc(info ,  EMV_TAG_95_TM_TVR , tmp);
	if (strlen(tmp)!=0)
	{
		getprintitemline("TVR", tmp);
	}
	else
	{
		getprintitemline("TVR", "0000000000");
	}
	cardreader_icdata_asc(info ,  EMV_TAG_9F36_IC_ATC , tmp);
	getprintitemline("ATC", tmp);

	getprintstytle(1);
	osl_print_add(PRINT_ROW_SPACE(6));
	osl_print_addex("CARD HOLDER SIGNATURE\r\n");
	osl_print_add(PRINT_ROW_SPACE(36));

	osl_print_add(PRINT_LINE_SEPARATE);

	osl_print_add("I ACKNOWLEDGE	SATISFACTORY RECEIPT OF RELATIVE GOODS/SERVICES\r\n");

	osl_print_add(PRINT_ROW_SPACE(24));

	getprintstytle(1);
	osl_print_add("---X---X---X---X---X--X--X--X--X--X--X--X--X--\r\n");

	getprintstytle(1);
	osl_print_add(PRINT_ROW_SPACE(108));


	PrintWriteWithPage();	
	return 0;
}


int upay_print_barcode( const char *code , long long amt )
{
	char tmp[512];
	char *p;
	char * field_44;
	char * field_63;

	if(osl_get_is_printer() == 0){
		comm_page_msg_box("Prompt", "Successful trade" , "" , "confirm" ,  15000);
		return 0;
	}

	getprintstytle(4);
	osl_print_add(PRINT_ALIGN(1));


	osl_print_add("Sales Slip\r\n");

	osl_print_add(PRINT_ALIGN(0));

	getprintstytle(2);
	osl_print_add(PRINT_LINE_SEPARATE);

	//get_setting_str(TERM_MERCHANT_NAME , tmp , sizeof(tmp));
	getprintitemline("MERCHANT NAME:", "test");

	getprintitemline("MERCHANT NO.:", "123456789012345");
	getprintitemline("TERMINAL NO.:", "32565412");

	getprintitemline("OPERATOR NO.:", "01");


	//getprintitem("卡号(CARD NUMBER)", tmp);
	getprintstytle(2);
	osl_print_addex("BAR CODE.:\r\n");
	getprintstytle(3);
	osl_print_add( code ); 
	osl_print_add("\r\n");

	getprintstytle(2);
	osl_print_addex("TRANS TYPE\r\n");
	getprintstytle(3);
	osl_print_add( "BarCode" ); 
	osl_print_add("\r\n");

	getprintitemline("EXP DATE:", "0729");


	getprintitemline("BATCH NO.:", "000001");
	getprintitemline("VOUCHER NO.:", "000023");
	getprintitemline("AUTH NO.:", "125023");
	getprintitemline("REFER NO.:", "125023125023");

	getprintitemline("DATE/TIME:", "2018-03-02 10:11:06");

	getprintstytle(2);
	osl_print_addex("AMOUNT\r\n");

	getprintstytle(4);
	osl_print_add("RMB ");	
	sprintf(tmp , "%0.2f",  amt/100.0);
	osl_print_add(tmp);
	osl_print_add("\r\n");


	getprintstytle(2);
	osl_print_add(PRINT_LINE_SEPARATE);

	getprintitem("REFERENCE", "");

	
	getprintstytle(1);
	osl_print_add(PRINT_ROW_SPACE(6));
	osl_print_addex("CARD HOLDER SIGNATURE\r\n");
	osl_print_add(PRINT_ROW_SPACE(36));

	osl_print_add(PRINT_LINE_SEPARATE);

	osl_print_add("I ACKNOWLEDGE	SATISFACTORY RECEIPT OF RELATIVE GOODS/SERVICES\r\n");

	osl_print_add(PRINT_ROW_SPACE(24));

	getprintstytle(1);
	osl_print_add("---X---X---X---X---X--X--X--X--X--X--X--X--X--\r\n");

	getprintstytle(1);
	osl_print_add(PRINT_ROW_SPACE(108));


	PrintWriteWithPage();	
	return 0;
}*/

