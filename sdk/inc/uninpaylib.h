#pragma once

int uninpay_init(char *app_path);



//交易性能——交易
//配置顺序见直连规范 表32　支持的交易类型说明
typedef enum _eTRANSTYPE
{
	FUNC_BALANCE = 0,			/**< 查询*/
	//消费类
	FUNC_SALE,				/**< 消费*/
	//预授权类
	FUNC_PREAUTH,				/**< 预授权*/
	FUNC_AUTHSALE,				/**< 预授权完成请求*/
	FUNC_AUTHSALEOFF,			/**< 预授权完成通知*/
	FUNC_AUTHSETTLE,			/**< 预授权结算*/
	FUNC_ADDTO_PREAUTH,			/**< 追加预授权*/
	//退货类
	FUNC_REFUND ,				/**< 退货*/
	//撤销类
	FUNC_VOID_SALE,			/**< 消费撤销*/
	FUNC_VOID_AUTHSALE,			/**< 预授权完成撤销*/
	FUNC_VOID_AUTHSETTLE,		/**< 结算撤销*/
	FUNC_VOID_PREAUTH,			/**< 预授授权撤销*/
	FUNC_VOID_REFUND,			/**< 撤销退货*/
	//离线类
	FUNC_OFFLINE,				/**< 离线结算*/
	FUNC_ADJUST,				/**< 结算调整*/
	//电子钱包类
	FUNC_EP_LOAD,				/**< EP圈存*/
	FUNC_EP_PURCHASE,			/**< EP消费*/
	FUNC_CASH_EP_LOAD,			/**< 现金充值圈存     */
	FUNC_NOT_BIND_EP_LOAD,		/**< 非指定帐户圈存 */
	//分期类
	FUNC_INSTALMENT,			/**< 分期付款*/
	FUNC_VOID_INSTALMENT,		/**< 撤销分期*/
	//积分类
	FUNC_BONUS_IIS_SALE,		/**< 发卡行积分消费*/
	FUNC_VOID_BONUS_IIS_SALE,	/**< 撤销发卡行积分消费*/
	FUNC_BONUS_ALLIANCE,		/**< 联盟积分消费*/
	FUNC_VOID_BONUS_ALLIANCE,	/**< 撤销联盟积分消费*/
	FUNC_ALLIANCE_BALANCE,		/**< 联盟积分查询*/
	FUNC_ALLIANCE_REFUND,		/**< 联盟积分退货*/
	FUNC_INTEGRALSIGNIN,		//收银员积分签到
	//电子现金类
	FUNC_QPBOC,					/**< 快速消费*/
	FUNC_EC_PURCHASE,			/**< 电子现金消费*/
	FUNC_EC_LOAD,				/**< 电子现金指定账户圈存*/
	FUNC_EC_LOAD_CASH,			/**< 电子现金圈存现金*/
	//FUNC_EC_LOAD_NOT_BIND,		/**< 电子现金圈存非指定账户*/
	FUNC_EC_NOT_BIND_OUT,		//电子现金非指定账户圈存转出
	FUNC_EC_NOT_BIND_IN,		//电子现金非指定账户转入
	FUNC_EC_VOID_LOAD_CASH,		/**< 电子现金圈存现金撤销*/
	FUNC_EC_REFUND,				/**< 电子现金脱机退货*/
	FUNC_EC_BALANCE,			/**< 电子现金余额查询*/
	//无卡类
	FUNC_APPOINTMENT_SALE,		/**< 无卡预约消费*/
	FUNC_VOID_APPOINTMENT_SALE,	/**< 撤销无卡预约消费*/
	//磁条充值类
	FUNC_MAG_LOAD_CASH,			/**< 磁条预付费卡现金充值*/
	FUNC_MAG_LOAD_ACCOUNT,		/**< 磁条预付费卡账户充值*/
	//手机芯片类
	FUNC_PHONE_SALE,			/**< 手机芯片消费*/
	FUNC_VOID_PHONE_SALE,		/**< 撤销手机芯片消费*/
	FUNC_REFUND_PHONE_SALE,		/**< 手机芯片退货*/
	FUNC_PHONE_PREAUTH,			/**< 手机芯片预授权*/	
	FUNC_VOID_PHONE_PREAUTH,	/**< 撤销手机芯片预授权*/
	FUNC_PHONE_AUTHSALE,		/**< 手机芯片预授权完成*/
	FUNC_PHONE_AUTHSALEOFF,		/**< 手机芯片完成通知*/
	FUNC_VOID_PHONE_AUTHSALE,	/**< 撤销手机完成请求*/
	FUNC_PHONE_BALANCE,			/**< 手机芯片余额查询*/
	//订购类
	FUNC_ORDER_SALE,			/**< 订购消费*/
	FUNC_VOID_ORDER_SALE,		/**< 订购消费撤销*/
	FUNC_ORDER_PREAUTH,			/**< 订购预授权*/
	FUNC_VOID_ORDER_PREAUTH,	/**< 订购预授权撤销*/
	FUNC_ORDER_AUTHSALE,		/**< 订购预授权完成*/
	FUNC_VOID_ORDER_AUTHSALE,	/**< 订购预授权完成撤销*/
	FUNC_ORDER_AUTHSALEOFF,		/**< 订购预授权完成通知*/
	FUNC_ORDER_REFUND,			/**< 订购退货*/
	//其他
	FUNC_EMV_SCRIPE,			/**< EMV脚本结果通知*/
	FUNC_EMV_REFUND,			/**< EMV脱机退货*/
	FUNC_PBOC_LOG,				/**< 读PBOC日志*/
	FUNC_LOAD_LOG,				/**< 读圈存日志*/
	FUNC_REVERSAL,				/**< 冲正*/
	FUNC_TC,					
	FUNC_SETTLE,					/**< 结算*/
	COUNTTRANSTYPECOUNT,
}TRANSTYPE;

typedef enum _UPAY_RET{
	UPAY_RET_CANCEL = -7,
	UPAY_RET_TIME_OVER = -4,
	UPAY_RET_TERMINATE,

	UPAY_RET_OK = 0,
	UPAY_RET_KEYIN,
	UPAY_RET_MAGTEK,
	UPAY_RET_ICC,
	UPAY_RET_RFID,
	UPAY_RET_FALLBACK_MAGTEK,
	UPAY_RET_FALLBACK_KEYIN,
}UPAY_RET;



typedef struct ___card_reader_info
{
	//input

	//title
	char title[20];
	//amount
	long long amt;
	//trans type
	TRANSTYPE  type;
	//ic data tags
	char icTags[128];
	//ic data tags len
	char icTagsLen;

	
	//output

	//card proc item
	UPAY_RET ret;
	//card pan
	char sPan[20];
	//card expdata
	char sExpData[6];
	//card track2 data
	char sTrack2[37 + 1];
	//card track3 data
	char sTrack3[104 + 1];
	//card Service Code
	char sServiceCode[2 + 1];
	//Card Serial  No
	char sCardSerialNo[4];

	//card IC Data
	char sICdata[512];
	//card IC Data Len
	int nICdatalen;


}cardreader;

// Set Transaction amount
cardreader *cardreader_create(TRANSTYPE type);
// Set Transaction amount
void cardreader_destory(cardreader * info);


// Set Transaction amount
int cardreader_set_amt(cardreader *info , long long amt );
// Set Transaction Title
int cardreader_set_title(cardreader *info , const char *title );

// Add Tag 
int cardreader_add_tag(cardreader *info , const char *tag);


// Card Reader
int cardreader_run(cardreader *info);

// Get IC data
int cardreader_icdata_asc(cardreader *info ,const char * tag , char *buff);

// ic_online Res
int cardreader_ic_onlineRes(cardreader *info ,char *sField55,int nFieldLen);



#define MFSDK_KT_MAINKEY		0x00
#define MFSDK_KT_PINENC			0x01
#define MFSDK_KT_MACENC			0x02
#define MFSDK_KT_MAGDEC			0x03
#define MFSDK_KT_TRANSKEY		0x04


#define MFSDK_ENCRYPT			0x00
#define MFSDK_DECRYPT			0x01


/**
* @brief Save the key in plaintext
* @param [type] Key type, one of MFSDK_KT_MAINKEY to MFSDK_KT_TRANSKEY
* @param [gid] Key Index 0-9
* @param [key] 16-byte key plaintext
* @param [kvc] 4 bytes kvc
* @return 0 succ
*/
int mfsdk_save_plaintext_key(int type, int gid, unsigned char * key, unsigned char *kvc);


/**
* @brief Save the key ciphertext
* @param [type] Key type, one of MFSDK_KT_MAINKEY to MFSDK_KT_MAGDEC
* @param [gid] Key Index 0-9
* @param [key] 16-byte key ciphertext
* @param [kvc] 4 bytes kvc
* @return 0 succ
*/
int mfsdk_save_encrypted_key(int type, int gid, unsigned char * key, unsigned char *kvc);

/**
* @brief Encryption and decryption operation
* @param [type] Key type, one of MFSDK_KT_MAINKEY to MFSDK_KT_MAGDEC
* @param [gid] Key Index 0-9
* @param [mode] MFSDK_ENCRYPT or MFSDK_DECRYPT
* @param [ind] Input data
* @param [size] Data size
* @param [outd] Output Data
* @return 0 succ
*/
int mfsdk_3des_run(int type, int gid, int mode, unsigned char *ind, int size, unsigned char *outd);
