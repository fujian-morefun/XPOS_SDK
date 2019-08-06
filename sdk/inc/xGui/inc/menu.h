/*! \file menu.h
	\brief 菜单列表
*	\author lx
*	\date 2014/02/07
*/

#ifndef ___MENU_H___
#define ___MENU_H___ 

#include "xgui_pub.h"
#include "2ddraw.h"

#define LINESPERPAGE	5
#define WIDTHPERLINE	108
#define MAX_ITEMTEXT_LEN	256

#define AS_ARROW_NONE	(0 << 0)
#define AS_ARROW_UP		(1 << 0)
#define AS_ARROW_DOWN	(1 << 1)
#define AS_ARROW_BOTH	(AS_ARROW_UP | AS_ARROW_DOWN)

#define MENU_RET_QUIT		-1
#define MENU_RET_HANDOFF	-2
#define MENU_RET_TIMEOVER	-3

#define MENU_REFRESH	(-6)

typedef struct __st_menuitem{
	char * szItemText;
	unsigned int nTextLen;
	int position;
	int nId;
	int nData;
	struct __st_menuitem * prev;
	struct __st_menuitem * next;
}MENUITEM_ST;

typedef struct _st_xmenu {
	 MENUITEM_ST *m_pMenuHead;
	 MENUITEM_ST *m_pMenuTail;
	 MENUITEM_ST *m_pCurSel;
	int m_nLineHeight;
	int m_nCurPos;
	int m_nCount;
	int m_nChHorzPos;
	char * m_szText;
	
	
	int m_bCreated;
	int m_bEnable;
	int m_bVisible;
	int m_bInited;
	RECT m_rect;
	int m_nStyle ;
	unsigned char m_retkey[20];
	int m_retkey_len;
	int m_nLastkey;
	int pDelMenuMsg;
	unsigned int m_nkeySel;
	int m_nline;
	unsigned int m_nTimeOver;
	unsigned int m_nTick;
	int flag;
}XMENU;

/**
* @brief 创建菜单
* @param szName 菜单名称
* @param nStyle 样式
* @param pRect 区域
* @param nParam 超时时间
* @return 菜单结构
*/
LIB_EXPORT XMENU * xgui_menu_Create( char * szText, int nStyle,RECT * pRect, int nParam);
LIB_EXPORT XMENU * xgui_menu_Create1( char * szText, int nStyle,RECT * pRect, int nParam);
LIB_EXPORT XMENU * xgui_menu_CreateEx( char * szText, int nStyle,RECT * pRect, int nParam , int flag);

/**
* @brief 显示菜单
* @param pm 菜单结构
* @return 0成功
*/
LIB_EXPORT void xgui_menu_Show(XMENU * pm);

/**
* @brief 添加菜单项
* @param pm 菜单结构
* @param szItemText 菜单名称
* @param nID 菜单id
* @return 0成功
*/
LIB_EXPORT int xgui_menu_AppendMenu(XMENU * pm,  char * szItemText,int nID);
/**
* @brief 插入菜单项
* @param pm 菜单结构
* @param szItemText 菜单名称
* @param nPosition 菜单id
* @param nID
* @return 0成功
*/
LIB_EXPORT int xgui_menu_InsertMenu(XMENU * pm,  char* szItemText, int nPosition,int nID);
/**
* @brief 删除菜单项
* @param pm 菜单结构
* @param nPosition 菜单位置
* @return 0成功
*/
LIB_EXPORT int xgui_menu_RemoveMenu(XMENU * pm, int nPosition);
/**
* @brief 读取菜单名称
* @param pm 菜单结构
* @param szItemText 菜单名称
* @param nPosition 菜单位置
* @return 0成功
*/
LIB_EXPORT int xgui_menu_GetItemText(XMENU * pm, char * szItemText, int nPosition) ;
/**
* @brief 设置菜单名称
* @param pm 菜单结构
* @param szItemText 菜单名称
* @param nPosition 菜单位置
* @return 0成功
*/
LIB_EXPORT int xgui_menu_SetItemText(XMENU * pm, char * szItemText, int nPosition) ;
/**
* @brief 读取菜单项数量
* @param pm 菜单结构
* @return 菜单项数量
*/
LIB_EXPORT int xgui_menu_GetCount(XMENU * pm );
/**
* @brief 获取菜单id
* @param pm 菜单结构
* @param nPosition 菜单位置
* @param pID 菜单id
* @return 0成功
*/
LIB_EXPORT int xgui_menu_GetItemID(XMENU * pm, int nPosition, int * pID);
/**
* @brief 获取菜单位置
* @param pm 菜单结构
* @param nID 菜单id
* @return 菜单位置
*/
LIB_EXPORT int xgui_menu_GetItemPosition(XMENU * pm, int nID);

/**
* @brief 读取当前位置
* @param pm 菜单结构
* @return 当前位置
*/
LIB_EXPORT int xgui_menu_GetCurSel(XMENU * pm) ;
/**
* @brief 设置当前位置
* @param pm 菜单结构
* @param nPosition 当前位置
* @return 0成功
*/
LIB_EXPORT int xgui_menu_SetCurSel(XMENU * pm, int nPosition);

/**
* @brief 菜单显示处理
* @param pm 菜单结构
* @return 操作结果
*/
LIB_EXPORT int xgui_menu_domodal(XMENU * pm);

/**
* @brief 释放菜单 
* @param pm 菜单结构
* @return 0成功
*/
LIB_EXPORT void xgui_menu_delete(XMENU * pm);
/**
* @brief 设置从菜单返回时的按键
* @param pm 菜单结构
* @param key 按键
* @param len 按键数量
* @return 0成功
*/
LIB_EXPORT int xgui_menu_SetReturnKey(XMENU *pm, char *key, int len);
/**
* @brief 获取菜单返回时的按键
* @param pm 菜单结构
* @return 按键值
*/
LIB_EXPORT int xgui_menu_getlastkey(XMENU * pm);
/**
* @brief 设置菜单标题
* @param pm 菜单结构
* @param szText 菜单标题
* @return 0成功
*/
LIB_EXPORT int xgui_menu_SetTitle(XMENU* pm, const char *szText);
/**
* @brief 获取菜单数据
* @param pm 菜单结构
* @param nID 菜单id
* @return 菜单数据
*/
LIB_EXPORT int xgui_menu_GetItemData_ID(XMENU* pm, int nID);
/**
* @brief 设置菜单数据
* @param pm 菜单结构
* @param nID 菜单id
* @param nData 菜单数据
* @return 
*/
LIB_EXPORT int xgui_menu_SetItemData_ID(XMENU *pm,int nID, int nData);
/**
* @brief 选择菜单
* @param pm 菜单结构
* @param nID 菜单id
* @return 0成功
*/
LIB_EXPORT int xgui_menu_SelItemData_ID(XMENU* pm, int nID);

LIB_EXPORT void xgui_menu_SetDelMsg(XMENU * pm,int bData);

#endif

