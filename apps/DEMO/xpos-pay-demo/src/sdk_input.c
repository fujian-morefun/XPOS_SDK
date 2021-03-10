#include "app_def.h"

static const char *rusian_keybuff[11] = {
	"0 ","1","2§¡§¢§£§¤§Ñ§Ò§Ó§Ô","3§¥§¦§§§¨§Õ§Ö§×§Ø","4§©§ª§«§¬§Ù§Ú§Û§Ü",
	"5§­§®§¯§°§Ý§Þ§ß§à","6§±§²§³§´§á§â§ã§ä","7§µ§¶§·§¸§å§æ§ç§è","8§½§¾§¿§À§í§î§ï§ð","9§Á§ñ",
	".,'?!\"-*@/\\:_;+&%#$=()<>"
};


static int sdk_getchar(char *buff, char *ch)
{
	int size = 1;
	if(Util_hzk_is_gbk_char((unsigned char *)buff) > 0){
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
		size = strlen(rusian_keybuff[i]);
		for(j =0; j < size; ){
			j += sdk_getchar((char *)rusian_keybuff[i] + j, ch2);
			if(strcmp(ch1, ch2) == 0){
				if(j>= size) j = 0;
				sdk_getchar((char *)rusian_keybuff[i] + j, ch2);
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
		if(Util_hzk_is_gbk_char(buff + offset) > 0) offset ++;
		count ++;
	}
	return count;
}


int sdk_input(char *title,  char *buff,int min, int max, int mode, int timeover)
{
	st_gui_message pMsg;
	int len = 0;
	int ret;
	int tick1 = Sys_TimerOpen(timeover);
	unsigned char pwdbuff[128]={0};
	int argot = mode & 0x100;
	int hzlen;

	mode =mode & 0xff;

	gui_post_message(GUI_GUIPAINT, 0 , 0);
	len = strlen(buff);
	if(len > max) buff[max] = 0;
	
	gui_post_message(GUI_GUIPAINT, 0 , 0);

	while(1){

		if (timeover> 0 && Sys_TimerCheck(tick1) == 0)		{
			ret = SDK_INPUT_RET_TIMEOVER;
			break;
		}

		if (gui_get_message(&pMsg, 100) == 0) {
			tick1 = Sys_TimerOpen(timeover);

			if (pMsg.message_id == GUI_GUIPAINT) {
				gui_begin_batch_paint();
				gui_clear_dc();
				gui_set_title(title);
				
				if (mode == SDK_INPUT_MODE_PWD){
					memset(pwdbuff , '*' , len);
					pwdbuff[len] = 0;
					gui_text_out(0, GUI_LINE_TOP(2), pwdbuff);
				}
				else{
					gui_text_out(0, GUI_LINE_TOP(2), buff);
				}
				gui_page_op_paint("§à§ä§Þ§Ö§ß§Ö§ß" , "§á§à§Õ§ä§Ó§Ö§â§Õ§Ú§ä§î");//("cancel" , "confirm");
				gui_end_batch_paint();
			}
			else if (pMsg.message_id == GUI_KEYPRESS) {
				if(argot !=0) argot_keyinput(pMsg.wparam);
				
				hzlen = sdk_input_get_count(buff);

				if (pMsg.wparam >= GUI_KEY_0 && pMsg.wparam <= GUI_KEY_9 && len < max){
					buff[len] = pMsg.wparam;
					len ++;
					buff[len] = 0;
					gui_post_message(GUI_GUIPAINT, 0 , 0);
				}
				else if (pMsg.wparam == GUI_KEY_XING && hzlen < max && (mode == SDK_INPUT_MODE_ALPHABET || mode == SDK_INPUT_MODE_IP)){
					buff[len] = '.';
					len ++;
					buff[len] = 0;
					gui_post_message(GUI_GUIPAINT, 0 , 0);
				}
				else if (pMsg.wparam == GUI_KEY_XING && hzlen > 0 && mode == SDK_INPUT_MODE_ALPHABET){
					len = sdk_newchar(buff, len);
					gui_post_message(GUI_GUIPAINT, 0 , 0);
				}
				else if (pMsg.wparam == GUI_KEY_BACKSPACE && len > 0)	{
					len --;
					if(buff[len] > 0xA0 && len >= 1) len --;
					buff[len] = 0;
					gui_post_message(GUI_GUIPAINT, 0 , 0);
				}
				else if (pMsg.wparam == GUI_KEY_OK && hzlen >= min && hzlen <= max)	{
					ret = SDK_INPUT_RET_OK;
					break;
				}
				else if (pMsg.wparam == GUI_KEY_QUIT)	{
					ret = SDK_INPUT_RET_QUIT;
					break;
				}
			}
		}
	}
	return ret ;
}



void sdk_print_item(char *head, char *data)
{

	UPrint_Str(head,0,0,0);
	UPrint_Str(":",0,0,0);
	UPrint_Str(data,0,0,1);
}

void sdk_input_print(char * buff1 , char * buff2)
{

	int ret ; 
	char dt[32]={0};

	gui_begin_batch_paint();			
	gui_clear_dc();
	gui_text_out_win_center("printing...");
	gui_end_batch_paint();


	Sys_GetDateTime(dt);
	sdk_print_item("SN", "90122331234");
	sdk_print_item("§Ó§â§Ö§Þ§ñ", dt);		// time
	sdk_print_item("§¯§Ñ§Ù§Ó§Ñ§ß§Ú§Ö §æ§Ú§â§Þ§í", buff1);				// vendor name
	sdk_print_item("§Õ§Ö§ß§î§Ô§Ú", buff2);//amount

	UPrint_Feed(100);

	ret = UPrint_Init();						// check no paper

	if(ret == 1){
		gui_messagebox_show( "Print" , "No paper" , "" , "confirm" , 0);
	}  
	else{
		UPrint_Start();						// Output to printer
	}
}

int sdk_input_test()
{
	int ret;
	char buff1[16]={0};
	char buff2[16]={0};

	ret = sdk_input("§¯§Ñ§Ù§Ó§Ñ§ß§Ú§Ö §æ§Ú§â§Þ§í",  buff1, 1, 10, SDK_INPUT_MODE_ALPHABET, 0);//vendor name
	if(ret == SDK_INPUT_RET_OK){
		ret = sdk_input("§Õ§Ö§ß§î§Ô§Ú",  buff2, 1, 10, SDK_INPUT_MODE_IP, 0);//amount
		if(ret == SDK_INPUT_RET_OK){
			sdk_input_print(buff1, buff2);
		}
	}

}