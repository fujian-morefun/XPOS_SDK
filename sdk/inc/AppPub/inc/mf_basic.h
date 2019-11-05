/*
* Data Type Global define
* Copyright (c) 2011 mfcomm
* 
* history
* date 			who						remark
* 2011-03-16	hexs@taner.com.cn		create 
*/

#ifndef _mf_BASIC_H_
#define _mf_BASIC_H_

/******************************************************************************
* COMMON
******************************************************************************/
//#include <stdbool.h>
#include <string.h>
#include <stdio.h>
//#include <unistd.h>
#include <errno.h>
//modified by zhiyu 0923
//#include <fcntl.h>
#include <stdlib.h>
//#include <syslog.h>
//#include <pthread.h>
//#include <sys/socket.h>
//#include <arpa/inet.h>
//#include <netinet/in.h>
//#include <sys/ioctl.h>
//modified by zhiyu 0923
//#include <sys/types.h>

#include "pub_def.h"

#include <pub/pub.h>

#define MAXSTR_LEN	1024

#ifndef MIN
#define MIN(a,b) ((a)<(b))?(a):(b)
#endif

#ifndef MAX
#define MAX(a,b) ((a)<(b))?(b):(a)
#endif



#ifndef ARRAYSIZE
#define ARRAYSIZE(a) sizeof(a)/sizeof(a[0]) 
#endif

typedef unsigned char 	uchar;
typedef unsigned short ushort;
typedef unsigned int 	uint;
typedef unsigned long	ulong;

typedef uchar	u8;
typedef ushort	u16;
typedef uint	u32;
typedef ulong	u64;
typedef u32		dword;

/*
* UID 
*/
#define UID_ROOT	0
#define UID_POS		1001
/*
* PATH 
*/
#define mf_IMAGE_PATH		"/dev/"
#define mf_APP_PATH		"/app/"
#define mf_MASTER_PATH	"/app/master/"
#define mf_MODULE_PATH	"/app/modules/"
#define mf_LIBRARY_PATH	"/app/lib/"
#define mf_SAFEFONT_PATH "/fonts/truetype/"

/*
*
*/
typedef struct {
	char *module_name;
	char *ver_file;
} TModule_Version;

/*
static TModule_Version module_ver_files[] = {
	{"", ""},
	{"", ""},
	{"", ""},
	
	
	{NULL, NULL},
};
*/
/*
* files
*/
#define mf_DAEMON_RILD	"rild"
#define mf_DAEMON_PRINTERD	"printerd"
#define mf_DAEMON_MFD	"mfd"
#define mf_DAEMON_DESKTOPD	"desktopd"

#define mf_IMG_ROOTFS	"mtd0ro"

/******************************************************************************
* simple single LIST
******************************************************************************/
//typedef struct int_node  
//{  
//    int value;  /* can used to: int void* etc. */
//    struct int_node *next;  
//}TSingleList_IntNode;
//
//typedef TSingleList_IntNode * SingleIntList; 

/******************************************************************************
* errno
******************************************************************************/
#include <errno.h>

#define XE_BASE					1000

#define XE_SUCCESS				(XE_BASE + 1)
#define XE_FAILED				(XE_BASE + 2)
#define XE_TIMEOUT				(XE_BASE + 3)
#define XE_PARAM				(XE_BASE + 4)
#define XE_INSTANCERUNNING		(XE_BASE + 5)
#define XE_NOTROOT				(XE_BASE + 6)



#define MF_RSA_PUBKEY_APP_FILE	"/etc/vendor/mf_app_rsapub.key"
#define MF_RSA_PUBKEY_IMG_FILE	"/etc/vendor/mf_img_rsapub.key"

/******************************************************************************
* crypto DES
******************************************************************************/
/* uiMode */
#define XM_alg_TDESENCRYPT	(uint)0x00000000	//Encryption with TDES Key
#define XM_alg_TDESDECRYPT	(uint)0x00000001	//Decryption using TDES key
#define XM_alg_TDESTECBMODE	(uint)0x00000000	//Using TECB mode of operation
#define XM_alg_TDESTCBCMODE	(uint)0x00000100	//Using TCBC mode of operation
#define XM_alg_TAESMACMODE	(uint)0x00000200	//Using TCBC mode of operation
#define XM_alg_TDESDEFAULTMODE	XM_alg_TDESTECBMODE	//Use default (TECB)

/******************************************************************************
* timer and RTC type definition
******************************************************************************/
#define XM_SYSTEM_DATE		0x01  
#define XM_SYSTEM_TIME		0x02 
#define XM_SYSTEM_DATETIME		(XM_SYSTEM_DATE | XM_SYSTEM_TIME) 

//typedef struct 
//{
//	ushort 	usYear; 		// 1900 -  2037
//	uchar  	ucMonth;		// 1 - 12 
//	uchar  	ucDay;			// 1 ~ 31
//	uchar  	ucDayOfWeek;		// 0-6
//	uchar  	ucHour;			// 0 - 23
//	uchar  	ucMinite; 		// 0 - 59
//	uchar  	ucSecond; 		// 0-59
//} mf_DATETIME; 


/******************************************************************************
* driver interface
******************************************************************************/

/*
* battery 
*/
#define mf_BATTERY_CHARGING		0x0000BA00      //Charging
#define mf_BATTERY_DISCHARGING	0x0000BA01      // Discharging
#define mf_BATTERY_FULL			0x0000BA02		//FULL
#define mf_BATTERY_NOTDISCHARGING	0x0000BA03      // NOT Discharging
#define mf_BATTERY_UNKOWN		0x0000BA04		// Unknown

/*
* LED 
*/
#define MF_LED_PRN		0x0000CD01   //Printer LED lamp identification
#define MF_LED_KBD		0x0000CD02  //keyboard led 

#define MF_LED_TURNON		1
#define MF_LED_TURNOFF		0

/*
* USB 
*/
#define mf_USB_POWER_ON	1
#define mf_USB_POWER_OFF	0

/*
* PRINTER
*/
#define mf_PRN_POWER_ON		1
#define mf_PRN_POWER_OFF	0
#define mf_PRN_POWER_RESET	1

#define mf_PRN_NOPAPER		1
#define mf_PRN_EXISTPAPER	0

/*
* PSAM
*/
#define mf_PSAM_DEV		"/dev/s3c2410_serial2"
#define mf_PSAM_POWER_ON	1
#define mf_PSAM_POWER_OFF	0

#define mf_PSAM1_CLOCK_ON	1
#define mf_PSAM2_CLOCK_ON	2
#define mf_PSAM_CLOCK_OFF	3

#define mf_PSAM_RESET		1
#define mf_PSAM1_ID			1
#define mf_PSAM2_ID			2

/*
* GPRS modem
*/
#define mf_MODEM_POWERON	"0"
#define mf_MODEM_POWEROFF	"1"
#define mf_MODEM_POWERRESET	"2"

/*
* brightness
*/
#define mf_MAX_BRIGHTNESS	100

/******************************************************************************
* others just like ipc
******************************************************************************/
union semun {
   int val;
   struct semid_ds *buf;
   unsigned short int *array;
   struct seminfo *__buf;
};

/******************************************************************************
* image file format
******************************************************************************/
#define SIG_RSA_LEN		256
#define SUM_SHA_LEN		32
#define IMAGE_MAGIC		"mf"

typedef struct {
	int		length;
	dword		version;
} TIMAGE_HEADER;


/******************************************************************************
* API
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*******************************
* log
*******************************/
/*
* display mesageHeader + hexstr to stderr.
* s: display header
* buff: binary data buffer
* len: binary data length to display
*/
void dump_dbg_data(const char * s, const unsigned char * buff, int len);
/*
* output formatted info to stderr.
*/
void mf_log(const char *fmt, ...);

/*
* syslog output to klogd or syslogd
*/
void mf_open_log(void);
void mf_close_log(void);
void mf_log_warn(const char *fmt, ...);
void mf_log_error(const char *fmt, ...);
void mf_log_debug(const char *fmt, ...);

int mf_getlasterror(void);
void mf_geterrormsg(int errnum, char *buf, uint buflen);

/*******************************
* filesystem
*******************************/
LIB_EXPORT int mf_access(const char *pathname, int mode);
int mf_fopen(const char *pathname, int flags);
int mf_fclose(int fd);
long mf_fseek(int fd, long offset, int whence);
int mf_fread(int fd, void *buf, uint count);
//int mf_freadtimeout(int fd, void *buf, uint count, int iMilTimeOut);
int mf_fwrite(int fd, const void *buf, uint count);
//int mf_fwritetimeout(int fd, void *buf, uint count, int iMilTimeOut);
int mf_fsyncwrite(int fd, const void *buf, uint count);
int mf_fdelete(const char *pathname);
long mf_ftell(int fd);
int mf_frename(const char *oldpath, const char *newpath);
int mf_fsetlength(const char *pathname, long length);
int mf_fgetlength(const char *pathname);
//long mf_diskfreespace(void);
int mf_meminfo(int *total, int *free);
//int mf_absname(char *buf, uint bufsiz);
//int mf_dirname(char *buf, uint bufsiz);
//int mf_basename(char *buf, uint bufsiz);
int mf_creat(const char *pathname, int flags);
/*******************************
* common
*******************************/
int make_argv(char * args, char ** argv);

/*******************************
* rs232
*******************************/
//int mf_rs232open(const char *devname, int flags);
//int	mf_rs232init(int fd,int nspeed,int nbits,char nevent,int nstop);
//int mf_rs232initdefault(int fd);
//int mf_rs232getcount_recvbuf(int fd);
//int mf_rs232getcount_sendbuf(int fd);
//int mf_rs232clear(int fd);
//int mf_rs232clear_recvbuf(int fd);
//int mf_rs232clear_sendbuf(int fd);
//
//int mf_rs232_recv(int fd, void *buf, uint count);
//int mf_rs232_send(int fd, void *buf, uint count);
//
//int mf_rs232_recvtimeout(int fd, void *buf, uint count, int iMilTimeOut);
//int mf_rs232_sendtimeout(int fd, void *buf, uint count, int iMilTimeOut);

/*******************************
* delay
*******************************/
//void mf_sleep(uint uiSeconds);
//void mf_msleep(uint uiMS);
//double mf_resetstopwatch(void);

/*******************************
* socket
*******************************/
//int mf_sockSendTimeout(int fd, const char *buf, int count, int msec);
//int mf_sockRecvTimeout(int fd, char *buf, int size, int msec);
//void mf_getIPPortViaSockfd(int sockfd, char *ipStr, int *pPort);
//int mf_newClientSock(const char *ipStr, int iPort);
//void mf_closeSock(int *sockfd, bool shut);
//int mf_newListenSock(int Port);


/*******************************
* OS time
*******************************/
long mf_is_valid_datetime(const mf_DATETIME *ptDateTime, uchar ucMode);
int mf_getosdatetime(mf_DATETIME *ptDateTime);
int mf_settime(const mf_DATETIME *ptDateTime);
int mf_tm2_datetime(mf_DATETIME *ptDateTime, const struct tm *ptm);
int mf_datetime2_tm(struct tm *ptm, const mf_DATETIME *ptDateTime);

/*******************************
* aux api
*******************************/
//int isInstanceRunning(void);

/*******************************
* check and crypto api
*******************************/
/*
* CRC 
*/
LIB_EXPORT extern u8 mf_getlrc(const u8 *input, int count);
LIB_EXPORT extern u8 mf_crc(u8 const *buffer, int len);
LIB_EXPORT extern u8 mf_crc8(const u8 *data, int length);
LIB_EXPORT extern u32 mf_crc32(u8 const *buffer, int len);
LIB_EXPORT extern u16 mf_crc16(u8 const *buffer, int len);



/*******************************
* char buffer
*******************************/
void ltrim(char *buf, uint ilen);
void rtrim(char *buf, uint ilen);
void trim(char *buf, uint ilen);
int start_with(const char *src, const char *needle);
int end_with(const char *src, const char *needle);

int mf_is_hexstring(const char *hexstr, uint len);
int mf_hex_to_int(char c) ;
int mf_hexstr_to_dec(unsigned char *pDst, const char *src, int count) ;
int make_argv(char * args, char ** argv) ;
int mf_moveMemoryBlock(uchar *data, uint col_data, uint line_data,
	uchar *buf, uint col_buf, uint line_buf,
	uint col_oft, uint line_oft);

/*******************************
* simple LIST
*******************************/
//void    IntList_Init(SingleIntList *list);    /* initialize a header to a list */
//void    IntList_Destroy(SingleIntList *list);
//void    IntList_Insert(int value, SingleIntList *list);  /* insert an element into a list */
//void    IntList_Remove(int value, SingleIntList *list);  /* remove an element from a list */
//int 	IntList_GetCount(SingleIntList *list);
//int		IntList_GetValue(int index, int defaultVal, SingleIntList *list);

/*******************************
* version
*******************************/
dword mf_getVer_image(const char *name);
dword mf_getVer_module(const char *name);
dword mf_getVer_library(const char *name);
dword mf_getVer_master(const char *name);
dword mf_getVer_daemon(const char *name);
const char *mf_getVerStr(dword vernum);

/*******************************
* patterned config file
*******************************/
int mf_modifyConfItems(const char * filename, const char *itemKey, const char *itemVal);
int mf_deleteConfItems(const char * filename, const char *itemKey);
int mf_swapConfItems(const char * filename, const char *itemVal1, const char *itemVal2, int iType); //iType =0 Key  iType=1 Value
int mf_getConfItemValList(const char * filename, char *buf, uint isize);
int mf_getKeyConfItemByVal(const char * filename, char *buf, uint isize);
int mf_getValueConfItem(const char * filename, char *buf, uint isize);

/*******************************
* runMaster
*******************************/
int runMaster(const char *appname, const char *command_arg, int ilen);

/******************************
* driver
******************************/
int mf_psam_power(int turnOnOrOff) ;
int mf_psam_chipselect(int selOper) ;
int mf_psam_reset(int dev_id) ;

int mf_beep(int iDuration) ;

int mf_isModemExist(void);
int mf_modemPowerReset(void);
int mf_modemPowerOff(void);
int mf_modemPowerOn(void);

int mf_USB_power(int turnOnOrOff) ;

int mf_led_conf(uint whichLED, int iOpen);
int mf_brightness_conf(int brightness);
int mf_brightness_load(void);

int mf_getExtendPowerStatus(void);
int mf_getBatteryCapacity(void);
int mf_getBatteryStatus(void);

int mf_openWdt(void);
int mf_closeWdt(void);
int mf_setWdtTimeout(unsigned int timeout);  //seconds
int mf_feedWdt(void);

/******************************************************************************
*  printer 
******************************************************************************/
int mf_printerPower(int turnOnOrOff) ;
int mf_printer_reset(void) ;
int mf_printer_goahead(uint lines) ;
int mf_isPrinterHasPaper(void) ;
int mf_printer_temperature(void) ;
int mf_printer_getStep(void) ;
int mf_printer_setStep(int step) ;

/******************************************************************************
* COMMON
******************************************************************************/
#define DOT_PER_LINE		384  /*Thermosensitivity maximum line 384 points*/
#define BYTE_PER_LINE		48 	//(384/8)  /*Thermosensitive maximum line of 48 bytes*/
#define MAX_WRITE_LINES		32	 //Maximum one-time write 32 lines
#define LINES_SPACE			8	//Row spacing

#define MAX_PKG_SIZE		3840 //48 * 80 lines, maximum support for - 1 - fonttype ==> 3835 bytes of string.¡£

#define PRINTER_DEVPATH		"/dev/thermal_printer"
#define PRINTER_SOCKET		"/tmp/prnt.sock"
#define MAX_PRINTER_TIMEOUT		5000 /* 5 seconds until timeout */

typedef enum  {
	font_16x16 = 0,
	font_24x24,
	font_32x32,
} font_type_t;  /*Fonts for Printing Chinese Character Strings*/

typedef enum  {
	dot_8x16 = 0,
	dot_16x24,
	dot_16x32,
	dot_24x32,
} dot_type_t;  /*Print fonts for ASCII strings*/

typedef enum  {
	align_top = 0,
	align_middle,
	align_bottom,
} align_type_t;  /*A line of baselines */

typedef enum {
	cmd_reset = 0,	/*reset printers*/
	cmd_lock,	/*Exclusive printer*/
	cmd_unlock, /*Release printer*/
	cmd_string, /*Print strings*/
	cmd_dot,	/*Print dot matrix*/
	cmd_xml,	/*Print XML format documents*/
	cmd_ack,	/*Response response*/
	cmd_nak,	/*Refusal to respond*/
} printer_frame_t; /* Data frame type */

typedef enum {
	st_idle = 0,
	st_busy,
} printer_status_t; /* Printer status */

typedef struct {
	font_type_t fonttype;
	dot_type_t dottype; 
	align_type_t baseline; 
	uint linespace;
}  string_config_t;

typedef struct {
	printer_frame_t type; 
	uint len; //content Effective length
	uchar content[MAX_PKG_SIZE];
}  print_comm_t; //Communicator


/************* xml format defination begin ****************/
/*
* | 0 | 1 | . | . | . | 47|
  |   |   |   |   |   |   |

  current printer canvas has 40 bytes width. so bill should be 48 always
  string and image node's width should not be larger than 48.
*/


#define MFML_ROOT_NODE		"bill"
#define MFML_STRING_NODE	"string"
#define MFML_IMAGE_NODE		"image"

#define MFML_ATTR_LEFT		"left"
#define MFML_ATTR_TOP			"top"
#define MFML_ATTR_HEIGHT	"height"
#define MFML_ATTR_WIDTH		"width"
#define MFML_ATTR_FONT		"font"
#define MFML_ATTR_DOT			"dot"
#define MFML_ATTR_ALIGN			"align"

#define DEF_ATTR_LEFT		"0"
#define DEF_ATTR_TOP			"0"
#define DEF_ATTR_FONT		font_16x16
#define DEF_ATTR_DOT			dot_8x16

//string section
typedef struct
{
	font_type_t font;
	dot_type_t 	dot;
	align_type_t align;
	int top;		
	int left;	// < 48
	char *content;  //Strings ending in0
}mfml_string_t;

//image section
typedef struct
{
	int 	width;  // bytes
	int		height; //bytes 
	uint 	top;   
	uint 	left;  // < 48
	uchar 	*content; //Memory address of image. length should be width(bytes) * height(bytes)
}mfml_image_t;

//canvas
typedef struct
{
	int 	width;  //must be DOT_PER_LINE = 384
	int		height;
}mfml_canvas_t;


//xml Format Printing api¡£
int mf_BeginPaint(mfml_canvas_t *canvas);
int mf_DrawString(mfml_string_t *stString);
int mf_DrawImage(mfml_image_t *stImage);
int mf_EndPaint(void);

/************* xml format defination begin ****************/

//Successful return of 0, error return of negative value
int mf_resetPrinter(void);
int mf_trylockPrinter(void);
int mf_unlockPrinter(void);
int mf_printDot(uchar *buf, uint size);
int mf_printStr(font_type_t fonttype, dot_type_t dottype, align_type_t baseline, uint linespace, char *str);



#ifdef __cplusplus
}
#endif

#endif //_mf_BASIC_H_
