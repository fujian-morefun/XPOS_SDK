#ifndef __EMV_ERR_CODE_
#define __EMV_ERR_CODE_ 
/**************************************/
//流程代码
//static unsigned char gcEmvErrorFLOW = 0;//流程码
#define EMV_PRE_PROCESS_FLOW			0x00
#define EMV_SEL_APP_FLOW				0x01
#define EMV_INIT_APP_FLOW				0x02
#define EMV_READ_DATA_FLOW				0x03
#define EMV_OFF_AUTH_FLOW				0x04
#define EMV_PROCE_RESTRICT_FLOW			0x05
#define EMV_CARDHOLDER_VERIFY_FLOW		0x06
#define EMV_RISK_MANA_FLOW				0x07
#define EMV_ACT_ANALY_FLOW				0x08
#define EMV_COMPLETE_FLOW				0x09

//流程具体错误码
//static unsigned int giEmvErrCode[4] ={0};//错误码
//是对应错误信息
/***********************************************************************/
/**<预处理错误Pre-processing error code*/
/**< qpboc 预处理*/
#define QPBOC_ERR_PRE			            0x0011  //qpboc 预处理出错。qpboc preprocessing error

#define QPBOC_ERR_PRE_AMTLIMIT		        0x0021  //授权金额大等于终端非接触交易限额。amount substantially transaction limit

#define QPBOC_ERR_PRE_ENTERAMT_CANCLE       0x0031  //输入金额取消。Enter amount to cancel


/***********************************************************************/
/**<应用选择错误*/
#define EMV_ERR_SELAPP						  0x0111  //应用选择出错。   Application selection error

/**<应用选择法*/
#define EMV_ERR_SELAPP_PSE			          0x0121  //PSE应用选择出错。  PSE application selection error
#define EMV_ERR_SELAPP_PSE_UNSUPPORT          0x0122  //卡片不支持PSE选择。 Card does not support PSE selection
#define EMV_ERR_SELAPP_APPLOCK		          0x0123  //应用被锁。  is locked
#define EMV_ERR_SELAPP_DIRSEL				  0x0124  //目录选择出错。Dir selection error
#define EMV_ERR_SELAPP_PARSE		  0x0125  //PPSE解析错误。PPSE parsing error

/**<AID列表法*/
#define EMV_ERR_AIDLIST		                  0x0131  //AID列表法选择出错。 AID list method selection error
#define EMV_ERR_AIDLIST_LOCK	              0x0132  //AID选择，卡片被锁。 AID selection, card is locked
#define EMV_ERR_ICCOP_SELECTAID	              0x0134  //发送AID选择命令返回负值。 Send AID select command to return negative value
#define EMV_ERR_ICCOP_SELECTAID_DATA84        0x0135  //AID选择84数据长度错。 AID selection tag84 data length error     
#define EMV_ERR_ICCOP_SELECTAID_DATASFI       0x0136  //AID选择数据返回没有88 SFI。  AID selection data returned without SFI
#define EMV_ERR_ICCOP_SELECTAID_SFI           0x0137  //AID选择数据返回SFI出错。 AID selection data returned SFI error  
#define EMV_ERR_SELECTAID_NOMATCH			  0X0138  //终端和卡片没有匹配的AID。 Terminal and card have no matching AID
#define EMV_ERR_SELECTAID_SW1W2_NO_9000		  0X0139  //Select Aid卡片返回非9000。Select Aid card returns non-9000
#define EMV_ERR_SELECTAID_PARSE_ERROR		  0X013a  //Select Aid卡片返回数据解析错误。Select Aid card returns data parsing error
#define EMV_ERR_SELECTAID_DATA_MISS			  0X013b  //Select Aid卡片返回数据缺失错误。Select Aid card returns missing data error

/**< qpboc应用选择*/ 
#define QPBOC_ERR_APPSEL		            0x0151  //QPBOC的应用选择错误
#define QPBOC_ERR_PPSE                      0x0152  //非接目录选择PPSE失败
#define QPBOC_ERR_AMT_CHECK                 0x0153  //交易金额检查失败 
#define QPBOC_ERR_APPSEL_PPSE	            0x0154  //QPBOC应用选择中目录选择返回不为9000
#define QPBOC_ERR_APPSEL_MISSBFOC		    0x0155  //应用选择丢失BF0C
#define QPBOC_ERR_APPSEL_UNPACKBFOC		    0x0156  //应用选择没有打包BF0C
#define QPBOC_ERR_APPSEL_UNPACK61		    0x0157  //QPBOC应用选择中没有打包61
#define QPBOC_ERR_APPSEL_PPSE6283	        0x0158  //QPBOC应用选择中返回6283

#define EMV_ERR_INITAPP_EC_MISMATCH			0x0161  // 纯电子现金卡交易类型不匹配
#define EMV_ERR_INITAPP_EC_QUIT				0x0162  // 电子现金应用选择退出

#define EMV_ERR_SIMPLE_PROC_EC              0x0171  // 交易类型是简易流程，但是纯电子现金卡 

#define EMV_ERR_SIMPLE_PROC                 0x0181	// 读取应用数据结束，判断为走简易流程 

#define EMV_ERR_EC_TMLIMIT					0x0191  //电子现金金额超限

/**************************************************************************/
/**<初始化应用错误*/
#define EMV_ERR_INITAPP_ERR					0x0211  //初始化应用错误。   Initialization application error

#define EMV_ERR_INITAPP_CHECKGPO			0x0221  //应用初始化时GPO命令返回缺少必要数据。  GPO command returns missing necessary data
#define EMV_ERR_INITAPP_GPO_UNPACK			0x0222  //GPO返回数据不能正确解析。 GPO return data cannot be parsed correctly
#define EMV_ERR_INITAPP_GPO_LEN				0x0223  //GPO 数据长度不正确。 GPO data length is incorrect
#define EMV_ERR_INITAPP_GPO_77				0x0224  //GPO 77 模板不能解析。 GPO 77 template cannot be parsed
#define EMV_ERR_INITAPP_GPO_80				0x0225  //GPO 80 模板不能解析。 GPO 80 template cannot be parsed
#define EMV_ERR_INITAPP_GPO_NO82            0x0226  //GPO 解析77模板时缺少82必要数据。 GPO is missing 82 necessary data when parsing 77 templates
#define EMV_ERR_INITAPP_GPO_NO94            0x0227  //GPO 解析77模板时缺少84必要数据。 GPO is missing 84 necessary data when parsing 77 templates
#define EMV_ERR_INITAPP_GETOP			    0x0228  //应用初始化时GPO命令返回不为9000，不为6985。 GPO command returns not 9000, not 6985 during application initialization 
#define EMV_ERR_INITAPP_PACKPDOL		    0x0229  //应用初始化时GPO中PDOL打包时出错。 Error in PDOL packaging in GPO during application initialization
#define EMV_ERR_INITAPP_SELACCOUNT			0x022a	//账户选择出错。Account selection error
#define EMV_ERR_INITAPP_6985				0x022b  //ICC返回6985 。ICC returns 6985

/**< qpboc应用初始化*/
#define	QPBOC_ERR_INITAPP_ERR	            0x0251  //QPBOC应用初始化失败 
#define QPBOC_ERR_INITAPP_PACKPDOL	        0x0252  //QPboc中打包DOL数据出错 
#define QPBOC_ERR_INITAPP_PDOLNO9F66	    0x0253  //QPBOC中Dol数据没有9F66 
#define QPBOC_ERR_INITAPP_GETGPO            0x0254  //获取GPO数据失败 
#define QPBOC_ERR_INITAPP_CHECK_GPO         0x0255  //检查GPO数据失败 
#define QPBOC_ERR_INITAPP_GPO6984		    0x0256  //QPboc的GPO返回6984，交易中止 
#define QPBOC_ERR_INITAPP_GPOMISSING82	    0x0257  //QPBOC的GPO中没有82
#define QPBOC_ERR_INITAPP_GETGPO_74         0x0258  //QPBOC的GPO中77模板中74解析出错 
#define QPBOC_ERR_INITAPP_GPO6985		    0x0259  //QPboc的GPO返回6985，交易中止 
#define QPBOC_ERR_INITAPP_GPO6986		    0x025a  //QPboc的GPO返回6986，交易中止 
#define QPBOC_ERR_INITAPP_GPONOLEN		    0x025b  //QPboc的GPO不响应
#define QPBOC_ERR_TURN_PBOC                 0x025c  //QPBOC 中如果GPO不存在9F26，且终支持PBOC，则转PBOC 

/**************************************************************************/
/**<读应用数据错误*/
#define EMV_ERR_READAPP					    0x0311  //读应用数据错误。 Read application data error

#define EMV_ERR_READAPP_CDOL1				0x0321  //检查应用数据，CDOL1 缺失。  Check application data, CDOL1 is missing
#define EMV_ERR_READAPP_CDOL2				0x0322  //检查应用数据，CDOL2 缺失。  Check application data, CDOL2 is missing
#define EMV_ERR_READAPP_EXPIREDATE		    0x0323  //检查应用数据，应用失效日期缺失或错误。 Check application data for missing or incorrect application expiration dates     
#define EMV_ERR_READAPP_APPEFFECTDATE	    0x0324  //检查应用数据，应用生效日期缺失或错误。 Check application data, missing or incorrect application effective date

#define EMV_ERR_READAPP_START				0x0331  //读取应用数据，由于AFL的起始位为0出错（IC卡）。 Error reading application data because the start bit of AFL is 0 (IC card)
#define EMV_ERR_READAPP_PARAM			    0x0332  //读取应用数据，由于AFL的起始位大于结束位出错（IC卡）。 Reading application data, because the start bit of AFL is larger than the end bit (IC card)

#define EMV_ERR_READAPP_ICCOP_READ		    0x0341  //RR（Read Record）时出错（返回不为9000）。 Error while reading record
#define EMV_ERR_READAPP_SFI				    0x0342  //RR 命令返回 只有70模板时，SFI才会小于等于10。 When the read data ,the SFI will be less than or equal to 10 only when the template is 70.
#define EMV_ERR_READAPP_PAN				    0x0343  //RR 数据检查，获取IC卡中卡号出错 Data check。 error in obtaining card number in IC card  

#define EMV_ERR_READAPP_TERM_ON_NEXT_APDU   0x0351  //RR Terminate on Next RA

#define	EMV_ERR_EC_NO9F74				    0x0361  //指示EC，但EC发卡行代码不存在  
#define EMV_ERR_EC_BLACKLIST			    0x0362  //应用数据检查时，EC在黑名单中  
#define EMV_ERR_EC_lEN9F74                  0x0363  //应用数据检查时，9F74的长度不为6 
#define EMV_ERR_EC_NO9F79                   0x0364  //电子现金中，缺少9F79余额 
#define EMV_ERR_EC_NO9F6D					0x0365  //电子现金中，缺少9F6D电子现金重置阈值

/**< 在应用初始化后读取交易日志 */
#define PBOC_ERR_READLOG_NO_BF0C            0x0371  // PBOC读取交易日志或者圈存日志，没有BF0C，无交易日志，交易中止  
#define PBOC_ERR_READLOG_NO_9F4D            0x0372  // PBOC读取交易日志，没有9F4D，无交易日志，交易中止   
#define PBOC_ERR_READLOG_9F4D_SFI           0x0373  // PBOC读取交易日志,读取9F4D的SFI范围不在11—30之间，交易中止
#define PBOC_ERR_READLOG_9F4F_FORMAT        0x0374  // PBOC读取交易日志,get 9F4F格式出错，交易格式错
#define PBOC_ERR_READLOG_NO_DF4D            0x0375  // PBOC读取圈存日志，没有9F4D，无交易日志，交易中止
#define PBOC_ERR_READLOG_DF4D_SFI           0x0376  // PBOC读取圈存日志,读取9F4D的SFI范围不在11—30之间，交易中止
#define PBOC_ERR_READLOG_DF4F_FORMAT        0x0377  // PBOC读取圈存日志,get 9F4F格式出错，交易格式错


/**************************************************************************/
/**<脱机认证错误*/
#define EMV_ERR_OFFAUTH					    0x0411  //脱机认证失败。 Offline authentication failed
/**<SDA  */
#define EMV_ERR_OFFAUTH_SDA_FAIL            0x0421 //SDA失败。  SDA failed
#define EMV_ERR_OFFAUTH_SM_SDA_FAIL         0x0422 // SM SDA 失败。   SM SDA failed
/**<DDA  */
#define EMV_ERR_OFFAUTH_DDA_FAIL		    0x0431 // DDA失败。 DDA failed
#define EMV_ERR_OFFAUTH_SM_DDA_FAIL         0x0432 // SM DDA 失败。 SM DDA failed
/*< CDA*/
#define EMV_ERR_OFFAUTH_CDA_PREFORM_FAIL    0x0441 //CDA的预处理失败。 CDA preprocessing failed
#define EMV_ERR_OFFAUTH_SM_CDA_PREFORM_FAIL 0x0442 // SM CDA的预处理失败。 SM CDA preprocessing failed

#define EMV_ERR_OFFAUTH_CAPK				0x0451 //获取CA公钥失败。Failed to obtain the CA public key.
#define EMV_ERR_OFFAUTH_ISPK				0x0452 //恢复发卡行公钥失败。Failed to recover the issuer's public key.
#define EMV_ERR_OFFAUTH_ICPK				0x0453 //恢复IC卡公钥失败。Failed to recover the IC card public key.
#define EMV_ERR_OFFAUTH_ISPK_CHECK			0x0454 //恢复并验证动态签名数据。Recover and verify dynamic signature data.
#define EMV_ERR_OFFAUTH_SDATA				0x0455 //恢复并验证静态认证数据失败。Failed to recover and verify static authentication data.

#define EMV_ERR_OFFAUTH_NO_AID_INDEX		0x0461  //脱机认证中恢复CAPK时卡片中没有AID或者CAPK 索引。There is no AID or CAPK index in the card when restoring CAPK in offline authentication.

#define EMV_ERR_OFFAUTH_GETINFO_FAIL		0x0462  //获取发卡行中心信息失败。Failed to get card issuer center information.
#define EMV_ERR_OFFAUTH_RECOVE_ISPK			0x0463  //恢复发卡行公钥失败。Failed to recover the issuer's public key.  
#define EMV_ERR_OFFAUTH_CHECK				0x0464  //检查恢复数据中的各项不正确。Check that the items in the recovered data are incorrect.
#define EMV_ERR_OFFLINE_CONNECTPK			0x0465  //将公钥以一定格式链接出错。Error linking public key in a certain format.
#define EMV_ERR_OFFAUTH_SIGNDYNAPPDT		0x0466  //内部认证返回数据77，无签名的动态应用数据。 The internal authentication returns data tag77, unsigned dynamic application data
#define EMV_ERR_OFFAUTH_SDA_DATA93          0x0467  //恢复并验证静态认证数据时缺少93。 Tag93 is missing when restoring and verifying static authentication data.
#define EMV_ERR_OFFAUTH_DDA_INTERAUTH		0x0468  //内部认证命令返回失败。 The internal authentication command failed.

#define EMV_ERR_OFFAUTH_DDA_INTERAUTH_FORMAT		0x0471 //内部认证返回数据模板格式不对。 The format of the internal authentication return data template is incorrect
#define EMV_ERR_OFFAUTH_DDA_INTERAUTH_ANALY			0x0472 //内部认证返回数据不能解析出TLV格式。 The internal authentication return data cannot be parsed in TLV format.
#define EMV_ERR_OFFAUTH_DDA_INTERAUTH_DATA80_LEN	0x0473 //内部认证返回数据80模板数据长度为0。 Internal authentication return data tag80 template data length is 0
#define EMV_ERR_OFFAUTH_DDOL_MIS					0x0474 //终端和卡片同时缺少DDOL。Both the terminal and the card are missing DDOL.
#define EMV_ERR_OFFAUTH_IC_DDOL9F37					0x0475 //卡片DDOL缺少9F37。Card DDOL is missing 9F37. 

#define QPBOC_ERR_FDDA_DDOL_MIS9F37         0x0481 //FDDA时准备DDOL的时候缺少9F37 
#define QPBOC_ERR_FDDA_DDOL_MIS9F02         0x0482 //FDDA时准备DDOL的时候缺少9F02 
#define QPBOC_ERR_FDDA_DDOL_MIS5F2A         0x0483 //FDDA时准备DDOL的时候缺少5F2A(交易货币代码) 
#define QPBOC_ERR_FDDA_DDOL_MIS9F69         0x0484 //FDDA时准备DDOL的时候缺少9F69(卡片认证相关数据) 
/**<fDDA  */
#define QPBOC_ERR_OFFAUTH_DDA_FAIL		    0x0485 // FDDA失败。 DDA failed
#define QPBOC_ERR_OFFAUTH_SM_DDA_FAIL       0x0486 // SM FDDA 失败。 SM DDA failed

#define EMV_ERR_GAC_CDA						0x0491  // cda失败。cda failed. 
#define EMV_ERR_GAC_CDA_ICPK                0x0492  // CDA 恢复IC卡公钥失败。Failed to recover IC card public key when CDA
#define EMV_ERR_GAC_CDA_ICPK_LEN            0x0493  // CDA时IC卡公钥长度不正确。IC card public key length is incorrect when CDA 
#define EMV_ERR_GAC_CDA_CERT                0x0494  // CDA证书格式检查失败。 Certificate format check failed when CDA 
#define EMV_ERR_GAC_SIGAPPDATA				0x0495  // 9F4B动态签名数据获取失败。Failed to obtain dynamic signature data

#define EMV_ERR_EC_NOBINDLOAD               0x04a1	// 电子现金非指定账户在脱机认证后返回 
#define EMV_ERR_ONLY_EC_NOBINDLOAD          0x04a2	// 纯电子现金非指定账户在脱机认证后返回 

/***********************************************************************/
/**<持卡人验证错误*/
#define EMV_ERR_CHVERIFY					0x0611  //持卡人验证错误。  Cardholder verification error.

#define EMV_ERR_CHVERIFY_CVMFOMAT		    0x0621  //CVM列表长度错误，交易中止。 CVM list length error

/***********************************************************************/
/**<行为分析错误*/
#define EMV_ERR_ACT_ANALY_TAA			    0x0811  //行为分析中，交易中止。During the ACT ANALY, the transaction was aborted.	 

#define EMV_ERR_ACT_ANALY_GAC               0x0821  //GAC 命令返回不为9000。GAC command returns not 9000
#define EMV_ERR_ACT_GAC_DATA                0x0822  //GAC 解析数据格式不正确。GAC parsing data is malformed
#define EMV_ERR_TAA_CID		                0x0823  //解析GAC数据CID等级高于终端请求（请求AAC或ARQC但返回TC,交易终止 请求AAC但卡片返回ARQC或TC,交易终止 请求AAC但卡片返回ARQC或TC,交易终止）。Parsing GAC data CID level is higher than terminal request
#define EMV_ERR_TAA_NOCID		            0x0824  //GAC返回数据中没有CID，交易中止。No CID in the returned data when GAC 
#define EMV_ERR_TAA_NOATC		            0x0825  //GAC返回数据中没有ATC，交易中止。No ATC in return data when GAC 
#define EMV_ERR_PARASE_NO_91                0x0826  //解析发卡行自定义数据时没有91。No tag91 when parsing custom data of issuer 
#define EMV_ERR_PARASE_91_LEN               0x0827  //发卡行自定义数据91 的长度不正确。tag91 is not the correct length

#define EMV_ERR_GAC_ERR_AC					0x0831	//密文数据获取失败。The ciphertext data acquisition failed.

#define EMV_ERR_GAC_CID_AAR					0x0841	//CID造成的AAR中止。AAR suspension due to CID


/***********************************************************************/
/**< 完成处理*/
#define EMV_ERR_COMPLETE					0x0911 //完成处理失败。Failed to complete processing 

#define EMV_ERR_COMPLETE_ADVICE				0x0921 //终端请求联机，且强制通知，但联机失败，交易中止。Terminal requested to connect and forced notification, but failed to connect
#define EMV_ERR_COMPLETE_GAC				0x0922 //第二次GAC返回不为9000。The second GAC return is not 9000    
#define EMV_ERR_COMPLETE_EC_NO_SCRIPT       0x0923 //电子现金圈存，查询的案例联机后没有脚本下发，交易中止。 
#define EMV_ERR_COMPLETE_CID_INTERRUPT      0x0924 //卡片密文返回交易中止，交易中止。 CID returned transaction aborted
#define EMV_ERR_COMPLETE_PARASE_GAC			0x0925 //GAC解析失败。GAC parsing failed 


/***********************************************************************/
/**<其他*/
#define EMV_ERR_INITHASH	                   0x0a11 //哈希列表未能初始化。Hash list failed to initialize  
/**<CAPK错误*/
#define EMV_ERR_CAPK	                       0x0a21 //CAPK出错。CAPK error
#define EMV_ERR_CAPK_NOFOUND		           0x0a22 //CAPK没有找到。CAPK not found 
#define EMV_ERR_CAPK_VERIFY		               0x0a23 //CAPK验证出错。CAPK verification error 
#define EMV_ERR_CAPK_EXPIRE		               0x0a24 //CAPK失效。CAPK is invalid
#define EMV_ERR_CAPK_RECOVER		           0x0a25 //CAPK在回收公钥中

/**<AID错误*/
#define EMV_ERR_AID		                       0x0a31 //AID出错。AID error
#define EMV_ERR_AID_GETLIST		               0x0a32 //读取AID文件，AID为空。Read AID file, AID is empty
#define EMV_ERR_AID_SPARAERR		           0x0a33 //获取AID时AID参数出错。AID parameter error while getting AID
#define EMV_ERR_AID_GPARAERR		           0x0a34 //增加AID时AID参数出错。AID parameter error when adding AID
#define EMV_ERR_AID_MAXNUM		               0x0a35 //AID超出最大数。AID exceeds the maximum number

/**<ICS错误*/
#define EMV_ERR_ICS		                       0x0a41 //ICS出错。ICS error
#define EMV_ERR_ICS_READ			           0x0a42 //ICS读取出错，交易中止。ICS read error

/**<IC卡操作错误*/
#define ERR_SWITCH_INTERFACE		           0x0a51  //转界面。Go to other interface
#define EMV_ERR_ICCOP_L1_ERR				   0x0a52  //APDU未收到返回。APDU not returned
#define EMV_ERR_ICCOP_POWERUP		           0x0a53  //IC卡上电出错。IC card power on error
#define EMV_ERR_ICCOP_POWERDOWN	               0x0a54  //IC卡下电出错。IC card power off error

/**< 其他显示类错误*/
#define EMV_ERR_PAN_QUIT                       0x0a61	// 提示PAN确认时，用户选择取消。When prompted for PAN confirmation, the user chooses to cancel   
#define EMV_ERR_AMT_QUIT                       0x0a62	// 提示输入交易金额时，用户选择取消。 When prompted to enter the transaction amount, the user chooses to cancel  

#define PAYPASS_ERR_CCC_CHECK				   0x0a71	// PAYPASS CCC 解析错误。PAYPASS CCC parsing error
#define PAYPASS_ERR_RRP_CHECK				   0x0a72	// PAYPASS RRP 解析错误。PAYPASS RRP parsing error




/***********************************************************************/


#endif
