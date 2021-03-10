
#include "../app_def.h"


#define NORMAL_TIME_OUT			60000
#define ENTER_AMOUNT_TIME_OUT	90000
#define AMOUNT_MAX_LEN			9

static void card_in_config(char*title, st_read_card_in *card_in)
{
	//Set card_in
	memset(card_in,0x00,sizeof(st_read_card_in));//initiate with all zeros
	card_in->trans_type=0;//EMV_SALE£¨0x00£© or EMV_CASHBACK£¨0x09£©;
	card_in->pin_input=1;
	card_in->pin_max_len=12;
	card_in->key_pid = SEC_DUKPT_FIELD;//SEC_MKSK_FIELD	0x01 SEC_DUKPT_FIELD 0x02
	card_in->pin_mksk_gid=-1;//The key index of MKSK; -1 is not encrypt
	card_in->pin_dukpt_gid=0;//The key index of DUKPT PIN KEY
	card_in->data_dukpt_gid=1;//The key index of DUPKT Track data KEY	
	card_in->pin_timeover=NORMAL_TIME_OUT;
	strcpy(card_in->title, title);
	//strcpy(card_in->card_page_msg,  "\xD9\x84\xD8\xA7\xDA\xAF");
	strcpy(card_in->card_page_msg, "Please insert/swipe");//Swipe interface prompt information, a line of 20 characters, up to two lines, automatic branch.
	card_in->forceIC=1;
	card_in->show_PAN=0;    
	card_in->card_mode = READ_CARD_MODE_MAG | READ_CARD_MODE_IC | READ_CARD_MODE_RF;	// Card reading method
	card_in->card_timeover = NORMAL_TIME_OUT;	// Card reading timeout ms

	return;
}
int upay_consum( void )
{
	char *title = "SALE";
	int ret;
	float famt = 0.00;
    long long namt = 0;
	st_read_card_in *card_in =NULL;
	st_read_card_out *card_out =NULL;
	st_card_info card_info={0};
	st_input_pin st_msg;
	SYS_TRACE( "upay_consum" );

	card_in=(st_read_card_in *)Util_Malloc(sizeof(st_read_card_in));
	if(card_in==NULL)
		return FAIL;

	card_in_config(title,card_in);//config before card reading

    namt = inputamount_page(title, AMOUNT_MAX_LEN, ENTER_AMOUNT_TIME_OUT);//Amount entering
	if(namt <= 0)//INPUT_INPUT_RET_TIMEOVER or INPUT_INPUT_RET_QUIT
    {
		Util_Free(card_in);
        return FAIL;
    }
    sprintf(card_in->amt, "%lld" , namt);

	card_out= (st_read_card_out *)Util_Malloc(sizeof(st_read_card_out));
    if(card_out==0)
	{
		Util_Free(card_in);
		return FAIL;
	}
	famt = (float)namt/100;
	memset(&st_msg,0x00,sizeof(st_input_pin));
	strcpy(st_msg.szFirstLine,"SALE");
	sprintf(st_msg.szSecLine," AMOUNT INR : %.2f",famt);
	strcpy(st_msg.szThirdLine,"   ENTER PIN");
	strcpy(st_msg.szFourthLine,"PIN length(4-16)");	//ERRMSG
	st_msg.PinType = 0;
	//st_msg.IsErrShow = 1;
	//EMV_SetPinInputMsg(st_msg);	//Custom interface
	ret = upay_readcard_proc(card_in, card_out);//card reading process

	//save card information to print
	strcpy(card_info.amt, card_in->amt);
	strcpy(card_info.title, card_in->title);
	strcpy(card_info.pan, card_out->pan);
	strcpy(card_info.expdate, card_out->exp_data);

	//Util_Free memory
	Util_Free(card_in);
	Util_Free(card_out);

	if(EMVAPI_RET_SUCC == ret)//approved transaction will print receipt
	{
		upay_print_proc(&card_info);			// Printout
	}

	return ret;
}

