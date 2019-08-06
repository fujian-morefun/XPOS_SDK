#include "sdk_input.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/message.h"
#include "xGui/inc/xgui_key.h"
#include "pub/osl/inc/osl_hzk.h"

static const char *keybuff[11] = {
	"0 ","1","2АБВГабвг","3ДЕЁЖдеёж","4ЗИЙКзийк",
	"5ЛМНОлмно","6ПРСТпрст","7УФХЦуфхц","8ЫЬЭЮыьэю","9Яя",
	".,'?!\"-*@/\\:_;+&%#$=()<>"
};


static int sdk_getchar(char *buff, char *ch)
{
	int size = 1;
	if(osl_hzk_is_gbk_char((unsigned char *)buff) > 0){
		ch[0] = buff[0];
		ch[1] = buff[1];
		size = 2;
	}
	else{
		ch[0] = buff[0];
		size = 1;
	}

	ch[size] = 0;
	return size;
}

static int sdk_newchar(char * buff, int len)
{
	int i,j;
	int size;
	char ch1[8]={0};
	char ch2[8]={0};
	int offset = 1;

	if(len ==0) return len;

	if(buff[len -1] > 0xA0 && len >= 2) offset = 2;

	sdk_getchar(buff + len - offset, ch1);

	for(i=0; i< 11; i ++){
		size = strlen(keybuff[i]);
		for(j =0; j < size; ){
			j += sdk_getchar((char *)keybuff[i] + j, ch2);
			if(strcmp(ch1, ch2) == 0){
				if(j>= size) j = 0;
				sdk_getchar((char *)keybuff[i] + j, ch2);
				sprintf(buff + len - offset, "%s" , ch2);
				return strlen(buff);
			}
		}
	}
	return len;
}


int sdk_input_get_count(char *buff)
{
	int offset = 0;
	int count = 0;
	int size = strlen(buff);
	while(offset< size){
		offset ++;
		if(osl_hzk_is_gbk_char(buff + offset) > 0) offset ++;
		count ++;
	}
	return count;
}


int sdk_input(char *title,  char *buff,int min, int max, int mode, int timeover)
{
	MESSAGE pMsg;
	int len = 0;
	int ret;
	int tick1 = osl_GetTick();
	unsigned char pwdbuff[128]={0};
	int argot = mode & 0x100;
	int hzlen;

	mode =mode & 0xff;

	xgui_PostMessage(XM_GUIPAINT, 0 , 0);
	len = strlen(buff);
	if(len > max) buff[max] = 0;
	
	xgui_PostMessage(XM_GUIPAINT, 0 , 0);

	while(1){

		if (timeover> 0 && osl_CheckTimeover(tick1,timeover) != 0)		{
			ret = SDK_INPUT_RET_TIMEOVER;
			break;
		}

		if (xgui_GetMessageWithTime(&pMsg, 100) == MESSAGE_ERR_NO_ERR) {
			tick1 = osl_GetTick();

			if (pMsg.MessageId == XM_GUIPAINT) {
				xgui_BeginBatchPaint();
				xgui_ClearDC();
				xgui_SetTitle(title);
				
				if (mode == SDK_INPUT_MODE_PWD){
					memset(pwdbuff , '*' , len);
					pwdbuff[len] = 0;
					xgui_TextOut(0, xgui_GetLineTop(2), pwdbuff);
				}
				else{
					xgui_TextOut(0, xgui_GetLineTop(2), buff);
				}
				xgui_Page_OP_Paint("отменен" , "подтвердить");
				xgui_EndBatchPaint();
			}
			else if (pMsg.MessageId == XM_KEYPRESS) {
				if(argot !=0) argot_keyinput(pMsg.WParam);
				
				hzlen = sdk_input_get_count(buff);

				if (pMsg.WParam >= KEY_0 && pMsg.WParam <= KEY_9 && len < max){
					buff[len] = pMsg.WParam;
					len ++;
					buff[len] = 0;
					xgui_PostMessage(XM_GUIPAINT, 0 , 0);
				}
				else if (pMsg.WParam == KEY_XING && hzlen < max && (mode == SDK_INPUT_MODE_ALPHABET || mode == SDK_INPUT_MODE_IP)){
					buff[len] = '.';
					len ++;
					buff[len] = 0;
					xgui_PostMessage(XM_GUIPAINT, 0 , 0);
				}
				else if (pMsg.WParam == KEY_JING && hzlen > 0 && mode == SDK_INPUT_MODE_ALPHABET){
					len = sdk_newchar(buff, len);
					xgui_PostMessage(XM_GUIPAINT, 0 , 0);
				}
				else if (pMsg.WParam == KEY_BACKSPACE && len > 0)	{
					len --;
					if(buff[len] > 0xA0 && len >= 1) len --;
					buff[len] = 0;
					xgui_PostMessage(XM_GUIPAINT, 0 , 0);
				}
				else if (pMsg.WParam == KEY_OK && hzlen >= min && hzlen <= max)	{
					ret = SDK_INPUT_RET_OK;
					break;
				}
				else if (pMsg.WParam == KEY_QUIT)	{
					ret = SDK_INPUT_RET_QUIT;
					break;
				}
			}
		}
	}
	return ret ;
}



#include "driver/mf_rtc.h"
#include "pub/osl/inc/osl_print.h"

static void get_date_time(char *buff)
{
	struct rtc_time date_time;
	mf_rtc_get_time(&date_time);
	sprintf(buff , "%d-%02d-%02d %02d:%02d:%02d" , 
		date_time.tm_year , date_time.tm_mon , date_time.tm_mday,
		date_time.tm_hour , date_time.tm_min , date_time.tm_sec);
}


void sdk_print_item(char *head, char *data)
{
	osl_print_add(head);
	osl_print_add(":");
	osl_print_add(data);
	osl_print_add("\r\n");
}

void sdk_input_print(char * buff1 , char * buff2)
{

	int ret ; 
	char dt[32]={0};

	xgui_BeginBatchPaint();			
	xgui_ClearDC();
	xgui_TextOut_Win_Center("printing...");
	xgui_EndBatchPaint();

	
	osl_print_add(osl_print_line_space(4));
	osl_print_add(PRINT_FONT_TYPE(064422));
	osl_print_add(osl_print_align(1));						// Set center alignment
	osl_print_add("Проверить\r\n \r\n");				// Set the print content

	osl_print_add(PRINT_FONT_TYPE(062211));				// Set English font
	osl_print_add(osl_print_align(0));						// Set center alignment

	//有SN、时间，商户名称，金额等等



	get_date_time(dt);
	sdk_print_item("SN", "90122331234");
	sdk_print_item("время", dt);		// 时间
	sdk_print_item("Название фирмы", buff1);				// 商户名称
	sdk_print_item("деньги", buff2);

	osl_print_add("\r\n \r\n \r\n \r\n");

	ret = mf_thermal_printer_nopaper();						// check no paper

	if(ret == 1){
		xgui_messagebox_show( "Print" , "No paper" , "" , "confirm" , 0);
	}  
	else{
		osl_print_write(osl_print_get());						// Output to printer
	}

	osl_print_free();										// Release print buffer
}

int sdk_input_test()
{
	int ret;
	char buff1[16]={0};
	char buff2[16]={0};

	ret = sdk_input("Название фирмы",  buff1, 1, 10, SDK_INPUT_MODE_ALPHABET, 0);
	if(ret == SDK_INPUT_RET_OK){
		ret = sdk_input("деньги",  buff2, 1, 10, SDK_INPUT_MODE_IP, 0);
		if(ret == SDK_INPUT_RET_OK){
			sdk_input_print(buff1, buff2);
		}
	}

}