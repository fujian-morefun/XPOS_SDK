#ifndef __ERRORCODE_H__
#define __ERRORCODE_H__
#include "pub/pub.h"
#define ERR_BASE		(-1000)





/*****************UI interface error  *************************  */

#define UI_ERROR (ERR_BASE - 2000)

#define   NOLINE  (-1)   /* Number of rows is zero */
#define  LINE_OVER  (-2)    /* Exceeding the maximum number of rows */
#define  MAX_TIME_OVER  (-3)   /*Time Settings Over Maximum Time Settings*/
#define  MAX_LEN_OVER    (-4)  /* Data beyond maximum length */

#define TIMEOUT_EXIT            0 /*  Overtime Exit */
#define  SURE_EXIT                 2    /*Press OK to exit*/
#define  CANCLE_EXIT             1   /*  Press Cancel to Exit */



#define MF_MES_TIP_ERROR               1       /*Message error prompt box*/

#define UI_TIMEOUT   (UI_ERROR-3)  

/*****************USB Communication error*******************/
#define USB_BASE_ERROR           (ERR_BASE-200)

#define USB_FD_ERROR               (USB_BASE_ERROR-1)     /* File descriptor error  */
#define USB_MEMORY_ERROR      (USB_BASE_ERROR-2)     /*  Memory Error  */
#define USB_READ_TIME_OUT     (USB_BASE_ERROR-3)    /* Readout time out  */
#define USB_READ_ERROR           (USB_BASE_ERROR-4)    /*   */
#define USB_WRITE_TIME_OUT   (USB_BASE_ERROR-5)    /*   Write time timeout */
#define CONNECT_ERROR             (USB_BASE_ERROR-6)    /*  link error */
#define USB_OPEN_ERROR           (USB_BASE_ERROR-7)    /*  USB Failed to open   */
#define USB_INIT_ERROR            (USB_BASE_ERROR -8)  /* USB initialization failed */
#define USB_CLEAR_ERROR         (USB_BASE_ERROR-9)  /*USB Clearance failure*/
 

/*timeout*/
#define WRITE_TIME_OUT 2000  /*3 Second write timeout*/
#define READ_TIME_OUT  2000    /*10 seconds read USB timeout*/
#define LOW_TIME_OUT 30      /* Function Minimum Timeout */
#define HIGHT_TIME_OUT 120   /* */
#define SUIT_TIME_OUT 80     /* */





/***************** Communication error*******************/
#define ERR_COM			(ERR_BASE)
/*****************USB Communication error*******************/
#define ERR_COM_USB	(ERR_COM-100)
#define ERR_COM_USB_PARAM (ERR_COM_USB)

#define ERR_PPP			(ERR_COM-110)
#define ERR_PPP_PARAM	(ERR_PPP)
#define ERR_PPP_TIMEOUT	(ERR_PPP-1)
#define ERR_PPP_OVERNUM	(ERR_PPP-2)

#define ERR_COM_TCP		(ERR_COM-200)
#define ERR_TCP_FCNTL_FGETFL           (ERR_COM_TCP)                 /**<fcntl( F_GETFL ) error*/
#define ERR_TCP_FCNTL_FSETFL           (ERR_COM_TCP-1)             /**<fcntl( F_SETFL ) Eror non-blocking setup failed*/
#define ERR_TCP_REFUSED                    (ERR_COM_TCP-2)             /**<connect refused*/
#define ERR_TCP_SELECT                       (ERR_COM_TCP-3)            /**<select  error*/
#define ERR_TCP_SELECT_TIMEOUT      (ERR_COM_TCP-4)            /**<select  timeout*/
#define ERR_TCP_GETSOCKOPT             (ERR_COM_TCP-5)           /**<getsockopt error*/
#define ERR_TCP_CONNECT_SOMEERR  (ERR_COM_TCP-6)           /**<some error*/

/**< File operation error*/
#define ERR_FILE					(ERR_BASE-1000)		/**< File operation error*/
#define ERR_FILE_FILENAME		(ERR_FILE)			/**< File Name Null or File Name Length Error*/
#define ERR_FILE_RECLEN			(ERR_FILE-1)			/**< File record length error*/
#define ERR_FILE_FILELEN		(ERR_FILE-3)			/**< Error reading file length*/
#define ERR_FILE_PARAM_IVALID	(ERR_FILE-4)			/**< Illegal parameters*/
#define ERR_FILE_NO_SPACE		(ERR_FILE-5)			/**< Insufficient writing space*/
#define ERR_FILE_SEEK			(ERR_FILE-6)			/**< File Location Error*/
#define ERR_FILE_NOT_EXIST		(ERR_FILE-7)			/**< file does not exist*/
#define ERR_FILE_DEL_FILE		(ERR_FILE-8)			/**< File deletion error*/
#define ERR_FILE_DEL_IDX		(ERR_FILE-9)			/**< Index deletion error*/
#define ERR_FILE_CREAT_IDX		(ERR_FILE-10)		/**< Creating Index Error*/
#define ERR_FILE_CREAT_FILE		(ERR_FILE-11)		/**< Creating Index Error*/
#define ERR_FILE_CLOSE_FILE		(ERR_FILE-12)		/**< File Closing Error*/
#define ERR_FILE_OPEN_FILE		(ERR_FILE-13)		/**< Error opening file*/
#define ERR_FILE_READ_HEAD		(ERR_FILE-14)		/**< Error in header file*/
#define ERR_FILE_READ_FILE		(ERR_FILE-15)		/**< Error in header file*/
#define ERR_FILE_READ_REC		(ERR_FILE-16)		/**< Errors in reading and recording*/
#define ERR_FILE_READ_INDEX	(ERR_FILE-17)		/**< Reading Index Error*/
#define ERR_FILE_WRITE_REC		(ERR_FILE-18)		/**< Write Record Error*/
#define ERR_FILE_WRITE_HEAD	(ERR_FILE-19)		/**< Write Record Error*/
#define ERR_FILE_FIND_REC		(ERR_FILE-20)		/**< Find Record Errors*/
#define ERR_FILE_UPDATEINDEX	(ERR_FILE-21)		/**< Update Index Error*/
#define ERR_FILE_DELINDEX		(ERR_FILE-22)		/**< Delete index error*/	
#define ERR_FILE_MALLOC			(ERR_FILE-23)		/**< memory alloc error*/


/**< TLV perational errors */
#define ERR_TLV					(ERR_BASE -1100)		
#define ERR_TLV_COUNT			(ERR_TLV)			/**<Computing TLV Data Object Error*/
#define ERR_TLV_PARSER			(ERR_TLV -1)			/**< Analysis of TLV Data Errors*/
#define ERR_TLV_NULL			(ERR_TLV -2)			/**< TLV pointer is empty */
#define ERR_TLV_GETDATA		(ERR_TLV -3)			/**<TLV Data Acquisition Error*/
#define ERR_TLV_SRCLEN			(ERR_TLV -4)			/**< Source data length error*/
#define ERR_TLV_GETTMPLT		(ERR_TLV -5)			/**< TLV Getting Template Data Error*/
#define ERR_TLV_DATA_NOT_EXIST	(ERR_TLV -6)		/**< Data does not exist*/
#define ERR_TLV_TAG_FORMAT	(ERR_TLV -7)			/**<TAG format error*/
#define ERR_TLV_MAXLEN			(ERR_TLV -8)			/**< Beyond the maximum resolvable length*/


/******************************************************************************
 *  Function name:	Ex_Get_Public_ErrCode: 
 *	Introduction to Functions:	Get the error code
 *	Entrance parameters:	none
 *	Export parameters:     none
 * 	return value  :		Value of error code
 ******************************************************************************/
void Ex_Set_PublibErrCode(int nCode);
/******************************************************************************
 *  Function name:	Ex_Get_Public_ErrCode: 
 *	Introduction to Functions:	Get the error code
 *	Entrance parameters:	none
 *	Export parameters:     none
 * 	return value  :		Value of error code
 ******************************************************************************/
LIB_EXPORT int Ex_Get_Public_ErrCode();
#endif
