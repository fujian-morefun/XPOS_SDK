#ifndef __EMV_ERR_CODE_
#define __EMV_ERR_CODE_ 


#define EMV_ERR_INITHASH	                   0x01 //哈希列表未能初始化  <D1>
/**<CAPK错误*/
#define EMV_ERR_CAPK	                       0x02 // CAPK出错 <D4>
#define EMV_ERR_CAPK_NOFOUND		           0x03 //CAPK没有找到 <D4>
#define EMV_ERR_CAPK_VERIFY		               0x04 //CAPK验证出错 <D4>
#define EMV_ERR_CAPK_EXPIRE		               0x05 //CAPK失效 <D4>


/**<AID错误*/
#define EMV_ERR_AID		                       0x06 //AID出错
#define EMV_ERR_AID_GETLIST		               0x07 //读取AID文件，AID为空
#define EMV_ERR_AID_PARAERR		               0x08 //AID参数出错
#define EMV_ERR_AID_MAXNUM		               0x09 //AID超出最大数

/**<ICS错误*/
#define EMV_ERR_ICS		                       0x0A //ICS出错
#define EMV_ERR_ICS_READ			           0x0B //ICS读取出错，交易中止

/**<IC卡操作错误*/
#define VISA_ERR_SWITCH				           0x0C //VISA转界面
#define EMV_ERR_ICCOP						   VISA_ERR_SWITCH
#define EMV_ERR_ICCOP_ERR					   0x0D //APDU未收到返回，L1层错，需要重新寻卡
#define EMV_ERR_ICCOP_POWERUP		           0x0E //IC卡上电出错
#define EMV_ERR_ICCOP_POWERDOWN	               0x0F //IC卡下电出错



/***********************************************************************/
/**<应用选择错误*/
#define EMV_ERR_SELAPP	                      0x10  //应用选择出错    <D1>
/**<应用选择法*/
#define EMV_ERR_SELAPP_PSE			          0x11  //PSE应用选择出错  <D2>

#define EMV_ERR_SELAPP_PSE_UNSUPPORT          0x12  //卡片不支持PSE选择，返6A81  <D3>
#define EMV_ERR_SELAPP_APPLOCK		          0x13  //应用被锁，卡片返回6284    <D3>
#define EMV_ERR_SELAPP_DIRSEL				  0x14  //目录选择出错
#define EMV_ERR_SELAPP_PARSE				  0x15	//PPSE解析错误

/**<AID列表法*/
#define EMV_ERR_AIDLIST		                  0x16  //AID列表法选择出错  <D2>

#define EMV_ERR_AIDLIST_LOCK	              0x17  //AID选择，卡片被锁  <D3>
#define EMV_ERR_AIDLIST_SELOP	              0x18  //AID选择出错   <D3>

#define EMV_ERR_ICCOP_SELECTAID	               0x19 //发送AID选择命令返回负值  <D4>
#define EMV_ERR_ICCOP_SELECTAID_DATA84         0x1A //AID选择84数据长度错       <D4>
#define EMV_ERR_ICCOP_SELECTAID_DATASFI        0x1B //AID选择数据返回没有88 SFI  <D4>
#define EMV_ERR_ICCOP_SELECTAID_SFI            0x1C // AID选择数据返回SFI出错    <D4>
#define EMV_ERR_SELECTAID_NOMATCH			   0X1D	//终端和卡片没有匹配的AID
#define EMV_ERR_SELECTAID_SW1W2_NO_9000		   0X1E	//Select Aid卡片返回非9000
#define EMV_ERR_SELECTAID_PARSE_ERROR		   0X1F	//Select Aid卡片返回数据解析错误
#define EMV_ERR_SELECTAID_DATA_MISS			   0X20	//Select Aid卡片返回数据缺失错误
/**************************************************************************/

/**<初始化应用错误*/
#define EMV_ERR_INITAPP_CHECKGPO			0x21  //应用初始化时GPO命令返回缺少必要数据   <D2>
#define EMV_ERR_INITAPP_GPO_UNPACK			0x22  //GPO返回数据不能正确解析 <D3>
#define EMV_ERR_INITAPP_GPO_LEN				0x23  //GPO 数据长度不正确 <D3>
#define EMV_ERR_INITAPP_GPO_77				0x24  //GPO 77 模板不能解析 <D3>
#define EMV_ERR_INITAPP_GPO_80				0x25  //GPO 77 模板不能解析 <D3>
#define EMV_ERR_INITAPP_GPO_NO82            0x26  //GPO 解析77模板时缺少82必要数据 <D3>
#define EMV_ERR_INITAPP_GPO_NO94            0x27  //GPO 解析77模板时缺少84必要数据 <D3>
#define EMV_ERR_INITAPP_GETOP			    0x28  //应用初始化时GPO命令返回不为9000，不为6985 <D2>

#define EMV_ERR_INITAPP_PACKPDOL		    0x29  //应用初始化时GPO中PDOL打包时出错 <D2>

#define EMV_ERR_INITAPP_SELACCOUNT			0x2A	//账户选择出错
#define EMV_ERR_INITAPP						0x2B  //初始化应用错误     <D1>

#define EMV_ERR_INITAPP_695				    0x2C  //ICC返回6985 <D2>
/**************************************************************************/

/**<读应用数据错误*/
#define EMV_ERR_READAPP					    0x30  //读应用数据错误 <D1>
#define EMV_ERR_READAPP_CDOL1				0x31  //检查应用数据，CDOL1 缺失  <D2>
#define EMV_ERR_READAPP_CDOL2				0x32  //检查应用数据，CDOL2 缺失  <D2>
#define EMV_ERR_READAPP_EXPIREDATE		    0x33  //检查应用数据，应用失效日期缺失或错误     <D2>
#define EMV_ERR_READAPP_APPEFFECTDATE	    0x34  //检查应用数据，应用生效日期缺失或错误 <D2>
#define EMV_ERR_READAPP_START				0x35  //读取应用数据，由于AFL的起始位为0出错（IC卡） <D2>
#define EMV_ERR_READAPP_PARAM			    0x36  //读取应用数据，由于AFL的起始位大于结束位出错（IC卡） <D2>
#define EMV_ERR_READAPP_ICCOP_READ		    0x37  //RR（Read Record）时出错（返回不为9000） <D2>
#define EMV_ERR_READAPP_SFI				    0x38  //RR 命令返回 只有70模板时，SFI才会小于等于10 <D2>
#define EMV_ERR_READAPP_PAN				    0x39  //RR 数据检查，获取IC卡中卡号出错   <D2>
#define EMV_ERR_READAPP_TERM_ON_NEXT_APDU   0x3A  //RR Terminate on Next RA

/**************************************************************************/
/**<脱机认证错误*/
#define EMV_ERR_OFFAUTH					    0x40  //脱机认证失败  <D1>
/**<SDA  */
#define EMV_ERR_OFFAUTH_SDA_FAIL            0x41 //SDA失败  <D2>
#define EMV_ERR_OFFAUTH_SM_SDA_FAIL         0x42 // SM SDA 失败    <D2>
/**<DDA  */
#define EMV_ERR_OFFAUTH_DDA_FAIL		    0x43 // DDA失败 <D2>
#define EMV_ERR_OFFAUTH_SM_DDA_FAIL         0x44 // SM DDA 失败 <D2>
/*< CDA*/
#define EMV_ERR_OFFAUTH_CDA_PREFORM_FAIL    0x45 //CDA的预处理失败 <D2>
#define EMV_ERR_OFFAUTH_SM_CDA_PREFORM_FAIL 0x46  // SM CDA的预处理失败 <D2>

#define EMV_ERR_OFFAUTH_CAPK				0x47 // 获取CA公钥失败 <D3>
#define EMV_ERR_OFFAUTH_ISPK				0x48 //恢复发卡行公钥失败 <D3>
#define EMV_ERR_OFFAUTH_ICPK				0x49 //恢复IC卡公钥失败 <D3>
#define EMV_ERR_OFFAUTH_ISPK_CHECK			0x4A //恢复并验证动态签名数据<D3>
#define EMV_ERR_OFFAUTH_SDATA				0x4B //恢复并验证静态认证数据失败<D3>

#define QPBOC_ERR_SM                        0x4C   // QPBOC中如果SM中脱机认证失败，且终端支持PBOC，则转其它界面  <D1>
//#define QPBOC_ERR_TURN_PBOC                 0x4D   //QPBOC 中如果GPO不存在9F26，且终支持PBOC，则转PBOC <D1>
#define EMV_ERR_OFFAUTH_SIGNDYNAPPDT		0x4E  //内部认证返回数据77，无签名的动态应用数据，交易中止 <D4>

/**<持卡人验证错误*/
#define EMV_ERR_CHVERIFY					0x50  //持卡人验证错误  <D1>
#define EMV_ERR_CHVERIFY_CVMFOMAT		    0x51  //CVM列表长度错误，交易中止 <D2>

/**<行为分析错误*/
#define EMV_ERR_ACT_ANALY_TAA			    0x60  //行为分析中，交易中止	 <D1>
#define EMV_ERR_ACT_ANALY_GAC               0x61   //GAC 命令返回不为9000 <D2>
#define EMV_ERR_ACT_GAC_DATA                0x62    //GAC 解析数据格式不正确 <D2>
#define EMV_ERR_TAA_CID		                0x63  //解析GAC数据CID等级高于终端请求（请求AAC或ARQC但返回TC,交易终止 请求AAC但卡片返回ARQC或TC,交易终止 请求AAC但卡片返回ARQC或TC,交易终止）
#define EMV_ERR_TAA_NOCID		            0x64  //GAC返回数据中没有CID，交易中止 <D3>
#define EMV_ERR_TAA_NOATC		            0x65  //GAC返回数据中没有ATC，交易中止 <D3>
#define EMV_ERR_PARASE_NO_91                0x66 // 解析发卡行自定义数据时没有91 <D3>
#define EMV_ERR_PARASE_91_LEN               0x67 //发卡行自定义数据91 的长度不正确<D3>
//#define EMV_ERR_GAC_CDA						0x68 // cda失败  <D2>
#define EMV_ERR_GAC_CDA_ICPK                0x68 // CDA 恢复IC卡公钥失败 <D3>
#define EMV_ERR_GAC_CDA_ICPK_LEN            0x69  //CDA时IC卡公钥长度不正确 <D3>
#define EMV_ERR_GAC_CDA_CERT                0x6A // CDA证书格式检查失败 <D3>
#define EMV_ERR_GAC_SIGAPPDATA				0x6B//9F4B动态签名数据获取失败
#define EMV_ERR_GAC_ERR_AC					0x6C//密文数据获取失败
#define EMV_ERR_GAC_CID_AAR					0x6C//CID造成的AAR中止

/**< 完成处理*/
#define EMV_ERR_COMPLETE					0x70 //完成处理失败 <d1>
#define EMV_ERR_COMPLETE_ADVICE				0x71 //终端请求联机，且强制通知，但联机失败，交易中止<d2>
#define EMV_ERR_COMPLETE_GAC				0x72  //第二次GAC返回不为9000  <D2>        
#define EMV_ERR_COMPLETE_EC_NO_SCRIPT       0x73 //电子现金圈存，查询的案例联机后没有脚本下发，交易中止 <D2>
#define EMV_ERR_COMPLETE_CID_INTERRUPT      0x74  //卡片密文返回交易中止，交易中止 <D2>
#define EMV_ERR_COMPLETE_PARASE_GAC			0x75 // GAC解析失败 <D2>

/**< qpboc 预处理*/
#define QPBOC_ERR_PRE			            0x80  //qpboc 预处理 <D1>
#define QPBOC_ERR_PRE_AMTLIMIT		        0x81  //授权金额大等于终端非接触交易限额<D2>
#define QPBOC_ERR_PRE_NO_AMT                0x82  //输入金额取消 <D2>
/**< qpboc应用选择*/ 
#define QPBOC_ERR_APPSEL		            0x8B  //QPBOC的应用选择错误 <D1>
#define QPBOC_ERR_PPSE                      0x83  //非接目录选择PPSE失败 <D2>
#define QPBOC_ERR_AMT_CHECK                 0x84   // 交易金额检查失败 <D2>

#define QPBOC_ERR_APPSEL_PPSE	            0x87  //QPBOC应用选择中目录选择返回不为9000 <D3>
#define QPBOC_ERR_APPSEL_MISSBFOC		    0x88  //应用选择丢失BF0C
#define QPBOC_ERR_APPSEL_UNPACKBFOC		    0x89  //应用选择没有打包BF0C
#define QPBOC_ERR_APPSEL_UNPACK61		    0x8A  //QPBOC测试应用选择中没有打包61
/**< qpboc应用初始化*/
#define	QPBOC_ERR_INITAPP                   0x90   //QPBOC应用初始化失败 <D1>
#define QPBOC_ERR_INITAPP_PACKPDOL	        0x91  //QPboc中打包DOL数据出错 <D2>
#define QPBOC_ERR_INITAPP_PDOLNO9F66	    0x92  //QPBOC中Dol数据没有9F66 <D3>
#define QPBOC_ERR_INITAPP_GETGPO            0x93    //获取GPO数据失败 <D2>
#define QPBOC_ERR_INITAPP_CHECK_GPO         0x94  // 检查GPO数据失败 <D2>
#define QPBOC_ERR_INITAPP_GPO6984		    0x95  //QPboc的GPO返回6984，交易中止 <D3>
#define QPBOC_ERR_INITAPP_GPOMISSING82	    0x96  //QPBOC的GPO中没有82<D4>
#define QPBOC_ERR_INITAPP_GETGPO_74         0x97  //QPBOC的GPO中77模板中74解析出错 <D4>
#define QPBOC_ERR_INITAPP_GPO6985		    0x98  //QPboc的GPO返回6985，交易中止 <D3>
#define QPBOC_ERR_INITAPP_GPO6986		    0x99  //QPboc的GPO返回6986，交易中止 <D3>
#define QPBOC_ERR_INITAPP_GPONOLEN		    0x9A  //QPboc的GPO不响应<D3>


/**< 公共部分错误*/
#define EMV_ERR_OFFAUTH_NO_AID_INDEX		0xA0  //脱机认证中恢复CAPK时卡片中没有AID或者CAPK 索引  <D4>
#define EMV_ERR_OFFAUTH_GETINFO_FAIL		0xA1  //获取发卡行中心信息失败   <D4>
#define EMV_ERR_OFFAUTH_RECOVE_ISPK			0xA2  //恢复发卡行公钥失败  <D4>
#define EMV_ERR_OFFAUTH_CHECK				0xA3  //检查恢复数据中的各项不正确 <D4>
#define EMV_ERR_OFFLINE_CONNECTPK			0xA4  //将公钥以一定格式链接出错<D4>
//#define EMV_ERR_OFFAUTH_SIGNDYNAPPDT		0xA5  //内部认证返回数据77，无签名的动态应用数据，交易中止 <D4>
#define EMV_ERR_OFFAUTH_SDA_DATA93          0xA6  //恢复并验证静态认证数据时缺少93 <D4>
#define EMV_ERR_OFFAUTH_DDA_INTERAUTH		0xA7 //内部认证命令返回失败，交易中止 <D4>
#define EMV_ERR_OFFAUTH_DDA_INTERAUTH_FORMAT		0xA8 //内部认证返回数据模板格式不对，交易中止 <D4>
#define EMV_ERR_OFFAUTH_DDA_INTERAUTH_ANALY			0xA9 //内部认证返回数据不能解析出TLV格式 <D4>
#define EMV_ERR_OFFAUTH_DDA_INTERAUTH_DATA80_LEN	0xAA //内部认证返回数据80模板数据长度为0，交易中止 <D4>
#define EMV_ERR_OFFAUTH_DDOL_MIS					0xAB //终端和卡片同时缺少DDOL <D4>
#define EMV_ERR_OFFAUTH_IC_DDOL9F37					0xAC    //卡片DDOL缺少9F37 <D4>

/**< 脱机认证 */
//#define QPBOC_ERR_SM                        0xB0   // QPBOC中如果SM中脱机认证失败，且终端支持PBOC，则转其它界面  <D1>

#define QPBOC_ERR_TURN_PBOC                 0xB1   //QPBOC 中如果GPO不存在9F26，且终支持PBOC，则转PBOC <D1>
#define QPBOC_ERR_FDDA_DDOL_MIS9F37         0xB2//FDDA时准备DDOL的时候缺少9F37 <D1>
#define QPBOC_ERR_FDDA_DDOL_MIS9F02         0xB3//FDDA时准备DDOL的时候缺少9F02 <D1>
#define QPBOC_ERR_FDDA_DDOL_MIS5F2A         0xB4//FDDA时准备DDOL的时候缺少5F2A(交易货币代码) <D1>
#define QPBOC_ERR_FDDA_DDOL_MIS9F69         0xB5//FDDA时准备DDOL的时候缺少9F69(卡片认证相关数据) <D1>

//电子现金相关
#define EMV_ERR_INITAPP_EC_INDICATOR_QUIT   0xC0  // 纯电子现金卡交易类型不匹配或者电子现金应用选择退出 <D2>
#define	EMV_ERR_EC_NO9F74				    0xC1  //指示EC，但EC发卡行代码不存在  <D2>
#define EMV_ERR_EC_BLACKLIST			    0xC2  //应用数据检查时，EC在黑名单中  <D2>
#define EMV_ERR_EC_lEN9F74                  0xC3  //应用数据检查时，9F74的长度不为6 <D2>
#define EMV_ERR_EC_NO9F79                   0xC4  //电子现金中，缺少9F79余额 <D2>
#define EMV_ERR_EC_NO9F6D					0xC5  //电子现金中，缺少9F6D电子现金重置阈值<D2>
#define EMV_ERR_SIMPLE_PROC_EC              0xC6  // 交易类型是简易流程，但是纯电子现金卡 <D1>
#define EMV_ERR_EC_TMLIMIT					0xC7  //电子现金金额超限

/**< 在应用初始化后读取交易日志 */
#define PBOC_ERR_READLOG_NO_BF0C               0xE0  // PBOC读取交易日志或者圈存日志，没有BF0C，无交易日志，交易中止  <D2>
#define PBOC_ERR_READLOG_NO_9F4D               0xE1  // PBOC读取交易日志，没有9F4D，无交易日志，交易中止   <D2>
#define PBOC_ERR_READLOG_9F4D_SFI              0xE2  // PBOC读取交易日志,读取9F4D的SFI范围不在11—30之间，交易中止<D2>
#define PBOC_ERR_READLOG_9F4F_FORMAT           0xE3  // PBOC读取交易日志,get 9F4F格式出错，交易格式错<D2>
#define PBOC_ERR_READLOG_NO_DF4D               0xE4  // PBOC读取圈存日志，没有9F4D，无交易日志，交易中止<D2>
#define PBOC_ERR_READLOG_DF4D_SFI              0xE5  // PBOC读取圈存日志,读取9F4D的SFI范围不在11—30之间，交易中止<D2>
#define PBOC_ERR_READLOG_DF4F_FORMAT           0xE6  // PBOC读取圈存日志,get 9F4F格式出错，交易格式错<D2>

/**< 其他显示类错误*/
#define EMV_ERR_PAN_QUIT                        0xF0	// 提示PAN确认时，用户选择确认取消   <D1>
#define EMV_ERR_SIMPLE_PROC                     0xF1	// 读取应用数据结束，判断为走简易流程 <D1>
#define EMV_ERR_AMT_QUIT                        0xF2	// 提示输入交易金额时，用户选择取消   <D1>
#define EMV_ERR_EC_NOBINDLOAD                   0xF3	// 电子现金非指定账户在脱机认证后返回 <D1>    
#define EMV_ERR_ONLY_EC_NOBINDLOAD              0xF4	// 纯电子现金非指定账户在脱机认证后返回 <D1> 
#define PAYPASS_ERR_CCC_CHECK					0xF5	// PAYPASS CCC 解析错误
#define PAYPASS_ERR_RRP_CHECK					0xF6	// PAYPASS RRP 解析错误
#define EC_ONLY_ERR_RET							-100	// 判断到纯电子现金返回

#endif
