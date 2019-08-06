#pragma once

#include "upay_pub.h"


static const char m_check_list[] = {39, 0, 3, 11, 41, 42 , 60 ,255};
char * upay_pub_check_list()
{
	return (char *)m_check_list;
}

static void upay_pub_init(st_tmf_param  * tmf_param , char * title , int eTransType)
{
	memset(tmf_param, 0, sizeof(st_tmf_param));

	strcpy(tmf_param->vCarduseMode, "00");		// 00	未指明  01	手工	02	磁条		03	条形码
	strcpy(tmf_param->vPinInputmode, "2");		// 0	未指明	1	交易中包含PIN		2	交易中不包含PIN
	tmf_param->bPIN_getcode = 0;					// 是否有pin
	tmf_param->bOnlinPin = 0;					// 是否有pin
	tmf_param->bEncryType = '0';				// PIN加密方法   0：PIN不出现，未知 	1：ANSI X9.8 Format（不带主账号信息）		2：ANSI X9.8 Format（带主账号信息）
	tmf_param->bMagEncry = '0';				// 磁道加密标志   0：不加密 	1：加密
	tmf_param->vTmCardmode[0] = '6';
	tmf_param->vICcode[0] = '0';
	tmf_param->vPartMark[0] = '1';
	tmf_param->title = title;
	tmf_param->eTransType = eTransType;

	memset( &tmf_param->tlv_send,0x00,sizeof(tmf_param->tlv_send));
	memset( &tmf_param->tlv_recv,0x00,sizeof(tmf_param->tlv_recv));
	memset( &tmf_param->old_data,0x00,sizeof(tmf_param->old_data));

	tmf_param->check_list = upay_pub_check_list();
	tmf_param->mac = 1;
	tmf_param->reversed = 1;
	tmf_param->manage = 0;

}

st_tmf_param  * upay_pub_create( int eTransType )
{
	st_tmf_param *ret =(st_tmf_param *) malloc(sizeof(st_tmf_param));	
	upay_pub_init(ret , (char *)"消费" , eTransType);
	return ret;
}

void upay_pub_destory( st_tmf_param * tmf_param )
{
	tlv_free_buff( &tmf_param->tlv_send );
	tlv_free_buff( &tmf_param->tlv_recv );
	tlv_free_buff( &tmf_param->old_data );
	free(tmf_param);
}

