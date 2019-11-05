/*! \file xgui_bmp.h
	\brief Picture function
*	\author lx
*	\date 2014/02/08
*/
#pragma once

#include "xgui_pub.h"

/**
* @brief Load the BMP image
* @param filename file name
* @param width bmp width
* @param height bmp height
* @returnIcon Bitmap Buffer Pointer, Allocated within Function, Released after External Use
*/
LIB_EXPORT char * xgui_load_bmp(char * filename , int *width , int *height);

//24bitbmp
LIB_EXPORT char * xgui_load_bmp24bit(char * filename , int *width , int *height);

LIB_EXPORT char * xgui_load_bmp4bit(char * filename , int *width , int *height);


LIB_EXPORT char * xgui_load_bmp_all(char * filename , int *width , int *height, int * color);
LIB_EXPORT char * xgui_get_bmp_file(char *filename);