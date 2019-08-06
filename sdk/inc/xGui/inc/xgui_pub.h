#pragma once

#include "pub\pub.h"

#define BOTTOM_BUTTON_HEIGHT	16

#if LCD_320_240
	#ifdef LCD_COLOR_1BIT
		#define LCD_320_240_1BIT		1
	#else
		#define LCD_320_240_16BIT		1
	#endif
#elif LCD_128_128
	#define LCD_128_128_1BIT			1
#else
	#define LCD_128_64_1BIT				1
#endif