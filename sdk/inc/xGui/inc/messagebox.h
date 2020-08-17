#ifndef _MESSAGEBOXPAGE_H_
#define _MESSAGEBOXPAGE_H_


#include "xgui_pub.h"

#define MSGBOX_RET_OK		1
#define MSGBOX_RET_QUIT		2
#define MSGBOX_RET_TIMEOUT	3
#define MSGBOX_RET_USER_KEY	4
#define MSGBOX_RET_ANY		-1


/**
* @brief Display single-line dialog box
* @param title Dialog Title
* @param msg Dialog content
* @param pszLeftOp left button
* @param pszRightOp right button
* @param timeover 
* @return Operational results
*/
LIB_EXPORT int xgui_messagebox_show(char *title, char *msg , char* pszLeftOp, char* pszRightOp , int timeover);
LIB_EXPORT int xgui_messagebox_showEx(char *title, char *msg , char* pszLeftOp, char* pszRightOp ,int timeover , int flag);
LIB_EXPORT int xgui_messagebox_showEx2(char *title, char *msg , char* pszLeftOp, char* pszRightOp ,int timeover , int flag, unsigned char * keylist, int * presskey);
LIB_EXPORT int xgui_messagebox_show2(char *title, char *msg , char* pszLeftOp, char* pszRightOp ,int timeover);

#endif
