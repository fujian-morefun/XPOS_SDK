#include "sdk_tts.h"
//#define MP3_FILE	"data\\1.mp3"

// Play unit 0 = hundred 1 = thousand 2 = million 3= One hundred thousand 4=Ten million
static void sdk_tts_play_unit(int index)
{
	char filename[16];
	sprintf(filename, "unit%d", index);
	Play_Voice(filename);	
}

// Play the numbers 0-19 20-90
static void sdk_tts_play_num(int num)
{
	char filename[16];

	if(num == 99){
		strcpy(filename, "numdot");
	}
	else{
		sprintf(filename, "num%d", num);
	}
	Play_Voice(filename);
}

// Play less than a thousand
static void sdk_tts_play_lt(int amt)
{
	int m;


	m = amt / 100;
	if(m >0){
		sdk_tts_play_num(m);
		sdk_tts_play_unit(0);		// hundred 
	}
	
	amt = amt % 100;
	if(amt > 20){ //  greater than 20
		m = amt / 10;
		sdk_tts_play_num(m * 10);	// Tens first digits
		amt = amt % 10;
	}
	sdk_tts_play_num(amt);   // Less than 20 direct play
}


void sdk_tts_play_amt_india(int amt)
{
	int m;


	if(amt >= 10000000){	// //If it is more than Ten million,
		m = amt / 10000000;
		sdk_tts_play_lt(m);	//  play the number of more than Ten million first
		sdk_tts_play_unit(4);	//plus the  "lakh"
		amt = amt % 10000000;		// Remove more than one million of the amount
	}

	if(amt >= 100000){	// //If it is more than One hundred thousand,
		m = amt / 100000;
		sdk_tts_play_lt(m);	//  play the number of more than One hundred thousand first
		sdk_tts_play_unit(3);	//plus the crore
		amt = amt % 100000;		// Remove more than One hundred thousand of the amount
	}

	// Determine if it is more than a thousand
	if(amt > 1000){		
		m = amt / 1000;
		sdk_tts_play_lt(m);		// play a part of a thousand or more
		sdk_tts_play_unit(1);	// play a thousand
		amt = amt % 1000;		
	}

	sdk_tts_play_lt(amt);			// Play numbers below a thousand

}



void sdk_tts_play_amt_en(int amt)
{
	int m;


	
	if(amt > 1000000){	// //If it is more than one million,
		m = amt / 1000000;
		sdk_tts_play_lt(m);	//  play the number of more than one million first
		sdk_tts_play_unit(2);	//plus the million
		amt = amt % 1000000;		// Remove more than one million of the amount
	}


	// Determine if it is more than a thousand
	if(amt > 1000){		
		m = amt / 1000;
		sdk_tts_play_lt(m);		// play a part of a thousand or more
		sdk_tts_play_unit(1);	// play a thousand
		amt = amt % 1000;		
	}
	
	sdk_tts_play_lt(amt);			// Play numbers below a thousand


}


void sdk_tts_test()
{
	Play_Voice("Payment successful, welcome to visit next time");
	
}
