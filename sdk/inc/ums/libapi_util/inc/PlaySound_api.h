#ifndef __PLAYSOUND_API_H
#define __PLAYSOUND_API_H

#define VOICE_SUCCESS				0x01	//1	交易成功
#define VOICE_FAIL					0x02	//2	交易失败
#define VOICE_WAVE_CARD				0x03	//3	请挥卡
#define VOICE_REMOVE_CARD			0x04	//4	请移卡
#define VOICE_LOW_BALANCE			0x05	//5	余额不足
#define VOICE_COLLECTION			0x06	//6	已收款
#define VOICE_HELLO					0x07	//7	您好
#define VOICE_ALIPAY_COLLECTION		0x08	//8	支付宝已收款
#define VOICE_WECHAT_COLLECTION		0x09	//9	微信已收款
#define VOICE_NUMBER_ZERO			0x0A	//10	零
#define VOICE_NUMBER_ONE			0x0B	//11	一
#define VOICE_NUMBER_TWO			0x0C	//12	二
#define VOICE_NUMBER_THREE			0x0D	//13	三
#define VOICE_NUMBER_FOUR			0x0E	//14	四
#define VOICE_NUMBER_FIVE			0x0F	//15	五
#define VOICE_NUMBER_SIX			0x10	//16	六
#define VOICE_NUMBER_SEVEN			0x11	//17	七
#define VOICE_NUMBER_EIGHT			0x12	//18	八
#define VOICE_NUMBER_NINE			0x13	//19	九
#define VOICE_NUMBER_TEN			0x14	//20	十
#define VOICE_NUMBER_DOT			0x15	//21	点
#define VOICE_NUMBER_HUNDRED		0x16	//22	百
#define VOICE_NUMBER_THOUSAND		0x17	//23	千
#define VOICE_NUMBER_TEN_THOUSAND	0x18	//24	万
#define VOICE_YUAN					0x19	//25	元
#define VOICE_TICK					0x1A	//26	滴
#define VOICE_SCAN_BARCODE			0x1B	//27	请扫码
#define VOICE_WAVE_AND_SCAN			0x1C	//28	请扫码或挥卡
#define VOICE_JIAO					0x1D	//29	角
#define VOICE_FEN					0x1E	//30	分
#define VOICE_HUNDRED_MILLION		0x1F	//31	亿
#define VOICE_AMOUNT				0X20	//32	金额
#define VOICE_CONSUME_AMOUNT		0X21	//33	消费金额
#define VOICE_CANCEL_AMOUNT			0X22	//34	撤销金额
#define VOICE_REFUND_AMOUNT			0X23	//35	退货金额
#define VOICE_SCAN_SUCCESS			0X24	//36	扫码成功
#define VOICE_SCAN_FAIL				0X25	//37	扫码失败

/*****************************************************************************
作    者: 成源
版    权: 艾体威尔电子技术(北京)有限公司
函数功能: 打开或语音芯片的功放
入口参数: 无
出口参数: 无
返 回 值: 0 成功  -1 失败 
备	 注: 无 
******************************************************************************/
int PlaySoundOpen_Api(void);

/*****************************************************************************
作    者: 成源
版    权: 艾体威尔电子技术(北京)有限公司
函数功能: 关闭语音芯片的功放
入口参数: 无
出口参数: 无
返 回 值: 0 成功  -1 失败 
备	 注: 无 
******************************************************************************/
int PlaySoundClose_Api(void);

/*****************************************************************************
作    者: 成源
版    权: 艾体威尔电子技术(北京)有限公司
函数功能: 设置语音芯片输出的音量大小
入口参数: Level: 有效范围：0 ~ 15。默认值为15。
出口参数: 无
返 回 值: 0 成功  -1 失败  1 参数无效
备	 注: 无 
******************************************************************************/
int PlaySoundLevel_Api(unsigned char Level);

/*****************************************************************************
作    者: 成源
版    权: 艾体威尔电子技术(北京)有限公司
函数功能: 播放第Num段语音
入口参数: 有效范围：1 ~ 223。实际支持播放语音的内容与个数，需要依据语音芯片当前录入的语音。
出口参数: 无
返 回 值: 0 成功  -1 失败  1 参数无效
备	 注: 无 
******************************************************************************/
int PlaySonudMusic_Api(unsigned char Num);

/*****************************************************************************
作    者: 成源
版    权: 艾体威尔电子技术(北京)有限公司
函数功能: 停止播放语音
入口参数: 无
出口参数: 无
返 回 值: 0 成功  其他失败 
备	 注: 无 
******************************************************************************/
int PlaySoundStop_Api(void);

/*****************************************************************************
作    者: 成源
版    权: 艾体威尔电子技术(北京)有限公司
函数功能: 循环播放第Num段语音
入口参数: 有效范围：1 ~ 223。实际支持播放语音的内容与个数，需要依据语音芯片当前录入的语音。
出口参数: 无
返 回 值: 0 成功  -1 失败  1 参数无效
备	 注: 无 
******************************************************************************/
int PlaySonudLoopMusic_Api(unsigned char Num);

/*****************************************************************************
作    者: 成源
版    权: 艾体威尔电子技术(北京)有限公司
函数功能: 停止循环播放语音
入口参数: 无
出口参数: 无
返 回 值: 0 成功  其他失败 
备	 注: 无 
******************************************************************************/
int PlaySoundLoopStop_Api(void);


#endif



