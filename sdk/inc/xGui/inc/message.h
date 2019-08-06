/*! \file message.h
	\brief 消息处理
*	\author lx
*	\date 2014/02/08
*/
#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "xgui_pub.h"

#ifdef __cplusplus
extern "C"{
#endif
	

#include "messagedatastruct.h"

#define XM_LONG_TIMEOVER		0x7fffffff

#define XM_CREATE

//电源类消息
#define XM_POWERFIRST			0x00000000 
#define XM_POWERDOWN			0x00000001
#define XM_POWNLOWER			0x00000002
#define XM_UNZIPFILE			0x00000003
#define XM_FINISHFILE		    0x00000004
#define XM_POWERENERGY			0x00000005 //节能页面
#define XM_POWERENERGYEXIT		0x00000006 //节能页面
#define XM_POWERLOWDOWN			0x00000007	// 低压关机

#define XM_POWERLAST			0x0000FFFF


//系统类消息
#define XM_SYSTEMFIRST			0x00010000
#define XM_SYSTEM_TC35			0x00010001
#define XM_SYSTEM_SWITCH		0x00010002
#define XM_SYSTEM_MODULE		0x00010003

#define XM_SYSTEMLAST			0x0001FFFF

//手柄类消息
#define XM_HOOKFIRST			0x00040000
#define XM_HOOKPRESS			0x00040001
#define XM_HOOKLAST				0x0004FFFF
	
//键盘类消息
#define XM_KEYFIRST				0x00050000
#define XM_KEYPRESS				0x00050001
#define XM_KEYLAST				0x0005FFFF


//串口类消息
#define XM_UARTFIRST			0x00060000
#define XM_UARTLAST				0x0006FFFF


//指针类消息
#define XM_POINTERFIRST			0x00070000
#define XM_POINTERUP			0x00070001
#define XM_POINTERDOWN			0x00070002
#define XM_POINTERMOVE			0x00070003

#define XM_POINTERLAST			0x0007FFFF


//GUI类消息
#define XM_GUIFIRST				0x000A0000
#define XM_GUIPAINT				0x000A0001
#define XM_GUITEXTOUT			0x000A0002
#define XM_GUIDRAWMENU			0x000A0003	//重画菜单
#define XM_GUIDRAWTEXT			0x000A0004	//重画文本
#define XM_GUIDRAWCURSOR		0x000A0005	//重画光标

#define XM_GUIEXITWIN			0x000A1000	//退出

#define XM_GUILAST				0x000AFFFF




//用户类消息
#define XM_USERFIRST			0x000E0000

#define XM_GPRS_TIP				0x000E0010
#define XM_PRODUCT_TEST			0x000E0011

#define XM_SCAN_OK				0x000E0021

#define XM_USERLAST				0x000EFFFF


/**
* @brief 初始化消息管理
* @param 
* @return 
*/
LIB_EXPORT unsigned int xgui_Message_init(void);	
/**
* @brief 发送消息，立即返回
* @param nMsgID 消息id
* @param wParam 消息参数
* @param lParam 消息参数
* @return 0成功
*/
LIB_EXPORT unsigned int xgui_PostMessage(unsigned int nMsgID,unsigned int wParam, unsigned int lParam);			

unsigned int xgui_GetMessage(PMESSAGE pMsg, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax );	
/**
* @brief 从系统消息队列取一条消息，如果没有消息则等待超时
* @param pMsg 消息结构
* @param timeover 超时时间
* @return 读取结果
*/
LIB_EXPORT unsigned int xgui_GetMessageWithTime( PMESSAGE pMsg , int timeover);
				   
#ifdef __cplusplus
}
#endif
#endif







