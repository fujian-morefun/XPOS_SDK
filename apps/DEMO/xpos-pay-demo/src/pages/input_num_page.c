#include "../app_def.h"


int input_num_page(char *buff , char *title , int min  , int max , int timeover , char pw, char argot )
{
	st_gui_message pMsg;
	int len = 0;
	int ret;
	unsigned char *pwdbuff;
	unsigned int tick1 = Sys_TimerOpen(timeover);
	gui_post_message(GUI_GUIPAINT, 0 , 0);			// Send a paint message
	len = strlen(buff);

	pwdbuff = Util_Malloc(max + 1);
	memset(pwdbuff , 0, max + 1);

	while(1){

		if (timeover > 0)		{				// Detection timeout
			if(Sys_TimerCheck(tick1) == 0){
				ret = INPUT_NUM_RET_TIMEOVER;
				break;
			}
		}

		if (gui_get_message(&pMsg, 100) == 0) {	// Receive message
			if (pMsg.message_id == GUI_GUIPAINT) {
				gui_begin_batch_paint();
				gui_clear_dc();				// Clear full screen

				gui_set_title(title);		//  Show title

				if (pw == 0){				// If not the password mode shows the actual string
					gui_textout_line_left(buff , GUI_LINE_TOP(1) );
				}
				else{			// If it is a password mode display string *
					memset(pwdbuff , '*' , len);
					pwdbuff[len] = 0;
					gui_textout_line_left( pwdbuff, GUI_LINE_TOP(1));
				}
				gui_page_op_paint("cancel" , "confirm");		// Show 2 buttons at the bottom
				gui_end_batch_paint();							// Output to the LCD screen
			}
			else if (pMsg.message_id == GUI_KEYPRESS) {		// key message
				tick1 = Sys_TimerOpen(timeover);
                                if (argot == 1){
                                    argot_keyinput(pMsg.wparam);
				}
				if (pMsg.wparam >= GUI_KEY_0 && pMsg.wparam <= GUI_KEY_9){
					if (len < max)	{
						buff[len] = pMsg.wparam;
						len ++;
						buff[len] = 0;
						gui_post_message(GUI_GUIPAINT, 0 , 0);
					}
				}
				else if (pMsg.wparam == GUI_KEY_BACKSPACE)	{
					if (len > 0)	{
						len --;
						buff[len] = 0;
						gui_post_message(GUI_GUIPAINT, 0 , 0);
					}
				}
				else if (pMsg.wparam == GUI_KEY_OK)	{
					if (len <min){
						gui_post_message(GUI_GUIPAINT, 0 , 0);
					}

					if (len >=min && len <= max ){
						ret = INPUT_NUM_RET_OK;
						break;
					}
				}
				else if (pMsg.wparam == GUI_KEY_QUIT)	{
					ret = INPUT_NUM_RET_QUIT;
					break;
				}
			}
			else{
				gui_proc_default_msg(&pMsg);	//  Let the system handle some common messages
			}
		}

	}	

	Util_Free(pwdbuff);
	return ret ;
}

int m_InputPin(char *psCardNo,char *psAmt,char cMsgType,char *psPin)	/*Enter password interface function pointer*/	
{
	int nRet;
	long long nAmt;
	char msg[32]={0};
	char pin[13] = {0};
	int ret;
	long long amt;
	char title[64] = {0};

	//The kernel amount is hexadecimal and is used to indicate that conversion is required.
// 	Ex_Str_HexToAsc((unsigned char*)psAmt,12,0,(unsigned char*)msg);
// 	amt = ATOLL(msg);
// 	memset(msg,0x00,sizeof(msg));
// 	//Displayed when the amount is not empty, if the balance inquiry has no amount, it will not be displayed.
// 	if (amt!=0)
// 	{
// 		sprintf(msg  ,"%.2f" , amt/100.0);
// 	}

	if(3 == cMsgType)
	{
		strcpy(title, "Pls enter pswd");
	}
	else if(2 == cMsgType)
	{
		strcpy(title, "Pls again pswd");
	}
	else if (1 == cMsgType)
	{
		strcpy(title, "Pls last pswd");
	}
	else
	{
		strcpy(title, "Pls enter pswd");
	}

	ret = input_num_page(psPin, title, 4, 12, 60000, 1, 0);

	//comm_page_msg_show( "Reading card, please do not pull the card!");

	//security_encry_pin(psCardNo, pin , psPin);

	if (strlen(psPin) > 0){
		return strlen(psPin);
	}
	else{	//Do not enter pin
		return INPUT_NUM_RET_OK;
	}
}
