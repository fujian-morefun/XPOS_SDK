/*! \file osl_print.h
	\brief Printing function
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
* @brief Setting Chinese fonts
* @param v Typeface
* @return Setting Characters
*/
LIB_EXPORT const char *  osl_print_cn_font_size(int v);
/**
* @brief Setting English Font
* @param v Typeface
* @return Setting Characters
*/
LIB_EXPORT const char *  osl_print_en_font_size(int v);
/**
* @brief Chinese Enlargement
* @param w transverse
* @param h portrait
* @return Setting Characters
*/
LIB_EXPORT const char *  osl_print_cn_font_zoom(int w,int h);
/**
* @brief Enlargement in English
* @param w transverse
* @param h portrait
* @return Setting Characters
*/
LIB_EXPORT const char *  osl_print_en_font_zoom(int w,int h);
/**
* @brief Set up row spacing
* @param v spacing
* @return Setting Characters
*/
LIB_EXPORT const char *  osl_print_line_space(int v);
/**
* @brief Vertical Paper Walking
* @param v Row number
* @return Setting Characters
*/
LIB_EXPORT const char *  osl_print_col_space(int v);
/**
* @brief Horizontal Paper Walking
* @param v Column number
* @return Setting Characters
*/
LIB_EXPORT const char *  osl_print_row_space(int v);
/**
* @brief align
* @param v 0 left 1medium 2right
* @return Setting Characters
*/
LIB_EXPORT const char *  osl_print_align(int v);
/**
* @brief print pictures
* @param imgfile file name
* @return  Setting Characters
*/
LIB_EXPORT const char *  osl_print_img(const char *imgfile);
/**
* @brief heating time
* @param v time
* @return Setting Characters
*/
LIB_EXPORT const char *  osl_print_heat_factor(int v);

/**
* @brief Get the print buffer
* @return 
*/
LIB_EXPORT char * osl_print_get();
/**
* @brief Add content to print buffer
* @param pbuff content
* @return 
*/
LIB_EXPORT void osl_print_add(const char * pbuff);
/**
* @brief Print Buffer Release
* @return 
*/
LIB_EXPORT void osl_print_free();


/**
* @brief Print initialization
* @return 
*/
LIB_EXPORT void osl_print_init();
/**
* @brief Print Output
* @param data content
* @return 0 success
*/
LIB_EXPORT int  osl_print_write(char * data);


/**
* @brief Setting the content of the original file
* @param blockfile file
* @return  Setting Characters
*/
LIB_EXPORT const char * osl_print_block(const char *blockfile);

LIB_EXPORT const char *  osl_print_block_width(int v);






