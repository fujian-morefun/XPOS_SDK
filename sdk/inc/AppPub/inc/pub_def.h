#pragma once

typedef struct 
{
	unsigned short 	usYear; 		//年 1900 -  2037
	unsigned char  	ucMonth;		//月 1 - 12 
	unsigned char  	ucDay;			//日 1 ~ 31
	unsigned char  	ucDayOfWeek;		//星期 0-6
	unsigned char  	ucHour;			//时 0 - 23
	unsigned char  	ucMinite; 		//分 0 - 59
	unsigned char  	ucSecond; 		//秒 0-59
} mf_DATETIME; 

typedef enum
{
	NO='0',
	YES='1'
}YESORNO;


typedef enum Alignment 
{
	ALN_LEFT   = 0,
	ALN_RIGHT  = 1
} Alignment;
#ifndef NULL
#define NULL 0
#endif
#define SUCC 0
#ifndef FAIL
#define FAIL (-1)
#endif
