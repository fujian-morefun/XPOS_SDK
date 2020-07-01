//#define DR_MP3_IMPLEMENTATION
//#include "dr_mp3.h"

#include "pub/osl/inc/osl_filedef.h"
#include "pub/osl/inc/osl_file_comm.h"

#define MP3_FILE	"data\\1.mp3"

#include "sdk_tts.h"
#include "pub/tracedef.h"
#include "driver/mf_misc.h"

#include "pub/osl/inc/osl_tts.h"






// Play unit 0 = hundred 1 = thousand 2 = million 3= One hundred thousand 4=Ten million
static void sdk_tts_play_unit(int index)
{
	char filename[16];
	sprintf(filename, "unit%d", index);
	osl_tts_play(filename);	
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
	osl_tts_play(filename);
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

	osl_tts_batch_begin();

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

	osl_tts_batch_end();
}



void sdk_tts_play_amt_en(int amt)
{
	int m;

	osl_tts_batch_begin();
	
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

	osl_tts_batch_end();
}


#ifdef WIN32
#define CPU_1903
#endif

void sdk_mp3_test()
{
/*
#ifdef CPU_1903
	drmp3_int16* pcmdata;
	char *mp3data;
	int dataSize;
	drmp3_uint64 pTotalFrameCount = 0;
	drmp3_config pConfig;

	pConfig.outputChannels = 1;
	pConfig.outputSampleRate = 16000;

	dataSize = File_GetLengthByName(MP3_FILE);

	APP_TRACE("dataSize:%d\r\n", dataSize);

	if(dataSize > 0){
		mp3data = malloc(dataSize);
		File_Read(MP3_FILE, mp3data, dataSize);

		pcmdata = drmp3_open_memory_and_read_pcm_frames_s16((const void*) mp3data, dataSize, &pConfig, &pTotalFrameCount, (const drmp3_allocation_callbacks*) 0);
		
		APP_TRACE("pTotalFrameCount:%d\r\n", pTotalFrameCount);

		drmp3_free(pcmdata, (const drmp3_allocation_callbacks*) 0);
		free(mp3data);
	}
	

#endif
	*/
}