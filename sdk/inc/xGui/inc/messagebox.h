/*! \file messagebox.h
	\brief 提示对话框
*	\author lx
*	\date 2014/02/08
*/
#ifndef _MESSAGEBOXPAGE_H___
#define _MESSAGEBOXPAGE_H___


#include "xgui_pub.h"

#define MSGBOX_RET_OK		1
#define MSGBOX_RET_QUIT		2
#define MSGBOX_RET_TIMEOUT	3
#define MSGBOX_RET_ANY		-1


/**
* @brief 显示单行对话框
* @param title 对话框标题
* @param msg 对话框内容
* @param pszLeftOp 左按钮
* @param pszRightOp 右按钮
* @param timeover 超时时间
* @return 操作结果
*/
LIB_EXPORT int xgui_messagebox_show(char *title, char *msg , char* pszLeftOp, char* pszRightOp , int timeover);
LIB_EXPORT int xgui_messagebox_showEx(char *title, char *msg , char* pszLeftOp, char* pszRightOp ,int timeover , int flag);

#endif
