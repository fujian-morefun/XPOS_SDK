#include "xgui\inc\2ddraw.h"
#include "xgui\inc\message.h"
#include "xgui\inc\xgui_key.h"
#include "input_num_page.h"
#include "pub\common\misc\inc\mfmalloc.h"



int input_num_page(char *buff , char *title , int min  , int max , int timeover , char pw, char argot )
{
	MESSAGE pMsg;
	int len = 0;
	int ret;
	unsigned int tick1;
	unsigned char *pwdbuff;

	tick1 = osl_GetTick();							// Get current tick
	xgui_PostMessage(XM_GUIPAINT, 0 , 0);			// Send a paint message
	len = strlen(buff);

	pwdbuff = MALLOC(max + 1);
	memset(pwdbuff , 0, max + 1);

	while(1){

		if (timeover > 0)		{				// Detection timeout
			if(osl_CheckTimeover(tick1,timeover) != 0){
				ret = INPUT_NUM_RET_TIMEOVER;
				break;
			}
		}

		if (xgui_GetMessageWithTime(&pMsg, 100) == MESSAGE_ERR_NO_ERR) {	// Receive message
			if (pMsg.MessageId == XM_GUIPAINT) {
				xgui_BeginBatchPaint();
				xgui_ClearDC();				// Clear full screen

				xgui_SetTitle(title);		//  Show title

				if (pw == 0){				// If not the password mode shows the actual string
					xgui_TextOut_Line_Left(buff , XGUI_LINE_TOP_1 );
				}
				else{			// If it is a password mode display string *
					memset(pwdbuff , '*' , len);
					pwdbuff[len] = 0;
					xgui_TextOut_Line_Left( pwdbuff, XGUI_LINE_TOP_1);
				}
				xgui_Page_OP_Paint("cancel" , "confirm");		// Show 2 buttons at the bottom
				xgui_EndBatchPaint();							// Output to the LCD screen
			}
			else if (pMsg.MessageId == XM_KEYPRESS) {		// key message
				tick1 = osl_GetTick();
                                if (argot == 1){
                                    argot_keyinput(pMsg.WParam);
				}
				if (pMsg.WParam >= KEY_0 && pMsg.WParam <= KEY_9){
					if (len < max)	{
						buff[len] = pMsg.WParam;
						len ++;
						buff[len] = 0;
						xgui_PostMessage(XM_GUIPAINT, 0 , 0);
					}
				}
				else if (pMsg.WParam == KEY_BACKSPACE)	{
					if (len > 0)	{
						len --;
						buff[len] = 0;
						xgui_PostMessage(XM_GUIPAINT, 0 , 0);
					}
				}
				else if (pMsg.WParam == KEY_OK)	{
					if (len <min){
						xgui_PostMessage(XM_GUIPAINT, 0 , 0);
					}

					if (len >=min && len <= max ){
						ret = INPUT_NUM_RET_OK;
						break;
					}
				}
				else if (pMsg.WParam == KEY_QUIT)	{
					ret = INPUT_NUM_RET_QUIT;
					break;
				}
			}
			else{
				xgui_proc_default_msg(&pMsg);	//  Let the system handle some common messages
			}
		}

	}	

	FREE(pwdbuff);
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
