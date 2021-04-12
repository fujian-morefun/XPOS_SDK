#include "app_def.h"

#define TEST_KEY_SIZE	16

static void showHexData(char*title,  char * data, int size)
{
	char msg[64]={0};
	int i;

	for(i = 0;i < size; i ++){
		sprintf(msg + strlen(msg), "%02X ", data[i]);
	}
	gui_messagebox_show(title, msg, "", "confirm" , 0);
}

void dukptTest()
{
	char init_key[TEST_KEY_SIZE] ={0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11};
	char init_ksn[10] ={0xFF,0xFF,0x98,0x76,0x54,0x32,0x10,0xE0,0x00,0x00};
	char key[TEST_KEY_SIZE]={0};
	char ksn[10]={0};
	char indata[8]={0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31};
	char outdata[8]={0};
	int gid = 0;
	int i = 0;
	static int init = 0;

	if (init == 0)
	{
		dukpt_init_ipek(gid, init_ksn, init_key);
		init = 1;
	}

	for(i=0; i<3; i++)
	{
		dukpt_prepare_key(gid, ksn); 
		showHexData("ksn", ksn, 10);

		showHexData("indata_enc", indata, 8);
		dukpt_3des_run(MKSK_ENCRYPT, indata, 8, outdata);
		showHexData("outdata_enc", outdata, 8);
		dukpt_3des_run(MKSK_DECRYPT, outdata, 8, indata);
		showHexData("outdata_dec", indata, 8);
	}
}

void mkskTest()
{
	char maink[TEST_KEY_SIZE] ={0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11};
	char pink[TEST_KEY_SIZE] ={0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22};
	char mack[TEST_KEY_SIZE] ={0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33};
	char magk[TEST_KEY_SIZE] ={0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44};
	char ind[16] = {0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55};

	char keyciphertext[TEST_KEY_SIZE];
	char outd[16];
	char kvc[8];		//	kvc is Key plaintext encryption eight 0x00
	int gid =0;			//	Key index 0-9

	gui_clear_dc();

	// Save the terminal master key plaintext
	mksk_save_plaintext_key(MKSK_MAINKEY_TYPE, gid, maink, kvc);	

	//Here you can check the kvc, it is main key plaintext encryption eight 0x00,
	showHexData("MAIN KEY KVC", kvc , 4);

	// Simulate server encryption key
	Util_Des(2, maink, (char *)pink, (char *)keyciphertext);
	Util_Des(2, maink, (char *)pink+8, (char *)keyciphertext+8);


	//Save the pin key ciphertext
	mksk_save_encrypted_key(MKSK_PINENC_TYPE, gid, keyciphertext, kvc);

	//Here you can check the kvc, it is pin key plaintext encryption eight 0x00,
	showHexData("PIN KEY KVC", kvc , 4);


	// Same save magkey and mackey
	Util_Des(2, maink, (char *)mack, (char *)keyciphertext);
	Util_Des(2, maink, (char *)mack+8, (char *)keyciphertext+8);

	mksk_save_encrypted_key(MKSK_MACENC_TYPE, gid, keyciphertext, kvc);


	Util_Des(2, maink, (char *)magk, (char *)keyciphertext);
	Util_Des(2, maink, (char *)magk+8, (char *)keyciphertext+8);
	mksk_save_encrypted_key(MKSK_MAGDEC_TYPE, gid, keyciphertext, kvc);


	// Use the pin key to encrypt data
	mksk_3des_run(MKSK_PINENC_TYPE, gid, MKSK_ENCRYPT, ind, sizeof(ind), outd);		
	showHexData("ENCRYPT", outd , sizeof(ind));

	// Use the pin key to decrypt data
	mksk_3des_run(MKSK_PINENC_TYPE, gid, MKSK_DECRYPT, ind, sizeof(ind), outd);
	showHexData("DECRYPT", outd , sizeof(ind));

	// Use the mackey key to calc mac
	sec_mac_proc(SEC_MKSK_FIELD, 0, SEC_MAC_X919_FORMAT, ind, sizeof(ind), outd, MKSK_MACENC_TYPE);
	showHexData("MAC", outd, sizeof(ind));

	gui_clear_dc();

	//main_page_lcd0_paint();
}

