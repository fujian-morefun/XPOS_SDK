#ifndef _EMV_TAG_
#define _EMV_TAG_

/*
* 卡片ICC数据元标签
*/
#define   EMV_TAG_9F26_IC_AC 				"\x9F\x26"		/**<  0 - 应用密文(Application Cryptogram)*/
#define   EMV_TAG_9F42_IC_APPCURCODE 		"\x9F\x42"		/**<  1 - 应用货币代码(Application Currency Code)*/
#define   EMV_TAG_9F44_IC_APPCUREXP		"\x9F\x44"		/**<  2 - 应用货币指数(Application Currency Exponent)*/
#define   EMV_TAG_9F05_IC_APPDISCDATA		"\x9F\x05"		/**<  3 - 应用自定义数据(Application Discretionary Data)*/
#define   EMV_TAG_5F25_IC_APPEFFECTDATE	"\x5F\x25"		/**<  4 - 应用生效日期(Application Effective Date)YYMMDD*/
#define   EMV_TAG_5F24_IC_APPEXPIREDATE	"\x5F\x24"		/**<  5 - 应用失效日期(Application Expiration Date)YYMMDD*/
#define   EMV_TAG_94_IC_AFL					"\x94"			/**<  6 - 应用文件定位器AFL(Application File Locator)	*/
#define   EMV_TAG_4F_IC_AID					"\x4F"			/**<  7 - 应用标识符AID(Application Identifier) */
#define   EMV_TAG_82_IC_AIP					"\x82"			/**<  8 - 应用交互特征AIP(Application Interchange Profile) */
#define   EMV_TAG_50_IC_APPLABEL			"\x50"			/**<  9 - 应用标签(Application Label) */
#define   EMV_TAG_9F12_IC_APNAME 			"\x9F\x12"		/**< 10 - 应用首选名称(Application Preferred Name) */
#define   EMV_TAG_5A_IC_PAN				"\x5A"			/**< 11 - 应用主帐号PAN(Application Primary Account Number) */
#define   EMV_TAG_5F34_IC_PANSN			"\x5F\x34"		/**< 12 - 应用主帐号序号PAN_Sn(Application Primary Account Number Sequence Number) */
#define   EMV_TAG_87_IC_APID				"\x87"			/**< 13 - 应用优先标识符(Application Priority Indicator)*/
#define   EMV_TAG_9F3B_IC_APCUR			"\x9F\x3B"		/**< 14 - 应用首选货币(Application Preference Currency)*/
#define   EMV_TAG_9F43_IC_APCUREXP		"\x9F\x43"		/**< 15 - 应用首选货币指数(Application Preferece Currency Exponent)*/
#define   EMV_TAG_61_IC_APPTEMP			"\x61"			/**< 16 - 应用模板(Application Template)*/
#define   EMV_TAG_9F36_IC_ATC				"\x9F\x36"		/**< 17 - 应用交易计数器ATC(Application Transaction Counter)*/
#define   EMV_TAG_9F07_IC_AUC				"\x9F\x07"		/**< 18 - 应用用途控制AUC(Application Usage Control)*/
#define   EMV_TAG_9F08_IC_APPVERNO		"\x9F\x08"		/**< 19 - 应用版本号(Application Version Number)*/
#define	  EMV_TAG_5F54_IC_BIC				"\x5F\x54"		/**<  - 发卡行标识码(Bank Identifier Code (BIC))*/
#define   EMV_TAG_8C_IC_CDOL1				"\x8C"			/**< 20 - 卡片风险管理数据对象列表1CDOL1(Card Risk Management Data Object List 1)*/
#define   EMV_TAG_8D_IC_CDOL2				"\x8D"			/**< 21 - 卡片风险管理数据对象列表2CDOL2(Card Risk Management Data Object List 2)*/
#define   EMV_TAG_5F20_IC_HOLDERNAME 		"\x5F\x20"		/**< 22 - 持卡人姓名(Cardholder Name)*/
#define   EMV_TAG_9F0B_IC_HOLDERNAMEEX 	"\x9F\x0B"		/**< 23 - 持卡人扩展姓名(Cardholder Name Extended)*/
#define   EMV_TAG_8E_IC_CVMLIST			"\x8E"			/**< 24 - 持卡人验证方法列表(Cardholder Verification Method List)*/
#define   EMV_TAG_8F_IC_CAPKINDEX			"\x8F"			/**< 25 - 认证中心公钥索引(Certification Authority Public Key Index)*/
#define   EMV_TAG_9F27_IC_CID				"\x9F\x27"		/**< 26 - 密文信息数据CID(Cryptogram Infomation Data)*/
#define   EMV_TAG_9F45_IC_DTAUTHCODE 		"\x9F\x45"		/**< 27 - 数据认证码(Data Authentication Code)*/
#define   EMV_TAG_84_IC_DFNAME 			"\x84"			/**< 28 - DF名称(Dedicated File Name)*/
#define   EMV_TAG_9D_IC_DDFNAME			"\x9D"			/**< 29 - 目录定义文件DDF名称(Directory Definition File)*/
#define   EMV_TAG_73_IC_DIRDISCTEMP		"\x73"			/**< 30 - 目录自定义模板(Directory Discretionary Template)*/
#define   EMV_TAG_9F49_IC_DDOL				"\x9F\x49"		/**< 31 - 动态数据认证数据对象列表DDOL(Dynamic Data Authentication Data Object List)*/
#define   EMV_TAG_BF0C_IC_FCIDISCDATA		"\xBF\x0C"		/**< 32 - FCI发卡行自定义数据(File Control Information Issuer Discretionary Data)*/
#define   EMV_TAG_A5_IC_FCIPROPTEMP		"\xA5"			/**< 33 - FCI专用模板(File Control Information Proprietary Template)*/
#define   EMV_TAG_6F_IC_FCITEMP			"\x6F"			/**< 34 - FCI模板(File Control Information Template)*/
#define   EMV_TAG_9F4C_IC_ICCDYNNUM		"\x9F\x4C"		/**< 35 - IC卡动态数(ICC Dynamic Number)*/
#define   EMV_TAG_9F2D_IC_PECERT 			"\x9F\x2D"		/**< 36 - IC卡PIN加密公钥证书(ICC PIN Encipherment Public Key Certificate)*/
#define   EMV_TAG_9F2E_IC_PEEXP			"\x9F\x2E"		/**< 37 - IC卡PIN加密公钥指数(ICC PIN Encipherment Public Key Exponent)*/
#define   EMV_TAG_9F2F_IC_PERMD			"\x9F\x2F"		/**< 38 - IC卡PIN加密公钥余项(ICC PIN Encipherment Public Key Remainder)*/
#define   EMV_TAG_9F46_IC_ICCPKCERT		"\x9F\x46"		/**< 39 - IC卡公钥证书(ICC Public Key Certificate)*/
#define   EMV_TAG_9F47_IC_ICCPKEXP			"\x9F\x47"		/**< 40 - IC卡公钥指数(ICC Public Key Exponent)*/
#define   EMV_TAG_9F48_IC_ICCPKRMD			"\x9F\x48"		/**< 41 - IC卡公钥余项(ICC Public Key Remainder)*/
#define   EMV_TAG_5F53_IC_IBAN				"\x5F\X53"		/**<  - 国际银行账户码(International Bank Account Number (IBAN) )*/
#define   EMV_TAG_9F0D_IC_IAC_DEFAULT		"\x9F\x0D"		/**< 42 - 发卡行行为代码-缺省(Issuer Action Code-Default)*/
#define   EMV_TAG_9F0E_IC_IAC_DENIAL 		"\x9F\x0E"		/**< 43 - 发卡行行为代码-拒绝(Issuer Action Code-Denial)*/
#define   EMV_TAG_9F0F_IC_IAC_ONLINE 		"\x9F\x0F"		/**< 44 - 发卡行行为代码-联机(Issuer Action Code-Online)*/
#define   EMV_TAG_9F10_IC_ISSAPPDATA 		"\x9F\x10"		/**< 45 - 发卡行应用数据(Issuer Application Data)*/
#define   EMV_TAG_9F11_IC_ISSCTINDEX 		"\x9F\x11"		/**< 46 - 发卡行代码表索引(Issuer Code Table Index)*/
#define   EMV_TAG_5F28_IC_ISSCOUNTRYCODE "\x5F\x28"		/**< 47 - 发卡行国家代码(Issuer Country Code)*/
#define	EMV_TAG_5F55_IC_ALPHA2 			"\x5F\X55"		/**<  - 终端国家代码(Issuer Country Code (alpha2 format) )*/
#define	EMV_TAG_5F56_IC_ALPHA3			"\x5F\X56"		/**<  - 终端国家代码(Issuer Country Code (alpha3 format)  )*/
#define 	EMV_TAG_42_IC_IIN					"\x42"			/**<  - 发卡行认证代码(Issuer Identification Number (IIN)  )*/
#define   EMV_TAG_90_IC_ISSPKCERT			"\x90"			/**< 48 - 发卡行公钥证书(Issuer Public Key Certificate)*/
#define   EMV_TAG_9F32_IC_ISSPKEXP			"\x9F\x32"		/**< 49 - 发卡行公钥指数(Issuer Public Key Exponent)*/
#define   EMV_TAG_92_IC_ISSPKRMD			"\x92"			/**< 50 - 发卡行公钥余项(Issuer Public Key Remainder)*/
#define   EMV_TAG_5F50_IC_ISSURL 			"\x5F\x50"		/**< 51 - 发卡行URL(Issuer URL)*/
#define   EMV_TAG_5F2D_IC_LANGPREF		"\x5F\x2D"		/**< 52 - 首选语言(Language Preference)*/
#define   EMV_TAG_9F13_IC_LASTATC			"\x9F\x13"		/**< 53 - 上次联机ATC寄存器(Last Online Application Transaction Counter Register)*/
#define   EMV_TAG_9F14_IC_LCOL				"\x9F\x14"		/**< 54 - 连续脱机交易下限(Lower Consecutive Offline Limit)*/
#define   EMV_TAG_9F17_IC_PINTRYCNTR 		"\x9F\x17"		/**< 55 - PIN重试计数器(Personal Identification Number Try Counter)*/
#define   EMV_TAG_9F38_IC_PDOL				"\x9F\x38"		/**< 56 - 处理选项数据对象列表PDOL(Processing Options Data Object List)*/
#define   EMV_TAG_80_IC_RMTF1				"\x80"			/**< 57 - 响应消息模板格式1(Response Message Template Format 1)*/
#define   EMV_TAG_77_IC_RMTF2				"\x77"			/**< 58 - 响应消息模板格式2(Response Message Template Format 2)*/
#define   EMV_TAG_5F30_IC_SERVICECODE		"\x5F\x30"		/**< 59 - 服务码(Service Code)*/
#define   EMV_TAG_88_IC_SFI					"\x88"			/**< 60 - 短文件标识符SFI(Short File Indicator)*/
#define   EMV_TAG_9F4B_IC_SIGNDYNAPPDT	"\x9F\x4B"		/**< 61 - 签名的动态应用数据(Signed Dynamic Application Data)*/
#define   EMV_TAG_93_IC_SIGNSTAAPPDT		"\x93"			/**< 62 - 签名的静态应用数据(Signed Static Application Data)*/
#define   EMV_TAG_9F4A_IC_SDATAGLIST 		"\x9F\x4A"		/**< 63 - 静态数据认证标签列表(Static Data Authentication Tag List)*/
#define   EMV_TAG_9F1F_IC_TRACK1DATA 		"\x9F\x1F"		/**< 64 - 1磁道自定义数据(Track 1 Discretionary Data)*/
#define   EMV_TAG_9F20_IC_TRACK2DATA 		"\x9F\x20"		/**< 65 - 2磁道自定义数据(Track 2 Discretionary Data)*/
#define   EMV_TAG_57_IC_TRACK2EQUDATA	"\x57"			/**< 66 - 2磁道等效数据(Track 2 Equivalent Data)*/
#define   EMV_TAG_97_IC_TDOL				"\x97"			/**< 67 - 交易证书数据对象列表TDOL(Transaction Certificate Data Object List)*/
#define   EMV_TAG_9F23_IC_UCOL				"\x9F\x23"		/**< 68 - 连续脱机交易上限(Upper Consecutive Offline Limit)	*/
#define	EMV_TAG_70_TEMP					"\x70"			/**< 69 - 基本数据模板70	*/
#define	EMV_TAG_9F61_IC_CERTNO			"\x9F\x61"		/**< 70 - 证件号*/
#define	EMV_TAG_9F62_IC_CERTTYPE			"\x9F\x62"		/**< 71 - 证件类型*/	
#define 	EMV_TAG_9F4D_IC_PBOCLOG			"\x9F\x4D"		/**< 72 - PBOC LOG*/
#define	EMV_TAG_9F4F_IC_PBOCLOGFORMAT	"\x9F\x4F"		/**< 73 - PBOC LOG格式*/
#define EMV_TAG_DF4D_IC_UPLOAD_FORMAT "\xDF\x4D"  /**<  圈存的交易日志格式*/

#define EMV_TAG_9F69_IC_CERTIFCATION_DATA        "\x9F\x69"  /**< 卡片认证相关数据*/
#define EMV_TAG_9F63_IC_IDENTIFY_INFOR           "\x9F\x63"  /**< 卡片标识信息 ***/

#define   EMV_TAG_9F24_IC_PAR				"\x9F\x24"		/**< PAR （主账户参考号）	*/


/*
* 终端TERM数据元标签
*/
#define   EMV_TAG_9F01_TM_ACQID			"\x9F\x01"	  /**< 0 - 收单行标识符(Acquirer Identifier)*/
#define   EMV_TAG_9F40_TM_CAP_AD 		  	"\x9F\x40"	  /**< 1 - 附加终端性能(Additional Terminal Capability)*/
#define   EMV_TAG_81_TM_AUTHAMNTB	   	"\x81"		  /**< 2 - 授权金额|二进制(Amount,Authorised<Binary>)*/
#define   EMV_TAG_9F02_TM_AUTHAMNTN	   	"\x9F\x02"	  /**< 3 - 授权金额|数字(Amount,Authorised<Binary>)*/
#define   EMV_TAG_9F04_TM_OTHERAMNTB 	"\x9F\x04"	  /**< 4 - 其他金额|二进制(Amount,Other<Binary>)*/
#define   EMV_TAG_9F03_TM_OTHERAMNTN 	"\x9F\x03"	  /**< 5 - 其他金额|数字(Amount,Other<Numeric>)*/
#define   EMV_TAG_9F3A_TM_REFCURAMNT 	"\x9F\x3A"	  /**< 6 - 参考货币金额(Amount,Reference Currency)*/
#define   EMV_TAG_9F06_TM_AID			  	"\x9F\x06"	  /**< 7 - 终端AID(Terminal Application Identifier)*/
#define   EMV_TAG_9F09_TM_APPVERNO		"\x9F\x09"	  /**< 8 - 终端应用版本号(Terminal Application Version Number)*/
#define	  EMV_TAG_5F57_TM_ACCOUNTTYPE	"\x5F\x57"	  /**< 9- 账户类型(Account Type)*/
#define   EMV_TAG_8A_TM_ARC			   	"\x8A"		  /**< 10 - 授权响应码ARC(Authorisation Response Code)*/
#define   EMV_TAG_9F34_TM_CVMRESULT	   	"\x9F\x34"	  /**< 11 - 持卡人验证方法结果(Cardholder Verification Method Results)*/
#define   EMV_TAG_9F22_TM_CAPKINDEX		"\x9F\x22"	  /**< 12 - 终端CA公钥索引(Terminal Certification Authority Public Key Index)*/
#define   EMV_TAG_9F1E_TM_IFDSN			"\x9F\x1E"	  /**< 13 - IFD序列号(Interface Device Serial Number)*/
#define	  EMV_TAG_83_TM_COMTEM			"\x83"		   /**<14- 命令模板(Command Template )*/
#define   EMV_TAG_86_TM_ISSSCRCMD		   	"\x86"		  /**< 15 - 发卡行脚本命令(Issuer Script Command)*/
#define   EMV_TAG_9F18_TM_ISSSCRID		   	"\x9F\x18"	  /**< 16 - 发卡行脚本标识符(Issuer Script Identifier)*/
#define   EMV_TAG_9F15_TM_MCHCATCODE 	"\x9F\x15"	  /**< 17 - 商户分类码(Merchant Category Code)*/
#define   EMV_TAG_9F16_TM_MCHID			"\x9F\x16"	  /**< 18 - 商户标识符(Merchant Identifier)*/
#define   EMV_TAG_9F39_TM_POSENTMODE 	"\x9F\x39"	  /**< 19 - POS输入模式(Point-of-Service Entry Mode)*/ //推荐磁条卡交易：02接触式借贷记：05qPBOC：07非接触借贷记：98
#define   EMV_TAG_9F33_TM_CAP			   	"\x9F\x33"	  /**< 20 - 终端性能(Terminal Capabilities)*/
#define   EMV_TAG_9F1A_TM_CNTRYCODE	   	"\x9F\x1A"	  /**< 21 - 终端国家代码(Terminal Country Code)*/
#define   EMV_TAG_9F1B_TM_FLOORLMT		"\x9F\x1B"	  /**< 22 - 终端限额(Terminal Floor Limit)*/
#define   EMV_TAG_9F1C_TM_TERMID 		   	"\x9F\x1C"	  /**< 23 - 终端标识符(Terminal Identification)*/
#define   EMV_TAG_9F1D_TM_RMDATA 		   	"\x9F\x1D"	  /**< 24 - 终端风险管理数据(Terminal Risk Management Data)*/
#define   EMV_TAG_9F35_TM_TERMTYPE		"\x9F\x35"	  /**< 25 - 终端类型(Terminal Type)*/
#define   EMV_TAG_95_TM_TVR			   	"\x95"		  /**< 26 - 终端验证结果TVR(Terminal Verification Result)*/
#define   EMV_TAG_98_TM_TCHASH 		   	"\x98"		  /**< 27 - 交易证书哈希值(Transaction Certificate Hash Value)*/
#define   EMV_TAG_5F2A_TM_CURCODE		   	"\x5F\x2A"	  /**< 28 - 交易货币代码(Transaction Currency Code)*/
#define   EMV_TAG_5F36_TM_CUREXP 		   	"\x5F\x36"	  /**< 29 - 交易货币指数(Transaction Currency Exponent)*/
#define   EMV_TAG_9A_TM_TRANSDATE	   		"\x9A"		  /**< 30 - 交易日期(Transaction Date)*/
#define   EMV_TAG_99_TM_PINDATA		   	"\x99"		  /**< 31 - PIN数据(Transaction Personal Identification Number Data)*/
#define   EMV_TAG_9F3C_TM_REFCURCODE 	   	"\x9F\x3C"	  /**< 32 - 交易参考货币代码(Transaction Reference Currency Code)*/
#define   EMV_TAG_9F3D_TM_REFCUREXP		"\x9F\x3D"	  /**< 33 - 交易参考货币指数(Transaction Reference Currency Exponent)*/
#define   EMV_TAG_9F41_TM_TRSEQCNTR	   	"\x9F\x41"	  /**< 34 - 交易序列计数器(Transcation Sequence Counter)*/
#define   EMV_TAG_9B_TM_TSI			   	"\x9B"		  /**< 35 - 交易状态信息TSI(Transaction Status Information)*/
#define   EMV_TAG_9F21_TM_TRANSTIME	   	"\x9F\x21"	  /**< 36 - 交易时间(Transaction Time)*/
#define   EMV_TAG_9C_TM_TRANSTYPE	   		"\x9C"		  /**< 37 - 交易类型(Transaction Type)*/
#define   EMV_TAG_9F37_TM_UNPNUM 		   	"\x9F\x37"	  /**< 38 -  不可预知数(Unpredictable Number) */
#define 	EMV_TAG_9F4E_TM_NAMELOC			"\x9F\x4E"	  /**< 39- 商户名称地址*/

/**<发卡行数据*/
#define   EMV_TAG_89_TM_AUTHCODE		"\x89"		  /**< 授权码(Authorization Code)*/
#define   EMV_TAG_91_TM_ISSAUTHDT	   	"\x91"		  /**<  发卡行认证数据(Issuer Authentication Data)*/
#define   EMV_TAG_71_ISS_RMTF			"\x71"		   /**< 发卡行脚本数据71模板*/
#define   EMV_TAG_72_ISS_RMTF			"\x72"		   /**< 发卡行脚本数据72模板*/
#define   EMV_TAG_71_ISS_SCRIPT		0x3F		   /**< 发卡行脚本数据71模板*/
#define   EMV_TAG_72_ISS_SCRIPT		0x7F		   /**< 发卡行脚本数据72模板*/

/**<以下为银联AID参数定义*/
#define	EMV_TAG_DF01_TM_ASI				"\xDF\x01"	  /**< 1 - 应用选择指示符,	指明终端是否支持AID部分匹配方式*/
#define	EMV_TAG_DF11_TM_DEFAULTTAC		"\xDF\x11"	  /**< 2 - 终端行为代码－默认*/
#define	EMV_TAG_DF12_TM_ONLINETAC		"\xDF\x12"	  /**< 3 - 终端行为代码－联机*/
#define	EMV_TAG_DF13_TM_REFUSETAC		"\xDF\x13"	  /**< 4 - 终端行为代码－拒绝*/
#define	EMV_TAG_DF14_TM_DDOL			"\xDF\x14"	  /**< 5 - 缺省动态数据认证数据对象列表(变长)*/
#define	EMV_TAG_DF15_TM_RANHOLD			"\xDF\x15"	  /**< 6 - 偏置随机选择的阈值*/
#define	EMV_TAG_DF16_TM_RANMAXPER		"\xDF\x16"	  /**< 7 - 偏置随机选择的最大目标百分数*/
#define	EMV_TAG_DF17_TM_RANTARPER		"\xDF\x17"	  /**< 8 - 随机选择的目标百分数*/
#define	EMV_TAG_DF18_TM_ONLINEPINCAP	"\xDF\x18"       /**< 9 - 终端联机PIN能力*/
#define	EMV_TAG_DF02_TM_CAPKMOD		"\xDF\x02"	  /**< 9 - (CAPK)认证中心模*/
#define	EMV_TAG_DF03_TM_CAPKCHECKSUM	"\xDF\x03"	  /**< 10 - 认证中心公钥校验和*/	
#define	EMV_TAG_DF04_TM_CAPKEXPONENT	"\xDF\x04"	  /**< 11 - 认证中心公钥指数*/
#define	EMV_TAG_DF05_TM_CAPKEXPIRE		"\xDF\x05"	  /**< 12 - 认证中心公钥有效期*/
#define	EMV_TAG_DF06_TM_CAPKHASHFLAG	"\xDF\x06"	  /**< 13 - 认证中心公钥哈希算法标识*/
#define	EMV_TAG_DF07_TM_CAPKALGORITHM	"\xDF\x07"	  /**< 14 - 认证中心公钥算法标识*/
#define	EMV_TAG_DF08_TM_CAINDEX			"\xDF\x08"	  /**< 14 - 认证中心公钥序列号 认证用*/
#define EMV_TAG_DF31_IC_IISSCRIRES		"\xDF\x31"	  /**< 15 - 发卡方脚本结果(Issuer Script Results)	*/
#define EMV_TAG_DF69_TM_SM				"\xDF\x69"		/**< 16 - SM算法支持指示器*/
#define EMV_TAG_9F63_TM_BIN				"\x9F\x63"		/**< */
#endif


/**<自定义标签*/
#define	EMV_TAG_B0_TM_PDOL				"\xB0"		   /**<PDOL*/
#define	EMV_TAG_B1_TM_DDOL1				"\xB1"		   /**<DDOL1*/
#define	EMV_TAG_B2_TM_DDOL2				"\xB2"		   /**<DDOL2*/
#define	EMV_TAG_B3_TM_DTDOL				"\xB3"		   /**<终端缺省TDOL*/
#define	EMV_TAG_B4_TM_ISSPK				"\xB4"		   /**<发卡行公钥*/
#define	EMV_TAG_B8_TM_DYNAMICSIG		"\xB8"		   /**<动态签名认证数据*/
#define	EMV_TAG_B9_TM_AUTHDATA			"\xB9"		   /**<静态认证数据*/
#define	EMV_TAG_BD_TM_ONLINEPIN			"\xBD"		   /**<联机密码密文*/
#define	EMV_TAG_99_TM_ONLINEPIN			"\x99"		   /**<联机密码密文 用于检测中心自动化测试工具定义*/
#define	EMV_TAG_BE_MSD_TRACK2			"\xBE"		   /**< MSD二磁道数据*/
#define	EMV_TAG_BF_IC_TRACK2_EXPIRY		"\xBA"		   /**< 二磁道有效期*/
#define	EMV_TAG_BB_IC_PK					"\xBB"		   /**<IC卡公钥*/
#define 	EMV_TAG_C5_IC_CTTA				"\xC5"		   /*累计交易总金额*/
#define 	EMV_TAG_C6_IC_CTTAL				"\xC6"		   /*累计交易总金额限制*/
/**< 电子现金 EC 支持双币种卡片数据*/
#define	EMV_TAG_DF79_IC_DOUBLE_CUR_EC_BALANCE				"\xDF\x79"	/**< 电子现金余额（EC Balance）*/
#define	EMV_TAG_DF77_IC_DOUBLE_CUR_EC_BALANCELIMIT			"\xDF\x77"	/**< 电子现金余额上限（EC Balance Limit）*/
#define	EMV_TAG_DF78_IC_DOUBLE_CUR_EC_STL					"\xDF\x78"	/**< 电子现金单笔交易限额（EC Single Transaction Limit）*/
#define	EMV_TAG_DF76_IC_DOUBLE_CUR_EC_RESETTHRESHOLD		"\xDF\x76"	/**< 电子现金重置阈值（EC Reset Threshold）*/
#define EMV_TAG_DF71_IC_DOUBLE_CUR_EC_CURCODE               "\xDF\x71"	/**< 电子现金货币代码（EC Cur Code）*/
/**< 电子现金 EC卡片数据*/
#define	EMV_TAG_9F79_IC_EC_BALANCE				"\x9F\x79"	/**< 电子现金余额（EC Balance）*/
#define	EMV_TAG_9F77_IC_EC_BALANCELIMIT			"\x9F\x77"	/**< 电子现金余额上限（EC Balance Limit）*/
#define	EMV_TAG_9F74_IC_EC_IAC					"\x9F\x74"	/**< 电子现金发卡行授权码（EC Issuer Authorization Code）*/
#define	EMV_TAG_9F78_IC_EC_STL					"\x9F\x78"	/**< 电子现金单笔交易限额（EC Single Transaction Limit）*/
#define	EMV_TAG_9F6D_IC_EC_RESETTHRESHOLD		"\x9F\x6D"	/**< 电子现金重置阈值（EC Reset Threshold）*/
#define EMV_TAG_9F51_IC_EC_CURCODE               "\x9F\x51"  /**< 电子现金货币代码**/
/**< 电子现金 EC终端数据*/
#define	EMV_TAG_9F7A_TM_EC_TSI					"\x9F\x7A"	/**< 电子现金终端支持指示器（EC Terminal Support Indicator）*/
#define	EMV_TAG_9F7B_TM_EC_TTL					"\x9F\x7B"	/**< 电子现金终端交易限额（EC Terminal Transaction Limit）*/

#define EMV_TAG_DF4F_UPLOAD_FORMAT              "\xDF\x4F" /**< 圈存交易的日期格式*/
#define  EMV_TAG_DF79_UPLOAG_BALANCE             "\xDF\x79" /**< 圈存交易日志的金额**/
/**< 非接触终端数据*/
#define EMV_TAG_9F66_TM_RF_TRANSPROP			"\x9F\x66"	/**< 终端交易属性*/
#define EMV_TAG_DF19_TM_RF_LIMIT					"\xDF\x19"	/**< 非接触终端交易限额*/
#define EMV_TAG_DF20_TM_RF_OFFLINELIMIT			"\xDF\x20"	/**< 非接触终端脱机交易限额*/
#define EMV_TAG_9F5D_IC_RF_BALANCE				"\x9F\x5D"	/**< 脱机可用余额*/
#define EMV_TAG_9F6C_IC_RF_TRANSPROP				"\x9F\x6C"	/**< 卡片交易属性*/
#define EMV_TAG_DF21_TM_CVMLIMIT					"\xDF\x21"	/**< 终端执行CVM限额*/

#define BCTC_TAG_DF8107_TRACK2					"\xDF\x81\x07"//自动化测试工具 二磁道数据
#define BCTC_TAG_DF8105_CERTRS					"\xDF\x81\x05"//自动化测试工具 证书序列号
#define BCTC_TAG_DF8104_CAPTURE					"\xDF\x81\x04"//自动化测试工具 00 表示batch data capture ； 01 表示online data capture。
#define BCTC_TAG_DF8101_TRCC					"\xDF\x81\x01"//自动化测试工具 Transaction Reference Currency Conversion(n8)
#define BCTC_TAG_DF8102_TDOL					"\xDF\x81\x02"//自动化测试工具 default TDOL
#define BCTC_TAG_DF8106_TIMEOUT					"\xDF\x81\x06"//自动化测试工具 0 表示进行交易；FF 表示退出程序；其他表示等待对应时间（单位：秒），随后再次发送交易启动报文
#define BCTC_TAG_DF8103_LOADTYPE				"\xDF\x81\x03"//自动化测试工具 下载参数指示位，可选出现：B8-B6：RFU B5：删除所有交易日志 B4：回收公钥 B3：黑名单 B2：AID B1：CAPK
