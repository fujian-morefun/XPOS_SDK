/*! \file xgui_bmp.h
	\brief 图片功能
*	\author lx
*	\date 2014/02/08
*/
#pragma once

#include "xgui_pub.h"

/**
* @brief 载入bmp图片
* @param filename 文件名
* @param width 图片宽度
* @param height 图片高度
* @return 图标位图缓冲区指针，在函数内分配，外部使用后需要释放
*/
LIB_EXPORT char * xgui_load_bmp(char * filename , int *width , int *height);

//24bitbmp图片
LIB_EXPORT char * xgui_load_bmp24bit(char * filename , int *width , int *height);

LIB_EXPORT char * xgui_load_bmp4bit(char * filename , int *width , int *height);


LIB_EXPORT char * xgui_load_bmp_all(char * filename , int *width , int *height, int * color);
LIB_EXPORT char * xgui_get_bmp_file(char *filename);