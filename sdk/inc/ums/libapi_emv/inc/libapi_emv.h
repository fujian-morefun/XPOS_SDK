#ifndef _LIBAPI_EMV__H__
#define _LIBAPI_EMV__H__

#include "def.h"



//函数功能Emv 内核回调函数，密码输入
//参数说明:
//		入参:cType :提示信息类型1－脱机密码2-最后一次脱机密码3 联机密码
//				chance：脱机PIN 输入剩余次数
//		出参: pszPin：密码明文
//
//返回值:
//		脱机返回： -3 按取消中止交易=0 未输入密码按确认(bypass) > 0 输
//						入的密码长度
//		联机返回：-3 按取消中止交易=0 不输密码直接按确认>0 成功
int EMV_InputPasswd(char cType, ushort chance, char *pszPin);


//函数功能:Emv 内核回调函数，金额输入
//参数说明:入参无
//			      出参Amount：输入的金额，12 字节ASCII 右对齐，左补0
//返回值: EMV_CANCEL = -14, //交易取消
//			EMV_OK = 0 //执行成功
int EMV_InputAmount(byte *Amount);

//获取EMV 库类模块版本号
//入参:无
//出参:pszVer 模块版本号
//返回值:成功返回模块版本号长度
//			UEMV_FAIL = -1, //执行失败
int EMV_GetModuleVer(char *pszVer);

//函数功能:EMV 终端参数始化
//参数说明:入参ptermconfig ：终端参数
//					st_callbackfun; 回调函数
//				出参:无
//返回值: UEMV_PRM_ERR =-8, //EMV 参数错
//			UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
//补充说明:启动应用时调用
//int EMV_TermConfigInit(const TERMCONFIG *ptermconfig, STEMVCALLBACKFUN *st_callbackfun);
int EMV_TermConfigInit(const TERMCONFIG *ptermconfig);

//函数功能:获取内核版本
//参数说明:入参Size ：返回值最大长度
//				出参KernelVersion: 返回的内核版本
//返回值:无
//
void EMV_GetKernelVersion(char *KernelVersion, int size);

//函数功能:清除EMV 内核流水、闪卡记录
//参数说明:入参无
//				出参无
//返回值: UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
//补充说明: 清交易流水时调用
int EMV_ClrWater(void);

//函数功能:根据TAG 获取卡片数据，从卡片中获取TAG 值
//参数说明:入参iSlotType：参见enum SlotType
//					iCardType：参见enum IccType
//					tag: 数据tag
//			出参:DataBuf: 输出数据指针
//					Len: 输出数据长度
//返回值: UEMV_PRM_NOT_FOUND=-3, //EMV 参数未找到
//			UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
//补充说明:支持非接
//int EMV_GetCardData(int iSlotType, int iCardType, char* Tag, byte* DataBuf, int* Len);
int EMV_GetCardData(char* Tag, byte* DataBuf, int* Len);

//函数功能:保存指定tag 的数据，保存到EMV 内核
//参数说明: 入参Tag： tag 值
//					  Len：数据长度	
//					  Value: 数据内容
//				出参无
//返回值: UEMV_PRM_ERR =-8, //EMV 参数错
//			UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
//补充说明:交易过程中用，针对一笔交易；
//				来源于终端的tag 可修改，来源于卡片的tag 无法修改
int EMV_StoreKernelData(char *Tag, int Len, byte *Value);


//函数功能搜索指定tag 的数据，从EMV 内核中获取指定TAG 值
//参数说明:入参Tag: tag 值
//				出参Len：Value 数据长度
//					   Value: 取出的数据内容
//返回值: UEMV_PRM_NOT_FOUND=-3, //EMV 参数未找到
//			UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
//补充说明: 存在此tag，但是此tag 没有初值时，返回UEMV_PRM_FAIL；
//				不存在此tag，但tag 合法，返回UEMV_PRM_NOT_FOUND
int EMV_GetKernelData (char *Tag, int *Len, byte *Value);

//函数功能: 保存AID 参数
//参数说明: 入参pTerminalApps: AID 参数数据指针
//				出参无
//返回值: UEMV_PRM_ERR =-8, //EMV 参数错
//			UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
int EMV_PrmSetAIDPrm(TERMINALAPPLIST *pTerminalApps);

//函数功能: 获取AID 参数
//参数说明: 入参无
//				出参pTerminalApps: AID 参数数据指针
//
//返回值: UEMV_PRM_NOT_FOUND=-3, //EMV 参数未找到
//			UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
int EMV_PrmGetAIDPrm(TERMINALAPPLIST *pTerminalApps);

//函数功能: 删除AID 参数
//参数说明: 入参AID: AID 数据指针
//					 AID_Len: AID 长度
//				出参无
//返回值: UEMV_PRM_NOT_FOUND=-3, //EMV 参数未找到
//			UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
int EMV_PrmDelAIDPrm(byte *AID, byte AID_Len);

//函数功能: 清空AID 参数
//参数说明: 入参无
//				出参无
//返回值: UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
//
int EMV_PrmClearAIDPrmFile(void);

//函数功能: 保存公钥
//参数说明: 入参ppkKey: 公钥结构指针
//				出参无
//返回值: UEMV_PRM_ERR =-8, //EMV 参数错
//			UEMV_PRM_CAPK_CHK_HASH_FAIL=-2, //公钥HASH 校验错误
//			UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
//补充说明:由于国密公钥校验值长度修改，老接口不再适用，请使用
//				EMV_PrmSetCAPKTLV 保存公钥
//
int EMV_PrmSetCAPK(CAPUBLICKEY *ppkKey);

//函数功能: 保存公钥
//参数说明: 入参pCAPK: 公钥数据TLV 格式详见表"认证中心公钥参数"
//			      		  nLen：公钥数据长度
//			       出参无
//返回值: UEMV_PRM_ERR =-8, //EMV 参数错
//			UEMV_PRM_CAPK_CHK_HASH_FAIL=-2, //公钥HASH 校验错误
//			UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
//	
int EMV_PrmSetCAPKTLV(byte *pCAPK, int nLen);

//函数功能: 根据RID 和索引获取公钥
//参数说明: 入参RID: RID 数据
//					PKIndex: 公钥索引
//				出参ppkKey: 获取到的公钥
//返回值: UEMV_PRM_NOT_FOUND=-3, //EMV 参数未找到
//			UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
//补充说明: 由于国密公钥校验值长度修改，老接口不再适用，请使用
//				EMV_PrmGetCAPKTLV
int EMV_PrmGetCAPK(CAPUBLICKEY *ppkKey, byte *RID, byte PKIndex);

//函数功能: 根据RID 和索引获取公钥
//参数说明: 入参RID: RID 数据
//					PKIndex: 公钥索引
//				出参pCAPK: 获取到的公钥数据,TLV 格式,详见表"认证中心公钥参数”
//						pnLen:公钥数据长度
//返回值: UEMV_PRM_NOT_FOUND=-3, //EMV 参数未找到
//			UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
//
int EMV_PrmGetCAPKTLV(byte *pCAPK, int *pnLen, byte *RID, byte PKIndex);

//函数功能: 根据RID 和索引删除公钥
//参数说明: 入参RID: RID 数据
//					 PKIndex: 公钥索引
//				出参
//返回值: UEMV_PRM_NOT_FOUND=-3, //EMV 参数未找到
//			UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
//补充说明: 支持Emv_PrmSetCAPK 及Emv_SetCAPKTLV 保存的公钥
int EMV_PrmDelCAPK(byte *RID, byte PKIndex);

//函数功能:清空公钥数据
//参数说明: 入参无
//				出参无
//返回值: UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
//补充说明: 支持Emv_PrmSetCAPK 及Emv_SetCAPKTLV 保存的公钥
int EMV_PrmClearCAPKFile(void);

//函数功能: EMV/PBOC 简化流程：包括应用选择、发送GPO 命令进行应用初始化
//				读取应用数据
//参数说明: 入参iSlotType：参见enum SlotType
//					iCardType：参见enum IccType
//				出参无
//返回值: UEMV_DECLINED = -15, //交易拒绝
//			UEMV_CANCEL = -14, //交易取消
//			UEMV_ONLINE = -13, //交易应联机
//			UEMV_CVM_FAIL = -12, //持卡人验证失败
//			UEMV_FALLBACK = -8, //交易fallback
//			UEMV_APP_BLOCK = -7, //应用已锁
//			UEMV_CANDIDATELIST_EMPTY = -6, //无共同应用
//			UEMV_PARA_ERR = -5, //参数错
//			UEMV_CARD_BLOCK = -4, //卡片已锁
//			UEMV_COMMAND_FAIL = -3, //读卡失败
//			UEMV_CARD_REMOVED = -2, //交易中卡片被移开
//			UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0 //执行成功
int EMV_ProcessSingleFlow(int iSlotType, int iCardType);

//函数功能: EMV/PBOC 标准流程(联机前)
//		包含的处理流程:包括应用选择、发送GPO 命令进行应用初始化读取应用数据、
//		脱机数据认证、处理限制、持卡人验证、终端风险管理、卡片行为分析
//参数说明: 入参iSlotType：参见enum SlotType
//					iCardType：参见enum IccType
//					OnlineFlag：强制联机标识，0 不强制，1 强制
//				出参pbMessage：错误说明，传入NULL 时，表示无需输出错误说明
//返回值: UEMV_EC_DECLINED = -19, //电子现金脱机拒绝
//			UEMV_DECLINED = -15, //交易拒绝
//			UEMV_CANCEL = -14, //交易取消
//			UEMV_ONLINE = -13, //交易应联机
//			UEMV_CVM_FAIL = -12, //持卡人验证失败
//			UEMV_APP_EXPIRED = -11, //应用已失效
//			UEMV_APP_EFFECT = -10, //应用尚未生效
//			UEMV_AUTH_FAIL = -9, //数据认证失败
//			UEMV_FALLBACK = -8, //交易fallback
//			UEMV_APP_BLOCK = -7, //应用已锁
//			UEMV_CANDIDATELIST_EMPTY = -6, //无共同应用
//			UEMV_PARA_ERR = -5, //参数错
//			UEMV_CARD_BLOCK = -4, //卡片已锁
//			UEMV_COMMAND_FAIL = -3, //读卡失败
//			UEMV_CARD_REMOVED = -2, //交易中卡片被移开
//			UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0 //执行成功
//			UEMV_EC_ACCEPT = 6, //电子现金脱机接受
//			UEMV_OFFLINE_ACCEPT = 7 //标准流程脱机接受
//补充说明:Onlineflag 优先级高于SetParameter 的0001；
//			电子现金脱机接受返回UEMV_EC_ACCEPT，
//			借贷记脱机接受返回UEMV_OFFLINE_ACCEPT
//			电子现金脱机拒绝UEMV_EC_DECLINED，其他拒绝为UEMV_DECLINED；
int EMV_ProcessNormFlow(int iSlotType, int iCardType, int OnlineFlag, byte *pbMessage);

//函数功能: EMV/PBOC 强制流程(联机后)：包含的处理流程：
//					联机处理、发卡行脚本处理、完成	
//参数说明: 入参SlotType：参见enum SlotType
//					CardType：参见enum IccType
//					bCommResult:联机处理结果:2 联机批准,1 联机拒绝,0 通讯失败
//					usAuthResCode：返回码域数据
//					Field55Data：接收到的IC 卡域数据
//					DataLen： 传入的Field55Data 数据长度
//				出参pbMessage：错误说明，传入NULL 时，表示无需输出错误说明
//返回值: UEMV_DECLINED = -15, //卡片拒绝
//			UEMV_PARA_ERR = -5, //入参数据错
//			UEMV_COMMAND_FAIL = -3, //与卡片数据交互失败
//			UEMV_CARD_REMOVED = -2, //交易中卡片被移开
//			UEMV_FAIL = -1, //其它失败
//			UEMV_OK = 0 //执行成功
//补充说明: 入参Field55Data 为解析出来的IC 卡域数据，不带长度；
//			第二次GAC 返回TC 时，返回UEMV_OK；返回AAC 时，返回
//			UEMV_DECLINED；
//			外部认证失败,脚本执行失败等失败原因可通过IC 卡tag 数据分析得到
int EMV_ProcessFroceFlow(int iSlotType, int iCardType, byte bCommResult, 
				char *usAuthResCode, char *Field55Data, uint *DataLen, byte *pbMessage);

//函数功能:获取卡片及终端共同支持的应用
//参数说明: 入参iSlotType：参见enum SlotType
//					iCardType：参见enum IccType
//				出参
//返回值: UEMV_APP_BLOCK = -7, //应用已锁
//			UEMV_CANDIDATELIST_EMPTY = -6, //无共同应用
//			UEMV_PARA_ERR = -5, //参数错
//			UEMV_CARD_BLOCK = -4, //卡片已锁
//			UEMV_COMMAND_FAIL = -3, //读卡失败
//			UEMV_CARD_REMOVED = -2, //交易中卡片被移开
//			UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0 //执行成功
//补充说明:参考PBOC 标准
//				获取的应用列表由API 自行维护
int EMV_GetAppCandidate(int iSlotType, int iCardType);

//函数功能:根据应用优先级将共同支持的应用排序，供用户选择
//参数说明: 入参iSlotType：参见enum SlotType
//					iCardType：参见enum IccType
//				出参
//返回值: UEMV_CANCEL = -14, //交易取消
//			UEMV_APP_BLOCK = -7, //应用已锁
//			UEMV_COMMAND_FAIL = -3, //读卡失败
//			UEMV_CARD_REMOVED = -2, //交易中卡片被移
//			UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0 //执行成功
//补充说明:若终端不支持持卡人选择应用，应自动选择优先级最高的应用；
//			若存在多个优先级相同的应用，可随机选择一个
int EMV_SelectApp(int iSlotType, int iCardType);

//函数功能: 应用初始化，调用GPO 命令通知IC 卡开始交易
//参数说明: 入参iSlotType：参见enum SlotType
//					iCardType：参见enum IccType
//				出参
//返回值: UEMV_APP_NOACCEPT = -18, //应用不接受，可重新选择
//			UEMV_FALLBACK = -8, //交易fallback
//			UEMV_APP_BLOCK = -7, //应用已锁
//			UEMV_PARA_ERR = -5, //参数错
//			UEMV_COMMAND_FAIL = -3, //读卡失败
//			UEMV_CARD_REMOVED = -2, //交易中卡片被移开
//			UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0 //执行成功
int EMV_InitiateApp(int iSlotType, int iCardType);

//函数功能终端获取IC 卡中包含的数据，以完成交易中的各种功能
//参数说明: 入参iSlotType：参见enum SlotType
//					iCardType：参见enum IccType
//				出参
//返回值: UEMV_COMMAND_FAIL = -3, //读卡失败
//			UEMV_CARD_REMOVED = -2, //交易中卡片被移开
//			UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0 //执行成功
//补充说明: 读取卡片中所有数据，数据存储有API 自行维护
int EMV_ReadAppData(int iSlotType, int iCardType);

//函数功能: 脱机数据认证，根据终端及卡片支持情况，执行相应数据认证
//参数说明: 入参iSlotType：参见enum SlotType
//					iCardType：参见enum IccType
//				出参
//返回值: UEMV_AUTH_FAIL = -9, //数据认证失败
//			UEMV_COMMAND_FAIL = -3, //与卡片数据交互失败
//			UEMV_CARD_REMOVED = -2, //交易中卡片被移开
//			UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0 //执行成功
int EMV_DataAuth(int iSlotType, int iCardType);

//函数功能: 交易处理限制，检查IC 卡中的应用与终端中应用的兼容程度，并做必须的调整。
//参数说明: 入参iSlotType：参见enum SlotType
//					iCardType：参见enum IccType
//				出参
//返回值: UEMV_DECLINED = -15, //交易拒绝
//			UEMV_APP_EXPIRED = -11, //应用已失效
//			UEMV_APP_EFFECT = -10, //应用尚未生效
//			UEMV_PARA_ERR = -5, //参数错
//			UEMV_COMMAND_FAIL = -3, //读卡失败
//			UEMV_CARD_REMOVED = -2, //交易中卡片被移开
//			UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0 //执行成功
int EMV_ProcRestrict(int iSlotTyp, int iCardType);

//函数功能终端风险管理是终端为保护收单行、发卡行及支付系统免受欺诈的风险管理。
//参数说明: 入参iSlotType：参见enum SlotType
//					iCardType：参见enum IccType
//				出参
//返回值: UEMV_DECLINED = -15, //交易拒绝
//			UEMV_PARA_ERR = -5, //参数错
//			UEMV_COMMAND_FAIL = -3, //读卡失败
//			UEMV_CARD_REMOVED = -2, //交易中卡片被移开
//			UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0 //执行成功
//补充说明: 风险管理涉及的交易流水数据由API 或内核自行维护
int EMV_TermRiskManage(int iSlotType, int iCardType);

//函数功能: 持卡人验证,将验证当前卡片的使用者是否是卡片中应用授权的人。
//参数说明: 入参iSlotType：参见enum SlotType
//					iCardType：参见enum IccType
//				出参
//返回值: UEMV_DECLINED = -15, //交易拒绝
//			UEMV_CANCEL = -14, //交易取消
//			UEMV_CVM_FAIL = -12, //持卡人验证失败
//			UEMV_PARA_ERR = -5, //参数错
//			UEMV_COMMAND_FAIL = -3, //读卡失败
//			UEMV_CARD_REMOVED = -2, //交易中卡片被移开
//			UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0 //执行成功
int EMV_VerfCardholder(int iSlotType, int iCardType);

//函数功能: 终端行为分析是终端将判断交易是否应该批准为脱机交易、
//			拒绝脱机交易或转为联机交易。
//参数说明: 入参iSlotType：参见enum SlotType
//					iCardType：参见enum IccType
//				出参
//返回值: UEMV_DECLINED = -15, //交易拒绝
//			UEMV_ONLINE = -13, //交易应联机
//			UEMV_PARA_ERR = -5, //参数错
//			UEMV_COMMAND_FAIL = -3, //读卡失败
//			UEMV_CARD_REMOVED = -2, //交易中卡片被移开
//			UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0 //执行成功
int EMV_TermAnalys(int iSlotType, int iCardType);

//函数功能: 电子现金余额查询
//参数说明: 入参SlotType：参见enum SlotType
//					CardType：参见enum IccType
//				出参Amount：金额
//返回值: UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0, //执行成功
//补充说明: 获取电子现金余额，支持接触式、非接触式
int EMV_GetECBalance(int iSlotType, int iCardType, unsigned long *Amount);

//函数功能: 设置非接交易卡BIN 黑名单列表
//参数说明: 入参st_EmvExpBINList：参考struct EMVEXCEPTIONBINLIST
//				出参无
//返回值: UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
//
int EMV_RF_PrmSetExceptionBINList(const EMVEXCEPTIONBINLIST *st_EmvExpBINList);

//函数功能: 获取非接交易卡BIN 黑名单列表
//参数说明: 入参无
//				出参st_EmvExpBINList：参考struct EMVEXCEPTIONBINLIST
//返回值: UEMV_PRM_NOT_FOUND=-3, //EMV 参数未找到
//			UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
int EMV_RF_PrmGetExceptionBINList(EMVEXCEPTIONBINLIST *st_EmvExpBINList);

//函数功能: 删除一个非接交易卡BIN 黑名单
//参数说明: 入参st_EmvExpBIN：参考struct EMVEXCEPTIONBIN
//				出参
//返回值: UEMV_PRM_NOT_FOUND=-3, //EMV 参数未找到
//			UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
int EMV_RF_PrmDelExceptionBIN(const EMVEXCEPTIONBIN *st_EmvExpBIN);

//函数功能: 清空非接交易卡BIN 黑名单列表文件
//参数说明: 入参无
//				出参
//返回值: UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
//
int EMV_RF_PrmClearExceptionBINFile(void);

//函数功能: 非接触式交易处理包括:qPBOC 交易预处理,应用选择,发送GPO 命令
//			进行应用初始化,读取应用数据,脱机数据认证,支持闪卡处理
//参数说明: 入参iSlotType：参见enum SlotType
//					iCardType：参见enum IccType
//					Amount: 金额
//					iEmvRFType: 参见enum EmvRFType
//				出参pbMessage：错误说明，传入NULL 时，表示无需输出错误说明
//返回值: UEMV_QPBOC_DODGE = -20, //闪卡处理失败
//			UEMV_APP_NOACCEPT = -18, //应用不接受，可重新选择
//			UEMV_DECLINED = -15, //交易拒绝
//			UEMV_CANCEL = -14, //交易取消
//			UEMV_CVM_FAIL = -12, //持卡人验证失败
//			UEMV_APP_EXPIRED = -11, //应用已失效
//			UEMV_APP_EFFECT = -10, //应用尚未生效
//			UEMV_AUTH_FAIL = -9, //数据认证失败
//			UEMV_APP_BLOCK = -7, //应用已锁
//			UEMV_CANDIDATELIST_EMPTY = -6, //无共同应用
//			UEMV_PARA_ERR = -5, //参数错
//			UEMV_CARD_BLOCK = -4, //卡片已锁
//			UEMV_COMMAND_FAIL = -3, //读卡失败
//			UEMV_CARD_REMOVED = -2, //交易中卡片被移开
//			UEMV_FAIL = -1, //执行失败
//			UEMV_OTHER_INTERFACE = 1, //请尝试其他通信界面
//			UEMV_QPBOC_OFFLINE = 2, //非接触QPBOC 交易脱机接受
//			UEMV_QPBOC_ONLINE = 3, //非接触QPBOC 交易联机,应用层完成联机处理过程
//			UEMV_PBOC_ONLINE = 4 //非接触PBOC 交易联机,应用层完成联机处理过程
//补充说明: 不包含寻卡，根据EmvRFType 执行不同的非接流程；
//			当笔闪卡处理，回调EMV_cqPBOCDodgeRefresh 刷新界面显示、寻卡；
//			当笔闪卡、全部闪卡处理成功，回调EMV_cqPBOCDogeRemoveTrace 让
//			应用删除失败交易流水；
//			当笔闪卡、全部闪卡处理失败，返回UEMV_QPBOC_DODGE，应用不保
//			存失败交易流水，其他失败返回码保存失败交易流水(闪卡发生时在回调
//			EMV_cqPBOCDodgeRefresh 内记录失败交易流水)。
int EMV_RF_ProcessFlow(int iSlotType, int iCardType, unsigned long *Amount,int iEmvRFType, byte *pbMessage);

//函数功能: 非接触式联机后流程：发卡行认证、发卡行脚本处理等
//参数说明: 入参iSlotType：参见enum SlotType
//					iCardType：参见enum IccType
//					bCommResult: 联机处理结果2 联机批准,1 联机拒绝,0通讯失败
//					usAuthResCode：返回码域数据
//					Field55Data：接收到的IC 卡域数据
//					DataLen： 传入的Field55Data 数据长度
//				出参Field55Data：处理完的IC 卡域数据
//						DataLen： 传出的Field55Data 数据长度
//						pbMessage：错误说明，传入NULL 时，表示无需输出错误说明
//返回值: UEMV_SCRIPT_FAIL = -17, //发卡行脚本执行失败
//			UEMV_ARPC_FAIL = -16, //发卡行认证失败
//			UEMV_DECLINED = -15, //卡片拒绝
//			UEMV_PARA_ERR = -5, //入参数据错
//			UEMV_COMMAND_FAIL = -3, //与卡片数据交互失败
//			UEMV_CARD_REMOVED = -2, //交易中卡片被移开
//			UEMV_FAIL = -1, //其它失败
//			UEMV_OK = 0 //执行成功
//补充说明: 非接PBOC 交易联机后流程
int EMV_RF_OnlineFollowProcess(int iSlotType, int iCardType, byte bCommResult, 
		char *usAuthResCode, char *Field55Data, uint *DataLen, byte *pbMessage);

//函数功能: 非接触式交易完成，非接读卡器下电
//参数说明: 入参iSlotType：参见enum SlotType
//					iCardType：参见enum IccType
//					TransFinal: 0-交易拒绝,1-交易接受
//				出参无
//返回值: UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0, //执行成功
int EMV_RF_Complete(int iSlotType, int iCardType, byte TransFinal);


//带内核非接读卡器(预留)

//函数功能保存AID 参数
int EMV_PCDPrmSetAIDPrm(TERMINALAPPLIST *pTerminalApps);
int EMV_PCDPrmGetAIDPrm(TERMINALAPPLIST *pTerminalApps);
int EMV_PCDPrmDelAIDPrm(byte *AID, byte AID_Len);
//函数功能:清空AID 参数
int EMV_PCDPrmClearAIDPrmFile(void);
//函数功能:保存公钥
int EMV_PCDPrmSetCAPK(CAPUBLICKEY *ppkKey);
//函数功能: 根据RID 和索引获取公钥
int EMV_PCDPrmGetCAPK(CAPUBLICKEY *ppkKey, byte *RID, byte PKIndex);
//函数功能: 根据RID 和索引删除公钥
int EMV_PCDPrmDelCAPK(byte *RID, byte PKIndex);
//函数功能:清空公钥数据
int EMV_PCDPrmClearCAPKFile(void);
//函数功能:设置卡BIN 黑名单列表
int EMV_PCDPrmSetExceptionBINList(const EMVEXCEPTIONBINLIST *st_EmvExpBINList);
//函数功能:获取卡BIN 黑名单列表
int EMV_PCDPrmGetExceptionBINList(EMVEXCEPTIONBINLIST *st_EmvExpBINList);
//函数功能:删除一个卡BIN 黑名单
int EMV_PCDPrmDelExceptionBIN(const EMVEXCEPTIONBIN *st_EmvExpBIN);
//函数功能:清空卡BIN 黑名单列表文件
int EMV_PCDPrmClearExceptionBINFile(void);
//函数功能:非接读卡器参数初始化
int EMV_PCDConfigInit(int iSlotType, const TERMCONFIG *ptermconfig);
//函数功能: 非接触式交易处理包括：qPBOC 交易预处理、寻卡、应用选择、发送GPO
//			命令进行应用初始化、读取应用数据、脱机数据认证
int EMV_PCDProcessFlow(unsigned long *Amount,int iEmvRFType, byte Timeout, byte *pbMessage);
//函数功能: 获取交易结果
int EMV_PCDProcessFlow_GetResult(byte *pbMessage);
//函数功能:取消交易
int EMV_PCDProcessFlow_Cancel(byte *pbMessage);
//函数功能: 非接触式联机后流程：发卡行认证、发卡行脚本处理等
int EMV_PCDOnlineFollowProcess(byte bCommResult, char *usAuthResCode,
		char *Field55Data, uint *DataLen, byte *pbMessage);
//函数功能非接触式交易完成，非接读卡器下电
int EMV_PCDComplete(byte TransFinal);
//函数功能获取电子现金余额
int EMV_PCDGetECBalance(unsigned long *Amount);
//函数功能将外置设备切回密码键盘状态
int EMV_PCDSwitch2Pinpad(void);
//

//////////////////////////////////////////////////////////////////////////////////


//函数功能:按aid 设置检查标记，交易预处理，预处理过程对应
//				PBOC 规范第十二卷6.2.2 章节
//参数说明: 入参iSlotType：参见enum SlotType
//					iCardType：参见enum IccType
//					ptPreProcInfo 参见struct Clss_PreProcInfo
//					ptTransParam 参见struct Clss_TransParam
//				出参无
//返回值: UEMV_PARA_ERR = -5, //参数错
//			UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0, //执行成功
//			UEMV_OTHER_INTERFACE = 1, //请尝试其他通信界面
//补充说明:所有的AID 都不满足预处理要求则返回UEMV_OTHER_INTERFACE；
//				只要一个AID 满足要求返回UEMV_OK；
//				参数错误返回UEMV_PARA_ERR；
//				其他错误返回UEMV_FAIL
//			备注：Clss_PreProcInfo *ptPreProcInfo 参数是数组指针，当
//			Clss_PreProcInfo 的成员aucRFU 的值为“"FF"时，表示终止符，最后一条数据；
//			预处理时需将不满足的AID 从终端应用候选列表中删除，后续通过
//			EMV_RF_AppSlt 与卡片完成AID 匹配
int EMV_RF_PreTransProc(/*int iSlotType, */int iCardType,
			Clss_PreProcInfo *ptPreProcInfo, Clss_TransParam *ptTransParam);

//函数功能:应用选择，建立应用候选列表，最终应用选择，由内核自动选择最高优先级应用
//参数说明: 入参iSlotType：参见enum SlotType
//					 iCardType：参见enum IccType
//				出参pucKernType  最终选择的应用内核类型
//				 	KERNTYPE_JCB：JCB	KERNTYPE_MC:MASTERCARD	
//					KERNTYPE_VIS：VISA     KERNTYPE_PBOC：PBOC
//					KERNTYPE_AE: American Express  
//					    pucDtOut--最终选择时的终端AID 名称，BCD 格式
//					   pnDtLen -- pucDtOut 的数据长度
//返回值: UEMV_APP_NOACCEPT = -18,//重新选择应用，应删除当前应用
//			UEMV_CANDIDATELIST_EMPTY = -6, //无终端支持应用
//			UEMV_PARA_ERR = -5, //参数错
//			UEMV_CARD_BLOCK = -4, //卡片已锁
//			UEMV_CANCEL = -14, //交易取消
//			UEMV_APP_BLOCK = -7, //应用已锁
//			UEMV_COMMAND_FAIL = -3, //读卡失败
//			UEMV_CARD_REMOVED = -2, //交易中卡片被移
//			UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0 //执行成功
//			UEMV_OTHER_INTERFACE = 1, //请尝试其他通信界面
//补充说明: 备注：当非接流程处理过程中遇到重新选择应用的情况之时，会重新调用
//			这个函数接口。即此接口在封装过程中要自动删除当前应用，直接处理
//			终应用选择。
//			如果是非接交易预处理EMV_RF_PreTransProc 后，第一次执行该接口时
//			需要创建候选列表，并执行最终选择。
//			如果返回重新选择应用，则再执行该接口时，只需要删除当前应用后进行
//			最终应用选择。
//			如果第一次授权失败，则再执行该接口时，只需要删除当前应用后进行最
//			终应用选择。
//			如果最终选择时无应用，返回UEMV_OTHER_INTERFACE
int EMV_RF_AppSlt(/*int iSlotType, */int iCardType, uchar *pucKernType,
			uchar *pucDtOut, int *pnDtLen);

//函数功能: 实现GPO 及读应用数据（实现QPBOC 的GP0 和Read Reord ，如果返
//				回的是非接PBOC 路径，也要实现GPO 和Read Record）
//				支持闪卡处理
//参数说明: 入参iSlotType：参见enum SlotType				
//					 iCardType：参见enum IccType
//				出参pucTransPath 交易路径类型
//					CLSS_VISA_QVSDC ：qPBOC 方式  CLSS_VISA_VSDC：完整非接PBOC 方式
//					   pucACType   AC 类型：//QPBOC 才有
//								AC_ AAC, AC_ TC, AC_ ARQC
//					   pucType，只有ARQC 的AC 类型下该参数才有效持卡人认证方式
//					   	RD_CVM_NO： 无持卡人认证
//						RD_CVM_ONLINE_PIN： 联机PIN
//						RD_CVM_SIG： 签名
//					只有AC 类型为TC 的情况，才会需要执行非接第二次授权。
//					如果AC 类型为ARQC，不会执行第二次授权
//返回值: UEMV_APP_NOACCEPT = -18,//重新选择应用，应删除当前应用
//			UEMV_DECLINED = -15, //交易拒绝
//			UEMV_CANCEL = -14, //交易取消
//			UEMV_ONLINE = -13, //交易应联机
//			//如果AC 为AAC 返回UEMV_DECLINED,如果AC 为AC_ ARQC 返回UEMV_ONLINE
//			//如果AC 为TC 或流程切换到非接PBOC 则返回UEMV_OK
//			UEMV_APP_EXPIRED = -11, //应用已失效//QPBOC
//			UEMV_PARA_ERR = -5, //参数错
//			UEMV_COMMAND_FAIL = -3, //读卡失败
//			UEMV_CARD_REMOVED = -2, //交易中卡片被移开
//			UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0, //执行成功
//			UEMV_OTHER_INTERFACE = 1,, //终止非接触交易, 使用接触界面方式执行交易。
//补充说明: 当笔闪卡处理，回调EMV_cqPBOCDodgeRefresh 刷新界面显示、寻卡；
//				当笔闪卡、全部闪卡处理成功，回调EMV_cqPBOCDogeRemoveTrace 让
//				应用删除失败交易流水；
int EMV_RF_1stProctrans (/*int iSlotType, */int iCardType, uchar *pucTransPath, 
				uchar *pucACType, uchar *pucType);

//函数功能: 非接第二次授权，实现脱机数据认证，持卡人认证(只用于QPBOC 交
//				易,1stProctrans ACType 为TC 才执行此函数)
//				如果是QPBOC TC 交易，只需要脱机数据认证，
//				如果此时AC 类型返回ARQC,则需要返回持卡人认证方法
//参数说明: 入参iSlotType：参见enum SlotType
//					iCardType：参见enum IccType
//				出参pucACType 交易须采用的AC 类型(此处可能返回AC_ AAC, AC_ TC, AC_ ARQC）
//					pucType，只有ARQC 的AC 类型下该参数才有效持卡人认证方式
//						RD_CVM_NO： 无持卡人认证
//						RD_CVM_ONLINE_PIN： 联机PIN
//						RD_CVM_SIG： 签名
//返回值: UEMV_QPBOC_DODGE = -20, //闪卡处理失败	
//			UEMV_DECLINED = -15, //交易拒绝
//			UEMV_CANCEL = -14, //交易取消
//			UEMV_ONLINE = -13, //交易应联机
//			UEMV_AUTH_FAIL = -9, //数据认证失败
//			UEMV_PARA_ERR = -5, //参数错
//			UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0, //执行成功
//补充说明: 当笔闪卡、全部闪卡处理失败，返回UEMV_QPBOC_DODGE，应用不保
//			存失败交易流水，其他失败返回码保存失败交易流水(闪卡发生时在回调
//			EMV_cqPBOCDodgeRefresh 内记录失败交易流水)；
//			如fdda 失败，根据9f6c 判断返回UEMV_ONLINE 或UEMV_AUTH_FAIL
int EMV_RF_2sdProctrans(int iSlotType, int iCardType, uchar *pucACType, uchar *pucType);

////////////////////////////////////////////////////
//回调函数的原型及功能说明
////////////////////////////////////////////////////

//函数功能: Emv 内核回调函数，持卡人证件认证
//参数说明: 入参
//				出参
//返回值: UEMV_CANCEL = -14, //交易取消
//			UEMV_CVM_FAIL = -12, //持卡人验证失败
//			UEMV_OK = 0, //执行成功
//
int EMV_cVerifyIDCard(void);

//函数功能: Emv 内核回调函数，应用选择
//参数说明: 入参pstAPPList 应用结构体数组
//						nAPPNum 应用个数
//				出参无
//返回值>=0 表示选择的应用
//			UEMV_CANCEL = -14, //交易取消
//			
int EMV_cSelectAapp(STAPPINFO *pstAPPList, int nAPPNum);

//函数功能: Emv 内核回调函数，当笔闪卡重挥刷新界面提示信息并重新寻卡
//参数说明: 入参psCmdBuf
//					0-发生闪卡，重新挥卡；
//					1-闪卡重挥卡号不符，重新挥卡
//				出参无
//返回值: UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0, //执行成功
//补充说明: psCmdBuf:指令字符串
//				0-回调函数刷新POS 界面提示信息，并等待重新挥卡。函数内部保存static
//				   参数卡号、金额，并保存失败交易流水；
//				1-回调函数刷新POS 界面提示信息，提示新卡卡号与原卡不一致，并等
//				   待重新挥卡
int EMV_cqPBOCDodgeRefresh(void *psCmdBuf);

//函数功能: Emv 内核回调函数，闪卡处理完成回调让应用删除失败的交易流水
//参数说明: 入参无
//				出参无
//返回值: UEMV_FAIL = -1, //执行失败
//			UEMV_OK = 0, //执行成功
//补充说明: 闪卡处理完成，回调该函数让应用删除失败的交易流水
int EMV_cqPBOCDogeRemoveTrace(void);
///////////////////////////////////////////////////////////////////////////////////


//函数功能Emv 内核回调函数设置
//参数说明: 入参pstEMVCALLBACKFUN EMV 回调函数结构体
//				出参无
//返回值: UEMV_PRM_ERR =-4, //EMV 参数错
//			UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
//补充说明: EMV 内核初始化之后调用
int EMV_SetCallbackFun(STEMVCALLBACKFUN2 *pstEMVCALLBACKFUN);

//函数功能: Emv 参数设置
//参数说明: 入参psParameter 参数列表，TLV 格式
//				出参无
//返回值: UEMV_PRM_ERR =-4, //EMV 参数错
//			UEMV_PRM_FAIL=-1, //EMV 参数操作失败
//			UEMV_PRM_OK=0 //EMV 参数操作成功
//补充说明: TLV，4 字节TAG，2 字节HEX 长度LENGTH，长度字节的VALUE
//				0001：是否强制联机，0x00-否，0x01-是（交易流程结束之后必须恢复				
//					为强制联机）；
//				0002：是否支持电子现金，0x00-否，0x01-是（交易流程结束之后必须
//					恢复为不支持电子现金）；
//				0003：是否允许选择被锁应用，0x00-否，0x01-是（交易流程结束之后
//					必须清除状态）；
//				0004：是否支持闪卡处理，0x00-否，0x01-是（EMV 内核初始化之后调
//					用，默认不支持即不处理闪卡直接返回失败（解决新库老应用问题））；
//				0005：闪卡记录可处理时间T2，默认“60”s；
//				0006：保存闪卡记录条数，默认“3”条
//				0007：是否支持国密IC 卡，使用国密公钥脱机数据认证，0x00-否，0x01-
//					是（EMV 内核初始化之后调用）
//
int EMV_SetParameter(char *psParameter);


//函数功能:获取非接流程错误代码
//参数说明:
//				入参	无
//				出参	pnErrorCode 错误代码
//返回值	UEMV_FAIL 				 = -1,		//执行失败
//			UEMV_OK					 =  0,		//执行成功
//补充说明	当非接交易流程返回失败时，可调用此接口
//				获取具体的错误代码，错误代码及其解释详见附录D
int EMV_RF_GetErrorCode(int *pnErrorCode);


#endif
