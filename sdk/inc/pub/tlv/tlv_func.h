/*! \file tlv_func.h
	\brief tlv function
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
* @brief Create a TLV
* @param tlv_data tlv Pointer
* @param len length
* @return 0 success
*/
LIB_EXPORT int tlv_creat_buff(st_tlv_data * tlv_data , int len);
/**
* @brief Save data to tlv
* @param tlv_data tlv Pointer
* @param buff buffer
* @param len length
* @return 0 success
*/
LIB_EXPORT int tlv_set_buff(st_tlv_data * tlv_data , unsigned char * buff , int len);
/**
* @brief Delete a tag in TLV
* @param tlv_data tlv Pointer
* @param tag Label
* @return 0 success
*/
LIB_EXPORT int tlv_del_tag(st_tlv_data * tlv_data , unsigned char tag);
/**
* @brief Add a tag in TLV
* @param tlv_data tlv Pointer
* @param tag Label
* @param buff buffer
* @param len  data length
* @return 0 success
*/
LIB_EXPORT int tlv_add_tag_bin(st_tlv_data * tlv_data , unsigned char tag , unsigned char * buff , int len);
/**
* @brief Add a string 
* @param tlv_data tlv Pointer
* @param tag Label
* @param buff Character string
* @return 0 success
*/
LIB_EXPORT int tlv_add_tag_str(st_tlv_data * tlv_data , unsigned char tag , unsigned char * buff);
/**
* @briefAdd a shaping
* @param tlv_data tlv Pointer
* @param tag Label
* @param val value
* @param n Filling length
* @return 0 success
*/
LIB_EXPORT int tlv_add_tag_int(st_tlv_data * tlv_data , unsigned char tag , int val , int n);
/**
* @brief Add a long shaping
* @param tlv_data tlv Pointer
* @param tag Label
* @param val vallue
* @param n Filling length
* @return 0 success
*/
LIB_EXPORT int tlv_add_tag_long(st_tlv_data * tlv_data , unsigned char tag , long long val , int n);
/**
* @brief Release a TLV
* @param tlv_data tlv Pointer
* @return 0 success
*/
LIB_EXPORT int tlv_free_buff(st_tlv_data * tlv_data);

/**
* @brief Copy TLV by list
* @param tlv_src The original TLV pointer
* @param tlv_des Aim TLV pointer
* @param tag_list Tag List 0xffEnd
* @return 0 success
*/
LIB_EXPORT int tlv_copy_tag_by_list(st_tlv_data * tlv_src , st_tlv_data * tlv_des , unsigned char *tag_list);

/**
* @brief Get a label value and release it using tlv_free_tag
* @param tlv_data tlv Pointer
* @param tag Label
* @param tlv_tag Label value
* @return >0 success
*/
LIB_EXPORT int tlv_get_tag(st_tlv_data * tlv_data , unsigned char tag , st_tlv_tag * tlv_tag);
LIB_EXPORT int tlv_get_tag_by_index(st_tlv_data * tlv_data , int index , st_tlv_tag * tlv_tag);
/**
* @brief Release TLV tag
* @param tlv_tag Label
* @return 0 success
*/
LIB_EXPORT int tlv_free_tag(st_tlv_tag * tlv_tag);

/**
* @brief et a list of all tags in TLV
* @param tlv_data tlv Pointer
* @param tag_list Tag List
* @param size List size
* @return Number of Actual Lists
*/
LIB_EXPORT int tlv_get_tag_index_list(st_tlv_data * tlv_data , unsigned char *tag_list , int size);


/**
* @brief Get a label value and unify the release of tlv_data after use
* @param tlv_data tlv Pointer
* @param index Label
* @return Label value
*/
LIB_EXPORT st_tlv_tag * tlv_get_tag_item(st_tlv_data * tlv_data , int index);

LIB_EXPORT int tlv_get_tag_item_list(st_tlv_data * tlv_data , unsigned char *tag_list);
LIB_EXPORT int tlv_free_tag_item_list(st_tlv_tag_list *tlv_tag_item_list);



LIB_EXPORT int tlv_add_tlvitem(st_tlv_data * tlv_data , unsigned char tag , st_tlv_data *tlvsub );
LIB_EXPORT int tlv_get_tlvitem(st_tlv_data * tlv_data , unsigned char tag , st_tlv_data *tlvsub );