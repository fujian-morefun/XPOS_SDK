#ifndef _DEF_HEAD_H_
#define _DEF_HEAD_H_




#ifdef HX_APP_VARIABLES
    #define EXTERN 
#else
    #define EXTERN extern 
#endif

//#include "struct.h"
//#include "coredef.h"
//#include "poslib.h" 

typedef unsigned char	uchar;
typedef unsigned char	byte;
typedef const char		cchar;
typedef unsigned int	uint;
typedef const int		cint;
typedef unsigned short	ushort;
typedef unsigned long	ulong;


#ifdef WIN32
#define __FUNCTION__	""
#endif

//#define Icc_Close Icc_Release

/**<Button definition*/
typedef enum                    /**<The key value is defined according to different manufacturers'tools*/
{
    UKEY_1 = 0x01,              /**<number key 1*/
    UKEY_2 = 0x02,              /**<number key 2*/
    UKEY_3 = 0x03,              /**<number key 3*/
    UKEY_4 = 0x04,              /**<number key 4*/
    UKEY_5 = 0x05,              /**<number key 5*/
    UKEY_6 = 0x06,              /**<number key 6*/
    UKEY_7 = 0x07,              /**<number key 7*/
    UKEY_8 = 0x08,              /**<number key 8*/
    UKEY_9 = 0x09,              /**<number key 9*/
    UKEY_0 = 0x0a,              /**<number key 0*/
    UKEY_ENTER   = 0x10,        /**<Enter button*/
    UKEY_CANCEL  = 0x11,        /**<Cancel button*/
    UKEY_UP      = 0x12,        /**<Page up button*/
    UKEY_DOWN    = 0x13,        /**<Page down button*/
    UKEY_FUN     = 0x14,        /**<Function key*/
    UKEY_BACK    = 0x15,        /**<Backspace key*/
    UKEY_POINT   = 0x16,        /**<Point button*/
    UKEY_LETTER  = 0x17,        /**<Letter key*/
    UKEY_MENU    = 0x18,        /**<Menu key*/
    UKEY_F1  = 0x19,            /**<F1 key*/
    UKEY_F2  = 0x1A,            /**<F2 key*/
    UKEY_F3  = 0x1B,            /**<F3 key*/
    UKEY_F4  = 0x1C             /**<F4 key*/
} KEY_VALUE;


//2.2.2	System class API

//Terminal information structure
typedef struct
{
	byte	Terminal[20];	//Terminal model,Align left(Vendor+model,PAX¡¢XGD¡¢LND¡¢NLD¡¢VFI¡¢HZR¡¢SYD)
	byte	SN[40];			//Terminal hardware serial number
	int		Disp_X;			//Horizontal maximum pixel
	int		Disp_Y;			//Vertical maximum pixel
	int		Disp_Line1;		//Large font screen shows the number of lines
	int		Disp_Line2;		//Small font screen shows the number of lines
	int		Disp_Chinese;	//One line shows the maximum number of Chinese characters
	int		Disp_Character;	//One line shows the maximum number of English and numeric characters (small font)
}TERMINALINFO;

//Master service function type definition
typedef int (*ServerFunc)(const char *pszAppName, void *pvInData, int iInLen, void *pvOutData, int *piOutLen);

//Master service attribute structure
typedef struct _ServerAttr
{
    char szServerName[32];    //Service function name
    ServerFunc pServerFunc;   //Service function pointer
    int iVerSion;             //Service function version
} ServerAttr;

//Language type enumeration
typedef enum
{
ULANGUAGE_CHINESE =  0,   //Chinese
ULANGUAGE_ENGLISH,        //English
ULANGUAGE_JAPANSES        //Japanese
}ULanguage;

//System class API returns an enumeration
typedef enum
{
	USYS_PARAERROR = -2,  //Parameter error
	USYS_FAIL      = -1,  //Failure
	USYS_SUCCESS    = 0,  //Success
	USYS_FIRST     = 1,   //First run after the program is updated
	USYS_NOFIRST   = 2    //The program is not running for the first time
}USysStatus;

//2.2.3	Display class API

//Display class API return code definition
typedef enum
{ 
	SCREEN_MAIN,     //Main screen
	SCREEN_GUEST	 //Guest display
} DispStatus;

typedef enum
{
	UDISP_DEV_FAIL  =-3,		//Device reason failed
	UDISP_FILE_FAIL =-2,		//File reason failed
	UDISP_FAIL     	=-1,		//Unknown reason failed
	UDISP_SUCCESS  	=0			//Success
} ScreenType;

//2.2.5	Tools API

#define UMAX_RSA_MODULUS_LEN   512   //RSA Maximum mode length
#define UMAX_RSA_PRIME_LEN     256   //RSA Maximum modulus prime length
//Tool class API return code definition
typedef enum
{
	UUTIL_TIMEOUT        = -3,    //Input timeout
	UUTIL_CANCEL         = -2,    //Enter cancel
	UUTIL_FAIL           = -1,    //Failure
	UUTIL_SUCCESS        =  0	  //Success
} UtilStatus;

//Barcode QR code format definition
typedef enum
{
	UCODE_QRCODE,
	UCODE_PDF417,
	UCODE_GMCODE,
	UCODE_CODE128,
	UCODE_CODE39,     
	UCODE_EAN13,     
	UCODE_EAN128
} BarCode;

//RSA Public key structure definition
typedef struct 
{
	uint   uiBits;   //Modulus (bit)
	byte   ucModulus[UMAX_RSA_MODULUS_LEN];   //mold
	byte   ucExponent[UMAX_RSA_MODULUS_LEN];  //index
}URSAPUBLICKEY;

//RSA Private key structure definition
typedef struct 
{
	uint   uiBits;    //Modulus (bit)
	byte   ucModulus[UMAX_RSA_MODULUS_LEN];   //mold
	byte   ucPublicExponent [UMAX_RSA_MODULUS_LEN];  //Public key index
	byte  ucExponent[UMAX_RSA_MODULUS_LEN];   //Private key index
	byte   ucPrime[2][UMAX_RSA_PRIME_LEN];     //pq Prime number,Prime factor
	byte   ucPrimeExponent[2][UMAX_RSA_PRIME_LEN]; //CRT index, prime and exponential division
	byte   ucCoefficient[UMAX_RSA_PRIME_LEN];  //CRT coefficient, prime and prime division value
}URSAPRIVATEKEY;

//RSA Algorithm key length enumeration
typedef enum 
{
	URSA_KEY_LEN_512,
	URSA_KEY_LEN_1024,
	URSA_KEY_LEN_2048
}URSAKeyLen;

//RSA Algorithm index enumeration
typedef enum 
{
	URSA_EXP_3,       //0x03
	URSA_EXP_10001    //0x10001
}URSAEXP;

//Signature version type enumeration
typedef enum
{
	USIGNATURE_INT,         //Built-in signature version
	USIGNATURE_EXT_COM1,    //External PinPad port, PIN pad signature version, corresponding to UPORT_COM1
	USIGNATURE_EXT_COM2,    //Separate external COM port signature version, corresponding to UPORT_COM2
	USIGNATURE_EXT_COM3,    //Separate external COM port signature version, corresponding to UPORT_COM3
	USIGNATURE_EXT_COM4,    //Separate external COM port signature version, corresponding to UPORT_COM4
	USIGNATURE_EXT_COM5,    //Separate external COM port signature version, corresponding to UPORT_COM5
	USIGNATURE_EXT_USB1,    //External PinPad port, PIN pad signature version, corresponding to UPORT_USB1
	USIGNATURE_EXT_USB2,    //Separate external USB port signature version, corresponding to UPORT_USB2
	USIGNATURE_EXT_USB3,    //Separate external USB port signature version, corresponding to UPORT_USB3
}USignaturePad;

//2.2.6	Communication class API

//SSL Handle definition
typedef int USSL_HANDLE;

//Communication method enumeration
typedef enum
{
	UCOMM_GPRS,				//GPRS Communication
	UCOMM_RS232,			//RS232 Communication
	UCOMM_WIFI,				//WIFI Communication

	UCOMM_CDMA,				//CDMA Communication
	UCOMM_IP,				//Ethernet IP Communication
	UCOMM_MODEM,			//MODEM Communication
} CommMode;

//Communication class return value enumeration
typedef enum
{ 
	UCOMM_SSL_RESOURCE             = -17,  //Exceeded the maximum SSL limit
	UCOMM_SSL_NONSUPPORT           = -16,  //Unsupported file format, protocol version, cipher suite
	UCOMM_SSL_CERT_NOT_YET_VALID   = -15,  //The other party's certificate is not yet valid
	UCOMM_SSL_CERT_HAS_EXPIRED     = -14,  //The other party's certificate has expired
	UCOMM_SSL_NOCONNECT            = -13,  //SSL Not connected yet
	UCOMM_SSL_SET_CIPHER_FAIL      = -12,  //Setting algorithm suite failed
	UCOMM_SSL_LOAD_KEY_FAIL        = -11,  //Failed to load private key
	UCOMM_SSL_LOAD_CERT_FAIL       = -10,  //Failed to load certificate
	UCOMM_SSL_LOAD_CA_FAIL         = -9,   //Failed to load CA
	UCOMM_DEVICE_UNAVAILABLE       = -8,   //Not available
	UCOMM_PARA_ERR                 = -7,   //Parameter error
	UCOMM_CONNECT_ERR              = -6,   //unable to connect
	UCOMM_CONNECTING               = -5,   //In the communication connection, PPP dialing
	UCOMM_LOGOFF                   = -4,   //Communication link disconnected
	UCOMM_CANCEL                   = -3,   //Button cancellation
	UCOMM_TIMEOUT                  = -2,   //Time out
	UCOMM_FAIL                     = -1,   //Failure
	UCOMM_SUCCESS                  =  0,   //Success
	UCOMM_LINK_OK                  =  1    //Communication link OK
} CommStatus;

//Hang up mode enumeration
typedef enum 	/*Hang up mode*/
{
	UHANGUP_FAST,		/*Hang up quickly, if it is for wireless, just hang up SOCKET and don't do it tcpwait*/
//	UHANGUP_DELAY,		/*Slowly hang up, if it is for wireless, just hang up SOCKET and do tcpwait*/
	UHANGUP_FAST_PPP,	/*Just hang up PPP and SOCKET for wireless and don't do it tcpwait*/
//	UHANGUP_DEALY_PPP,  /*Just hang up PPP and SOCKET for wireless and do it tcpwait*/
//  UHANGUP_EXIT
}HangUpMode;

//Wireless network registration parameter structure(GPRS¡¢CDMA)
typedef struct
{
	char  NetUsername[41] ; /* User name to be used when the wireless modem establishes a PPP link */
	char  NetPassword[21] ; /* The password to be used when the wireless modem establishes a PPP link. */
	char  ModemDialNo[21] ; /*The access number used by the wireless modem to establish a PPP link is in the form of an ATD+ number, such as the form of "ATD*99***1# code.*/
	char  GprsApn[41] ;		/*Mobile APN name*/
	char  SimPin[11] ;		/*SIM Card pin*/
	char  WorkMode ;		/*0x01:Long chain; 0x02:Short chain*/
	char  DtrFlag;			/*Is there flow control?0x00:Flow control,0x01:No flow control*/
    char  PppType;			/*Agreement type*/
}PPPLOGINCONFIG;

//Ethernet communication parameter structure
typedef struct
{
	byte DHCP;			/*Whether to open DHCP,0-NO,1-YES*/
	char  IP[16] ;		/*Local IP address*/
	char Gateway[16] ;	/*Local gateway*/
	char  Mask[16] ;	/*Local subnet mask*/
    char  Dns1[16];		/*DNS*/
    char  Dns2[16];		/*DNS*/
}IPCONFIG;

#if 0
//WIFI Password format
typedef enum
{ 
	WLN_KEY_TYPE_NOKEY,  /*Do not use a password*/
	WLN_KEY_TYPE_HEX,    /*Use hexadecimal password format*/
	WLN_KEY_TYPE_ASCII   /*Use ASCII password format*/
}UWLNKEYTYPE;

//WIFI Secure encryption mode
typedef enum
{ 
	WLN_NET_SEC_NONE,       /*Do not use secure encryption mode*/
	WLN_NET_SEC_WEP_OPEN,   /*WEP mode using open key*/
	WLN_NET_SEC_WEP_SHARED, /*WEP mode using shared key*/
	WLN_NET_SEC_WPA,        /*Use WPA mode*/
	WLN_NET_SEC_WPA2,       /*Use WPA2 mode*/
	WLN_NET_SEC_WPA_PSK,    /*Use WPA-PSK mode*/
	WLN_NET_SEC_WPA2_PSK    /*Use WPA2-PSK mode*/
}UWLNNETSEC;
#endif

/*WIFI Security Encryption Mode Accessory Attribute*/
typedef enum
{
    WLN_NET_WSEC_OFF,
    WLN_NET_WSEC_WEP,
    WLN_NET_WSEC_TKIP,
    WLN_NET_WSEC_WEP128,
    WLN_NET_WSEC_AES,
} UWLNNETWSEC;

/*WIFI Secure encryption authentication method*/
typedef enum
{
    WLN_NET_AUTH_OPEN,
    WLN_NET_AUTH_WEP,
    WLN_NET_AUTH_Shared,
    WLN_NET_AUTH_IEEE8021X,
    WLN_NET_AUTH_WPA_PSK,
    WLN_NET_AUTH_WPA_EAP,
    WLN_NET_AUTH_WPA2_PSK,
    WLN_NET_AUTH_WPA2_EAP,
    WLN_NET_AUTH_WPA_CCKM,
    WLN_NET_AUTH_WPA2_CCKM,
    WLN_NET_AUTH_NONE,
} UWLNNETWAUTHTYPE;

/**<WIFI Communication parameter structure:*/
typedef struct
{
    byte DHCP;           /**<Whether to open DHCP£¬0x00-No£¬0x01-yes*/
    int  Wsec;			 /*Contains the numeric value for network security type.See enum UWLNNETWSEC*/
    int  WAuthType;		 /*Contains the numeric value for the network authentication type.See UWLNNETWAUTHTYPE*/
    byte SSID[100];      /**<WIFI user*/
    byte Pwd[100];       /**<WIFI password*/
    char IP[16];         /**<Local IP address*/
    char Gateway[16];    /**<Local gateway*/
    char Mask[16];       /**<Local subnet mask*/
    char Dns1[16];       /**<DNS*/
    char Dns2[16];       /**<DNS*/
} WIFICONFIG;

/**<WIFI Hotspot information structure:*/
typedef struct
{
    byte SSID[100];		/*WIFI Hotspot name*/
    int  Wsec;			/*Contains the numeric value for network security type.See enum UWLNNETWSEC*/
    int  WAuthType;		/*Contains the numeric value for the network authentication type.See UWLNNETWAUTHTYPE*/
} WIFIINFO;

//IP¡¢WIFI Communication local IP information
typedef struct
{
	char  IP[16];         /*Local IP address*/
	char  Gateway[16];	  /*Local gateway*/
	char  Mask[16];       /*Local subnet mask*/
    char  Dns1[16];       /*DNS*/
	char  Dns2[16];       /*DNS*/
	char  MAC[18];        /*MAC address,Format such as 00-23-5A-15-99-42*/
}TERMINALIPINFO;

//MODEM Communication parameter structure
typedef struct
{
	int     DialMode;        /*Dial mode£º0 Synchronize,1 Asynchronous*/
	char	PredialNo[10];   /*Outside line number*/
	char	TelNo[3][21];	 /*Telephone number*/
	int		IsCheckDialTone; /*Whether to detect dial tone	 0 default detection, 1 does not detect */
}MODEMCONFIG;

//Peripheral extension interface enumeration
typedef enum
{
	UPORT_COM1,    //COM port 1, do the default PinPad port
	UPORT_COM2,    //COM port 2, do the default RS232 port 1
	UPORT_COM3,    //COM port 3, do the default RS232 port 2
	UPORT_COM4,    //COM port 4
	UPORT_COM5,    //COM port 5
	UPORT_USB1,    //USB port 1,Can be used as a USB PinPad port
	UPORT_USB2,    //USB port 2
	UPORT_USB3,    //USB port 3
	UPORT_LAN      //Ethernet TCP/IP port
}ExtPort;

//Serial communication baud rate enumeration
typedef enum
{
	UBPS9600,
	UBPS115200
}BaudRate;//According to the actual support situation

//Serial communication data bit, stop bit, check digit parameter enumeration
typedef enum
{
	UDB8		= 0xc0,		//8-bit data bit selection
	UDB7		= 0x40,		//7-bit data bit selection
	UDB6		= 0x80,		//6-bit data bit selection
	UDB5		= 0x00,		//5-bit data bit selection
	USTOP2		= 0x20,		//2 stop bits
	USTOP15		= 0x10,		//1.5 stop position
	USTOP1		= 0x08,		//1 stop position
	UNP			= 0x04,		//No parity
	UEP			= 0x02,		//Even parity
	UOP			= 0x01		//Odd parity
}AuxFlag;

//Serial communication parameter structure
typedef struct
{
	int Aux;		/*Serial port number, see enum ExtPort */	
	int iBaudRate;  /*Serial port baud rate, see enum BaudRate*/
	int iAuxFlag;   /*Serial port characteristics such as data bits, stop bits, check bits, etc.*/
}RS232CONFIG;

//Establish host connection communication parameter structure (Ethernet, WIFI, GPRS, CDMA)
typedef struct
{
	char	HostIp[2][16]; /*Server IP address*/
	int		HostPort[2];   /*Service port number*/
	char	HostDns[50];   /*Server domain name*/
}HOSTCONFIG;

//Communication parameters initialize the joint structure (Ethernet, WIFI, GPRS, CDMA, MODEM)
typedef struct
{
int iCommMode;		/*Communication method, read the communication method in the machine parameters, see enum CommMode */
	union
	{
		PPPLOGINCONFIG	st_ppploginconfig ;	/*GPRS¡¢CDMA parameter,see PPPLOGINCONFIG */
		IPCONFIG		st_ipconfig;		/*Ethernet parameter,see IPCONFIG */
		WIFICONFIG      st_wificonfig;		/*WIFI parameter,see WIFICONFIG */
		MODEMCONFIG     st_modemconfig;		/*MODEM Communication parameters,see MODEMCONFIG */
	} INITCONFIG;
	void ( *ShowFunc )( void ) ;			/*Interface information displayed when blocked*/
	int   CycCount;							/*Cycles*/
}COMMCONFIG;

//Establish a host connection communication parameter joint structure (Ethernet, WIFI, GPRS, CDMA, MODEM)
typedef struct
{
	int iCommMode;	/*Communication method, read the communication method in the machine parameters, see enum CommMode */ 
	
	HOSTCONFIG     st_hostconfig;			//See HOSTCONFIG
	
	void ( *ShowFunc )( void ) ;			/*Interface information displayed when blocked*/
}COMMHOSTCONFIG;

//SSL Protocol enumeration
typedef enum
{
	UPROTOCOL_TLSv1_2    //TLS version 1.2
}UProtocolType;

//Enumeration of SSL certificate file format
typedef enum
{
	USSL_FILE_DER,  //DER (ASN1) file format 
	USSL_FILE_PEM   //PEM (BASE64) file format
}USSLFileFormat;

//SSL cipher suite enumeration
typedef enum
{
	CIPHER_RSA_NULL_MD5,			/*cipher suite-RSA_NULL_MD5*/
	CIPHER_RSA_NULL_SHA,			/*cipher suite-RSA_NULL_SHA*/
	CIPHER_RSA_RC4_40_MD5,			/*cipher suite-RSA_RC4_40_MD5*/
	CIPHER_RSA_RC4_128_MD5,			/*cipher suite-RSA_RC4_128_MD5*/
	CIPHER_RSA_RC4_128_SHA,			/*cipher suite-RSA_RC4_128_SHA*/
	CIPHER_RSA_RC2_40_MD5,			/*cipher suite-RSA_RC2_40_MD5*/
	CIPHER_RSA_IDEA_128_SHA,		/*cipher suite-IDEA_128_SHA*/
	CIPHER_RSA_DES_40_CBC_SHA,		/*cipher suite-DES_40_CBC_SHA*/
	CIPHER_RSA_DES_64_CBC_SHA,		/*cipher suite-DES_64_CBC_SHA*/
	CIPHER_RSA_DES_192_CBC3_SHA,    /*cipher suite-DES_192_CBC3_SHA*/
	CIPHER_DH_RSA_DES_192_CBC3_SHA, /*cipher suite-DH_DSS_DES_192_CBC3_SHA*/
	CIPHER_DH_DSS_DES_40_CBC_SHA,   /*cipher suite-DH_DSS_DES_40_CBC_SHA*/
	CIPHER_DH_DSS_DES_64_CBC_SHA,   /*cipher suite-DH_DSS_DES_64_CBC_SHA*/
	CIPHER_DH_DSS_DES_192_CBC3_SHA, /*cipher suite-DH_DSS_DES_192_CBC3_SHA*/
	CIPHER_DH_RSA_DES_40_CBC_SHA,   /*cipher suite-DH_RSA_DES_40_CBC_SHA*/
	CIPHER_DH_RSA_DES_64_CBC_SHA,   /*cipher suite-DH_RSA_DES_64_CBC_SHA*/
	CIPHER_EDH_DSS_DES_40_CBC_SHA,  /*cipher suite-EDH_DSS_DES_40_CBC_SHA*/
	CIPHER_EDH_DSS_DES_64_CBC_SHA,  /*cipher suite-EDH_DSS_DES_64_CBC_SHA*/
	CIPHER_EDH_DSS_DES_192_CBC3_SHA,/*cipher suite-EDH_DSS_DES_192_CBC3_SHA*/
	CIPHER_EDH_RSA_DES_40_CBC_SHA,  /*cipher suite-EDH_RSA_DES_40_CBC_SHA*/
	CIPHER_EDH_RSA_DES_64_CBC_SHA,  /*cipher suite-EDH_RSA_DES_64_CBC_SHA*/
	CIPHER_EDH_RSA_DES_192_CBC3_SHA,/*cipher suite-EDH_RSA_DES_192_CBC3_SHA*/
	CIPHER_ADH_RC4_40_MD5,			/*cipher suite-ADH_RC4_40_MD5*/
	CIPHER_ADH_RC4_128_MD5,			/*cipher suite-ADH_RC4_128_MD5*/
	CIPHER_ADH_DES_40_CBC_SHA,		/*cipher suite-ADH_DES_40_CBC_SHA*/
	CIPHER_FZA_DMS_NULL_SHA,		/*cipher suite-FZA_DMS_NULL_SHA*/
	CIPHER_CK_FZA_DMS_FZA_SHA,		/*cipher suite-CK_FZA_DMS_FZA_SHA*/
	CIPHER_CK_FZA_DMS_RC4_SHA,		/*cipher suite-CK_FZA_DMS_RC4_SHA*/
	CIPHER_CK_ADH_DES_64_CBC_SHA,   /*cipher suite-CK_ADH_DES_64_CBC_SHA*/
	CIPHER_CK_ADH_DES_192_CBC_SHA   /*cipher suite-CK_ADH_DES_192_CBC_SHA*/
}UCipherSuite;

//GSM base station information structure
typedef struct
{
	byte szMCC[5];     //Mobile country code, three digits, such as China 460
	byte szMNC[5];     //Mobile network number, such as mobile 00, Unicom 01
	byte szLAC[5];     //Area code
	byte szCID[5];     //Cell code
	int  nSIG;         //Signal strength, if it is positive, please add 110, negative value, add 220
	int  nTAG;         //Time advance, range 0-63
}BASESTATIONGSM;

//CDMA base station information structure
typedef struct
{
	byte szMCC[5];       //Mobile country code, three digits, such as China 460
	byte szSID[5];       //System identification code, each prefecture-level city has only one sid.
	byte szNID[5];       //The network identification code is managed by each local network, that is, it is allocated by the local branch office. Each prefecture-level city may have 1 to 3 nid.
	byte szBID[5];       //Indicates a certain cell in the network, which can be understood as a base station.
	int  nSIG;           //Signal strength, if it is positive, please add 110, negative value, add 220
	int  nTAG;           //Time advance, range,0-63
}BASESTATIONCDMA;

//2.2.7	IC card processing API

//IC card type enumeration
typedef enum
{
	//	UICC_SLE4442, //Reserved
	//	UICC_SLE4428, //Reserved
	//	UICC_SLE4436, //Reserved
	//	UICC_AT24C64, //Reserved
	UICC_CPUCARD,
	UICC_MIFARE,	  //Non-connected MIFARE card,Reserved
	//	UICC_RFCPU_1356,//Non-connected CPU¿¨13.56M
	//	UICC_RFCPU_24   //Non-connected CPU¿¨2.4G
} IccType;

//IC card slot enumeration
typedef enum
{
	USLOT_PSAM1,       //Contact PSAM card slot1
	USLOT_PSAM2,       //Contact PSAM card slot2
	USLOT_PSAM3,       //Contact PSAM card slot3
	USLOT_PSAM4,       //Contact PSAM card slot4
	USLOT_EXCARD,      //Contact user card slot
	USLOT_INRF,        //Built-in non-card slot
	USLOT_EXRF_COM1,   //External non-card slot COM1 port
	USLOT_EXRF_COM2,   //External non-card slot COM2 port
	USLOT_EXRF_COM3,   //External non-card slot COM3 port
	USLOT_EXRF_USB     //External non-card slot USB port
} SlotType;


//IC card instruction structure
typedef struct
{
	//	byte OperType;	/* See enum - OperationType */
	byte CLA;			/* Class byte of the command message*/
	byte INS;			/* Instrution*/
	byte P1;			/* Parameter1*/
	byte P2;			/* Parameter2*/
	byte Lc;			/* length of being sent data*/
	byte Le;			/* length of expected data,Actual return value*/
	byte SW1;			/* status word1*/
	byte SW2;			/* status word2*/
	byte C_Data[256];	/* command data*/
	byte R_Data[256];	/* response data*/
} ICCAPDU;

//IC card operation return code enumeration
typedef enum 	
{
	UICC_NORF            = -3,   // No card
//	UICC_EMPTY           = -3,   // Card slot without card
	UICC_COMMAND_FAIL    = -2,   // Communication error with card
	UICC_FAIL            = -1,   // operation failed
	UICC_OK              =  0    // Successful operation
}ICCStatus;

//2.2.9	File manipulation API

//File handle redefinition
typedef int FILE_HANDLE;
//File storage location enumeration
typedef enum			/*The file storage location, the private representation is stored in the current sub-application directory, only the current sub-application is accessible; the public representation is stored in a public location, and all sub-applications are accessible.*/
{
	FILE_PRIVATE,       //Private, this file is stored in the current sub-application directory, other sub-applications are inaccessible
	FILE_PUBLIC         //Publicly, this file is stored in a public location and accessible to all sub-applications
}FILELOCATION;

//File open mode definition
typedef  enum
{
	FILE_RDONLY = 0,	 //Read-only, there is no return error
		FILE_WRONLY,     //Write only, there is no return error
		FILE_RDWR,       //Read and write, there is no return error
		FILE_APPEND,     //Append, create if it does not exist, pointer to the end of the file when it exists
		FILE_CREAT,      //Create, delete rebuild when it already exists
}FileFlags;

//File pointer positioning
typedef  enum
{
	FILE_SEEK_SET = 0,   //To the file header
		FILE_SEEK_CUR,   //To the current location
		FILE_SEEK_END    //To the end of the file
}FileSeekFlags;

//File operation return value
typedef enum
{
	UFILE_NO_EXIST      = -12,             //The specified file does not exist
	UFILE_PARAERROR     = -11,             //Parameter error
	UFILE_NO_RECORD		= -10,             //Record not found
	UFILE_REMOVE_FAIL	= -9,              //Move file error
	UFILE_CLOSE_FAIL	= -8,              //Close file error
	UFILE_DELETE_FAIL	= -7,              //Delete file record error
	UFILE_SEEK_FAIL		= -6,              //Positioning file pointer error
	UFILE_READ_FAIL		= -5,              //Reading error
	UFILE_WRITE_FAIL	= -4,              //Write error
	UFILE_CREATE_FAIL 	= -3,              //File reconstruction error
	UFILE_OPEN_FAIL  	= -2,              //Open error
	UFILE_FAIL			= -1,              //File operation failed
	UFILE_SUCCESS       =  0               //File operation success
}FileRet;

//File operation search condition structure
typedef struct
{
	uint   StartOffset;  //Look up from the first few bytes of the structure, starting at 0
	uint   Length;       //Compare byte length
	byte*   SearchKey;   //Find keywords
}DBSEARCOND;

//2.2.10 Password keyboard API

//PinPad type enumeration
typedef enum
{
	UPP_INT		=0,      /* Built-in password keyboard */
	UPP_EXT_COM1,		 /* COM1 port external password keyboard */
	UPP_EXT_COM2,		 /* COM2 port external password keyboard */
	UPP_EXT_USB		     /* USB port external password keyboard */
}PinPadType;

//Encryption mode
typedef enum
{
	UDES_TYPE_SINGLE	=1,	/* Single DES */
	UDES_TYPE_TRIPLE,		/* 3DES */
	UDES_TYPE_SM4			/* National secret SM4 */
}DesType;

//Key type
typedef enum
{
	UKEY_TYPE_MST		=0,	/* Master key */
	UKEY_TYPE_PIN,			/* PIN Work key */
	UKEY_TYPE_MAC,			/* MAC Work key */
	UKEY_TYPE_TRACK,        /*TRACK Work key*/
	UKEY_TYPE_TEST          /*Test Work key*/
}KeyType;

//PINPAD password input interface return value
typedef enum
{
	UPIN_TIMEOUT    = -3,    // Password input timeout
	UPIN_ABORT		= -2,	 // Operator abandons input
	UPIN_ERROR		= -1,	 // Input error 
	UPIN_ESC		=  0,	 // User cancel input
	UPIN_SUCCESS	=  1,	 // Input success 
	UPIN_NONE		=  2	 // No password, equivalent to BYPASS
}PinInputStatus;

//Non-PIN input function return value definition
typedef enum
{
	UPP_ERROR_SM	= -10,				// National secret key/algorithm processing failed
	UPP_KEY_EXIST   = -9,               // Key group already exists
	UPP_DECLINED    = -8,               // Operation rejected
	UPP_ERROR		= -7,				// Error 
	UPP_FAILURE		= -6,				// System level failure 
	UPP_ESCAPE		= -5,				// Operation is exited 
	UPP_TIMEOUT		= -4,				// Timeout (external keyboard communication)
	UPP_MAC_ERROR	= -3,				// Calculated MAC error
	UPP_ERR_PAN		= -2,				// The primary account number is incorrect. 
	UPP_ABORT		= -1,				// User gives up 
	UPP_SUCCESS		= 0				    // success 
}PPStatus;

//2.2.11 EMV class API

#define  UMAX_TERMINAL_APPL    21        //The maximum number of applications supported by card terminals
#define  UMAX_EXCEPTION_BIN_COUNT	100  //Card BIN blacklist maximum number

//EMV parameter operation returns an enumeration
typedef enum
{ 
	UEMV_PRM_ERR  =-4,					//EMV Parameter error
	UEMV_PRM_NOT_FOUND=-3,				//EMV Parameter not found
	UEMV_PRM_CAPK_CHK_HASH_FAIL=-2,		//Public key HASH check error
	UEMV_PRM_FAIL=-1,					//EMV Parameter operation failed
	UEMV_PRM_OK=0             			//EMV Parameter operation success
} ParamStatus;

//EMV transaction status enumeration
typedef enum
{
	UEMV_QPBOC_DODGE          = -20,    /**<Flash card processing failed*/
	UEMV_EC_DECLINED          = -19,    //Electronic cash offline rejection
	UEMV_APP_NOACCEPT         = -18,    //App does not accept, can be re-selected
	UEMV_SCRIPT_FAIL          = -17,	//Issuer script execution failed
	UEMV_ARPC_FAIL            = -16,	//Issuer authentication failed
	UEMV_DECLINED             = -15,	//Transaction rejection
	UEMV_CANCEL               = -14,	//deal canceled
	UEMV_ONLINE               = -13,	//Transaction should be online
	UEMV_CVM_FAIL             = -12,    //Cardholder verification failed
	UEMV_APP_EXPIRED          = -11,    //Application has expired
	UEMV_APP_EFFECT           = -10,    //App has not yet taken effect
	UEMV_AUTH_FAIL            = -9,     //Data authentication failed
	UEMV_FALLBACK             = -8,		//Transaction fallback
	UEMV_APP_BLOCK            = -7,		//App locked
	UEMV_CANDIDATELIST_EMPTY  = -6,		//No common application
	UEMV_PARA_ERR             = -5,     //Parameter error
	UEMV_CARD_BLOCK           = -4,     //Card locked
	UEMV_COMMAND_FAIL         = -3,     //Card reading failed
	UEMV_CARD_REMOVED         = -2,		//The card was removed during the transaction
	UEMV_FAIL 				  = -1,		//Execution failed
	UEMV_OK					  =  0,		//Execution succeed
	UEMV_OTHER_INTERFACE	  =  1,		//Please try other communication interface
	UEMV_QPBOC_OFFLINE		  =  2,		//Non-contact QPBOC transactions are accepted offline
	UEMV_QPBOC_ONLINE         =  3,		//Non-contact QPBOC transaction online
	UEMV_PBOC_ONLINE          = 4,		//Non-contact PBOC transaction online
	//UEMV_MSD_ONLINE         = 5		//Contactless MSD transaction online
	UEMV_EC_ACCEPT            = 6,      //Electronic cash offline acceptance
	UEMV_OFFLINE_ACCEPT       = 7       //Standard process offline acceptance
} EmvStatus;

//Terminal parameter structure
typedef struct { 
    char    TermCap[3] ;          /*Terminal performance '9F33'*/
    char    AdditionalTermCap[5] ;/*Terminal additional performance*/
    char    IFDSerialNum[9] ;	  /*IFD serial number '9F1E'*/
    char    TermCountryCode[2] ;  /*Terminal country code '9F1A'*/
    char    TermID[9] ;           /*Terminal identification '9F1C'*/
    char    TermType ;            /*Terminal type '9F35'*/
    char    TransCurrCode[2] ;    /*Transaction currency '5F2A'*/
    char    TransCurrExp;         /*Transaction currency index '5F36'*/
    //PSE Selection
    char    bPSE;                 /*Whether to support the choice PSE 1*/
    char    bCardHolderConfirm;   /*Whether to support cardholder confirmation 1*/
    char    bPreferedOrder;		  /*Whether to support the preferred display 1*/
    char    bPartialAID;          /*Whether to support partial AID matching 1*/
    char    bMultiLanguage;       /*Whether to support multiple languages 0*/
    char    bCommonCharset;       /*Whether to support public character sets 0*/
    //Data Authentication
    char    bIPKCValidtionCheck;  /*Whether to check the validity of the issuer's public key authentication 1*/
    char    bContainDefaultDDOL;  /*Whether to include the defaultDDOL 1*/
    char    bCAPKFailOperAction;  /*CAPK Is operator intervention required when reading an error? 1*/
    char    bCAPKChecksum;		  /*Whether to perform CAPK check 1*/
    //Cardholder Verification Method
    char    bBypassPIN;           /*Whether to support skipping PIN input (requires change process, to be determined)*/
    char    bGetDataForPINCounter;/*PIN Try to check if the counter is supportedGetData 1*/
    char    bFailCVM;			  /*Whether to support the wrong CVM (must be Yes)*/
    char    bAmountBeforeCVM;     /*CVM Whether the amount is known before 1*/
    //Term Risk Management
    char    bLimitFloorCheck;     /*Whether to perform a minimum check 1*/
    char    bRandomTransSelect;   /*Whether to make random trading choices 1*/
    char    bValocityCheck;       /*Whether to check the frequency 1*/
    char    bTransLog;            /* Whether to record the transaction log 1*/
    char    bExceptionFile;       /*Whether to support card blacklist 1*/
    char    bTRMBaseOnAIP;        /*Whether terminal risk management is based on application interaction characteristics 1*/
    //Terminal Action Analysis
    char    bTerminalActionCodes; /*Whether to support terminal behavior code 1*/
    char    bDefActCodesBefore1stGenAC; /*Is the default behavior code prior to FirstGenerateAC ?*/
    char    bDefActCodesAfter1stGenAC;  /*Is the default behavior code after FirstGenerateAC ?*/
    //Completion Processing
    char    bForceOnline;        /*Whether to allow forced online 1*/
    char    bForceAccept;        /*Whether to allow forced acceptance of transactions 1*/
    char    bAdvices;            /*Whether to support notification 0*/
    char    bIISVoiceReferal;    /*Whether to support the voice reference initiated by the card issuer ?*/
    char    bCardVoiceReferal;   /*Whether to support the voice reference initiated by the card issuer ?*/
    char    bBatchDataCapture;   /*Whether to support batch data collection*/
    char    bDefaultTDOL;        /*Is there a default? TDOL*/
    //Exception Handling
    char    cEntryModeUsingMagStripe; /*POSEntryMode value when the IC card is faulty and can only be swiped*/
    char    bAccountSelect;      /*Whether to support account selection*/
}TERMCONFIG; 


//EMV_AID Parameter structure
typedef struct
{
	byte AID[16];						//AID
	byte AID_Length;					//AID length
	byte bAppSelIndicator;				//Application selection indicator
	byte bTerminalPriority;				//Terminal priority
	/* Domestic */
	byte bMaxTargetDomestic;			/*Offset randomly selected maximum target percentage*/
	byte bTargetPercentageDomestic;		/*Randomly selected target percentage*/
	byte abTFL_Domestic[4];				/* Terminal minimum */
	byte abThresholdValueDomestic[4];	/*Offset randomly selected threshold*/
	/* International */
	byte bMaxTargetPercentageInt;		/*Offset randomly selected maximum target percentage*/
	byte bTargetPercentageInt;			/*Randomly selected target percentage*/
	byte abTFL_International[4];		/* Terminal minimum */
	byte abThresholdValueInt[4];		/*Offset randomly selected threshold*/
	
	byte abTerminalApplVersion[4];		/* Terminal application version */
	byte abMerchantCategoryCode[2];		/* Business category code tag: 9F15 */        
	byte bTransactionCategoryCode;		/* Transaction category code Europay only, tag: 9F53 */
	byte abTrnCurrencyCode[2];			/* Currency code tag: 5F2A */
	byte abTerminalCountryCode[2];		/* Country code terminal tag: 9F1A */
	byte TAC_Default[5];				/* TAC Default data format (n5) */    
	byte TAC_Denial[5];					/* TAC Refuse: data format (n5) */    
	byte TAC_Online[5];					/* TAC Online: data format (n5) */  
	byte abDDOL[20];					/* DDOL */
	byte DDOL_Length;					/* DDOL Length */
	byte abTDOL[20];					/* TDOL */
	byte TDOL_Length;					/* TDOL Length */
	byte abTrnCurrencyExp;				/* tag: 5F36 */
	byte abEC_TFL[6];					/* Terminal electronic cash transaction limit tag: 9F7B n12*/
	byte TerminalType;					/* Terminal type: data format (n 3) */
	char cOnlinePinCap;					/* Terminal online pin capability */
	byte TerminalCap[3];				/* Terminal capability: data format (n 3) */
	byte AddTerminalCap[5];				/* Terminal additional performance :data format (n 3) */
	byte abRFOfflineLimit[6];			/*Contactless offline minimum :DF19*/
	byte abRFTransLimit[6];				/*Contactless transaction limit:DF20*/
	byte abRFCVMLimit[6];				/*Terminal performs CVM quota: DF21*/
	byte abTransProp[4];			    /*Terminal transaction attribute: 9F66*/
	byte bStatusCheck;          	    /*Non-contact status check, 0x00-Not checking,0x01-checking*/
	byte abAcquirerID[6];         	    /*Acquirer line identifier:9F01*/
}APPLICATIONPARAMS;

//EMV_AID Parameter total structure
typedef struct
{
	byte bTermAppCount;//Actual number of AID parameters
	APPLICATIONPARAMS TermApp[UMAX_TERMINAL_APPL];
}TERMINALAPPLIST;

//CAPublic key structure
typedef struct
{								
	byte RID[5];					/* Registered Application Provider Identifier */
	byte CA_PKIndex;				/* Certification Authority Public Key Index */
	byte CA_HashAlgoIndicator;		/* Certification Authority Public Key Hash Algorithm Identification */
	byte CA_PKAlgoIndicator;		/* Certification Authority Public Key Algorithm Identifier */
	byte LengthOfCAPKModulus;		/* Certification Center Public Key Mode Length */
	byte CAPKModulus[248];			/* Certification center public key model */
	byte LengthOfCAPKExponent;		/* Certification Authority Public Key Index Length */
	byte CAPKExponent[3];			/* Certification Authority Public Key Index */
	byte ChecksumHash[20];			/* Certification Authority Public Key Check Value */
	byte CAPKExpDate[4];			/* Certification Authority Public Key Validity Period */
}CAPUBLICKEY;

//EMV Callback
typedef struct
{
	int (*EMV_InputPasswd)(char cType, ushort chance,char *pszPin);
	int (*EMV_InputAmount)(byte *Amount);
}STEMVCALLBACKFUN;
//Non-connected mode enumeration
typedef enum
{
	UEMV_RF_PBOC        = 0,     //Non-connected PBOC standard process
	UEMV_RF_QPBOC       = 1,     //Non-connectedqPBOC
	//UEMV_RF_MSD       = 2,	 //Non-connected MSD
	UEMV_RF_PBOC_SINGLE = 3		 //Non-connected PBOC streamlined process
}EmvRFType;

//Card BIN blacklist structure
typedef struct
{
  byte bBINLen;
  byte abBIN[10];		       /* 5A: BCD */
}EMVEXCEPTIONBIN;

//Card BIN blacklist total structure
typedef struct
{
  byte            bCount;  //the actual amount
  EMVEXCEPTIONBIN ExpBIN[UMAX_EXCEPTION_BIN_COUNT];
}EMVEXCEPTIONBINLIST;

//Transaction path type
#define CLSS_VISA_QVSDC          2   // qPBOC the way
#define CLSS_VISA_VSDC           3   // Complete non-connected PBOC mode

//AC Types
#define AC_AAC                0x00
#define AC_TC                 0x01
#define AC_ARQC               0x02

//Cardholder authentication method
#define RD_CVM_NO             0x00   // no CVM
#define RD_CVM_SIG            0x10   // signature
#define RD_CVM_ONLINE_PIN     0x11   // online PIN

//Kernel type
#define KERNTYPE_DEF             0
#define KERNTYPE_JCB             1
#define KERNTYPE_MC              2
#define KERNTYPE_VIS             3
#define KERNTYPE_PBOC            4
#define KERNTYPE_AE              5
#define KERNTYPE_RFU             6

//Non-contact transaction preprocessing structure
typedef struct
{
    ulong ulTermFLmt;       /* Terminal offline limit */
    ulong ulRdClssTxnLmt;   /* Card reader non-receiving transaction limit */
    ulong ulRdCVMLmt;       /* Card reader CVM limit */
    ulong ulRdClssFLmt;     /* Card reader non-offline limit*/
    byte aucAID[17];        /* Application AID */
    byte ucAidLen;          /* Application AID length*/
    byte ucKernType;        /* Application kernel number
							KERNTYPE_DEF: The kernel matches itself according to the RID
							KERNTYPE_JCB: JCB.
							KERNTYPE_MC: MASTERCARD.
							KERNTYPE_VIS: VISA.
							KERNTYPE_PBOC: PBOC.
							KERNTYPE_AE: American Express.*/
    // payWave				//The parameters of QPBOC are also set in this block.
    byte ucCrypto17Flg;		/* MSD Whether CVN17 supports flags, 0-does not supported, 1-support*/
    byte ucZeroAmtNoAllowed;/* The amount is 0 check mark, 0-check amount is 0, and if the amount is 0, it will request online; 1 - check amount is 0, and the amount is not allowed to be 0; 2 - check whether the amount is 0*/
    byte ucStatusCheckFlg;  /* Status check flag, 0-not supported (do not check the amount, do not modify TTQ), 1- support (At this time, if the transaction amount is 1 yuan, the kernel must force the modification of TTQ to request the connection)*/
    byte aucReaderTTQ[5];   /* Terminal transaction attribute TTQ*/
    // common
    byte ucTermFLmtFlg;		/* Terminal offline quota check flag, 0 - no check, 1- check and quota exists, 2- check but quota does not exist */
    byte ucRdClssTxnLmtFlg;	/* The reader does not accept the transaction limit, check the mark, 0-do not check, 1-check and the limit exists, 2- check but the limit does not exist*/
    byte ucRdCVMLmtFlg;		/* Card reader CVM quota check flag, 0 - no check, 1- check and quota exists, 2- check but quota does not exist*/
    byte ucRdClssFLmtFlg;	/* The card reader is not connected to the offline limit check flag, 0 - no check, 1- check and the limit exists, 2- check but the limit does not exist*/
    byte aucRFU[2];
} Clss_PreProcInfo;

//Non-connected transaction related parameter structure
typedef struct
{
    ulong ulAmntAuth;          // Authorized amount(ulong)
    ulong ulAmntOther;         // Other amount(ulong)
    ulong ulTransNo;           // Transaction sequence counter(4 BYTE)
    byte ucTransType;          // Transaction Type '9C'
    byte aucTransDate[4];      // Transaction date YYMMDD	3-byte BCD end 0x00
    byte aucTransTime[4];      // Transaction time HHMMSS	3-byte BCD end 0x00
} Clss_TransParam;

//Application information structure
typedef struct
{
    char  szAID[32 + 1];       //AID  End of ASCII format "\0"
    char  szAppName[32 + 1];   //Application name ends in ASCII format "\0"
} STAPPINFO;

//Callback function structure 2
typedef struct
{
    int (*EMV_InputPasswd)(char cType, ushort chance, char *pszPin);
    int (*EMV_InputAmount)(byte *Amount);
    int (*EMV_cVerifyIDCard)(void); //Return value meaning Please refer to the function prototype description
    int (*EMV_cSelectAapp)(STAPPINFO *pstAPPList, int nAPPNum); //For the meaning of the return value, please refer to the function prototype description.
    int (*EMV_cqPBOCDodgeRefresh)(void *psCmdBuf);
    int (*EMV_cqPBOCDogeRemoveTrace)(void);
} STEMVCALLBACKFUN2;

//2.2.12 TMS class API

#define UMAX_APP_COUNT  30		//Maximum number of applications
#define UMAX_MODULE_COUNT  800  //Maximum number of downloaded files

//Application information structure
typedef struct
{
	char AppName[20+1];         //Application name
	char AppDispName[20+1];     //App display name, if there is 01000006 tag, then send the tag content
	char AppVar[15+1];          //Application version number, TMS system only supports 15-digit version number
	char TerminalID[8+1];		//Terminal number
	char ShopId[15+1];			//Business number
	byte bisMainApp;            //Whether the main control application, 0-no, 1- is
}UAPPINFO;

//Application information structure
typedef struct
{
	byte		bCount;                     //Actual application number
	UAPPINFO	AppInfo[UMAX_APP_COUNT];	//See struct UAPPINFO
}UAPPINFOLIST;

//Module type enumeration
typedef enum
{
	UMODULE_FILE     = 0,       //File, 2-5 files can use 0, distinguished by the master
	UMODULE_PARAFILE = 1,       //Parameter file
	UMODULE_TRADE    = 2,       //Business module
	UMODULE_PUBLIC   = 3,       //Common module
	UMODULE_API      = 4,       //API module
	UMODULE_PRIVATE  = 5,       //Manufacturer private library
	UMODULE_DATA     = 6,       //Data class file (reserved)
	UMODULE_DRIVER   = 7,	    //Hardware driver (reserved)
	UMODULE_OS       = 8,       //Underlying OS (reserved)
	UMODULE_APP      = 9        //Application, executable
}UModuleType;

//Module information structure
typedef struct
{
	char ModuleName[50];    //Module name
	int  ModuleType;        //See enum UModuleType
	char AppName[20+1];     //App name indicating that the file belongs to an app
}UMODULEINFO;

//Module information total structure
typedef struct
{
	ushort	nCount;								//Actual number of downloaded files
	UMODULEINFO ModuleInfo[UMAX_MODULE_COUNT];	//See struct UMODULEINFO
}UMODULEINFOLIST;

//TMS Download communication type enumeration
typedef enum
{
	UTMS_BYRS232 = 1,	   //Serial port
	UTMS_BYMODEM     = 2,  //MODEM asynchronous
	UTMS_BYETHENET   = 3,  //Wired Ethernet
	UTMS_BYWIFI      = 4,  //WIFI
	UTMS_BYGPRS      = 5,  //GPRS,WCDMA(WCDMA and GPRS parameters are the same)
	UTMS_BYCDMA      = 6,  //CDMA
	UTMS_BYMODEMPPP  = 7,  //MODEMPPP dials after walking TCPIP
	UTMS_BYUSB       = 8   //USB
}UTMSComType;

//TMS Download communication structure
typedef struct
{
	unsigned char ucCOMMType;  /*Communication type£ºSee enum UTMSCOMTYPE*/
	unsigned char ucTPDUFlag;  /*TPDU presence identifier: 0-none, 1-is*/
	unsigned char aucTPDU[5];  /*TPDU number (requires identification with TPDU)*/
	unsigned int  uiSockID;	   /*Tcpip communication Socket ID UTMSCOMTYPE 3,4,5,6,7*/
	unsigned long hCommHandle; /*Communication handle UTMSCOMTYP 1,2,8*/

	unsigned char ucPackNum;   /*The number of download packets continuously sent by the server during the download phase: minimum 1, maximum 8*/
	unsigned int uiFrameLen;   /*Length of the transmission data frame in the download phase (unit: byte)*/
	unsigned char ucSyncFlag;  /*Forcing the terminal to perform a one-to-one message exchange mode with the server: 0-off 1-open*/
	unsigned char ucIfCheck;   /*Download phase data verification identifier: 0 - no parity 1-check*/
	unsigned char ucBreakType; /*Whether the button is allowed during the download phase (cancel/clear key) interrupt download 0-not allowed 1-allow*/
	unsigned int  uiReTime;    /*After the communication packet receives timeout, the number of re-receives (that is, the number of times the server resends the message)*/
	unsigned int  uiTimeoutMs; /*Single communication packet reception timeout (unit: milliseconds)*/
	unsigned int   uiDelayTime;/*Delay before the terminal sends each packet (unit: milliseconds)*/
	unsigned int   uiSlotTime; /*Server-side continuous packet interval (in milliseconds)*/
	unsigned char  auReserver[100];  /*Reserved domain*/
	unsigned int   uiRFULen;   /*Extended space length*/
	void        *pvRFU;        /*Extended space pointer*/
	unsigned char DlTxnType;   /*Download transaction type 0-initialize, 1-change, 2-online report*/
}UTMSPARAMETERS;

//TMS class API return value enumeration
typedef enum
{	
	UTMS_TIMEOUT			= -3,   //time out
	UTMS_QUIT				= -2,	//cancel
	UTMS_FAIL               = -1,   //failure
	UTMS_OK                 =  0    //success
}UTMSStatus;

#define KEY_BUF_SIZE		128		//Keyboard input buffer length
//#define	ITWELLSYSINFOLEN	40		
#define SWIPEDANDINICEVENT	0xFF	//Standby interface with magnetic card operation
//#define INICEVENT			0xF0	//Standby interface to insert IC operation
#define XGDOK				0X01

#define BEEPERROR			1		//Buzzer is abnormally called
#define BEEPNORMAL      	0		//Buzzer is called normally
#define DECRYP				0		//Decrypt
#define ENCRYP				1		//Encryption

//The working state of pos, used for handling
#define WORK_STATUS			0		//Non-batch delivery status, working status
#define	UPLOGRMB			1		//Used to select different transaction records when sending batches
#define UPLOGFRN			2
#define UPLOGALL			3
#define UPLOGDETAILTYPE1	4		//The reconciliation is flat, and the subsequent single is sent
#define UPLOGDETAILTYPE2	4		//The reconciliation is not smooth, and the subsequent single is sent
#define		PIN_PED			0x00	//Built in
#define		PIN_PP			0x01	//External

#define		TIMEOUT			-2		//Time out

#define		COM_PAD_NO		0x00			//rs232 A
#define		PINPADCOM		0x01			//pinpad
#define		COM_RS232B_NO	0x02			//rs232 B
#define		USB_DEVICE		0x04
#define		USB_HOST		0x06

#define		MAX_LCD_LINENUM 			5	//The maximum number of lines that the LCD can display

#if (defined(V50X_MACHINE))
#define		MAX_LCDWIDTH				26
#else
#define		MAX_LCDWIDTH				20
#endif

#define		MAX_MENUNAME_LEN			14		//Maximum length of menu name
#define		SEARCH_DIRECTION_NEXT 		1
#define		SEARCH_DIRECTION_PREV 		0
#define		MCARDNO_MAX_LEN 			19		//Maximum length of the card number
#define		MAX_AMT_LEN					12		//Maximum amount of money
#define		MAX_PWD_LEN 				8		//Maximum password length
#define		BASE_YEAR 					2000	//Base year
#define		INPUT_TIMEOUT_VAL			30		//30s Enter the timeout value
#define		INPUT_INFINITE				-1
#define		INPUT_TIMEOUT 				-2		//Enter timeout code
#define		SCRIPT_SUCCESS				0		//The script ran successfully
#define		SCRIPT_CANCEL 				-1		//The script was canceled
#define		SCRIPT_ERROR				-3		//Script format error
#define		SCRIPT_NONEXIST				-4
#define		SCRIPT_CHECKERR				-5
#define		SCRIPT_MEMLACK				-6

#define MAX_RSA_MODULUS_LEN		512   // RSA maximum mode length
#define MAX_RSA_PRIME_LEN		256   // RSA maximum modulus prime length

// RSA public key structure definition
typedef struct{
unsigned int uiBits;							//Modulus, bit unit
unsigned char ucModulus[MAX_RSA_MODULUS_LEN];   //mold
unsigned char ucExponent[MAX_RSA_MODULUS_LEN];  //index
}RSAPUBLICKEY;
 
//RSA private key structure definition
typedef struct{
unsigned int uiBits;								 //Modulus, bit unit
unsigned char ucModulus[MAX_RSA_MODULUS_LEN];		 //mold
unsigned char ucPublicExponent [MAX_RSA_MODULUS_LEN];//Public key index
unsigned char ucExponent[MAX_RSA_MODULUS_LEN];		 //Private key index
unsigned char ucPrime[2][MAX_RSA_PRIME_LEN];		 //pq prime number, prime factor
unsigned char ucPrimeExponent[2][MAX_RSA_PRIME_LEN]; //CRT Index, prime and exponential division
unsigned char ucCoefficient[MAX_RSA_PRIME_LEN];		 //CRT Coefficient, prime and prime division
}RSAPRIVATEKEY;

#endif

