#include "pub/osl/inc/osl_filedef.h"
#include "sdk_file.h"
#include "driver/mf_system.h"
#include "sdk_log.h"

#define FILE_NAME	"data\\test.ini"


static int init = 0;
void fileTest()
{
	int fp;
	char *str = "1234567890";
	char buff[16]={0};

	//if(init == 0){
	//	mf_file_init();		// Initialize file system
	//}

	fp = mf_file_open(FILE_NAME, FILE_CREAT_FLAG, FILE_WRITE_MODE);
	if(fp>=0){
		mf_file_write(fp, str, strlen(str));		// write 10 byte "1234567890"
		mf_file_close(fp);
	}

	fp = mf_file_open(FILE_NAME, FILE_READ_FLAG, FILE_READ_MODE);
	if(fp >= 0){
		
		mf_file_lseek(fp, 0, SEEK_SET);	// seek 0 
		memset(buff, 0, sizeof(buff));
		mf_file_read(fp, buff, 5);		// read 5 byte
		sdk_log_out("buff1:%s\r\n", buff);

		mf_file_lseek(fp, 8, SEEK_SET);	// move 8 
		memset(buff, 0, sizeof(buff));
		mf_file_read(fp, buff, 2);		// read 2 byte
		sdk_log_out("buff2:%s\r\n", buff);  // log out "90"

		mf_file_close(fp);
	}

}