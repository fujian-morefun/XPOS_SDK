#include "mpos_pub.h"
#include "driver/uart.h"
#include "driver/mf_rtc.h"
#include "pub/tracedef.h"
#include "pub/osl/inc/osl_time.h"
#include "json/inc/json_tokener.h"
#include "pub/common/misc/inc/mfmalloc.h"

#define PKT_SIZE	128


void mpos_pub_check_sum_update(unsigned char * check_value , unsigned char *buff , int length)
{
	int i ; 
	for(i = 0 ; i < length ; i++){
		*check_value = *check_value ^ buff[i];
	}
}


int mpos_uart_send(char * buf, int count)
{
	osl_uart_send(MPOS_PORT_COM , buf , count);
}

void mpay_pub_pack_data(char * buff, char * key , char * val)
{	
	if(strlen(buff) == 0){
		sprintf(buff + strlen(buff),  "%s=%s", key, val);
	}else{
		sprintf(buff + strlen(buff),  "&%s=%s", key, val);
	}

}

static void mpay_pub_pack_json(char * val)
{
	int size = strlen(val);
	char *buff = MALLOC(size + 256);
	int i = 0;
	int j = 0;
	char * item[50];
	int len[50];
	int count = 0;
	char * src = val;
	char key[32] = {0};
	char data[512] = {0};
	int rl = 0;


	memset(buff, 0, size + 256);
	//memset(src, 0, size + 64);
	//strcpy(src, val);

	item[0] = val;
	len[0] = 0;

	for(i = 0; i < size; i++){
		if(*val == '&'){
			count ++;
			item[count] = val + 1;
			len[count] = 0;
		}
		else{
			len[count] ++;
		}
		val ++;
	}
	if(len[count] > 0) count ++;


	strcpy(buff, "{");
	for(i = 0; i < count; i ++){

		memset(key, 0, sizeof(key));
		memset(data, 0, sizeof(data));

		for(j = 0; j <len[i]; j ++){
			if(*(item[i] + j) == '='){
				rl = len[i] - j -1;
				if(j > 0) memcpy(key, item[i], j);
				if(rl > 0)	memcpy(data, item[i] + j + 1, rl);
				sprintf(buff + strlen(buff), "\"%s\":\"%s\",", key, data);
				break;
			}
		}
	}

	buff[strlen(buff) -1] = 0;
	strcat(buff, "}");
	memcpy(src, buff, strlen(buff));

	//APP_TRACE("send buff:%s\r\n", src);

	FREE(buff);
}

//STX(0x4D46)  Data length	 Instruction number  Variable data		ETX(0x02)		
//2bytes		2bytes			 1 byte				variable		1bytes	
int mpos_pub_send_pkt(st_pkt_info  * pkt)
{
	//unsigned char check_sum = 0;
	char head[7] = {0};
	char end[3] = {0};
	char * buf;
	int count = 0;
	char cmd[3] = {0};
	char res[3] = {0};
	char tbuf[256] = {0};
	
	APP_TRACE("mpos_pub_send_pkt");

	buf = MALLOC(sizeof(head) + sizeof(tbuf) + sizeof(end));

	head[0] = STX_CODE_1;
	head[1] = STX_CODE_2;

	sprintf(cmd, "%02d", pkt->func);
	mpay_pub_pack_data(tbuf, "C", cmd);
	res[0] = pkt->ret / 10 + '0';
	res[1] = pkt->ret % 10 + '0';
	mpay_pub_pack_data(tbuf, "R", res);
	mpay_pub_pack_json(tbuf);
	mpos_pub_set_len(&head[2] , strlen(tbuf));
// 	head[4] = pkt->func;
// 	head[5] = pkt->ret / 10 + '0';
// 	head[6] = pkt->ret % 10 + '0';
 
	//mpos_pub_check_sum_update(&check_sum , head  + 2, sizeof(head) - 2);

	//if(len > 0) mpos_pub_check_sum_update(&check_sum , pdata , len);
	
	//end[0] = ETX_CODE;
	strcpy(end, ETX_CODE);
	//mpos_pub_check_sum_update(&check_sum , end , 1);
	//end[1] = check_sum;
	memset(buf, 0, sizeof(buf));
    memcpy(buf, head, strlen(head));
	memcpy(buf+strlen(head), tbuf, strlen(tbuf));
	memcpy(buf+strlen(head)+strlen(tbuf), end, strlen(end));
	count = strlen(head) + strlen(tbuf) + strlen(end);
	mpos_uart_send(buf, count);

	{
		//char tip[32];
		//DATE_TIME_T dt={0};
		//sprintf(tip , "mpos_send_pkt(%02d)[%03d]:%s\r\n" , pkt->func, count, buf);
		//APP_TRACE("mpos_send_pkt(%02d)[%04d]:%s\r\n", pkt->func, count, buf);
//		osl_GetDateTime( &dt);
// 		sprintf(tip , "%02d:%02d:%02d SEND(%04d):" , dt.nHour,dt.nMinute,dt.nSecond, count);
// 		APP_TRACE_BUFF_LOG(buf , count , tip);
	}

	FREE(buf);
	return 0;
}


int mpos_pub_pkt_check(unsigned char * pdata , int len , st_pkt_info  *pkt)
{	
	struct json_object *rootobj=0;
	char temp[5] = {0};

	rootobj = (struct json_object *)json_tokener_parse(pdata);
	if ((int)rootobj > 0)
	{
		mpay_pub_get_json(rootobj, "C", temp, 2);
		APP_TRACE("cmd:%s\r\n" , temp);
		pkt->func = atoi(temp);
		pkt->pbuff = &pdata[0];
		pkt->pbuff[len] = 0;
		pkt->len = len;
		pkt->ret = 0;

		json_object_put(rootobj);
	}

	return 0;
}


void mpos_pub_pack_str(unsigned char * pbuff , unsigned char * str ,int size)
{
	int len;
	len = strlen(str);
	if(len > size) len = size;
	memset(pbuff , 0x20 , size);
	memcpy(pbuff , str , len);
}


int mpos_pub_get_ll_len(unsigned char *pbuff)
{
	int len = 0;
	len = (pbuff[0] & 0xf0) * 16 * 1000 + (pbuff[0] & 0x0f) * 100;
	len +=	(pbuff[1] & 0xf0) * 16 * 10 + (pbuff[1] & 0x0f);
	return len;
}

void mpos_pub_set_ll_len(unsigned char *pbuff , int len)
{
	pbuff[0] = (len / 1000) * 16 + (len / 100 % 10);
	pbuff[1] = (len / 10 % 10) * 16 + (len % 10);
}

int mpos_pub_get_len(unsigned char *pbuff)
{
	int len = 0;
	char temp[5] = {0};

	memcpy(temp, pbuff, 4);
	len = atoi(temp);

	return len;
}

void mpos_pub_set_len(unsigned char *pbuff , int len)
{
	sprintf(pbuff, "%04d", len);		
}

int mpos_pub_unpack_ll_data(unsigned char *pbuff , unsigned char * pdata , int size)
{
	int len;
	len = mpos_pub_get_ll_len(pbuff);
	if(len > size) return 0;
	
	if(len > 0){
		memcpy(pdata , pbuff  + 2, len);
	}


	return len + 2;
}

unsigned int mpos_pub_get_int_2(unsigned char *pbuff)
{
	unsigned int count = 0 ;
	count = pbuff[0] * 256 + pbuff[1];
	return count;
}

unsigned int mpos_pub_get_int_4(unsigned char *pbuff)
{
	unsigned int count = 0 ;
	count = pbuff[0] * 0x1000000 + pbuff[1] * 0x10000 + pbuff[2] * 0x100 + pbuff[3];;
	return count;
}


void mpos_pub_set_int_2(unsigned int count , unsigned char *pbuff)
{
	pbuff[0]  = count % 0x100;
	pbuff[1]  = count / 0x100 % 0x100;
}

void mpos_pub_set_int_4(unsigned int count , unsigned char *pbuff)
{

	pbuff[3]  = count % 0x100;
	pbuff[2]  = count / 0x100 % 0x100;
	pbuff[1]  = count / 0x10000 % 0x100;
	pbuff[0]  = count / 0x1000000 % 0x100;
}


int mpos_pub_atoi(char *pbuff , int len)
{
	char tmp[12];
	int data;
	if(len > 10) return 0;

	memcpy(tmp , pbuff ,len);
	tmp[len] = 0;
	
	data = atoi(tmp);
	return data;
}




int mpos_pub_pkt_tlv_bin(char * buff, int offset, int tag, char * val, int length)
{
	buff[offset++] = tag;
	buff[offset++] =  length / 256;
	buff[offset++] =  length % 256;
	memcpy(buff + offset, val, length);
	return (offset + length);
}

int mpos_pub_pkt_tlv_int2(char * buff, int offset,int tag, int val)
{
	unsigned char bin[2];
	bin[0] = val / 256;
	bin[1] = val % 256;
	return mpos_pub_pkt_tlv_bin(buff, offset, tag, (char *)bin, 2);
}

int mpos_pub_pkt_tlv_int(char * buff, int offset,int tag, int val)
{
	unsigned char bin[1];
	bin[0] = val;
	return mpos_pub_pkt_tlv_bin(buff, offset, tag, (char *)bin, 1);
}

int mpos_pub_pkt_tlv_str(char * buff, int offset,int tag, char * val)
{
	return mpos_pub_pkt_tlv_bin(buff, offset, tag, val, strlen(val));
}


int mpos_pub_pkt_tlv_get(char *buff, int size, int tag1, char * val)
{
	int offset = 0;
	int tag2;
	int length;
	int ret = -1;
	unsigned char * pbuff= (unsigned char *)buff;
	while(offset < size){
		tag2 = buff[offset++];
		length = buff[offset ++] * 256;
		length += buff[offset ++];

		if(tag1 == tag2){
			if(length > 0) memcpy(val, buff + offset, length);
			val[length] = 0;
			ret = 0;
		}
		offset += length;
	}

	return ret;
}

int mpay_pub_get_json(struct json_object * rootobj , char *key , char * val, int size)
{
	int ret = -1;
	struct json_object * itemobj = (struct json_object *) json_object_object_get(rootobj, key);	

	size --;
	strcpy(val, "");
	if (((int)itemobj)> 0){
		char *pdata = json_object_to_json_string(itemobj);
		int len = strlen(pdata);
		char *p_ucs = 0;
		char *p_asc = 0;

		p_ucs = (char*)malloc(len+1);
		p_asc = (char*)malloc(len+1);
		memset(p_ucs,0,len+1);
		memset(p_asc,0,len+1);

		strcpy(p_ucs, pdata);
		ret = utf8str2astr(p_ucs,strlen(p_ucs),p_asc,len+1);

		if(ret>=strlen(p_ucs)){ //Conversion failed
			strcpy(val,p_ucs);
			free(p_ucs);
			free(p_asc);
			return 1;
		}

		if(strlen(p_asc) < size){
			strcpy(val,p_asc);
		}
		else{
			memcpy(val, p_asc, size);
			val[size] = 0;
		}


		free(p_ucs);
		free(p_asc);
		ret = 1;
	}

	return ret;
}
