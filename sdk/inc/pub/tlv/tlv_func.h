/*! \file tlv_func.h
	\brief tlv功能
*	\author lx
*	\date 2014/02/08
*/
#pragma once

#include "pub\pub.h"

typedef struct _st_tlv_tag{
	int len;
	unsigned char tag;
	unsigned char *val;
}st_tlv_tag;


typedef struct _st_tlv_tag_list{
	struct _st_tlv_tag tlv_tag;
	struct _st_tlv_tag_list * next;
}st_tlv_tag_list;

typedef struct _st_tlv_data{
	int datalen;
	int bufflen;
	unsigned char * buff;
	st_tlv_tag_list tag_list;
}st_tlv_data;

/**
* @brief 创建一个tlv
* @param tlv_data tlv指针
* @param len 长度
* @return 0成功
*/
LIB_EXPORT int tlv_creat_buff(st_tlv_data * tlv_data , int len);
/**
* @brief 保存数据到tlv
* @param tlv_data tlv指针
* @param buff 缓冲区
* @param len 长度
* @return 0成功
*/
LIB_EXPORT int tlv_set_buff(st_tlv_data * tlv_data , unsigned char * buff , int len);
/**
* @brief 删除tlv中的一个tag
* @param tlv_data tlv指针
* @param tag 标签
* @return 0成功
*/
LIB_EXPORT int tlv_del_tag(st_tlv_data * tlv_data , unsigned char tag);
/**
* @brief 添加一个数据到tlv
* @param tlv_data tlv指针
* @param tag 标签
* @param buff 缓冲区
* @param len 数据长度
* @return 0成功
*/
LIB_EXPORT int tlv_add_tag_bin(st_tlv_data * tlv_data , unsigned char tag , unsigned char * buff , int len);
/**
* @brief 添加一个字符串
* @param tlv_data tlv指针
* @param tag 标签
* @param buff 字符串
* @return 0成功
*/
LIB_EXPORT int tlv_add_tag_str(st_tlv_data * tlv_data , unsigned char tag , unsigned char * buff);
/**
* @brief 添加一个整形
* @param tlv_data tlv指针
* @param tag 标签
* @param val 值
* @param n 填充长度
* @return 0成功
*/
LIB_EXPORT int tlv_add_tag_int(st_tlv_data * tlv_data , unsigned char tag , int val , int n);
/**
* @brief 添加一个长整形
* @param tlv_data tlv指针
* @param tag 标签
* @param val 值
* @param n 填充长度
* @return 0成功
*/
LIB_EXPORT int tlv_add_tag_long(st_tlv_data * tlv_data , unsigned char tag , long long val , int n);
/**
* @brief 释放一个tlv
* @param tlv_data tlv指针
* @return 0成功
*/
LIB_EXPORT int tlv_free_buff(st_tlv_data * tlv_data);

/**
* @brief 按照列表拷贝tlv
* @param tlv_src 原始tlv指针
* @param tlv_des 目的tlv指针
* @param tag_list 标签列表 0xff结束
* @return 0成功
*/
LIB_EXPORT int tlv_copy_tag_by_list(st_tlv_data * tlv_src , st_tlv_data * tlv_des , unsigned char *tag_list);

/**
* @brief 获取一个标签值，使用后使用tlv_free_tag释放
* @param tlv_data tlv指针
* @param tag 标签
* @param tlv_tag 标签值
* @return >0成功
*/
LIB_EXPORT int tlv_get_tag(st_tlv_data * tlv_data , unsigned char tag , st_tlv_tag * tlv_tag);
LIB_EXPORT int tlv_get_tag_by_index(st_tlv_data * tlv_data , int index , st_tlv_tag * tlv_tag);
/**
* @brief 释放tlv标签
* @param tlv_tag 标签
* @return 0成功
*/
LIB_EXPORT int tlv_free_tag(st_tlv_tag * tlv_tag);

/**
* @brief 获取tlv中的所有标签列表
* @param tlv_data tlv指针
* @param tag_list 标签列表
* @param size 列表大小
* @return 实际列表数量
*/
LIB_EXPORT int tlv_get_tag_index_list(st_tlv_data * tlv_data , unsigned char *tag_list , int size);


/**
* @brief 获取一个标签值，使用后在释放tlv_data后统一释放
* @param tlv_data tlv指针
* @param index 标签
* @return 标签值
*/
LIB_EXPORT st_tlv_tag * tlv_get_tag_item(st_tlv_data * tlv_data , int index);

LIB_EXPORT int tlv_get_tag_item_list(st_tlv_data * tlv_data , unsigned char *tag_list);
LIB_EXPORT int tlv_free_tag_item_list(st_tlv_tag_list *tlv_tag_item_list);



LIB_EXPORT int tlv_add_tlvitem(st_tlv_data * tlv_data , unsigned char tag , st_tlv_data *tlvsub );
LIB_EXPORT int tlv_get_tlvitem(st_tlv_data * tlv_data , unsigned char tag , st_tlv_data *tlvsub );