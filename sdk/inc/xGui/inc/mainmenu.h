#ifndef __MAIN_MENU__
#define __MAIN_MENU__
#pragma once

#include "xgui_pub.h"


#define MENU_ITEM_COUNT(a)		sizeof(a)/sizeof(st_main_menu_item_def)


typedef struct __st_main_menu_item_def{
	char *parent;	
	char *name;		
	char *id;		
}st_main_menu_item_def;

/**
* @brief Add callback function
* @param pfunc callback
* @return 
*/
LIB_EXPORT int xgui_main_menu_func_add(void * pfunc);

/**
* @brief Remove callback function
* @param pfunc callback
* @return 
*/
LIB_EXPORT int xgui_main_menu_func_del(void * pfunc);


/**
* @brief Add menu list
* @param menu_item Menu list
* @param count Number of menu lists
* @return 
*/
LIB_EXPORT int xgui_main_menu_item_add_list(st_main_menu_item_def * menu_item , int count);
/**
* @brief Add menu items
* @param parent Parent menu ID
* @param name Menu Name
* @param id menuid
* @return 
*/
LIB_EXPORT int xgui_main_menu_item_add(const st_main_menu_item_def * menu_item);
/**
* @brief Delete menu items
* @param name Menu Name
* @param id menu id
* @return 
*/
LIB_EXPORT int xgui_main_menu_item_del(char *name ,char *id);
LIB_EXPORT int xgui_main_menu_item_del_ex(char *name ,char *id ,char * parent);
/**
* @brief show menu
* @param id menu id
* @param timeover 
* @return 
*/
LIB_EXPORT void xgui_main_menu_show(char *id , int timeover);
LIB_EXPORT void xgui_main_menu_show4(char *id , int timeover);

//Titled
LIB_EXPORT int xgui_main_menu_show2(char *title,char *id , int timeover);
// 320 With title, 128 without
LIB_EXPORT int xgui_main_menu_show3(char *title,char *id , int timeover);

#endif

