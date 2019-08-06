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
#define   EMV_TAG_5F53_IC_IBAN				"\x5F\x53"		/**<  - 国际银行账户码(International Bank Account Number (IBAN) )*/
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
#define   EMV_TAG_9F19_IC_TOKEN				"\x9F\x19"		/**< Token Data Object）	*/
#define   EMV_TAG_DF61_IC_ODA				"\xDF\x61"		/**< 卡片增值功能 用以指示ODA	*/


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
#define		EMV_TAG_9F4E_TM_NAMELOC			"\x9F\x4E"	  /**< 39- 商户名称地址*/

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
#define EMV_TAG_DF31_IC_IISSCRIRES		"\xDF\x31"	  /**< 15 - 发卡方脚本结果(Issuer Script Results)EMV及PBOC用*/
#define EMV_TAG_9F5B_IC_IISSCRIRES		"\x9F\x5B"	  /**< 15 - 发卡方脚本结果(Issuer Script Results)	*/
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
#define	EMV_TAG_BC_MSD_TEC				"\xBC"		   /**<Terminal Entry Capability*/
#define	EMV_TAG_BB_IC_PK					"\xBB"		   /**<IC卡公钥*/
#define 	EMV_TAG_C5_IC_CTTA				"\xC5"		   /*累计交易总金额*/
#define 	EMV_TAG_C6_IC_CTTAL				"\xC6"		   /*累计交易总金额限制*/
#define 	EMV_TAG_C1_MSD_TRACK1				"\xC1"		   /*MSD一磁道数据*/
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

//EMV_Entry_Point
#define EMV_TAG_9F2A_IC_KERN_ID				"\x9F\x2A"		// Kernel Identifier 
#define	EMV_TAG_9F0A_IC_ASRPD				"\x9F\x0A"		//Application Selection Registered Proprietary Data
#define	EMV_TAG_9F29_IC_EXSEL				"\x9F\x29"		//Extended Selection
//MASTER标签----IC卡数据元
#define   M_TAG_56_IC_TRACK1			"\x56"				// TRACK1
#define	  M_TAG_9F24_IC_PAR					"\x9F\x24"		//Payment Account Reference 
#define   M_TAG_9F50_IC_ACCUBAL				"\x9F\x50"		// Offline Accumulator Balance 脱机累积消费金额
#define   M_TAG_9F51_IC_DRDOL				"\x9F\x51"		// DRDOL – 用于RECOVER AC命令
#define   M_TAG_9F54_IC_DS_ODS_Card			"\x9F\x54"		// DS ODS Card
#define   M_TAG_9F5B_IC_DSDOL				"\x9F\x5B"		// DSDOL – 用于GAC命令
#define   M_TAG_9F5D_IC_APP_CAPA_INFO		"\x9F\x5D"		// Application Capabilities Information 应用性能信息
#define	  M_TAG_9F5E_IC_DS_ID				"\x9F\x5E"		// DS ID
#define	  M_TAG_9F5F_IC_DS_SLOT_AVAILABILITY	"\x9F\x5F"		// DS Slot Availability 
#define   M_TAG_9F60_IC_CVC3_TRACK1			"\x9F\x60"      // CVC3-TRACK1
#define   M_TAG_9F61_IC_CVC3_TRACK2			"\x9F\x61"      // CVC3-TRACK2
#define   M_TAG_9F62_IC_PCVC3_TRACK1			"\x9F\x62"      // PCVC3-TRACK1
#define   M_TAG_9F63_IC_PUNATC_TRACK1		"\x9F\x63"      // PUNATC-TRACK1
#define   M_TAG_9F64_IC_NATC_TRACK1			"\x9F\x64"      // NATC-TRACK1
#define   M_TAG_9F65_IC_PCVC3_TRACK2			"\x9F\x65"      // PCVC3-TRACK2
#define   M_TAG_9F66_IC_PUNATC_TRACK2		"\x9F\x66"      // PUNATC-TRACK2
#define   M_TAG_9F67_IC_NATC_TRACK2			"\x9F\x67"      // NATC-TRACK2
#define   M_TAG_9F69_IC_UDOL					"\x9F\x69"      // UDOL
#define   M_TAG_9F6B_IC_TRACK2				"\x9F\x6B"      // Track 2 Data
#define   M_TAG_9F6D_IC_APPVERNO_MAG			"\x9F\x6D"      // Mag-stripe Application Version Number (Reader)
#define   M_TAG_IC_THIRDPARTY				"\x9F\x6E"      // PayPass Third Party Data   
#define   M_TAG_9F6F_IC_DS_SLOT_MANAGE_CONTROL	"\x9F\x6F"	// DS Slot Management Control
#define	  M_TAG_9F70_IC_PROTECTED_DATA_1		"\x9F\x70"		// Protected Data Envelope 1 
#define	  M_TAG_9F71_IC_PROTECTED_DATA_2		"\x9F\x71"		// Protected Data Envelope 2 
#define	  M_TAG_9F72_IC_PROTECTED_DATA_3		"\x9F\x72"		// Protected Data Envelope 3 
#define	  M_TAG_9F73_IC_PROTECTED_DATA_4		"\x9F\x73"		// Protected Data Envelope 4 
#define	  M_TAG_9F74_IC_PROTECTED_DATA_5		"\x9F\x74"		// Protected Data Envelope 5 
#define	  M_TAG_9F75_IC_UNPROTECTED_DATA_1	"\x9F\x75"		// Unprotected Data Envelope 1 
#define	  M_TAG_9F76_IC_UNPROTECTED_DATA_2	"\x9F\x76"		// Unprotected Data Envelope 2 
#define	  M_TAG_9F77_IC_UNPROTECTED_DATA_3	"\x9F\x77"		// Unprotected Data Envelope 3 
#define	  M_TAG_9F78_IC_UNPROTECTED_DATA_4	"\x9F\x78"		// Unprotected Data Envelope 4 
#define	  M_TAG_9F79_IC_UNPROTECTED_DATA_5	"\x9F\x79"		// Unprotected Data Envelope 5 
#define	  M_TAG_9F7D_IC_DS_SUMMARY_1			"\x9F\x7D"		// DS Summary 1
#define	  M_TAG_9F7F_IC_DS_UNPREDICTABLE_NUMBER	"\x9F\x7F"		// DS Unpredictable Number 
#define	  M_TAG_DF4B_IC_PCII					"\xDF\x4B"		//POS Cardholder Interaction Information 
#define   M_TAG_DF8101_IC_DS_SUMMARY_2			"\xDF\x81\x01"	// DS Summary 2
#define   M_TAG_DF8102_IC_DS_SUMMARY_3			"\xDF\x81\x02"	// DS Summary 3
#define   M_TAG_DF8302_IC_RRP_ENTROPY			"\xDF\x83\x02"	// RRP Device Relay Resistance Entropy 		
#define	  M_TAG_DF8303_IC_RRP_MIN_TIME			"\xDF\x83\x03"	// Min Time For Processing Relay Resistance APDU
#define	  M_TAG_DF8304_IC_RRP_MAX_TIME			"\xDF\x83\x04"	// Max Time For Processing Relay Resistance APDU
#define   M_TAG_DF8305_IC_RRP_TRANSPORT_TIME	"\xDF\x83\x05"	// RRP Device Estimated Transmission Time For Relay Resistance R-APDU


//MASTER标签----终端数据元
#define  M_TAG_DF8301_TM_RRP_TERMINAL_ENTROPY	"\xDF\x83\x01"			//Terminal Relay Resistance Entropy
#define  M_TAG_DF8306_TM_RRP_MEASURE_TIME		"\xDF\x83\x06"			//Measured Relay Resistance Processing Time
#define  M_TAG_DF8307_TM_RRP_COUNTER			"\xDF\x83\x07"			//RRP Counter 

#define  M_TAG_DF61_TM_DS_DIGEST_H 			"\xDF\x61"			//DS Digest H 
#define  M_TAG_DF62_TM_DS_ODS_INFO			"\xDF\x62"			//DS ODS Info 
#define  M_TAG_DF63_TM_DS_ODS_TERM			"\xDF\x63"			//DS ODS Term 
#define  M_TAG_DF60_TM_DS_INPUT_CARD			"\xDF\x60"			//DS Input (Card) 
#define  M_TAG_9F6A_TM_UN_NUMBER				"\x9F\x6A"			//Unpredictable Number (Numeric) 
#define  M_TAG_9F6D_TM_MAG_APP_VER_NUM		"\x9F\x6D"			//Mag-stripe Application Version Number
#define  M_TAG_9F53_TM_TRANSCATECODE			"\x9F\x53"			//Transaction Category Code
#define  M_TAG_9F5C_TM_DS_REQ_OPER_ID		"\x9F\x5C"			//DS Requested Operator ID
#define  M_TAG_9F7C_TM_MERCHANT_CUSTOM_DATA	"\x9F\x7C"			//Merchant Custom Data
#define  M_TAG_9F7E_TM_MOBILE_SUPP			"\x9F\x7E"			//Mobile Support Indicator 手机支持标志
#define  M_TAG_DF8104_TM_BAL_BFGENAC			"\xDF\x81\x04"		//Balance Read before Gene
#define  M_TAG_DF8105_TM_BAL_AFGENAC			"\xDF\x81\x05"		//Balance Read after Gene
#define  M_TAG_DF8106_TM_DATA_NEEDED 			"\xDF\x81\x06"		//Data Needed 
#define  M_TAG_DF8107_TM_CDOL1_DT				"\xDF\x81\x07"		//CDOL1 Related Data
#define  M_TAG_DF8108_TM_DS_AC_TYPE			"\xDF\x81\x08"		//DS AC Type
#define  M_TAG_DF8109_TM_DS_INPUT_TERM			"\xDF\x81\x09"		//DS Input (Term) 
#define  M_TAG_DF810A_TM_DS_ODS_INFO_READER	"\xDF\x81\x0A"		//DS ODS Info For Reader 
#define  M_TAG_DF810B_TM_DS_Summary_Status	"\xDF\x81\x0B"		//DS Summary Status
#define  M_TAG_DF810C_TM_KERNID				"\xDF\x81\x0C"		//Kernel ID
#define  M_TAG_DF810D_TM_DSVN_TERM				"\xDF\x81\x0D"		//DSVN Term
#define  M_TAG_DF810E_TM_POST_GAC_PUTDATA_STATUS	"\xDF\x81\x0E"		//Post-Gen AC Put Data Status
#define  M_TAG_DF810F_TM_PRE_GAC_PUTDATA_STATUS	"\xDF\x81\x0F"		//Pre-Gen AC Put Data Status
#define  M_TAG_DF8110_TM_FIRST_WRITE_FLAG		"\xDF\x81\x10"		// Proceed To First Write Flag 
#define  M_TAG_DF8111_TM_PDOL_DT				"\xDF\x81\x11"		//PDOL Related Data
#define  M_TAG_DF8112_TM_TAGS_TO_READ			"\xDF\x81\x12"		//Tags To Read 
#define  M_TAG_DF8113_TM_DRDOL_DT				"\xDF\x81\x13"		//DRDOL Related Data
#define  M_TAG_DF8114_TM_REFE_CTRL_PARA		"\xDF\x81\x14"      // Reference Control Parameter
#define  M_TAG_DF8115_TM_ERR_INDI				"\xDF\x81\x15"		//Error Indication
#define  M_TAG_DF8116_TM_UI_REQ    			"\xDF\x81\x16"      // User Interface Request Data
#define  M_TAG_DF8117_TM_CARD_INPUT_CAPA		"\xDF\x81\x17"		//Card Data Input Capability
#define  M_TAG_DF8118_TM_MC_CVMCAPA_REQ		"\xDF\x81\x18"		//CVM Capability – CVM Required 
#define  M_TAG_DF8119_TM_MC_CVMCAPA_NOREQ		"\xDF\x81\x19"		//CVM Capability – NO CVM Required
#define  M_TAG_DF811A_TM_DEF_UDOL				"\xDF\x81\x1A"		//Default UDOL
#define  M_TAG_DF811B_TM_KERNCONF				"\xDF\x81\x1B"		//Kernel Configuration
#define  M_TAG_DF811C_TM_MAX_TORN_TIME			"\xDF\x81\x1C"		//Max Lifetime of Torn Transaction Log Record
#define  M_TAG_DF811D_TM_MAX_TORN_NUM			"\xDF\x81\x1D"		//Max Number of Torn Transaction Log Records
#define  M_TAG_DF811E_TM_MS_CVMCAPA_REQ		"\xDF\x81\x1E"		//Mag-stripe CVM Capability – CVM Required
#define  M_TAG_DF811F_TM_SEC_CAPA    			"\xDF\x81\x1F"      // Security Capability

#define  M_TAG_DF8120_TM_TAC_DEFAULT    				"\xDF\x81\x20"      // Terminal Action Code – Default
#define  M_TAG_DF8121_TM_TAC_DENIAL     				"\xDF\x81\x21"      // Terminal Action Code – Denial
#define  M_TAG_DF8122_TM_TAC_ONLINE    				"\xDF\x81\x22"      // Terminal Action Code – Online
#define  M_TAG_DF8123_TM_PPFLOOR_LMT					"\xDF\x81\x23"      // Reader Contactless Floor Limit
#define  M_TAG_DF8124_TM_PPTRAN_LMT_NODC				"\xDF\x81\x24"      // Reader Contactless Transaction Limit (No On-device CVM) 
#define  M_TAG_DF8125_TM_PPTRAN_LMT_ODC				"\xDF\x81\x25"      // Reader Contactless Transaction Limit (On-device CVM) 
#define  M_TAG_DF8126_TM_PPCVM_LMT       				"\xDF\x81\x26"      // Reader CVM Required Limit
#define  M_TAG_DF8127_TM_TIME_OUT_VALUE      			"\xDF\x81\x27"      // Time Out Value 
#define  M_TAG_DF8128_TM_IDS_STATUS       				"\xDF\x81\x28"      // IDS Status 
#define  M_TAG_DF8129_TM_OUTCOME_PAR					"\xDF\x81\x29"		//Outcome Parameter Set
#define  M_TAG_DF812A_TM_DDCARD_TRACK1					"\xDF\x81\x2A"		//DD Card (Track1)
#define  M_TAG_DF812B_TM_DDCARD_TRACK2					"\xDF\x81\x2B"		//DD Card (Track2)
#define  M_TAG_DF812C_TM_MS_CVMCAPA_NOREQ				"\xDF\x81\x2C"		//Mag-stripe CVM Capability – No CVM Required
#define  M_TAG_DF812D_TM_MESG_HOLD_TIME				"\xDF\x81\x2D"		//Message Hold Time

#define  M_TAG_DF8130_TM_HOLD_TIME						"\xDF\x81\x30"		//Hold Time Value
#define  M_TAG_DF8131_TM_PHONE_MESG					"\xDF\x81\x31"		//Phone Message Table
#define  M_TAG_DF8132_TM_RRP_MIN_GRACE_PERIOD			"\xDF\x81\x32"		// Minimum Relay Resistance Grace Period
#define  M_TAG_DF8133_TM_RRP_MAX_GRACE_PERIOD			"\xDF\x81\x33"		// Maximum Relay Resistance Grace Period 
#define  M_TAG_DF8134_TM_RRP_TERM_EXP_TIME_CAPDU		"\xDF\x81\x34"		// Terminal Expected Transmission Time For Relay Resistance C-APDU 
#define  M_TAG_DF8135_TM_RRP_TERM_EXP_TIME_RAPDU		"\xDF\x81\x35"		// Terminal Expected Transmission Time For Relay Resistance R-APDU 
#define  M_TAG_DF8136_TM_RRP_ACCURACY_THRESHOLD		"\xDF\x81\x36"	// Relay Resistance Accuracy Threshold
#define  M_TAG_DF8137_TM_RRP_TRANMSIT_TIME_MISMATCH	"\xDF\x81\x37"	// Relay Resistance Transmission Time Mismatch 


#define  M_TAG_FF8101_TM_TORN_REC    					"\xFF\x81\x01"      // Torn Record
#define  M_TAG_FF8102_TAGS_TO_WRITE_PRE_GAC			"\xFF\x81\x02"      // Tags To Write Before Gen AC
#define  M_TAG_FF8103_TAGS_TO_WRITE_POST_GAC			"\xFF\x81\x03"      // Tags To Write After Gen AC 
#define  M_TAG_FF8104_TAGS_DATA_TO_SEND				"\xFF\x81\x04"      // Data To Send
#define  M_TAG_FF8105_TM_DATA_REC						"\xFF\x81\x05"		//Data Record
#define  M_TAG_FF8106_TM_DISC_DATA						"\xFF\x81\x06"		//Discretionary Data

//PayPass自定义标签
#define  M_TAG_DF8201_TM_DET_INFO				"\xDF\x82\x01"		//DET_INFO
#define  M_TAG_DF8202_TM_ACTIVE_SFI			"\xDF\x82\x02"		//ACTIVE SFI
#define  M_TAG_DF8203_TM_RECR_CERT_RID			"\xDF\x82\x03"		//回收证书RID------针对模拟后台设置添加
#define  M_TAG_DF8204_TM_RECR_CERT_SN			"\xDF\x82\x04"		//回收证书序列号---针对模拟后台设置添加
#define  M_TAG_DF8205_TM_RECR_CERT_INDEX		"\xDF\x82\x05"		//回收证书索引-----针对模拟后台设置添加			||||||| .r20203
#define  M_TAG_DF8206_TM_DEK_INFO_WAIT			"\xDF\x82\x06"		//DET_INFO_WAIT
#define	 M_TAG_DF8207_TM_DEK_INFO				"\xDF\x82\x07"		//DET_INFO_WAIT
#define  M_TAG_DF8208_TM_COFIG_NUM				"\xDF\x82\x08"		//模拟后台配置功能号
#define  M_TAG_DF8209_TM_DISC_TORN_DATA		"\xDF\x82\x09"		//发送带TornRecord的自定义数(PayPass)
#define  M_TAG_DF820A_TM_APDU_SEND				"\xDF\x82\x0A"		//DE APDU发送
#define  M_TAG_DF820B_TM_APDU_RECV				"\xDF\x82\x0B"		//DE APDU接收数据
#define  M_TAG_DF820C_TM_DYNAMIC_DATA		"\xDF\x82\x0C"		//ICC Dynamic Data
#define  M_TAG_DF820E_TM_STOP_SIGNAL		"\xDF\x82\x0D"		//应用端设置STOP信号
#define  M_TAG_DF820F_TM_RA_UPDATE			"\xDF\x82\x0F"		//设置RA更新条件

//VISA标签
#define	EMV_TAG_9F7C_IC_CED					"\x9F\x7C"	/**< Customer Exclusive Data (CED)*/
#define	EMV_TAG_9F6E_IC_FFI					"\x9F\x6E"	/**< Form Factor Indicator (FFI)*/


//RUPAY
//IC卡标签	
#define RP_TAG_DF07_IC_SR_DIR	"\xDF\x07"			//Service Directory 
#define RP_TAG_DF33_IC_SRD		"\xDF\x33"			//Service Related Data
#define RP_TAG_DF3B_IC_SRD		"\xDF\x3B"			//Application Usage Control Extension
#define RP_TAG_DF61_IC_DSR_ID	"\xDF\x61"			//ICC Dynamic Signature Record Identifier
#define RP_TAG_DF16_IC_S_ID		"\xDF\x16"			//Service ID
#define RP_TAG_DF15_IC_SMI		"\xDF\x15"			//Service Management Info
#define RP_TAG_DF20_IC_SATC		"\xDF\x20"			//Service ATC
#define RP_TAG_DF47_IC_PRMISS	"\xDF\x47"			//PRMiss
#define RP_TAG_DF49_IC_PRMICC	"\xDF\x49"			//ICC Service Partial Key (PRMicc) 
#define RP_TAG_DF48_IC_PRMACQ	"\xDF\x48"			//PRMacq 
#define RP_TAG_DF4B_IC_PRE_PRMACQ	"\xDF\x4B"			//Pre PRMacq 
#define RP_TAG_DF54_IC_PRMACQ_KCV	"\xDF\x54"		//PRMacq KCV 

//终端标签
#define RP_TAG_DF22_TM_S_SUMMARY				"\xDF\x22"			// Service Summary
#define RP_TAG_DF23_TM_S_SIGNATURE				"\xDF\x23"			// Service Signature
#define RP_TAG_DF3A_TM_S_CAP_AD_EX				"\xDF\x3A"			// Additional Terminal Capabilities Extension (tag DF3A)
#define RP_TAG_DF4D_TM_CVM_LIMIT				"\xDF\x4D"			//Terminal CVM Limit
#define RP_TAG_DF45_TM_S_TERMINAL_DATA			"\xDF\x45"			//Service Terminal Data
#define RP_TAG_DF4C_TM_TRANC_LIMIT				"\xDF\x4C"			//Contactless Transaction Limit 


//rupay自定义标签
#define DEF_RP_TAG_DF8501_TM_LEGACY_PARAM				"\xDF\x85\x01"		//rupay legacy param
#define DEF_RP_TAG_DF8502_TM_NON_LEGACY_PARAM			"\xDF\x85\x02"		//rupay non legacy param
#define DEF_RP_TAG_DF8503_TM_FUN_SWITCH					"\xDF\x85\x03"		//rupay SWITCH性能 16字节  (CDC/EXCEPT/ADVICE/TORN对应标签的索引字节1,2,3,4,5-16字节RFU)
#define DEF_RP_TAG_DF8504_TM_CVM_CAP					"\xDF\x85\x04"		//rupay CVM性能	16字节 (Online PIN/Signature/NoCvm/qDDA对应标签的索引字节为1,2,3,4),5-16 RFU
#define DEF_RP_TAG_DF8505_TM_RANHOLD					"\xDF\x85\x05"		//rupay 偏置随机选择的阈值
#define DEF_RP_TAG_DF8506_TM_RANMAXPER					"\xDF\x85\x06"		//rupay 偏置随机选择最大百分比
#define DEF_RP_TAG_DF8507_TM_RANTARPER					"\xDF\x85\x07"		//rupay 偏置随机选择目标百分比
#define DEF_RP_TAG_DF8508_TM_DEFAULTTAC					"\xDF\x85\x08"		//rupay 终端行为代码－默认
#define DEF_RP_TAG_DF8509_TM_ONLINETAC					"\xDF\x85\x09"		//rupay 终端行为代码－联机
#define DEF_RP_TAG_DF850A_TM_REFUSETAC					"\xDF\x85\x0A"		//rupay 终端行为代码－拒绝
#define DEF_RP_TAG_DF850A_TM_REFUSETAC					"\xDF\x85\x0A"		//rupay 终端行为代码－拒绝
#define DEF_RP_TAG_DF850B_TM_TORN_TERM_ACTYPE			"\xDF\x85\x0B"		//rupay torn actype
//AEMX 
//IC卡标签
#define AMEX_TAG_9F70_CARD_INTERFACE_AND_PAYMENT_CAP   	     "\x9F\x70"  //Card_Interface_and_Payment_Capabilities
#define AMEX_TAG_9F71_MOBILE_CVM_RESULTS				     "\x9F\x71"  //Mobile_CVM_Results
#define AMEX_TAG_9F1F_TRACK1_DIS_Data						 "\x9F\x1F"  //Track1_Discretionary_Data
#define AMEX_TAG_9F20_TRACK2_DIS_Data						 "\x9F\x20"  //Track2_Discretionary_Data
//终端标签
#define AMEX_TAG_9F6D_CONTACT_READ_CAP             	 "\x9F\x6D"  //Contactless_Reader_Capabilities
#define AMEX_TAG_9F6E_ENHANCED_CONTACT_READ_CAP		 "\x9F\x6E"  //Enhanced_Contactless_Reader_Capabilities
//AMEX自定义标准
#define AMEX_TAG_DF8601_TM_FUN_SWITCH 					 "\xDF\x86\x01"  //drl/delay auth 切换
#define AMEX_TAG_DF8602_DRL_READER_CON_FOOL_LIMIT		 "\xDF\x86\x02"  //default Dynamic Reader Limits-- Reader Contactless Floor Limit
#define AMEX_TAG_DF8603_DRL_READER_CON_TRANS_LIMIT	     "\xDF\x86\x03"  //default Dynamic Reader Limits-- Reader Contactless Transaction Limit
#define AMEX_TAG_DF8604_DRL_READER_CVM_LIMIT			 "\xDF\x86\x04"  //default Dynamic Reader Limits-- Reader CVM Required Limit
#define AMEX_TAG_DF8605_DRL_DATA                         "\xDF\x86\x05"
             //用于存储DRL_for_XXXXb     格式 两个字节长度DRL选项+DRL_READER_CON_TRANS_LIMIT(6b)+DRL_READER_CON_FOOL_LIMIT(6b)+AMEX_TAG_DF8604_DRL_READER_CVM_LIMIT(6b)
			 //后期改成文件下载是否更好
#define AMEX_TAG_DF8606_TM_CHECK_INDICATE                "\xDF\x86\x06"     //B1b8   Reader Contactless Floor Limit check
																		    //B1b7   Reader Contactless Transaction Limit check
																			//B1b6   Reader CVM Required Limit check
																			//B1b5   Reader zero Amount check
																			//B1b4   Reader zero option Amount check
																			//B1b3   Reader static check
																			//B1B2   Reader TM Floor Limit check
//EMV 公共自定义TAG
#define DEF_TAG_ISS_RECOVER_SIGN	"\xDF\x84\x01"		//回收证书标识		0--不存在 1-存在
#define DEF_TAG_TORN_RECORD_DATA	"\xDF\x84\x02"		//闪卡数据
#define DEF_TAG_TRAN_RESULT_STATUS	"\xDF\x84\x03"		//交易结果状态		0--TC  1--ARQC 2--AAC  3--AAR
#define DEF_TAG_PAN_BLACK_LIST		"\xDF\x84\x04"		//卡号黑名单标识	0--不存在 1--存在
#define DEF_TAG_ONLINE_REQ_TYPE		"\xDF\x84\x05"		//联机请求类型		0--授权请求 1--金融请求  2--金融确认  3--批上送


//#define DEF_TAG_DF820D_FORCE_KERNEL_ID			"\xDF\x82\x0D"   //认证宏--不同卡组规范在PPSE和ADF过程逻辑可能不兼容,不兼容的部分可以通过设置对应的内核ID差异处理