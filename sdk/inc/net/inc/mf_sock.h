/*! \file mf_sock.h
	\brief sock����
*	\author lx
*	\date 2014/02/08
*/
#pragma once

#include <pub/pub.h>
#ifdef __cplusplus
extern "C"{
#endif

/**
* @brief sock��ʼ��
* @return 
*/
LIB_EXPORT void mf_model_init();
LIB_EXPORT void mf_sock_init();
LIB_EXPORT int mf_sock_get_type();
/**
* @brief ����apn
* @param apn apn����
* @param user �û���
* @param pwd ����
* @return 
*/
LIB_EXPORT void mf_setapn(const char *apn,const char *user,const char *pwd);

/**
* @brief sock����
* @return 
*/
LIB_EXPORT int mf_sock_create();


/**
* @brief sock����
* @param s ͨ����
* @param pIp ip
* @param nPort �˿�
* @return < 0 ʧ��  >=0 �ɹ�
*/
LIB_EXPORT int mf_sock_connect(int s,const char * pIp, int nPort);

/**
* @brief ��������
* @param s ͨ����
* @param buff ������
* @param len ����
* @param timeover ��ʱʱ��
* @return �յ�����			0  ��ʱ  -1 �����ѶϿ�
*/
LIB_EXPORT int mf_sock_recv(int s, unsigned char * buff, int len, unsigned int timeover);
/**
* @brief ��������
* @param s ͨ����
* @param buff ������
* @param size ����
* @return С��0ʧ��
*/
LIB_EXPORT int mf_sock_send(int s, unsigned char * buff , int size);
/**
* @brief �ر�sock
* @param s ͨ����
* @return 
*/
LIB_EXPORT int mf_sock_close(int s);


LIB_EXPORT void mf_set_connnect_server_func(int index, void * func);

LIB_EXPORT void mf_sock_fifo_resize(int index , int size);

#ifdef __cplusplus
}
#endif