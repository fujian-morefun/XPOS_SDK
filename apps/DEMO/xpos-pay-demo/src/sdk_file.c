#include "app_def.h"


#define FILE_NAME	"test.ini"


void fileTest()
{
	int ret = 0;
	int fp;
	char *str = "1234567890";
	char buff[50]={0};
	char buffer[32]={0};

	ret = UFile_OpenCreate(FILE_NAME, FILE_PRIVATE, FILE_CREAT, &fp, 0);//File open / create
	if( ret == UFILE_SUCCESS){
		UFile_Write(fp, str, strlen(str));// write 10 byte "1234567890"
		UFile_Close(fp);				  // Close the file
		sprintf(buffer, "Write: %s", str);
		gui_messagebox_show( "FileTest" , buffer , "" , "confirm" , 0);
	}
	else{
		gui_messagebox_show( "FileTest" , "File open or create fail" , "" , "confirm" , 0);
	}
	ret = UFile_GetLength(FILE_NAME,FILE_PRIVATE);
	memset(buffer,0x00,sizeof(buffer));
	sprintf(buffer, "file length: %d", ret);
	gui_messagebox_show( "FileTest" , buffer , "" , "confirm" , 0);
	ret = UFile_OpenCreate(FILE_NAME, FILE_PRIVATE, FILE_RDWR, &fp, 0);
	if( ret == UFILE_SUCCESS){
		UFile_Lseek(fp, 0, 0);	// seek 0 
		memset(buff, 0, sizeof(buff));
		UFile_Read(fp, buff, 5);		// read 5 byte
		sprintf(buffer, "Read 5: %s", buff);
		gui_messagebox_show( "FileTest" , buffer , "" , "confirm" , 0);

		UFile_Lseek(fp, 8, 0);	// move 8 
		memset(buff, 0, sizeof(buff));
		UFile_Read(fp, buff, 2);		// read 2 byte
		//sdk_log_out("buff2:%s\r\n", buff);// log out "90"
		sprintf(buffer, "Read 2: %s", buff);
		gui_messagebox_show( "FileTest" , buffer , "" , "confirm" , 0);
		UFile_Close(fp);				// Close the file
	}
	else{
		gui_messagebox_show( "FileTest" , "File open or create fail" , "" , "confirm" , 0);
	}

	UFile_Remove(FILE_NAME, FILE_PUBLIC);//Delete file
}

