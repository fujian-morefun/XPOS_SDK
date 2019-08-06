/*! \file osl_print.h
	\brief 打印功能
*	\author lx
*	\date 2014/02/08
*/
#pragma once

#include "pub\pub.h"


#define PRINT_ERR_OK			(0)
#define PRINT_ERR_NO_PAPER1		(-1)
#define PRINT_ERR_NO_PAPER2		(-2)
#define PRINT_ERR_NO_PAPER3		(-3)
#define PRINT_ERR_FILE_ERR		(-4)
#define PRINT_ERR_TIMEROVER		(-5)


#define PRINT_FONT_TYPE(x)		"<font_type=" #x ">"
#define CN_FONT_SIZE(x)			"<cn_font_size=" #x ">"
#define	EN_FONT_SIZE(x)			"<en_font_size=" #x ">"
#define	CN_FONT_ZOOM(x)			"<cn_font_zoom=" #x ">"
#define	EN_FONT_ZOOM(x)			"<en_font_zoom=" #x ">"
#define	PRINT_LINE_SPACE(x)		"<print_line_space=" #x ">"
#define	PRINT_COL_SPACE(x)		"<print_col_space=" #x ">"
#define	PRINT_ROW_SPACE(x)		"<print_row_space=" #x ">"
#define	PRINT_ALIGN(x)			"<print_align=" #x ">"
#define	PRINT_IMG(x)			"<print_img=" #x ">"
#define	PRINT_HEAT_FACTOR(x)	"<print_heat_factor=" #x ">"
#define	PRINT_BLOCK(x)			"<print_block=" #x ">"
#define	PRINT_BLOCK_WIDTH(x)	"<print_bwidth=" #x ">"
#define	PRINT_COL_TO(x)			"<print_col_to=" #x ">"

/**
* @brief 设置中文字体
* @param v 字体
* @return 设置字符
*/
LIB_EXPORT const char *  osl_print_cn_font_size(int v);
/**
* @brief 设置英文字体
* @param v 字体
* @return 设置字符
*/
LIB_EXPORT const char *  osl_print_en_font_size(int v);
/**
* @brief 中文放大
* @param w 横向
* @param h 纵向
* @return 设置字符
*/
LIB_EXPORT const char *  osl_print_cn_font_zoom(int w,int h);
/**
* @brief 英文放大
* @param w 横向
* @param h 纵向
* @return 设置字符
*/
LIB_EXPORT const char *  osl_print_en_font_zoom(int w,int h);
/**
* @brief 设置行间距
* @param v 间距
* @return 设置字符
*/
LIB_EXPORT const char *  osl_print_line_space(int v);
/**
* @brief 纵向走纸
* @param v 行数
* @return 设置字符
*/
LIB_EXPORT const char *  osl_print_col_space(int v);
/**
* @brief 横向走纸
* @param v 列数
* @return 设置字符
*/
LIB_EXPORT const char *  osl_print_row_space(int v);
/**
* @brief 对齐方式
* @param v 0左 1中 2右
* @return 设置字符
*/
LIB_EXPORT const char *  osl_print_align(int v);
/**
* @brief 打印图片
* @param imgfile 文件名
* @return  设置字符
*/
LIB_EXPORT const char *  osl_print_img(const char *imgfile);
/**
* @brief 加热时间
* @param v 时间
* @return 设置字符
*/
LIB_EXPORT const char *  osl_print_heat_factor(int v);

/**
* @brief 获取打印缓冲区
* @return 
*/
LIB_EXPORT char * osl_print_get();
/**
* @brief 添加内容到打印缓冲区
* @param pbuff 内容
* @return 
*/
LIB_EXPORT void osl_print_add(const char * pbuff);
/**
* @brief 打印缓冲区释放
* @return 
*/
LIB_EXPORT void osl_print_free();


/**
* @brief 打印初始化
* @return 
*/
LIB_EXPORT void osl_print_init();
/**
* @brief 打印输出
* @param data 内容
* @return 0成功
*/
LIB_EXPORT int  osl_print_write(char * data);


/**
* @brief 设置原始文件内容
* @param blockfile 文件
* @return  设置字符
*/
LIB_EXPORT const char * osl_print_block(const char *blockfile);

LIB_EXPORT const char *  osl_print_block_width(int v);






