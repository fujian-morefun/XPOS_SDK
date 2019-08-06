#ifndef __ERRORCODE_H__
#define __ERRORCODE_H__
#include "pub/pub.h"
#define ERR_BASE		(-1000)





/***************** UI界面错误  *************************  */

#define UI_ERROR (ERR_BASE - 2000)

#define   NOLINE  (-1)   /* 行数为零 */
#define  LINE_OVER  (-2)    /* 超出最大行数 */
#define  MAX_TIME_OVER  (-3)   /*时间设置超过最大时间设置*/
#define  MAX_LEN_OVER    (-4)  /* 数据超出了最大长度 */

#define TIMEOUT_EXIT            0 /*  超时退出 */
#define  SURE_EXIT                 2    /*按确定键退出*/
#define  CANCLE_EXIT             1   /*  按取消键退出 */



#define MF_MES_TIP_ERROR               1       /*消息的出错提示框*/

#define UI_TIMEOUT   (UI_ERROR-3)  

/*****************USB 通讯错误*******************/
#define USB_BASE_ERROR           (ERR_BASE-200)

#define USB_FD_ERROR               (USB_BASE_ERROR-1)     /* 文件描述符出错  */
#define USB_MEMORY_ERROR      (USB_BASE_ERROR-2)     /*  内存出错  */
#define USB_READ_TIME_OUT     (USB_BASE_ERROR-3)    /* 读出时间超时  */
#define USB_READ_ERROR           (USB_BASE_ERROR-4)    /*   */
#define USB_WRITE_TIME_OUT   (USB_BASE_ERROR-5)    /*   写入时间超时 */
#define CONNECT_ERROR             (USB_BASE_ERROR-6)    /*  连接出错 */
#define USB_OPEN_ERROR           (USB_BASE_ERROR-7)    /*  USB 打开失败   */
#define USB_INIT_ERROR            (USB_BASE_ERROR -8)  /* USB初始化失败 */
#define USB_CLEAR_ERROR         (USB_BASE_ERROR-9)  /*USB 清除失败*/
 

/*超时时间*/
#define WRITE_TIME_OUT 2000  /*3秒钟写入超时时间*/
#define READ_TIME_OUT  2000    /*10秒读取USB超时时间*/
#define LOW_TIME_OUT 30      /* 函数最低超时时间 */
#define HIGHT_TIME_OUT 120   /* */
#define SUIT_TIME_OUT 80     /* */





/***************** 通讯错误*******************/
#define ERR_COM			(ERR_BASE)
/*****************USB 通讯错误*******************/
#define ERR_COM_USB	(ERR_COM-100)
#define ERR_COM_USB_PARAM (ERR_COM_USB)

#define ERR_PPP			(ERR_COM-110)
#define ERR_PPP_PARAM	(ERR_PPP)
#define ERR_PPP_TIMEOUT	(ERR_PPP-1)
#define ERR_PPP_OVERNUM	(ERR_PPP-2)

#define ERR_COM_TCP		(ERR_COM-200)
#define ERR_TCP_FCNTL_FGETFL           (ERR_COM_TCP)                 /**<fcntl( F_GETFL ) error*/
#define ERR_TCP_FCNTL_FSETFL           (ERR_COM_TCP-1)             /**<fcntl( F_SETFL ) error非阻塞式设置失败*/
#define ERR_TCP_REFUSED                    (ERR_COM_TCP-2)             /**<connect refused*/
#define ERR_TCP_SELECT                       (ERR_COM_TCP-3)            /**<select  error*/
#define ERR_TCP_SELECT_TIMEOUT      (ERR_COM_TCP-4)            /**<select  timeout*/
#define ERR_TCP_GETSOCKOPT             (ERR_COM_TCP-5)           /**<getsockopt error*/
#define ERR_TCP_CONNECT_SOMEERR  (ERR_COM_TCP-6)           /**<some error*/

/**< 文件操作错误*/
#define ERR_FILE					(ERR_BASE-1000)		/**< 文件操作错误*/
#define ERR_FILE_FILENAME		(ERR_FILE)			/**< 文件名为空或文件名长度错误*/
#define ERR_FILE_RECLEN			(ERR_FILE-1)			/**< 文件记录长度错误*/
#define ERR_FILE_FILELEN		(ERR_FILE-3)			/**< 读文件长度错误*/
#define ERR_FILE_PARAM_IVALID	(ERR_FILE-4)			/**< 参数不合法*/
#define ERR_FILE_NO_SPACE		(ERR_FILE-5)			/**< 写文件空间不足*/
#define ERR_FILE_SEEK			(ERR_FILE-6)			/**< 文件定位错误*/
#define ERR_FILE_NOT_EXIST		(ERR_FILE-7)			/**< 文件不存在*/
#define ERR_FILE_DEL_FILE		(ERR_FILE-8)			/**< 文件删除错误*/
#define ERR_FILE_DEL_IDX		(ERR_FILE-9)			/**< 索引删除错误*/
#define ERR_FILE_CREAT_IDX		(ERR_FILE-10)		/**< 创建索引错误*/
#define ERR_FILE_CREAT_FILE		(ERR_FILE-11)		/**< 创建文件错误*/
#define ERR_FILE_CLOSE_FILE		(ERR_FILE-12)		/**< 文件关闭错误*/
#define ERR_FILE_OPEN_FILE		(ERR_FILE-13)		/**< 打开文件错误*/
#define ERR_FILE_READ_HEAD		(ERR_FILE-14)		/**< 读头文件错误*/
#define ERR_FILE_READ_FILE		(ERR_FILE-15)		/**< 读文件错误*/
#define ERR_FILE_READ_REC		(ERR_FILE-16)		/**< 读记录错误*/
#define ERR_FILE_READ_INDEX	(ERR_FILE-17)		/**< 读索引错误*/
#define ERR_FILE_WRITE_REC		(ERR_FILE-18)		/**< 写记录错误*/
#define ERR_FILE_WRITE_HEAD	(ERR_FILE-19)		/**< 写文件头错误*/
#define ERR_FILE_FIND_REC		(ERR_FILE-20)		/**< 查找记录错误*/
#define ERR_FILE_UPDATEINDEX	(ERR_FILE-21)		/**< 更新索引错误*/
#define ERR_FILE_DELINDEX		(ERR_FILE-22)		/**< 删除索引错误*/	
#define ERR_FILE_MALLOC			(ERR_FILE-23)		/**< 内存分配错误*/


/**< TLV 操作错误 */
#define ERR_TLV					(ERR_BASE -1100)		
#define ERR_TLV_COUNT			(ERR_TLV)			/**< 计算TLV数据对象错误*/
#define ERR_TLV_PARSER			(ERR_TLV -1)			/**< 解析TLV数据错*/
#define ERR_TLV_NULL			(ERR_TLV -2)			/**< TLV指针为空*/
#define ERR_TLV_GETDATA		(ERR_TLV -3)			/**< TLV获取数据错误*/
#define ERR_TLV_SRCLEN			(ERR_TLV -4)			/**< 源数据长度错误*/
#define ERR_TLV_GETTMPLT		(ERR_TLV -5)			/**< TLV获取模板数据错误*/
#define ERR_TLV_DATA_NOT_EXIST	(ERR_TLV -6)		/**< 数据不存在*/
#define ERR_TLV_TAG_FORMAT	(ERR_TLV -7)			/**< TAG格式错误*/
#define ERR_TLV_MAXLEN			(ERR_TLV -8)			/**< 超出可解析的最大长度*/


/******************************************************************************
 *  函数名称:	Ex_Get_Public_ErrCode: 
 *	函数介绍:	获取错误码
 *	入口参数:	无
 *	出口参数:     无
 * 	返回值  :		错误码的值
 ******************************************************************************/
void Ex_Set_PublibErrCode(int nCode);
/******************************************************************************
 *  函数名称:	Ex_Get_Public_ErrCode: 
 *	函数介绍:	获取错误码
 *	入口参数:	无
 *	出口参数:     无
 * 	返回值  :		错误码的值
 ******************************************************************************/
LIB_EXPORT int Ex_Get_Public_ErrCode();
#endif
