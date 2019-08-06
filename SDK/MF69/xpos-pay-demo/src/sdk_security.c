#include "sdk_security.h"
#include "pub/des/inc/des.h"
#include "xGui/inc/messagebox.h"

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

void securityTest()
{
	// Test key in plaintext
/*	char maink[TEST_KEY_SIZE] ={0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11};
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
	showHexData("DECRYPT", outd , sizeof(ind));*/

}