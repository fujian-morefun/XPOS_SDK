/*! \file mainmenu.h
	\brief 主菜单
*	\author lx
*	\date 2014/02/07
*/
#pragma once

#include "xgui_pub.h"


#define MENU_ITEM_COUNT(a)		sizeof(a)/sizeof(st_main_menu_item_def)


typedef struct __st_main_menu_item_def{
	char *parent;	
	char *name;		
	char *id;		
}st_main_menu_item_def;

/**
* @brief 添加回调函数
* @param pfunc 回调函数
* @return 
*/
LIB_EXPORT int xgui_main_menu_func_add(void * pfunc);

/**
* @brief 移除回调函数
* @param pfunc 回调函数
* @return 
*/
LIB_EXPORT int xgui_main_menu_func_del(void * pfunc);


/**
* @brief 添加菜单列表
* @param menu_item 菜单列表
* @param count 菜单列表数量
* @return 
*/
LIB_EXPORT int xgui_main_menu_item_add_list(st_main_menu_item_def * menu_item , int count);
/**
* @brief 添加菜单项
* @param parent 父菜单id
* @param name 菜单名称
* @param id 菜单id
* @return 
*/
LIB_EXPORT int xgui_main_menu_item_add(const st_main_menu_item_def * menu_item);
/**
* @brief 删除菜单项
* @param name 菜单名称
* @param id 菜单id
* @return 
*/
LIB_EXPORT int xgui_main_menu_item_del(char *name ,char *id);
LIB_EXPORT int xgui_main_menu_item_del_ex(char *name ,char *id ,char * parent);
/**
* @brief 显示菜单
* @param id 菜单id
* @param timeover 超时时间
* @return 
*/
LIB_EXPORT void xgui_main_menu_show(char *id , int timeover);
//带标题
LIB_EXPORT int xgui_main_menu_show2(char *title,char *id , int timeover);
// 320 带标题 ，128不带
LIB_EXPORT int xgui_main_menu_show3(char *title,char *id , int timeover);



