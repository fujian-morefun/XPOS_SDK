#ifndef _MF_SOCK_
#define _MF_SOCK_

#pragma once

#include <pub/pub.h>
#ifdef __cplusplus
extern "C"{
#endif

/**
* @brief sock初始化
* @return 
*/
LIB_EXPORT void mf_model_init();
LIB_EXPORT void mf_sock_init();
LIB_EXPORT int mf_sock_get_type();
/**
* @brief 设置apn
* @param apn apn名称
* @param user 用户名
* @param pwd 密码
* @return 
*/
LIB_EXPORT void mf_setapn(const char *apn,const char *user,const char *pwd);

/**
* @brief sock创建
* @return 
*/
LIB_EXPORT int mf_sock_create();


/**
* @brief sock连接
* @param s 通道号
* @param pIp ip
* @param nPort 端口
* @return < 0 失败  >=0 成功
*/
LIB_EXPORT int mf_sock_connect(int s,const char * pIp, int nPort);

/**
* @brief 接收数据
* @param s 通道号
* @param buff 缓冲区
* @param len 长度
* @param timeover 超时时间
* @return 收到长度			0  超时  -1 网络已断开
*/
LIB_EXPORT int mf_sock_recv(int s, unsigned char * buff, int len, unsigned int timeover);
/**
* @brief 发送数据
* @param s 通道号
* @param buff 缓冲区
* @param size 长度
* @return 小于0失败
*/
LIB_EXPORT int mf_sock_send(int s, unsigned char * buff , int size);
/**
* @brief 关闭sock
* @param s 通道号
* @return 
*/
LIB_EXPORT int mf_sock_close(int s);


LIB_EXPORT void mf_set_connnect_server_func(int index, void * func);

LIB_EXPORT void mf_sock_fifo_resize(int index , int size);

#ifdef __cplusplus
}
#endif

#endif