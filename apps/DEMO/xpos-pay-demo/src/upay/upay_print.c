#include "../app_def.h"

void upay_print_line(char * head, char* val)
{
	UPrint_SetFont(8, 2, 2);
	UPrint_Str(head,1, 1, 0);
	UPrint_Str(val, 1,1, 1);
}
int upay_print_proc( st_card_info *card_info )
{
	//char *p;
	int ret = 0;
	long long amt = 0;
	char samt[32]={0};



	while(1)
	{
		ret = UPrint_Init();


	//UPrint_SetDensity(3);//Set print density to 3 normal
	
		if (ret == UPRN_OUTOF_PAPER)
		{
			gui_messagebox_show( "Print" , "No paper" , "" , "confirm" , 0);
			return 0;
		}		
		
		UPrint_SetDensity(3);//Set print density to 3 normal


		UPrint_SetFont(7, 2, 2);
		UPrint_StrBold("Sales Slip", 1,1,4, 1);//Centered large font print title,empty 4 lines

		upay_print_line("MERCHANT NAME:", "test");
		upay_print_line("MERCHANT NO.:", "123456789012345");
		upay_print_line("TERMINAL NO.:", "32565412");
		upay_print_line("OPERATOR NO.:", "01");
		upay_print_line("ISS NO.:", "0201");
		upay_print_line("ACQ NO.:", "0301");
		
		UPrint_SetFont(8, 2, 2);
		UPrint_Str("CARD NO.:",1, 1, 1);
		UPrint_SetFont(8, 3, 3);
		UPrint_StrBold(card_info->pan, 1,1, 4, 1); 

		UPrint_SetFont(8, 2, 2);
		UPrint_Str("TRANS TYPE",1, 1, 1);
		UPrint_SetFont(8, 3, 3);
		UPrint_Str(card_info->title, 1,1, 1 ); 

		UPrint_SetFont(8, 2, 2);
		upay_print_line("EXP DATE:", card_info->expdate);
		upay_print_line("BATCH NO.:", "000001");
		upay_print_line("VOUCHER NO.:", "000023");
		upay_print_line("AUTH NO.:", "125023");
		upay_print_line("REFER NO.:", "125023125023");
		upay_print_line("DATE/TIME:", "2018-03-02 10:11:06");

		UPrint_Str("AMOUNT",1, 1, 1);
		UPrint_SetFont(8, 3, 3);
		UPrint_Str("RMB ",1, 1, 0);	
		amt = atoll((const char *)card_info->amt);
		sprintf(samt, "%0.2f", amt/100.00);
		UPrint_Str(samt,1, 1, 1);

		UPrint_SetFont(8, 2, 2);
		UPrint_Feed(6);		// Print 6-point line blank
		UPrint_Str("CARD HOLDER SIGNATURE",1, 1, 1);
		UPrint_Feed(36);
		UPrint_Str("I ACKNOWLEDGE	SATISFACTORY RECEIPT OF RELATIVE GOODS/SERVICES",1, 1, 1);
		UPrint_Feed(24);
		UPrint_Str("---X---X---X---X---X---X---X---", 1,1, 1);
		UPrint_Feed(108);

		ret = UPrint_Start();// Output to printer
		if (ret == UPRN_SUCCESS)
		{
			gui_messagebox_show( "Print" , "Print Success" , "" , "confirm" , 0);
			break;
		}
		else if (ret == UPRN_OUTOF_PAPER)
		{
			if (gui_messagebox_show( "Print" , "No paper!\nLoad paper and press OK" , "cancel" , "confirm" , 0) != 1)
			{
				break;
			}
			//UPrint_Str(ENDLINE, 0, 1);
			//Sys_Sleep(1000);
		}
		else if (ret == UPRN_FILE_FAIL)
		{
			gui_messagebox_show( "Print" , "Open File Fail" , "" , "confirm" , 0);
			break;
		}
		else if (ret == UPRN_DEV_FAIL)
		{
			gui_messagebox_show( "Print" , "Printer device failure" , "" , "confirm" , 0);
			break;
		}
		else
		{
			gui_messagebox_show( "Print" , "Printer unknown fault" , "" , "confirm" , 0);
			break;
		}
	}
	return 0;
}

