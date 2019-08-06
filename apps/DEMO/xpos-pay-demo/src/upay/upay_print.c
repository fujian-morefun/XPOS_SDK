#include "upay_print.h"
#include "pub/osl/inc/osl_print.h"
#include "pub/tracedef.h"


void upay_print_stytle(int s)
{
	if(s == 1){	//16 dot matrix
		osl_print_add(osl_print_en_font_size(1));
		osl_print_add(osl_print_en_font_zoom(1,1));
	}
	else if(s == 2){	//24 dot matrix
		osl_print_add(osl_print_en_font_size(6));
		osl_print_add(osl_print_en_font_zoom(1,1));
	}
	else if(s == 3){	//32 dot matrix
		osl_print_add(osl_print_en_font_size(6));
		osl_print_add(osl_print_en_font_zoom(1,2));
	}			
	else if(s == 4){	//48 dot matrix
		osl_print_add(osl_print_en_font_size(6));
		osl_print_add(osl_print_en_font_zoom(2,2));
	}
	else if(s == 5){	//8-16 dot matrix
		osl_print_add(osl_print_en_font_size(5));
		osl_print_add(osl_print_en_font_zoom(1,1));
		
	}
}

//Add a line of print data
void upay_print_line(char * head, char* val)
{
	
	osl_print_add(head);
	osl_print_add(val);
	osl_print_add("\r\n");
}


int upay_print_proc( st_card_info *card_info )
{
	//char *p;
	int ret = 0;
	long long amt = 0;
	char samt[32]={0};

	if(osl_get_is_printer() == 0){
		xgui_messagebox_show("Sale", "OK" , "" , "confirm" ,  15000);
		return 0;
	}

	ret = mf_thermal_printer_nopaper();						// check no paper
	if(ret == 1)
	{
		xgui_messagebox_show( "Print" , "No paper" , "" , "confirm" , 0);
		return -1;
	}  

	osl_print_add(osl_print_align(1));		// Set center alignment
	upay_print_stytle(4);					// Set 48 dot matrix font
	osl_print_add("Sales Slip\r\n \r\n");	// Add a print title

	osl_print_add(osl_print_align(0));
	upay_print_stytle(2);					// // Set 24 dot matrix font
	upay_print_line("MERCHANT NAME:", "test");
	upay_print_line("MERCHANT NO.:", "123456789012345");
	upay_print_line("TERMINAL NO.:", "32565412");
	upay_print_line("OPERATOR NO.:", "01");
	upay_print_line("ISS NO.:", "0201");
	upay_print_line("ACQ NO.:", "0301");
	
	upay_print_stytle(2);
	osl_print_add("CARD NO.:\r\n");
	upay_print_stytle(3);
	osl_print_add(card_info->pan); 
	osl_print_add("\r\n");

	upay_print_stytle(2);
	osl_print_add("TRANS TYPE\r\n");
	upay_print_stytle(3);
	osl_print_add(card_info->title ); 
	osl_print_add("\r\n");

	upay_print_line("EXP DATE:", card_info->expdate);


	upay_print_line("BATCH NO.:", "000001");
	upay_print_line("VOUCHER NO.:", "000023");
	upay_print_line("AUTH NO.:", "125023");
	upay_print_line("REFER NO.:", "125023125023");
	upay_print_line("DATE/TIME:", "2018-03-02 10:11:06");

	upay_print_stytle(2);
	osl_print_add("AMOUNT\r\n");

	upay_print_stytle(4);
	osl_print_add("RMB ");	
	Ex_Str_Char12ToLong(&amt, (unsigned char *)card_info->amt);
	sprintf(samt, "%0.2f", amt/100.00);
	osl_print_add(samt);
	osl_print_add("\r\n");

	upay_print_stytle(1);
	osl_print_add(osl_print_row_space(6));		// Print 6-point line blank
	osl_print_add("CARD HOLDER SIGNATURE\r\n");
	osl_print_add(osl_print_row_space(36));
	osl_print_add("I ACKNOWLEDGE	SATISFACTORY RECEIPT OF RELATIVE GOODS/SERVICES\r\n");
	osl_print_add(osl_print_row_space(24));
	upay_print_stytle(1);
	osl_print_add("---X---X---X---X---X--X--X--X--X--X--X--X--X--\r\n");

	upay_print_stytle(1);
	osl_print_add(osl_print_row_space(108));


	osl_print_write(osl_print_get());		// Output to printer
	
	xgui_messagebox_show("", "printing...", "", "ok", 0);

	osl_print_free();

	return 0;
}
