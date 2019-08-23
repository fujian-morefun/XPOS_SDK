#include "pub/osl/inc/osl_init.h"
#include "pub/inc/taskdef.h"
#include "ucosii/ucos_ii.h"
#include "driver/mf_driverlib.h"
#include "sdk_xgui.h"
#include "pub/osl/inc/osl_BaseParam.h"
#include "xGui/inc/2ddraw.h"
#include "xGui/inc/message.h"
#include "xGui/inc/xgui_key.h"
#include "xGui/inc/xgui_bmp.h"
#include "pub/common/misc/inc/mfmalloc.h"
#include "pub\tracedef.h"
#include "pub/osl/inc/osl_filedef.h"
#include "sdk_file.h"
#include "libapi_xpos/inc/libapi_emv.h"


#pragma data_alignment=8

#define LOGOIMG "data\\logo1.bmp"

/*
#define PACKED

#pragma pack(1)

typedef PACKED struct tagRGBQUAD {
	unsigned char    rgbBlue;
	unsigned char    rgbGreen;
	unsigned char    rgbRed;
	unsigned char    rgbReserved;
} RGBQUAD;


typedef PACKED struct tagBITMAPFILEHEADER {
	unsigned short    bfType;
	unsigned long   bfSize;
	unsigned short    bfReserved1;
	unsigned short    bfReserved2;
	unsigned long   bfOffBits;
}BITMAPFILEHEADER;

typedef PACKED struct tagBITMAPINFOHEADER{
	unsigned long      biSize;
	long       biWidth;
	long       biHeight;
	unsigned short       biPlanes;
	unsigned short       biBitCount;
	unsigned long      biCompression;
	unsigned long      biSizeImage;
	long       biXPelsPerMeter;
	long       biYPelsPerMeter;
	unsigned long      biClrUsed;
	unsigned long      biClrImportant;
} BITMAPINFOHEADER,  *PBITMAPINFOHEADER;
*/

#define _APP_TASK_SIZE		(1024+1024+1024)			// Thread stack size
#define _APP_TASK_PRIO		(_APP_TASK_MIN_PRIO + 3)	// Thread priority
static OS_STK pTaskStk[_APP_TASK_SIZE];					// Thread stack

/*
int osl_app_init(int flag)
{
	osl_log_init();
	mf_file_init();						// 文件系统初始化
	osl_TimerInit();					// 定时器初始化
	xgui_init();						// xgui初始化
	//ap_logo_page_show();
	osl_print_init();					// 打印初始化
	argot_init(KEY_JING ,KEY_XING);		                // 暗码初始化
	mf_sock_init();						// 网络初始化
	mf_model_init();        

	dukpt_init();
	InitKeyFile();

	if((flag & 0x01) != 0) tms_init();
	sc_set_otp_str("WG96#D@4");
	InitRpc();
	power_init();
	sc_set_check_app(0);				        // 禁用app检测			
	sc_init();						// 开盖检测初始化
	pt_init();
	ini_proc();						// 处理ini升级文件
	if((flag & 0x02) != 0) mf_file_space_task();

	return 0;
}*/


static void sys_init()
{
	osl_app_init(0);					// Application initialization
	mf_auxlcd_backlight(1);					// Lighting backlight
	osl_set_language(1);					// Set the English language
}

/*
char * xgui_load_bmp4bit1(char * filename , int *width , int *height)
{
	char *ret = 0;
	int fd ;
	fd = FILE_OPEN(filename,FILE_READ_FLAG,FILE_READ_MODE);

	if ( fd != FILE_OPEN_FAIL ){
		BITMAPFILEHEADER *pBitFile;
		BITMAPINFOHEADER *pBitInfo;
		int len = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		char *bmpfiledata = MALLOC(len);

		FILE_LSEEK(fd,0,SEEK_SET);
		FILE_READ( fd  , bmpfiledata, len );

		pBitFile = (BITMAPFILEHEADER*) bmpfiledata;
		pBitInfo = (BITMAPINFOHEADER*) ( bmpfiledata + sizeof(BITMAPFILEHEADER) );

		ret = MALLOC(pBitInfo->biSizeImage);
		FILE_LSEEK(fd, pBitFile->bfOffBits, SEEK_SET);
		FILE_READ( fd, ret, pBitInfo->biSizeImage );

		*width = pBitInfo->biWidth;
		*height = pBitInfo->biHeight;

		FILE_CLOSE(fd);
		FREE(bmpfiledata);
	}

	return ret;

}*/


static void showlogo()
{
        int logowidth;
        int logoheight;
        int logoleft;
        int logotop;
        int logocolor;

        char * pbmp;	  
             
        pbmp = xgui_load_bmp_all(LOGOIMG, &logowidth , &logoheight, &logocolor);
		//pbmp = xgui_load_bmp4bit(LOGOIMG , &logowidth , &logoheight);

        if (pbmp != 0){
		xgui_BeginBatchPaint();
		XGUI_SET_WIN_RC;
		xgui_ClearDC();        
		
		xgui_out_bits_bmp(0, XGUI_LINE_TOP_1, pbmp , logowidth , logoheight , 0 , logocolor);
		//xgui_out_bits_bmp4bit(0, 0, pbmp , logowidth , logoheight , 0);
       
		FREE(pbmp);
		xgui_EndBatchPaint(); 
		osl_Sleep(1000); 
		} 
}

static void app_init()
{
	APP_TRACE_FILE("app run\r\n");

	set_malloc_log(0);
	//ap_logo_page_show();				// Display boot logo
	osl_setAppVision(APP_VER);	// Set the application version
	EMV_iKernelInit();//Init EMV
	//mbedtls_init();    
	showlogo();
	
	sdk_main_page(); //Start page       
}



static void _AppWorkTask(void * pParam)
{
	sys_init();				
	app_init();
}


void app_main()
{
	int nErrorCode;

	mf_driverlib_init();			 // Driver initialization
	OSInit();						 // ucosii initialization
	// Create an application thread
	OSTaskCreateExt(_AppWorkTask, 0, &(pTaskStk[_APP_TASK_SIZE -1]), _APP_TASK_PRIO ,_APP_TASK_PRIO ,&(pTaskStk[0]) , _APP_TASK_SIZE , 0 , OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK);
	OSStart();						// 	ucosii run
	while(1) osl_Sleep(1000);
}

#ifndef WIN32
void main(){
	app_main();
}
#endif

