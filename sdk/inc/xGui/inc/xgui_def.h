#pragma once


#define PAGE1				0
#define PAGE2				1
#define PAGE3				2
#define PAGE4				3

#ifdef LCD_320_240

	#define IN_LINE_LINE_1		LINE1
	#define IN_LINE_LINE_2		LINE2
	#define IN_LINE_LINE_3		LINE3
	#define IN_LINE_LINE_4		LINE4
	#define IN_LINE_LINE_5		LINE5
	#define IN_LINE_LINE_6		LINE1
	#define IN_LINE_LINE_7		LINE2
	#define IN_LINE_LINE_8		LINE3
	#define IN_LINE_LINE_9		LINE4
	#define IN_LINE_LINE_10		LINE5

	#define IN_PAGE_LINE_1		PAGE1
	#define IN_PAGE_LINE_2		PAGE1
	#define IN_PAGE_LINE_3		PAGE1
	#define IN_PAGE_LINE_4		PAGE1
	#define IN_PAGE_LINE_5		PAGE1
	#define IN_PAGE_LINE_6		PAGE2
	#define IN_PAGE_LINE_7		PAGE2
	#define IN_PAGE_LINE_8		PAGE2
	#define IN_PAGE_LINE_9		PAGE2
	#define IN_PAGE_LINE_10		PAGE2

	#define LEFT1				0
	#define LEFT2				160


	#define LINE1				(3 + 33 * 1)
	#define LINE2				(3 + 33 * 2)
	#define LINE3				(3 + 33 * 3)
	#define LINE4				(3 + 33 * 4)
	#define LINE5				(3 + 33 * 5)

#else

	#define IN_LINE_LINE_1		LINE1
	#define IN_LINE_LINE_2		LINE2
	#define IN_LINE_LINE_3		LINE3
	#define IN_LINE_LINE_4		LINE4
	#define IN_LINE_LINE_5		LINE1
	#define IN_LINE_LINE_6		LINE2
	#define IN_LINE_LINE_7		LINE3
	#define IN_LINE_LINE_8		LINE4
	#define IN_LINE_LINE_9		LINE1
	#define IN_LINE_LINE_10		LINE2

	#define IN_PAGE_LINE_1		PAGE1
	#define IN_PAGE_LINE_2		PAGE1
	#define IN_PAGE_LINE_3		PAGE1
	#define IN_PAGE_LINE_4		PAGE1
	#define IN_PAGE_LINE_5		PAGE2
	#define IN_PAGE_LINE_6		PAGE2
	#define IN_PAGE_LINE_7		PAGE2
	#define IN_PAGE_LINE_8		PAGE2
	#define IN_PAGE_LINE_9		PAGE3
	#define IN_PAGE_LINE_10		PAGE3


	#define LEFT1				0
	#define LEFT2				64

	#define LINE1				0
	#define LINE2				12
	#define LINE3				24
	#define LINE4				36

#endif