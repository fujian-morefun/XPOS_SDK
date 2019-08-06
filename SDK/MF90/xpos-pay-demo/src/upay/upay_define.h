#pragma once

#include "pub\tlv\tlv_func.h"

//业务过程参数相关

#define MAX_LEN_CARD_NUM			19	// 卡号最大长度
#define LEN_CARD_EXP_DATE			4	// 卡有效期

#define PIN_PSW_MAX_LEN				8    // PIN密文数据长度
#define OPER_PSW_LEN				6    // 操作员密码长度
#define GOODS_NO_STR_LEN			30   // 商品编码长度
#define AMOUNT_STR_MAX_LEN			12   // 金额串最大长度
#define EVENT_NO_STR_LEN			30   // 项目编码长度
#define TRANS_CERT_NO_LEN			6    // 交易凭证号长度
#define CARD_NUM_MAX_LEN			19   // 卡号最大长度

#define SERVICE_ENTRY_MODE_LEN		3    // 服务点输入方式码
#define CARD_SEQ_NUM_LEN			3    // 卡片序列号
#define SERCICE_COND_MODE_LEN		2    // 服务点条件码
#define SERVICE_PINCAPCODE_LEN		2    // 服务点PIN获取码
#define AUTH_MECH_CODE_LEN			11   // 授权机构代码长度
#define AUTH_CODE_LEN				6    // 授权码长度
#define MSG_TYPE_CODE_LEN			2    // 消息类型码
#define CARD_CORP_CODE_LEN			3    // 国际信用卡公司代码长度
#define CERTIFICATE_TYPE_LEN		2    // 持卡认证件类别代码长度
#define CERTIFICATE_NUM_LEN			20   // 持卡人证件号码最大长度
#define ACQ_INSTITUE_LEN			11   // 收单行标识码长度
#define ISS_CODE_LEN				11   // 发卡行标识码长度
#define POS_CENTER_CODE_LEN			12   // POS中心标识码长度  
#define POS_TRANS_TYPE_LEN			4    // 交易类型长度
#define POS_TRANS_BATCH_NO_LEN		6    // 交易批次号
#define POS_TRANS_DATE_LEN			4    // 交易日期 MMDD
#define POS_TRANS_TIME_LEN			6    // 交易时间 HHMMSS
#define POS_REFER_NO_LEN			12   // 参考号长度
#define POS_PONITS_LEN				10   // 积分数值串长度
#define MSG_RSP_CODE_LEN			2    // 应答码长度
#define POS_TERMINAL_CODE_LEN		8	 // 终端代码长度
#define POS_MERCHANT_CODE_LEN		15   // 商户代码
#define POS_CURRENCY_CODE_LEN		3    // 交易货币代码
#define POS_TRANS_PROCODE_LEN		6    // 交易处理码
#define POS_SETTLE_TOTAL_LEN		30   // 结算总额串长度
#define POS_INTO_ACCOUNT_NUM_LEN	28	 // 转入账户标志码长度  
#define POS_PHONE_NUM_LEN			11   // 手机号码长度
#define POS_ORDER_NUM_LEN			6    // 预约号码长度
#define POS_CVN2_NUM_LEN			3    // CVN2码长度
#define POS_CERT_NUM_LAST_LEN		6    // 身份证号码后6位
#define POS_ENCRYPT_KEY_LEN			100  // POS中心下发的密钥密文数据 
#define POS_TRACE_1_DATA_LEN		100  //一磁道数据长度
#define POS_TRACE_2_DATA_LEN		37   // 二磁道数据长度
#define POS_TRACE_3_DATA_LEN		104  // 三磁道数据长度
#define POS_TRACE_2_DATA_BCD_LEN	19   // 二磁道数据长度
#define POS_TRACE_3_DATA_BCD_LEN	52	 // 三磁道数据长度
#define POS_TRANS_BILLS_LEN			3    // 交易笔数的字符串长度
#define POS_YEAR_LEN				4    //年份
#define POS_CARDHOLDTYPE_LEN		20   //证件号码长度
#define POS_ISS_EXT_LEN				20   // 发卡行标示扩展
#define POS_CUP_EXT_LEN				20   // 中银联标示扩展
#define POS_ACQ_EXT_LEN				20   // 收单行标示扩展 
#define POS_MONEY_TYPE_LEN			3    //还款币种
#define POS_WIN_POINT_LEN			12   //奖励积分
#define POS_FIRST_HANDPAY_LEN		12   //首期手续费
#define POS_ONCE_HANDPAY_LEN		12   //每期手续费
#define POS_DATA_634_LEN			60   //63.4域长度
#define POS_IC_AID_MAX_LEN			32   // AID最大长度
#define POS_IC_TC_MAX_LEN			16   // IC卡交易证书最大长度
#define POS_DATA_44_LEN				50	 //44域长度
#define FIELD_55_MAX_SIZE			512

typedef struct _st_tmf_param
{
	char sPan[MAX_LEN_CARD_NUM + 1];
	char sAmt[AMOUNT_STR_MAX_LEN + 1];
	char sExpData[LEN_CARD_EXP_DATE + 1];
	char sCardSerialNo[CARD_SEQ_NUM_LEN + 1];
	char sTrack2[POS_TRACE_2_DATA_LEN + 1];
	char sTrack3[POS_TRACE_3_DATA_LEN + 1];
	char sInputMode[SERVICE_ENTRY_MODE_LEN + 1];
	char sPin[PIN_PSW_MAX_LEN + 1];
	int  nPinLen;
	char sField55[FIELD_55_MAX_SIZE+1];
	int nFilde55Len;

	char vCarduseMode[2 + 1];	//服务点输入方式码（用于报文上送的卡使用方式）
	char vPinInputmode[1 + 1];	//服务点方式（是否包含pin）
	char bPIN_getcode;			//PIN获取码
	char bOnlinPin;				//是否输入联机pin
	char bEncryType;			//PIN加密方法
	char bMagEncry;				//磁道加密标志
	char vTmCardmode[2];		//终端读取(卡)能力
	char vICcode[2];			//IC卡条件代码
	char vPartMark[2];			//支持部分扣款和返回余额的标志
	char vCardUse[32];			//卡使用方式，用于记录保存
	char vChName[45 +1];		//持卡人姓名
	char vAccountType[4];		//账户类型，仅在积分消费交易时要求填写。
	char * title;
	int eTransType;

	//发送
	st_tlv_data tlv_send ;

	//接收
	st_tlv_data tlv_recv ;

	//原交易信息
	st_tlv_data old_data ;

	char reversed;
	char mac;
	char manage;
	const char * check_list;

}st_tmf_param;
