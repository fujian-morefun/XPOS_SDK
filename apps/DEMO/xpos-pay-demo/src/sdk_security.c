#include "sdk_security.h"
#include "AppPub/mfd/mf_security.h"
#include "pub/des/inc/des.h"
#include "xGui/inc/messagebox.h"
#include "AppPub/mfd/mf_dukpt.h"
#include "pub/aes/inc/pub_aes.h"
//#include "pub/aes/inc/aes.h"
#include "libapi_xpos/inc/libapi_security.h"

#define TEST_KEY_SIZE	16


static void showHexData(char*title,  char * data, int size)
{
	char msg[256]={0};
	int i;

	for(i = 0;i < size; i ++){
		sprintf(msg + strlen(msg), "%02X ", data[i]);
	}
	xgui_messagebox_show(title, msg, "", "confirm" , 0);
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

	//dukpt_init_key(gid, init_ksn, init_key);
	for(i=0; i<3; i++)
	{
		dukpt_get_ksn(gid, ksn);
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
	// Test key in plaintext
	char maink[TEST_KEY_SIZE] ={0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11};
	char pink[TEST_KEY_SIZE] ={0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22};
	char mack[TEST_KEY_SIZE] ={0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33};
	char magk[TEST_KEY_SIZE] ={0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44};
	char ind[16] = {0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55};

	char keyciphertext[TEST_KEY_SIZE];
	char outd[16];
	char kvc[8];		//kvc is Key plaintext encryption eight 0x00
	int gid =0;		// Key index 0-9

	// Save the terminal master key plaintext
	mfsdk_save_plaintext_key(MFSDK_KT_MAINKEY, gid ,maink, kvc);	

	//Here you can check the kvc, it is main key plaintext encryption eight 0x00,
	showHexData("MAIN KEY KVC", kvc , 4);

	// Simulate server encryption key
	RunDes(MFSDK_ENCRYPT, ECB, (char *)pink, (char *)keyciphertext, TEST_KEY_SIZE, maink, TEST_KEY_SIZE);

	//Save the pin key ciphertext
	mfsdk_save_encrypted_key(MFSDK_KT_PINENC, gid, keyciphertext, kvc);

	//Here you can check the kvc, it is pin key plaintext encryption eight 0x00,
	showHexData("PIN KEY KVC", kvc , 4);

	// Same save magkey and mackey
	RunDes(MFSDK_ENCRYPT, ECB, (char *)mack, (char *)keyciphertext, TEST_KEY_SIZE, maink, TEST_KEY_SIZE);
	mfsdk_save_encrypted_key(MFSDK_KT_MACENC, gid, keyciphertext, kvc);

	RunDes(MFSDK_ENCRYPT, ECB, (char *)magk, (char *)keyciphertext, TEST_KEY_SIZE, maink, TEST_KEY_SIZE);
	mfsdk_save_encrypted_key(MFSDK_KT_MAGDEC, gid, keyciphertext, kvc);

	// Use the pin key to encrypt data
	mfsdk_3des_run(MFSDK_KT_PINENC, gid, MFSDK_ENCRYPT, ind, sizeof(ind), outd);		
	showHexData("ENCRYPT", outd , sizeof(ind));

	// Use the pin key to decrypt data
	mfsdk_3des_run(MFSDK_KT_PINENC, gid, MFSDK_DECRYPT, ind, sizeof(ind), outd);
	showHexData("DECRYPT", outd , sizeof(ind));

	// Use the magkey key to encrypt data
	mfsdk_3des_run(MFSDK_KT_MAGDEC, gid, MFSDK_ENCRYPT, ind, sizeof(ind), outd);		
	showHexData("ENCRYPT", outd , sizeof(ind));

	// Use the magkey key to decrypt data
	mfsdk_3des_run(MFSDK_KT_MAGDEC, gid, MFSDK_DECRYPT, ind, sizeof(ind), outd);
	showHexData("DECRYPT", outd , sizeof(ind));
}

void securityTest()
{
	dukptTest();
	//mkskTest();
	

}